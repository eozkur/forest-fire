#ifndef FORESTFIRESIMULATORH
#define FORESTFIRESIMULATORH

#include <stdlib.h>
#include <time.h>

#include "board/board.h"
#include "board/cell.h"

class ForestFireSimulator
{
public:
    ForestFireSimulator(const unsigned short boardHeight, const unsigned short boardWidth);
    ~ForestFireSimulator();

    unsigned short getP() const;
    void setP(const unsigned short p);

    unsigned short getF() const;
    void setF(const unsigned short f);

    unsigned short getSimulationSpeed() const;
    void setSimulationSpeed(const unsigned short simulationSpeed);

    unsigned short getBoardHeight() const;
    unsigned short getBoardWidth() const;

    void simulationStep();
    void startAutomatedSimulation();
    void stopAutomatedSimulation();

private:
    static const unsigned short PROBABILITY_100_PERCENT = 10000;

    unsigned short p;
    unsigned short f;
    unsigned short simulationSpeed;

    Board *board;

    bool doProbabilityCheck(const unsigned short probability, const unsigned short outOf) const;

    void growTrees();
    void igniteTrees();
    void spreadFire();
};

#endif // FORESTFIRESIMULATORH
