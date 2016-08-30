#include "cell.h"

Cell::Cell(const unsigned short x, const unsigned short y)
{
    this->x = x;
    this->y = y;

    cellState = CellState::Empty;
}

Cell::~Cell()
{
}

unsigned short Cell::getX() const
{
    return x;
}

unsigned short Cell::getY() const
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
