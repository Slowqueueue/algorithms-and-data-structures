#ifndef ADS_RGR_VERTEX_H
#define ADS_RGR_VERTEX_H
#include <iostream>
using namespace std;

//АТД «Дескриптор вершины графа»
template<class Name, class Data>
class Vertex {
    Name name;  //Имя вершины
    Data data;  //Данные, связанные с вершиной
public:
    bool isName, isData;
    int index;
    int color;
    int distance;
    Vertex() :
        isName(false),
        isData(false) {
        color = 0;
        distance = INT_MAX;
    }
    Vertex(Name name) :
        name(name),
        isName(true),
        isData(false) {
        color = 0;
        distance = INT_MAX;
    }
    void setName(Name name);
    void setData(Data data);
    Name getName();
    Data getData();
    bool hasName();
    bool hasData();
};
template<class Name, class Data>
void Vertex<Name, Data>::setName(Name name) {
    this->name = name;
    isName = true;
}
template<class Name, class Data>
void Vertex<Name, Data>::setData(Data data) {
    this->data = data;
    isData = true;
}
template<class Name, class Data>
Name Vertex<Name, Data>::getName() {
    return name;
}
template<class Name, class Data>
Data Vertex<Name, Data>::getData() {
    return data;
}
template<class Name, class Data>
bool Vertex<Name, Data>::hasName() {
    return isName;
}
template<class Name, class Data>
bool Vertex<Name, Data>::hasData() {
    return isData;
}
#endif //ADS_RGR_VERTEX_H