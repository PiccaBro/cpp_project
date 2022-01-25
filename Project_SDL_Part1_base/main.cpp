#include <stdio.h>
#include <string>

#include "application.h"

int main(int argc, char *argv[])
{
    std::cout << "Starting up the application" << std::endl;

    if (argc != 5)
        throw std::runtime_error("Need three arguments - "
                                 "number of sheep, number of wolves, "
                                 "simulation time\n");

    init();

    std::cout << "Done with initilization" << std::endl;

    std::shared_ptr<application> my_app =
        std::make_unique<application>(argc, argv);

    std::cout << "Created window" << std::endl;

    int retval = my_app->get_exit_code();

    // std::cout << "Exiting application with code " << retval << std::endl;
    SDL_Quit();
    // return retval;
    return 0;
}