#include "View.h"

using namespace std;

View::View(){
    size=11;
    scale=2;
    //origin is already (0,0) initially
}

void View::Draw()           //GIVEN
{
    for (int j = size-1; j >= -1; j--)
    {
        for (int i = -1; i <= size-1; i++)
        {
            //grid axis
            if (i == -1 && j%2 == 0)
            {
                cout << j*2;
                if (j/5 == 0)
                {
                    cout << " ";
                }
            }
            else if (i == -1 && j%2 != 0)
            {
                cout << "  ";
            }
            else if (j == -1 && i%2 == 0)
            {
                cout << i*2;
                if (i/5 == 0)
                {
                    cout << " ";
                }
                cout << "  ";
            }
            //draw objects
            if (i >= 0 && j >=0)
            {
                cout << grid[i][j][0] << grid[i][j][1];
            }
        }
        cout << endl;
    }
}

void View::Clear(){
    for (int j = size-1; j >= -1; j--)
    {
        for (int i = -1; i <= size-1; i++)
        {
            if (i >= 0 && j >=0)
            {
                grid[i][j][0] = '.';
                grid[i][j][1] = ' ';
            }
            
        }
    }
}


bool View::GetSubscripts(int &out_x, int &out_y, Point2D location){
    out_x = (location.x-origin.x)/scale;
    out_y = (location.y-origin.y)/scale;

    if (out_x<view_maxsize && out_y<view_maxsize){
        return true;
    } else {
        cout<<"An object is outside the display!"<<endl;
        return false;
    }

}

void View::Plot(GameObject * ptr) {
    int out_x = ptr->GetLocation().x;
    int out_y = ptr->GetLocation().y;

    if (View::GetSubscripts(out_x, out_y, ptr->GetLocation()) && ptr->ShouldBeVisible()) {

        if (grid[out_x][out_y][0] == '.'){
            ptr->DrawSelf(grid[out_x][out_y]); // makes [0], [1] object's id
        } else {
            grid[out_x][out_y][0] = '*';
            grid[out_x][out_y][1] = ' ';
       }
    }
}





