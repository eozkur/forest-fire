#include "forestfiresimulator.h"

ForestFireSimulator::ForestFireSimulator(const unsigned int boardHeight, const unsigned int boardWidth)
{
    board = new Board(boardHeight, boardWidth);

    this->p = p;
    this->f = f;
    this->simulationSpeed = simulationSpeed;
}

unsigned int ForestFireSimulator::getP() const
{
    return p;
}

void ForestFireSimulator::setP(const unsigned int p)
{
    this->p = p;
}

unsigned int ForestFireSimulator::getF() const
{
    return f;
}

void ForestFireSimulator::setF(const unsigned int f)
{
    this->f = f;
}

unsigned int ForestFireSimulator::getSimulationSpeed() const
{
    return simulationSpeed;
}

void ForestFireSimulator::setSimulationSpeed(const unsigned int simulationSpeed)
{
    this->simulationSpeed = simulationSpeed;
}

unsigned int ForestFireSimulator::getBoardHeight() const
{
    return board->getHeight();
}

unsigned int ForestFireSimulator::getBoardWidth() const
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

bool ForestFireSimulator::doProbabilityCheck(const unsigned int probability, const unsigned int outOf) const
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
    for (unsigned long i = 0; i < emptyCells->size(); ++i)
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
    for (unsigned long i = 0; i < treeCells->size(); ++i)
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
    for (unsigned long i = 0; i < fireCells->size(); ++i)
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


