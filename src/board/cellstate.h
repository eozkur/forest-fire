#ifndef CELLSTATEH
#define CELLSTATEH

/*!
 * \brief Used to track the state of a cell on the Board.
 */
enum CellState
{
    Empty, /*< A Cell with no special properties. */
    Tree, /*< A Cell that may either catch fire from an adjacent cell or catch on fire on its own randomly. */
    Fire /*< A Cell that spreads to all adjacent trees, then transforms into an empty Cell. */
};

#endif // CELLSTATEH
