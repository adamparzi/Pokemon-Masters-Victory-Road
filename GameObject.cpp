#include <iostream>
#include "GameObject.h"

using namespace std;

    GameObject::GameObject(char in_code){
        display_code = in_code;
        id_num = 1;
        state = 0;    
        cout << "GameObject constructed" << endl; // not "default" as of RV2

    }
    GameObject::GameObject(Point2D in_loc, int in_id, char in_code){
        display_code = in_code;
        id_num = in_id;
        location = in_loc;
        state = 0;
        cout << "GameObject constructed" << endl;
    }

    GameObject::~GameObject(){
        cout<<"GameObject destructed"<<endl;
    }

    Point2D GameObject::GetLocation(){ //remember that MEMBER FUNCTIONS must have class specified in .cpp using :: 
        return location;
    }
    int GameObject::GetId(){
        return id_num;
    }
    char GameObject::GetState(){
        return state;
    }
    void GameObject::ShowStatus(){
        cout << display_code << id_num << " at " << location << endl; 
    }

    void GameObject::DrawSelf(char * ptr){
        *ptr = display_code;  
        *(ptr+1) = id_num + '0';

    } //FOR LATER (view)
