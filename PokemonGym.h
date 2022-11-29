#ifndef POKEMONGYM_H
#define POKEMONGYM_H

#include <iostream>
#include "Building.h"

using namespace std;

enum PokemonGymStates {
    NOT_DEFEATED = 0,
    DEFEATED = 1
};

class PokemonGym : public Building
{
    private:

    unsigned int num_battle_remaining;
    unsigned int max_number_of_battles;
    unsigned int health_cost_per_battle;
    double PokeDollar_cost_per_battle;
    unsigned int experience_per_battle;

    public:

    PokemonGym();
    PokemonGym(unsigned int, unsigned int, double, unsigned int, int, Point2D);
    virtual ~PokemonGym();

    double GetPokeDollarCost(unsigned int battle_qty);
    unsigned int GetHealthCost(unsigned int battle_qty);
    unsigned int GetNumBattlesRemaining();
    bool IsAbleToBattle(unsigned int battle_qty, double budget, unsigned int health);
    unsigned int TrainPokemon(unsigned int battle_units);
    unsigned int GetExperiencePerBattle();
    bool Update();
    bool passed();
    void ShowStatus();
};


#endif