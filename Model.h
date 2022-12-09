// #ifndef MODEL_H
// #define MODEL_H

#pragma once

#include <iostream>
#include "Trainer.h"
#include "PokemonCenter.h"
#include "PokemonGym.h"
#include "View.h"

#include <list>
#include "WildPokemon.h"

using namespace std;

class Model
{
private:
    int time;
    list<GameObject *> object_ptrs;
    list<GameObject *> active_ptrs;
    int num_objects;
    list<Trainer *> trainer_ptrs;
    int num_trainers;
    list<PokemonCenter *> center_ptrs;
    int num_centers;
    list<PokemonGym *> gym_ptrs;
    int num_gyms;

    list<WildPokemon *> wildpokemon_ptrs;
    int num_wildpokemon;

public:
    Model();
    virtual ~Model();
    // add destructor to gym,trainer,center,and gameobject to confirm correct output

    Trainer *GetTrainerPtr(int id);
    PokemonCenter *GetPokemonCenterPtr(int id);
    PokemonGym *GetPokemonGymPtr(int id);
    // WildPokemon *GetWildPokemonPtr(int id);
    bool Update();
    void Display(View &view); // View created later
    void ShowStatus();
};

// #endif