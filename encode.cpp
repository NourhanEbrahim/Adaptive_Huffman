#include <bits/stdc++.h>
#include"BST.h"
#include"Node.h"

using namespace std;

BST:: BST()    //constructor
{
    NYT->Data.second="NYT"; //Name
    NYT->Data.first=0;      //weight
    NYT->left=NULL;
    NYT->right=NULL;
    root = NYT;
}
BST:: ~BST() {}
string s1="";
string BST ::lookup(Node*tree,string y ,string stt="") //search and out the code of the symbol
{
    if(tree->Data.second == "NO")      //Parent node with children
    {
        if(tree->left->Data.second == y )
        {
            stt+='0';
            return stt;
        }
        if(tree->right->Data.second == y )
        {
            stt+='1';
            return stt;
        }
        if(tree->left->Data.second == "NO")
        {
            s1=lookup(tree->left , y ,stt+'0');
        }
        if(tree->right->Data.second == "NO")
        {
            s1=lookup(tree->right , y,stt+'1');
        }
    }
    return s1;
}

void BST :: increas(Node*tree , string y)  //Update weight if symbol is exist before
{
    if(tree->Data.second == "NO")
        tree->Data.first++;
    if(tree->left->Data.second == y )
    {
        tree->left->Data.first++;
    }
    else if(tree->right->Data.second == y )
    {
        tree->right->Data.first++;
    }
    else if(tree->left->Data.second == "NO")
    {
        increas(tree->left,y);
    }
    else if(tree->right->Data.second == "NO")
    {
        increas(tree->right,y);
    }
}

void BST :: getBalance( Node *N )    //Balance the tree if left > right
{
    if ((N->left->Data.first) <= (N->right->Data.first))
    {
        if (N->left->Data.second == "NO" )
        {
            getBalance(N->left);
        }
        else if (N->right->Data.second == "NO")
        {
            getBalance(N->right);
        }
    }
    else
    {
        Node* temp = new Node();
        temp = N->left;
        N->left= N->right;
        N->right = temp;
        // if there's more balance
        if(N->left->Data.second =="NO")getBalance(N->left);
        if (N->right->Data.second == "NO")getBalance(N->right);
    }
}

void BST :: updateWeight(Node*tree )    //Update the weight of the tree if new symbol is inserted
{
    if(tree->Data.second == "NO")tree->Data.first++;
    if(tree->left!=NULL && tree->left->Data.second == "NO")updateWeight(tree->left);
    if(tree->right!=NULL && tree->right->Data.second == "NO")updateWeight(tree->right);
}
bool b=1;
Node* BST ::Insert(Node*tree,string  x )   //Insert new symbol
{

    if(tree == NYT)
    {

        Node* t = new Node();
        Node* node2= new Node();
        t->Data.first = 0;
        t->Data.second ="NO";
        node2->Data.second =x;
        node2->Data.first = 1;
        node2->left=NULL;
        node2->right=NULL;
        t->right = node2;
        t->left = NYT;
        if(b)            //Specifies the root
        {
            root=t;
            b=0;
        }
        return t;
    }
    else if(tree->Data.second == "NO" )
    {
        if(tree->left->Data.second == "NO"||tree->left->Data.second == "NYT")
        {
            tree->left = Insert (tree->left, x );
        }

        else if(tree->right->Data.second == "NO"||tree->right->Data.second == "NYT")
        {
            tree->right=Insert (tree->right, x );
        }

    }

    return tree;

}

string decimaltobinary(int n, bool b1,int e)   //convert decimal value to binary
{
    string s="";
    while(n!=0)
    {
        s+=((n%2)+'0');
        n=n/2;
    }
    if(b1)    //if index <= 2r
    {
        while(s.size() < e+1)s+="0";
    }
    else     //if index > 2r
    {
        while(s.size()< e)s+="0";
    }
    reverse(s.begin(),s.end());
    return s;
}
pair<int ,int> CalcER (int m)    //Calculate the value e , r
{
    pair <int , int> p;    //first -> e , second -> r
    p.first = log2(m);
    p.second = m-pow(2,p.first);
    return p;
}
string yt="";
int main()
{
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    int e,r ,num;
    string inp , s;
    cin>>s;    //Set of input
    cin>>inp;  //input
    num = s.size();
    int frq[num+1];
    memset(frq,0,sizeof frq);
    e=CalcER(num).first;
    r=CalcER(num).second;
    cout<<s<<endl;
    BST T;

    int j=0;
    string enc="",n ,st;
    while(j<inp.size())
    {
        if(j)T.getBalance(T.root);    //balance the tree after the first symbol
        int index;
        n = inp[j];
        for(int i=0; i<s.size(); i++)   //Get the index of the symbol from the set
        {
            if(s[i] == n[0])
            {
                index=i+1;
                break;
            }
        }
        if(!frq[index])     //check if the symbol come for the first time
        {

            frq[index]++;
            if(0 < index && index <= 2*r)
            {
                st=decimaltobinary(index-1,1,e);   //find the code of the index

            }
            else if(index > 2*r)
                st=decimaltobinary((index-1)-r,0,e);
            //find the code of the symbol
            if(j)
            {
                yt=T.lookup(T.root,"NYT");  //found the code of NYT
                s1="";
                enc+=yt+st;
            }
            else enc+=st;
            T.Insert(T.root,n);
            T.updateWeight(T.root);
        }
        else              //if the symbol is exist in the tree
        {
            frq[index]++;
            st = T.lookup(T.root ,n);    //found the code of the symbol of the tree
            s1="";
            T.increas(T.root , n);
            enc+=st;
        }

        j++;

    }
    cout<<enc;
    return 0;
}

