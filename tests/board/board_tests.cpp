#include "tests/catch.hpp"

#include <limits.h>

#include "src/board/board.h"

/*!
 * \brief checkNodes Checks every coordPair against the x, y coords of every Cell object in neightborsPtr.
 *
 * \param coordPairsXY A vector of x,y coord pairs that the Cell objects in neighborsPtr is expected to contain. This paramter will be emptied as coord pairs are found.
 * \param neighborsPtr Pointer to the return value of getNeighbors.
 *
 * \return True if every coordPair was found in neighborsPtr's Cell objects, false otherwise.
 */
bool checkNeighborCoords(
        std::vector<std::pair<unsigned short, unsigned short>> *coordPairsXY,
        const std::vector<Cell *> *neighborsPtr)
{
    unsigned int validNeighborCount = 0;

    for (unsigned int neighborsIndex = 0; neighborsIndex < neighborsPtr->size(); ++neighborsIndex)
    {
        Cell *currentCell = neighborsPtr->at(neighborsIndex);

        for (int coordIndex = 0; (unsigned int)coordIndex < coordPairsXY->size(); ++coordIndex)
        {
            std::pair<unsigned short, unsigned short> currentCoords = coordPairsXY->at(coordIndex);

            if ((currentCell->getX() == currentCoords.first) &&
                (currentCell->getY() == currentCoords.second))
            {
                // keep track of how many validNeighbors we found
                validNeighborCount += 1;

                // remove the coord pair so we can detect duplicate neighbors
                coordPairsXY->erase(coordPairsXY->begin() + coordIndex);

                // continue on to the next Cell
                break;
            }
        }
    }

    return (validNeighborCount == neighborsPtr->size());
}

TEST_CASE("Board")
{
    // Catch doesn't like static variables in sections,
    //  so store max height/width locally.
    unsigned short maxHeight = Board::MAX_HEIGHT;
    unsigned short maxWidth = Board::MAX_WIDTH;

    SECTION("handles min parameters correctly")
    {
        Board boardMin(0, 0);
        REQUIRE(boardMin.getHeight() == 0);
        REQUIRE(boardMin.getWidth() == 0);
    }

    SECTION("handles uneven parameters correctly")
    {
        Board boardHeight(maxHeight, 1);
        REQUIRE(boardHeight.getHeight() == maxHeight);
        REQUIRE(boardHeight.getWidth() == 1);

        Board boardWidth(1, maxWidth);
        REQUIRE(boardWidth.getHeight() == 1);
        REQUIRE(boardWidth.getWidth() == maxWidth);
    }

    SECTION("handles max parameters correctly")
    {
        Board boardMax(maxHeight, maxWidth);
        REQUIRE(boardMax.getHeight() == maxHeight);
        REQUIRE(boardMax.getWidth() == maxWidth);
    }

    SECTION("getCell handles invalid operation correctly")
    {
        Board boardInvalid(0, 0);
        Cell *cellPtr = boardInvalid.getCell(0, 0);
        REQUIRE(cellPtr == nullptr);
    }

    SECTION("getCell handles valid operation correctly")
    {
        Board board(5, 5);
        Cell *cellPtr = board.getCell(0, 0);
        REQUIRE(cellPtr != nullptr);

        cellPtr->setCellState(CellState::Tree);
        cellPtr = board.getCell(0, 0);
        REQUIRE(cellPtr->getCellState() == CellState::Tree);
    }

    SECTION("getNeighbors handles invalid coords correctly")
    {
        Board board(3, 3);
        std::vector<Cell *> *neighborsPtr;

        neighborsPtr = board.getNeighbors(3, 3);
        REQUIRE(neighborsPtr == nullptr);
    }

    SECTION("getNeighbors doesn't return the node at the requested coord")
    {
        Board board(3, 3);
        std::vector<Cell *> *neighborsPtr = board.getNeighbors(1, 1);
        REQUIRE(neighborsPtr != nullptr);

        // the node we requested shouldn't be included in the results
        for (unsigned int i = 0; i < neighborsPtr->size(); ++i)
        {
            Cell *cellPtr = neighborsPtr->at(i);
            if ((cellPtr->getX() == 1) && (cellPtr->getY() == 1))
            {
                REQUIRE(false);
            }
        }

        REQUIRE(true);
    }

    SECTION("getNeighbors returns all surrounding nodes (center)")
    {
        /*
         * 5x5 board
         *
         * C = cell that getNeighbors was called on
         * O = cells that neighbor C
         *      (the cells that should be returned by getNeighbors)
         * X = cells that do not neighbor C
         *
         * X X X X X
         * X O O O X
         * X O C O X
         * X O O O X
         * X X X X X
         */

        Board board(5, 5);
        std::vector<Cell *> *neighborsPtr = board.getNeighbors(2, 2);
        REQUIRE(neighborsPtr != nullptr);

        // Ensure that it returned all 8 surrounding nodes.
        REQUIRE(neighborsPtr->size() == 8);

        // Verify the coords of each returned node.
        std::vector<std::pair<unsigned short, unsigned short>> *coordPairsXY =
                new std::vector<std::pair<unsigned short, unsigned short>>();

        // Add all of the expected coords to coordPairsXY
        coordPairsXY->push_back(std::pair<unsigned short, unsigned short>(1, 1));
        coordPairsXY->push_back(std::pair<unsigned short, unsigned short>(2, 1));
        coordPairsXY->push_back(std::pair<unsigned short, unsigned short>(3, 1));

        coordPairsXY->push_back(std::pair<unsigned short, unsigned short>(1, 2));
        coordPairsXY->push_back(std::pair<unsigned short, unsigned short>(3, 2));

        coordPairsXY->push_back(std::pair<unsigned short, unsigned short>(1, 3));
        coordPairsXY->push_back(std::pair<unsigned short, unsigned short>(2, 3));
        coordPairsXY->push_back(std::pair<unsigned short, unsigned short>(3, 3));

        bool areNodesValid = checkNeighborCoords(coordPairsXY, neighborsPtr);

        delete coordPairsXY;
        REQUIRE(areNodesValid);
    }

    SECTION("getNeighbors returns all surrounding nodes (top)")
    {
        /*
         * 5x5 board
         *
         * C = cell that getNeighbors was called on
         * O = cells that neighbor C
         *      (the cells that should be returned by getNeighbors)
         * X = cells that do not neighbor C
         *
         * X O C O X
         * X O O O X
         * X X X X X
         * X X X X X
         * X X X X X
         */

        Board board(5, 5);
        std::vector<Cell *> *neighborsPtr = board.getNeighbors(2, 0);
        REQUIRE(neighborsPtr != nullptr);

        // Ensure that it returned all 5 surrounding nodes.
        REQUIRE(neighborsPtr->size() == 5);

        // Verify the coords of each returned node.
        std::vector<std::pair<unsigned short, unsigned short>> *coordPairsXY =
                new std::vector<std::pair<unsigned short, unsigned short>>();

        // Add all of the expected coords to coordPairsXY
        coordPairsXY->push_back(std::pair<unsigned short, unsigned short>(1, 0));
        coordPairsXY->push_back(std::pair<unsigned short, unsigned short>(3, 0));

        coordPairsXY->push_back(std::pair<unsigned short, unsigned short>(1, 1));
        coordPairsXY->push_back(std::pair<unsigned short, unsigned short>(2, 1));
        coordPairsXY->push_back(std::pair<unsigned short, unsigned short>(3, 1));

        bool areNodesValid = checkNeighborCoords(coordPairsXY, neighborsPtr);

        delete coordPairsXY;
        REQUIRE(areNodesValid);
    }

    SECTION("getNeighbors returns all surrounding nodes (top-right)")
    {
        /*
         * 5x5 board
         *
         * C = cell that getNeighbors was called on
         * O = cells that neighbor C
         *      (the cells that should be returned by getNeighbors)
         * X = cells that do not neighbor C
         *
         * X X X O C
         * X X X O O
         * X X X X X
         * X X X X X
         * X X X X X
         */

        Board board(5, 5);
        std::vector<Cell *> *neighborsPtr = board.getNeighbors(4, 0);
        REQUIRE(neighborsPtr != nullptr);

        // Ensure that it returned all 3 surrounding nodes.
        REQUIRE(neighborsPtr->size() == 3);

        // Verify the coords of each returned node.
        std::vector<std::pair<unsigned short, unsigned short>> *coordPairsXY =
                new std::vector<std::pair<unsigned short, unsigned short>>();

        // Add all of the expected coords to coordPairsXY
        coordPairsXY->push_back(std::pair<unsigned short, unsigned short>(3, 0));

        coordPairsXY->push_back(std::pair<unsigned short, unsigned short>(3, 1));
        coordPairsXY->push_back(std::pair<unsigned short, unsigned short>(4, 1));

        bool areNodesValid = checkNeighborCoords(coordPairsXY, neighborsPtr);

        delete coordPairsXY;
        REQUIRE(areNodesValid);
    }

    SECTION("getAllCellsWithState operates correctly")
    {
        Board board(5, 5);

        // Verify request with none found.
        std::vector<Cell *> *cellsWithState = board.getAllCellsWithState(CellState::Fire);
        REQUIRE(cellsWithState != nullptr);
        REQUIRE(cellsWithState->size() == 0);

        // Set some of the tiles for counting (1 fire, 2 trees, 22 empty)
        board.getCell(0, 0)->setCellState(CellState::Fire);

        board.getCell(1, 0)->setCellState(CellState::Tree);
        board.getCell(2, 0)->setCellState(CellState::Tree);

        // Verify correct counts
        cellsWithState = board.getAllCellsWithState(CellState::Fire);
        REQUIRE(cellsWithState != nullptr);
        REQUIRE(cellsWithState->size() == 1);

        cellsWithState = board.getAllCellsWithState(CellState::Tree);
        REQUIRE(cellsWithState != nullptr);
        REQUIRE(cellsWithState->size() == 2);

        cellsWithState = board.getAllCellsWithState(CellState::Empty);
        REQUIRE(cellsWithState != nullptr);
        REQUIRE(cellsWithState->size() == 22);
    }
}
