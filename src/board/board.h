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
    /*!
     * \brief Board
     * \param height Height of the board (Max is 10,000)
     * \param width Width of the board (Max is 10,000)
     */
    Board(const unsigned short height, const unsigned short width);
    ~Board();

    // Set the max limits since they seem to be near the memory limit.
    // TODO Investigate.
    static const unsigned short MAX_HEIGHT = 10000;
    static const unsigned short MAX_WIDTH = 10000;

    unsigned short getHeight() const;
    unsigned short getWidth() const;

    //! \returns Cell* at (x, y). If (x, y) is invalid, returns nullptr instead.
    Cell *getCell(const unsigned short x, const unsigned short y) const;

    //! \returns Cells surrounding (x, y). If (x, y) is invalid, returns nullptr instead.
    std::vector<Cell *> *getNeighbors(const unsigned short x, const unsigned short y) const;

    //! \returns All cells with the given CellState. Returns an empty vector if none are found.
    std::vector<Cell *> *getAllCellsWithState(const CellState cellState) const;

private:
    unsigned short height;
    unsigned short width;

    std::vector<Cell *> *cells;

    bool getIndexOf(const unsigned short x, const unsigned short y, unsigned int &index) const;
    bool validateCoordinates(const unsigned short x, const unsigned short y) const;
};

#endif // BOARDH
