// [[Rcpp::depends(BH)]]

#ifndef SPATIAL_HASH_HPP
#define SPATIAL_HASH_HPP

#include <vector>
#include <cmath>
#include <unordered_map>
#include <utility>
#include <Rcpp.h>

#include "Cell.hpp"

typedef struct point {

  double x;
  double y;

  bool operator<(const struct point& other) const {

    return pow(x,2) + pow(y,2) < pow(other.x,2) + pow(other.y,2);

  }

  bool operator==(const struct point& other) const {

    return x == other.x && y == other.y;

  }

  bool operator!=(const struct point& other) const {

    return x != other.x || y != other.y;

  }

} Point;

namespace std {

  template<>
  struct hash<Point> {

    std::size_t operator()(const Point& p) const {

      return (51 + std::hash<int>()(p.x)) * 51 + std::hash<int>()(p.y);

    }

  };

}

class SpatialIterator;

class SpatialHash {

private:

  std::unordered_map<Point, Cell*> m_hash_map;
  std::vector<Cell*> m_cell_list;

  double m_bucket_size, m_bucket_tol;

  Point Hash(Cell*);
  Point Hash(Point);

  void RemoveKey(Cell*);

public:

  friend class SpatialIterator;
  friend class TestSpatialHash;

  SpatialHash(double);
  SpatialHash() {}
  ~SpatialHash() {}

  void AddKey(Cell*);
  void Insert(Cell*);
  void Delete(Cell*);
  //TODO: weird how this is called with cell refs
  void Update(Cell&, Cell&);

  Cell* GetRandomCell();
  int size();

  SpatialIterator getCircularIterator(Cell*,double);
  SpatialIterator getFullIterator();

};

class SpatialIterator {

private:

  SpatialHash* m_hash;
  
  std::vector<Point> search_points;
  signed int index;

public:

  friend class TestSpatialIterator;

  SpatialIterator(SpatialHash* hash) {
  
    m_hash = hash;
    std::vector<Cell*>::iterator iter = m_hash->m_cell_list.begin();
    
    for (; iter != m_hash->m_cell_list.end(); ++iter) {

      search_points.push_back(m_hash->Hash(*iter));

    }

    index = -1;
    
  }

  SpatialIterator(SpatialHash* hash, Point pt, double radius) {

    m_hash = hash;
    double max_rad = 2 * (m_hash->m_bucket_size + m_hash->m_bucket_tol);
    radius += max_rad;
    double x = pt.x - radius;
    double del_y, y;

    while (x < pt.x + radius) {

      del_y = pow(pow(radius,2) - pow(abs(x) - abs(pt.x), 2),0.5);
      y = pt.y - del_y;
    
      while (y < pt.y + del_y) {

        Point p = {x,y};

        p = m_hash->Hash(p);

        if (m_hash->m_hash_map.count(p) > 0 && m_hash->Hash(pt) != p) {
  
          search_points.push_back(p);

        }

        y += hash->m_bucket_size;

      }

      x += hash->m_bucket_size;

    }
          
    index = -1;

  }

  bool Next() {

    //may not be neccesary to have the first condition
    if ((!search_points.empty() && index < 0)
        || ((unsigned) (index + 1) < search_points.size())) {
    
      ++index;
      return true;

    } else {

      return false;

    }

  }
       
  Cell* getCell() {

    return m_hash->m_hash_map[search_points[index]];
    
  }

};

#endif
