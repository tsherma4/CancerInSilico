#ifndef CIS_OFF_LATTICE_CELL_BASED_MODEL_H
#define CIS_OFF_LATTICE_CELL_BASED_MODEL_H

// abstract implementation of an off lattice cell model

#include "../Core/CellBasedModel.h"
#include "../Core/SquareLattice.h"
#include "OffLatticeCell.h"

typedef SquareLattice<OffLatticeCell>::iterator CellIterator;
typedef SquareLattice<OffLatticeCell>::local_iterator LocalCellIterator;

// second element is true if infinite
typedef std::pair<double, bool> Energy;

class OffLatticeCellBasedModel : public CellBasedModel
{
protected:

    // holds all of the cells
    SquareLattice<OffLatticeCell> mCellPopulation;

    // monte carlo updating parameters
    double mMaxDeformation;
    double mMaxTranslation;
    double mMaxRotation;

public:

    // constructor and virtual destructor
    OffLatticeCellBasedModel(Rcpp::S4*);
    virtual ~OffLatticeCellBasedModel() {}

    // get parameters
    double maxTranslation() const {return mMaxTranslation;}
    double maxRotation()    const {return mMaxRotation;}

    // find largest possible radius across cell types
    double maxRadius();    

    // single time step, Monte Carlo step
    void oneTimeStep(double);
    void oneMCStep();

    // update system
    void updateDrugs(double);
    void doTrial(OffLatticeCell&);
    void checkMitosis(OffLatticeCell&);

    // relevant functions for attempting/accepting trials
    virtual bool attemptTrial(OffLatticeCell&) = 0;
    virtual bool acceptTrial(Energy, Energy, unsigned, unsigned) const = 0;
    virtual Energy calculateHamiltonian(const OffLatticeCell&) = 0;
    virtual unsigned numNeighbors(const OffLatticeCell&) = 0;

    // check hard conditions on cell placement
    bool checkOverlap(const OffLatticeCell&);
    bool checkBoundary(const OffLatticeCell&);

    // iterators for cells in this model
    CellIterator begin() {return mCellPopulation.begin();}
    CellIterator end()   {return mCellPopulation.end();}    

    // do trials
    virtual double maxGrowth(OffLatticeCell&) const = 0;
    virtual double maxDeformation(OffLatticeCell&) const = 0;
    void growth(OffLatticeCell&);
    void translation(OffLatticeCell&);
    void deformation(OffLatticeCell&);
    void rotation(OffLatticeCell&);    

    // record the current stat of the population
    void recordPopulation();

    // size of cell population
    unsigned size() const {return mCellPopulation.size();}
};

#endif
