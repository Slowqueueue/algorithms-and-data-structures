#ifndef ADS_RGR_FIRST_TASK_H
#define ADS_RGR_FIRST_TASK_H
#include "Graph.h"
#include <unordered_set>

using namespace std;

template <class Vertex, class Edge>
class FirstTask
{
	Graph<Vertex, Edge>* graph;
    Vertex* vertex;
    vector<vector<Vertex*>> simpleCycles;
public:
	FirstTask(Graph<Vertex, Edge>* g, Vertex* v)
	{
        set(g,v);
	}

	FirstTask(const FirstTask<Vertex, Edge>& firstTask)
	{
		Graph<Vertex, Edge>* g = firstTask.graph;
        Vertex* v = firstTask.vertex;
        set(g,v);
	}

	~FirstTask() {
        simpleCycles.clear();
	}

	void set(Graph<Vertex, Edge>* g, Vertex* v) {
		graph = g;
        vertex = v;
		restart();
	}

	void restart()
	{
		vector<vector<Vertex*>> cycles;
		vector<Vertex*> path;
		unordered_set<int> visited;
		findCyclesFromVertex(vertex, vertex, path, visited, cycles);
        simpleCycles = cycles;
	}

	void result()
	{
        if (simpleCycles.empty())
            cout << "Простые циклы, включающие заданную вершину не найдены" << endl;
        else {
            for (const auto& cycle : simpleCycles) {
                for (Vertex* v : cycle) {
                    cout << v->index << " ";
                }
                cout << endl;
            }
        }
	}
private:
    void findCyclesFromVertex(Vertex* startVertex, Vertex* currentVertex, vector<Vertex*>& path, unordered_set<int>& visited, vector<vector<Vertex*>>& cycles) {
        path.push_back(currentVertex);
        visited.insert(currentVertex->index);
        for (int i = 0; i < graph->getVertexCount(); ++i) {
            Vertex* neighbor = graph->getVertex(i);

            if (graph->hasEdge(currentVertex->index, neighbor->index)) {
                if (neighbor == startVertex) {
                    vector<Vertex*> cycle(path);
                    cycle.push_back(startVertex);
                    cycles.push_back(cycle);
                }
                else if (visited.find(neighbor->index) == visited.end()) {
                    findCyclesFromVertex(startVertex, neighbor, path, visited, cycles);
                }
            }
        }
        path.pop_back();
        visited.erase(currentVertex->index);
    }
};

#endif //ADS_RGR_FIRST_TASK_H