#include <iostream>
#include <time.h>

// using namespace std;

struct Node {
    int value;
    Node *left;
    Node *right;
};

class BinaryTree {
private:
    Node *root;

public:
    BinaryTree() {
        root = NULL;
    };

    void insert(int value) {
        Node *p = new Node;
        Node *parent;
        
        p->value = value;
        p->left = NULL;
        p->right = NULL;
        parent = NULL;
        
        if (is_empty()) {
            root = p;
        } 
        else if (!is_empty()) {
            Node *ptr;
            ptr = root;
            while(ptr != NULL) {
                parent = ptr;
                if (value > ptr->value) {
                    ptr = ptr->right;
                } 
                else {
                    ptr = ptr->left;
                }
            }
            if (value < parent->value) {
                parent->left = p;
            } 
            else {
                parent->right = p;
            }
        }
    };

    bool search(int key) {
        return search(key, root);
    };

    bool search(int key, Node *ptr) {
        if (ptr != NULL) {
            if (key == ptr->value) {
                std::cout << "Found " << ptr->value << std::endl;
                return true;
            }
            if (key <= ptr->value) {
                return search(key, ptr->left);
            } 
            else {
                return search(key, ptr->right);
            }
        } 
        else if (ptr == NULL) {
            std::cout << "Could not find " << key << std::endl;
            return false;
        }
        return NULL;
    }

    void displayTree() {
        displayTree(root);
    }

    void displayTree(Node *ptr) {
        if (ptr != NULL) {
            displayTree(ptr->left);
            std::cout << ptr->value << std::endl;
            displayTree(ptr->right);
        }
    };
    
    bool is_empty() {
        return root == NULL;
    }

    Node *get_root() {
        return root;
    }
};

int main() {

    BinaryTree bin_tree;
    
    srand(time(NULL));
    for (int i = 0; i < 24; i++) {
        int rand_val = rand() % 100; // Generate number between 0 to 99
        bin_tree.insert(rand_val);
    }
    
    // bin_tree.insert(20);
    // bin_tree.insert(10);
    // bin_tree.insert(22);
    // bin_tree.insert(17);
    // bin_tree.insert(21);
    // bin_tree.insert(11);

    bin_tree.displayTree();
    
    int val = rand() % 100;
    bin_tree.search(val);

    return 0;
}
