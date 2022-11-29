#include <iostream>
#include "Model.h"

using namespace std;

Model::Model(){
    time = 0;

    trainer_ptrs[0] = new Trainer("Ash", 1, 'T', 1, Point2D(5,1));
    trainer_ptrs[1] = new Trainer("Misty", 2, 'T',2,Point2D(10,1));

    center_ptrs[0] = new PokemonCenter(1, 1, 100, Point2D(1,20));
    center_ptrs[1] = new PokemonCenter(2, 2, 200, Point2D(10,20));

    gym_ptrs[0] = new PokemonGym(10, 1, 2.0, 3, 1, Point2D(0,0)); // CHANGE
    gym_ptrs[1] = new PokemonGym(20, 5, 7.5, 4, 2, Point2D(5,5));


    object_ptrs[0]=trainer_ptrs[0];
    object_ptrs[1]=trainer_ptrs[1];
    object_ptrs[2]=center_ptrs[0];
    object_ptrs[3]=center_ptrs[1];
    object_ptrs[4]=gym_ptrs[0];
    object_ptrs[5]=gym_ptrs[1];
    
    num_objects = 6;
    num_trainers=2;
    num_centers=2;
    num_gyms=2;

    cout << "Model default constructed"<<endl;
}

Model::~Model() {
    for (int i=0;i<num_objects;i++){
        delete object_ptrs[i];
    }
    cout<<"Model destructed"<<endl;
}

Trainer * Model::GetTrainerPtr(int id){
    for (int i=0;i<num_trainers;i++){
        if (trainer_ptrs[i]->GetId()==id){
            return trainer_ptrs[i];
            break;
        }
    }
    return 0; //return the null pointer if no id is matched
}
PokemonCenter * Model::GetPokemonCenterPtr(int id){
    for (int i=0;i<num_centers;i++){
        if (center_ptrs[i]->GetId()==id){
            return center_ptrs[i];
            break;
        }
    }
    return 0;
    
}
PokemonGym * Model::GetPokemonGymPtr(int id){
    for (int i=0;i<num_gyms;i++){
        if (gym_ptrs[i]->GetId()==id){
            return gym_ptrs[i];
            break;
        }
    }
    return 0;
}
bool Model::Update() {
    time++;

    bool update_check=false; // temp bool; false if no update is true
    int passed_gyms=0; //temp count to see if all gyms are passed
    int fainted_trainers=0;

    for (int i=0;i<num_objects;i++){
        if(object_ptrs[i]->Update())
            update_check=true;  //turns true when ANY update is true
    }

    for (int i=0;i<num_gyms;i++){
        if(gym_ptrs[i]->passed())
            passed_gyms++;
    }

    if (passed_gyms==num_gyms){ // if all gyms are passed, done!
        cout<<"GAME OVER: You win! All battles are done!"<<endl;
        exit(0); //successful termination of program
    }

    for (int i=0;i<num_trainers;i++){
        if(trainer_ptrs[i]->HasFainted())
            fainted_trainers++;
    }

    if (fainted_trainers==num_trainers){
        cout<<"GAME OVER: You lose! All of your Trainers' Pokemon have fainted!"<<endl;
        exit(0);
    }

    return update_check;
}

void Model::Display(View& view){
    Model::ShowStatus(); // starts by displaying current time and status

    for (int i=0;i<num_objects;i++){
        view.Plot(object_ptrs[i]);
    }

} //View created later

void Model::ShowStatus(){
    cout<<"Time: "<<time<<endl;
    cout<<"--- Object Statuses ---"<<endl;

    for (int i=0;i<num_objects;i++){
        object_ptrs[i]->ShowStatus();
    }
}   