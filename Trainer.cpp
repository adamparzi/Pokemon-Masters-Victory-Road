#include <iostream>
#include "Trainer.h"
#include "time.h"
#include "math.h"

using namespace std;

Trainer::Trainer()
:GameObject('T')
{
    state = STOPPED;
    speed = 5;
    is_at_center = false;
    is_IN_GYM = false;
    health = 20;
    experience = 0;
    PokeDollars = 0;
    battles_to_buy=0;
    potions_to_buy=0;
    current_center=0;
    current_gym=0;
    //delta is assigned as needed in SetupDestination()

    cout << "Trainer default constructed" << endl;
}

Trainer::Trainer(char in_code)
:GameObject(in_code)
{
    speed = 5;
    state = STOPPED;
    is_at_center = false;
    is_IN_GYM = false;
    health = 20;
    experience = 0;
    PokeDollars = 0;
    battles_to_buy=0;
    potions_to_buy=0;
    current_center=0;
    current_gym=0;

    cout << "Trainer constructed" << endl;
}

Trainer::Trainer(string in_name, int in_id, char in_code, unsigned int in_speed, Point2D in_loc)
:GameObject(in_loc,in_id,in_code)
{
    state = STOPPED;
    speed = in_speed;
    name = in_name;
    is_at_center = false;
    is_IN_GYM = false;
    health = 20;
    experience = 0;
    PokeDollars = 0;
    battles_to_buy=0;
    potions_to_buy=0;
    current_center=0;
    current_gym=0;

    cout << "Trainer constructed" << endl;
}

Trainer::~Trainer(){
    cout<<"Trainer destructed"<<endl;
}

void Trainer::SetupDestination(Point2D dest){
    destination = dest;
    delta = (destination - location) * (speed/GetDistanceBetween(destination, location));

    if (state==AT_CENTER){ //if trainer is moving FROM a center
        current_center->RemoveOneTrainer();
    }
    if (state==IN_GYM){
        current_gym->RemoveOneTrainer();
    }
}

void Trainer::StartMoving(Point2D dest){
    
    if (GetDistanceBetween(location, dest)==0){
        cout << display_code<<id_num<<": I'm already there. See?" << endl;
    } else if(HasFainted()){
        cout <<display_code<<id_num<<": My pokemon have fainted. I cannot move and you cannot see me." << endl;
    } else {
        SetupDestination(dest);
        state = MOVING;
        cout << display_code<<id_num<<": On my way." << endl;
    }
}

void Trainer::StartMovingToGym(PokemonGym* gym){
    current_gym = gym;

    if (HasFainted()){
        cout << display_code << id_num<<": My Pokemon have fainted so I can't move to gym..." << endl;
    } else if (GetDistanceBetween(location, gym->GetLocation()) == 0) { // if already there!
        cout << display_code << id_num<<": I am already at the PokemonGym!" << endl;
    } else {
        SetupDestination(gym->GetLocation());
        state = MOVING_TO_GYM; // ORDER MATTERS here
        cout << display_code << id_num<<": On my way to Gym " << gym->GetId() << endl;
    }

}

void Trainer::StartMovingToCenter(PokemonCenter* center){
    current_center = center;

    if (HasFainted()){
        cout << display_code << id_num<<": My Pokemon have fainted so I can't move to the center..." << endl;
    } else if (GetDistanceBetween(location, center->GetLocation()) == 0) { // if already there!
        cout << display_code << id_num<<": I am already at the Center!" << endl;
    } else {
        SetupDestination(center->GetLocation());
        state = MOVING_TO_CENTER;
        cout << display_code << id_num<<": On my way to Center " << center->GetId() << endl;
    }
}

void Trainer::StartBattling(unsigned int num_battles){
    if (HasFainted()){
        cout << display_code << id_num<<": My Pokemon have fainted so no more battles for me..." << endl;
    } else if (state != IN_GYM){
        cout << display_code << id_num<<": I can only battle in a PokemonGym!" << endl;
    } else if (current_gym->GetPokeDollarCost(num_battles) > PokeDollars) {
        cout << display_code << id_num<<": Not enough money for battles..." << endl;
    } else if (current_gym->passed()) {
        cout << display_code << id_num<<" Cannot battle! This PokemonGym has no more trainers to battle!" << endl;
    } else {
        state = BATTLING_IN_GYM;
        battles_to_buy = num_battles; // CHECK - when to call update()?
        cout << display_code << id_num<<": Started to battle at the PokemonGym "<<current_gym->GetId()<< " with " <<num_battles<<" battle(s)" << endl;
    }
}

void Trainer::StartRecoveringHealth(unsigned int num_potions){
    if (HasFainted()){
        cout<<display_code<<id_num<<": My Pokemon have fainted and can't drink any potions..." << endl;
    } else if (state != AT_CENTER){
        cout<<display_code<<id_num<<": I can only recover health at a Pokemon Center!" << endl; //CANNOT command to buy potions multiple times within 1 tick
    } else if (!(current_center->CanAffordPotion(num_potions, PokeDollars))) {
        cout<< display_code<<id_num<<": Not enough money to recover health..." << endl;
    } else if (!(current_center->HasPotions())) {
        cout<<display_code<<id_num<<" Cannot recover! No potion remaining in this Pokemon Center." << endl;
    }
    else {
        state = RECOVERING_HEALTH;
        potions_to_buy = current_center->DistributePotion(num_potions);

        cout<<display_code<<id_num<<": Started recovering "<<potions_to_buy
            <<" potions at PokemonCenter "<<current_center->GetId()<<"."<<endl;

        // either increase health HERE, or call Update() to do it? depends on timing
        // when do you update? edit: figured out
        }
}

void Trainer::Stop(){
    state = STOPPED;
    cout <<display_code <<id_num<<": Stopping..."<<endl;
}

bool Trainer::HasFainted(){ // Has "just now" fainted
    if (health==0 && state !=FAINTED) // prevents continuous announcement that Ash is dead
        return true;
    else
        return false;

}

string Trainer::GetName(){
    return name;
}

bool Trainer::ShouldBeVisible(){
    if (state!=FAINTED) // can't call HasFainted() because want Ash to STAY invisible when dead 
        return true;
    else
        return false;
}

void Trainer::ShowStatus(){
    cout<<name<<" status: " << endl;
    GameObject::ShowStatus();

    //print 3 things for each state (might as well place outside switch)
    cout <<"Health: "<<health<<endl;
    cout <<"PokeDollars: "<<PokeDollars<<endl;
    cout <<"Experience: "<<experience<<endl;

    switch (state)  {
        case MOVING:
            cout<<" moving at a speed of "<<speed<<" to destination "<< destination<<" at each step of "
                << delta<<"."<<endl;
            break;

        case STOPPED:
            cout<< " stopped"<<endl;
            break;

        case MOVING_TO_GYM:
            cout<<" heading to PokemonGym "<<current_gym->GetId()<<" at a speed of "<<speed<<
                " at each step of " << delta<< "."<< endl;
            break;

        case MOVING_TO_CENTER:
            cout<<" heading to PokemonCenter "<<current_center->GetId()<<" at a speed of "<<speed<<
                " at each step of " << delta<< "."<< endl;
            break;
        
        case IN_GYM:
            cout <<" inside PokemonGym "<<current_gym->GetId()<<endl;
            break;
        
        case AT_CENTER:
            cout <<" inside PokemonCenter "<<current_center->GetId()<<endl;
            break;

        case BATTLING_IN_GYM:
            cout <<" battling in PokemonGym "<<current_gym->GetId()<<endl;
            break;

        case RECOVERING_HEALTH:
            cout<<" recovering health in PokemonCenter "<<current_center->GetId()<<endl;
            break;

        case FAINTED: // SELF-ADDED - fits well and informs player 
            cout<<" fainted"<<endl;
            break;
    }
}

bool Trainer::Update(){
    //how trainer moves
    //can't move when fainted!
    if (HasFainted()){
        cout<<name<<" is out of health and can't move!"<<endl; // map removes trainer before this is displayed, but 
            //since Update() is scarcely called, believe this is expected behavior
        state = FAINTED;
        return false;
    } 

    switch (state)  {
        case MOVING:
            if(UpdateLocation()){ // returns true when arrived to dest AND assigns loc=dest
                Stop();
                return true;
            } else
                return false;
            break;

        case STOPPED:
            return false;
            break;

        case MOVING_TO_GYM:
            if (UpdateLocation()){ 
                state = IN_GYM;
                current_gym->AddOneTrainer();
                return true;
            } else
                return false;
            break;

        case MOVING_TO_CENTER:
            if (UpdateLocation()){ 
                state = AT_CENTER;
                current_center->AddOneTrainer();
                return true;
            } else
                return false;
            break;
        
        case IN_GYM:
            return false;
            break;
        
        case AT_CENTER:
            return false;
            break;

        case BATTLING_IN_GYM:
            health-=current_gym->GetHealthCost(battles_to_buy);
            PokeDollars-=current_gym->GetPokeDollarCost(battles_to_buy);
            experience+=battles_to_buy*current_gym->GetExperiencePerBattle();
            // ^ Train shouldn't be called twice, so use this instead

            cout<<"** "<<name<<" completed "<<battles_to_buy<<" battles(s)! **"<<endl;
            cout<<"** "<<name<<" gained "<<current_gym->TrainPokemon(battles_to_buy)<<" experience! **"<<endl;
            //^ couts AND also calls Train 

            state = IN_GYM;
            return true;
            break;

        case RECOVERING_HEALTH:
            health += 5*potions_to_buy;
            PokeDollars-=current_center->GetPokeDollarCost(potions_to_buy);

            cout<<"** "<<name<<" bought "<<potions_to_buy<<" potions(s)! **"<<endl;
            cout<<"** "<<name<<" recovered "<<5*potions_to_buy<<" health! **"<<endl;
            
            state = AT_CENTER;
            return true;
            break;
        default:
            return false;
    }
}

bool Trainer::UpdateLocation(){
// how trainer moves
    if (fabs(destination.x-location.x)<=fabs(delta.x) && fabs(destination.y-location.y)<=fabs(delta.y)){ //skips a location if one step nearby
        location=destination;
        cout<<display_code<<id_num<<": I'm there!"<<endl;
        return true;
    } else {
        location=location+delta; //can't use += operator since we didn't overload that!
        health-=1;//battling pokemon in tall grass with each step!
        PokeDollars+=GetRandomAmountOfPokeDollars();
        cout <<display_code <<id_num<<": step..."<<endl;
        return false;
    }
}

static double GetRandomAmountOfPokeDollars(){
    srand(time(NULL));

    return (((double)rand())/ RAND_MAX)*2.0; // random double between 0.0 and 2.0
}