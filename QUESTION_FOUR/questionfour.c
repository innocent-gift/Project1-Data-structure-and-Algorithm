#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define structure for a medicine node in the BST
typedef struct MedicineNode {
    char code[50];
    char name[100];
    int quantity;
    double unit_price;
    struct MedicineNode *left;
    struct MedicineNode *right;
} MedicineNode;

// Create a new node using dynamic memory allocation
MedicineNode* create_node(const char *code, const char *name, int quantity, double unit_price) {
    MedicineNode *new_node = (MedicineNode*)malloc(sizeof(MedicineNode));
    if (!new_node) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    strcpy(new_node->code, code);
    strcpy(new_node->name, name);
    new_node->quantity = quantity;
    new_node->unit_price = unit_price;
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;
}

// Insert into BST or update quantity if duplicate medicine code is found
MedicineNode* insert_or_update(MedicineNode *root, const char *code, const char *name, int quantity, double unit_price) {
    if (root == NULL) {
        return create_node(code, name, quantity, unit_price);
    }

    int cmp = strcmp(code, root->code);
    if (cmp < 0) {
        root->left = insert_or_update(root->left, code, name, quantity, unit_price);
    } else if (cmp > 0) {
        root->right = insert_or_update(root->right, code, name, quantity, unit_price);
    } else {
        // Duplicate code found: update quantity as required
        root->quantity += quantity;
        printf("[Notice]: Duplicate code %s found. Quantity updated by +%d (New Total: %d).\n", 
               code, quantity, root->quantity);
    }
    return root;
}

// Search for a medicine by code
MedicineNode* search_medicine(MedicineNode *root, const char *code) {
    if (root == NULL || strcmp(root->code, code) == 0) {
        return root;
    }
    if (strcmp(code, root->code) < 0) {
        return search_medicine(root->left, code);
    }
    return search_medicine(root->right, code);
}

// In-order traversal to display complete inventory sorted by code
void in_order_traversal(MedicineNode *root) {
    if (root == NULL) return;
    in_order_traversal(root->left);
    printf("%-10s | %-35s | Qty: %-5d | Price: %.2f RWF\n", 
           root->code, root->name, root->quantity, root->unit_price);
    in_order_traversal(root->right);
}

// Load inventory from file with validation
MedicineNode* load_inventory_from_file(const char *filename, MedicineNode *root) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Error: Could not open file %s\n", filename);
        return root;
    }

    char line[256];
    int line_num = 0;

    while (fgets(line, sizeof(line), file)) {
        line_num++;
        // Remove trailing newline if present
        line[strcspn(line, "\r\n")] = 0;
        
        // Skip empty lines
        if (strlen(line) == 0) continue;

        char code[50], name[100];
        int quantity;
        double unit_price;

        // Parse pipe-separated format: MedicineCode|MedicineName|Quantity|UnitPrice
        if (sscanf(line, "%49[^|]|%99[^|]|%d|%lf", code, name, &quantity, &unit_price) == 4) {
            if (quantity < 0 || unit_price < 0) {
                printf("Warning: Invalid negative quantity or price at line %d. Record skipped.\n", line_num);
                continue;
            }
            root = insert_or_update(root, code, name, quantity, unit_price);
        } else {
            printf("Warning: Malformed record at line %d. Record skipped.\n", line_num);
        }
    }

    fclose(file);
    return root;
}

// Free allocated memory recursively
void free_tree(MedicineNode *root) {
    if (root == NULL) return;
    free_tree(root->left);
    free_tree(root->right);
    free(root);
}

int main() {
    MedicineNode *root = NULL;
    
    printf("Loading pharmacy inventory from inventory.txt...\n");
    root = load_inventory_from_file("inventory.txt", root);
    printf("Inventory loaded successfully into BST.\n");

    int choice;
    char search_code[50];

    do {
        printf("\n=== Hospital Pharmacy Inventory System ===\n");
        printf("1. Search Medicine by Code\n");
        printf("2. Display Complete Inventory (Sorted by Code)\n");
        printf("3. Exit and Clear Memory\n");
        printf("Enter your choice (1-3): ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter a number.\n");
            while(getchar() != '\n');
            continue;
        }

        switch (choice) {
            case 1:
                printf("Enter Medicine Code (e.g., M1001): ");
                scanf("%49s", search_code);
                {
                    MedicineNode *result = search_medicine(root, search_code);
                    if (result != NULL) {
                        printf("\n--- Medicine Found ---\n");
                        printf("Code       : %s\n", result->code);
                        printf("Name       : %s\n", result->name);
                        printf("Quantity   : %d\n", result->quantity);
                        printf("Unit Price : %.2f RWF\n", result->unit_price);
                        printf("----------------------\n");
                    } else {
                        printf("\n[Result]: Medicine code '%s' does not exist in the inventory.\n", search_code);
                    }
                }
                break;
            case 2:
                printf("\n--- Complete Pharmacy Inventory (In-Order Traversal) ---\n");
                if (root == NULL) {
                    printf("Inventory is empty.\n");
                } else {
                    in_order_traversal(root);
                }
                printf("-------------------------------------------------------\n");
                break;
            case 3:
                printf("Releasing memory and exiting...\n");
                free_tree(root);
                root = NULL;
                printf("Program terminated gracefully. No memory leaks.\n");
                break;
            default:
                printf("Invalid choice. Please select between 1 and 3.\n");
        }
    } while (choice != 3);

    return 0;
}
