#include<bits/stdc++.h>
#ifndef BST_H_INCLUDED
#define BST_H_INCLUDED
#include"Node.h"
using namespace std;
class BST {
public:
   ~BST();
   BST();
  string lookup (Node*tree,string c,string s);
  void increas(Node*tree , string y);
  void getBalance( Node *N );
  void updateWeight(Node*tree);
  Node* Insert(Node*tree,string x);
   Node* NYT = new Node();
   Node* root= new Node();
       };


#endif
