#ifndef ADS_RGR_FIRST_TASK_H
#define ADS_RGR_FIRST_TASK_H
#include "Graph.h"
#include <vector>
#include <queue>
using namespace std;

enum Color {
    NONE,
    BLUE,
    RED
};

template <class VertexT, class EdgeT>
class FirstTask {
    Graph<VertexT, EdgeT>* graph;
    bool isInitiallyBipartite = true;
    vector<Color> colors;
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
        colors.clear();
    }

    void Set(Graph<VertexT, EdgeT>* g)
    {
        graph = g;
        Restart();
    }

    void Restart()
    {
        colors.clear();
        bool leaveLoop;
        while (!isBipartiteAndColor()) {
            isInitiallyBipartite = false;
            leaveLoop = false;
            for (int i = 0; i < graph->getVertexCount(); ++i) {
                for (int j = 0; j < graph->getVertexCount(); ++j) {
                    if (graph->hasEdge(i, j)) {
                        if (colors[i] == colors[j] && colors[i] != 0 && colors[j] != 0) {
                            graph->deleteEdge(i, j);
                            leaveLoop = true;
                            break;
                        }
                    }
                }
                if (leaveLoop) break;
            }
            colors.clear();
        }
    }

    void Result()
    {
        if (graph->getVertexCount() == 0) {
            cout << "Граф пустой" << endl;
            return;
        }
        if (!isInitiallyBipartite)
            cout << "Исходный граф не являлся двудольным. Было выполнено формирование" << endl;
        else
            cout << "Исходный граф является двудольным" << endl;
        for (int i = 0; i < graph->getVertexCount(); ++i) {
            VertexT* v = graph->getVertex(i);
            cout << "Вершина " << i << " окрашена в " << (colors[i] == 1 ? "СИНИЙ" : "КРАСНЫЙ") << " цвет" << endl;
        }
        cout << "\n\n\n";
        if (graph->isDense()) graph->printGraph();
        else  graph->printGraph(false);
    }
protected:
    bool isBipartiteAndColor() {
        int vertexCount = graph->getVertexCount();
        if (vertexCount == 0) return true;
        colors.resize(vertexCount, NONE);
        queue<VertexT*> q;
        for (int i = 0; i < vertexCount; ++i) {
            VertexT* start = graph->getVertex(i);
            int startIdx = start->index;
            if (colors[startIdx] != NONE) continue;
            colors[startIdx] = BLUE;
            q.push(start);
            while (!q.empty()) {
                VertexT* current = q.front();
                q.pop();
                int currentIdx = current->index;
                for (int j = 0; j < vertexCount; ++j) {
                    VertexT* neighbor = graph->getVertex(j);
                    if (neighbor == current) continue;

                    if (graph->hasEdge(current, neighbor)) {
                        int neighborIdx = neighbor->index;
                        if (colors[neighborIdx] == NONE) {
                            colors[neighborIdx] = (colors[currentIdx] == BLUE) ? RED : BLUE;
                            q.push(neighbor);
                        }
                        else if (colors[neighborIdx] == colors[currentIdx]) {
                            return false;
                        }
                    }
                }
            }
        }
        return true;
    }
};
#endif //ADS_RGR_FIRST_TASK_H