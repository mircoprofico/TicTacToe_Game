#include <cstdlib>
#include "game.h"
#include "display.h"

//#include <iostream> // #3 Missing import for cerr
//#include <exception>    // #3 Missing import for exception
//#include <cstdlib>  // #3 Missing import for EXIT_SUCCESS

int main(int argc, char* argv[]) {  // Could use the [[maybe_unused]] compiler directive
    (void)argc; // #1 Okay for SDL but a comment have been appreciated. It is really ugly and unusual.
    (void)argv;

    const size_t ROW = 3;
    const size_t COL = 3;
    const size_t NB_ADJ_CELL_FOR_WIN = 3;

    try
    {
        Game  logic(ROW, COL);
        DisplayTTT display(logic);

        display.run();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';  // #3 Should have used std::endl instead of \n (compatibility)
    }
    return EXIT_SUCCESS;    // #9 It should not be a success if there has been an error
}