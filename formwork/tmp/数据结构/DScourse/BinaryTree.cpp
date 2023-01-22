#include "BinaryTree.h"

#include <iostream>
using namespace std;

void BinaryTree::makeTree(const BTType &x, BinaryTree &lt, BinaryTree &rt)
{
    root = new BTreeNode(x,lt.root,rt.root);
    lt.root=NULL;
    rt.root=NULL;
}


void testBinaryTree()
{
    BinaryTree tree;
}
