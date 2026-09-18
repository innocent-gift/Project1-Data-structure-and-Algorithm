#include <stdio.h>
#include <stdlib.h>

// Define structure for a binary tree node representing a tournament participant/match
typedef struct TreeNode {
    int data;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

// Function to create a new tree node using dynamic memory allocation
TreeNode* create_node(int data) {
    TreeNode *new_node = (TreeNode*)malloc(sizeof(TreeNode));
    if (!new_node) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    new_node->data = data;
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;
}

/* 
 * Tree Construction Rule: Binary Search Tree (BST) Insertion Rule
 * - For any given node, all participant identifiers in its left subtree are smaller than the node's value.
 * - All participant identifiers in its right subtree are greater than the node's value.
 */
TreeNode* insert_bst(TreeNode* root, int data) {
    if (root == NULL) {
        return create_node(data);
    }
    if (data < root->data) {
        root->left = insert_bst(root->left, data);
    } else if (data > root->data) {
        root->right = insert_bst(root->right, data);
    }
    // Duplicate values are ignored
    return root;
}

// Search for a node by its identifier
TreeNode* search_node(TreeNode* root, int data) {
    if (root == NULL || root->data == data) {
        return root;
    }
    if (data < root->data) {
        return search_node(root->left, data);
    }
    return search_node(root->right, data);
}

// Find the parent of a given target identifier
TreeNode* find_parent(TreeNode* root, int target, TreeNode* parent) {
    if (root == NULL) {
        return NULL;
    }
    if (root->data == target) {
        return parent;
    }
    if (target < root->data) {
        return find_parent(root->left, target, root);
    } else {
        return find_parent(root->right, target, root);
    }
}

// 1. Display Root
void display_root(TreeNode* root) {
    if (root == NULL) {
        printf("\n[Tournament Status]: The tournament tree is empty.\n");
    } else {
        printf("\nRoot Participant / Match Identifier: %d\n", root->data);
    }
}

// 2. Display All Leaf Participants (Helper + Wrapper)
void display_leaves_recursive(TreeNode* root, int *found) {
    if (root == NULL) return;
    
    if (root->left == NULL && root->right == NULL) {
        printf("%d ", root->data);
        *found = 1;
        return;
    }
    display_leaves_recursive(root->left, found);
    display_leaves_recursive(root->right, found);
}

void display_leaves(TreeNode* root) {
    if (root == NULL) {
        printf("\n[Tournament Status]: The tournament tree is empty.\n");
        return;
    }
    int found = 0;
    printf("\nLeaf Participants: ");
    display_leaves_recursive(root, &found);
    if (!found) {
        printf("None found.");
    }
    printf("\n");
}

// 3. Display Parent Match/Identifier
void display_parent_query(TreeNode* root, int target) {
    TreeNode* node = search_node(root, target);
    if (node == NULL) {
        printf("\n[Error]: Participant identifier %d does not exist in the tournament tree.\n", target);
        return;
    }
    if (node == root) {
        printf("\n[Special Case]: Participant %d is the root node and has no parent.\n", target);
        return;
    }
    TreeNode* parent = find_parent(root, target, NULL);
    if (parent != NULL) {
        printf("\nParent match/identifier for %d is: %d\n", target, parent->data);
    }
}

// 4. Display Sibling Participant
void display_sibling_query(TreeNode* root, int target) {
    TreeNode* node = search_node(root, target);
    if (node == NULL) {
        printf("\n[Error]: Participant identifier %d does not exist in the tournament tree.\n", target);
        return;
    }
    if (node == root) {
        printf("\n[Special Case]: Participant %d is the root node and has no sibling.\n", target);
        return;
    }
    TreeNode* parent = find_parent(root, target, NULL);
    if (parent != NULL) {
        TreeNode* sibling = NULL;
        if (parent->left == node) {
            sibling = parent->right;
        } else {
            sibling = parent->left;
        }
        
        if (sibling != NULL) {
            printf("\nSibling participant for %d is: %d\n", target, sibling->data);
        } else {
            printf("\n[Special Case]: Participant %d has no sibling (single child branch).\n", target);
        }
    }
}

// 5. Display Grandchildren
void display_grandchildren_query(TreeNode* root, int target) {
    TreeNode* node = search_node(root, target);
    if (node == NULL) {
        printf("\n[Error]: Participant identifier %d does not exist in the tournament tree.\n", target);
        return;
    }
    
    int has_grandchildren = 0;
    printf("\nGrandchildren of participant %d: ", target);
    
    if (node->left != NULL) {
        if (node->left->left != NULL) {
            printf("%d ", node->left->left->data);
            has_grandchildren = 1;
        }
        if (node->left->right != NULL) {
            printf("%d ", node->left->right->data);
            has_grandchildren = 1;
        }
    }
    if (node->right != NULL) {
        if (node->right->left != NULL) {
            printf("%d ", node->right->left->data);
            has_grandchildren = 1;
        }
        if (node->right->right != NULL) {
            printf("%d ", node->right->right->data);
            has_grandchildren = 1;
        }
    }
    
    if (!has_grandchildren) {
        printf("None (Node has no grandchildren).");
    }
    printf("\n");
}

// Free all memory allocated for the binary tree recursively
void free_tree(TreeNode* root) {
    if (root == NULL) return;
    free_tree(root->left);
    free_tree(root->right);
    free(root);
}

int main() {
    // Provided array of participant identifiers
    int participants[] = {
        42, 17, 68, 9, 23, 55, 81, 4, 13, 20, 31, 49, 61, 75, 90, 2, 7, 11, 15, 19, 
        21, 27, 35, 45, 52, 58, 64, 72, 78, 85, 95, 1, 3, 5, 6, 8, 10, 12, 14, 16, 
        18, 22, 24, 26, 29, 33, 37, 41, 44, 47, 50, 54, 57, 60, 63, 66, 70, 74, 77, 
        80, 83, 87, 92, 97, 25, 28, 30, 34, 39
    };
    int n = sizeof(participants) / sizeof(participants[0]);

    TreeNode *root = NULL;
    printf("Constructing Binary Tournament Tree using BST rules...\n");
    for (int i = 0; i < n; i++) {
        root = insert_bst(root, participants[i]);
    }
    printf("Tournament tree constructed successfully with %d participants.\n", n);

    int choice, target;
    do {
        printf("\n=== E-Sports Tournament Management System ===\n");
        printf("1. Display Root Participant / Match Identifier\n");
        printf("2. Display All Leaf Participants\n");
        printf("3. Display Parent of a Participant\n");
        printf("4. Display Sibling of a Participant\n");
        printf("5. Display Grandchildren of a Participant\n");
        printf("6. Exit and Release Memory\n");
        printf("Enter your choice (1-6): ");
        
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter a valid number.\n");
            while(getchar() != '\n'); // clear input buffer
            continue;
        }

        switch (choice) {
            case 1:
                display_root(root);
                break;
            case 2:
                display_leaves(root);
                break;
            case 3:
                printf("Enter participant identifier: ");
                if (scanf("%d", &target) == 1) {
                    display_parent_query(root, target);
                } else {
                    printf("Invalid input.\n");
                    while(getchar() != '\n');
                }
                break;
            case 4:
                printf("Enter participant identifier: ");
                if (scanf("%d", &target) == 1) {
                    display_sibling_query(root, target);
                } else {
                    printf("Invalid input.\n");
                    while(getchar() != '\n');
                }
                break;
            case 5:
                printf("Enter participant identifier: ");
                if (scanf("%d", &target) == 1) {
                    display_grandchildren_query(root, target);
                } else {
                    printf("Invalid input.\n");
                    while(getchar() != '\n');
                }
                break;
            case 6:
                printf("Releasing all allocated memory and exiting...\n");
                free_tree(root);
                root = NULL;
                printf("Program terminated gracefully. No memory leaks.\n");
                break;
            default:
                printf("Invalid choice. Please select between 1 and 6.\n");
        }
    } while (choice != 6);

    return 0;
}
