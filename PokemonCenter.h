#ifndef POKEMONCENTER_H
#define POKEMONCENTER_H

#include <iostream>
#include "Building.h"


using namespace std;

enum PokemonCenterStates {
    POTIONS_AVAILABLE = 0,
    NO_POTIONS_AVAILABLE = 1
};

class PokemonCenter : public Building
{
    private:

    unsigned int potion_capacity;
    unsigned int num_potions_remaining;
    double pokedollar_cost_per_potion;

    public:

    PokemonCenter();
    PokemonCenter(int, double, unsigned int, Point2D);
    virtual ~PokemonCenter();

    bool HasPotions();
    unsigned int GetNumPotionsRemaining();
    bool CanAffordPotion(unsigned int, double);
    double GetPokeDollarCost(unsigned int);
    unsigned int DistributePotion(unsigned int);
    bool Update();
    void ShowStatus();


};






#endif