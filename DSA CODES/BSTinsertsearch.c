#include <stdio.h>
#include <stdlib.h>

// Structure for a node
struct TreeNode {
    int data;
    struct TreeNode *left;
    struct TreeNode *right;
};

// Function to create a new node
struct TreeNode* createNode(int value) {
    struct TreeNode* newNode = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    newNode->data = value;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Function to insert a node
struct TreeNode* insert(struct TreeNode* root, int value) {
    if (root == NULL) {
        return createNode(value);
    }

    if (value < root->data) {
        root->left = insert(root->left, value);
    } else if (value > root->data) {
        root->right = insert(root->right, value);
    }

    return root;
}

// Function to search for a value
struct TreeNode* search(struct TreeNode* root, int value) {
    if (root == NULL || root->data == value) {
        return root;
    }

    if (value < root->data) {
        return search(root->left, value);
    }

    return search(root->right, value);
}

int main() {
    struct TreeNode* root = NULL;
    int choice, value;
    struct TreeNode* foundNode;

    printf("Binary Search Tree Operations:\n");
    do {
        printf("\n1. Insert\n2. Search\n3. Exit\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter the value to insert: ");
                scanf("%d", &value);
                root = insert(root, value);
                printf("Value %d inserted into the tree.\n", value);
                break;
            case 2:
                printf("Enter the value to search: ");
                scanf("%d", &value);
                foundNode = search(root, value);
                if (foundNode != NULL) {
                    printf("Value %d found in the tree.\n", value);
                } else {
                    printf("Value %d not found in the tree.\n", value);
                }
                break;
            case 3:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Please enter again.\n");
        }
    } while (choice != 3);

    return 0;
}
