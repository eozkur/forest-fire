#include "forestfiresimulator.h"

ForestFireSimulator::ForestFireSimulator(const unsigned short boardHeight, const unsigned short boardWidth)
{
    board = new Board(boardHeight, boardWidth);

    this->p = 200;
    this->f = 10;
    this->simulationSpeed = 60;
}

ForestFireSimulator::~ForestFireSimulator()
{
    delete board;
}

unsigned short ForestFireSimulator::getP() const
{
    return p;
}

void ForestFireSimulator::setP(const unsigned short p)
{
    this->p = p;
}

unsigned short ForestFireSimulator::getF() const
{
    return f;
}

void ForestFireSimulator::setF(const unsigned short f)
{
    this->f = f;
}

unsigned short ForestFireSimulator::getSimulationSpeed() const
{
    return simulationSpeed;
}

void ForestFireSimulator::setSimulationSpeed(const unsigned short simulationSpeed)
{
    this->simulationSpeed = simulationSpeed;
}

unsigned short ForestFireSimulator::getBoardHeight() const
{
    return board->getHeight();
}

unsigned short ForestFireSimulator::getBoardWidth() const
{
    return board->getWidth();
}

void ForestFireSimulator::simulationStep()
{
    growTrees();
    igniteTrees();
    spreadFire();
}

void ForestFireSimulator::startAutomatedSimulation()
{

}

void ForestFireSimulator::stopAutomatedSimulation()
{

}

bool ForestFireSimulator::doProbabilityCheck(const unsigned short probability, const unsigned short outOf) const
{
    srand(time(NULL));

    if ((rand() % outOf) < probability)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void ForestFireSimulator::growTrees()
{
    // 1) An empty cell turns into a tree with probability p.
    std::vector<Cell*> *emptyCells = board->getAllCellsWithState(CellState::Empty);
    for (unsigned int i = 0; i < emptyCells->size(); ++i)
    {
        if (doProbabilityCheck(p, PROBABILITY_100_PERCENT))
        {
            emptyCells->at(i)->setCellState(CellState::Tree);
        }
    }
}

void ForestFireSimulator::igniteTrees()
{
    // 2) A tree ignites with probability f.
    std::vector<Cell*> *treeCells = board->getAllCellsWithState(CellState::Tree);
    for (unsigned int i = 0; i < treeCells->size(); ++i)
    {
        if (doProbabilityCheck(f, PROBABILITY_100_PERCENT))
        {
            treeCells->at(i)->setCellState(CellState::Fire);
        }
    }
}

void ForestFireSimulator::spreadFire()
{
    // 3) A tree will burn if at least one neighbor is burning.
    // 4) A burning cell turns into an empty cell
    //   (after it spreads its own fire)
    std::vector<Cell*> *fireCells = board->getAllCellsWithState(CellState::Fire);
    for (unsigned int i = 0; i < fireCells->size(); ++i)
    {
        Cell *currentCell = fireCells->at(i);
        std::vector<Cell*> *neighbors = board->getNeighbors(currentCell->getX(), currentCell->getY());

        for (unsigned short i = 0; i < neighbors->size(); ++i)
        {
            Cell* currentNeighbor = neighbors->at(i);

            if (currentNeighbor->getCellState() == CellState::Tree)
            {
                currentNeighbor->setCellState(CellState::Fire);
            }
        }

        currentCell->setCellState(CellState::Empty);
    }
}


