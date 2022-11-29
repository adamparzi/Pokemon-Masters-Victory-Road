#include <iostream>
#include "Building.h"

using namespace std; 

    Building::Building() 
    :GameObject('B') // default Building calls GameObject('B') + other Building member
    {   // ^ already said display_code = 'B' 
        trainer_count = 0;

        cout << "Building default constructed" << endl;
    }
    Building::Building(char in_code, int in_id, Point2D in_loc) 
    :GameObject(in_loc,in_id,in_code)
    {
        trainer_count = 0;

        cout << "Building constructed" << endl;
    }

    void Building::AddOneTrainer(){
        trainer_count++;
    }
    void Building::RemoveOneTrainer(){
        trainer_count--;
    }
    void Building::ShowStatus(){
        cout << display_code << id_num << " located at " << location << endl;
        if (trainer_count > 1 || trainer_count == 0)
            cout << trainer_count << " trainers are in this building" << endl;
        else
            cout << trainer_count << " trainer is in this building" << endl;
    }
    bool Building::ShouldBeVisible(){
        return true;
    }

