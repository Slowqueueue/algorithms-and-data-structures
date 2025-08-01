#ifndef ADS_RGR_SECOND_TASK_H
#define ADS_RGR_SECOND_TASK_H

#include "Graph.h"
#include <vector>
using namespace std;

template<class Vertex, class Edge>
class SecondTask {
    Graph<Vertex, Edge>* graph;
    vector<vector<vector<int>>> way;
    bool hasWeight = false;
    bool err = false;
    const int INF = 10000000;

    void resize();

    void bellman_ford(int s);

    void err_test(int s);

    int getMinEdgeCount(vector<vector<int>> A, int i);

public:
    explicit SecondTask(Graph<Vertex, Edge>* g);

    SecondTask(SecondTask<Vertex, Edge>& secondTask);

    ~SecondTask();

    void set(Graph<Vertex, Edge>* g);

    void restart();

    void result(int index,int d);
};

template<class Vertex, class Edge>
void SecondTask<Vertex, Edge>::err_test(int s) {
    int* dist = new int[graph->getVertexCount()];
    for (int i = 1; i <= graph->getVertexCount() - 1; i++) {
        for (int u = 0; u < graph->getVertexCount(); ++u) {
            for (int v = 0; v < graph->getVertexCount(); ++v) {
                if (graph->hasEdge(u, v)) {
                    if (dist[u] != INF && dist[u] + graph->getEdge(u, v)->getWeight() < dist[v]) dist[v] = dist[u] + graph->getEdge(u, v)->getWeight();
                }
            }
        }
    }
    for (int i = 0; i < graph->getEdgeCount(); i++) {
        for (int u = 0; u < graph->getVertexCount(); ++u) {
            for (int v = 0; v < graph->getVertexCount(); ++v) {
                if (graph->hasEdge(u, v)) {
                    if (dist[u] != INF && dist[u] + graph->getEdge(u, v)->getWeight() < dist[v]) {
                        err = true;
                        delete[] dist;
                        return;
                    }
                }
            }
        }
    }
    delete[] dist;
}

template<class Vertex, class Edge>
void SecondTask<Vertex, Edge>::bellman_ford(int s) {
    vector<vector<int>> A;
    vector<vector<int>> P;
    vector<int> p;
    A.resize(graph->getVertexCount());
    P.resize(graph->getVertexCount());
    p.resize(graph->getVertexCount());
    for (int v = 0; v < graph->getVertexCount(); v++) {
        A[v].resize(graph->getVertexCount());
        P[v].resize(graph->getVertexCount());
        p[v] = -1;
        for (int i = 0; i < graph->getVertexCount(); i++) {
            A[v][i] = INF;
            P[v][i] = -1;
        }
    }
    A[s][0] = 0;
    for (int i = 1; i < graph->getVertexCount() - 1; i++) {
        for (int u = 0; u < graph->getVertexCount(); ++u) {
            for (int v = 0; v < graph->getVertexCount(); ++v) {
                if (graph->hasEdge(u, v)) {
                    if (!hasWeight) {
                        hasWeight = graph->getEdge(u, v)->hasWeight();
                        if (!hasWeight) return;
                    }
                    if ((graph->getEdge(u, v)->getWeight()) >= 0) {
                        if (A[v][i] > A[u][i - 1] + graph->getEdge(u, v)->getWeight()) {
                            A[v][i] = A[u][i - 1] + graph->getEdge(u, v)->getWeight();
                            P[v][i] = u;
                        }
                    }
                    else {
                        if (A[v][i] > A[u][i - 1] - graph->getEdge(u, v)->getWeight()) {
                            A[v][i] = A[u][i - 1] - graph->getEdge(u, v)->getWeight();
                            P[v][i] = u;
                        }
                    }
                }
            }
        }
    }
    for (int i = 0; i < graph->getVertexCount(); ++i) {
        if (i == s)
            continue;
        int I = i;
        int j = getMinEdgeCount(A, I);
        while (j >= 0 && j != INF) {
            p[j] = I;
            I = P[I][j];
            j--;
        }
        for (int k = 0; k < graph->getVertexCount(); ++k) {
            way[s][i][k] = p[k];
        }
        for (int k = 0; k < graph->getVertexCount(); ++k) {
            p[k] = -1;
        }
    }

    for (int i = 0; i < graph->getVertexCount(); ++i) {
        A[i].clear();
        P[i].clear();
    }
    A.clear();
    P.clear();
    p.clear();
}

template<class Vertex, class Edge>
int SecondTask<Vertex, Edge>::getMinEdgeCount(vector<vector<int>> A, int i) {
    int min = INF;
    for (int j = 0; j < graph->getVertexCount(); ++j) {
        if (A[i][j] > 0 && A[i][j] < min) {
            min = j;
        }
    }
    return min;
}

template<class Vertex, class Edge>
void SecondTask<Vertex, Edge>::resize() {
    way.resize(graph->getVertexCount());
    for (int s = 0; s < graph->getVertexCount(); ++s) {
        way[s].resize(graph->getVertexCount());
        for (int i = 0; i < graph->getVertexCount(); ++i) {
            way[s][i].resize(graph->getVertexCount());
        }
    }
}

template<class Vertex, class Edge>
SecondTask<Vertex, Edge>::SecondTask(Graph<Vertex, Edge>* g) {
    graph = g;
    resize();
    restart();
}

template<class Vertex, class Edge>
SecondTask<Vertex, Edge>::SecondTask(SecondTask<Vertex, Edge>& secondTask) {
    graph = secondTask.graph;
    resize();
    restart();
}

template<class Vertex, class Edge>
SecondTask<Vertex, Edge>::~SecondTask() {
    for (int s = 0; s < graph->getVertexCount(); ++s) {
        for (int j = 0; j < graph->getVertexCount(); ++j) {
            way[s][j].clear();
        }
        way[s].clear();
    }
    way.clear();
}

template<class Vertex, class Edge>
void SecondTask<Vertex, Edge>::set(Graph<Vertex, Edge>* g) {
    graph = g;
    resize();
    restart();
}

template<class Vertex, class Edge>
void SecondTask<Vertex, Edge>::restart() {
    for (int s = 0; s < graph->getVertexCount(); ++s) {
        err_test(s);
        if (err) return;
    }
    for (int s = 0; s < graph->getVertexCount(); ++s) {
        for (int i = 0; i < graph->getVertexCount(); ++i) {
            for (int j = 0; j < graph->getVertexCount(); ++j) {
                way[s][i][j] = -1;
            }
        }
    }
    for (int s = 0; s < graph->getVertexCount(); ++s) {
        bellman_ford(s);
    }
}

template<class Vertex, class Edge>
void SecondTask<Vertex, Edge>::result(int index, int d) {
    if (err) {
        cout << "В графе содержится отрицательный цикл" << endl;
        return;
    }
    if (!hasWeight) {
        cout << "Граф не является взвешенным" << endl;
        return;
    }
    if (index >= graph->getVertexCount()) {
        cout << "Вершина не существует" << endl;
        return;
    }
        cout << "Пути из " << index << " вершины:" << endl;
        int count = 0, i = 0, k_legacy = 0, legacyway = -1;
        int* arr = new int[graph->getVertexCount()], *weightsum = new int [graph->getVertexCount()];
        for (int j = 0; j < graph->getVertexCount(); ++j) {
            weightsum[j] = 0;
            if (index == j)
                continue;
            cout << index << " -> " << j << ": ";
            for (int k = 0; k < graph->getVertexCount(); ++k) {
                if (way[index][j][k] != -1) {
                    cout << way[index][j][k] << " ";
                    if (legacyway != -1) weightsum[j] = weightsum[j] + graph->getEdge(legacyway, way[index][j][k])->getWeight();
                    k_legacy = k;
                    legacyway = way[index][j][k];
                }
            }
            legacyway = -1;
            if (weightsum[j] != 0) cout << "Расстояние: " << weightsum[j];
            cout << endl;
            //if (abs(weightsum[j]) <= d) {
            if (weightsum[j] <= d) {
                if (way[index][j][k_legacy] != -1) {
                    arr[i] = way[index][j][k_legacy];
                    i++;
                    count++;
                }
            }
            cout << endl;
        }
        if (count != 0) {
            cout << "Искомые вершины: " << endl;
            for (int h = 0; h < count; ++h) {
                cout << arr[h] << " ";
            }
        }
        else cout << "Искомых вершин не существует";
        cout << endl;
}

#endif //ADS_RGR_SECOND_TASK_H
