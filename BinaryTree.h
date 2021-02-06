//
//  BinaryTree.h
//  BinaryTree
//
//  Created by Pavel on 03.02.2021.
//

#ifndef BinaryTree_h
#define BinaryTree_h

#include <stdio.h>
#include <string>
#include <vector>



 //��������� Node,��� ����� ������ � ��������� ��������� T
template<typename T>
struct Node
{
    //~Node(){delete _left,delete _right;};
    Node(T data) :_data(data) {};
    T _data;
    Node* _left = nullptr;
    Node* _right = nullptr;
};

template<typename T>
class BinaryTree
{
public:
    BinaryTree(Node<T>* root) : _root(root) {};//����������� �� ���������
    void add(T data);//���������� ��������� 
    void postorderTravesal();//���
    Node<T>* search(T data);//����� ��������
    void remove(T data);//�������� ���������

    //��� �����
    std::vector<std::vector<int>> CreateParth();
    void CreateGraph(std::vector<T>& element, std::vector<std::vector<int>>& g);

private:
    
    void postorderTravesalPrivate(Node<T>*& root, size_t size);//���
    void addPrivate(T data, Node<T>*& root);//��������� ����� ���������� �������� � ������
    Node<T>* _root; //��������� �� ������ ������
    void CreateGraphPrivate(std::vector<int>& vectorElement, Node<T>*& root);//�������� ��� ��� �����
};


template<typename T>
void BinaryTree<T>::add(T data)
{
    addPrivate(data, _root);
}

template<typename T>
void BinaryTree<T>::addPrivate(T data, Node<T>*& root)
{
    if (root == nullptr)
    {
        root = new Node<T>(data);
        return;
    }
    Node<T>*& currentNode = root->_data > data ? root->_left : root->_right;
    addPrivate(data, currentNode);
}

template<typename T>
void BinaryTree<T>::postorderTravesal()
{
    postorderTravesalPrivate(_root, 0);
}

template<typename T>
void BinaryTree<T>::postorderTravesalPrivate(Node<T>*& root, size_t size)
{
    if (root != nullptr)
    {
        size += 3;
        postorderTravesalPrivate(root->_right, size);
        std::cout << std::string(size, ' ') << root->_data << std::endl;
        postorderTravesalPrivate(root->_left, size);
        size -= 3;
    }
}

template<typename T>
Node<T>* BinaryTree<T>::search(T data)
{
    Node<T>* currentNode = _root;
    while (currentNode != nullptr)
    {
        if (currentNode->_data > data)
        {
            currentNode = currentNode->_left;
        }
        else if (currentNode->_data < data)
        {
            currentNode = currentNode->_right;
        }
        else
        {
            return currentNode;
        }
    }
    return nullptr;
}


template<typename T>
void BinaryTree<T>::remove(T data)
{
    //����� �������� � ��� ��������
    Node<T>* currentNode = _root;
    Node<T>* parentNode = nullptr;
    while (currentNode != nullptr)
    {
        if (currentNode->_data > data)
        {
            parentNode = currentNode;
            currentNode = currentNode->_left;
        }
        else if (currentNode->_data < data)
        {
            parentNode = currentNode;
            currentNode = currentNode->_right;
        }
        else
        {
            break;
        }
    }
    if (currentNode->_data != data)
    {
        return;
    }
    
    //���� ������ ���� � ����� ��������
    if (currentNode != nullptr)
    {
        //����  �� �����  ��������
        if (currentNode->_left == nullptr && currentNode->_right == nullptr)
        {
            parentNode = parentNode->_data > data ? parentNode->_left = nullptr : parentNode->_right = nullptr;

        }
        //���� ����� ������ �������
        else if (currentNode->_left == nullptr || currentNode->_right == nullptr)
        {
            //���� ������
            if (currentNode->_left != nullptr)
            {
                parentNode = parentNode->_data > data ? parentNode->_left = currentNode->_left : parentNode->_right = currentNode->_left;
            }
            //���� �������
            else if (currentNode->_right != nullptr)
            {
                parentNode = parentNode->_data > data ? parentNode->_left = currentNode->_right : parentNode->_right = currentNode->_right;
            }

        }
        //���� ����� ���������� ��������
        else
        {
            //���� ������� �� ��������� �������,��� ����� ������ ���� ��� �����,����� ��� �����
            Node<T>* nextNode = currentNode->_right;
            while (nextNode->_left != nullptr)
            {
                nextNode = nextNode->_left;
            }

            //���������� ������� ��������� ������� �� ������
            remove(nextNode->_data);

            //������ � ������ ���������� �������� ������ �� ��������� �������
            parentNode = parentNode->_data > data ? parentNode->_left = nextNode : parentNode->_right = nextNode;

            //������ ������ � ������ ��������,������� ����� �a ����� ����������
            nextNode->_right = currentNode->_right;
            nextNode->_left = currentNode->_left;

        }
        delete currentNode;
    }
    return;
}

//�������� ���
template<typename T>
std::vector<std::vector<int>> BinaryTree<T>::CreateParth()
{
    std::vector<std::vector<int>> allParth;
    std::vector<T> allElement;
    CreateGraphPrivate(allElement, _root);

    for (size_t i = 0; i < allElement.size(); ++i)
    {
        Node<T>* searchNode = this->search(allElement[i]);
        if (searchNode->_left != nullptr)
        {
            allParth.push_back({ searchNode->_data,searchNode->_left->_data });
        }
        if (searchNode->_right != nullptr)
        {
            allParth.push_back({ searchNode->_data,searchNode->_right->_data });
        }
    }
    return allParth;
}


//�������� ��� � ������� ��������� ��� �����
template<typename T>
void BinaryTree<T>::CreateGraph(std::vector<T>& element, std::vector<std::vector<int>>& g)
{
    std::vector<T> allElement;
    CreateGraphPrivate(allElement,_root);
    std::vector<std::vector<int>> allParth = CreateParth();
    element = allElement;
    g = allParth;

}



//�������� ��� ��� �����
template<typename T>
void BinaryTree<T>::CreateGraphPrivate(std::vector<int>& vectorElement, Node<T>*&  root )
{
    if (root != nullptr)
    {
        CreateGraphPrivate(vectorElement,root->_left);
        vectorElement.push_back(root->_data);
        CreateGraphPrivate(vectorElement,root->_right);

    }
}
#endif /* BinaryTree_h */
