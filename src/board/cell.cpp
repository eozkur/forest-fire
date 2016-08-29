#include "cell.h"

Cell::Cell(const unsigned int x, const unsigned int y)
{
    this->x = x;
    this->y = y;

    cellState = CellState::Empty;
}

Cell::~Cell()
{
}

unsigned int Cell::getX() const
{
    return x;
}

unsigned int Cell::getY() const
{
    return y;
}

CellState Cell::getCellState() const
{
    return cellState;
}

void Cell::setCellState(const CellState newCellState)
{
    if (newCellState != cellState)
    {
        cellState = newCellState;
    }
}
