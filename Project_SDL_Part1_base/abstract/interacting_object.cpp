#include "../application.h"

int interacting_object::getStamina()
{
    return this->stamina;
}
int interacting_object::getMaxStamina()
{
    return this->max_stamina;
}

bool interacting_object::getSex()
{
    return this->sex;
}

bool interacting_object::getBirth()
{
    return this->give_birth;
}

bool interacting_object::isAlive()
{
    return this->alive;
}

void interacting_object::setBirth(bool give_birth)
{
    this->give_birth = give_birth;
}

void interacting_object::setSex(bool sex)
{
    this->sex = sex;
}

void interacting_object::setAlive(bool alive)
{
    this->alive = alive;
}

bool interacting_object::isPrey()
{
    return this->prey;
}

bool interacting_object::isPredator()
{
    return this->predator;
}

enum animal_type interacting_object::get_type()
{
    return this->a_type;
}

void interacting_object::set_type(enum animal_type type)
{
    a_type = type;
}

void interacting_object::setPrey(bool prey)
{
    this->prey = prey;
}

void interacting_object::setPredator(bool predator)
{
    this->predator = predator;
}

void interacting_object::setMaxStamina(int max)
{
    this->max_stamina = max;
}
void interacting_object::setStamina(int stamina, bool random)
{
    if (!(random && rand() % 6))
        this->stamina = stamina;
}
