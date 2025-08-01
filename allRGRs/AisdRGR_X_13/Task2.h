#ifndef ADS_RGR_SECOND_TASK_H
#define ADS_RGR_SECOND_TASK_H

#include "Graph.h"
#include <queue>

template <class VertexT, class EdgeT>
class SecondTask {
    Graph<VertexT, EdgeT>* graph;
    int radius = INT_MAX;
    vector<VertexT*> radiusPath;
public:
    SecondTask(Graph<VertexT, EdgeT>* g)
    {
        set(g);
    }

    SecondTask(const SecondTask<VertexT, EdgeT>& secondTask)
    {
        Graph<Vertex, Edge>* g = secondTask.graph;
        set(g);
    }

    ~SecondTask()
    {
        radiusPath.clear();
    }

    void set(Graph<VertexT, EdgeT>* g) {
        graph = g;
        restart();
    }

    void restart() {
        int vertexCount = graph->getVertexCount();
        for (int i = 0; i < vertexCount; ++i) {
            VertexT* v = graph->getVertex(i);
            pair<int, vector<VertexT*>> result = dijkstra(v);
            int ecc = result.first;
            vector<VertexT*> path = result.second;
            if (ecc < radius) {
                radius = ecc;
                radiusPath = path;
            }
        }
    }

    void result() {
        if (graph->getVertexCount() == 0) {
            cout << "Граф пуст" << endl;
            return;
        }
        if (radius == INT_MAX) {
            cout << "Радиус равен бесконечности" << endl;
        }
        else {
            cout << "Радиус: " << radius << endl;
            cout << "Путь: ";
            for (VertexT* v : radiusPath) {
                cout << v->index << " ";
            }
            cout << endl;
        }
    }
private:
    pair<int, vector<VertexT*>> dijkstra(VertexT* target) {
        int vertexCount = graph->getVertexCount();
        vector<int> dist(vertexCount, INT_MAX);
        vector<VertexT*> prev(vertexCount, nullptr);
        dist[target->index] = 0;
        priority_queue<pair<int, VertexT*>, vector<pair<int, VertexT*>>, greater<pair<int, VertexT*>>> pq;
        pq.push(make_pair(0, target));
        while (!pq.empty()) {
            pair<int, VertexT*> current = pq.top();
            pq.pop();
            int currentDist = current.first;
            VertexT* u = current.second;
            if (currentDist > dist[u->index]) continue;
            for (int i = 0; i < vertexCount; ++i) {
                VertexT* v = graph->getVertex(i);
                if (graph->hasEdge(v, u)) {
                    EdgeT* edge = graph->getEdge(v, u);
                    int weight;
                    if (edge->hasWeight())
                        weight = edge->getWeight();
                    else continue;
                    if (dist[v->index] > dist[u->index] + weight) {
                        dist[v->index] = dist[u->index] + weight;
                        prev[v->index] = u;
                        pq.push(make_pair(dist[v->index], v));
                    }
                }
            }
        }
        int maxDist = 0;
        VertexT* farthest = nullptr;
        for (int i = 0; i < vertexCount; ++i) {
            if (dist[i] != INT_MAX && dist[i] > maxDist) {
                maxDist = dist[i];
                farthest = graph->getVertex(i);
            }
        }
        vector<VertexT*> path;
        if (farthest) {
            for (VertexT* v = farthest; v != nullptr; v = prev[v->index]) {
                path.push_back(v);
            }
        }
        else maxDist = INT_MAX;
        return make_pair(maxDist, path);
    }
};

#endif //ADS_RGR_SECOND_TASK_H