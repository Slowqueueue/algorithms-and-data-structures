#ifndef ADS_RGR_FIRST_TASK_H
#define ADS_RGR_FIRST_TASK_H
#define WHITE 0
#define GREY 1
#define BLACK 2
#include "Graph.h"
#include <queue>
using namespace std;

template <class VertexT, class EdgeT>
class FirstTask {
	vector<int> *color, *d, *p, *f;
	queue<int, list<int>>* Sons;
	int* low;
	int time, t;
public:
	Graph<VertexT, EdgeT>* G;
	int BV;
	bool solved = false;

	FirstTask(Graph<VertexT, EdgeT>* g) {
		G = g;
		set(G);
	};

	FirstTask(const FirstTask<VertexT, EdgeT>& T) {
		G = T.G;
	}

	~FirstTask() {
	};

	void set(Graph<VertexT, EdgeT>* g) {
		G = g;
		low = new int[G->getVertexCount()];
		color = new vector<int>;
		color->resize(G->getVertexCount(), WHITE);
		p = new vector<int>;
		p->resize(G->getVertexCount(), -1);
		d = new vector<int>;
		d->resize(G->getVertexCount(), 0);
		f = new vector<int>;
		f->resize(G->getVertexCount(), 0);
		Sons = new queue<int, list<int>>;
		BV = 0;
		restart();
		return;
	}

	void restart() {
		if (solved) return;
		DFS(G);
		t = (*f)[0];
		for (int i = 0; i < G->getVertexCount(); i++)
			if ((*f)[i] < t)
				t = (*f)[i];
		for (int i = 0; i < G->getVertexCount(); i++) {
			FindLow();
			t++;
		}
		for (int i = 0; i < G->getVertexCount(); i++)
			FindBadVertex(i);
		solved = true;
		return;
	};

	int result() {
		cout << endl << "Количество точек сочленения: " << BV << endl << endl;
		G->printGraph();
		return BV;
	}
protected:
	int DFS(Graph<VertexT, EdgeT>* G) {
		time = 0;
		int trees = 0;
		for (int i = 0; i < G->getVertexCount(); i++)
		{
			if ((*color)[i] == WHITE)
				DFS_Visit(G->getVertex(i), i);
		}
		return trees;
	}

	void DFS_Visit(VertexT* u, int index)
	{
		(*color)[index] = GREY;
		(*d)[index] = time;
		++time;
		for (int i = 0; i < G->getVertexCount(); i++)
			if (G->hasEdge(index, i))
				if ((*color)[i] == WHITE) {
					(*p)[i] = index;
					DFS_Visit(G->getVertex(i), i);
				}
		(*color)[index] = BLACK;
		(*f)[index] = time;
		++time;
		return;
	}

	void FindLow() {
		int index1 = 0;
		int i;
		while (t <= time) {
			for (index1 = 0; index1 < G->getVertexCount(); index1++) {
				if ((*f)[index1] == t)
					break;
			}
			if (index1 < G->getVertexCount())
				break;
			t++;
		}
		int index2 = 0;
		low[index1] = (*d)[index1];

		Graph<Vertex<string, int>, Edge<Vertex<string, int>, int, int>>::OutputEdgeIterator outputEdgeIterator(*G, *G->getVertex(index1));
		for (outputEdgeIterator.toBegin(); !outputEdgeIterator.onEnd(); ++outputEdgeIterator) {
			if (index1 == (*outputEdgeIterator)->getVertex1()->index)
				index2 = (*outputEdgeIterator)->getVertex2()->index;
			else if (index1 == (*outputEdgeIterator)->getVertex2()->index)
				index2 = (*outputEdgeIterator)->getVertex1()->index;
			if (index2 == (*p)[index1])
				continue;
			if (index1 == (*p)[index2]) {
				low[index1] = min(low[index2], low[index1]);
				continue;
			}
			low[index1] = min(low[index1], (*d)[index2]);
		}
		return;
	}

	void FindBadVertex(int index1) {
		int point;
		int v1, v2;
		if ((*p)[index1] == -1) {
			int kids = 0;
			for (int i = 0; i < G->getVertexCount(); i++)
				if (index1 == (*p)[i])
					kids++;
			if (kids > 1) {
				HelpRoot(index1);
				BV++;
			}
			return;
		}

		Graph<Vertex<string, int>, Edge<Vertex<string, int>, int, int>>::OutputEdgeIterator outputEdgeIterator(*G, *G->getVertex(index1));
		int index2 = 0;
		for (outputEdgeIterator.toBegin(); !outputEdgeIterator.onEnd(); ++outputEdgeIterator) {
			if (index1 == (*outputEdgeIterator)->getVertex1()->index) {
				index2 = (*outputEdgeIterator)->getVertex2()->index;
			}
			else if (index1 == (*outputEdgeIterator)->getVertex2()->index) {
				index2 = (*outputEdgeIterator)->getVertex1()->index;
			}
			if (index1 == (*p)[index2] && low[index2] >= (*d)[index1]) {
				BV++;
				for (v1 = 0; v1 < G->getVertexCount(); v1++)
					if (v1 == (*p)[index1])
						break;
				v2 = index2;
				try {
					G->insertEdge(v1, v2);
				}
				catch (const runtime_error& error) {
					BV--;
				}
			}
		}
		return;
	}

	void HelpRoot(int index1) {
		Graph<Vertex<string, int>, Edge<Vertex<string, int>, int, int>>::OutputEdgeIterator outputEdgeIterator(*G, *G->getVertex(index1));
		int index2;
		for (outputEdgeIterator.toBegin(); !outputEdgeIterator.onEnd(); ++outputEdgeIterator) {
			if ((*outputEdgeIterator)->getVertex1()->index == index1)
				index2 = (*outputEdgeIterator)->getVertex2()->index;
			else
				index2 = (*outputEdgeIterator)->getVertex1()->index;
			Sons->push(index2);
		}
		int son1, son2;
		son1 = Sons->front();
		Sons->pop();
		if (Sons->size() == 0) {
			BV--;
			return;
		}
		son2 = Sons->front();
		try {
			G->insertEdge(son1, son2);
		}
		catch (const runtime_error& error) {
			BV--;
		}
		return;
	}
};

#endif //ADS_RGR_FIRST_TASK_H