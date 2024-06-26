#ifndef BST_H
#define BST_H
#include <string>
#include <unordered_map>
#include <queue>
#include <iostream>
#include <stdlib.h>
#include <sstream>

namespace cop4530 {

template<typename T>
class BST{
    struct BSTNode
    {
        int count;
        T element;
        BSTNode *left;
        BSTNode *right;

        BSTNode(const T & val, BSTNode *lt, BSTNode *rt, int c = 0) : element{val}, count{c}, left{lt}, right{rt} {};
        BSTNode(const T && val, BSTNode *lt, BSTNode *rt, int c = 0) : element{val}, count{c}, left{lt}, right{rt} {};
    };

    public:
        BST(int th = 1);
        BST(const std::string input, int th = 1);
        BST(const BST&);
        BST(BST&&);
        ~BST();

        void buildFromInputString(const std::string input);
        const BST & operator= (const BST & x);
        const BST & operator= (BST && x);
        bool empty();
        void printInOrder() const;
        void printLevelOrder() const;
        int numOfNodes() const;
        int height() const;
        void makeEmpty();
        void insert(const T& v);
        void insert(T &&v);
        void remove(const T& v);
        bool contains(const T& v);

    private:

    BSTNode *root;
    int limit;
    
    void printInOrder(BSTNode *t) const;
	void printLevelOrder(BSTNode *t) const;
	void makeEmpty(BSTNode* &t);
	void insert(const T& v, BSTNode *&t);
    void insert(T&& v, BSTNode *&t);
	void remove(const T& v, BSTNode *&t);
	bool contains(const T &x, BSTNode *&t, BSTNode *&prev = nullptr) const;
	int numOfNodes(BSTNode *t) const;
	int height(BSTNode *t) const;
	BSTNode *clone(BSTNode *t) const;
    BSTNode * findMin( BSTNode *t ) const;
    void rotateRightChild(BSTNode *t, BSTNode* child) const;
    void rotateLeftChild(BSTNode *t, BSTNode* child) const;
};

#include "bst.hpp"

}
#endif


