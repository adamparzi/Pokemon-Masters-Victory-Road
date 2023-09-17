// #ifndef TRAINER_H
// #define TRAINER_H

#pragma once // replaces include guards?

#include <iostream>
#include <time.h>
#include <math.h>
#include "GameObject.h"
#include "PokemonGym.h"
#include "PokemonCenter.h"

#include "WildPokemon.h" //- CIRCULAR DEPENDANCY

using namespace std;

enum TrainerStates
{
    STOPPED = 0,
    MOVING = 1,
    FAINTED = 2,
    AT_CENTER = 3,
    IN_GYM = 4,
    MOVING_TO_CENTER = 5,
    MOVING_TO_GYM = 6,
    BATTLING_IN_GYM = 7,
    RECOVERING_HEALTH = 8
};

class WildPokemon;

class Trainer : public GameObject
{

public:
    Trainer();
    Trainer(char in_code);
    Trainer(string in_name, int in_id, char in_code, unsigned int in_speed, Point2D in_loc);

    virtual ~Trainer();

    void StartMoving(Point2D dest);
    void StartMovingToGym(PokemonGym *gym);
    void StartMovingToCenter(PokemonCenter *center);
    void StartBattling(unsigned int num_battles);
    void StartRecoveringHealth(unsigned int num_potions);
    void Stop();
    bool HasFainted();
    bool ShouldBeVisible();
    void ShowStatus();
    bool Update();

    void setPokemon(WildPokemon *pokemon); // PA4

    string GetName(); // SELF-IMPLEMENTED getter for name for Model

protected:
    bool UpdateLocation();
    void SetupDestination(Point2D dest);

private:
    double speed;
    bool is_at_center;
    bool is_IN_GYM;
    unsigned int health;
    unsigned int experience;
    double PokeDollars;
    unsigned int battles_to_buy;
    unsigned int potions_to_buy;
    string name;
    PokemonCenter *current_center;
    PokemonGym *current_gym;
    Point2D destination;
    Vector2D delta;

    WildPokemon *current_pokemon; // pa4
};

static double GetRandomAmountOfPokeDollars(); // states static, but doesnt specify it in example header...

// #endif