#include <iostream>  // ����������� ���������� ��� �����-������
#include <vector>    // ����������� ���������� ��� ������ � ������������� ��������� (���������)
#include <string>    // ����������� ���������� ��� ������ �� ��������
#include <algorithm> // ����������� ���������� ��� ����������, ����� ��� find

using namespace std;

// ��������������� ���������� ������ Vertex ��� ������������� � ������ Edge
template <class V, class E>
class Vertex;

// ����� ��� ������������� ����� �����
template <class V, class E>
class Edge {
public:
    // ����������� ������ Edge
    Edge(const E &properties, Vertex<V, E> *vertex1, Vertex<V, E> *vertex2)
        : properties_(properties), vertex1_(vertex1), vertex2_(vertex2) {}

    // ����� ��� ��������� ������ �������, ��������� � ������
    const Vertex<V, E>* getVertex1() const { return vertex1_; }

    // ����� ��� ��������� ������ �������, ��������� � ������
    const Vertex<V, E>* getVertex2() const { return vertex2_; }

    // ����� ��� ��������� ������� �����
    const E* getProperties() const { return &properties_; }

private:
    E properties_;          // �������� �����
    Vertex<V, E>* vertex1_; // ��������� �� ������ �������
    Vertex<V, E>* vertex2_; // ��������� �� ������ �������
};

// ����� ��� ������������� ������� �����
template <class V, class E>
class Vertex {
public:
    // ����������� ������ Vertex
    Vertex(const V &properties) : properties_(properties) {}

    // ����� ��� ������ ���������� � ������� � � �����
    void print() const {
        cout << "�������: " << properties_ << endl;
        for (const Edge<V, E>* edge : edges_) {
            cout << "  ����� � " << *(edge->getVertex2()->getProperties())
                 << " (���������: " << *(edge->getProperties()) << ")" << endl;
        }
    }

    // ����� ��� ��������� ������� �������
    const V* getProperties() const { return &properties_; }

    // ����� ��� ���������� �����, ������������ ��� ������� � ������� ��������
    void addEdge(const E &properties, Vertex<V, E>* target) {
        // �������� ������ ����� � ���������� ��� � ������ ����� ������
        Edge<V, E>* edge = new Edge<V, E>(properties, this, target);
        edges_.push_back(edge);
        target->edges_.push_back(edge);
    }

private:
    V properties_;               // �������� �������
    vector<Edge<V, E>*> edges_;  // ������ ���������� �� �����, ��������� � ��������
};

// ���������� ��� ������ �����, ������� ������������� ������������
template <class V, class E>
class OneTimeVisitor {
public:
    // ����� ��� ��������� �������
    bool visitVertex(const Vertex<V, E>* vertex) {
        // ���������, ���� �� ������� ��� ��������
        if (find(visited_.begin(), visited_.end(), vertex) != visited_.end())
            return false; // ���� ��� ��������, ���������� false
        
        visited_.push_back(vertex); // ��������� ������� � ������ ����������
        return true;                // ���������� true, ��� ��� ������� ��������
    }

    // ����� ��� ��������� ����� (������ ���������� true)
    bool visitEdge(const Edge<V, E>*) { return true; }

    // ����� ��� ������ �� ������� (������� ��������� ���������� �������)
    void leaveVertex(const Vertex<V, E>*) { visited_.pop_back(); }

    // ����� ��� ������ �� ����� (������ �� ������)
    void leaveEdge(const Edge<V, E>*) {}

private:
    vector<const Vertex<V, E>*> visited_; // ������ ���������� ������
};

// ������� main - ����� ����� � ���������
int main() {
    // ������� ������� �����
    Vertex<string, int> v1("������� 1");
    Vertex<string, int> v2("������� 2");
    
    // ��������� ���� ����� ���������
    v1.addEdge(5, &v2);  // ����� �� v1 � v2 � ����� 5

    // ������� ���������� � �������� � �����
    v1.print();
    v2.print();

    return 0; // ���������� 0 ��� ��������� ���������� ���������
}