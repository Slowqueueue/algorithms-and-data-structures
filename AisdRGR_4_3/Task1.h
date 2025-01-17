#ifndef ADS_RGR_FIRST_TASK_H
#define ADS_RGR_FIRST_TASK_H
#include "Graph.h"
#include <queue>
using namespace std;
template <class Vertex, class Edge>
class FirstTask
{
private:
	Graph<Vertex, Edge>* graph;   //Обрабатываемый граф
	bool** matrix;                  //Матрица смежности
	int result_d;

	int maxDistanceVertex(int vertexIndex)
	{
		for (int i = 0; i < graph->getVertexCount(); i++)
		{
			Vertex* vertex = graph->getVertex(i);
			vertex->color = 0;
			vertex->distance = INT_MAX;
		}

		Vertex* vertexPointer = graph->getVertex(vertexIndex);
		vertexPointer->color = 1;
		vertexPointer->distance = 0;

		//создаем очередь из указателей на вершины
		queue<int> vertexIndexQueue;
		vertexIndexQueue.push(vertexIndex);

		//находим расстояния до всех вершин
		while (!vertexIndexQueue.empty())
		{
			int vertexFirstIndex = vertexIndexQueue.front();
			vertexIndexQueue.pop();
			Vertex* vertexFirstPointer = graph->getVertex(vertexFirstIndex);
			for (int j = 0; j < graph->getVertexCount(); j++)
			{
				Vertex* vertexSecondPointer = graph->getVertex(j);
				if (matrix[vertexFirstIndex][j] == true && vertexSecondPointer->color == 0)
				{
					vertexSecondPointer->color = 1;
					vertexSecondPointer->distance = vertexFirstPointer->distance + 1;
					vertexIndexQueue.push(j);
				}
			}
			vertexFirstPointer->color = 2;

		}

		//ищем максимальное из них
		int maxDistance = 0;
		for (int i = 0; i < graph->getVertexCount(); i++)
		{
			Vertex* vertex = graph->getVertex(i);
			if (vertex->distance > maxDistance)
				maxDistance = vertex->distance;
		}

		return maxDistance;

	}

public:
	//Конструкторы-деструкторы
	FirstTask(Graph<Vertex, Edge>* g) : graph(g)
	{
		restart();
	}
	FirstTask(const FirstTask<Vertex, Edge>& firstTask)
	{
		graph = firstTask.graph;
		restart();
	}
	~FirstTask() {
		for (int i = 0; i < graph->getVertexCount(); i++) delete[] matrix[i];
		delete[] matrix;
	}

	void set(Graph<Vertex, Edge>& g) {
		graph = g;
		restart();
	}

	void restart()
	{
		//Строим матрицу смежности
		matrix = new bool* [graph->getVertexCount()];

		for (int i = 0; i < graph->getVertexCount(); ++i)
		{
			matrix[i] = new bool[graph->getVertexCount()];
			for (int j = 0; j < graph->getVertexCount(); ++j)
			{
				if (graph->hasEdge(i, j))
					matrix[i][j] = true;
				else
					matrix[i][j] = false;
			}
		}

		result_d = 0;
		for (int i = 0; i < graph->getVertexCount(); i++)
		{
			int interMax = maxDistanceVertex(i);
			if (interMax > result_d)
				result_d = interMax;
		}
	}

	int result()
	{
		if (result_d == INT_MAX) {
			cout << "Граф несвязный\n";
			return 0;
		}
		else {
			cout << endl << "Диаметр графа: " << result_d << endl;
			return result_d;
		}
	}
};
#endif //ADS_RGR_FIRST_TASK_H