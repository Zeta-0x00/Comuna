#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;
    int arrival_time;
    int burst_time;
    int remaining_time;
} process;

typedef struct node_t {
    process *proc;
    struct node_t *next;
} node;

typedef struct {
    node *head;
    node *tail;
} fifo;

// Initialize a new FIFO
void fifo_init(fifo *f) {
    f->head = NULL;
    f->tail = NULL;
}

// Check if the FIFO is empty
int fifo_empty(fifo *f) {
    return (f->head == NULL);
}

// Add a process to the end of the FIFO
void fifo_enqueue(fifo *f, process *proc) {
    node *new_node = (node *) malloc(sizeof(node));
    new_node->proc = proc;
    new_node->next = NULL;

    if (f->tail == NULL) {
        f->head = new_node;
        f->tail = new_node;
    } else {
        f->tail->next = new_node;
        f->tail = new_node;
    }
}

// Remove the first process from the FIFO
process *fifo_dequeue(fifo *f) {
    if (f->head == NULL) {
        return NULL;
    }

    node *temp = f->head;
    process *p = temp->proc;

    if (f->head == f->tail) {
        f->head = NULL;
        f->tail = NULL;
    } else {
        f->head = f->head->next;
    }

    free(temp);

    return p;
}

// Print the contents of the FIFO
void fifo_print(fifo *f) {
    node *temp = f->head;
    while (temp != NULL) {
        printf("ID: %d, Arrival Time: %d, Burst Time: %d, Remaining Time: %d\n", 
            temp->proc->id, temp->proc->arrival_time, temp->proc->burst_time, temp->proc->remaining_time);
        temp = temp->next;
    }
}

int main() {
    // Create a new FIFO
    fifo f;
    fifo_init(&f);

    // Create some test processes
    process p1 = {1, 0, 10, 10};
    process p2 = {2, 2, 5, 5};
    process p3 = {3, 4, 8, 8};

    // Add the processes to the FIFO
    fifo_enqueue(&f, &p1);
    fifo_enqueue(&f, &p2);
    fifo_enqueue(&f, &p3);

    // Print the contents of the FIFO
    fifo_print(&f);

    // Remove the first process from the FIFO
    process *p = fifo_dequeue(&f);
    printf("Removed process: ID %d\n", p->id);

    // Print the contents of the FIFO again
    fifo_print(&f);

    return 0;
}

