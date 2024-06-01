#include <stdio.h>
#include <stdlib.h>

// Node structure
struct Node {
    int data;
    struct Node* next;
};

// Function to display the linked list
void displayList(struct Node* head) {
    struct Node* current = head;
    while (current != NULL) {
        printf("%d -> ", current->data);
        current = current->next;
    }
    printf("NULL\n");
}

// Function to insert a new node at the beginning of the linked list
struct Node* insertAtBeginning(struct Node* head, int value) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = value;
    newNode->next = head;
    return newNode;
}

// Function to insert a new node at the end of the linked list
struct Node* insertAtEnd(struct Node* head, int value) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = value;
    newNode->next = NULL;

    if (head == NULL) {
        return newNode;
    }

    struct Node* current = head;
    while (current->next != NULL) {
        current = current->next;
    }

    current->next = newNode;
    return head;
}

// Function to insert a new node after a given node
struct Node* insertAfterNode(struct Node* head, int afterValue, int value) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = value;
    newNode->next = NULL;

    struct Node* current = head;

    while (current != NULL && current->data != afterValue) {
        current = current->next;
    }

    if (current == NULL) {
        printf("Node with value %d not found.\n", afterValue);
        return head;
    }

    newNode->next = current->next;
    current->next = newNode;

    return head;
}

// Function to insert a new node before a given node
struct Node* insertBeforeNode(struct Node* head, int beforeValue, int value) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = value;
    newNode->next = NULL;

    if (head == NULL) {
        return newNode;
    }

    if (head->data == beforeValue) {
        newNode->next = head;
        return newNode;
    }

    struct Node* current = head;

    while (current->next != NULL && current->next->data != beforeValue) {
        current = current->next;
    }

    if (current->next == NULL) {
        printf("Node with value %d not found.\n", beforeValue);
        return head;
    }

    newNode->next = current->next;
    current->next = newNode;

    return head;
}

// Function to free memory allocated for the linked list
void freeList(struct Node* head) {
    struct Node* current = head;
    while (current != NULL) {
        struct Node* temp = current;
        current = current->next;
        free(temp);
    }
}

int main() {
    struct Node* head = NULL;
    int choice, value, afterValue, beforeValue;

    do {
        printf("\n--- Singly Linked List Operations ---\n");
        printf("1. Insert at the beginning\n");
        printf("2. Insert at the end\n");
        printf("3. Insert after a node\n");
        printf("4. Insert before a node\n");
        printf("5. Display the linked list\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter the value to insert: ");
                scanf("%d", &value);
                head = insertAtBeginning(head, value);
                break;
            case 2:
                printf("Enter the value to insert: ");
                scanf("%d", &value);
                head = insertAtEnd(head, value);
                break;
            case 3:
                printf("Enter the value to insert: ");
                scanf("%d", &value);
                printf("Enter the value of the node after which to insert: ");
                scanf("%d", &afterValue);
                head = insertAfterNode(head, afterValue, value);
                break;
            case 4:
                printf("Enter the value to insert: ");
                scanf("%d", &value);
                printf("Enter the value of the node before which to insert: ");
                scanf("%d", &beforeValue);
                head = insertBeforeNode(head, beforeValue, value);
                break;
            case 5:
                displayList(head);
                break;
            case 0:
                printf("Exiting the program.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 0);

    // Free memory before exiting
    freeList(head);

    return 0;
}
