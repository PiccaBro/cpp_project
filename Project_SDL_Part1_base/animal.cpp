#include "application.h"

/*
  +=====================================================+
  |                       ANIMAL                        |
  +=====================================================+
*/

// getters
enum animal_type animal::get_type()
{
    return a_type;
}

// setters
void animal::set_type(enum animal_type type)
{
    a_type = type;
}