#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node {
    int val;
    struct Node* next;
} node_t;

void print_node(node_t* node) {
    printf("val:  %d\n", node->val);
    printf("addr: %p\n", node);
    printf("next: %p\n", node->next);
}

node_t* create_new_node(int val) {
    node_t* result = (node_t*)calloc(1, sizeof(node_t));
    if (result == NULL) {
        printf("malloc() failed!\n");
        return NULL;
    }
    
    result->val = val;
    result->next = NULL;
    return result;
}

void freelist(node_t* head) {
    if (head == NULL) return;
    
    node_t* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
    free(head);
}

void printlist(node_t* head) {
    if (head == NULL) {
        printf("empty list!\n");
        return;
    }
    
    node_t* temp = head;
    while (temp != NULL) {
        printf("%d - ", temp->val);
        temp = temp->next;
    }
    printf("\n");
}

node_t* insert_at_head(node_t** head, node_t* node_to_insert) {
    if (node_to_insert == NULL) {
        printf("try to insert NULL!\n");
        return NULL;
    }
    
    node_to_insert->next = *head;
    *head = node_to_insert;
    return *head;
}

void insert_after_node(node_t* node_to_insert_after, node_t* newnode) {
    if (node_to_insert_after == NULL) {
        printf("node_to_insert_after is NULL!\n");
        return;
    }
    if (newnode == NULL) {
        printf("newnode is NULL!\n");
        return;
    }
    
    // 11 -> 12 -> 13 -> ... wanna add 77 after 12 
    // 11 -> 12 -> 77 -> 13 -> ...
    
    newnode->next = node_to_insert_after->next;
    node_to_insert_after->next = newnode;
}

node_t* find_node(node_t* head, int target) {
    node_t* temp = head;
    while (temp != NULL) {
        if (temp->val == target) {
            printf("found node with value %d\n", temp->val);
            return temp;
        }
        temp = temp->next;
    }
    printf("no such node with value %d\n", target);
    return NULL;
}

void remove_node(node_t** head, node_t* node_to_remove) {
    if (*head == NULL) {
        printf("empty list!\n");
        return;
    }
    if (node_to_remove == NULL) {
        printf("try to remove NULL!\n");
        return;
    }
    
    // 1. remove head 
    if (*head == node_to_remove) {
        *head = node_to_remove->next;
        free(node_to_remove);
    }
    // 2. remove any other node 
    else {
        // find the previous node in the list, i.e. temp->next == node_to_remove
        node_t* temp = *head;
        while (temp != NULL && temp->next != node_to_remove) {
            temp = temp->next;
        }
        if (temp->next == NULL) return;
        
        // 11 -> 12 -> 77 -> 13 -> ...
        // 11 -> 77 -> 13 -> ...
        
        temp->next = node_to_remove->next;
        node_to_remove->next = NULL;
        free(node_to_remove);
    }
    return;
}

void remove_node2(node_t** head, int target) {
    node_t* node_to_remove = find_node(*head, target);
    if (node_to_remove == NULL) return;
    
    remove_node(head, node_to_remove);
}

node_t* seplist(node_t* head) {
    // 1. even odd 
    
    // 2. odd even 
    
    return NULL;
}

bool hasCycle(node_t* head) {
    node_t* fast = head, *slow = head;
    while (fast != NULL && fast->next != NULL) {
        fast = fast->next->next;
        slow = slow->next;
        if (fast == slow) return true;
    }
    return false;
}

node_t* reverselist(node_t* head) {
    // 11 -> 12 -> 13
    // 13 -> 12 -> 11
    
    node_t* newhead = NULL;
    while (head != NULL) {
        node_t* temp = head->next;
        head->next = newhead;
        newhead = head;
        head = temp;
    }
    return newhead;
}

int main() {
    const int Len = 25;
    
    node_t* head = NULL;
    node_t* temp = NULL;
    
    for (int i = 0; i < Len; i++) {
        temp = create_new_node(i);
        insert_at_head(&head, temp);
    }
    
    temp = find_node(head, 12);
    printlist(head);
    
    insert_after_node(temp, create_new_node(77));
    printlist(head);
    
    remove_node(&head, temp);
    printlist(head);
    
    remove_node2(&head, 22);
    printlist(head);
    
    temp = reverselist(head);
    printlist(temp);
    
    freelist(head);
    return 0;
}








