#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char order_id[50];
    char customer_name[50];
    char product_category[50];
    double order_value;
} Order;

// Comparison function based on warehouse rules:
// 1. OrderValue descending
// 2. CustomerName ascending lexicographical
// 3. OrderID ascending lexicographical
int compare_orders(const Order *a, const Order *b) {
    if (a->order_value != b->order_value) {
        return (b->order_value > a->order_value) ? 1 : -1;
    }
    int name_cmp = strcmp(a->customer_name, b->customer_name);
    if (name_cmp != 0) {
        return name_cmp;
    }
    return strcmp(a->order_id, b->order_id);
}

void swap(Order *a, Order *b) {
    Order temp = *a;
    *a = *b;
    *b = temp;
}

int partition(Order arr[], int low, int high) {
    Order pivot = arr[high];
    int i = (low - 1);
    
    for (int j = low; j <= high - 1; j++) {
        // If arr[j] comes before pivot according to priority rules
        if (compare_orders(&arr[j], &pivot) < 0) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

// Quick Sort implemented from scratch
void quick_sort(Order arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quick_sort(arr, low, pi - 1);
        quick_sort(arr, pi + 1, high);
    }
}

int main() {
    FILE *file = fopen("orders.txt", "r");
    if (!file) {
        printf("Error: Could not open orders.txt\n");
        return 1;
    }

    int capacity = 10;
    int count = 0;
    Order *orders = malloc(capacity * sizeof(Order));
    if (!orders) {
        printf("Memory allocation failed\n");
        fclose(file);
        return 1;
    }

    char id[50], name[50], cat[50];
    double val;

    // Read file line by line handling unknown number of orders
    while (fscanf(file, "%49s %49s %49s %lf", id, name, cat, &val) == 4) {
        if (count >= capacity) {
            capacity *= 2;
            Order *temp = realloc(orders, capacity * sizeof(Order));
            if (!temp) {
                printf("Memory reallocation failed\n");
                free(orders);
                fclose(file);
                return 1;
            }
            orders = temp;
        }
        strcpy(orders[count].order_id, id);
        strcpy(orders[count].customer_name, name);
        strcpy(orders[count].product_category, cat);
        orders[count].order_value = val;
        count++;
    }
    fclose(file);

    // Calculate total value of all orders
    double total_value = 0;
    for (int i = 0; i < count; i++) {
        total_value += orders[i].order_value;
    }

    // Sort orders using custom Quick Sort
    if (count > 1) {
        quick_sort(orders, 0, count - 1);
    }

    // Write sorted orders to priority_orders.txt
    FILE *out = fopen("priority_orders.txt", "w");
    if (!out) {
        printf("Error: Could not create priority_orders.txt\n");
        free(orders);
        return 1;
    }

    for (int i = 0; i < count; i++) {
        fprintf(out, "%s %s %s %.0f\n", 
                orders[i].order_id, 
                orders[i].customer_name, 
                orders[i].product_category, 
                orders[i].order_value);
    }
    fclose(out);

    // Display required statistics
    printf("Number of orders processed: %d\n", count);
    printf("Total value of all orders: %.2f RWF\n", total_value);

    free(orders);
    return 0;
}
