#include "WildPokemon.h"

using namespace std;

WildPokemon::WildPokemon(): 
GameObject('W')
{
    attack = 5;
    health = 2;
    variant = false;
    in_combat = false;
    current_trainer=0;
}

WildPokemon::WildPokemon(string name, double attack, double health, 
bool variant, int id, Point2D in_loc): 
GameObject(in_loc, id,'W')
{
    this->name = name;
    this->attack = attack;
    this->health = health;
    this->variant = variant;
    in_combat = false;
    current_trainer=0;
}

void WildPokemon::follow(Trainer* t){
    if (IsAlive()) {
        current_trainer = t; // may repeat, doesn't matter
        location = t->GetLocation(); // follows!
    }
}
bool WildPokemon::get_variant(){
    return variant;
}
double WildPokemon::get_attack(){
    return attack;
}
double WildPokemon::get_health(){
    return health;
}
bool WildPokemon::get_in_combat(){
    return in_combat;
}

bool WildPokemon::IsAlive(){
    if (health == 0)
        return false;
    else
        return true;
}

bool WildPokemon::Update(){
    if (!IsAlive() && state != DEAD){
        cout <<"** "<< name << " has fainted! **" << endl;
        state = DEAD;
        id_num = 'w';
        in_combat = false;
        return true;
    } else if (current_trainer && state != IN_TRAINER){ // NULL trainer pointer returns false!
        cout <<"** "<< name << " is following "<< current_trainer->GetName()<< " **"<<endl;
        state = IN_TRAINER;
        in_combat = true;
        return true;
    } 
    else return false;
}


void WildPokemon::ShowStatus(){
    cout<<name<<" status: " << endl;
    GameObject::ShowStatus();

    cout <<"Health: "<<health<<endl;
    cout <<"Attack damage: "<<attack<<endl;

    switch (state)  {
        case IN_ENVIRONMENT:
            cout << " currently hiding in tall grass" << endl;
            break;
        
        case DEAD:
            cout << " fainted" << endl;
            break;

        case IN_TRAINER: // same thing as in_combat?
            cout << " following trainer "<< current_trainer->GetName()<<endl;
            break;
    }


}

bool WildPokemon::ShouldBeVisible(){
    if (IsAlive())
        return true;
    return false;
}