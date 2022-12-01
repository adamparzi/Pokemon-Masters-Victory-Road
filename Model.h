#ifndef MODEL_H
#define MODEL_H

#include <iostream>
#include "GameObject.h"
#include "Trainer.h"
#include "PokemonCenter.h"
#include "PokemonGym.h"
#include "View.h"

#include "WildPokemon.h"

using namespace std;

class Model
{
    private:

    int time;
    GameObject * object_ptrs[10];
    int num_objects; 
    Trainer* trainer_ptrs[10];
    int num_trainers;
    PokemonCenter * center_ptrs[10];
    int num_centers;
    PokemonGym * gym_ptrs[10];
    int num_gyms;
    WildPokemon* wildpokemon_ptrs[10];
    int num_wildpokemon;

    public: 

    Model();
    virtual ~Model();
    // add destructor to gym,trainer,center,and gameobject to confirm correct output

    Trainer * GetTrainerPtr(int id);
    PokemonCenter * GetPokemonCenterPtr(int id);
    PokemonGym * GetPokemonGymPtr(int id);
    WildPokemon * GetWildPokemonPtr(int id);
    bool Update();
    void Display(View &view); //View created later
    void ShowStatus();


};


#endif