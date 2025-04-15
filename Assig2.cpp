#include <iostream>
using namespace std;

class Node {
public:
    int player_id;
    int score;
    Node* left;
    Node* right;
    int height;

    Node(int p, int s) {
        player_id = p;
        score = s;
        height = 1;
        left = NULL;
        right = NULL;
    }
};

int getHeight(Node* root) {
    if(root==NULL){
        return 0;
    }else{
        return root->height;
    }
}

int getBalanceFactor(Node* root) {
    if(root==NULL){
        return 0;
    }
    return getHeight(root->left) - getHeight(root->right);
}

Node* rightRotation(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;
    x->right = y;
    y->left = T2;
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
    return x;
}

Node* leftRotation(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;
    y->left = x;
    x->right = T2;
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
    return y;
}

Node* balance(Node* root) {
    if (root == NULL) return root;

    root->height = max(getHeight(root->left), getHeight(root->right)) + 1;
    int bf = getBalanceFactor(root);

    if (bf > 1 && getBalanceFactor(root->left) >= 0)
        return rightRotation(root);

    if (bf > 1 && getBalanceFactor(root->left) < 0) {
        root->left = leftRotation(root->left);
        return rightRotation(root);
    }

    if (bf < -1 && getBalanceFactor(root->right) <= 0)
        return leftRotation(root);

    if (bf < -1 && getBalanceFactor(root->right) > 0) {
        root->right = rightRotation(root->right);
        return leftRotation(root);
    }

    return root;
}

Node* insert(Node* root, int p, int s) {
    if (root == NULL)
        return new Node(p, s);

    if (p < root->player_id)
        root->left = insert(root->left, p, s);
    else if (p > root->player_id)
        root->right = insert(root->right, p, s);
    else
        return root; 

    return balance(root);
}

Node* minValueNode(Node* root) {
    Node* current = root;
    while (current->left != NULL)
        current = current->left;
    return current;
}

Node* deleteNode(Node* root, int p) {
    if (root == NULL)
        return root;

    if (p < root->player_id)
        root->left = deleteNode(root->left, p);
    else if (p > root->player_id)
        root->right = deleteNode(root->right, p);
    else {
        if (root->left == NULL || root->right == NULL) {
            if (root->left == NULL) {
                Node* temp = root->right;
                delete root;
                return temp;
            } else if (root->right == NULL) {
                Node* temp = root->left;
                delete root;
                return temp;
            }            
        } else {
            Node* temp = minValueNode(root->right);
            root->player_id = temp->player_id;
            root->score = temp->score;
            root->right = deleteNode(root->right, temp->player_id);
        }
    }

    if (root == NULL)
        return root;

    return balance(root);
}

void inorder(Node* root) {
    if (root != NULL) {
        inorder(root->left);
        cout << "Player ID: " << root->player_id << " , Score: " << root->score << endl;
        inorder(root->right);
    }
}

int main() {
    Node* root = NULL;
    int choice, player_id, score;

    while (true) {
        cout << "\n1. Register Player\n2. Display Leaderboard\n3. Remove Player\n4. Exit\nEnter Choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter Player ID: ";
                cin >> player_id ;
                cout<<"Enter Player Score: ";
                cin>>score;
                root = insert(root, player_id, score);
                break;
            case 2:
                if (!root) {
                    cout << "No players in the game.\n";
                } else {
                    inorder(root);
                }
                break;
            case 3:
                cout << "Enter Player ID to remove: ";
                cin >> player_id;
                root = deleteNode(root, player_id);
                cout <<" removed\n";
                break;
            case 4:
                return 0;
            default:
                cout << "Invalid choice.\n";
        }
    }
}



