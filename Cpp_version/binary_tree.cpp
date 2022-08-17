#include <iostream>
#include <time.h>

// using namespace std;

struct Node {
    int value;
    struct Node* left, *right;
};

class BinaryTree {
private:
    struct Node *root;

public:
    BinaryTree() {
        root = NULL;
    };

    void insert(int value) {
        // struct Node *p = new Node;
        struct Node* p = (struct Node*)calloc(1, sizeof(struct Node));
        struct Node* parent;
        
        p->value = value;
        p->left = p->right = NULL;
        parent = NULL;
        
        if (is_empty()) {
            root = p;
        } 
        else if (!is_empty()) {
            struct Node* ptr;
            ptr = root;
            while (ptr != NULL) {
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

    bool search(int key, struct Node* ptr) {
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

    void displayTree(struct Node* ptr) {
        if (ptr != NULL) {
            displayTree(ptr->left);
            std::cout << ptr->value << std::endl;
            displayTree(ptr->right);
        }
    };
    
    bool is_empty() {
        return root == NULL;
    }

    struct Node* get_root() {
        return root;
    }
    
    struct Node* emptyBST(struct Node* root) {
        struct Node* temp;
        
        if (root != NULL) {
     
            // Traverse to left subtree
            emptyBST(root->left);
     
            // Traverse to right subtree
            emptyBST(root->right);
     
            std::cout << "\nReleased node: " << root->value;
            temp = root;
     
            // Require for free memory
            free(temp);
        }
        return root;
    }
};

int main() {
    const int num_elements = 6;
    
    BinaryTree bin_tree;
    
    // srand(time(NULL));
    std::cout << "original values: \n";
    for (int i = 0; i < num_elements; i++) {
        int rand_val = rand() % 100; // Generate number between 0 to 99
        std::cout << rand_val << "\n";
        bin_tree.insert(rand_val);
    }
    std::cout << "\n";
    
    std::cout << "sorted results: \n";
    bin_tree.displayTree();
    std::cout << "\n";
    
    int val = rand() % 100;
    bin_tree.search(val);

    return 0;
}

