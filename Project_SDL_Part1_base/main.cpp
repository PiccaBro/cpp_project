#include <stdio.h>
#include <string>

#include "application.h"

int main(int argc, char *argv[])
{
    if (argc != 5)
    {
        fprintf(stderr, "Usage : ./SDL_part1 n_sheep n_wolf n_dog time\n");
        fprintf(stderr, "\nParameters :\n");
        fprintf(stderr, "\tn_sheep\t : The number of sheep\n");
        fprintf(stderr, "\tn_wolf\t : The number of wolf\n");
        fprintf(stderr, "\tn_dog\t : The number of dog\n");
        fprintf(stderr, "\ttime\t : duration of the game (in seconds)\n");
        return 1;
    }
    std::cout << "Starting up the application" << std::endl;
    init();

    std::cout << "Done with initilization" << std::endl;

    std::shared_ptr<application> my_app =
        std::make_unique<application>(argc, argv);

    std::cout << "Created window" << std::endl;

    int retval = my_app->get_exit_code();

    std::cout << "Exiting application with code " << retval << std::endl;
    SDL_Quit();
    // return retval;
    return 0;
}