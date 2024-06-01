#include <stdio.h>
#include <stdlib.h>

// Define the structure for a doubly linked list node
struct Node {
    int data;
    struct Node* prev;
    struct Node* next;
};

// Function to create a new node
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}

// Function to insert a node at the beginning of the doubly linked list
void insertAtBeginning(struct Node** head, int data) {
    struct Node* newNode = createNode(data);
    newNode->next = *head;
    if (*head != NULL) {
        (*head)->prev = newNode;
    }
    *head = newNode;
}

// Function to insert a node at the end of the doubly linked list
void insertAtEnd(struct Node** head, int data) {
    struct Node* newNode = createNode(data);
    struct Node* last = *head;

    if (*head == NULL) {
        *head = newNode;
        return;
    }

    while (last->next != NULL) {
        last = last->next;
    }

    last->next = newNode;
    newNode->prev = last;
}

// Function to insert a node after a given node in the doubly linked list
void insertAfter(struct Node* prevNode, int data) {
    if (prevNode == NULL) {
        printf("Previous node cannot be NULL\n");
        return;
    }

    struct Node* newNode = createNode(data);
    newNode->next = prevNode->next;
    newNode->prev = prevNode;
    prevNode->next = newNode;

    if (newNode->next != NULL) {
        newNode->next->prev = newNode;
    }
}

// Function to insert a node before a given node in the doubly linked list
void insertBefore(struct Node** head, struct Node* nextNode, int data) {
    if (nextNode == NULL) {
        printf("Next node cannot be NULL\n");
        return;
    }

    struct Node* newNode = createNode(data);
    newNode->prev = nextNode->prev;
    newNode->next = nextNode;

    if (nextNode->prev != NULL) {
        nextNode->prev->next = newNode;
    } else {
        *head = newNode;
    }

    nextNode->prev = newNode;
}

// Function to print the doubly linked list
void printList(struct Node* head) {
    while (head != NULL) {
        printf("%d <-> ", head->data);
        head = head->next;
    }
    printf("NULL\n");
}

// Main function to test the doubly linked list operations
int main() {
    struct Node* head = NULL;
    int choice, data;
    struct Node* nodeToInsertAfter;
    struct Node* nodeToInsertBefore;

    do {
        printf("\n1. Insert at the beginning\n");
        printf("2. Insert at the end\n");
        printf("3. Insert after a given node\n");
        printf("4. Insert before a given node\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter data to insert at the beginning: ");
                scanf("%d", &data);
                insertAtBeginning(&head, data);
                break;

            case 2:
                printf("Enter data to insert at the end: ");
                scanf("%d", &data);
                insertAtEnd(&head, data);
                break;

            case 3:
                printf("Enter data to insert after: ");
                scanf("%d", &data);
                nodeToInsertAfter = head;
                while (nodeToInsertAfter != NULL && nodeToInsertAfter->data != data) {
                    nodeToInsertAfter = nodeToInsertAfter->next;
                }
                insertAfter(nodeToInsertAfter, data);
                break;

            case 4:
                printf("Enter data to insert before: ");
                scanf("%d", &data);
                nodeToInsertBefore = head;
                while (nodeToInsertBefore != NULL && nodeToInsertBefore->data != data) {
                    nodeToInsertBefore = nodeToInsertBefore->next;
                }
                insertBefore(&head, nodeToInsertBefore, data);
                break;

            case 0:
                break;

            default:
                printf("Invalid choice. Please enter a valid option.\n");
        }

        // Print the doubly linked list after each operation
        printf("Doubly Linked List: ");
        printList(head);

    } while (choice != 0);

    return 0;
}
