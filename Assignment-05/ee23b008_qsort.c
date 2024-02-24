/*
Names (2 collaborators): -Nithin Ken Maran (EE23B050)
                         -Arivoli Ramamoorthy (EE23B008)
RollNo's: EE23B050, EE23B008
version: 1.0

*** description ***

- takes a file as input
- file has comma separated integers
- returns and prints sorted list of integers
- uses singly linked lists and quick sort

*/

#include <stdio.h>
#include <stdlib.h>

// Define a structure to represent a node in a linked list
struct Node {
    int data;           // Store data
    struct Node* next;  // Pointer to the next node
};

// Function to create a new node with the given data
struct Node* createNode(int data) {
    // Allocate memory for the new node
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));

    // Set the data and make the new node point to NULL
    newNode->data = data;
    newNode->next = NULL;
    
    return newNode;
}

// Function to append a new node with data to the end of the linked list
void appendToList(struct Node** head, int data) {
    struct Node* newNode = createNode(data);

    if (*head == NULL) {
        // If the list is empty, make the new node the head
        *head = newNode;
    } else {
        // Traverse the list to find the last node and link it to the new node
        struct Node* current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
    }
}

// Function to find the last node of the linked list
struct Node* last_node(struct Node* head) {
    struct Node* temp = head;
    while (temp != NULL && temp->next != NULL) {
        temp = temp->next;
    }
    return temp;
}

// Function to partition the list for quick sort
struct Node* partition(struct Node* first, struct Node* last) {
    struct Node* pivot = first;
    struct Node* front = first;
    int temp = 0;
    while (front != NULL && front != last) {
        if (front->data < last->data) {
            pivot = first;

            // Swap node values
            temp = first->data;
            first->data = front->data;
            front->data = temp;

            first = first->next;
        }

        front = front->next;
    }

    // Swap the value of the last node with the current node (pivot)
    temp = first->data;
    first->data = last->data;
    last->data = temp;
    return pivot;
}

// Function to perform quick sort on the linked list
void quick_sort(struct Node* first, struct Node* last) {
    if (first == last) {
        return;
    }
    struct Node* pivot = partition(first, last);

    if (pivot != NULL && pivot->next != NULL) {
        quick_sort(pivot->next, last);
    }

    if (pivot != NULL && first != pivot) {
        quick_sort(first, pivot);
    }
}

// Function to display the linked list
void display(struct Node* head) {
    if (head == NULL) {
        printf("Empty linked list");
        return;
    }
    struct Node* temp = head;
    printf("\n Linked List :");
    while (temp != NULL) {
        printf("  %d", temp->data);
        temp = temp->next;
    }
}

int main(int argc, char** argv) {
    struct Node* head = NULL; // Initialize head to NULL
    int number;

    FILE* fin = fopen(argv[1], "r");

    while ((fscanf(fin, "%d,", &number) != EOF)) {
        // Append numbers from a file to the linked list
        appendToList(&head, number);
    }

    // Perform quick sort on the linked list
    quick_sort(head, last_node(head));

    // Display the sorted linked list
    display(head);

    // Free the allocated memory for the linked list nodes
    struct Node* current = head;
    while (current != NULL) {
        struct Node* next = current->next;
        free(current);
        current = next;
    }

    return 0;
}
