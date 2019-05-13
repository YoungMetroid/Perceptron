#ifndef PERCEPTRON_H
#define PERCEPTRON_H

#include <iostream>
#include <string.h>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <iomanip>

class perceptron
{

private:
    const int MaxIterations = 100000;
    const double Learning_Rate = 0.00001;
    enum {xCoordinate, yCoordinate,type_class};
    double bias = 1.00;
    float thetha;
    int iterations;
    std::vector<int> outputs;
    std::vector<double> weights;
    std::vector<std::vector<int>> points;
    int sumatoria_Activation(std::vector<int>&);
    bool train(std::vector<int>&);
    bool training;

    public:
    perceptron(int&);
    void setPoints(std::vector<std::vector<int>>);
    std::vector<double> calculate();
    std::vector<std::vector<int>> getLine();
    int getIterations();
    int getMaxIterations();
    bool getTraining();



};

#endif // PERCEPTRON_H
