// #ifndef WILDPOKEMON_H
// #define WILDPOKEMON_H
#pragma once

#include <iostream>
#include "GameObject.h"
#include "Point2D.h"
#include "Trainer.h"

using namespace std;

enum PokemonStates
{
    IN_ENVIRONMENT = 0, // default already set by gameobj constructor
    DEAD = 1,
    IN_TRAINER = 2
};

class Trainer;
class WildPokemon : public GameObject
{
protected:
    double attack;
    double health;
    bool variant;
    bool in_combat;
    string name;
    Trainer *current_trainer;

public:
    WildPokemon();
    WildPokemon(string name, double attack, double health,
                bool variant, int id, Point2D in_loc);

    void follow(Trainer *t);
    bool get_variant();
    double get_attack();
    double get_health();
    bool get_in_combat();
    bool Update();
    void ShowStatus();
    bool IsAlive();
    bool ShouldBeVisible();
    void TakeDamage();
};

// #endif