#ifndef BOARDH
#define BOARDH

#include <vector>

#include "cell.h"

/*!
 * \brief Top-level Board access class for getting information about Cell.
 */
class Board
{
public:
    Board(const unsigned int height, const unsigned int width);
    ~Board();

    unsigned int getHeight() const;
    unsigned int getWidth() const;

    Cell *getCell(const unsigned int x, const unsigned int y) const;
    std::vector<Cell *> *getNeighbors(const unsigned int x, const unsigned int y) const;
    std::vector<Cell *> *getAllCellsWithState(const CellState cellState) const;

private:
    unsigned int height;
    unsigned int width;

    std::vector<Cell *> *cells;

    bool getIndexOf(const unsigned int x, const unsigned int y, unsigned long &index) const;
    bool validateCoordinates(const unsigned int x, const unsigned int y) const;
};

#endif // BOARDH
