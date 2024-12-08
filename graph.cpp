#include <iostream>  // Подключение библиотеки для ввода-вывода
#include <vector>    // Подключение библиотеки для работы с динамическими массивами (векторами)
#include <string>    // Подключение библиотеки для работы со строками
#include <algorithm> // Подключение библиотеки для алгоритмов, таких как find

using namespace std;

// Предварительное объявление класса Vertex для использования в классе Edge
template <class V, class E>
class Vertex;

// Класс для представления ребер графа
template <class V, class E>
class Edge {
public:
    // Конструктор класса Edge
    Edge(const E &properties, Vertex<V, E> *vertex1, Vertex<V, E> *vertex2)
        : properties_(properties), vertex1_(vertex1), vertex2_(vertex2) {}

    // Метод для получения первой вершины, связанной с ребром
    const Vertex<V, E>* getVertex1() const { return vertex1_; }

    // Метод для получения второй вершины, связанной с ребром
    const Vertex<V, E>* getVertex2() const { return vertex2_; }

    // Метод для получения свойств ребра
    const E* getProperties() const { return &properties_; }

private:
    E properties_;          // Свойства ребра
    Vertex<V, E>* vertex1_; // Указатель на первую вершину
    Vertex<V, E>* vertex2_; // Указатель на вторую вершину
};

// Класс для представления вершины графа
template <class V, class E>
class Vertex {
public:
    // Конструктор класса Vertex
    Vertex(const V &properties) : properties_(properties) {}

    // Метод для вывода информации о вершине и её рёбрах
    void print() const {
        cout << "Вершина: " << properties_ << endl;
        for (const Edge<V, E>* edge : edges_) {
            cout << "  Ребро к " << *(edge->getVertex2()->getProperties())
                 << " (стоимость: " << *(edge->getProperties()) << ")" << endl;
        }
    }

    // Метод для получения свойств вершины
    const V* getProperties() const { return &properties_; }

    // Метод для добавления ребра, соединяющего эту вершину с целевой вершиной
    void addEdge(const E &properties, Vertex<V, E>* target) {
        // Создание нового ребра и добавление его в списки обеих вершин
        Edge<V, E>* edge = new Edge<V, E>(properties, this, target);
        edges_.push_back(edge);
        target->edges_.push_back(edge);
    }

private:
    V properties_;               // Свойства вершины
    vector<Edge<V, E>*> edges_;  // Список указателей на ребра, связанные с вершиной
};

// Посетитель для обхода графа, который предотвращает зацикливание
template <class V, class E>
class OneTimeVisitor {
public:
    // Метод для посещения вершины
    bool visitVertex(const Vertex<V, E>* vertex) {
        // Проверяем, была ли вершина уже посещена
        if (find(visited_.begin(), visited_.end(), vertex) != visited_.end())
            return false; // Если уже посещена, возвращаем false
        
        visited_.push_back(vertex); // Добавляем вершину в список посещенных
        return true;                // Возвращаем true, так как вершина посещена
    }

    // Метод для посещения ребра (всегда возвращает true)
    bool visitEdge(const Edge<V, E>*) { return true; }

    // Метод для выхода из вершины (удаляем последнюю посещенную вершину)
    void leaveVertex(const Vertex<V, E>*) { visited_.pop_back(); }

    // Метод для выхода из ребра (ничего не делаем)
    void leaveEdge(const Edge<V, E>*) {}

private:
    vector<const Vertex<V, E>*> visited_; // Список посещенных вершин
};

// Функция main - точка входа в программу
int main() {
    // Создаем вершины графа
    Vertex<string, int> v1("Вершина 1");
    Vertex<string, int> v2("Вершина 2");
    
    // Добавляем рёбра между вершинами
    v1.addEdge(5, &v2);  // Ребро от v1 к v2 с весом 5

    // Выводим информацию о вершинах и рёбрах
    v1.print();
    v2.print();

    return 0; // Возвращаем 0 для успешного завершения программы
}