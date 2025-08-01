#ifndef ADS_RGR_EDGE_H
#define ADS_RGR_EDGE_H
#include <iostream>
using namespace std;

//АТД «Дескриптор ребра графа»
template<class Vertex, class Weight, class Data>
class Edge {
    Vertex* v1, * v2;   //Вершины, которые соединяет ребро
    Weight weight;     //Вес
    Data data;         //Данные ребра
    bool isWeight, isData;
public:
    Edge(Vertex* v1, Vertex* v2) :
        v1(v1),
        v2(v2),
        isWeight(false),
        weight(0),
        isData(false) {}
    Edge(Vertex* v1, Vertex* v2, Weight weight) :
        v1(v1),
        v2(v2),
        weight(weight),
        isWeight(true),
        isData(false) {}
    void setWeight(Weight weight);
    void setData(Data data);
    Weight getWeight();
    Data getData();
    Vertex* getVertex1();
    Vertex* getVertex2();
    bool hasWeight();
    bool hasData();
};
template<class Vertex, class Weight, class Data>
void Edge<Vertex, Weight, Data>::setWeight(Weight weight) {
    this->weight = weight;
    isWeight = true;
}
template<class Vertex, class Weight, class Data>
void Edge<Vertex, Weight, Data>::setData(Data data) {
    this->data = data;
    isData = true;
}
template<class Vertex, class Weight, class Data>
Weight Edge<Vertex, Weight, Data>::getWeight() {
    return weight;
}
template<class Vertex, class Weight, class Data>
Data Edge<Vertex, Weight, Data>::getData() {
    return data;
}
template<class Vertex, class Weight, class Data>
Vertex* Edge<Vertex, Weight, Data>::getVertex1() {
    return v1;
}
template<class Vertex, class Weight, class Data>
Vertex* Edge<Vertex, Weight, Data>::getVertex2() {
    return v2;
}
template<class Vertex, class Weight, class Data>
bool Edge<Vertex, Weight, Data>::hasWeight() {
    return isWeight;
}
template<class Vertex, class Weight, class Data>
bool Edge<Vertex, Weight, Data>::hasData() {
    return isData;
}
#endif //ADS_RGR_EDGE_H