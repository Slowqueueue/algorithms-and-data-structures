#ifndef ADS_RGR_GRAPH_H
#define ADS_RGR_GRAPH_H
#include <iostream>
#include "Graph_forms.h"
#include <iomanip>
using namespace std;

//АТД простой граф
template<class Vertex, class Edge>
class Graph {
    vector<Vertex*> vertexVector; //Вектор вершин
    GraphForm<Edge>* data;        //Данные формы графа
    bool directed;                //Тип графа
    bool dense;                   //Форма графа
    int edgeCounter;              //Число рёбер
    //обновление индексов вершин
    void refreshIndex(int startIndex);
    //Получение индекса вершины по дескриптору
    int getIndex(Vertex* v);
public:
    //Создает пустой L-граф с нулевым числом вершин и рёбер
    Graph();
    //Создает граф с V вершинами, без ребер, типа D, формы представления F
    Graph(int vertexCount, bool directed, bool dense);
    //Создать граф с V вершинами, с E случайными ребрами, типа D , формы F
    Graph(int vertexCount, int edgeCount, bool directed, bool dense);
    //конструктор копирования
    Graph(const Graph<Vertex, Edge>& G);
    //деструктор
    ~Graph();
    //Информация о графе
    //Число вершин, рёбер, насыщенность
    int getVertexCount();
    int getEdgeCount();
    double getRatio();
    //Тип графа
    bool isDirected();
    bool isDense();
    //Преобразования
    void toDenseGraph();
    void toSparseGraph();
    //Данные
    //Вершины
    Vertex* insertVertex();
    Vertex* insertVertex(int index);
    Vertex* insertVertexname(string name);
    bool deleteVertex(Vertex* v);
    bool deleteVertex(int index);
    Vertex* getVertex(int index);
    //Рёбра
    Edge* insertEdge(Vertex* v1, Vertex* v2);
    Edge* insertEdge(int index1, int index2);
    Edge* insertEdgeWeight(Vertex* v1, Vertex* v2, int weight);
    Edge* insertEdgeWeight(int index1, int index2, int weight);
    bool deleteEdge(Vertex* v1, Vertex* v2);
    bool deleteEdge(int index1, int index2);
    bool hasEdge(Vertex* v1, Vertex* v2);
    bool hasEdge(int v1, int v2);
    Edge* getEdge(Vertex* v1, Vertex* v2);
    Edge* getEdge(int v1, int v2);
    void printGraph(bool isMatrix = true);
    //Итератор вершин
    class VertexIterator {
        Graph<Vertex, Edge>* graph;
        bool end;
        int current;
    public:
        explicit VertexIterator(Graph<Vertex, Edge>& g);
        //Возвращает итератор, установленный на первую вершину графа
        bool toBegin();
        //Переход к следующей позиции
        bool operator++();
        bool operator++(int);
        //Установить итератор вершин на конечную вершину
        bool toEnd();
        //Проверка на выход
        bool onEnd();
        //Получение вершины
        Vertex* operator*();
    };
    //Итератор рёбер
    class EdgeIterator {
        Graph<Vertex, Edge>* graph; //Обрабатываемый граф
        typename GraphMatrixForm<Edge>::EdgeIterator* matrixIter;
        typename GraphListForm<Edge>::EdgeIterator* listIter;
        bool isMatrix;
    public:
        bool end;
        explicit EdgeIterator(Graph<Vertex, Edge>& g);
        //Установка в начало
        bool toBegin();
        //Установить итератор рёбер на конечное ребро
        bool toEnd();
        //Сдвиг на следующий элемент
        bool operator++();
        bool operator++(int);
        //Проверка на выход
        bool onEnd();
        //Получение ребра
        Edge* operator*();
    };
    //Итератор исходящих рёбер
    class OutputEdgeIterator {
        Graph<Vertex, Edge>* graph; //Обрабатываемый граф
        typename GraphMatrixForm<Edge>::OutputEdgeIterator* matrixIter;
        typename GraphListForm<Edge>::OutputEdgeIterator* listIter;
        bool isMatrix;
    public:
        int currentV1;
        bool end;
        explicit OutputEdgeIterator(Graph<Vertex, Edge>& g, Vertex& v);
        //Установка в начало
        bool toBegin();
        //Установить итератор рёбер на конечное ребро
        bool toEnd();
        //Сдвиг на следующий элемент
        bool operator++();
        bool operator++(int);
        //Проверка на выход
        bool onEnd();
        //Получение ребра
        Edge* operator*();
    };
};
template<class Vertex, class Edge>
Graph<Vertex, Edge>::OutputEdgeIterator::OutputEdgeIterator(Graph<Vertex, Edge>& g, Vertex& v) {
    graph = &g;
    currentV1 = graph->getIndex(&v);
    if (graph->isDense()) {
        matrixIter = new typename GraphMatrixForm<Edge>::OutputEdgeIterator(
            static_cast<GraphMatrixForm<Edge> *>(g.data),
            currentV1);
        isMatrix = true;
    }
    else {
        listIter = new typename GraphListForm<Edge>::OutputEdgeIterator(
            static_cast<GraphListForm<Edge> *>(g.data),
            currentV1);
        isMatrix = false;
    }
}
template<class Vertex, class Edge>
bool Graph<Vertex, Edge>::OutputEdgeIterator::toBegin() {
    if (isMatrix)
        return matrixIter->toBegin();
    else
        return listIter->toBegin();
}
template<class Vertex, class Edge>
bool Graph<Vertex, Edge>::OutputEdgeIterator::operator++() {
    if (isMatrix)
        return matrixIter->next();
    else
        return listIter->next();
}
template<class Vertex, class Edge>
bool Graph<Vertex, Edge>::OutputEdgeIterator::operator++(int) {
    if (isMatrix)
        return matrixIter->next();
    else
        return listIter->next();
}
template<class Vertex, class Edge>
bool Graph<Vertex, Edge>::OutputEdgeIterator::toEnd() {
    if (isMatrix)
        return matrixIter->toEnd();
    else
        return listIter->toEnd();
}
template<class Vertex, class Edge>
bool Graph<Vertex, Edge>::OutputEdgeIterator::onEnd() {
    if (isMatrix)
        return matrixIter->onEnd();
    else
        return listIter->onEnd();
}
template<class Vertex, class Edge>
Edge* Graph<Vertex, Edge>::OutputEdgeIterator::operator*() {
    if (onEnd())
        throw runtime_error("Исключение");
    if (isMatrix)
        return matrixIter->getEdge();
    else
        return listIter->getEdge();
}
template<class Vertex, class Edge>
Graph<Vertex, Edge>::EdgeIterator::EdgeIterator(Graph<Vertex, Edge>& g) {
    graph = &g;
    if (graph->isDense()) {
        matrixIter = new typename GraphMatrixForm<Edge>::EdgeIterator(
            static_cast<GraphMatrixForm<Edge> *>(g.data));
        isMatrix = true;
    }
    else {
        listIter = new typename GraphListForm<Edge>::EdgeIterator(static_cast<GraphListForm<Edge> *>(g.data));
        isMatrix = false;
    }
    toBegin();
}
template<class Vertex, class Edge>
bool Graph<Vertex, Edge>::EdgeIterator::toBegin() {
    if (isMatrix)
        return matrixIter->toBegin();
    else
        return listIter->toBegin();
}
template<class Vertex, class Edge>
bool Graph<Vertex, Edge>::EdgeIterator::operator++() {
    if (isMatrix)
        return matrixIter->next();
    else
        return listIter->next();
}
template<class Vertex, class Edge>
bool Graph<Vertex, Edge>::EdgeIterator::operator++(int) {
    if (isMatrix)
        return matrixIter->next();
    else
        return listIter->next();
}
template<class Vertex, class Edge>
bool Graph<Vertex, Edge>::EdgeIterator::onEnd() {
    if (isMatrix)
        return matrixIter->onEnd();
    else
        return listIter->onEnd();
}
template<class Vertex, class Edge>
bool Graph<Vertex, Edge>::EdgeIterator::toEnd() {
    if (isMatrix)
        return matrixIter->toEnd();
    else
        return listIter->toEnd();
}
template<class Vertex, class Edge>
Edge* Graph<Vertex, Edge>::EdgeIterator::operator*() {
    if (onEnd())
        throw runtime_error("Исключение");
    if (isMatrix)
        return matrixIter->getEdge();
    else
        return listIter->getEdge();
}
template<class Vertex, class Edge>
Graph<Vertex, Edge>::VertexIterator::VertexIterator(Graph<Vertex, Edge>& g) {
    graph = &g;
    toBegin();
}
template<class Vertex, class Edge>
bool Graph<Vertex, Edge>::VertexIterator::toBegin() {
    if (graph->vertexVector.size() == 0) {
        end = true;
        return false;
    }
    current = 0;
    end = false;
    return true;
}
template<class Vertex, class Edge>
bool Graph<Vertex, Edge>::VertexIterator::operator++() {
    if (end)
        return false;
    ++current;
    if (graph->vertexVector.size() == current) {
        end = true;
        return false;
    }
    return true;
}
template<class Vertex, class Edge>
bool Graph<Vertex, Edge>::VertexIterator::operator++(int) {
    if (end)
        return false;
    ++current;
    if (graph->vertexVector.size() == current) {
        end = true;
        return false;
    }
    return true;
}
template<class Vertex, class Edge>
bool Graph<Vertex, Edge>::VertexIterator::toEnd() {
    if (graph->vertexVector.size() == 0) {
        end = true;
        return false;
    }
    current = graph->vertexVector.size() - 1;
    end = true;
    return true;
}
template<class Vertex, class Edge>
bool Graph<Vertex, Edge>::VertexIterator::onEnd() {
    return end;
}
template<class Vertex, class Edge>
Vertex* Graph<Vertex, Edge>::VertexIterator::operator*() {
    if (current >= graph->vertexVector.size() || current == -1)
        throw runtime_error("Исключение");
    return graph->vertexVector[current];
}
template<class Vertex, class Edge>
void Graph<Vertex, Edge>::refreshIndex(int startIndex) {
    if (startIndex < 0 || startIndex >= vertexVector.size())
        return;

    for (int i = startIndex; i < vertexVector.size(); i++)
        vertexVector[i]->index = i;
}
template<class Vertex, class Edge>
int Graph<Vertex, Edge>::getIndex(Vertex* v) {
    int i;
    for (i = 0; i < vertexVector.size(); ++i) {
        if (vertexVector[i] == v)
            break;
    }
    if (i == vertexVector.size())
        throw runtime_error("Исключение");
    return i;
}
template<class Vertex, class Edge>
Graph<Vertex, Edge>::Graph() {
    data = new GraphListForm<Edge>(false);
    directed = false;
    dense = false;
    edgeCounter = 0;
}
template<class Vertex, class Edge>
Graph<Vertex, Edge>::Graph(int vertexCount, bool directed, bool dense) {
    if (dense)
        data = new GraphMatrixForm<Edge>(directed);
    else
        data = new GraphListForm<Edge>(directed);
    for (int i = 0; i < vertexCount; ++i) {
        auto* v = new Vertex();
        vertexVector.push_back(v);
        data->insertVertex(i);
    }
    this->directed = directed;
    this->dense = dense;
    edgeCounter = 0;
    refreshIndex(0);
}
template<class Vertex, class Edge>
Graph<Vertex, Edge>::Graph(int vertexCount, int edgeCount, bool directed, bool dense) {
    if (dense)
        data = new GraphMatrixForm<Edge>(directed);
    else
        data = new GraphListForm<Edge>(directed);

    for (int i = 0; i < vertexCount; ++i) {
        auto* v = new Vertex();
        vertexVector.push_back(v);
        data->insertVertex(i);
    }
    this->directed = directed;
    this->dense = dense;
    edgeCounter = 0;
    //Вставляем рёбра
    if (edgeCount <= 0) return;
    //Корректируем число рёбер, чтобы не превышало максимумы
    if (directed) {
        if (edgeCount > vertexCount * (vertexCount - 1))
            edgeCount = vertexCount * (vertexCount - 1);

    }
    else {
        if (edgeCount > (vertexCount * (vertexCount - 1)) / 2)
            edgeCount = (vertexCount * (vertexCount - 1)) / 2;
    }
    //Вставляем
    int v1, v2;
    refreshIndex(0);
    srand(time(0));
    while (edgeCounter < edgeCount) {
        v1 = rand() % vertexCount;
        v2 = rand() % vertexCount;
        if (v1 == v2)
            continue;
        if (data->hasEdge(v1, v2))
            continue;
        Edge* t = new Edge(vertexVector[v1], vertexVector[v2]);
        data->insertEdge(v1, v2, t);
        if (!directed)
            data->insertEdge(v2, v1, t);
        ++edgeCounter;
    }
}
template<class Vertex, class Edge>
Graph<Vertex, Edge>::Graph(const Graph<Vertex, Edge>& G) {
    delete data;
    if (G.Dense())
        data = new GraphMatrixForm<Edge>(*(G.data));
    else
        data = new GraphListForm<Edge>(*(G.data));
    directed = G.directed;
    dense = G.dense;
}
template<class Vertex, class Edge>
Graph<Vertex, Edge>::~Graph() {
    while (vertexVector.size() != 0)
        deleteVertex(vertexVector.size() - 1);
    delete data;
}
template<class Vertex, class Edge>
int Graph<Vertex, Edge>::getVertexCount() {
    return vertexVector.size();
}
template<class Vertex, class Edge>
int Graph<Vertex, Edge>::getEdgeCount() {
    return edgeCounter;
}
template<class Vertex, class Edge>
double Graph<Vertex, Edge>::getRatio() {
    int max = vertexVector.size() * (vertexVector.size() - 1);
    if (!directed)
        max /= 2;
    return (double)edgeCounter / (double)max;
}
template<class Vertex, class Edge>
bool Graph<Vertex, Edge>::isDirected() {
    return directed;
}
template<class Vertex, class Edge>
bool Graph<Vertex, Edge>::isDense() {
    return dense;
}
template<class Vertex, class Edge>
void Graph<Vertex, Edge>::toDenseGraph() {
    //Создаём структуру хранения М-графа
    GraphForm<Edge>* newData = new GraphMatrixForm<Edge>(directed);

    //Создаём вершины
    for (int i = 0; i < vertexVector.size(); ++i)
        newData->insertVertex(i);
    //Переносим рёбра
    for (int i = 0; i < vertexVector.size(); ++i)
        for (int j = 0; j < vertexVector.size(); ++j)
            if (data->hasEdge(i, j))
                newData->insertEdge(i, j, data->getEdge(i, j));
    delete data;
    data = newData;
    dense = true;
}
template<class Vertex, class Edge>
void Graph<Vertex, Edge>::toSparseGraph() {
    //Создаём структуру хранения L-графа
    GraphForm<Edge>* newData = new GraphListForm<Edge>(directed);

    //Создаём вершины
    for (int i = 0; i < vertexVector.size(); ++i)
        newData->insertVertex(i);

    //Переносим рёбра
    for (int i = 0; i < vertexVector.size(); ++i)
        for (int j = 0; j < vertexVector.size(); ++j)
            if (data->hasEdge(i, j))
                newData->insertEdge(i, j, data->getEdge(i, j));
    delete data;
    data = newData;
    dense = false;
}
template<class Vertex, class Edge>
Vertex* Graph<Vertex, Edge>::insertVertex() {
    auto* v = new Vertex;
    if (!data->insertVertex(vertexVector.size()))
        throw runtime_error("Исключение");
    vertexVector.push_back(v);
    refreshIndex(vertexVector.size() - 1);
    return v;
}
template<class Vertex, class Edge>
Vertex* Graph<Vertex, Edge>::insertVertex(int index) {
    auto* v = new Vertex;
    if (data->insertVertex(index) == false)
        throw runtime_error("Исключение");
    vertexVector.insert(vertexVector.begin() + index, v);
    refreshIndex(index);
    return v;
}
template<class Vertex, class Edge>
Vertex* Graph<Vertex, Edge>::insertVertexname(string name) {
    auto* v = new Vertex;
    if (!data->insertVertex(vertexVector.size()))
        throw runtime_error("Исключение");
    vertexVector.push_back(v);
    refreshIndex(vertexVector.size() - 1);
    v->setName(name);
    return v;
}
template<class Vertex, class Edge>
bool Graph<Vertex, Edge>::deleteVertex(Vertex* v) {
    int index = getIndex(v);
    edgeCounter -= data->deleteEdgesFromVertex(index);
    if (data->deleteVertex(index)) {
        vertexVector.erase(vertexVector.begin() + index);
        refreshIndex(index);
        return true;
    }
    return false;
}
template<class Vertex, class Edge>
bool Graph<Vertex, Edge>::deleteVertex(int index) {
    if (index < 0 || index >= vertexVector.size())
        return false;
    edgeCounter -= data->deleteEdgesFromVertex(index);
    if (data->deleteVertex(index)) {
        vertexVector.erase(vertexVector.begin() + index);
        refreshIndex(index);
        return true;
    }
    return false;
}
template<class Vertex, class Edge>
Vertex* Graph<Vertex, Edge>::getVertex(int index) {
    if (index < 0 || index >= vertexVector.size())
        throw runtime_error("Исключение");
    return vertexVector[index];
}
template<class Vertex, class Edge>
Edge* Graph<Vertex, Edge>::insertEdge(Vertex* v1, Vertex* v2) {
    Edge* e = new Edge(v1, v2);
    bool success = data->insertEdge(getIndex(v1), getIndex(v2), e);
    if (!directed)
        data->insertEdge(getIndex(v2), getIndex(v1), e);
    if (success) {
        ++edgeCounter;
        return e;
    }
    else {
        delete e;
        throw runtime_error("Исключение");
    }
}
template<class Vertex, class Edge>
Edge* Graph<Vertex, Edge>::insertEdgeWeight(Vertex* v1, Vertex* v2, int weight) {
    Edge* e = new Edge(v1, v2);
    bool success = data->insertEdge(getIndex(v1), getIndex(v2), e);
    if (!directed)
        data->insertEdge(getIndex(v2), getIndex(v1), e);
    if (success) {
        ++edgeCounter;
        e->setWeight(weight);
        return e;
    }
    else {
        delete e;
        throw runtime_error("Исключение");
    }
}
template<class Vertex, class Edge>
Edge* Graph<Vertex, Edge>::insertEdge(int index1, int index2) {
    if (index1 < 0 || index2 < 0 || index1 >= vertexVector.size() || index2 >= vertexVector.size())
        throw runtime_error("Исключение");
    Edge* e = new Edge(vertexVector[index1], vertexVector[index2]);
    bool success = data->insertEdge(index1, index2, e);
    if (!directed)
        data->insertEdge(index2, index1, e);
    if (success) {
        ++edgeCounter;
        return e;
    }
    else {
        delete e;
        throw runtime_error("Исключение");
    }
}
template<class Vertex, class Edge>
Edge* Graph<Vertex, Edge>::insertEdgeWeight(int index1, int index2, int weight) {
    if (index1 < 0 || index2 < 0 || index1 >= vertexVector.size() || index2 >= vertexVector.size())
        throw runtime_error("Исключение");
    Edge* e = new Edge(vertexVector[index1], vertexVector[index2]);
    bool success = data->insertEdge(index1, index2, e);
    if (!directed)
        data->insertEdge(index2, index1, e);
    if (success) {
        ++edgeCounter;
        e->setWeight(weight);
        return e;
    }
    else {
        delete e;
        throw runtime_error("Исключение");
    }
}
template<class Vertex, class Edge>
bool Graph<Vertex, Edge>::deleteEdge(Vertex* v1, Vertex* v2) {
    if (data->deleteEdge(getIndex(v1), getIndex(v2))) {
        --edgeCounter;
        if (!directed)
            data->deleteEdge(getIndex(v2), getIndex(v1));
        return true;
    }
    else
        return false;
}
template<class Vertex, class Edge>
bool Graph<Vertex, Edge>::deleteEdge(int index1, int index2) {
    if (index1 < 0 || index2 < 0 || index1 >= vertexVector.size() || index2 >= vertexVector.size())
        return false;
    if (data->deleteEdge(index1, index2)) {
        --edgeCounter;
        if (!directed)
            data->deleteEdge(index2, index1);
        return true;
    }
    else
        return false;
}
template<class Vertex, class Edge>
bool Graph<Vertex, Edge>::hasEdge(Vertex* v1, Vertex* v2) {
    int ind1, ind2;
    try { ind1 = getIndex(v1); }
    catch (runtime_error error) {
        cout << error.what() << endl;
        return false;
    }
    try { ind2 = getIndex(v2); }
    catch (runtime_error error) {
        cout << error.what() << endl;
        return false;
    }
    return data->hasEdge(getIndex(v1), getIndex(v2));
}
template<class Vertex, class Edge>
bool Graph<Vertex, Edge>::hasEdge(int v1, int v2) {
    if (v1 < 0 || v1 >= vertexVector.size()) return false;
    if (v2 < 0 || v2 >= vertexVector.size()) return false;
    return data->hasEdge(v1, v2);
}
template<class Vertex, class Edge>
Edge* Graph<Vertex, Edge>::getEdge(Vertex* v1, Vertex* v2) {
    return data->getEdge(getIndex(v1), getIndex(v2));
}
template<class Vertex, class Edge>
Edge* Graph<Vertex, Edge>::getEdge(int v1, int v2) {
    return data->getEdge(v1, v2);
}

template<class Vertex, class Edge>
void Graph<Vertex, Edge>::printGraph(bool isMatrix) {
    if (isMatrix) {
        cout << setw(6) << "";
        for (int i = 0; i < getVertexCount(); i++) {
            cout << setw(6) << "(i" << i;
            if (getVertex(i)->hasName())
                cout << "," << getVertex(i)->getName();
            cout << ")";

        }
        cout << "\n\n\n";
        for (int i = 0; i < getVertexCount(); i++) {
            cout << setw(6) << "(i" << i;
            if (getVertex(i)->hasName())
                cout << "," << getVertex(i)->getName();
            cout << ")";
            for (int j = 0; j < getVertexCount(); j++) {
                if (hasEdge(i, j)) {
                    if (getEdge(i, j)->hasWeight())
                        cout << setw(8) << getEdge(i, j)->getWeight();
                    else
                        cout << setw(8) << "+ ";

                }
                else
                    cout << setw(8) << "- ";
            }
            cout << "\n\n\n";
        }
    }
    else {
        for (int i = 0; i < getVertexCount(); i++) {
            cout << setw(10) << "(i" << i;
            if (getVertex(i)->hasName())
                cout << "," << getVertex(i)->getName();
            cout << ")   ";
            OutputEdgeIterator
                outputEdgeIterator(*this, *(getVertex(i)));
            outputEdgeIterator.toBegin();
            while (!outputEdgeIterator.onEnd()) {
                int index = 0;
                if ((*outputEdgeIterator)->getVertex1()->index != i)
                    index = (*outputEdgeIterator)->getVertex1()->index;
                else
                    index = (*outputEdgeIterator)->getVertex2()->index;
                cout << setw(6) << "->(";
                cout << "i" << getVertex(index)->index;
                if (getVertex(index)->hasName())
                    cout << "," << getVertex(index)->getName();
                if ((*outputEdgeIterator)->hasWeight())
                    cout << "|" << (*outputEdgeIterator)->getWeight();
                cout << ") ";
                ++outputEdgeIterator;
            }
            cout << "\n\n\n";
        }
    }
}
#endif//ADS_RGR_EDGE_H