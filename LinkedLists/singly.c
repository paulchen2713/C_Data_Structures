#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int val;
    struct Node* next;
} node_t;

void print_node(node_t* node) {
    printf("val:  %d\n", node->val);
    printf("addr: 0x%p\n", (void*)node);
    printf("next: 0x%p\n", node->next);
}

node_t* create_new_node(int val) {
    node_t* result = (node_t*)malloc(sizeof(node_t));
    if (result == NULL) return NULL;

    result->val = val;
    result->next = NULL;
    return result;
}

void printlist(node_t* head) {
    node_t* temp = head;
    while (temp != NULL) {
        printf("%d - ", temp->val);
        temp = temp->next;
    }
    printf("\n");
}

void freelist(node_t* head) {
    if (head == NULL) return;

    node_t* temp, *start = head;
    while (temp != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
    free(start);
}

node_t* insert_at_head(node_t** head, node_t* node_to_insert) {
    if (node_to_insert == NULL) {
        printf("try to insert NULL!\n");
        return NULL;
    }

    node_to_insert->next = *head;
    *head = node_to_insert;
    return node_to_insert;
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
        printf("Empty list!\n");
        return;
    }
    if (node_to_remove == NULL) {
        printf("can't remove NULL!\n");
        return;
    }

    if (*head == node_to_remove) {
        *head = node_to_remove->next;
        free(node_to_remove);
        return;
    }
    else {
        // find the previous node in the list
        node_t* temp = *head;
        while (temp != NULL && temp->next != node_to_remove) {
            temp = temp->next;
        }
        if (temp->next == NULL) return;

        temp->next = node_to_remove->next;
        node_to_remove->next = NULL;
        free(node_to_remove);
    }
}

node_t* oddEvenList(node_t** head) {
    if (*head == NULL || !((*head)->next)) return *head;

    node_t* odd = *head, *even = (*head)->next, *even_head = even;
    while (even && even->next) {
        odd = odd->next = even->next;
        even = even->next = odd->next;
    }
    odd->next = even_head;
    return *head;
}


int main() {
    const int Len = 25;

    node_t* head = NULL, *temp = NULL;

    for (int i = 0; i < Len; i++) {
        temp = create_new_node(i);
        insert_at_head(&head, temp);
    }
    oddEvenList(&head);
    printlist(head);

    temp = find_node(head, 12);

    insert_after_node(temp, create_new_node(99));  // insert 99 after 12
    printlist(head);

    remove_node(&head, temp);  // remove 12
    printlist(head);

    
    freelist(head);
    return 0;
}

