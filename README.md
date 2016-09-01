# forest-fire
An implementation of the forest fire cellular automata simulation with a simple SDL powered front-end.

The intent of this project is a hello, world! of sorts for playing around with different development tools and libraries.

## Forest Fire Simulation Rules
    1) An empty cell turns into a tree with probability p.
    2) A tree ignites with probability f.
    3) A tree will burn if at least one neighbor is burning.
    4) A burning cell turns into an empty cell.
	
## Command Line Arguments
--run-all-tests Runs all tests in the tests directory using [Catch](https://github.com/philsquared/Catch), then returns.

## Developers
forest-fire is currently being developed as a 32-bit program for Windows using Qt Creator 4.0.2 and the MinGW 5.3.0 32-bit compiler.

### TODO List
	- Fix frames per second counter in main.cpp
	- Update all throw exceptions to assert statements.
	- Add a real command line arg parser.
	- Add command line arguments for setting the board size.

### Generating Documentation
forest-fire uses [Doxygen](http://www.stack.nl/~dimitri/doxygen/) to generate its documentation. To regenerate the docs, simply run docs/generate-docs.bat.

### Running Tests
forest-fire uses [Catch](https://github.com/philsquared/Catch) to run its unit tests. To run all of the tests, run forest-fire with the --run-all-tests command line argument.

	forest-fire.exe --run-all-tests
	
### Deploying
Build forest-fire for your target machine, then zip the contents of your bin folder.

### Contributing
Currently, the project is small enough to not worry about anything formal. If you are interested in helping, just send me an email.
