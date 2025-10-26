#include <iostream>
#include <cmath>

//Declare the pi as 3.1416
const float pi = 3.1416;

//Function to find distance using the parameter x1, x2, y1, y2 based on the formula given
float Distance(float x1, float y1, float x2, float y2){
    float distance = sqrt((pow(x2-x1, 2))+(pow(y2-y1, 2)));
    return distance;
}

//Function to find the radius using the parameter x1, x2, y1, y2 based on the Distance function
float Radius(float x1, float y1, float x2, float y2){
    return Distance(x1, y1, x2, y2);
}


//Function to find the circumference using the parameter radius. It's formula is 2*pi*r
float Circumference(float radius){
    return 2 * pi * radius;
}

//Function to find the area of a circle based on the two points, the formula is pi*r*r
float Area(float radius){
    return pi * pow(radius, 2);
}


int main(){
    float x1, y1, x2, y2;

    //Input point 1
    std::cout << "Center coordinate x1: ";
    std::cin >> x1;
    std::cout << "Center coordinate y1: ";
    std::cin >> y1;

    //Input point 2
    std::cout << "Random point on coordinate x2: ";
    std::cin >> x2;
    std::cout << "Random point on coordinate y2: ";
    std::cin >> y2;

    //Store the radius in variable "radius"
    float radius = Radius(x1,y1,x2,y2);

    //Outputs the answers
    std::cout << "\nAnswers:\n\nRadius of circle: " << Radius(x1,y1,x2,y2) << "\n";
    std::cout << "Diameter of circle: " << 2 * Radius(x1,y1,x2,y2) << "\n";
    std::cout << "Circumference: " << Circumference(radius) << "\n";
    std::cout << "Area: " << Area(radius) << "\n";


    return 0;
}