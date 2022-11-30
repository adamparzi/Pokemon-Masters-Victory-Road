#include "WildPokemon.h"

using namespace std;

WildPokemon::WildPokemon(): 
GameObject('W')
{
    attack = 5;
    health = 2;
    variant = false;
    in_combat = false;
}

WildPokemon::WildPokemon(string name, double attack, double health, 
bool variant, int id, Point2D in_loc): 
GameObject(in_loc, id,'W')
{
    this->attack = attack;
    this->health = health;
    this->variant = variant;
    in_combat = false;
}

void WildPokemon::follow(Trainer* t){
    current_trainer = t;
    // also updates trainer info as needed
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
bool WildPokemon::Update(){
    if (!IsAlive()){
        cout <<"Pokemon " << name << " has fainted!" << endl;
        state = DEAD;
    }




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

        case IN_TRAINER:
            cout << " following trainer "<< current_trainer->GetName()<<endl;
            break;
    }


}
bool WildPokemon::IsAlive(){
    if (health == 0)
        return false;
    else
        return true;
}
