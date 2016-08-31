#include "board.h"

Board::Board(const unsigned short height, const unsigned short width)
{
    if (height > MAX_HEIGHT)
    {
        // TODO Way to notify (should throw exception?)
        throw std::exception();
    }

    if (width > MAX_WIDTH)
    {
        // TODO Way to notify (should throw exception?)
        throw std::exception();
    }

    this->height = height;
    this->width = width;

    // Populate cells
    cells = new std::vector<Cell *>();

    // Manually promote the shorts to ints to avoid compiler multiplication issues.
    unsigned int proposedSize = ((unsigned int)(height)) * ((unsigned int)(width));
    if (proposedSize > cells->max_size())
    {
        // TODO Way to notify (should throw exception?)
        throw std::exception();
    }

    cells->resize(height * width);

    for (unsigned short y = 0; y < height; ++y)
    {
        for (unsigned short x = 0; x < width; ++x)
        {
            unsigned int index;
            if (getIndexOf(x, y, index))
            {
                cells->at(index) = new Cell(x, y);
            }
            else
            {
                // TODO Way to notify (should throw exception?)
                throw std::exception();
            }
        }
    }
}

Board::~Board()
{
    for (unsigned int i = 0; i < cells->size(); ++i)
    {
        delete cells->at(i);
    }

    delete cells;
}

unsigned short Board::getHeight() const
{
    return height;
}

unsigned short Board::getWidth() const
{
    return width;
}

Cell *Board::getCell(const unsigned short x, const unsigned short y) const
{
    unsigned int index;
    if (getIndexOf(x, y, index) == false)
    {
        return nullptr;
    }

    return cells->at(index);
}

std::vector<Cell *> *Board::getNeighbors(const unsigned short x, const unsigned short y) const
{
    std::vector<Cell *> *neighbors = new std::vector<Cell *>();

    if (validateCoordinates(x, y) == false)
    {
        return nullptr;
    }

    unsigned int index;

    for (int yIndex = (y - 1); yIndex <= (y + 1); ++yIndex)
    {
        for (int xIndex = (x - 1); xIndex <= (x + 1); ++xIndex)
        {
            // Don't return the node that is at the requested coord
            if ((xIndex == x) && (yIndex == y))
            {
                continue;
            }

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

    for (unsigned int i = 0; i < cells->size(); ++i)
    {
        if (cells->at(i)->getCellState() == cellState)
        {
            Cell *cellPtr = cells->at(i);
            cellsWithState->push_back(cellPtr);
        }
    }

    return cellsWithState;
}

bool Board::getIndexOf(const int x, const int y, unsigned int &index) const
{
    if (validateCoordinates(x, y) == false)
    {
        return false;
    }

    index = ((width * y) + x);
    return true;
}

bool Board::validateCoordinates(const int x, const int y) const
{
    if (x < 0)
    {
        return false;
    }

    if (y < 0)
    {
        return false;
    }

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
