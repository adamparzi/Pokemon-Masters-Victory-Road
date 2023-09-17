#include "GameCommand.h"

using namespace std;    

void DoMoveCommand(Model & model, int trainer_id, Point2D p1){
    if (model.GetTrainerPtr(trainer_id)!=0){
        cout<<"Moving "<<model.GetTrainerPtr(trainer_id)->GetName()<<" to "<<p1<<endl;

        model.GetTrainerPtr(trainer_id)->StartMoving(p1);
    } else{
        cout<<"Error: Please enter a valid command!"<<endl;
    }
}

void DoMoveToCenterCommand(Model & model, int trainer_id, int center_id){
    if (model.GetTrainerPtr(trainer_id)!=0 && model.GetPokemonCenterPtr(center_id)!=0){
        cout<<"Moving "<<model.GetTrainerPtr(trainer_id)->GetName()<<" to "<<
            model.GetPokemonCenterPtr(center_id)->GetLocation()<<endl;

        model.GetTrainerPtr(trainer_id)->StartMovingToCenter(model.GetPokemonCenterPtr(center_id));
    } else{
        cout<<"Error: Please enter a valid command!"<<endl;
    }
    
}

void DoMoveToGymCommand(Model & model, int trainer_id, int gym_id){
    if (model.GetTrainerPtr(trainer_id)!=0 && model.GetPokemonGymPtr(gym_id)!=0){
        cout<<"Moving "<<model.GetTrainerPtr(trainer_id)->GetName()<<" to "<<
            model.GetPokemonGymPtr(gym_id)->GetLocation()<<endl;

        model.GetTrainerPtr(trainer_id)->StartMovingToGym(model.GetPokemonGymPtr(gym_id));
    } else{
        cout<<"Error: Please enter a valid command!"<<endl;
    }
}

void DoStopCommand(Model & model, int trainer_id){
    if (model.GetTrainerPtr(trainer_id)!=0){
        cout<<"Stopping "<<model.GetTrainerPtr(trainer_id)->GetName()<<endl;

        model.GetTrainerPtr(trainer_id)->Stop();    //recheck stop() function, make sure Update() doesn't move it or anything
    } else {
        cout<<"Error: Please enter a valid command!"<<endl;
    }
}

void DoBattleCommand(Model & model, int trainer_id, unsigned int battles){
    if (model.GetTrainerPtr(trainer_id)!=0 && battles>0){
        cout<<model.GetTrainerPtr(trainer_id)->GetName()<<" is battling"<<endl;             // HAVE TO MAKE SURE HE'S NOT FAINTED BEFORE THIS COUTS; SAME FOR OTHER FUNCTION CALLS HERE

        model.GetTrainerPtr(trainer_id)->StartBattling(battles);
    } else{
        cout<<"Error: Please enter a valid command!"<<endl;
    }
}

void DoRecoverInCenterCommand(Model& model, int trainer_id, unsigned int
    potions_needed){
    if (model.GetTrainerPtr(trainer_id)!=0 && potions_needed>0){
        cout<<"Recovering "<<model.GetTrainerPtr(trainer_id)->GetName()<<
            "'s Pokemon's health"<<endl;

        model.GetTrainerPtr(trainer_id)->StartRecoveringHealth(potions_needed);
    } else {
        cout<<"Error: Please enter a valid command!"<<endl;
    }
}

void DoAdvanceCommand(Model& model, View& view){
    cout<<"Advancing one tick."<<endl;
    
    model.Update();
    
    view.Clear();
    model.Display(view);
    view.Draw();
    

}

void DoRunCommand(Model& model, View& view){
    cout<<"Advancing to next event."<<endl;

    for (int i=0;i<5;i++){  //runs for max 5 time steps
        if (model.Update()){
            break;
        }
    }
    view.Clear();
    model.Display(view);

    view.Draw();

}
