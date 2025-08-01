#ifndef ADS_RGR_FIRST_TASK_H
#define ADS_RGR_FIRST_TASK_H
#include "Graph.h"
#include <unordered_set>
#include <unordered_map>
#include <stack>
using namespace std;

template <class VertexT, class EdgeT>
class FirstTask {
    Graph<VertexT, EdgeT>* graph;
    bool isConnected = true;
    vector<pair<int, int>> addedEdges;
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
        addedEdges.clear();
    }

    void Set(Graph<VertexT, EdgeT>* g)
    {
        graph = g;
        Restart();
    }

    void Restart()
    {
        auto components = findConnectedComponents();
        if (components.size() <= 1) {
            if (!components.empty()) {
                eliminateBridgesInComponent(components[0]);
            }
            return;
        }
        for (size_t i = 1; i < components.size(); ++i) {
            int v1 = *(components[i].begin());
            int v2 = *(components[(i + 1) % components.size()].begin());
            if (!graph->hasEdge(v1, v2)) {
                graph->insertEdge(v1, v2);
                isConnected = false;
                addedEdges.push_back(make_pair(v1, v2));
            }
        }
        components = findConnectedComponents();
        if (!components.empty()) {
            eliminateBridgesInComponent(components[0]);
        }
    }

    void Result()
    {
        if (graph->getVertexCount() == 0) {
            cout << "Граф пуст" << endl;
            return;
        }
        if (isConnected)
            cout << "Исходный граф является реберно-связным" << endl;
        else {
            cout << "Исходный граф не являлся реберно-связным. Было выполнено формирование." << endl;
            cout << "Были добавлены ребра: " << endl;
            for (const auto& edge : addedEdges) {
                cout << edge.first << " " << edge.second << endl;
            }
            cout << "Добавлено ребер: " << addedEdges.size() << endl;
        }
        cout << endl;
        graph->printGraph(graph->isDense());
    }
protected:
    vector<unordered_set<int>> findConnectedComponents() {
        vector<unordered_set<int>> components;
        int vertexCount = graph->getVertexCount();
        unordered_set<int> visited;
        for (int i = 0; i < vertexCount; ++i) {
            if (!visited.count(i)) {
                unordered_set<int> component;
                stack<int> stack;
                stack.push(i);
                visited.insert(i);
                component.insert(i);
                while (!stack.empty()) {
                    int currentIdx = stack.top();
                    stack.pop();
                    VertexT* currentVertex = graph->getVertex(currentIdx);
                    for (int neighborIdx = 0; neighborIdx < vertexCount; ++neighborIdx) {
                        if (neighborIdx == currentIdx) continue;
                        if (graph->hasEdge(currentIdx, neighborIdx) && !visited.count(neighborIdx)) {
                            visited.insert(neighborIdx);
                            component.insert(neighborIdx);
                            stack.push(neighborIdx);
                        }
                    }
                }
                components.push_back(component);
            }
        }
        return components;
    }

    void eliminateBridgesInComponent(const unordered_set<int>& component) {
        auto bridges = findBridgesInComponent(component);
        for (const auto& bridge : bridges) {
            int u = bridge.first;
            int v = bridge.second;
            unordered_set<int> neighbors_u;
            for (int w : component) {
                if (w != v && graph->hasEdge(u, w)) {
                    neighbors_u.insert(w);
                }
            }
            unordered_set<int> neighbors_v;
            for (int w : component) {
                if (w != u && graph->hasEdge(v, w)) {
                    neighbors_v.insert(w);
                }
            }
            bool edge_added = false;
            for (int nu : neighbors_u) {
                for (int nv : neighbors_v) {
                    if (!graph->hasEdge(nu, nv)) {
                        graph->insertEdge(nu, nv);
                        isConnected = false;
                        addedEdges.push_back(make_pair(nu, nv));
                        edge_added = true;
                        break;
                    }
                }
                if (edge_added) break;
            }
            if (!edge_added) {
                unordered_set<int> subgraph1, subgraph2;
                findSubgraphsAfterBridgeRemoval(u, v, component, subgraph1, subgraph2);
                if (!subgraph1.empty() && !subgraph2.empty()) {
                    int w1 = *subgraph1.begin();
                    int w2 = *subgraph2.begin();
                    if (!graph->hasEdge(w1, w2)) {
                        graph->insertEdge(w1, w2);
                        isConnected = false;
                        addedEdges.push_back(make_pair(w1, w2));
                    }
                }
            }
        }
    }

    void findSubgraphsAfterBridgeRemoval(int u, int v, const unordered_set<int>& component,
        unordered_set<int>& subgraph1, unordered_set<int>& subgraph2) {
        unordered_set<int> visited;
        stack<int> stack;
        stack.push(u);
        visited.insert(u);
        while (!stack.empty()) {
            int current = stack.top();
            stack.pop();
            subgraph1.insert(current);
            for (int neighbor : component) {
                if ((current == u && neighbor == v) || (current == v && neighbor == u)) continue;
                if (graph->hasEdge(current, neighbor) && !visited.count(neighbor)) {
                    visited.insert(neighbor);
                    stack.push(neighbor);
                }
            }
        }
        for (int vertex : component) {
            if (!visited.count(vertex)) {
                subgraph2.insert(vertex);
            }
        }
    }

    vector<pair<int, int>> findBridgesInComponent(const unordered_set<int>& component) {
        vector<pair<int, int>> bridges;
        unordered_map<int, int> disc, low;
        unordered_map<int, int> parent;
        int time = 0;
        for (int u : component) {
            disc[u] = low[u] = -1;
            parent[u] = -1;
        }
        for (int u : component) {
            if (disc[u] == -1) {
                findBridges(u, disc, low, parent, bridges, time, component);
            }
        }
        return bridges;
    }

    void findBridges(int u, unordered_map<int, int>& disc, unordered_map<int, int>& low, unordered_map<int, int>& parent, vector<pair<int, int>>& bridges, int& time, const unordered_set<int>& component) {
        disc[u] = low[u] = ++time;
        for (int v : component) {
            if (v == u) continue;
            if (graph->hasEdge(u, v)) {
                if (disc[v] == -1) {
                    parent[v] = u;
                    findBridges(v, disc, low, parent, bridges, time, component);
                    low[u] = min(low[u], low[v]);
                    if (low[v] > disc[u]) {
                        bridges.push_back(make_pair(u, v));
                    }
                }
                else if (v != parent[u]) {
                    low[u] = min(low[u], disc[v]);
                }
            }
        }
    }
};
#endif //ADS_RGR_FIRST_TASK_H