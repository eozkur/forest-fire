#include "forestfiresimulator.h"

ForestFireSimulator::ForestFireSimulator(const unsigned short boardHeight, const unsigned short boardWidth)
{
    board = new Board(boardHeight, boardWidth);
    init();
}

ForestFireSimulator::ForestFireSimulator(Board *board)
{
    if (board == nullptr)
    {
        // TODO Way to notify (should throw exception?)
        throw std::exception();
    }

    this->board = board;
    init();
}

void ForestFireSimulator::init()
{
    this->p = 200;
    this->f = 10;

    srand(time(NULL));
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

bool ForestFireSimulator::doProbabilityCheck(const unsigned short probability, const unsigned short outOf) const
{
    int r = rand();
    if ((r % outOf) < probability)
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

    delete(emptyCells);
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

    delete(treeCells);
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

        delete(neighbors);
        currentCell->setCellState(CellState::Empty);
    }

    delete(fireCells);
}


