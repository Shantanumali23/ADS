#include <iostream>
using namespace std;

const int MAX_ORDER = 3;

class Node {
public:
    int values[MAX_ORDER - 1];
    Node* childNodes[MAX_ORDER];
    int valueCount;
    bool isLeafNode;
    
    Node(bool leaf) {
        isLeafNode = leaf;
        valueCount = 0;
        for (int i = 0; i < MAX_ORDER; i++)
            childNodes[i] = nullptr;
    }
};

class BTree {
public:
    Node* rootNode;
    
    void splitNode(Node* parent, int index, Node* fullNode) {
        Node* newNode = new Node(fullNode->isLeafNode);
        newNode->valueCount = 1;
        newNode->values[0] = fullNode->values[1]; 
        
        if (!fullNode->isLeafNode) {
            newNode->childNodes[0] = fullNode->childNodes[1];
            newNode->childNodes[1] = fullNode->childNodes[2];
        }
        
        fullNode->valueCount = 1;
        
        for (int j = parent->valueCount; j > index; j--)
            parent->childNodes[j + 1] = parent->childNodes[j];
        
        parent->childNodes[index + 1] = newNode;
        
        for (int j = parent->valueCount - 1; j >= index; j--)
            parent->values[j + 1] = parent->values[j];
        
        parent->values[index] = fullNode->values[1];
        parent->valueCount++;
    }
    
    void insertIntoNonFull(Node* node, int val) {
        int i = node->valueCount - 1;
        
        if (node->isLeafNode) {
            while (i >= 0 && val < node->values[i]) {
                node->values[i + 1] = node->values[i];
                i--;
            }
            node->values[i + 1] = val;
            node->valueCount++;
        } else {
            while (i >= 0 && val < node->values[i])
                i--;
            i++;
            
            if (node->childNodes[i]->valueCount == MAX_ORDER - 1) {
                splitNode(node, i, node->childNodes[i]);
                if (val > node->values[i])
                    i++;
            }
            insertIntoNonFull(node->childNodes[i], val);
        }
    }
    
    void traverseLevel(Node* node) {
        if (!node) {
            cout << "Tree is empty." << endl;
            return;
        }
        Node* queue[100];
        int front = 0, rear = 0;
        queue[rear++] = node;
        
        while (front < rear) {
            Node* temp = queue[front++];
            for (int i = 0; i < temp->valueCount; i++)
                cout << temp->values[i] << " ";
            
            if (!temp->isLeafNode)
                for (int i = 0; i <= temp->valueCount; i++)
                    queue[rear++] = temp->childNodes[i];
        }
        cout << endl;
    }
    
    BTree() 
    { 
        rootNode = nullptr; 
    }
    
    void insertValue(int val) {
        if (!rootNode) {
            rootNode = new Node(true);
            rootNode->values[0] = val;
            rootNode->valueCount = 1;
        } else {
            if (rootNode->valueCount == MAX_ORDER - 1) {
                Node* newRoot = new Node(false);
                newRoot->childNodes[0] = rootNode;
                splitNode(newRoot, 0, rootNode);
                rootNode = newRoot;
            }
            insertIntoNonFull(rootNode, val);
        }
    }
    
    void display() {
        cout << "B-Tree Level Order: ";
        if (!rootNode) {
            cout << "Tree is empty." << endl;
            return;
        }
        Node* queue[100];
        int front = 0, rear = 0;
        queue[rear++] = rootNode;
        
        while (front < rear) {
            Node* temp = queue[front++];
            for (int i = 0; i < temp->valueCount; i++)
                cout << temp->values[i] << " ";
            
            if (!temp->isLeafNode)
                for (int i = 0; i <= temp->valueCount; i++)
                    queue[rear++] = temp->childNodes[i];
        }
        cout << endl;
    }
};

int main() {
    BTree tree;
    int option, val;
    do {
        cout << "\n1. Insert\n2. Display Level Order\n3. Exit\nEnter choice: ";
        cin >> option;
        switch (option) {
            case 1:
                cout << "Enter value: ";
                cin >> val;
                tree.insertValue(val);
                break;
            case 2:
                tree.display();
                break;
            case 3:break;
            default:
                cout << "Invalid choice!\n";
        }
    } while (option != 3);
    return 0;
}