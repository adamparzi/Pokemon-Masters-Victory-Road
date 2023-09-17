#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "Point2D.h"
#include <string>
#include <sstream>

using namespace std;

class GameObject
{
    protected:

    Point2D location;
    int id_num;
    char display_code;
    char state;

    public: 

    GameObject(char);
    GameObject(Point2D, int, char);
    virtual ~GameObject(); //no harm in making ALL destructors virtual

    Point2D GetLocation();
    int GetId();
    char GetState();
    
    virtual bool Update()=0; //makes gameobject abstract base class!
    virtual void ShowStatus();
    virtual bool ShouldBeVisible()=0;

    void DrawSelf(char * ptr); //FOR LATER (view)



};




#endif