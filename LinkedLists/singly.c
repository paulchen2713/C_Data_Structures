#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node {
    int val;
    struct Node* next;
} node_t;

void print_node(node_t* node) {
    printf("val:  %d\n", node->val);
    printf("addr: 0x%p\n", node);
    printf("next: 0x%p\n", node->next);
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

void freelist(node_t* head) {
    if (head == NULL) return;
    
    node_t* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

void insert_at_head(node_t** head, node_t* node_to_insert) {
    if (*head == NULL) return;

    if (node_to_insert == NULL) {
        printf("try to insert NULL!\n");
        return;
    }
    
    node_to_insert->next = *head;
    *head = node_to_insert;
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

node_t* middle_node(node_t* head) {
    if (head == NULL) return NULL;

    node_t* fast = head, *slow = head;
    while (fast != NULL && fast->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow;
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

bool hasCycle(node_t* head) {
    if (head == NULL || head->next == NULL) return false;

    node_t* fast = head, *slow = head;
    while (fast != NULL && fast->next != NULL) {
        fast = fast->next->next;
        slow = slow->next;
        if (fast == slow) return true;
    }
    return false;
}

void remove_elements(node_t** head, int target) {
    if (*head == NULL) return;
    
    node_t* temp = *head;
    while (temp->next != NULL) {
        if (temp->next->val == target) {
            temp->next = temp->next->next;
        }
        else temp = temp->next;
    }

    *head = ((*head)->val == target) ? (*head)->next : *head;
}

node_t* reverselist(node_t* head) {
    if (head == NULL || head->next == NULL) return head;
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

void seplist(node_t** head, int mode) {
    if (*head == NULL) return;
    if (mode != 1 && mode != 2) {
        printf("invalid mode index, please enter 1 or 2:\n");
        printf("  1: even-odd list\n");
        printf("  2: odd-even list\n");
        return;
    }

    node_t* evenfirst = NULL, *evenlast = NULL;
    node_t* oddfirst = NULL, *oddlast = NULL;

    node_t* temp = *head;
    int val = 0;
    while (temp != NULL) {
        val = temp->val;
        if (val & 1) {  // odd
            if (oddfirst == NULL) {
                oddfirst = temp;
                oddlast = oddfirst;
            }
            else {
                oddlast->next = temp;
                oddlast = oddlast->next;
            }
        }
        else {
            if (evenfirst == NULL) {
                evenfirst = temp;
                evenlast = evenfirst;
            }
            else {
                evenlast->next = temp;
                evenlast = evenlast->next;
            }
        }
        temp = temp->next;
    }
    if (evenfirst == NULL || oddfirst == NULL) return;
    
    // 1. even->odd
    if (mode == 1) {
        evenlast->next = oddfirst;
        oddlast->next = NULL;
        *head = evenfirst;
    }
    // 2. odd->even
    else if (mode == 2) {
        oddlast->next = evenfirst;
        evenlast->next = NULL;
        *head = oddfirst;
    }
}


int main() {
    const int Len = 25;
    
    node_t* head = create_new_node(33);
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
    insert_at_head(&head, create_new_node(99));
    insert_at_head(&head, create_new_node(99));
    insert_at_head(&head, create_new_node(99));
    printlist(head);

    head = reverselist(head);
    printlist(head);

    remove_elements(&head, 99);
    printlist(head);

    seplist(&head, 1);
    printlist(head);

    temp = middle_node(head);
    printlist(temp);

    seplist(&head, 2);
    printlist(head);

    temp = middle_node(head);
    printlist(temp);

    
    freelist(head);
    free(head);
    return 0;
}

/*
D:\C++\LinkedLists>singly.exe
found node with value 12
24 - 23 - 22 - 21 - 20 - 19 - 18 - 17 - 16 - 15 - 14 - 13 - 12 - 11 - 10 - 9 - 8 - 7 - 6 - 5 - 4 - 3 - 2 - 1 - 0 - 33 -
24 - 23 - 22 - 21 - 20 - 19 - 18 - 17 - 16 - 15 - 14 - 13 - 12 - 77 - 11 - 10 - 9 - 8 - 7 - 6 - 5 - 4 - 3 - 2 - 1 - 0 - 33 -
24 - 23 - 22 - 21 - 20 - 19 - 18 - 17 - 16 - 15 - 14 - 13 - 77 - 11 - 10 - 9 - 8 - 7 - 6 - 5 - 4 - 3 - 2 - 1 - 0 - 33 -
found node with value 22
99 - 99 - 99 - 24 - 23 - 21 - 20 - 19 - 18 - 17 - 16 - 15 - 14 - 13 - 77 - 11 - 10 - 9 - 8 - 7 - 6 - 5 - 4 - 3 - 2 - 1 - 0 - 33 -
33 - 0 - 1 - 2 - 3 - 4 - 5 - 6 - 7 - 8 - 9 - 10 - 11 - 77 - 13 - 14 - 15 - 16 - 17 - 18 - 19 - 20 - 21 - 23 - 24 - 99 - 99 - 99 -
33 - 0 - 1 - 2 - 3 - 4 - 5 - 6 - 7 - 8 - 9 - 10 - 11 - 77 - 13 - 14 - 15 - 16 - 17 - 18 - 19 - 20 - 21 - 23 - 24 -
0 - 2 - 4 - 6 - 8 - 10 - 14 - 16 - 18 - 20 - 24 - 33 - 1 - 3 - 5 - 7 - 9 - 11 - 77 - 13 - 15 - 17 - 19 - 21 - 23 -
1 - 3 - 5 - 7 - 9 - 11 - 77 - 13 - 15 - 17 - 19 - 21 - 23 -
33 - 1 - 3 - 5 - 7 - 9 - 11 - 77 - 13 - 15 - 17 - 19 - 21 - 23 - 0 - 2 - 4 - 6 - 8 - 10 - 14 - 16 - 18 - 20 - 24 -
21 - 23 - 0 - 2 - 4 - 6 - 8 - 10 - 14 - 16 - 18 - 20 - 24 -
*/







