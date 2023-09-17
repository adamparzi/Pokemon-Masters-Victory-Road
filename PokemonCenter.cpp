#include <iostream>
#include "PokemonCenter.h"


using namespace std;

    PokemonCenter::PokemonCenter()
    {
        display_code = 'C';
        potion_capacity = 100;
        num_potions_remaining = potion_capacity;
        pokedollar_cost_per_potion = 5;
        state = POTIONS_AVAILABLE;

        cout << "PokemonCenter default constructed" << endl;

    }
    PokemonCenter::PokemonCenter(int in_id, double potion_cost, unsigned int potion_cap, Point2D in_loc)
    {
        display_code = 'C';
        id_num = in_id;
        pokedollar_cost_per_potion = potion_cost;
        potion_capacity = potion_cap;
        num_potions_remaining = potion_capacity;
        location = in_loc;
        state = POTIONS_AVAILABLE;


        cout << "PokemonCenter constructed" << endl;

    }

    PokemonCenter::~PokemonCenter(){
        cout<<"PokemonCenter destructed"<<endl;
    }

    bool PokemonCenter::HasPotions(){
        if (num_potions_remaining >= 1)
            return true;
        else 
            return false;
    }
    unsigned int PokemonCenter::GetNumPotionsRemaining(){
        return num_potions_remaining;
    }
    bool PokemonCenter::CanAffordPotion(unsigned int potion, double budget){
        if ((potion*pokedollar_cost_per_potion) < budget)
            return true;
        else    
            return false;
    }
    double PokemonCenter::GetPokeDollarCost(unsigned int potion){
        return pokedollar_cost_per_potion * potion;
    }
    unsigned int PokemonCenter::DistributePotion(unsigned int potion_needed){
        if (num_potions_remaining >= potion_needed){
            num_potions_remaining -= potion_needed;
            return potion_needed;
        } else {
            potion_needed = num_potions_remaining; // same strat at TrainPokemon() in PokemonGym
            num_potions_remaining = 0;
            return potion_needed;
        }
    }
    bool PokemonCenter::Update(){
        if (!HasPotions() && state == POTIONS_AVAILABLE){
            state = NO_POTIONS_AVAILABLE;
            display_code = 'c';
            cout << "PokemonCenter " << id_num << " has ran out of potions." << endl;
            return true;
        } else
            return false;
    }
    void PokemonCenter::ShowStatus(){
        cout << "PokemonCenter Status: " << endl;
        Building::ShowStatus();
        cout << "PokeDollars per potion: " << pokedollar_cost_per_potion << endl
        << "has " << num_potions_remaining << " potion(s) remaining." << endl;
    }

