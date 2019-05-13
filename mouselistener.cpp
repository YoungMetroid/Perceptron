#include "mouselistener.h"

mouseListener::mouseListener():colorAzul(0),colorRojo(0)
{

}

//type_class is the color RED or BLUE
//The temps are the weight for each coordiante and the Bias
//which are generated randomly
void mouseListener::addObject(int &Xcoordinate, int &Ycoordinate, int type_class)
{
   if(!checkIfExist(Xcoordinate,Ycoordinate))
   {
       if(type_class == 1)
           colorRojo++;
       else
           colorAzul++;

       std::vector<int> temp;
       temp.push_back(Xcoordinate-250);
       temp.push_back((Ycoordinate-250)*-1);
       temp.push_back(type_class);
       objects.push_back(temp);
   }
}

std::vector<std::vector<int>>mouseListener::getObject()
{
    return objects;
}

void mouseListener::print()
{
    for(int x = 0; x < objects.size();x++)
    {
        for(int y = 0; y < 2;y++)
        {
            std::cout << std::setprecision(4);
            if(y ==1 )
            {
                std::cout << "Y:" << (objects[x][y]-250)*-1 << " ";
            }
            else std::cout << "X:" << objects[x][y]-250 << " ";
        }
        std::cout << std::endl;
    }
}
//Checks if the coordinate has already been taken
//ensuring that only one class can only be on one coordinate (x,y)
bool mouseListener::checkIfExist(int &Xcoordinate,int&Ycoordinate)
{
    for(int x = 0; x < objects.size();x++)
    {
       for(int y = 0; y < 2;y++)
       {
           if(objects[x][y] == Xcoordinate and objects[x][y]== Ycoordinate)
              return true;

       }
    }
    return false;
}
std::vector<int>mouseListener::getClassesSize()
{
    std::vector<int>temp;
    temp.push_back(colorAzul);
    temp.push_back(colorRojo);
    return temp;
}
