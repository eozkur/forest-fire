#include "board.h"

Board::Board(const unsigned int height, const unsigned int width)
{
    this->height = height;
    this->width = width;

    cells = new std::vector<Cell *>();
}

unsigned int Board::getHeight() const
{
    return height;
}

unsigned int Board::getWidth() const
{
    return width;
}

Cell *Board::getCell(const unsigned int x, const unsigned int y) const
{
    unsigned long index;
    if (getIndexOf(x, y, index) == false)
    {
        return nullptr;
    }

    return cells->at(index);
}

std::vector<Cell *> *Board::getNeighbors(const unsigned int x, const unsigned int y) const
{
    std::vector<Cell *> *neighbors = new std::vector<Cell *>();

    if (validateCoordinates(x, y) == false)
    {
        return nullptr;
    }

    unsigned long index;

    for (unsigned int yIndex = (y - 1); yIndex <= (y + 1); ++yIndex)
    {
        for (unsigned int xIndex = (x - 1); xIndex <= (x + 1); ++xIndex)
        {
            if (getIndexOf(xIndex, yIndex, index) == false)
            {
                continue;
            }

            neighbors->push_back(getCell(xIndex, yIndex));
        }
    }

    return neighbors;
}

std::vector<Cell *> *Board::getAllCellsWithState(const CellState cellState) const
{
    std::vector<Cell *> *cellsWithState = new std::vector<Cell *>();

    for (unsigned long i = 0; i < cells->size(); ++i)
    {
        if (cells->at(i)->getCellState() == cellState)
        {
            Cell *cellPtr = cells->at(i);
            cellsWithState->push_back(cellPtr);
        }
    }

    return cellsWithState;
}

bool Board::getIndexOf(const unsigned int x, const unsigned int y, unsigned long &index) const
{
    if (validateCoordinates(x, y) == false)
    {
        return false;
    }

    index = ((width * y) + x);
    return true;
}

bool Board::validateCoordinates(const unsigned int x, const unsigned int y) const
{
    if (x >= width)
    {
        return false;
    }

    if (y >= height)
    {
        return false;
    }

    return true;
}
