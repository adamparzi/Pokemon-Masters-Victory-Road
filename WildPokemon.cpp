#include "WildPokemon.h"

using namespace std;

WildPokemon::WildPokemon() : GameObject('W')
{
    attack = 5;
    health = 2;
    variant = false;
    in_combat = false;
    current_trainer = 0;
}

WildPokemon::WildPokemon(string name, double attack, double health,
                         bool variant, int id, Point2D in_loc) : GameObject(in_loc, id, 'W')
{
    this->name = name;
    this->attack = attack;
    this->health = health;
    this->variant = variant;
    in_combat = false;
    current_trainer = 0;
}

void WildPokemon::follow(Trainer *t)
{
    if (IsAlive() && !current_trainer)
    {
        current_trainer = t;
        location = current_trainer->GetLocation(); // set it initially to be quick
    }
}
bool WildPokemon::get_variant()
{
    return variant;
}
double WildPokemon::get_attack()
{
    return attack;
}
double WildPokemon::get_health()
{
    return health;
}
bool WildPokemon::get_in_combat()
{
    return in_combat;
}

bool WildPokemon::IsAlive()
{
    if (health > 0)
        return true;
    return false;
}

bool WildPokemon::Update()
{

    if (!IsAlive() && state != DEAD) // if dead AND dead state hasn't been assigned
    {
        cout << "** " << name << " has fainted! **" << endl;
        state = DEAD;
        id_num = 'w';
        in_combat = false;
        current_trainer = 0;
        return true;
    }

    if (!IsAlive()) // state must be DEAD
        return false;

    if (current_trainer && state != IN_TRAINER) // if trainer is assigned, and wasn't already assigned
    {                                           // NULL trainer pointer returns false!
        cout << "** " << name << " is following " << current_trainer->GetName() << " **" << endl;
        state = IN_TRAINER;
        in_combat = true;
        return true;
    }

    if (current_trainer) // state must be IN_TRAINER
    {
        location = current_trainer->GetLocation();
        health--; // pokemon hp goes down by 1 each step
    }

    return false;
}

void WildPokemon::ShowStatus()
{
    cout << name << " status: " << endl;
    GameObject::ShowStatus();

    cout << "Health: " << health << endl;
    cout << "Attack damage: " << attack << endl;

    if (!IsAlive())
    {
        cout << " fainted" << endl; // want immediate update
        return;
    }

    switch (state)
    {
    case IN_ENVIRONMENT:
        cout << " currently hiding in tall grass" << endl;
        break;

    case IN_TRAINER: // same thing as in_combat?
        cout << " following trainer " << current_trainer->GetName() << endl;
        break;
    }
}

bool WildPokemon::ShouldBeVisible()
{
    if (IsAlive())
        return true;
    return false;
}