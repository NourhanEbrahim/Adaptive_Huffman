#include <bits/stdc++.h>
#include"BST.h"
#include"Node.h"

using namespace std;
BST:: BST()     //constructor
{
    NYT->Data.second="NYT";
    NYT->Data.first=0;
    NYT->left=NULL;
    NYT->right=NULL;
    root = NYT;
}
BST:: ~BST() {}
string nu;
bool BST ::lookup(Node*tree,string y ) //check if leaf (NYT or symbol)
{
    for(int j=0; j<y.size(); j++)
    {
        if(y[j] == '0')
        {
            tree=tree->left;
        }
        else
            tree=tree->right;
    }
    nu=tree->Data.second;
    return !(tree->Data.second == "NO");
}

void BST :: increas(Node*tree , string y)   //update repeated symbol
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
        if(tree->left!=NULL)increas(tree->left,y);
    }
    else if(tree->right->Data.second == "NO")
    {
        if(tree->right!=NULL)increas(tree->right,y);
    }

}

void BST :: getBalance( Node *N )       //balance if (tree->left > tree->right)
{
    if ((N->left->Data.first) <= (N->right->Data.first))
    {
        if (N->left->Data.second == "NO" )
        {
            if(N->left!=NULL)getBalance(N->left );
        }
        else if (N->right->Data.second == "NO")
        {
            if(N->right!=NULL) getBalance(N->right);
        }
    }
    else
    {
        Node* temp = new Node();
        temp = N->left;
        N->left= N->right;
        N->right = temp;
        if(N->left->Data.second =="NO")getBalance(N->left );
        if (N->right->Data.second == "NO")getBalance(N->right);
    }
}

void BST :: updateWeight(Node*tree )
{
    if(tree->Data.second == "NO")tree->Data.first++;
    if(tree->left!=NULL && tree->left->Data.second == "NO")updateWeight(tree->left);
    if(tree->right!=NULL && tree->right->Data.second == "NO")updateWeight(tree->right);
}
bool b=1;
Node* BST ::Insert(Node*tree,string  x )
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
        if(b)
        {
            root=t;
            b=0;
        }

        return t;
    }
    else if(tree->Data.second == "NO" )
    {
        if(tree->left->Data.second == "NO"||tree->left->Data.second == "NYT")tree->left=Insert (tree->left, x );
        else if(tree->right->Data.second == "NO"||tree->right->Data.second == "NYT")
        {
            tree->right=Insert (tree->right, x );
        }

    }

    return tree;

}

int binToDecimal(string s)   //convert the binary to decimal
{
    reverse(s.begin(),s.end());
    int x=0;
    for(int i=0; i<s.size(); i++)
    {
        if(s[i]=='1')
        {
            x+=pow(2,i);
        }
    }
    return x;
}
pair<int ,int> CalcER (int m)
{
    pair<int ,int> p;
    p.first=log2(m);
    p.second=m-pow(2,p.first);
    return p;
}

string yt="";
int main()
{
    freopen("../encode/output.txt","r",stdin);
    freopen("output2.txt","w",stdout);
    BST T;
    bool b=1;
    int e,r;
    string st,s,stt,ans="",n;
    cin>>s;
    cin>>st;
    if(s.size()==1)
    {
        for(int i=0; i<st.size(); i++)
        {
            cout<<s;
        }
    }
    else
    {
        e=CalcER(s.size()).first;
        r=CalcER(s.size()).second;
        int y = 0,z;
        while(y < st.size())
        {
            if(b)            //if first symbol we read (e) bits
            {
                stt=st.substr(y,e);
                z=binToDecimal(stt);
                if(z < r)
                {
                    stt+=st[y+e];
                    z=binToDecimal(stt);
                    y+=e+1;
                }
                else
                {
                    z+=r;
                    y+=e;
                }
                n=s[z];
                ans+=n;
                b=0;
                T.Insert(T.root,n);
                T.updateWeight(T.root);
                T.getBalance(T.root);
            }
            else         //if not first symbol
            {
                stt=st[y];
                y++;
                while(!T.lookup(T.root,stt))    //while the code is not leaf
                {
                    stt+=st[y];     //read one more bit
                    y++;
                }
                if(nu == "NYT")    //if leaf is NYT
                {
                    stt=st.substr(y,e);    //Read (e) more bits
                    z=binToDecimal(stt);
                    if(z < r)
                    {
                        stt+=st[y+e];
                        z=binToDecimal(stt);
                        y+=e+1;

                    }
                    else
                    {
                        z+=r;
                        y+=e;
                    }
                    n=s[z];
                    T.Insert(T.root,n);
                    T.updateWeight(T.root);
                    T.getBalance(T.root);
                    ans+=n;
                }
                else           //if leaf is symbol
                {
                    ans+=nu;       //out this symbol
                    T.increas(T.root,nu);
                    T.getBalance(T.root);
                }
            }
        }
        cout<<ans;
    }
    return 0;
}
