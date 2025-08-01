#ifndef ADS_RGR_VERTEX_MAP_H
#define ADS_RGR_VERTEX_MAP_H
#include <map>
using namespace std;

template<class Name, class Data>
class MapVertex {
    map<Name, Data> mapVertex;
public:
    bool replaceName(Name name1, Name name2);
    bool addPair(Name name, Data data);
    Data getData(Name name);
    bool delPair(Name name);
};
template<class Name, class Data>
bool MapVertex<Name, Data>::replaceName(Name name1, Name name2) {
    if (mapVertex.find(name2) == mapVertex.end()) {
        Data data = mapVertex[name1];
        mapVertex.erase(name1);
        data->setName(name2);
        mapVertex[name2] = data;
        return true;
    }
    return false;
}
template<class Name, class Data>
bool MapVertex<Name, Data>::addPair(Name name, Data data) {
    if (mapVertex.find(name) == mapVertex.end()) {
        data->setName(name);
        mapVertex[name] = data;
        return true;
    }
    return false;
}
template<class Name, class Data>
Data MapVertex<Name, Data>::getData(Name name) {
    if (mapVertex.find(name) != mapVertex.end())
        return mapVertex[name];
    else
        throw runtime_error("Исключение");
}
template<class Name, class Data>
bool MapVertex<Name, Data>::delPair(Name name) {
    return mapVertex.erase(name) == 1;
}
#endif //ADS_RGR_VERTEX_MAP_H