#ifndef ADS_RGR_FIRST_TASK_H
#define ADS_RGR_FIRST_TASK_H
#include "Graph.h"
#include <vector>
#include <queue>
using namespace std;

template <class VertexT, class EdgeT>
class FirstTask {
	Graph<VertexT, EdgeT>* graph;
	vector<VertexT*> result;
public:
	FirstTask(Graph<VertexT, EdgeT>* g) {
		Set(g);
	}

	FirstTask(const FirstTask<VertexT, EdgeT>& FirstTask)
	{
		Graph<VertexT, EdgeT>* g = FirstTask.graph;
		Set(g);
	}

	~FirstTask()
	{
		result.clear();
	}

	void Set(Graph<VertexT, EdgeT>* g)
	{
		graph = g;
		Restart();
	}

	void Restart()
	{
		result.clear();
		int n = graph->getVertexCount();
		vector<int> inDegree(n, 0);
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < n; ++j) {
				if (graph->hasEdge(j, i)) {
					inDegree[i]++;
				}
			}
		}
		queue<int> sources;
		for (int i = 0; i < n; ++i) {
			if (inDegree[i] == 0) {
				sources.push(i);
			}
		}
		while (!sources.empty()) {
			int i = sources.front();
			sources.pop();
			VertexT* v = graph->getVertex(i);
			result.push_back(v);
			for (int j = 0; j < n; ++j) {
				if (graph->hasEdge(i, j)) {
					inDegree[j]--;
					if (inDegree[j] == 0) {
						sources.push(j);
					}
				}
			}
		}
		for (int i = 0; i < n; ++i) {
			if (inDegree[i] != 0) {
				result.clear();
				break;
			}
		}
	}

	void Result()
	{
		if (graph->getVertexCount() == 0) {
			cout << "Граф пуст" << endl;
			return;
		}
		if (result.empty()) {
			cout << "Граф содержит цикл" << endl;
		}
		else {
			for (VertexT* v : result) {
				cout << v->index << " ";
			}
			cout << endl;
		}
	}
};
#endif //ADS_RGR_FIRST_TASK_H