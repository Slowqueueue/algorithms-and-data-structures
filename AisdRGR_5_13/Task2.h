#ifndef ADS_RGR_SECOND_TASK_H
#define ADS_RGR_SECOND_TASK_H
#include "Graph.h"
#define MAX 200
#define MAX_INT 2147483647
#define MIN_INT -2147483647;
using namespace std;
template<class Vertex, class Edge>
class SecondTask {
    struct Vertex_Simply
    {
        int vertex;
        int parrent;
        int w;
        bool state;
        Vertex_Simply(int vertex, int parrent, int w)
        {
            this->vertex = vertex;
            this->parrent = parrent;
            this->state = true;
            this->w = w;
        }
        Vertex_Simply(int vertex)
        {
            this->vertex = vertex;
            this->w = MAX_INT;
            this->state = false;
        }
    };
    class stack
    {
        struct Node
        {
            Vertex_Simply* v;
            Node* next;
            Node()
            {
                v = NULL;
                next = NULL;
            }
            Node(Vertex_Simply* v, Node* next)
            {
                this->v = v;
                this->next = next;
            }
        };
        Node* top;
    public:
        stack()
        {
            top = NULL;
        }
        void push(Vertex_Simply* t)
        {
            Node* current = new Node(t, top);
            top = current;
        }
        Vertex_Simply* pop()
        {
            if (top != NULL)
            {
                Vertex_Simply* v = top->v;
                Node* current = top;
                top = top->next;
                delete current;
                return v;
            }
            else
            {
                return NULL;
            }
        }
        bool state()
        {
            if (top != NULL)
                return true;
            else
                return false;
        }
    };
    Graph<Vertex, Edge>* graph;
    int way[MAX];
    int R;
    int end;
    bool res;
    bool Route(int v1);
public:
    explicit SecondTask(Graph<Vertex, Edge>* g);
    SecondTask(SecondTask<Vertex, Edge>& secondTask);
    ~SecondTask();
    void set(Graph<Vertex, Edge>* g);
    void restart();
    void result();
};
template<class Vertex, class Edge>
bool SecondTask<Vertex, Edge>::Route(int v1) {
    Vertex_Simply* v[MAX];
    for (int i = 0; i < graph->getVertexCount(); i++)
        v[i] = new Vertex_Simply(i);
    int curr_v = v1;
    int son_v = 0;
    int w;
    stack st;
    v[curr_v]->w = 0;
    v[curr_v]->parrent = -1;
    st.push(v[curr_v]);
    while (st.state())
    {
        v[graph->getVertexCount()] = st.pop();
        v[graph->getVertexCount()]->state = true;
        curr_v = v[graph->getVertexCount()]->vertex;
        Vertex* vertex = graph->getVertex(curr_v);
        typename Graph<Vertex, Edge>::OutputEdgeIterator outputEdgeIterator(*graph, *vertex);
        outputEdgeIterator.toBegin();
        Edge* Ed;
        try {
        Ed = *outputEdgeIterator;
        }
        catch (const runtime_error& error) {
            continue;
        }
        while (Ed != NULL)
        {
            if (Ed->hasWeight()) w = Ed->getWeight();
            else {
                cout << "Граф невзвешенный\n";
                return 0;
            }
            try {
                if (Ed->getVertex1()->index == curr_v)
                    son_v = Ed->getVertex2()->index;
                else
                    son_v = Ed->getVertex1()->index;
            }
            catch (const runtime_error& error) {
                break;
            }
            if (v[son_v]->w > (v[curr_v]->w + w))
            {
                v[son_v]->w = v[curr_v]->w + w;
                v[son_v]->parrent = curr_v;
            }
            if (!v[son_v]->state)
                st.push(v[son_v]);
            ++outputEdgeIterator;
            try {
            Ed = *outputEdgeIterator;
            }
            catch (const runtime_error& error) {
                break;
            }
        }
    }
    int s = MAX;
    int end_v;
    for (int i = 0; i < graph->getVertexCount(); i++)
        if (v[i]->vertex != v1)
            if (v[i]->state)
            {
                if (v[i]->w > s || s == MAX)
                {
                    end_v = v[i]->vertex;
                    s = v[i]->w;
                }
            }
            else {
                cout << "Граф несвязный\n";
                return 0;
            }
    if (s < R)
    {
        R = s;
        int j = 0;
        way[j] = end_v;
        int v2 = v[end_v]->vertex;
        while (v2 != v1)
        {
            j++;
            v2 = v[v2]->parrent;
            way[j] = v2;
        }
        way[j + 1] = -1;
        end = j;
    }
    for (int i = 0; i < graph->getVertexCount(); i++)
        delete v[i];
    return 1;
}
template<class Vertex, class Edge>
SecondTask<Vertex, Edge>::SecondTask(Graph<Vertex, Edge>* g) {
    graph = g;
    R = MAX_INT;
    restart();
}
template<class Vertex, class Edge>
SecondTask<Vertex, Edge>::SecondTask(SecondTask<Vertex, Edge>& secondTask) {
    graph = secondTask.graph;
    R = MAX_INT;
    restart();
}
template<class Vertex, class Edge>
SecondTask<Vertex, Edge>::~SecondTask() {
}
template<class Vertex, class Edge>
void SecondTask<Vertex, Edge>::set(Graph<Vertex, Edge>* g) {
    graph = g;
    R = MAX_INT;
    restart();
}
template<class Vertex, class Edge>
void SecondTask<Vertex, Edge>::restart() {
    for (int i = 0; i < graph->getVertexCount(); i++) {
        res = Route(i);
        if (!res) {
            return;
        }
    }
}
template<class Vertex, class Edge>
void SecondTask<Vertex, Edge>::result() {
    if (res) {
        cout << "\nРадиус графа: " << R << endl;
        cout << "Путь: " << way[end];
        for (int i = (end - 1); i >= 0; i--)
        {
            cout << "-" << way[i];
        }
        cout << endl;
    }
    else {
        cout << "Ошибка. Несвязный, либо невзвешенный граф\n";
    }
}
#endif //ADS_RGR_SECOND_TASK_H