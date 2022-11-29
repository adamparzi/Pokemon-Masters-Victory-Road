#include <iostream>
#include <fstream> // for filestream, reading and writing to file
#include <cmath>
#include <time.h>
#include <stdlib.h>
#include <iomanip>

#include "PokemonCenter.h"
#include "PokemonGym.h"
#include "Trainer.h"
#include "Model.h"
#include "GameCommand.h"
#include "View.h"

using namespace std;

Model model;
View view;

int main() {
    char command = ' ';
    int trainer_id;
    int gym_id;
    int center_id;
    Point2D p1;
    unsigned int num_battles;
    unsigned int num_potions;

    view.Clear(); // erases previous objects, if there were any

    model.Display(view); // shows time, all statuses, and sets all objects positions
    view.Draw(); // draws grid and object positions

    while (command != 'q') { // kinda arbitrary - should quit before reaching back  
        cout << "Enter command:" << endl;
        cin >> command;

        switch (command) // calls a function for appropriate command
        {
            case 'm':
                cin >> trainer_id >> p1.x >> p1.y;  //requests ADDITIONAL input from user
                DoMoveCommand(model, trainer_id, p1); //carries out command
            break;

            case 'c':
                cin >> trainer_id >> center_id;
                DoMoveToCenterCommand(model, trainer_id, center_id);
            break;

            case 'g':
                cin >> trainer_id >> gym_id;
                DoMoveToGymCommand(model, trainer_id, gym_id);
            break;

            case 's':
                cin >> trainer_id;
                DoStopCommand(model, trainer_id);
            break;

            case 'p':
                cin >> trainer_id >> num_potions;
                DoRecoverInCenterCommand(model, trainer_id, num_potions);
            break;

            case 'b':
                cin >> trainer_id >> num_battles;
                DoBattleCommand(model, trainer_id, num_battles);
            break;

            case 'a':
                DoAdvanceCommand(model, view);
            break;

            case 'r':
                DoRunCommand(model, view);
            break;

            case 'q':
                exit(0);
            break;
        }
    }

}