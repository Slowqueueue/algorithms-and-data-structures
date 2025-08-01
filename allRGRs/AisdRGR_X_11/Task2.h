#ifndef ADS_RGR_SECOND_TASK_H
#define ADS_RGR_SECOND_TASK_H

#include "Graph.h"
#include <vector>
using namespace std;

template<class Vertex, class Edge>
class SecondTask {
    Graph<Vertex, Edge>* graph;
    vector<vector<vector<int>>> way;
    bool hasWeight = true;
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

    void result();
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
                    if (!graph->getEdge(u, v)->hasWeight()) {
                        hasWeight = false;
                        return;
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
    set(g);
}

template<class Vertex, class Edge>
SecondTask<Vertex, Edge>::SecondTask(SecondTask<Vertex, Edge>& secondTask) {
    Graph<Vertex, Edge>* g = secondTask.graph;
    set(g);
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
void SecondTask<Vertex, Edge>::result() {
    if (err) {
        cout << "В графе содержится отрицательный цикл" << endl;
        return;
    }
    if (!hasWeight) {
        cout << "Граф не является взвешенным" << endl;
        return;
    }
    for (int i = 0; i < graph->getVertexCount(); ++i) {
        cout << "Пути из вершины " << i << ":" << endl;
        int legacyway = -1;
        int* weightsum = new int[graph->getVertexCount()];
        for (int j = 0; j < graph->getVertexCount(); ++j) {
            weightsum[j] = 0;
            if (i == j)
                continue;
            cout << i << " -> " << j << ": ";
            for (int k = 0; k < graph->getVertexCount(); ++k) {
                if (way[i][j][k] != -1) {
                    cout << way[i][j][k] << " ";
                    if (legacyway != -1) weightsum[j] = weightsum[j] + graph->getEdge(legacyway, way[i][j][k])->getWeight();
                    legacyway = way[i][j][k];
                }
            }
            legacyway = -1;
            if (weightsum[j] != 0) cout << "Расстояние: " << weightsum[j];
            else cout << "Нет пути";
            cout << endl;
        }
    }
}

#endif //ADS_RGR_SECOND_TASK_H
