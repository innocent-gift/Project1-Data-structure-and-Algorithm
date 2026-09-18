#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define structure for a laboratory sample node
typedef struct SampleNode {
    char sample_id[50];
    char sample_type[50];
    int priority; // 1 = Urgent, 2 = Normal, 3 = Routine
    struct SampleNode *prev;
    struct SampleNode *next;
} SampleNode;

// Define structure for the doubly linked queue with head, tail, and current tracker
typedef struct {
    SampleNode *head;
    SampleNode *tail;
    SampleNode *current;
    int size;
} LabQueue;

// Initialize the queue
void init_queue(LabQueue *q) {
    q->head = NULL;
    q->tail = NULL;
    q->current = NULL;
    q->size = 0;
}

// Create a new sample node
SampleNode* create_node(const char *id, const char *type, int priority) {
    SampleNode *new_node = (SampleNode*)malloc(sizeof(SampleNode));
    if (!new_node) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    strcpy(new_node->sample_id, id);
    strcpy(new_node->sample_type, type);
    new_node->priority = priority;
    new_node->prev = NULL;
    new_node->next = NULL;
    return new_node;
}

// Add a new sample to the end of the queue (O(1) time complexity using tail pointer)
void add_sample(LabQueue *q, const char *id, const char *type, int priority) {
    SampleNode *new_node = create_node(id, type, priority);
    
    if (q->head == NULL) {
        q->head = new_node;
        q->tail = new_node;
        q->current = new_node; // Set current to the first item if queue was empty
    } else {
        q->tail->next = new_node;
        new_node->prev = q->tail;
        q->tail = new_node;
    }
    q->size++;
    printf("Successfully added Sample ID: %s to the queue.\n", id);
}

// Display the current sample details
void display_current(LabQueue *q) {
    if (q->current == NULL) {
        printf("\n[Queue Status]: The queue is currently empty.\n");
        return;
    }
    
    const char *priority_str = (q->current->priority == 1) ? "Urgent" :
                               (q->current->priority == 2) ? "Normal" : "Routine";
    
    printf("\n--- Current Sample Details ---\n");
    printf("Sample ID   : %s\n", q->current->sample_id);
    printf("Sample Type : %s\n", q->current->sample_type);
    printf("Priority    : %d (%s)\n", q->current->priority, priority_str);
    printf("------------------------------\n");
}

// Move to the next sample in the queue
void move_next(LabQueue *q) {
    if (q->current == NULL) {
        printf("\n[Navigation]: The queue is empty.\n");
        return;
    }
    if (q->current->next != NULL) {
        q->current = q->current->next;
        printf("\n[Navigation]: Moved to the next sample.\n");
        display_current(q);
    } else {
        printf("\n[Navigation]: Reached the end of the queue. Cannot move forward.\n");
    }
}

// Move to the previous sample in the queue
void move_prev(LabQueue *q) {
    if (q->current == NULL) {
        printf("\n[Navigation]: The queue is empty.\n");
        return;
    }
    if (q->current->prev != NULL) {
        q->current = q->current->prev;
        printf("\n[Navigation]: Moved to the previous sample.\n");
        display_current(q);
    } else {
        printf("\n[Navigation]: Already at the first sample. Cannot move backward.\n");
    }
}

// Free all memory allocated for the queue
void free_queue(LabQueue *q) {
    SampleNode *current = q->head;
    while (current != NULL) {
        SampleNode *next_node = current->next;
        free(current);
        current = next_node;
    }
    q->head = NULL;
    q->tail = NULL;
    q->current = NULL;
    q->size = 0;
}

// Main menu interface
int main() {
    LabQueue queue;
    init_queue(&queue);

    int choice;
    char id[50], type[50];
    int priority;

    // Load initial set of laboratory samples
    printf("Initializing queue with sample data...\n");
    add_sample(&queue, "SMP101", "Blood-Plasma", 1);
    add_sample(&queue, "SMP102", "Serum", 2);
    add_sample(&queue, "SMP103", "Whole-Blood", 3);

    do {
        printf("\n=== Hospital Laboratory Sample Queue System ===\n");
        printf("1. Display Current Sample\n");
        printf("2. Move to Next Sample\n");
        printf("3. Move to Previous Sample\n");
        printf("4. Add New Sample to End of Queue\n");
        printf("5. Exit and Clear Queue\n");
        printf("Enter your choice (1-5): ");
        
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter a number.\n");
            while(getchar() != '\n'); // clear buffer
            continue;
        }

        switch (choice) {
            case 1:
                display_current(&queue);
                break;
            case 2:
                move_next(&queue);
                break;
            case 3:
                move_prev(&queue);
                break;
            case 4:
                printf("Enter Sample ID: ");
                scanf("%49s", id);
                printf("Enter Sample Type: ");
                scanf("%49s", type);
                printf("Enter Priority Level (1=Urgent, 2=Normal, 3=Routine): ");
                scanf("%d", &priority);
                add_sample(&queue, id, type, priority);
                break;
            case 5:
                printf("Exiting system and freeing memory...\n");
                free_queue(&queue);
                printf("Program terminated gracefully. No memory leaks.\n");
                break;
            default:
                printf("Invalid choice. Please select between 1 and 5.\n");
        }
    } while (choice != 5);

    return 0;
}
