#include<iostream>
#include<queue>
using namespace std;

class node{
    public:
    int key;
    string value;
    node *left,*right;

    node(){
        key=0;
        value="";
        left=NULL;
        right=NULL;
    }

    node(int k,string val){
        key=k;
        value=val;
        left=NULL;
        right=NULL;
    }   
};

node *insert(node*root,int k,string val){
    if(root == NULL){
        return new node(k,val);
    }
    if(root->key==k){
        return root;
    }
    
    if(root->key < k){
        root->right = insert(root->right,k,val);
    }else{
        root->left = insert(root->left,k,val);
    }

    return root;
}

void inorder(node *root){
    if(root!=NULL){
        inorder(root->left);
        cout<<root->key<<" : "<<root->value<<endl;
        inorder(root->right);
    }
}

void preorder(node *root){
    if(root!=NULL){
        cout<<root->key<<" : "<<root->value<<endl;
        preorder(root->left);
        preorder(root->right);
    }
}

void postorder(node *root){
    if(root !=NULL){
        postorder(root->left);
        postorder(root->right);
        cout<<root->key<<" : "<<root->value<<endl;
    }
}

bool search(node *root, int k){
    if(root==NULL){
        cout<<"Not found"<<endl;
        return false;
    }
    if(root->key == k){
        cout<<"Found: "<<root->key<<" : "<<root->value<<endl;
        return true;
    }
    if(root->key > k) return search(root->left,k);
    
    return search(root->right,k);
}

node* minValueNode(node* root) {
    node* current = root;
    while (current && current->left != NULL)
        current = current->left;
    return current;
}

node *deletenode(node*root,int k){
    if (root == NULL)
        return root;
   
    if (k < root->key) {
        root->left = deletenode(root->left, k);
    }
    else if (k > root->key) {
        root->right = deletenode(root->right, k);
    }
    else {
        if (root->left == NULL) {
            node* temp = root->right;
            delete root;
            return temp;
        }
        else if (root->right == NULL) {
            node* temp = root->left;
            delete root;
            return temp;
        }
        
        node* temp = minValueNode(root->right);
        root->key = temp->key;
        root->value = temp->value;
        root->right = deletenode(root->right, temp->key);
    }
    return root;
}

void level(node *root){
    if(root==NULL){
        cout<<"Dictionary is empty!"<<endl;
        return;
    }
    queue<node*>q;
    q.push(root);
    while(!q.empty()){
        int levelSize = q.size();
        for(int i = 0; i < levelSize; i++) {
            node *p = q.front();
            q.pop();
            cout<<p->key<<" : "<<p->value<<"  ";
            if(p->left){
                q.push(p->left);
            }
            if(p->right){
                q.push(p->right);
            }
        }
        cout << endl;
    }
}

void swap(node * root){
    node *temp = root->left;
    root->left = root->right;
    root->right = temp;
}

node *mirror(node* root){
    if(root == NULL){
        return root;
    }
    swap(root);
    mirror(root->left);
    mirror(root->right);
    return root;
}

node* copyTree(node* root) {
    if (root == NULL) return NULL;
    node* newNode = new node(root->key, root->value);
    newNode->left = copyTree(root->left);
    newNode->right = copyTree(root->right);
    return newNode;
}

int main(){
    node* root = NULL;
    node* mirrorRoot = NULL;
    node* copyRoot = NULL;
    
    int choice, key, search_key, delete_key;
    string val;

    while (true) {
        cout << "\n1.Insert A Word \n2.Inorder Traversal \n3.Preorder Traversal \n4.Postorder Traversal \n5.Search A word \n6.Delete a word \n7.Mirror Image of dictionary \n8.Create copy of dictionary \n9.Display dictionary level-wise \n10.Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter key: ";
                cin >> key;
                cout << "Enter Value: ";
                cin >> val;
                root = insert(root, key, val);
                break;
            case 2:
                cout << "Inorder Traversal: " << endl;
                inorder(root);
                break;
            case 3:
                cout << "Preorder Traversal: " << endl;
                preorder(root);
                break;
            case 4:
                cout << "Postorder Traversal: " << endl;
                postorder(root);
                break;
            case 5:
                cout << "Enter key to search: ";
                cin >> search_key;
                search(root, search_key);
                break;
            case 6:
                cout << "Enter key to delete: ";
                cin >> delete_key;
                root = deletenode(root, delete_key);
                break;
            case 7:
                mirrorRoot = copyTree(root);
                mirrorRoot = mirror(mirrorRoot);
                cout << "Mirror created. Displaying mirror:" << endl;
                inorder(mirrorRoot);
                break;
            case 8:
                copyRoot = copyTree(root);
                cout << "Copy created. Original:" << endl;
                inorder(root);
                cout << "Copy:" << endl;
                inorder(copyRoot);
                break;
            case 9:
                cout << "Levelwise:" << endl;
                level(root);
                break;
            case 10:
                return 0;
            default:
                cout << "Invalid Choice" << endl;
        }
    }
    return 0;
}