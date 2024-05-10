#include <iostream>
#include <cstdlib>
#include <random>

using namespace std;

struct TreapNode {
    int key;
    int priority;
    TreapNode *left, *right;
};

class TreapPriorityQueue {
public:
    TreapNode* root;

    TreapPriorityQueue() {
        root = NULL;
    }

    void push(int key) {
        root = insertUtil(root, key);
    }

    void pop() {
        if (root) {
            cout << "Popping element with priority " << root->priority << endl;
            root = deleteMaxUtil(root);
        }
    }

    int top() {
        if (root)
            return root->key;
        return -1; // Or throw an exception
    }

    bool empty() {
        return root == NULL;
    }

    TreapNode* insertUtil(TreapNode* root, int key) {
        if (!root)
            return newNode(key);

        if (key <= root->key) {
            root->left = insertUtil(root->left, key);

            if (root->left->priority > root->priority)
                root = rightRotate(root);
        } else {
            root->right = insertUtil(root->right, key);

            if (root->right->priority > root->priority)
                root = leftRotate(root);
        }

        return root;
    }

    void inorderTraversal(TreapNode* root) {
        if (root) {
            inorderTraversal(root->left);
            cout << root->key << " ";
            inorderTraversal(root->right);
        }
    }

    void deleteKey(int key) {
        root = deleteUtil(root, key);
    }

private:
    TreapNode* newNode(int key) {
        TreapNode* temp = new TreapNode;
        temp->key = key;
        temp->priority = rand(); // Assign random priority
        temp->left = temp->right = NULL;
        cout << "Inserted element with priority " << temp->priority << endl;
        return temp;
    }

    TreapNode* rightRotate(TreapNode* y) {
        TreapNode* x = y->left;
        TreapNode* T2 = x->right;

        x->right = y;
        y->left = T2;

        return x;
    }

    TreapNode* leftRotate(TreapNode* x) {
        TreapNode* y = x->right;
        TreapNode* T2 = y->left;

        y->left = x;
        x->right = T2;

        return y;
    }

    TreapNode* deleteMaxUtil(TreapNode* root) {
        if (root == NULL)
            return root;

        if (root->left == NULL && root->right == NULL) {
            delete root;
            return NULL;
        }

        if (root->left == NULL) {
            TreapNode* temp = root->right;
            delete root;
            return temp;
        }

        if (root->right == NULL) {
            TreapNode* temp = root->left;
            delete root;
            return temp;
        }

        if (root->left->priority < root->right->priority) {
            root = leftRotate(root);
            root->left = deleteMaxUtil(root->left);
        } else {
            root = rightRotate(root);
            root->right = deleteMaxUtil(root->right);
        }

        return root;
    }

    TreapNode* deleteUtil(TreapNode* root, int key) {
        if (root == NULL)
            return root;

        if (key < root->key)
            root->left = deleteUtil(root->left, key);
        else if (key > root->key)
            root->right = deleteUtil(root->right, key);
        else
            root = deleteMaxUtil(root);

        return root;
    }
};


// Test the priority queue and Treap functions
void testPriorityQueueAndTreap() {
    TreapPriorityQueue pq;

    int keys[] = {5, 3, 8, 1, 4};

    // Push elements into the priority queue with specified priorities
    cout << "Pushing elements into the priority queue with random priorities..." << endl;
    for (int i = 0; i < 5; ++i) {
        pq.push(keys[i]);
    }

    // Print inorder traversal
    cout << "Inorder traversal of the treap: ";
    pq.inorderTraversal(pq.root);
    cout << endl;

    // Delete elements
    cout << "Deleting elements with keys 3 and 8..." << endl;
    pq.deleteKey(3);
    pq.deleteKey(8);

    // Print inorder traversal after deletion
    cout << "Inorder traversal of the treap after deletion: ";
    pq.inorderTraversal(pq.root);
    cout << endl;

    // Pop elements from the priority queue
    cout << "Elements popped from the priority queue: ";
    while (!pq.empty()) {
        cout << pq.top() << " ";
        pq.pop();
    }
    cout << endl;
}


int main() {
    srand(time(NULL)); // Seed the random number generator
    testPriorityQueueAndTreap();
    return 0;
}


