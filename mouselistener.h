#ifndef MOUSELISTENER_H
#define MOUSELISTENER_H
#include <iostream>
#include <vector>

#include <iomanip>

class mouseListener
{
private:
    int colorRojo;
    int colorAzul;
    std::vector<std::vector<int>> objects;

public:   
    mouseListener();
    void addObject(int&,int&,int);
    void print();
    bool checkIfExist(int&,int&);
    std::vector<int> getClassesSize();
    std::vector<std::vector<int>> getObject();


};

#endif // MOUSELISTENER_H
