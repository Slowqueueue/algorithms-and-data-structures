#ifndef ADS_RGR_SECOND_TASK_H
#define ADS_RGR_SECOND_TASK_H
#include "Graph.h"
#include <queue>
#include <unordered_map>
using namespace std;

struct PathInfo {
    vector<int> vertices;
    int distance;
};

template <class VertexT, class EdgeT>
class SecondTask {
	Graph<VertexT, EdgeT>* graph;
    int vertexIndex;
    unordered_map<int, vector<PathInfo>> allPaths;
public:
	SecondTask(Graph<VertexT, EdgeT>* g, int v) {
		Set(g, v);
	}

	SecondTask(const SecondTask<VertexT, EdgeT>& SecondTask)
	{
		Graph<VertexT, EdgeT>* g = SecondTask.graph;
        int v = SecondTask.vertexIndex;
		Set(g, v);
	}

    ~SecondTask() {
        allPaths.clear();
    }

	void Set(Graph<VertexT, EdgeT>* g, int v)
	{
		graph = g;
        vertexIndex = v;
		Restart();
	}

	void Restart()
	{
        auto result = dijkstraReverse(vertexIndex);
        for (int v = 0; v < graph->getVertexCount(); ++v) {
            if (v == vertexIndex || result.distances[v] == INT_MAX) continue;
            vector<int> currentPath;
            vector<PathInfo> paths;
            buildPaths(v, vertexIndex, result.prev, result.distances, currentPath, paths);
            allPaths[v] = paths;
        }
	}

	void Result()
	{
        if (allPaths.empty()) {
            cout << "В заданную вершину путей нет" << endl;
            return;
        }
        for (const auto& entry : allPaths) {
            int start = entry.first;
            cout << "\nКратчайшие пути из вершины " << start << " в вершину " << vertexIndex << ":\n";
            for (const auto& pathInfo : entry.second) {
                cout << "Расстояние: " << pathInfo.distance << ", Путь: ";
                for (int v : pathInfo.vertices) {
                    cout << v << " ";
                }
                cout << endl;
            }
        }
	}
protected:
    struct DijkstraResult {
        vector<int> distances;
        unordered_map<int, vector<int>> prev;
    };

    unordered_map<int, vector<pair<int, int>>> buildReverseGraph() {
        unordered_map<int, vector<pair<int, int>>> reverseGraph;
        int vertexCount = graph->getVertexCount();
        for (int i = 0; i < vertexCount; ++i) {
            VertexT* v = graph->getVertex(i);
            for (int j = 0; j < vertexCount; ++j) {
                VertexT* u = graph->getVertex(j);
                if (graph->hasEdge(u->index, v->index)) {
                    EdgeT* edge = graph->getEdge(u->index, v->index);
                    if (edge && edge->hasWeight()) {
                        reverseGraph[v->index].emplace_back(u->index, edge->getWeight());
                    }
                }
            }
        }
        return reverseGraph;
    }

    DijkstraResult dijkstraReverse(int vertexIndex) {
        auto reverseGraph = buildReverseGraph();
        int vertexCount = graph->getVertexCount();
        DijkstraResult result;
        result.distances.resize(vertexCount, INT_MAX);
        result.distances[vertexIndex] = 0;
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        pq.emplace(0, vertexIndex);
        while (!pq.empty()) {
            auto current = pq.top();
            int currentDist = current.first;
            int u = current.second;
            pq.pop();
            if (currentDist > result.distances[u]) {
                continue;
            }
            for (const auto& edge : reverseGraph[u]) {
                int v = edge.first;
                int weight = edge.second;
                int newDist = currentDist + weight;
                if (newDist < result.distances[v]) {
                    result.distances[v] = newDist;
                    result.prev[v] = { u };
                    pq.emplace(newDist, v);
                }
                else if (newDist == result.distances[v]) {
                    result.prev[v].push_back(u);
                }
            }
        }
        return result;
    }

    void buildPaths(int u, int target, const unordered_map<int, vector<int>>& prev, const vector<int>& distances, vector<int>& currentPath, vector<PathInfo>& resultPaths) {
        currentPath.push_back(u);
        if (u == target) {
            PathInfo path;
            path.vertices = currentPath;
            path.distance = distances[currentPath[0]];
            resultPaths.push_back(path);
        }
        else {
            for (int v : prev.at(u)) {
                buildPaths(v, target, prev, distances, currentPath, resultPaths);
            }
        }
        currentPath.pop_back();
    }
};
#endif //ADS_RGR_SECOND_TASK_H