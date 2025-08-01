#include "Graph.h"
#include "Vertex_map.h"
#include "Vertex.h"
#include "Edge.h"
#include "Task.h"
#include "Task2.h"
#include <windows.h>
#include <ctime>
#include <iostream>
#include <string>

//const int VERTEX_COUNT = 7;
//const int EDGE_COUNT = 30;
//const int DIRECTED = true;
//const int DENSE = true;
using namespace std;
void vertexIteratorMenu(Graph<Vertex<string, int>, Edge<Vertex<string, int>, int, int>>* graph,
    MapVertex<string, Vertex<string, int>*>& mapVertex) {
    Graph<Vertex<string, int>, Edge<Vertex<string, int>, int, int>>::VertexIterator vertexIterator(*graph);
    int key;
    while (true) {
        cout << endl;
        cout << "Меню итератора вершин графа" << endl;
        cout << "1. Перевести итератор в начальную позицию" << endl;
        cout << "2. Перевести итератор в конечную позицию" << endl;
        cout << "3. Операция перехода к следующему" << endl;
        cout << "4. Прочитать имя" << endl;
        cout << "5. Задать имя" << endl;
        cout << "6. Прочитать данные" << endl;
        cout << "7. Задать данные" << endl;
        cout << "8. Прочитать индекс" << endl;
        cout << "9. Выход" << endl;
        cin >> key;
        switch (key) {
        case 1:
            cout << boolalpha << vertexIterator.toBegin() << endl;
            break;
        case 2:
            cout << boolalpha << vertexIterator.toEnd() << endl;
            break;
        case 3:
            cout << boolalpha << ++vertexIterator << endl;
            break;
        case 4:
            try {
                if ((*vertexIterator)->hasName())
                    cout << "Имя: " << (*vertexIterator)->getName() << endl;
                else
                    cout << boolalpha << false << endl;
            }
            catch (const runtime_error& error) {
                cout << error.what() << endl;
            }
            break;
        case 5:
            try {
                cout << "Введите имя:" << endl;
                string name;
                cin >> name;
                bool success;
                if (!(*vertexIterator)->hasName())
                    success = mapVertex.addPair(name, (*vertexIterator));
                else
                    success = mapVertex.replaceName((*vertexIterator)->getName(), name);

                if (success) {
                    (*vertexIterator)->setName(name);
                    cout << boolalpha << true << endl;
                }
                else
                    cout << boolalpha << false << endl;
            }
            catch (const runtime_error& error) {
                cout << error.what() << endl;
            }
            break;
        case 6:
            try {
                if ((*vertexIterator)->hasData())
                    cout << "Данные: " << (*vertexIterator)->getData() << endl;
                else
                    cout << boolalpha << false << endl;
            }
            catch (const runtime_error& error) {
                cout << error.what() << endl;
            }
            break;
        case 7: {
            cout << "Введите данные:" << endl;
            int data;
            cin >> data;
            try {
                (*vertexIterator)->setData(data);
                cout << boolalpha << true << endl;
            }
            catch (const runtime_error& error) {
                cout << error.what() << endl;
            }
            break;
        }
        case 8:
            try {
                cout << (*vertexIterator)->index << endl;
            }
            catch (const runtime_error& error) {
                cout << error.what() << endl;
            }
            break;
        case 9:
            return;
        }
    }
}
void edgeIteratorMenu(Graph<Vertex<string, int>, Edge<Vertex<string, int>, int, int>>* graph) {
    Graph<Vertex<string, int>, Edge<Vertex<string, int>, int, int>>::EdgeIterator edgeIterator(*graph);
    int key;
    while (true) {
        cout << endl;
        cout << "Меню итератора ребер графа" << endl;
        cout << "1. Перевести итератор в начальную позицию" << endl;
        cout << "2. Перевести итератор в конечную позицию" << endl;
        cout << "3. Операция перехода к следующему" << endl;
        cout << "4. Прочитать вес" << endl;
        cout << "5. Задать вес" << endl;    
        cout << "6. Прочитать данные" << endl;
        cout << "7. Задать данные" << endl;
        cout << "8. Прочитать индекс" << endl;
        cout << "9. Выход" << endl;
        cin >> key;
        switch (key) {
        case 1:
            cout << boolalpha << edgeIterator.toBegin() << endl;
            break;
        case 2:
            cout << boolalpha << edgeIterator.toEnd() << endl;
            break;
        case 3:
            cout << boolalpha << ++edgeIterator << endl;
            break;
        case 4:
            try {
                if ((*edgeIterator)->hasWeight())
                    cout << "Вес: " << (*edgeIterator)->getWeight() << endl;
                else
                    cout << boolalpha << false << endl;
            }
            catch (const runtime_error& error) {
                cout << error.what() << endl;
            }
            break;
        case 5: {
            cout << "Введите вес:" << endl;
            int weight;
            cin >> weight;
            try {
                (*edgeIterator)->setWeight(weight);
                cout << boolalpha << true << endl;
            }
            catch (const runtime_error& error) {
                cout << error.what() << endl;
            }
            break;
        }
        case 6:
            try {
                if ((*edgeIterator)->hasData())
                    cout << "Данные: " << (*edgeIterator)->getData() << endl;
                else
                    cout << boolalpha << false << endl;
            }
            catch (const runtime_error& error) {
                cout << error.what() << endl;
            }
            break;
        case 7: {
            cout << "Введите данные:" << endl;
            int data;
            cin >> data;
            try {
                (*edgeIterator)->setData(data);
                cout << boolalpha << true << endl;
            }
            catch (const runtime_error& error) {
                cout << error.what() << endl;
            }
            break;
        }
        case 8: {
            try {
                cout << (*edgeIterator)->getVertex1()->index << " "
                    << (*edgeIterator)->getVertex2()->index << endl;
            }
            catch (const runtime_error& error) {
                cout << error.what() << endl;
            }
            break;
        }
        case 9:
            return;
        }
    }
}
void outputEdgeIteratorMenu(Graph<Vertex<string, int>, Edge<Vertex<string, int>, int, int>>* graph) {
    int vertexIndex;
    while (true) {
        cout << "Введите индекс вершины:" << endl;
        cin >> vertexIndex;
        if (vertexIndex >= graph->getVertexCount() || graph->getVertexCount() < 0) {
            cout << "Исключение" << endl;
            return;
        }
        Vertex<string, int>* vertex;
        try {
            vertex = graph->getVertex(vertexIndex);
        }
        catch (const runtime_error& error) {
            cout << error.what() << endl;
            continue;
        }
        Graph<Vertex<string, int>, Edge<Vertex<string, int>, int, int>>::OutputEdgeIterator outputEdgeIterator(
            *graph,
            *vertex);
        int key;
        bool work = true;
        while (work) {
            cout << endl;
            cout << "Меню итератора исходящих ребер вершины" << endl;
            cout << "1. Перевести итератор в начальную позицию" << endl;
            cout << "2. Перевести итератор в конечную позицию" << endl;
            cout << "3. Операция перехода к следующему" << endl;
            cout << "4. Прочитать вес" << endl;
            cout << "5. Задать вес" << endl;
            cout << "6. Прочитать данные" << endl;
            cout << "7. Задать данные" << endl;
            cout << "8. Прочитать индекс" << endl;
            cout << "9. Сменить вершину" << endl;
            cout << "10.Выход" << endl;
            cin >> key;
            switch (key) {
            case 1:
                cout << boolalpha << outputEdgeIterator.toBegin() << endl;
                break;
            case 2:
                cout << boolalpha << outputEdgeIterator.toEnd() << endl;
                break;
            case 3:
                cout << boolalpha << ++outputEdgeIterator << endl;
                break;
            case 4:
                try {
                    if ((*outputEdgeIterator)->hasWeight())
                        cout << "Вес: " << (*outputEdgeIterator)->getWeight() << endl;
                    else
                        cout << boolalpha << false << endl;
                }
                catch (const runtime_error& error) {
                    cout << error.what() << endl;
                }
                break;
            case 5: {
                cout << "Введите вес:" << endl;
                int weight;
                cin >> weight;
                try {
                    (*outputEdgeIterator)->setWeight(weight);
                    cout << boolalpha << true << endl;
                }
                catch (const runtime_error& error) {
                    cout << error.what() << endl;
                }
                break;
            }
            case 6:
                try {
                    if ((*outputEdgeIterator)->hasData())
                        cout << "Данные: " << (*outputEdgeIterator)->getData() << endl;
                    else
                        cout << boolalpha << false << endl;
                }
                catch (const runtime_error& error) {
                    cout << error.what() << endl;
                }
                break;
            case 7:
                cout << "Введите данные:" << endl;
                int data;
                cin >> data;
                try {
                    (*outputEdgeIterator)->setData(data);
                    cout << boolalpha << true << endl;
                }
                catch (const runtime_error& error) {
                    cout << error.what() << endl;
                }
                break;
            case 8: {
                try {
                    cout << endl << (*outputEdgeIterator)->getVertex1()->index << " "
                        << (*outputEdgeIterator)->getVertex2()->index
                        << endl;
                }
                catch (const runtime_error& error) {
                    cout << error.what() << endl;
                }
                break;
            }
            case 9:
                work = false;
                break;
            case 10:
                return;
            }
        }
    }
}
void VertexOperationsMenu(Graph<Vertex<string, int>, Edge<Vertex<string, int>, int, int>>* graph, MapVertex<string, Vertex<string, int>*> &mapVertex) {
    int vertexIndex;
    
    while (true) {
        int ans;
        string name;
        cout << "Выбор вершины по индексу(0) или по имени(1)?" << endl;
        cin >> ans;
        if (ans == 1) {
            try {
                cout << "Введите имя вершины:" << endl;
                cin >> name;
                vertexIndex = mapVertex.getData(name)->index;
            }
            catch (const runtime_error& error) {
                cout << error.what() << endl;
                break;
            }
        }
        else {
            cout << "Введите индекс вершины:" << endl;
            cin >> vertexIndex;
        }
        if (vertexIndex >= graph->getVertexCount() || graph->getVertexCount() < 0) {
            cout << "Исключение" << endl;
            break;
        }
        Vertex<string, int>* vertex;
        try {
            vertex = graph->getVertex(vertexIndex);
        }
        catch (const runtime_error& error) {
            cout << error.what() << endl;
            continue;
        }
        int key;
        bool work = true;
        while (work) {
            cout << endl;
            cout << "Меню операций над вершиной" << endl;
            cout << "1. Прочитать имя" << endl;
            cout << "2. Задать имя" << endl;
            cout << "3. Прочитать данные" << endl;
            cout << "4. Задать данные" << endl;
            cout << "5. Сменить вершину" << endl;
            cout << "6. Выход" << endl;
            cin >> key;
            switch (key) {
            case 1:
                if (graph->getVertex(vertexIndex)->hasName())
                    cout << boolalpha << graph->getVertex(vertexIndex)->getName() << endl;
                else cout << boolalpha << false << endl;
                break;
            case 2:
                cout << "Введите имя: " << endl;
                cin >> name;
                mapVertex.addPair(name, graph->getVertex(vertexIndex));
                graph->getVertex(vertexIndex)->setName(name);
                cout << boolalpha << true << endl;
                break;
            case 3:
                if (graph->getVertex(vertexIndex)->hasData())
                cout << boolalpha << graph->getVertex(vertexIndex)->getData() << endl;
                else cout << boolalpha << false << endl;
                break;
            case 4:
                int data;
                cout << "Введите данные: " << endl;
                cin >> data;
                graph->getVertex(vertexIndex)->setData(data);
                cout << boolalpha << true << endl;
                break;
            case 5:
                work = false;
                break;
            case 6:
                return;
            }
        }
    }
}
void EdgeOperationsMenu(Graph<Vertex<string, int>, Edge<Vertex<string, int>, int, int>>* graph, MapVertex<string, Vertex<string, int>*>& mapVertex) {
    int index1,index2;

    while (true) {
        int ans;
        string name1, name2;
        cout << "Выбор ребра по индексам вершин(0) или по именам вершин(1)?" << endl;
        cin >> ans;
        if (ans == 1) {
            try {
                cout << "Введите имена вершин" << endl;
                cout << "Имя вершины 1:" << endl;
                cin >> name1;
                cout << "Имя вершины 2:" << endl;
                cin >> name2;
                index1 = mapVertex.getData(name1)->index;
                index2 = mapVertex.getData(name2)->index;
            }
            catch (const runtime_error& error) {
                cout << error.what() << endl;
                return;
            }
        }
        else {
            cout << "Введите индексы вершин" << endl;
            cout << "Индекс вершины 1:" << endl;
            cin >> index1;
            cout << "Индекс вершины 2:" << endl;
            cin >> index2;
        }
        Edge<Vertex<string,int>, int,int>* edge;
        try {
            edge = graph->getEdge(index1, index2);
        }
        catch (const runtime_error& error) {
            cout << error.what() << endl;
            return;
        }
        int key, weight;
        bool work = true;
        while (work) {
            cout << endl;
            cout << "Меню операций над вершиной" << endl;
            cout << "1. Прочитать вес ребра" << endl;
            cout << "2. Задать вес ребра" << endl;
            cout << "3. Прочитать данные" << endl;
            cout << "4. Задать данные" << endl;
            cout << "5. Сменить ребро" << endl;
            cout << "6. Выход" << endl;
            cin >> key;
            switch (key) {
            case 1:
                if (graph->getEdge(index1, index2)->hasWeight())
                    cout << boolalpha << graph->getEdge(index1, index2)->getWeight() << endl;
                else cout << boolalpha << false << endl;
                break;
            case 2:
                cout << "Введите вес: " << endl;
                cin >> weight;
                graph->getEdge(index1, index2)->setWeight(weight);
                cout << boolalpha << true << endl;
                break;
            case 3:
                if (graph->getEdge(index1, index2)->hasData())
                    cout << boolalpha << graph->getEdge(index1, index2)->getData() << endl;
                else cout << boolalpha << false << endl;
                break;
            case 4:
                int data;
                cout << "Введите данные: " << endl;
                cin >> data;
                graph->getEdge(index1, index2)->setData(data);
                cout << boolalpha << true << endl;
                break;
            case 5:
                work = false;
                break;
            case 6:
                return;
            }
        }
    }
}
void firstTaskMenu(Graph<Vertex<string, int>, Edge<Vertex<string, int>, int, int>>* graph) {
    FirstTask<Vertex<string, int>, Edge<Vertex<string, int>, int, int>> firstTask(graph);
    int key;
    while (true) {
        cout << endl;
        cout << "Определение гамильтонова цикла" << endl;
        cout << "1. Найти гамильтонов цикл" << endl;
        cout << "2. Результаты поиска" << endl;
        cout << "3. Выход" << endl;
        cin >> key;
        switch (key) {
        case 1:
            firstTask.restart();
            break;
        case 2:
            firstTask.result();
            break;
        case 3:
            return;
        }
    }
}
void secondTaskMenu(Graph<Vertex<string, int>, Edge<Vertex<string, int>, int, int>>* graph) {
    SecondTask<Vertex<string, int>, Edge<Vertex<string, int>, int, int>> secondTask(graph);

    int key;
    while (true) {
        cout << "Задача для взвешенного графа" << endl;
        cout << "1. Вычислить" << endl;
        cout << "2. Результаты" << endl;
        cout << "3. Выход" << endl;
        cin >> key;
        switch (key) {
        case 1:
            secondTask.restart();
            break;
        case 2:
            int index, d;
            cout << "Введите индекс: " << endl;
            cin >> index;
            cout << "Введите d: " << endl;
            cin >> d;
            secondTask.result(index, d);
            break;
        case 3:
            return;
        }
    }
}

int main()
{
    setlocale(LC_ALL, "Russian");
    int VERTEX_COUNT;
    int EDGE_COUNT;
    int DIRECTED;
    int DENSE;
    int aaa;
    bool randomgraph = false;
    cout << "Создание графа" << endl;
    cout << "0. Создать пустой L - граф с нулевым числом вершин и ребер" << endl;
    cout << "1. Создать граф с V вершинами, без ребер, типа D, формы представления F" << endl;
    cout << "2. Создать граф с V вершинами, с E случайными ребрами, типа D, формы F" << endl;
    cout << "3. Создать свой граф" << endl;
    cin >> aaa;
    switch (aaa) {
    case 0:
        VERTEX_COUNT = 0;
        EDGE_COUNT = 0;
        DENSE = 0;
        cout << "Выберите тип графа (0 - неориентированный, 1 - ориентированный):" << endl;
        cin >> DIRECTED;
        goto start;
        break;
    case 1:
        cout << "Введите количество вершин:" << endl;
        cin >> VERTEX_COUNT;
        EDGE_COUNT = 0;
        cout << "Выберите форму графа (0 - L-граф, 1 - M-граф):" << endl;
        cin >> DENSE;
        cout << "Выберите тип графа (0 - неориентированный, 1 - ориентированный):" << endl;
        cin >> DIRECTED;
        break;
    case 2:
        cout << "Введите количество вершин:" << endl;
        cin >> VERTEX_COUNT;
        cout << "Введите количество рёбер:" << endl;
        cin >> EDGE_COUNT;
        cout << "Выберите форму графа (0 - L-граф, 1 - M-граф):" << endl;
        cin >> DENSE;
        cout << "Выберите тип графа (0 - неориентированный, 1 - ориентированный):" << endl;
        cin >> DIRECTED;
        randomgraph = true;
        break;
    case 3:
        cout << "Введите количество вершин:" << endl;
        cin >> VERTEX_COUNT;
        cout << "Введите количество рёбер:" << endl;
        cin >> EDGE_COUNT;
        cout << "Выберите форму графа (0 - L-граф, 1 - M-граф):" << endl;
        cin >> DENSE;
        cout << "Выберите тип графа (0 - неориентированный, 1 - ориентированный):" << endl;
        cin >> DIRECTED;
        break;
    default: cout << "Ошибка";
        return 0;
        break;
    }
start:
    //srand(time(nullptr));
    auto* graph = new Graph<Vertex<string, int>, Edge<Vertex<string, int>, int, int>>(VERTEX_COUNT, EDGE_COUNT, DIRECTED, DENSE);
    Graph<Vertex<string, int>, Edge<Vertex<string, int>, int, int>>::EdgeIterator edgeIterator(*graph);
    MapVertex<string, Vertex<string, int>*> mapVertex;
    bool exit = true;
    int key, index1, index2;
    string name1, name2;
    if (randomgraph == true) {
        randomgraph = false;
        goto random;
    }
    while (exit) {
        cout << endl;
        cout << "Меню" << endl;
        cout << "1. Вывести граф на экран" << endl;
        cout << "2. Заполнить ребра графа случайными значениями веса" << endl;
        cout << "3. Получить количество вершин в графе" << endl;
        cout << "4. Получить количество ребер в графе" << endl;
        cout << "5. Получить тип графа (ориентированный/неориентированный)" << endl;
        cout << "6. Получить форму представления графа (L-граф/M-граф)" << endl;
        cout << "7. Получить коэффициент насыщенности графа" << endl;
        cout << "8. Преобразовать граф к M-графу" << endl;
        cout << "9. Преобразовать граф к L-графу" << endl;
        cout << "10.Добавить вершину к графу" << endl;
        cout << "11.Добавить вершину с именем к графу" << endl;
        cout << "12.Удалить вершину по имени" << endl;
        cout << "13.Удалить вершину по индексу" << endl;
        cout << "14.Добавить ребро по именам вершин" << endl;
        cout << "15.Добавить ребро по индексам вершин" << endl;
        cout << "16.Добавить ребро с весом по именам вершин" << endl;
        cout << "17.Добавить ребро с весом по индексам вершин" << endl;
        cout << "18.Удалить ребро по именам вершин" << endl;
        cout << "19.Удалить ребро по индексам вершин" << endl;
        cout << "20.Итератор вершин графа" << endl;
        cout << "21.Итератор ребер графа" << endl;
        cout << "22.Итератор исходящих ребер вершины" << endl;
        cout << "23.Операции над вершиной" << endl;
        cout << "24.Операции над ребром" << endl;
        cout << "25.Определение гамильтонова цикла" << endl;
        cout << "26.Задача для взвешенного графа" << endl;
        cout << "27.Установить вес для ребра" << endl;
        cout << "28.Выход" << endl;
        cin >> key;
        switch (key) {
        case 28:
            exit = false;
            break;
        case 1:
            if (graph->isDense()) graph->printGraph();
            else  graph->printGraph(false);
            break;
        case 2:
        random:
            int weightMax;
            int weightMin;
            cout << "Введите диапазон веса" << endl;
            cout << "Минимальный:" << endl;
            cin >> weightMin;
            cout << "Максимальный:" << endl;
            cin >> weightMax;
            for (int i = 0; i < graph->getVertexCount(); i++) {
                for (int j = 0; j < graph->getVertexCount(); j++) {
                    if (graph->hasEdge(i, j)) {
                        int weight = rand() % (weightMax - weightMin) + weightMin;
                        graph->getEdge(i, j)->setWeight(weight);
                    }
                }
            }
            break;
        case 3:
            cout << "Количество вершин: " << graph->getVertexCount() << endl;
            break;
        case 4:
            cout << "Количество ребер: " << graph->getEdgeCount() << endl;
            break;
        case 5:
            if (graph->isDirected())
                cout << "Ориентированный" << endl;
            else
                cout << "Неориентированный" << endl;
            break;
        case 6:
            if (graph->isDense())
                cout << "M-граф" << endl;
            else
                cout << "L-граф" << endl;
            break;
        case 7:
            cout << graph->getRatio() << endl;
            break;
        case 8:
            graph->toDenseGraph();
            break;
        case 9:
            graph->toSparseGraph();
            break;
        case 10:
            try {
                graph->insertVertex();
            }
            catch (const runtime_error& error) {
                cout << error.what() << endl;
            }
            break;
        case 11:
            try {
                cout << "Введите имя:" << endl;
                string name;
                cin >> name;
                mapVertex.addPair(name, graph->insertVertexname(name));
            }
            catch (const runtime_error& error) {
                cout << error.what() << endl;
            }
            break;
        case 12:
            try {
                cout << "Введите имя:" << endl;
                string name;
                cin >> name;
                int index = mapVertex.getData(name)->index;
                mapVertex.delPair(name);
                cout << boolalpha << graph->deleteVertex(index) << endl;
            }
            catch (const runtime_error& error) {
                cout << boolalpha << false << endl;
            }
            break;
        case 13:
            cout << "Введите индекс:" << endl;
            int index;
            cin >> index;
            try {
                if (graph->getVertex(index)->hasName()) {
                    mapVertex.delPair(graph->getVertex(index)->getName());
                }
                cout << boolalpha << graph->deleteVertex(index) << endl;
            }
            catch (const runtime_error& error) {
                cout << boolalpha << false << endl;
            }
            break;
        case 14:
            try {
                cout << "Введите имена вершин" << endl;
                cout << "Имя вершины 1:" << endl;
                cin >> name1;
                cout << "Имя вершины 2:" << endl;
                cin >> name2;
                index1 = mapVertex.getData(name1)->index;
                index2 = mapVertex.getData(name2)->index;
                graph->insertEdge(index1, index2);
                cout << boolalpha << true << endl;
            }
            catch (const runtime_error& error) {
                cout << boolalpha << false << endl;
            }
            break;
        case 15:
            cout << "Введите индексы вершин" << endl;
            cout << "Индекс вершины 1:" << endl;
            cin >> index1;
            cout << "Индекс вершины 2:" << endl;
            cin >> index2;
            try {
                graph->insertEdge(index1, index2);
                cout << boolalpha << true << endl;
            }
            catch (const runtime_error& error) {
                cout << boolalpha << false << endl;
            }
            break;
        case 16:
            try {
                int weight;
                cout << "Введите вес ребра" << endl;
                cin >> weight;
                cout << "Введите имена вершин" << endl;
                cout << "Имя вершины 1:" << endl;
                cin >> name1;
                cout << "Имя вершины 2:" << endl;
                cin >> name2;
                index1 = mapVertex.getData(name1)->index;
                index2 = mapVertex.getData(name2)->index;
                graph->insertEdgeWeight(index1, index2, weight);
                cout << boolalpha << true << endl;
            }
            catch (const runtime_error& error) {
                cout << boolalpha << false << endl;
            }
            break;
        case 17:
            int weight;
            cout << "Введите вес ребра" << endl;
            cin >> weight;
            cout << "Введите индексы вершин" << endl;
            cout << "Индекс вершины 1:" << endl;
            cin >> index1;
            cout << "Индекс вершины 2:" << endl;
            cin >> index2;
            try {
                graph->insertEdgeWeight(index1, index2, weight);
                cout << boolalpha << true << endl;
            }
            catch (const runtime_error& error) {
                cout << boolalpha << false << endl;
            }
            break;
        case 18:
            try {
                cout << "Введите имена вершин" << endl;
                cout << "Имя вершины 1:" << endl;
                cin >> name1;
                cout << "Имя вершины 2:" << endl;
                cin >> name2;
                index1 = mapVertex.getData(name1)->index;
                index2 = mapVertex.getData(name2)->index;
                cout << boolalpha << graph->deleteEdge(index1, index2) << endl;
            }
            catch (const runtime_error& error) {
                cout << boolalpha << false << endl;
            }
            break;
        case 19:
            try {
                cout << "Введите индексы вершин" << endl;
                cout << "Индекс вершины 1:" << endl;
                cin >> index1;
                cout << "Индекс вершины 2:" << endl;
                cin >> index2;
                cout << boolalpha << graph->deleteEdge(index1, index2) << endl;
            }
            catch (const runtime_error& error) {
                cout << boolalpha << false << endl;
            }
            break;
        case 20:
            vertexIteratorMenu(graph, mapVertex);
            break;
        case 21:
            edgeIteratorMenu(graph);
            break;
        case 22:
            outputEdgeIteratorMenu(graph);
            break;
        case 23:
            VertexOperationsMenu(graph, mapVertex);
            break;
        case 24:
            EdgeOperationsMenu(graph, mapVertex);
            break;
        case 25:
            firstTaskMenu(graph);
            break;
        case 26:
            secondTaskMenu(graph);
            break;
        case 27:
            int ans;
            cout << "Введите вес ребра:" << endl;
            cin >> weight;
            cout << "Установить по индексу(0) или по имени(1):" << endl;
            cin >> ans;
            if (ans == 1) {
                try {
                    cout << "Введите имена вершин" << endl;
                    cout << "Имя вершины 1:" << endl;
                    cin >> name1;
                    cout << "Имя вершины 2:" << endl;
                    cin >> name2;
                    index1 = mapVertex.getData(name1)->index;
                    index2 = mapVertex.getData(name2)->index;
                    graph->getEdge(index1, index2)->setWeight(weight);
                    cout << boolalpha << true << endl;
                }
                catch (const runtime_error& error) {
                    cout << boolalpha << false << endl;
                }
                break;
            }
            else {
                try {
                    cout << "Введите индексы вершин" << endl;
                    cout << "Индекс вершины 1:" << endl;
                    cin >> index1;
                    cout << "Индекс вершины 2:" << endl;
                    cin >> index2;
                    graph->getEdge(index1, index2)->setWeight(weight);
                    cout << boolalpha << true << endl;
                }
                catch (const runtime_error& error) {
                    cout << error.what() << endl;
                }
                break;
            }
            break;
        }
    }
    return 0;
}