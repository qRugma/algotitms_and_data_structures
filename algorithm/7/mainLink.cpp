#include "booleanvector.hpp"
#include "linkedlist.hpp"
#include <fstream>
#include <iostream>
#include <vector>

struct Leader;

struct Trailer {
    Leader* leaderPtr;
};

struct Leader {
    int VertexNumber;
    int inDegree;
    LinkedList<Trailer>* trailerList;
};

class VertexFinder {
  public:
    VertexFinder(const int vertexNumber) : vertexNumber_(vertexNumber) {}

    bool operator()(const Leader& leader) { return leader.VertexNumber == vertexNumber_; }

  private:
    int vertexNumber_;
};

bool isEdge(LinkedList<Leader>& list, Leader& lead, BooleanVector& ignoreEdges) {
    int inDegree = lead.inDegree;
    for (auto item : list) {
        if (!ignoreEdges[item.VertexNumber - 1])
            continue;
        for (auto tra : *item.trailerList)
            if (tra.leaderPtr->VertexNumber == lead.VertexNumber)
                inDegree--;
    }
    return inDegree == 0;
}

std::vector<int> TopSortLink(LinkedList<Leader> list) {
    int maxNum = 0;
    for (auto lead : list) 
        maxNum = std::max(maxNum, lead.VertexNumber);

    BooleanVector ignoreEdges(maxNum, 0);
    std::vector<int> result;
    while (ignoreEdges.getWeight() != ignoreEdges.getLenght())
        for (auto lead : list)
            if (!ignoreEdges[lead.VertexNumber - 1] and isEdge(list, lead, ignoreEdges)) {
                result.push_back(lead.VertexNumber);
                ignoreEdges.set_value(1, lead.VertexNumber - 1);
            }
    return result;
}

int main() {
    LinkedList<Leader> graph;
    int inVertex, outVertex;
    std::ifstream graphFile("graph.txt");

    while (true) {
        graphFile >> inVertex >> outVertex;
        if (inVertex == 0 and outVertex == 0)
            break;

        auto firstVertexIt = graph.find_if(VertexFinder(inVertex));

        if (firstVertexIt == graph.end())
            graph.push_front(Leader{inVertex, 0, new LinkedList<Trailer>()});

        Leader* pA = &(*graph.find_if(VertexFinder(inVertex)));

        auto secondVertexIt = graph.find_if(VertexFinder(outVertex));

        if (secondVertexIt == graph.end())
            graph.push_front(Leader{outVertex, 0, new LinkedList<Trailer>()});

        Leader* pB = &(*graph.find_if(VertexFinder(outVertex)));

        ++pB->inDegree;

        pA->trailerList->push_front(Trailer{pB});
    }

    auto answer = TopSortLink(graph);
    for (auto i : answer) 
        std::cout << i << " ";
}