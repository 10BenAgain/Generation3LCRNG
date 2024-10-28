#include <stdlib.h>
#include <stdio.h>

struct Node {
    int data;
    struct Node *next;
};

struct Node* add(struct Node** h,  int x) {
    struct Node* temp = (struct Node *)malloc(sizeof(struct Node));
    temp->data = x;
    temp->next = NULL;
    *h = temp;
    return *h;
}

void print_list(struct Node* h) {
    struct Node* temp = h;
    printf("List is: ");
    while(temp != NULL) {
        printf(" %d", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

int main(void) {
    struct Node* head;
    head = NULL;

    int n, i, x;
    n = 5;
    x = 1;

    for (i = 0; i < n; i++, x++) {
        struct Node* new = add(&head, x);
        print_list(new);
    }

    free(head);
    return 0;
}