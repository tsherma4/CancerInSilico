#include <cmath>
#include <Rcpp.h>

#include "OffLatticeCell.h"
#include "../Core/Random.h"

OffLatticeRadiusSolver OffLatticeCell::mSolver = OffLatticeRadiusSolver();

// constructor
OffLatticeCell::OffLatticeCell(CellType type) : Cell(type)
{
    clearTrialRecord();
    mCoordinates = Point<double>(0.0, 0.0);
    setRadius(sqrt(mType.size()));
    mAxisAngle = Random::uniform(0, 2 * M_PI);
}

// set radius of cell - adjust axis length accordingly
void OffLatticeCell::setRadius(double rad)
{
    mRadius = rad;
    mAxisLength = 2 * mRadius;
}

// set axis length of cell - adjust radius accordingly
void OffLatticeCell::setAxisLength(double len)
{
    if (len < sqrt(8 * mType.size()))
    {
        throw std::invalid_argument("adjusting axis on interphase cell");
    }
    mAxisLength = len;
    double adjusted = len / sqrt(mType.size());
    mRadius = sqrt(mType.size()) * mSolver.radius(adjusted);
}

// undergo cell division, return daughter cell
void OffLatticeCell::divide(OffLatticeCell& daughter)
{
    // update coordinates
    daughter.setCoordinates(centers().first);
    setCoordinates(centers().second);

    // update state of parent
    setRadius(sqrt(mType.size()));
    mAxisAngle = Random::uniform(0, 2 * M_PI);
    mPhase = INTERPHASE;
    mReadyToDivide = false;
    clearTrialRecord();
}

// go to random point in the cell cycle
void OffLatticeCell::gotoRandomCyclePoint()
{
    double chance = 1 - 2 / (mCycleLength + 2);
    if (Random::uniform(0,1) < chance) // random point of interphase
    {
        mPhase = INTERPHASE;
        setRadius(Random::uniform(sqrt(mType.size()),
            sqrt(2 * mType.size())));
    }
    else // random point of mitosis
    {
        mPhase = MITOSIS;
        setAxisLength(Random::uniform(sqrt(8 * mType.size()),
            sqrt(16 * mType.size())));
    }
}

// calculate the center of each side of the 'dumbell' shape
std::pair< Point<double>, Point<double> > OffLatticeCell::centers() const
{
    std::pair< Point<double>, Point<double> > centers;
    
    // offset from true center in both dimensions
    double xOffset = ((0.5 * mAxisLength) - mRadius) * cos(mAxisAngle);
    double yOffset = ((0.5 * mAxisLength) - mRadius) * sin(mAxisAngle);

    // apply offset
    centers.first = Point<double>(mCoordinates.x + xOffset,
        mCoordinates.y + yOffset);
    centers.second = Point<double>(mCoordinates.x - xOffset,
        mCoordinates.y - yOffset);

    return centers;
}

// calculate distance between two cells (distance between edges)
double OffLatticeCell::distance(const OffLatticeCell& b) const
{
    // find smallest between two centers 
    double minD = centers().first.distance(b.centers().first);
    minD = std::min(minD, centers().first.distance(b.centers().second));
    minD = std::min(minD, centers().second.distance(b.centers().first));
    minD = std::min(minD, centers().second.distance(b.centers().second));

    // return distance (between centers) minus the radii
    return minD - radius() - b.radius();
}

bool OffLatticeCell::operator!=(const OffLatticeCell& other) const
{
    return coordinates() != other.coordinates();
}

bool OffLatticeCell::operator==(const OffLatticeCell& other) const
{
    return coordinates() == other.coordinates();
}

// clear accept/reject trail record
void OffLatticeCell::clearTrialRecord()
{
    mAcceptedTrials = 0;
    mTotalTrials = 0;
}

// add trial to record
void OffLatticeCell::addToTrialRecord(bool result)
{
    mTotalTrials += 1;
    if (result) {mAcceptedTrials += 1;}
}

// get trial record, return 1 if low number of trials done
double OffLatticeCell::getTrialRecord()
{
    return mTotalTrials < 5 ? 1 : mAcceptedTrials / mTotalTrials;
}

