#ifndef ADS_RGR_GRAPH_FORMS_H
#define ADS_RGR_GRAPH_FORMS_H
#include <iostream>
#include <vector>
#include <list>
using namespace std;
//Форма представления
template<class Edge>
class GraphForm {
public:
    vector<vector<Edge*>> matrixmap;
    //Вставка и удаление вершин и рёбер
    virtual bool insertVertex(int index) = 0;
    virtual bool deleteVertex(int index) = 0;
    virtual bool insertEdge(int v1, int v2, Edge* t) = 0;
    virtual bool deleteEdge(int v1, int v2) = 0;
    //Удалить входящие и исходящие ребра из вершины
    virtual int deleteEdgesFromVertex(int index) = 0;
    //Проверка и получение
    virtual bool hasEdge(int v1, int v2) = 0;
    virtual Edge* getEdge(int v1, int v2) = 0;
};
//Матричная форма представления
template<class Edge>
class GraphMatrixForm : public GraphForm<Edge> {
    bool directed;
public:
    //Матрица смежности
    vector<vector<Edge*>> matrix;
    explicit GraphMatrixForm(bool directed) : directed(directed) {}
    //Вставка и удаление вершин и рёбер
    bool insertVertex(int index);
    bool deleteVertex(int index);
    bool insertEdge(int v1, int v2, Edge* t);
    bool deleteEdge(int v1, int v2);
    //Удалить входящие и исходящие из вершины рёбра
    int deleteEdgesFromVertex(int index);
    //Проверка и получение
    bool hasEdge(int v1, int v2);
    Edge* getEdge(int v1, int v2);
    //Итератор рёбер
    class EdgeIterator {
        bool end;
        GraphMatrixForm* form;
    public:
        int currentI, currentJ;
        explicit EdgeIterator(GraphMatrixForm* f);
        bool toBegin();
        bool onEnd();
        bool toEnd();
        bool next();
        Edge* getEdge();
    };
    //Итератор исходящих рёбер
    class OutputEdgeIterator {
        int currentI, currentJ;
        bool end;
        GraphMatrixForm* form;
    public:
        OutputEdgeIterator(GraphMatrixForm* f, int index);
        bool toBegin();
        bool toEnd();
        bool onEnd();
        bool next();
        Edge* getEdge();
    };
};
//Форма представления список
template<class Edge>
class GraphListForm : public GraphForm<Edge> {
    //Элемент списка
    class Node {
    public:
        Edge* edge;  //Само ребро
        int v2;      //Вторая вершина, которую ребро соединяет
    };
    bool directed;
    vector<list<Node>> edgeList; //Списки смежности
public:
    explicit GraphListForm(bool directed) : directed(directed) {}
    //Вставка и удаление вершин и рёбер
    bool insertVertex(int index);
    bool deleteVertex(int index);
    bool insertEdge(int v1, int v2, Edge* t);
    bool deleteEdge(int v1, int v2);
    //Удалить входящие и исходящие из вершины рёбра
    int deleteEdgesFromVertex(int index);
    //Проверка и получение
    bool hasEdge(int v1, int v2);
    Edge* getEdge(int v1, int v2);
    //Итератор рёбер
    class EdgeIterator {
        int currentI;
        typename list<typename GraphListForm<Edge>::Node>::iterator currentJ;
        bool end;
        GraphListForm* form;
    public:
        explicit EdgeIterator(GraphListForm* f);
        //Установить итератор рёбер на начальное ребро
        bool toBegin();
        bool onEnd();
        //Установить итератор рёбер на конечное ребро
        bool toEnd();
        //Переход к следующей позиции
        bool next();
        Edge* getEdge();
    };
    //Итератор исходящих рёбер
    class OutputEdgeIterator {
        int currentI;
        typename list<typename GraphListForm<Edge>::Node>::iterator currentJ;
        bool end;
        GraphListForm* form;
    public:
        OutputEdgeIterator(GraphListForm* f, int vIndex);
        bool toBegin();
        bool onEnd();
        bool toEnd();
        bool next();
        Edge* getEdge();
    };
};
template<class Edge>
GraphListForm<Edge>::OutputEdgeIterator::OutputEdgeIterator(GraphListForm* f, int vIndex) {
    this->form = f;
    currentI = vIndex;
    toBegin();
}
template<class Edge>
bool GraphListForm<Edge>::OutputEdgeIterator::toBegin() {
    for (currentJ = form->edgeList[currentI].begin(); currentJ != form->edgeList[currentI].end(); ++currentJ)
        if ((*currentJ).edge) {
            end = false;
            return true;
        }
    end = true;
    return false;
}
template<class Edge>
bool GraphListForm<Edge>::OutputEdgeIterator::onEnd() {
    return end;
}
template<class Edge>
bool GraphListForm<Edge>::OutputEdgeIterator::toEnd() {
    typename list<typename GraphListForm<Edge>::Node>::iterator prev_curJ;
    for (currentJ = form->edgeList[currentI].begin(); currentJ != form->edgeList[currentI].end(); ++currentJ)
        if ((*currentJ).edge)
            prev_curJ = currentJ;
    if (!(*prev_curJ).edge) {
        end = true;
        return false;
    }
    else {
        end = false;
        currentJ = prev_curJ;
        return true;
    }
}
template<class Edge>
bool GraphListForm<Edge>::OutputEdgeIterator::next() {
    if (end)
        return false;
    ++currentJ;
    while (currentJ != form->edgeList[currentI].end()) {
        if ((*currentJ).edge)
            return true;
        ++currentJ;
    }
    end = true;
    return true;
}
template<class Edge>
Edge* GraphListForm<Edge>::OutputEdgeIterator::getEdge() {
    if (end)
        throw runtime_error("Исключение");
    return (*currentJ).edge;
}
template<class Edge>
GraphListForm<Edge>::EdgeIterator::EdgeIterator(GraphListForm* f) {
    this->form = f;
}
template<class Edge>
bool GraphListForm<Edge>::EdgeIterator::toBegin() {
    for (currentI = 0; currentI < form->edgeList.size(); ++currentI)
        for (currentJ = form->edgeList[currentI].begin(); currentJ != form->edgeList[currentI].end(); ++currentJ)
            if ((*currentJ).edge) {
                end = false;
                return true;
            }
    end = true;
    return false;
}
template<class Edge>
bool GraphListForm<Edge>::EdgeIterator::onEnd() {
    return end;
}
template<class Edge>
bool GraphListForm<Edge>::EdgeIterator::toEnd() {
    typename list<typename GraphListForm<Edge>::Node>::iterator prev_curJ;
    for (currentI = 0; currentI < form->edgeList.size(); ++currentI) {
        for (currentJ = form->edgeList[currentI].begin(); currentJ != form->edgeList[currentI].end(); ++currentJ) {
            if ((*currentJ).edge)
                prev_curJ = currentJ;
            if (!(*prev_curJ).edge) {
                end = true;
                return false;
            }
            else {
                end = false;
                currentJ = prev_curJ;
                return true;
            }
        }
    }
}
template<class Edge>
bool GraphListForm<Edge>::EdgeIterator::next() {
    if (end)
        return false;
    ++currentJ;
    while (currentI < form->edgeList.size()) {
        while (currentJ != form->edgeList[currentI].end()) {
            if ((*currentJ).edge && (form->directed || !form->directed && (*currentJ).v2 > currentI))
                return true;
            ++currentJ;
        }
        ++currentI;
        if (currentI < form->edgeList.size())
            currentJ = form->edgeList[currentI].begin();
    }
    end = true;
    return true;
}
template<class Edge>
Edge* GraphListForm<Edge>::EdgeIterator::getEdge() {
    if (end)
        throw runtime_error("Исключение");
    return (*currentJ).edge;
}
template<class Edge>
bool GraphListForm<Edge>::insertVertex(int index) {
    int size = edgeList.size(); //Число вершин
    if (index < 0 || index > size) //Неверный номер вершины
        return false;
    //Создаём новый список смежности
    list<Node> newList;
    //Вставляем
    edgeList.insert(edgeList.begin() + index, newList);
    ++size;
    //Обновляем дескрипторы
    for (int i = 0; i < size; ++i)
        for (typename list<Node>::iterator j = edgeList[i].begin(); j != edgeList[i].end(); ++j)
            if ((*j).v2 >= index)//если текущая вершина имеет больший номер, чем вставляемая,
                ++((*j).v2);//то увеличиваем этот номер
    return true;
}
template<class Edge>
bool GraphListForm<Edge>::deleteVertex(int index) {
    int size = edgeList.size(); //Число вершин
    if (index < 0 || index >= size)  //Неверный номер вершины
        return false;
    //Удаляем из списков записи о рёбрах
    for (int i = 0; i < size; ++i)
        for (typename list<Node>::iterator j = edgeList[i].begin(); j != edgeList[i].end(); ++j)
            if ((*j).v2 == index) {
                edgeList[i].erase(j);
                break;
            }
    //Удаляем список смежности
    edgeList.erase(edgeList.begin() + index);
    --size;
    //Обновляем дескрипторы
    for (int i = 0; i < size; ++i)
        for (typename list<Node>::iterator j = edgeList[i].begin(); j != edgeList[i].end(); ++j)
            if ((*j).v2 > index)//если текущая вершина имеет больший номер, чем удаляемая,
                --((*j).v2);//то уменьшить этот номер
    return true;
}
template<class Edge>
bool GraphListForm<Edge>::insertEdge(int v1, int v2, Edge* t) {
    int size = edgeList.size(); //Число вершин
    if (v1 < 0 || v2 < 0 || v1 >= size || v2 >= size)//Неверный номер вершины
        return false;
    if (v1 == v2 || hasEdge(v1, v2))  //Петля или ребро уже есть
        return false;
    //Вставляем ребро
    Node node;
    node.edge = t;
    node.v2 = v2;
    edgeList[v1].push_front(node);
    return true;
}
template<class Edge>
bool GraphListForm<Edge>::deleteEdge(int v1, int v2) {
    int size = edgeList.size(); //Число вершин
    //Неверный номер вершины
    if (v1 < 0 || v2 < 0 || v1 >= size || v2 >= size)
        return false;
    //Ребра нет
    if (v1 == v2 || hasEdge(v1, v2) == false)
        return false;
    //Удаляем ребро
    for (typename list<Node>::iterator j = edgeList[v1].begin(); j != edgeList[v1].end(); ++j)
        if ((*j).v2 == v2) {
            edgeList[v1].erase(j);
            break;
        }
    return true;
}
template<class Edge>
int GraphListForm<Edge>::deleteEdgesFromVertex(int index) {
    int size = edgeList.size(); //Число вершин
    int deleted = 0;
    //Неверный номер вершины
    if (index < 0 || index >= size)
        return 0;
    //Удаляем связанные с вершиной рёбра
    for (int i = 0; i < size; ++i)
        for (typename list<Node>::iterator j = edgeList[i].begin(); j != edgeList[i].end(); ++j)
            if ((*j).v2 == index) {
                delete (*j).edge;
                edgeList[i].erase(j);
                ++deleted;
                //Стираем симметричное ребро
                if (!directed)
                    for (typename list<Node>::iterator k = edgeList[index].begin(); k != edgeList[index].end(); ++k)
                        if ((*k).v2 == i) {
                            edgeList[index].erase(k);
                            break;
                        }
                break;
            }
    if (directed) {
        for (typename list<Node>::iterator z = edgeList[index].begin(); z != edgeList[index].end(); ++z) {
            delete (*z).edge;
            deleted++;
        }
    }
    return deleted;
}
template<class Edge>
bool GraphListForm<Edge>::hasEdge(int v1, int v2) {
    int size = edgeList.size(); //Число вершин
    //Неверный номер вершины
    if (v1 < 0 || v2 < 0 || v1 >= size || v2 >= size)
        return false;
    //Петля
    if (v1 == v2)
        return false;
    for (typename list<Node>::iterator j = edgeList[v1].begin(); j != edgeList[v1].end(); ++j)
        if ((*j).v2 == v2)
            return true;
    return false;
}
template<class Edge>
Edge* GraphListForm<Edge>::getEdge(int v1, int v2) {
    int size = edgeList.size(); //Число вершин
    //Неверный номер вершины
    if (v1 < 0 || v2 < 0 || v1 >= size || v2 >= size)
        throw runtime_error("Исключение");
    //Петля
    if (v1 == v2)
        throw runtime_error("Исключение");
    for (typename list<Node>::iterator j = edgeList[v1].begin(); j != edgeList[v1].end(); ++j)
        if ((*j).v2 == v2)
            return (*j).edge;
    throw runtime_error("Исключение");
}
template<class Edge>
GraphMatrixForm<Edge>::OutputEdgeIterator::OutputEdgeIterator(GraphMatrixForm* f, int index) {
    this->form = f;
    currentI = index;
    toBegin();
}
template<class Edge>
bool GraphMatrixForm<Edge>::OutputEdgeIterator::toBegin() {
    for (currentJ = 0; currentJ < form->matrix.size(); ++currentJ)
        if (form->matrix[currentI][currentJ]) {
            end = false;
            return true;
        }
    end = true;
    return false;
}
template<class Edge>
bool GraphMatrixForm<Edge>::OutputEdgeIterator::toEnd() {
    for (currentJ = form->matrix.size() - 1; currentJ >= 0; --currentJ)
        if (form->matrix[currentI][currentJ]) {
            end = false;
            return true;
        }
    end = true;
    return false;
}
template<class Edge>
bool GraphMatrixForm<Edge>::OutputEdgeIterator::onEnd() {
    return end;
}
template<class Edge>
bool GraphMatrixForm<Edge>::OutputEdgeIterator::next() {
    if (end)
        return false;
    ++currentJ;
    while (currentJ < form->matrix.size()) {
        if (form->matrix[currentI][currentJ])
            return true;
        ++currentJ;
    }
    end = true;
    return false;
}
template<class Edge>
Edge* GraphMatrixForm<Edge>::OutputEdgeIterator::getEdge() {
    if (end)
        throw runtime_error("Исключение");
    return form->matrix[currentI][currentJ];
}
template<class Edge>
GraphMatrixForm<Edge>::EdgeIterator::EdgeIterator(GraphMatrixForm* f) {
    this->form = f;
    toBegin();
}
template<class Edge>
bool GraphMatrixForm<Edge>::EdgeIterator::toBegin() {
    for (int i = 0; i < form->matrix.size(); ++i)
        for (int j = 0; j < form->matrix.size(); ++j)
            if (form->matrix[i][j]) {
                currentI = i;
                currentJ = j;
                end = false;
                return true;
            }
    end = true;
    return false;
}
template<class Edge>
bool GraphMatrixForm<Edge>::EdgeIterator::onEnd() {
    return end;
}
template<class Edge>
bool GraphMatrixForm<Edge>::EdgeIterator::toEnd() {
    for (int i = form->matrix.size() - 1; i >= 0; --i)
        for (int j = form->matrix.size() - 1; j >= 0; --j)
            if (form->matrix[i][j]) {
                currentI = i;
                currentJ = j;
                end = false;
                return true;
            }
    end = true;
    return false;
}
template<class Edge>
bool GraphMatrixForm<Edge>::EdgeIterator::next() {
    if (end)
        return false;
    ++currentJ;
    while (currentI < form->matrix.size()) {
        while (currentJ < form->matrix.size()) {
            if (form->matrix[currentI][currentJ])
                return true;
            ++currentJ;
        }
        ++currentI;
        currentJ = (form->directed ? 0 : currentI + 1);
    }
    end = true;
    return false;
}
template<class Edge>
Edge* GraphMatrixForm<Edge>::EdgeIterator::getEdge() {
    if (end)
        throw runtime_error("Исключение");
    if (!(form->matrix[currentI][currentJ]))
        throw runtime_error("Исключение");
    return form->matrix[currentI][currentJ];
}
template<class Edge>
bool GraphMatrixForm<Edge>::insertVertex(int index) {
    int size = matrix.size(); //Число вершин
    //Неверный номер вершины
    if (index < 0 || index > size) return false;
    //Создаём новую пустую строку
    vector<Edge*> newLine;
    newLine.assign(size, NULL);
    //Вставляем новую строку:
    matrix.insert(matrix.begin() + index, newLine);
    ++size;
    //Вставляем новый столбец:
    for (int i = 0; i < size; ++i)
        matrix[i].insert(matrix[i].begin() + index, (Edge*)NULL);
    return true;
}
template<class Edge>
bool GraphMatrixForm<Edge>::deleteVertex(int index) {
    int size = matrix.size(); //Число вершин
    //Неверный номер вершины
    if (index < 0 || index >= size) return false;
    //Удаляем строку:
    matrix.erase(matrix.begin() + index);
    --size;
    //Удаляем столбец:
    for (int i = 0; i < size; i++)
        matrix[i].erase(matrix[i].begin() + index);
    return true;
}
template<class Edge>
bool GraphMatrixForm<Edge>::insertEdge(int v1, int v2, Edge* t) {
    int size = matrix.size(); //Число вершин
    //Неверный номер вершины
    if (v1 < 0 || v2 < 0 || v1 >= size || v2 >= size) return false;
    //Петля или ребро уже есть
    if (v1 == v2 || matrix[v1][v2] != NULL) return false;
    //Вставляем ребро
    matrix[v1][v2] = t;
    return true;
}
template<class Edge>
bool GraphMatrixForm<Edge>::deleteEdge(int v1, int v2) {
    int size = matrix.size(); //Число вершин
    //Неверный номер вершины
    if (v1 < 0 || v2 < 0 || v1 >= size || v2 >= size) return false;
    //Ребра нет
    if (v1 == v2 || matrix[v1][v2] == NULL) return false;
    matrix[v1][v2] = NULL;
    return true;
}
template<class Edge>
int GraphMatrixForm<Edge>::deleteEdgesFromVertex(int index) {
    int size = matrix.size(); //Число вершин
    int deleted = 0;
    //Неверный номер вершины
    if (index < 0 || index >= size) return 0;
    //Удаляем связанные с вершиной рёбра
    for (int i = 0; i < size; i++) {
        if (matrix[i][index] != NULL) {
            delete matrix[i][index];
            matrix[i][index] = NULL;
            ++deleted;
            //Стираем симметричное ребро
            if (!directed)
                matrix[index][i] = NULL;
        }
        if (matrix[index][i] != NULL) {
            delete matrix[index][i];
            matrix[index][i] = NULL;
            ++deleted;
        }
    }
    return deleted;
}
template<class Edge>
bool GraphMatrixForm<Edge>::hasEdge(int v1, int v2) {
    int size = matrix.size(); //Число вершин
    //Неверный номер вершины
    if (v1 < 0 || v2 < 0 || v1 >= size || v2 >= size)
        return false;
    if (v1 == v2) //Петля
        return false;
    if (matrix[v1][v2] != NULL)
        return true;
    return false;
}
template<class Edge>
Edge* GraphMatrixForm<Edge>::getEdge(int v1, int v2) {
    int size = matrix.size(); //Число вершин
    //Неверный номер вершины
    if (v1 < 0 || v2 < 0 || v1 >= size || v2 >= size)
        throw runtime_error("Исключение");
    if (v1 == v2 || matrix[v1][v2] == NULL)//Петля
        throw runtime_error("Исключение");
    return matrix[v1][v2];
}
#endif //ADS_RGR_GRAPH_FORMS_H