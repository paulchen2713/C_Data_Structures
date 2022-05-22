// Initial Template for C
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct TreeNode {
    int val;
    struct TreeNode *right;
    struct TreeNode *left;
};

struct TreeNode *createNewNode(int value) {
    struct TreeNode *temp = (struct TreeNode *)malloc(sizeof(struct TreeNode *));
    temp->val = value;
    temp->left = temp->right = NULL;
    return temp;
}

struct TreeNode *insert(struct TreeNode *tree, int val) {

    if (tree == NULL) {
        return createNewNode(val);
    }
    if (val < tree->val) {
        tree->left = insert(tree->left, val);
    } else if (val > tree->val) {
        tree->right = insert(tree->right, val);
    }

    return tree;
}


 // } Driver Code Ends
// User function Template for C

// Function to search a struct node in BST.
bool search(struct TreeNode* root, int x) {
    if (root == NULL) {
        return false;
    }
    if (x == root->val) {
        return true;
    } else if (x > root->val) {
        return search(root->right, x);
    } else if (x < root->val) {
        return search(root->left, x);
    }
    return false;
}


// { Driver Code Starts.

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        struct TreeNode *root = NULL;

        int N;
        scanf("%d", &N);
        for (int i = 0; i < N; i++) {
            int k;
            scanf("%d", &k);
            root = insert(root, k);
        }

        int s;
        scanf("%d", &s);

        bool ans = search(root, s);

        if (ans) {
            printf("1\n");
        } else {
            printf("0\n");
        }
    }
    return 0;
}
  // } Driver Code Ends