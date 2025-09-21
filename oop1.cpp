#include <iostream>
#include <format>
#include <cmath>
#include <algorithm>


class FreeVector{

    // Point start;
    // Point end;
    // Point radius;

    int start[3] = {0, 0, 0};
    int end[3] = {0, 0, 0};
    int radius[3] = {0, 0, 0};
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
    FreeVector(int Start[3], int End[3]){
        for(int i=0; i<dim; i++){
            start[i] = Start[i];
            end[i] = End[i];
        }
        calcRadius();
    }
    // FreeVector(const FreeVector&);

    // ~FreeVector(){}
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

    void newCoors(int Start[3], int End[3]){
        start[0] = Start[0];
        start[1] = Start[1];
        start[2] = Start[2];
        end[0] = End[0];
        end[1] = End[1];
        end[2] = End[2];
        calcRadius();
    }
    
    double lenght() const{
        int sum = 0;
        for(int i=0; i<dim; i++)
            sum += pow(radius[i], 2);
        return sqrt(sum);
    }

    FreeVector operator+(const FreeVector& rhs) const{
        FreeVector tmp;
        
        for(int i=0; i<dim; i++){
            tmp.start[i] = start[i];
            tmp.end[i] = end[i] + rhs.radius[i];
        }

        tmp.calcRadius();
        return tmp;
    }

    FreeVector operator-(const FreeVector& rhs) const{
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

    bool operator==(const FreeVector rhs) const{
        if(
            radius[0] == rhs.radius[0] and
            radius[1] == rhs.radius[1] and
            radius[2] == rhs.radius[2]
        ) return true;
        return false;
    }

    double scalar(const FreeVector rhs) const{
        double sum=0;
        for(int i=0; i<dim; i++)
            sum += radius[i] * rhs.radius[i];
        return sum / (lenght() * rhs.lenght());
    }

    FreeVector VectorMultiplication(const FreeVector rhs) const{
        FreeVector tmp;
        // need check for another dim
        for(int i=0, l=1, r=dim-1; i<dim; i++, l++, r++, l%=dim, r%=dim){
            tmp.start[i] = start[i];
            tmp.end[i] = radius[l]*rhs.radius[r] - radius[r]*rhs.radius[l] + start[i];
        }
        tmp.calcRadius();
        return tmp;
    }
};

int main(){
    FreeVector vec{0, 1, 0, 1, 2, 3}, vec2{0, 2, 3, 0, -2, 6};
    vec.print();
    vec2.print();
    std::cout << "lenght=" << vec.lenght() << std::endl;
    
    std::cout << "sum: " << std::endl;
    FreeVector vec3 = vec + vec2;
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

    vec3 = vec.VectorMultiplication(vec2);
    vec3.print();

    std::cout << "";
}