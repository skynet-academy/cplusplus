#include<cstdlib>
#include<iostream>
#include<string>
#include<vector>
#include<ctime>
#include<numeric>
#include<cmath>
struct Shape{
    double length, width;
    Shape(double l = 1, double w = 1){
        length = l;
        width = w;
    }
    double Area(){
        return length * width;
    }
private:
    int id;
};
struct Circle: Shape{
    Circle(double width){
            this-> width = width;
    }
    double Area(){
        return 3.14159 * std::pow(width/2,2);
    }
};

int main(){
    Shape shape(20,15);
    std::cout<<"Square area: "<<shape.Area()<<"\n";
    Circle circle(32);
    std::cout<<"Circle area: "<<circle.Area()<<"\n";
    Shape rectangle(23,45);
    std::cout<<"Rectangle area: "<<rectangle.Area()<<"\n";
    return 0;
}