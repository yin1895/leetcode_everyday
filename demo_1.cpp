#include<iostream>
#include<vector>
#include<iomanip>

using namespace std;

class Node{
    private:
        int val;
        Node *l;
        Node *r;

    public:
        Node(int tmp)
        {
            val = tmp;
            l=nullptr;
            r=nullptr;
        }

        int getVal(){return val;}

        void setL(Node* tmp)
        {
            l = tmp;
        }

        void setR(Node* tmp)
        {
            r = tmp;
        }

        Node* getl(){return l;}
        Node* getr(){return r;}
};

Node * createTree()
{
    int val = 0;
    cin >> val;
    if(val==0) return nullptr;

    Node* current = new Node(val);

    current->setL(createTree());
    current->setR(createTree());
    return current;
}

void travelsolv(Node*root,vector<int>&vals)
{
    if(root==nullptr) return;

    travelsolv(root->getl(),vals);

    travelsolv(root->getr(),vals);

    vals.push_back(root->getVal());


}

int main()
{
    vector<int> vals;
    Node* root = createTree();
 
    travelsolv(root,vals);

    for(auto &it : vals)
    {
        cout << it <<' ';
    }
    cout << endl;
    return 0;
}