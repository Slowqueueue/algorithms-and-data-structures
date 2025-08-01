#ifndef ADS_RGR_GRAPH_FORMS_H
#define ADS_RGR_GRAPH_FORMS_H
#include <iostream>
#include <vector>
#include <list>
using namespace std;
//����� �������������
template<class Edge>
class GraphForm {
public:
    vector<vector<Edge*>> matrixmap;
    //������� � �������� ������ � ����
    virtual bool insertVertex(int index) = 0;
    virtual bool deleteVertex(int index) = 0;
    virtual bool insertEdge(int v1, int v2, Edge* t) = 0;
    virtual bool deleteEdge(int v1, int v2) = 0;
    //������� �������� � ��������� ����� �� �������
    virtual int deleteEdgesFromVertex(int index) = 0;
    //�������� � ���������
    virtual bool hasEdge(int v1, int v2) = 0;
    virtual Edge* getEdge(int v1, int v2) = 0;
};
//��������� ����� �������������
template<class Edge>
class GraphMatrixForm : public GraphForm<Edge> {
    bool directed;
public:
    //������� ���������
    vector<vector<Edge*>> matrix;
    explicit GraphMatrixForm(bool directed) : directed(directed) {}
    //������� � �������� ������ � ����
    bool insertVertex(int index);
    bool deleteVertex(int index);
    bool insertEdge(int v1, int v2, Edge* t);
    bool deleteEdge(int v1, int v2);
    //������� �������� � ��������� �� ������� ����
    int deleteEdgesFromVertex(int index);
    //�������� � ���������
    bool hasEdge(int v1, int v2);
    Edge* getEdge(int v1, int v2);
    //�������� ����
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
    //�������� ��������� ����
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
//����� ������������� ������
template<class Edge>
class GraphListForm : public GraphForm<Edge> {
    //������� ������
    class Node {
    public:
        Edge* edge;  //���� �����
        int v2;      //������ �������, ������� ����� ���������
    };
    bool directed;
    vector<list<Node>> edgeList; //������ ���������
public:
    explicit GraphListForm(bool directed) : directed(directed) {}
    //������� � �������� ������ � ����
    bool insertVertex(int index);
    bool deleteVertex(int index);
    bool insertEdge(int v1, int v2, Edge* t);
    bool deleteEdge(int v1, int v2);
    //������� �������� � ��������� �� ������� ����
    int deleteEdgesFromVertex(int index);
    //�������� � ���������
    bool hasEdge(int v1, int v2);
    Edge* getEdge(int v1, int v2);
    //�������� ����
    class EdgeIterator {
        int currentI;
        typename list<typename GraphListForm<Edge>::Node>::iterator currentJ;
        bool end;
        GraphListForm* form;
    public:
        explicit EdgeIterator(GraphListForm* f);
        //���������� �������� ���� �� ��������� �����
        bool toBegin();
        bool onEnd();
        //���������� �������� ���� �� �������� �����
        bool toEnd();
        //������� � ��������� �������
        bool next();
        Edge* getEdge();
    };
    //�������� ��������� ����
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
        throw runtime_error("����������");
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
        throw runtime_error("����������");
    return (*currentJ).edge;
}
template<class Edge>
bool GraphListForm<Edge>::insertVertex(int index) {
    int size = edgeList.size(); //����� ������
    if (index < 0 || index > size) //�������� ����� �������
        return false;
    //������ ����� ������ ���������
    list<Node> newList;
    //���������
    edgeList.insert(edgeList.begin() + index, newList);
    ++size;
    //��������� �����������
    for (int i = 0; i < size; ++i)
        for (typename list<Node>::iterator j = edgeList[i].begin(); j != edgeList[i].end(); ++j)
            if ((*j).v2 >= index)//���� ������� ������� ����� ������� �����, ��� �����������,
                ++((*j).v2);//�� ����������� ���� �����
    return true;
}
template<class Edge>
bool GraphListForm<Edge>::deleteVertex(int index) {
    int size = edgeList.size(); //����� ������
    if (index < 0 || index >= size)  //�������� ����� �������
        return false;
    //������� �� ������� ������ � �����
    for (int i = 0; i < size; ++i)
        for (typename list<Node>::iterator j = edgeList[i].begin(); j != edgeList[i].end(); ++j)
            if ((*j).v2 == index) {
                edgeList[i].erase(j);
                break;
            }
    //������� ������ ���������
    edgeList.erase(edgeList.begin() + index);
    --size;
    //��������� �����������
    for (int i = 0; i < size; ++i)
        for (typename list<Node>::iterator j = edgeList[i].begin(); j != edgeList[i].end(); ++j)
            if ((*j).v2 > index)//���� ������� ������� ����� ������� �����, ��� ���������,
                --((*j).v2);//�� ��������� ���� �����
    return true;
}
template<class Edge>
bool GraphListForm<Edge>::insertEdge(int v1, int v2, Edge* t) {
    int size = edgeList.size(); //����� ������
    if (v1 < 0 || v2 < 0 || v1 >= size || v2 >= size)//�������� ����� �������
        return false;
    if (v1 == v2 || hasEdge(v1, v2))  //����� ��� ����� ��� ����
        return false;
    //��������� �����
    Node node;
    node.edge = t;
    node.v2 = v2;
    edgeList[v1].push_front(node);
    return true;
}
template<class Edge>
bool GraphListForm<Edge>::deleteEdge(int v1, int v2) {
    int size = edgeList.size(); //����� ������
    //�������� ����� �������
    if (v1 < 0 || v2 < 0 || v1 >= size || v2 >= size)
        return false;
    //����� ���
    if (v1 == v2 || hasEdge(v1, v2) == false)
        return false;
    //������� �����
    for (typename list<Node>::iterator j = edgeList[v1].begin(); j != edgeList[v1].end(); ++j)
        if ((*j).v2 == v2) {
            edgeList[v1].erase(j);
            break;
        }
    return true;
}
template<class Edge>
int GraphListForm<Edge>::deleteEdgesFromVertex(int index) {
    int size = edgeList.size(); //����� ������
    int deleted = 0;
    //�������� ����� �������
    if (index < 0 || index >= size)
        return 0;
    //������� ��������� � �������� ����
    for (int i = 0; i < size; ++i)
        for (typename list<Node>::iterator j = edgeList[i].begin(); j != edgeList[i].end(); ++j)
            if ((*j).v2 == index) {
                delete (*j).edge;
                edgeList[i].erase(j);
                ++deleted;
                //������� ������������ �����
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
    int size = edgeList.size(); //����� ������
    //�������� ����� �������
    if (v1 < 0 || v2 < 0 || v1 >= size || v2 >= size)
        return false;
    //�����
    if (v1 == v2)
        return false;
    for (typename list<Node>::iterator j = edgeList[v1].begin(); j != edgeList[v1].end(); ++j)
        if ((*j).v2 == v2)
            return true;
    return false;
}
template<class Edge>
Edge* GraphListForm<Edge>::getEdge(int v1, int v2) {
    int size = edgeList.size(); //����� ������
    //�������� ����� �������
    if (v1 < 0 || v2 < 0 || v1 >= size || v2 >= size)
        throw runtime_error("����������");
    //�����
    if (v1 == v2)
        throw runtime_error("����������");
    for (typename list<Node>::iterator j = edgeList[v1].begin(); j != edgeList[v1].end(); ++j)
        if ((*j).v2 == v2)
            return (*j).edge;
    throw runtime_error("����������");
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
        throw runtime_error("����������");
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
        throw runtime_error("����������");
    if (!(form->matrix[currentI][currentJ]))
        throw runtime_error("����������");
    return form->matrix[currentI][currentJ];
}
template<class Edge>
bool GraphMatrixForm<Edge>::insertVertex(int index) {
    int size = matrix.size(); //����� ������
    //�������� ����� �������
    if (index < 0 || index > size) return false;
    //������ ����� ������ ������
    vector<Edge*> newLine;
    newLine.assign(size, NULL);
    //��������� ����� ������:
    matrix.insert(matrix.begin() + index, newLine);
    ++size;
    //��������� ����� �������:
    for (int i = 0; i < size; ++i)
        matrix[i].insert(matrix[i].begin() + index, (Edge*)NULL);
    return true;
}
template<class Edge>
bool GraphMatrixForm<Edge>::deleteVertex(int index) {
    int size = matrix.size(); //����� ������
    //�������� ����� �������
    if (index < 0 || index >= size) return false;
    //������� ������:
    matrix.erase(matrix.begin() + index);
    --size;
    //������� �������:
    for (int i = 0; i < size; i++)
        matrix[i].erase(matrix[i].begin() + index);
    return true;
}
template<class Edge>
bool GraphMatrixForm<Edge>::insertEdge(int v1, int v2, Edge* t) {
    int size = matrix.size(); //����� ������
    //�������� ����� �������
    if (v1 < 0 || v2 < 0 || v1 >= size || v2 >= size) return false;
    //����� ��� ����� ��� ����
    if (v1 == v2 || matrix[v1][v2] != NULL) return false;
    //��������� �����
    matrix[v1][v2] = t;
    return true;
}
template<class Edge>
bool GraphMatrixForm<Edge>::deleteEdge(int v1, int v2) {
    int size = matrix.size(); //����� ������
    //�������� ����� �������
    if (v1 < 0 || v2 < 0 || v1 >= size || v2 >= size) return false;
    //����� ���
    if (v1 == v2 || matrix[v1][v2] == NULL) return false;
    matrix[v1][v2] = NULL;
    return true;
}
template<class Edge>
int GraphMatrixForm<Edge>::deleteEdgesFromVertex(int index) {
    int size = matrix.size(); //����� ������
    int deleted = 0;
    //�������� ����� �������
    if (index < 0 || index >= size) return 0;
    //������� ��������� � �������� ����
    for (int i = 0; i < size; i++) {
        if (matrix[i][index] != NULL) {
            delete matrix[i][index];
            matrix[i][index] = NULL;
            ++deleted;
            //������� ������������ �����
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
    int size = matrix.size(); //����� ������
    //�������� ����� �������
    if (v1 < 0 || v2 < 0 || v1 >= size || v2 >= size)
        return false;
    if (v1 == v2) //�����
        return false;
    if (matrix[v1][v2] != NULL)
        return true;
    return false;
}
template<class Edge>
Edge* GraphMatrixForm<Edge>::getEdge(int v1, int v2) {
    int size = matrix.size(); //����� ������
    //�������� ����� �������
    if (v1 < 0 || v2 < 0 || v1 >= size || v2 >= size)
        throw runtime_error("����������");
    if (v1 == v2 || matrix[v1][v2] == NULL)//�����
        throw runtime_error("����������");
    return matrix[v1][v2];
}
#endif //ADS_RGR_GRAPH_FORMS_H