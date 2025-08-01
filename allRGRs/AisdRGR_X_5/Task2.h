#ifndef ADS_RGR_SECOND_TASK_H
#define ADS_RGR_SECOND_TASK_H
#include "Graph.h"
#include <queue>
using namespace std;

class Tree
{
	struct Node
	{
		int key;
		Node* left;
		Node* right;
		Node(int k)
		{
			key = k;
			left = NULL;
			right = NULL;
		}
	};
	Node* root;
	int size;
public:
	Tree()
	{
		root = NULL;
		size = 0;
	}

	~Tree()
	{
		Bypass_Destructor(root);
		root = NULL;
	}

	int GetSize()
	{
		return size;
	}

	bool Insert(int key)
	{
		Node* newNode = new Node(key);
		if (root == NULL)
		{
			root = newNode;
			size++;
			return true;
		}
		Node* interNode = root;
		while (true) {
			if (key > interNode->key) {
				if (interNode->right == NULL) {
					interNode->right = newNode;
					size++;
					return true;
				}
				else
					interNode = interNode->right;
			}
			else if (key < interNode->key) {
				if (interNode->left == NULL) {
					interNode->left = newNode;
					size++;
					return true;
				}
				else
					interNode = interNode->left;
			}
			else
			{
				delete newNode;
				return false;
			}
		}
	}

	bool IsExist(int key)
	{
		Node* interNode = root;
		while (interNode != NULL) {
			if (key > interNode->key)
				interNode = interNode->right;
			else if (key < interNode->key)
				interNode = interNode->left;
			else
				return true;
		}
		return false;
	}

	void BypassAdd(Node* t)
	{
		if (t == NULL) return;
		Insert(t->key);
		BypassAdd(t->left);
		BypassAdd(t->right);
	}

	void AddTree(Tree* treeToAdd)
	{
		BypassAdd(treeToAdd->root);
	}
protected:
	void Bypass_Destructor(Node* t)
	{
		if (t == NULL) return;
		Bypass_Destructor(t->left);
		Bypass_Destructor(t->right);
		delete t;
	}
};

template <class VertexT, class EdgeT>
class SecondTask {
	Graph<VertexT, EdgeT>* graph;
	int d;
	vector<vector<bool>> result;
	vector<Tree*> areaArray;
public:
	SecondTask(Graph<VertexT, EdgeT>* g, int _d) {
		Set(g, _d);
	}

	SecondTask(const SecondTask<VertexT, EdgeT>& SecondTask)
	{
		Graph<VertexT, EdgeT>* g = SecondTask.graph;
		int _d = SecondTask.d;
		Set(g, _d);
	}

	void Set(Graph<VertexT, EdgeT>* g, int _d)
	{
		graph = g;
		d = _d;
		Restart();
	}

	void Restart()
	{
		result.clear();
		vector<EdgeT*> edgeArray;
		for (int i = 0; i < graph->getVertexCount(); i++) {
			for (int j = i; j < graph->getVertexCount(); j++) {
				if (graph->hasEdge(i, j)) {
					EdgeT* edge = graph->getEdge(i, j);
					if (edge->getWeight() > d) {
						if (edgeArray.size() == 0)
							edgeArray.push_back(edge);
						else {
							int pos;
							for (pos = 0; pos < edgeArray.size(); pos++)
								if (edge->getWeight() < edgeArray[pos]->getWeight())
									break;
							edgeArray.insert(edgeArray.begin() + pos, edge);
						}
					}
				}
			}
		}
		for (int i = 0; i < graph->getVertexCount(); i++) {
			Tree* area = new Tree();
			area->Insert(i);
			areaArray.push_back(area);
		}
		for (int i = 0; i < edgeArray.size();) {
			EdgeT* edge = edgeArray[i];
			int v1 = edge->getVertex1()->index;
			int v2 = edge->getVertex2()->index;
			int area1 = GetArea(v1);
			int area2 = GetArea(v2);
			if (area1 == area2)
				edgeArray.erase(edgeArray.begin() + i);
			else {
				if (areaArray[area1]->GetSize() > areaArray[area2]->GetSize()) {
					areaArray[area1]->AddTree(areaArray[area2]);
					delete areaArray[area2];
					areaArray.erase(areaArray.begin() + area2);
				}
				else {
					areaArray[area2]->AddTree(areaArray[area1]);
					delete areaArray[area1];
					areaArray.erase(areaArray.begin() + area1);
				}
				i++;
			}
		}
		while (areaArray.size() != 0) {
			delete areaArray[0];
			areaArray.erase(areaArray.begin());
		}
		for (int i = 0; i < graph->getVertexCount(); ++i) {
			vector<bool> newLine;
			newLine.assign(graph->getVertexCount(), false);
			result.insert(result.begin() + i, newLine);
		}
		for (int i = 0; i < edgeArray.size(); i++) {
			EdgeT* edge = edgeArray[i];
			int v1 = edge->getVertex1()->index;
			int v2 = edge->getVertex2()->index;
			result[v1][v2] = true;
			result[v2][v1] = true;
		}
	}

	void Result()
	{
		cout << setw(6) << "";
		for (int i = 0; i < graph->getVertexCount(); i++) {
			cout << setw(6) << "(i" << i;
			if (graph->getVertex(i)->hasName())
				cout << "," << graph->getVertex(i)->getName();
			cout << ")";
		}
		cout << "\n\n\n";
		for (int i = 0; i < graph->getVertexCount(); i++) {
			cout << setw(6) << "(i" << i;
			if (graph->getVertex(i)->hasName())
				cout << "," << graph->getVertex(i)->getName();
			cout << ")";
			for (int j = 0; j < graph->getVertexCount(); j++) {
				if (result[i][j]) {
					if (graph->getEdge(i, j)->hasWeight())
						cout << setw(8) << graph->getEdge(i, j)->getWeight();
					else
						cout << setw(8) << "+ ";
				}
				else
					cout << setw(8) << "- ";
			}
			cout << "\n\n\n";
		}
	}
protected:
	int GetArea(int vertexIndex) {
		for (int i = 0; i < areaArray.size(); i++)
			if (areaArray[i]->IsExist(vertexIndex))
				return i;
		return -1;
	}
};
#endif //ADS_RGR_SECOND_TASK_H