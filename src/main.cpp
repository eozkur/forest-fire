#define CATCH_CONFIG_RUNNER
#include "tests/catch.hpp"

#include <chrono>
#include <ctime>

#include "display/displaymanager.h"
#include "forestfiresimulator.h"

int main(int argc, char *argv[])
{
    // Program argument strings
    const std::string runAllTestsArgument = "--run-all-tests";

    // Parse command line arguments
    if (argc > 1 && !strcmp(argv[1], runAllTestsArgument.c_str()))
    {
        return Catch::Session().run();
    }

    // Begin the simulation.
    Board *board = new Board(1600, 1800);

    DisplayManager dm(board);

    ForestFireSimulator ffs(board);

    // TODO fix framesPerSecond
    int framesPerSecond = 1;

    std::chrono::time_point<std::chrono::high_resolution_clock> start;
    std::chrono::duration<double> elapsed;

    // Run the simulation loop
    do
    {
        std::chrono::high_resolution_clock::time_point start(
                    std::chrono::high_resolution_clock::now());

        ffs.simulationStep();

        bool keepRendering = dm.renderBoard();
        if (keepRendering == false)
        {
            break;
        }

        elapsed = (std::chrono::high_resolution_clock::now() - start);

    } while (elapsed.count() < (1000 / framesPerSecond));

    return 0;
}
