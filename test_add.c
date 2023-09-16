// #include ./Header/Parsing_Header.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define the doubly linked list node structure
typedef struct Node {
    char *content;
    struct Node *prev;
    struct Node *next;
} Node;

// Function to create a new node

// Function to insert a node at the end of the list

// Function to replace nodes with concatenated content by indices
void replaceNodesByIndex(Node **head, int startIndex, int endIndex, Node *replacementNode) {
    Node *start = *head;
    Node *end = *head;

    // Move 'start' and 'end' to the specified indices
    for (int i = 0; i < startIndex && start != NULL; i++) {
        start = start->next;
    }

    for (int i = 0; i < endIndex && end != NULL; i++) {
        end = end->next;
    }

    if (start == NULL || end == NULL) {
        return; // Invalid indices, nothing to replace
    }

    // Special case: Removing nodes at the beginning
    if (start->prev == NULL) { //l's'|A_SP|st
        *head = end->next; 
        if (*head != NULL) {
            (*head)->prev = NULL;
        }
    } else {
        start->prev->next = end->next;
    }

    // Special case: Removing nodes at the end
    if (end->next != NULL) {
        end->next->prev = start->prev;
    }

    // Insert the replacement node in place
    if (start->prev != NULL) {
        start->prev->next = replacementNode;
    }
    replacementNode->prev = start->prev;
    replacementNode->next = end->next;
    if (end->next != NULL) {
        end->next->prev = replacementNode;
    }

    // Free the memory of the removed nodes
    while (start != end->next) {
        Node *temp = start;
        start = start->next;
        free(temp->content);
        free(temp);
    }
}

// Function to print the doubly linked list

