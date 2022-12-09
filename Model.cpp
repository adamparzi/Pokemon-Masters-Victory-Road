#include <iostream>
#include "Model.h"

using namespace std;

int fainted_trainers = 0;
int passed_gyms = 0; // count to see if all gyms are passed/ trainers dead

Model::Model()
{
    time = 0;

    Trainer *T1 = new Trainer("Ash", 1, 'T', 2, Point2D(5, 1));
    Trainer *T2 = new Trainer("Misty", 2, 'T', 1, Point2D(10, 1));

    PokemonCenter *C1 = new PokemonCenter(1, 1, 100, Point2D(1, 20));
    PokemonCenter *C2 = new PokemonCenter(2, 2, 200, Point2D(10, 20));

    PokemonGym *G1 = new PokemonGym(10, 1, 2, 3, 1, Point2D(0, 0));
    PokemonGym *G2 = new PokemonGym(20, 5, 7.5, 4, 2, Point2D(5, 5));

    WildPokemon *W1 = new WildPokemon("WildPokemon1", 5, 2, false, 1, Point2D(10, 12));
    WildPokemon *W2 = new WildPokemon("WildPokemon2", 6, 3, false, 2, Point2D(15, 5));
    // pokemon2 slightly stronger & tankier

    object_ptrs.push_back(T1); // all 4 object types
    object_ptrs.push_back(T2);
    object_ptrs.push_back(C1);
    object_ptrs.push_back(C2);
    object_ptrs.push_back(G1);
    object_ptrs.push_back(G2);
    object_ptrs.push_back(W1);
    object_ptrs.push_back(W2);

    trainer_ptrs.push_back(T1); // all 4 object types
    trainer_ptrs.push_back(T2);
    center_ptrs.push_back(C1);
    center_ptrs.push_back(C2);
    gym_ptrs.push_back(G1);
    gym_ptrs.push_back(G2);
    wildpokemon_ptrs.push_back(W1);
    wildpokemon_ptrs.push_back(W2);

    active_ptrs.assign(object_ptrs.begin(), object_ptrs.end());

    num_objects = 8;

    num_trainers = 2;
    num_centers = 2;
    num_gyms = 2;
    num_wildpokemon = 2;

    cout << "Model default constructed" << endl;
}

Model::~Model()
{
    for (list<GameObject *>::iterator iter = object_ptrs.begin(); iter != object_ptrs.end(); iter++) // iterating over list
    {
        delete *iter;
    }
    cout << "Model destructed" << endl;
}

Trainer *Model::GetTrainerPtr(int id)
{
    for (list<Trainer *>::iterator iter = trainer_ptrs.begin(); iter != trainer_ptrs.end(); iter++)
    {
        if ((*iter)->GetId() == id)
            return *iter;
    }
    return 0; // return the null pointer if no id is matched
}
PokemonCenter *Model::GetPokemonCenterPtr(int id)
{
    for (list<PokemonCenter *>::iterator iter = center_ptrs.begin(); iter != center_ptrs.end(); iter++)
    {
        if ((*iter)->GetId() == id)
            return *iter;
    }
    return 0;
}
PokemonGym *Model::GetPokemonGymPtr(int id)
{
    for (list<PokemonGym *>::iterator iter = gym_ptrs.begin(); iter != gym_ptrs.end(); iter++)
    {
        if ((*iter)->GetId() == id)
            return *iter;
    }
    return 0;
}

bool Model::Update()
{
    time++;

    bool update_check = false; // temp bool; false if no update is true

    for (list<GameObject *>::iterator iter = active_ptrs.begin(); iter != active_ptrs.end(); iter++)
    {
        if ((*iter)->Update())
        {
            update_check = true; // turns true when ANY update is true
        }
    }

    for (list<PokemonGym *>::iterator iter = gym_ptrs.begin(); iter != gym_ptrs.end(); iter++)
    {
        if ((*iter)->passed())
            passed_gyms++;
    }

    if (passed_gyms == num_gyms)
    { // if all gyms are passed, done!
        cout << "GAME OVER: You win! All battles are done!" << endl;
        exit(0); // successful termination of program
    }

    for (list<Trainer *>::iterator iter = trainer_ptrs.begin(); iter != trainer_ptrs.end(); iter++)
    {

        if ((*iter)->HasFainted())
            fainted_trainers++;

        if (fainted_trainers == num_trainers)
        {
            cout << "GAME OVER: You lose! All of your Trainers' Pokemon have fainted!" << endl;
            cout << "Fainted trainers: " << fainted_trainers << endl;
            cout << "Num trainers: " << num_trainers << endl;

            exit(0);
        }
    }

    // PA4 - if any trainers are near a pokemon, pokemon should follow them
    for (list<Trainer *>::iterator iter = trainer_ptrs.begin(); iter != trainer_ptrs.end(); iter++)
    {
        Point2D trainer_loc = (*iter)->GetLocation();

        for (list<WildPokemon *>::iterator pokemon_iter = wildpokemon_ptrs.begin(); pokemon_iter != wildpokemon_ptrs.end(); pokemon_iter++)
        {
            Point2D pokemon_loc = (*pokemon_iter)->GetLocation();

            if (fabs(pokemon_loc.x - trainer_loc.x) <= 2 && fabs(pokemon_loc.y - trainer_loc.y) <= 2 && (*pokemon_iter)->IsAlive())
            {
                (*pokemon_iter)->follow(*iter);     // gives pokemon a current_trainer
                (*iter)->setPokemon(*pokemon_iter); // gives trainer a current_pokemon
            }
        }
    }

    for (list<GameObject *>::iterator iter = active_ptrs.begin(); iter != active_ptrs.end(); iter++)
    { // when its not on the grid, it's not an active pointer
        if (!(*iter)->ShouldBeVisible())
        {
            active_ptrs.erase(iter);
            cout << "Dead object removed" << endl;
        }
    }

    return update_check;
}

void Model::Display(View &view)
{
    Model::ShowStatus(); // starts by displaying current time and status

    for (list<GameObject *>::iterator iter = active_ptrs.begin(); iter != active_ptrs.end(); iter++)
    {
        view.Plot(*iter);
    }
}

void Model::ShowStatus()
{
    cout << "Time: " << time << endl;
    cout << "--- Object Statuses ---" << endl;

    for (list<GameObject *>::iterator iter = object_ptrs.begin(); iter != object_ptrs.end(); iter++)
    {
        (*iter)->ShowStatus();
    }
}

// PA4
void Model::NewCommand(char type, int id, double x, double y)
{
    if (type != 'c' && type != 'g' && type != 't' && type != 'w')
    {
        throw Invalid_Input("Bad new object command.");
    }

    if (id > 9)
    {
        throw Invalid_Input("ID can't be greater than 9");
    }

    switch (type)
    {
    case 'c':
    {
        for (list<PokemonCenter *>::iterator iter = center_ptrs.begin(); iter != center_ptrs.end(); iter++)
        {
            if (id == (*iter)->GetId())
                throw Invalid_Input("Invalid center ID.");
        }

        PokemonCenter *C = new PokemonCenter(id, 1, 100, Point2D(x, y));

        active_ptrs.push_back(C);
        center_ptrs.push_back(C);
        object_ptrs.push_back(C);

        cout << "New center created." << endl;
        break;
    }

    case 'g':
    {
        for (list<PokemonGym *>::iterator iter = gym_ptrs.begin(); iter != gym_ptrs.end(); iter++)
        {
            if (id == (*iter)->GetId())
                throw Invalid_Input("Invalid gym ID.");
        }

        PokemonGym *G = new PokemonGym(10, 1, 2, 1, id, Point2D(x, y));

        active_ptrs.push_back(G);
        gym_ptrs.push_back(G);
        object_ptrs.push_back(G);

        cout << "New gym created." << endl;
        break;
    }

    case 't':
    {
        for (list<Trainer *>::iterator iter = trainer_ptrs.begin(); iter != trainer_ptrs.end(); iter++)
        {
            if (id == (*iter)->GetId())
                throw Invalid_Input("Invalid trainer ID.");
        }
        Trainer *T = new Trainer("Joy", id, 'T', 1, Point2D(x, y));

        object_ptrs.push_back(T);
        trainer_ptrs.push_back(T);
        active_ptrs.push_back(T);

        cout << "New trainer created." << endl;
        break;
    }

    case 'w':
    {
        for (list<WildPokemon *>::iterator iter = wildpokemon_ptrs.begin(); iter != wildpokemon_ptrs.end(); iter++)
        {
            if (id == (*iter)->GetId())
                throw Invalid_Input("Invalid wild pokemon ID.");
        }
        WildPokemon *W = new WildPokemon("Summoned Pokemon", 3, 5, false, id, Point2D(x, y));

        object_ptrs.push_back(W);
        wildpokemon_ptrs.push_back(W);
        active_ptrs.push_back(W);

        cout << "New wild pokemon created." << endl;
        break;
    }

    default:
        cout << "Unknown command." << endl;
    }
}