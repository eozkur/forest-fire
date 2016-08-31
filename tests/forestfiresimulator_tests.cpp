#include "tests/catch.hpp"

#include <limits.h>

#include "src/forestfiresimulator.h"

TEST_CASE("ForestFireSimulator")
{
    // Catch doesn't like static variables in sections,
    //  so store max height/width locally.
    unsigned short maxHeight = Board::MAX_HEIGHT;
    unsigned short maxWidth = Board::MAX_WIDTH;

    SECTION("handles min parameters correctly")
    {
        ForestFireSimulator ffs(0, 0);
        REQUIRE(ffs.getBoardHeight() == 0);
        REQUIRE(ffs.getBoardWidth() == 0);
    }

    SECTION("handles max parameters correctly")
    {
        ForestFireSimulator ffs(maxHeight, maxWidth);
        REQUIRE(ffs.getBoardHeight() == maxHeight);
        REQUIRE(ffs.getBoardWidth() == maxWidth);
    }

    SECTION("handles random (valid) parameters correctly")
    {
        ForestFireSimulator ffs(4444, 5555);
        REQUIRE(ffs.getBoardHeight() == 4444);
        REQUIRE(ffs.getBoardWidth() == 5555);
    }

    SECTION("handles get/set P correctly")
    {
        ForestFireSimulator ffs(0, 0);

        ffs.setP(0);
        REQUIRE(ffs.getP() == 0);

        ffs.setP(USHRT_MAX);
        REQUIRE(ffs.getP() == USHRT_MAX);

        ffs.setP(4200);
        REQUIRE(ffs.getP() == 4200);
    }

    SECTION("handles get/set F correctly")
    {
        ForestFireSimulator ffs(0, 0);

        ffs.setF(0);
        REQUIRE(ffs.getF() == 0);

        ffs.setF(USHRT_MAX);
        REQUIRE(ffs.getF() == USHRT_MAX);

        ffs.setF(4200);
        REQUIRE(ffs.getF() == 4200);
    }

    SECTION("handles simulationStep correctly")
    {
        /*
         * 5x5 board
         *
         * F = fire
         * T = tree
         * X = empty
         *
         * Initial Step
         *
         * X T X T T
         * X T X T T
         * X T F X X
         * X X T X X
         * X X X T T
         */

        // Perform initial setup
        Board *board = new Board(5, 5);

        // first row
        board->getCell(1, 0)->setCellState(CellState::Tree);
        board->getCell(3, 0)->setCellState(CellState::Tree);
        board->getCell(4, 0)->setCellState(CellState::Tree);

        // second row
        board->getCell(1, 1)->setCellState(CellState::Tree);
        board->getCell(3, 1)->setCellState(CellState::Tree);
        board->getCell(4, 1)->setCellState(CellState::Tree);

        // third row
        board->getCell(1, 2)->setCellState(CellState::Tree);
        board->getCell(2, 2)->setCellState(CellState::Fire);

        // fourth row
        board->getCell(2, 3)->setCellState(CellState::Tree);

        // fifth row
        board->getCell(3, 4)->setCellState(CellState::Tree);
        board->getCell(4, 4)->setCellState(CellState::Tree);

        ForestFireSimulator ffs(board);

        // Disable random components.
        ffs.setP(0);
        ffs.setF(0);

        // verify setup
        REQUIRE(board->getAllCellsWithState(CellState::Fire)->size() == 1);
        REQUIRE(board->getAllCellsWithState(CellState::Tree)->size() == 10);
        REQUIRE(board->getAllCellsWithState(CellState::Empty)->size() == 14);

       /*
        * Step 1
        *
        * X T X T T
        * X F X F T
        * X F X X X
        * X X F X X
        * X X X T T
        */

        ffs.simulationStep();
        REQUIRE(board->getAllCellsWithState(CellState::Fire)->size() == 4);
        REQUIRE(board->getAllCellsWithState(CellState::Tree)->size() == 6);
        REQUIRE(board->getAllCellsWithState(CellState::Empty)->size() == 15);

        /*
         * Step 2
         *
         * X F X F F
         * X X X X F
         * X X X X X
         * X X X X X
         * X X X F T
         */

        ffs.simulationStep();
        REQUIRE(board->getAllCellsWithState(CellState::Fire)->size() == 5);
        REQUIRE(board->getAllCellsWithState(CellState::Tree)->size() == 1);
        REQUIRE(board->getAllCellsWithState(CellState::Empty)->size() == 19);

        /*
         * Step 3
         *
         * X X X X X
         * X X X X X
         * X X X X X
         * X X X X X
         * X X X X F
         */

        ffs.simulationStep();
        REQUIRE(board->getAllCellsWithState(CellState::Fire)->size() == 1);
        REQUIRE(board->getAllCellsWithState(CellState::Tree)->size() == 0);
        REQUIRE(board->getAllCellsWithState(CellState::Empty)->size() == 24);

        /*
         * Step 4
         *
         * X X X X X
         * X X X X X
         * X X X X X
         * X X X X X
         * X X X X X
         */

        ffs.simulationStep();
        REQUIRE(board->getAllCellsWithState(CellState::Fire)->size() == 0);
        REQUIRE(board->getAllCellsWithState(CellState::Tree)->size() == 0);
        REQUIRE(board->getAllCellsWithState(CellState::Empty)->size() == 25);
    }
}
