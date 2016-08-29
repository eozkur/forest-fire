#ifndef FORESTFIRESIMULATORH
#define FORESTFIRESIMULATORH

#include <stdlib.h>
#include <time.h>
#include <vector>

#include "board/board.h"
#include "board/cell.h"

class ForestFireSimulator
{
public:
    ForestFireSimulator(const unsigned int boardHeight, const unsigned int boardWidth);

    unsigned int getP() const;
    void setP(const unsigned int p);

    unsigned int getF() const;
    void setF(const unsigned int f);

    unsigned int getSimulationSpeed() const;
    void setSimulationSpeed(const unsigned int simulationSpeed);

    unsigned int getBoardHeight() const;
    unsigned int getBoardWidth() const;

    void simulationStep();
    void startAutomatedSimulation();
    void stopAutomatedSimulation();

private:
    static const unsigned int PROBABILITY_100_PERCENT = 10000;

    unsigned int p;
    unsigned int f;
    unsigned int simulationSpeed;

    Board *board;

    bool doProbabilityCheck(const unsigned int probability, const unsigned int outOf) const;

    void growTrees();
    void igniteTrees();
    void spreadFire();
};

#endif // FORESTFIRESIMULATORH
