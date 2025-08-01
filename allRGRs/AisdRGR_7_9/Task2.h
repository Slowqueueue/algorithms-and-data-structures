#ifndef ADS_RGR_SECOND_TASK_H
#define ADS_RGR_SECOND_TASK_H
#include "Graph.h"
using namespace std;

template <class VertexT, class EdgeT>
class SecondTask {
    bool isEmpty = false;
    const int INF = 100000000;
	Graph<VertexT, EdgeT>* graph;
    vector<vector<int>> distMatrix;
    int diameter;
    vector<int> peripheryVertices;
public:
	SecondTask(Graph<VertexT, EdgeT>* g) {
		Set(g);
	}

	SecondTask(const SecondTask<VertexT, EdgeT>& SecondTask)
	{
		Graph<VertexT, EdgeT>* g = SecondTask.graph;
		Set(g);
	}

    ~SecondTask() {
        distMatrix.clear();
        peripheryVertices.clear();
    }

	void Set(Graph<VertexT, EdgeT>* g)
	{
		graph = g;
		Restart();
	}

	void Restart()
	{
		if (graph->getVertexCount() == 0) {
            isEmpty = true;
		}
        else {
            distMatrix = floyd(graph);
            pair<vector<int>, int> peripheryResult = findPeriphery(distMatrix);
            peripheryVertices = peripheryResult.first;
            diameter = peripheryResult.second;
        }
	}

	void Result()
	{
        if (isEmpty)
            cout << "Граф пуст" << endl;
        else {
            cout << "Матрица кратчайших расстояний:" << endl;
            for (const auto& row : distMatrix) {
                for (int val : row) {
                    if (val == INF)
                        cout << setw(6) << "INF" << " ";
                    else
                        cout << setw(6) << val << " ";
                }
                cout << endl;
            }
            if (diameter == INF)
                cout << "Диаметр графа равен бесконечности" << endl ;
            else
                cout << "Диаметр графа: " << diameter << endl;
            cout << "Периферийные вершины: ";
            for (int vertexIndex : peripheryVertices) {
                cout << vertexIndex << " ";
            }
            cout << endl;
        }
	}
protected:
    vector<vector<int>> floyd(Graph<VertexT, EdgeT>* graph) {
        int n = graph->getVertexCount();
        vector<vector<int>> dist(n, vector<int>(n, INF));
        for (int i = 0; i < n; ++i) {
            dist[i][i] = 0;
            for (int j = 0; j < n; ++j) {
                if (i != j && graph->hasEdge(i, j)) {
                    EdgeT* edge = graph->getEdge(i, j);
                    dist[i][j] = edge->getWeight();
                }
            }
        }
        for (int k = 0; k < n; ++k) {
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < n; ++j) {
                    if (dist[i][k] != INF && dist[k][j] != INF &&
                        dist[i][k] + dist[k][j] < dist[i][j]) {
                        dist[i][j] = dist[i][k] + dist[k][j];
                    }
                }
            }
        }
        return dist;
    }

    pair<vector<int>, int> findPeriphery(const vector<vector<int>>& distMatrix) {
        int numVertices = graph->getVertexCount();
        vector<int> eccentricities(numVertices);
        for (int j = 0; j < numVertices; ++j) {
            int maxDist = 0;
            for (int i = 0; i < numVertices; ++i) {
                maxDist = max(maxDist, distMatrix[i][j]);
            }
            eccentricities[j] = maxDist;
        }
        int diameter = *std::max_element(eccentricities.begin(), eccentricities.end());
        vector<int> peripheryVertices;
        for (int i = 0; i < numVertices; ++i) {
            if (eccentricities[i] == diameter) {
                peripheryVertices.push_back(i);
            }
        }
        return { peripheryVertices, diameter };
    }
};
#endif //ADS_RGR_SECOND_TASK_H