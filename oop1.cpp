#include <iostream>
#include <format>
#include <cmath>
#include <algorithm>
#include <array>
#include <oop1.hpp>

class FreeVector{

    // Point start;
    // Point end;
    // Point radius;


    std::array<double, 3> start = {0, 0, 0};
    std::array<double, 3> end = {0, 0, 0};
    std::array<double, 3> radius = {0, 0, 0};
    int dim = 3;


    void calcRadius(){
        for(int i=0; i<dim; i++){
        radius[i] = end[i] - start[i]; 
        }
    }

    public:

    FreeVector(){}

    //first three is start point, next is end point
    FreeVector(int xS, int yS, int zS,
               int xE, int yE, int zE){
        start[0] = xS;
        start[1] = yS;
        start[2] = zS;

        end[0] = xE;
        end[1] = yE;
        end[2] = zE;
        calcRadius();
    }

    // size start and end need >= 3
    FreeVector(int *Start, int *End){
        for(int i=0; i<dim; i++){
            start[i] = Start[i];
            end[i] = End[i];
        }
        calcRadius();
    }
    // FreeVector(const FreeVector&);

    // ~FreeVector(){}

    const double* getStart(){
        return start.begin();
    }

    const double* getEnd(){
        return end.begin();
    }
    
    const double* getRadius(){
        return radius.begin();
    }

    //first three is start point, next is end point
    void newCoors(int xS, int yS, int zS,
                  int xE, int yE, int zE){
        start[0] = xS;
        start[1] = yS;
        start[2] = zS;

        end[0] = xE;
        end[1] = yE;
        end[2] = zE;
        calcRadius();
    }

    void newStart(int xS, int yS, int zS)


    void print(){
        std::cout << "start:\t" << std::format(
            "x={}, y={}, z={}", start[0], start[1], start[2]
        ) << std::endl;
        std::cout << "end:\t" << std::format(
            "x={}, y={}, z={}", end[0], end[1], end[2]
        ) << std::endl;
        std::cout << "radius:\t" << std::format(
            "x={}, y={}, z={}", radius[0], radius[1], radius[2]
        ) << std::endl;
    }

    // size start need >= 3
    void newStart(const int* Start){
        for(int i=0; i<dim; i++)
            start[i] = Start[i];
        calcRadius();
    }

    // size end need >= 3
    void newEnd(const int* End){
        for(int i=0; i<dim; i++)
            end[i] = End[i];
        calcRadius();
    }

    // size start and end need >= 3
    void newCoors(const int* Start, const int* End){
        for(int i=0; i<dim; i++){
            start[i] = Start[i];
            end[i] = End[i];
        }
        calcRadius();
    }
    
    double lenght() const{
        int sum = 0;
        for(int i=0; i<dim; i++)
            sum += pow(radius[i], 2);
        return sqrt(sum);
    }

    FreeVector orthonormal(){
        FreeVector tmp;
        tmp.start = start;
        double len = lenght();
        for(int i=0; i<dim; i++)
            tmp.end[i] = start[i] + (radius[i] / len);
        calcRadius();
    }

    FreeVector operator+(const FreeVector &rhs) const{
        FreeVector tmp;
        
        for(int i=0; i<dim; i++){
            tmp.start[i] = start[i];
            tmp.end[i] = end[i] + rhs.radius[i];
        }

        tmp.calcRadius();
        return tmp;
    }

    FreeVector operator-(const FreeVector &rhs) const{
        FreeVector tmp;
        
        
        for(int i=0; i<dim; i++){
            tmp.start[i] = start[i];
            tmp.end[i] = end[i] - rhs.radius[i];
        }


        tmp.calcRadius();
        return tmp;
    }

    FreeVector operator*(const int num) const{
        FreeVector tmp;

        for(int i=0; i<dim; i++){
            tmp.start[i] = start[i];
            tmp.end[i] = start[i] + radius[i] * num;
        }
        tmp.calcRadius();
        return tmp;
    }

    bool operator==(const FreeVector &rhs) const{
        if(
            radius[0] == rhs.radius[0] and
            radius[1] == rhs.radius[1] and
            radius[2] == rhs.radius[2]
        ) return true;
        return false;
    }

    double scalar(const FreeVector &rhs) const{
        double sum=0;
        for(int i=0; i<dim; i++)
            sum += radius[i] * rhs.radius[i];
        return sum / (lenght() * rhs.lenght());
    }

    FreeVector vectorProduct(const FreeVector &rhs) const{
        FreeVector tmp;
        // dont work for another dim
        for(int i=0, l=1, r=dim-1; i<dim; i++, l++, r++, l%=dim, r%=dim){
            tmp.start[i] = start[i];
            tmp.end[i] = radius[l]*rhs.radius[r] - radius[r]*rhs.radius[l] + start[i];
        }
        tmp.calcRadius();
        return tmp;
    }

    double tripleProduct(const FreeVector &mhs, const FreeVector &rhs) const {
        return scalar(mhs.vectorProduct(rhs));
    }

    FreeVector doubleVectorProduct(const FreeVector &mhs, const FreeVector &rhs) const {
        return this->vectorProduct(mhs.vectorProduct(rhs));
    }

};

int main(){
    FreeVector vec{0, 1, 0, 1, 2, 3}, vec2{0, 2, 3, 0, -2, 6}, vec3;
    // vec.print();
    // vec2.print();
    // for(int i=0; i<3; i++)
    //     vec.getRadius()[i] = 0;
        
    //геттеры
    for(int i=0; i<3; i++)
        std::cout << vec.getStart()[i];
    std::cout << std::endl;
    for(int i=0; i<3; i++)
        std::cout << vec.getEnd()[i];
    std::cout << std::endl;
    for(int i=0; i<3; i++)
        std::cout << vec.getRadius()[i];
    std::cout << std::endl;

    std::cout << "lenght=" << vec.lenght() << std::endl;
    
    std::cout << "sum: " << std::endl;
    vec3 = vec + vec2;
    vec3.print();
    
    std::cout << "subtraction: " << std::endl;
    vec3 = vec - vec2;
    vec3.print();

    std::cout << "multipcation: " << std::endl;
    vec3 = vec*2;
    vec3.print();

    std::cout << "equal: " << std::endl;
    std::cout << std::boolalpha;
    std::cout << "vec==vec: " << (vec == vec) << std::endl;
    std::cout << "vec==vec2: " << (vec == vec2) << std::endl;

    std::cout << "scalar: " << std::endl;
    std::cout << vec.scalar(vec2) << std::endl;

    std::cout << "vector multiplication: " << std::endl;

    vec3 = vec.vectorProduct(vec2);
    vec3.print();

    std::cout << "tripleProduct: " << std::endl;
    std::cout << vec.tripleProduct(vec2, vec3) << std::endl;
    std::cout << vec.tripleProduct(vec3, vec2) << std::endl;

}