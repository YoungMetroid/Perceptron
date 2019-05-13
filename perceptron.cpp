#include "perceptron.h"

perceptron::perceptron(int &amount_of_weights):iterations(0),training(true)
{
     srand(time(NULL));
    for(int i = 0; i < amount_of_weights; i++)
    {
        float new_Weight = (rand()%201)-100;
        new_Weight /= 100;
        this->weights.push_back(new_Weight);
        std::cout << i << std::endl;
    }
    this->weights.push_back(1.0);

    thetha = 0;

    std::cout <<"Weight 1: " << weights[0] << std::endl;
    std::cout <<"Weight 2: " << weights[1] << std::endl;
    std::cout << "Bias: " << bias << std::endl;

}
//p = parameter
void perceptron::setPoints(std::vector<std::vector<int>> pPoints)
{
    points = pPoints;
    std::cout << points.size() << std::endl;
    for(int i = 0; i < points.size(); i++)
    {
       points[i][type_class] == 1 ? outputs.push_back(1) :  outputs.push_back(0);
       std::cout << "X:" << points[i][xCoordinate]-250 << " Y: " << (points[i][yCoordinate]-250)*-1 << std::endl;
    }
    std::cout << "End" << std::endl;
}
std::vector<double> perceptron::calculate()
{

    if(training)
    {
        iterations++;
      //  std::cout << "Epoch: " << iterations << std::endl;
        training = false;
        for(int currentPoint = 0; currentPoint < points.size(); currentPoint++)
        {
            std::vector<int>temp;
            temp.push_back(points[currentPoint][0]);
            temp.push_back((points[currentPoint][1]));
            temp.push_back(points[currentPoint][2]);

            if(train(temp))
            {
                training = true;
            }
        }

    }
    else
    {
        iterations = MaxIterations;
        iterations++;
    }
    /*
    std::cout << "Iterations" << iterations << std::endl;
    std::cout <<"Weight 0: " << weights[0] << std::endl;
    std::cout <<"Weight 1: " << weights[1] << std::endl;
    std::cout << "Bias: " << weights[2] << std::endl;
    */
    return weights;
}

bool perceptron::train(std::vector<int> &currentPoint)
{
    int activation = sumatoria_Activation(currentPoint);

    bool mustTrain = (activation - currentPoint[2]) != 0;
    if(mustTrain)
    {
        weights[2] += Learning_Rate * (activation -currentPoint[2]);
        weights[0] += Learning_Rate * ( activation - currentPoint[2]) * currentPoint[0];
        weights[1] += Learning_Rate * (activation- currentPoint[2]) * currentPoint[1];
       // std::cout << "Weight_0: " << weights[0] << std::endl;
       // std::cout << "Weight_1: " << weights[1] << std::endl;

    }
    return mustTrain;
}
///Sums all the weights and returns a activation function
int perceptron::sumatoria_Activation(std::vector<int>&coordinates)
{
    double sum = weights[2];
    for(int i = 0; i < weights.size()-1 ;i++)
    {
           sum += weights[i] * coordinates[i];
    }
  //  std::cout << "Sum: " << sum << std::endl;
    return (sum >thetha) ? 0:1;
}

int perceptron::getIterations()
{
    return iterations;
}
int perceptron::getMaxIterations()
{
    return MaxIterations;
}
bool perceptron::getTraining()
{
    return training;
}

