#ifndef ADS_RGR_FIRST_TASK_H
#define ADS_RGR_FIRST_TASK_H
#include "Graph.h"
#include <vector>

using namespace std;
template<class Vertex, class Edge>
class FirstTask {
    Graph<Vertex, Edge>* graph;
    vector<bool> visited;
    vector<int> path;
    bool res;
    bool hamilton(int cur);
public:
    explicit FirstTask(Graph<Vertex, Edge>* g);
    FirstTask(FirstTask<Vertex, Edge>& firstTask);
    ~FirstTask();
    void set(Graph<Vertex, Edge>* g);
    void restart();
    void result();
};
template<class Vertex, class Edge>
bool FirstTask<Vertex, Edge>::hamilton(int cur) {
    {
        path.push_back(cur);
        if (path.size() == graph->getVertexCount()) {
            if (graph->hasEdge(path.back(), path[0])) {
                return true;
            }
            else {
                path.pop_back();
                return false;
            }
        }
        visited[cur] = true;
        for (int i = 0; i < graph->getVertexCount(); ++i) {
            if (graph->hasEdge(cur, i) && !visited[i]) {
                if (hamilton(i)) {
                    return true;
                }
            }
        }
        visited[cur] = false;
        path.pop_back();
        return false;
    }
}
template<class Vertex, class Edge>
FirstTask<Vertex, Edge>::FirstTask(Graph<Vertex, Edge>* g) {
    graph = g;
    restart();
}
template<class Vertex, class Edge>
FirstTask<Vertex, Edge>::FirstTask(FirstTask<Vertex, Edge>& firstTask) {
    graph = firstTask.graph;
    restart();
}
template<class Vertex, class Edge>
FirstTask<Vertex, Edge>::~FirstTask() {
    visited.clear();
    path.clear();
}
template<class Vertex, class Edge>
void FirstTask<Vertex, Edge>::set(Graph<Vertex, Edge>* g) {
    graph = g;
    restart();
}
template<class Vertex, class Edge>
void FirstTask<Vertex, Edge>::restart() {
    visited.resize(graph->getVertexCount());
    path.resize(graph->getVertexCount());
    for (int i = 0; i < graph->getVertexCount(); ++i) {
        res = hamilton(i);
        if (res) return;
        visited.resize(graph->getVertexCount());
        path.clear();
    }
}
template<class Vertex, class Edge>
void FirstTask<Vertex, Edge>::result() {
    if (res) {
        cout << "Гамильтонов цикл:\n";
        for (int i = 0; i < graph->getVertexCount(); ++i) {
            cout << path[i] << " -> ";
        }
        cout << path[0] << endl;
    }
    else {
        cout << "Нет решений\n";
    }
}
#endif //ADS_RGR_FIRST_TASK_H