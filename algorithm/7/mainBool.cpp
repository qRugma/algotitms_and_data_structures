#include "booleanmatrix.hpp"
#include "booleanvector.hpp"
#include <iostream>
#include <vector>
#include <fstream>


bool isEdge(const BooleanMatrix& mat, size_t column, BooleanVector& ignoreEdges){
    for(size_t i=0; i<mat.rows(); i++)
        if (!ignoreEdges[i] and mat[column][i])
            return false;
    return true;
}


std::vector<int> TopSortBool(const BooleanMatrix& mat){
    std::vector<int> result;
    BooleanVector ignoreEdges(mat.columns(), 0);

    while(ignoreEdges.getWeight() != ignoreEdges.getLenght()){
        for(size_t i=0; i<mat.columns(); i++)
            if(!ignoreEdges[i] and isEdge(mat, i, ignoreEdges)){
                result.push_back(i+1);
                ignoreEdges.set_value(1, i);
            }
    }
    return result;
}



struct inElem{
    int a, b;
};


int main() {
    std::vector<inElem> In;
    int inVertex, outVertex, maxNum=0;

    std::ifstream graphFile("graph.txt");

    while (true){
        graphFile >> inVertex >> outVertex;
        if (inVertex == 0 and outVertex == 0)
            break;
        In.push_back(inElem{inVertex, outVertex});
        maxNum = std::max(maxNum, std::max(inVertex, outVertex));
    }

    BooleanMatrix mas(maxNum, maxNum);
    for(auto i : In)
        mas.set(i.b-1, i.a-1, 1);
    // std::cout << mas << std::endl;
    auto answer = TopSortBool(mas);
    for(auto i : answer)
        std::cout << i << " ";
}