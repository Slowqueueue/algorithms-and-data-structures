#ifndef ADS_RGR_SECOND_TASK_H
#define ADS_RGR_SECOND_TASK_H
#include "Graph.h"
using namespace std;

template <class VertexT, class EdgeT>
class SecondTask {
    const int INF = 100000000;
	Graph<VertexT, EdgeT>* graph;
	int result;
    vector<vector<int>> distMatrix;
    vector<int> maxDistances;
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
        maxDistances.clear();
    }

	void Set(Graph<VertexT, EdgeT>* g)
	{
		graph = g;
		Restart();
	}

	void Restart()
	{
		if (graph->getVertexCount() == 0) {
			result = -1;
		}
        else {
            distMatrix = Floyd(graph);
            maxDistances = FindMaxDistances(distMatrix);
            result = FindCenterIndex(maxDistances);
        }
	}

	void Result()
	{
        if (result == -1)
            cout << "Граф несвязный, либо пустой" << endl;
        else {
            vector<int> centers;
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
            cout << "Максимальные расстояния до остальных вершин: ";
            for (int i = 0; i < maxDistances.size(); ++i) {
                if (maxDistances[i] == INF)
                    cout << "INF ";
                else
                    cout << maxDistances[i] << " ";
                if (maxDistances[i] == *min_element(maxDistances.begin(), maxDistances.end()))
                    centers.push_back(i);
            }
            if (centers.size() > 1) {
                cout << endl << "Центры графа: ";
                for (int center : centers) {
                    cout << center << " ";
                }
            }
            else
                cout << endl << "Центр графа: " << result << endl;
        }
	}
protected:
    vector<vector<int>> Floyd(Graph<VertexT, EdgeT>* graph) {
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

    vector<int> FindMaxDistances(const vector<vector<int>>& distMatrix) {
        int n = distMatrix.size();
        vector<int> maxDistances(n, 0);
        for (int j = 0; j < n; ++j) {
            int max_dist = 0;
            for (int i = 0; i < n; ++i) {
                if (i != j) {
                    max_dist = max(max_dist, distMatrix[i][j]);
                }
            }
            maxDistances[j] = max_dist;
        }
        return maxDistances;
    }

    int FindCenterIndex(const vector<int>& maxDistances) {
        auto min_element_it = min_element(maxDistances.begin(), maxDistances.end());
        if (min_element_it == maxDistances.end() || *min_element_it == INF) {
            return -1;
        }
        return distance(maxDistances.begin(), min_element_it);
    }
};
#endif //ADS_RGR_SECOND_TASK_H