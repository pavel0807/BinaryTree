#include <iostream>
#include "BinaryTree.h"

#include <vector>
#include <fstream>
#include <cstdlib>

using namespace std;

//Стандартные обозначения GraphViz
typedef vector<int> adjacent_t;
typedef vector<adjacent_t> graph_t;

void CreateTree(std::vector<int>& elements, std::vector<std::vector<int>>& _g);//Создание дерева
void write_dot(const char* fname, const graph_t& g, const std::vector<int> allElement);//Записать в файл .dot 

int main()
{
    std::vector<std::vector<int>> g;
    std::vector<int> allElements;
    CreateTree(allElements, g);

    write_dot("g.dot", g, allElements);

    system("dot g.dot -Tpng -og.png");
}

void CreateTree(std::vector<int>& elements, std::vector<std::vector<int>>& _g) 
{
    std::vector<std::vector<int>> g;
    std::vector<int> allElements;
    Node<int>standart(10);
    BinaryTree<int> a(&standart);
    a.add(5);
    a.add(15);
    a.add(7);
    a.add(17);
    a.add(1);
    a.add(12);
    a.add(3);
    a.add(18);
    a.CreateGraph(allElements, g);
    elements = allElements;
    _g = g;

}

void write_dot(const char* fname, const graph_t& g,const std::vector<int> allElement)
{
    ofstream out(fname);
    out << "digraph {\n";
    for (size_t i = 0; i < allElement.size(); ++i) {
        out << "  " << allElement[i] << ";\n";
    }
    for (size_t i = 0; i < g.size(); ++i) {
       
            out << "  " << g[i][0] << " -> " << g[i][1] << ";\n";
        
    }
    out << "}\n";
}

