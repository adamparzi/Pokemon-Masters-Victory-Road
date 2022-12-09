#include <iostream>
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
#include "Invalid_Input.h"

using namespace std;

Model model;
View view;

int main()
{
    char command = ' ';
    int trainer_id;
    int gym_id;
    int center_id;
    Point2D p1;
    unsigned int num_battles;
    unsigned int num_potions;
    unsigned int xnum;
    unsigned int ynum;
    char type;
    int new_id;

    view.Clear(); // erases previous objects, if there were any

    model.Display(view); // shows time, all statuses, and sets all objects positions
    view.Draw();         // draws grid and object positions

    while (command != 'q') // kinda arbitrary - should quit before reaching back
    {
        cout << "Enter command:" << endl;
        if (!(cin >> command))
            throw Invalid_Input("Bad command input");
        try
        {
            switch (command) // calls a function for appropriate command
            {
            case 'm':
                if (!(cin >> trainer_id >> p1.x >> p1.y))
                    throw Invalid_Input("Bad move command");

                DoMoveCommand(model, trainer_id, p1); // carries out command
                break;

            case 'c':
                if (!(cin >> trainer_id >> center_id))
                    throw Invalid_Input("Bad move to center command");

                DoMoveToCenterCommand(model, trainer_id, center_id);
                break;

            case 'g':
                if (!(cin >> trainer_id >> gym_id))
                    throw Invalid_Input("Bad move to gym command");

                DoMoveToGymCommand(model, trainer_id, gym_id);
                break;

            case 's':
                if (!(cin >> trainer_id))
                    throw Invalid_Input("Bad stop command");

                DoStopCommand(model, trainer_id);
                break;

            case 'p':
                if (!(cin >> trainer_id >> num_potions))
                    throw Invalid_Input("Bad buy potion command");

                DoRecoverInCenterCommand(model, trainer_id, num_potions);
                break;

            case 'b':
                if (!(cin >> trainer_id >> num_battles))
                    throw Invalid_Input("Bad battle command");

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

            case 'n':
                if (!(cin >> type >> new_id >> xnum >> ynum))
                    throw Invalid_Input("Bad new object command");
                model.NewCommand(type, new_id, xnum, ynum);
                break;
            }
        }
        catch (Invalid_Input &except)
        {
            cout << "Invalid input - " << except.msg_ptr << endl;
            // actions to be taken if the input is wrong
        }
    }
}