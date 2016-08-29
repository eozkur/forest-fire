#ifndef CELLH
#define CELLH

#include "cellstate.h"

class Cell
{
public:
    Cell(const unsigned int x, const unsigned int y);

    unsigned int getX() const;
    unsigned int getY() const;

    CellState getCellState() const;
    void setCellState(const CellState newCellState);

private:
    unsigned int x;
    unsigned int y;

    CellState cellState;
};

#endif // CELLH
