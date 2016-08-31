#ifndef FORESTFIRESIMULATORH
#define FORESTFIRESIMULATORH

#include <stdlib.h>
#include <time.h>

#include "board/board.h"
#include "board/cell.h"
#include "display/displaymanager.h"

class ForestFireSimulator
{
public:
    ForestFireSimulator(const unsigned short boardHeight, const unsigned short boardWidth);
    ForestFireSimulator(Board *board);
    ~ForestFireSimulator();

    unsigned short getP() const;
    void setP(const unsigned short p);

    unsigned short getF() const;
    void setF(const unsigned short f);

    unsigned short getBoardHeight() const;
    unsigned short getBoardWidth() const;

    void simulationStep();
    void runSimulation();

private:
    static const unsigned short PROBABILITY_100_PERCENT = 10000;

    unsigned short p;
    unsigned short f;

    Board *board;

    void init();
    bool doProbabilityCheck(const unsigned short probability, const unsigned short outOf) const;

    void growTrees();
    void igniteTrees();
    void spreadFire();
};

#endif // FORESTFIRESIMULATORH
