#include <iostream>
#include <string.h>
#include "Model.h"
#include "Point2D.h"
#include "Trainer.h"

using namespace std;


void DoMoveCommand(Model & model, int trainer_id, Point2D p1);
void DoMoveToCenterCommand(Model & model, int trainer_id, int center_id);
void DoMoveToGymCommand(Model & model, int trainer_id, int gym_id);
void DoStopCommand(Model & model, int trainer_id);
void DoBattleCommand(Model & model, int trainer_id, unsigned int battles);
void DoRecoverInCenterCommand(Model& model, int trainer_id, unsigned int
    potions_needed);
void DoAdvanceCommand(Model& model, View& view);
void DoRunCommand(Model& model, View& view);


