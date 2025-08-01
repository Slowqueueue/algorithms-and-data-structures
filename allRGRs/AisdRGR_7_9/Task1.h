#ifndef ADS_RGR_FIRST_TASK_H
#define ADS_RGR_FIRST_TASK_H
#include "Graph.h"
#include <vector>
using namespace std;

enum class VertexState {
    Unvisited,
    Visiting,
    Visited
};

template <class VertexT, class EdgeT>
class FirstTask {
    Graph<VertexT, EdgeT>* graph;
    vector<int> sortedVertices;
public:
    FirstTask(Graph<VertexT, EdgeT>* g) {
        Set(g);
    }

    FirstTask(const FirstTask<VertexT, EdgeT>& FirstTask)
    {
        Graph<VertexT, EdgeT>* g = FirstTask.graph;
        Set(g);
    }

    ~FirstTask() {
        sortedVertices.clear();
    }

    void Set(Graph<VertexT, EdgeT>* g)
    {
        graph = g;
        Restart();
    }

    void Restart()
    {
        sortedVertices.clear();
        int vertexCount = graph->getVertexCount();
        vector<VertexState> state(vertexCount, VertexState::Unvisited);
        for (int i = 0; i < vertexCount; ++i) {
            if (state[i] == VertexState::Unvisited) {
                if (!dfs(graph->getVertex(i), state)) {
                    sortedVertices.clear();
                    return;
                }
            }
        }
        reverse(sortedVertices.begin(), sortedVertices.end());
    }

    void Result()
    {
        if (!sortedVertices.empty()) {
            for (int vertexIndex : sortedVertices) {
                cout << vertexIndex << " ";
            }
            cout << endl;
        }
        else {
            cout << "Граф пуст, либо содержит цикл" << endl;
        }
    }
protected:
    bool dfs(VertexT* vertex, vector<VertexState>& state) {
        state[vertex->index] = VertexState::Visiting;
        for (int i = 0; i < graph->getVertexCount(); ++i) {
            VertexT* neighbor = graph->getVertex(i);
            if (graph->hasEdge(vertex, neighbor)) {
                if (state[neighbor->index] == VertexState::Unvisited) {
                    if (!dfs(neighbor, state)) {
                        return false;
                    }
                }
                else if (state[neighbor->index] == VertexState::Visiting) {
                    return false;
                }
            }
        }
        state[vertex->index] = VertexState::Visited;
        sortedVertices.push_back(vertex->index);
        return true;
    }
};
#endif //ADS_RGR_FIRST_TASK_H