#ifndef ADS_RGR_SECOND_TASK_H
#define ADS_RGR_SECOND_TASK_H
#include "Graph.h"
#include <queue>
using namespace std;

class QueueNode {
public:
	float PriorityWeight;
	int Parent;
	int QueIndex;
	QueueNode(float w, int p) {
		PriorityWeight = w;
		Parent = p;
	}

};

class MyObj {
public:
	bool operator()(QueueNode* w1, QueueNode* w2) {
		if (w1->PriorityWeight > w2->PriorityWeight)
			return true;
		else
			return false;
	};
};

class MinEdge {
public:
	int Pr;
	int V;
	int Weight;
	MinEdge(int v, int w, int p) {
		Pr = p;
		V = v;
		Weight = w;
	};
};

template <class VertexT, class EdgeT>
class SecondTask {
	priority_queue<QueueNode*, vector<QueueNode*>, MyObj> QueueEdges;
	priority_queue<QueueNode*, vector<QueueNode*>, MyObj> QueueEdges_cpy;
public:
	Graph<VertexT, EdgeT>* PrimGraph;
	queue<MinEdge*, list<MinEdge*>>* MinFrame;
	int PV;
	bool errflag = false;
	SecondTask(Graph<VertexT, EdgeT>* g, int v)
	{
		MinFrame = new queue<MinEdge*, list<MinEdge*>>();
		set(g, v);
	};

	SecondTask(SecondTask <VertexT, EdgeT>& T)
	{
		Graph<VertexT, EdgeT>* g = T.PrimGraph;
		int v = T.PV;
		MinFrame = new queue<MinEdge*, list<MinEdge*>>();
		set(g, v);
	};
	~SecondTask() {
		while (MinFrame->size() != 0)
			MinFrame->pop();
	};
	void set(Graph<VertexT, EdgeT>* g, int v) {
		PrimGraph = g;
		PV = v;
		for (int i = 0; i < PrimGraph->getVertexCount(); i++) {
			Graph<Vertex<string, int>, Edge<Vertex<string, int>, int, int>>::OutputEdgeIterator outputEdgeIterator(*PrimGraph, *PrimGraph->getVertex(i));
			if (!outputEdgeIterator.toBegin()) {
				errflag = true;
				return;
			}
			for (outputEdgeIterator.toBegin(); !outputEdgeIterator.onEnd(); ++outputEdgeIterator) {
				if ((*outputEdgeIterator)->getWeight() == 0) {
					errflag = true;
					return;
				}
			}
		}
		while (MinFrame->size() != 0)
			MinFrame->pop();
		while (QueueEdges.size() != 0)
			QueueEdges.pop();
		while (QueueEdges_cpy.size() != 0)
			QueueEdges_cpy.pop();
		restart();
		Build_Frame();
		return;
	}

	void restart() {
		MST_Prim();
		return;
	}
	void result() {
		if (!errflag) PrimGraph->printGraph();
		else cout << "Граф невзвешенный, либо несвязный" << endl;
		return;
	};
protected:
	void MST_Prim() {
		int comp;
		QueueNode* t = new QueueNode(0, -1);
		t->QueIndex = PV;
		QueueEdges.push(t);

		for (int i = 0; i < PrimGraph->getVertexCount(); i++) {
			if (i != PV) {
				QueueNode* q = new QueueNode(999, -1);
				q->QueIndex = i;
				QueueEdges.push(q);
			}
		}
		while (QueueEdges.size() != 0) {
			QueueNode* v = QueueEdges.top();
			QueueEdges.pop();
			int j;
			for (j = 0; j < PrimGraph->getVertexCount(); j++) {
				if (j == v->QueIndex)
					break;
			}
			Graph<Vertex<string, int>, Edge<Vertex<string, int>, int, int>>::OutputEdgeIterator outputEdgeIterator(*PrimGraph, *PrimGraph->getVertex(j));
			for (outputEdgeIterator.toBegin(); !outputEdgeIterator.onEnd(); ++outputEdgeIterator) {
				if ((*outputEdgeIterator)->getVertex2()->index == v->QueIndex)
					comp = (*outputEdgeIterator)->getVertex1()->index;
				else
					comp = (*outputEdgeIterator)->getVertex2()->index;
				QueueNode* q1 = 0, * q2 = 0;
				int c = -1, w;
				while (QueueEdges.size() != 0) {
					q1 = QueueEdges.top();
					QueueEdges.pop();
					if (q1->QueIndex == comp) {
						c = q1->QueIndex;
						w = q1->PriorityWeight;
						break;
					}
					QueueEdges_cpy.push(q1);
				}
				while (QueueEdges_cpy.size() != 0) {
					q2 = QueueEdges_cpy.top();
					QueueEdges_cpy.pop();
					QueueEdges.push(q2);
				}
				if (c >= 0 && ((*outputEdgeIterator)->getWeight() <= w)) {
					q1->Parent = v->QueIndex;
					q1->PriorityWeight = (*outputEdgeIterator)->getWeight();
				}
				if (c >= 0)
					QueueEdges.push(q1);
			}
			MinEdge* m;
			m = new MinEdge(v->QueIndex, v->PriorityWeight, v->Parent);
			MinFrame->push(m);
		}
	}
	void Build_Frame() {
		queue<MinEdge*, list<MinEdge*>>* MinFrame_cpy;
		MinFrame_cpy = new queue<MinEdge*, list<MinEdge*>>;
		MinEdge* m;
		int index1, index2;
		int v1, v2;
		bool fl = false;
		Graph<Vertex<string, int>, Edge<Vertex<string, int>, int, int>>::EdgeIterator edgeIterator(*PrimGraph);
		for (edgeIterator.toBegin(); !edgeIterator.onEnd(); ++edgeIterator) {
			v1 = (*edgeIterator)->getVertex1()->index;
			v2 = (*edgeIterator)->getVertex2()->index;
			while (MinFrame->size() != 0) {
				m = MinFrame->front();
				MinFrame->pop();
				MinFrame_cpy->push(m);
				index1 = m->V;
				index2 = m->Pr;
				if (v1 == index1 && v2 == index2 || v1 == index2 && v2 == index1) {
					fl = true;
					break;
				}
			}
			if (!fl) {
				try {
					PrimGraph->deleteEdge(v1, v2);
				}
				catch (const runtime_error& error) {
					cout << "Исключение" << endl;
				}
			}
			while (MinFrame_cpy->size() != 0) {
				m = MinFrame_cpy->front();
				MinFrame_cpy->pop();
				MinFrame->push(m);
			}
			fl = false;
		}
	};
};


#endif //ADS_RGR_SECOND_TASK_H