#ifndef CELLH
#define CELLH

#include "cellstate.h"

/*!
 * \brief A cell within the Board that holds a CellState.
 */
class Cell
{
public:
    Cell(const unsigned short x, const unsigned short y);
    ~Cell();

    unsigned short getX() const;
    unsigned short getY() const;

    CellState getCellState() const;
    void setCellState(const CellState newCellState);

private:
    unsigned short x;
    unsigned short y;

    CellState cellState;
};

#endif // CELLH
