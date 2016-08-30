#include "tests/catch.hpp"

#include <limits.h>

#include "src/board/board.h"

TEST_CASE("Board")
{
    unsigned short maxHeight = Board::MAX_HEIGHT;
    unsigned short maxWidth = Board::MAX_WIDTH;

    SECTION("handles parameters correctly")
    {
        Board boardMin(0, 0);
        REQUIRE(boardMin.getHeight() == 0);
        REQUIRE(boardMin.getWidth() == 0);

        Board boardHeight(maxHeight, 1);
        REQUIRE(boardHeight.getHeight() == maxHeight);
        REQUIRE(boardHeight.getWidth() == 1);

        Board boardWidth(1, maxWidth);
        REQUIRE(boardWidth.getHeight() == 1);
        REQUIRE(boardWidth.getWidth() == maxWidth);

        Board boardMax(maxHeight, maxWidth);
        REQUIRE(boardMax.getHeight() == maxHeight);
        REQUIRE(boardMax.getWidth() == maxWidth);
    }

    SECTION("getCell operates correctly")
    {
        Board boardInvalid(0, 0);
        Cell *cellPtr = boardInvalid.getCell(0, 0);
        REQUIRE(cellPtr == nullptr);

        Board board(5, 5);
        cellPtr = board.getCell(0, 0);
        REQUIRE(cellPtr != nullptr);

        cellPtr->setCellState(CellState::Tree);
        cellPtr = board.getCell(0, 0);
        REQUIRE(cellPtr->getCellState() == CellState::Tree);
    }

    SECTION("getNeighbors operates correctly")
    {
        Board board(3, 3);
        std::vector<Cell *> *neighborsPtr;

        // check invalid access
        neighborsPtr = board.getNeighbors(4, 4);
        REQUIRE(neighborsPtr == nullptr);

        // check center access
        // TODO PICKUP
    }
}
