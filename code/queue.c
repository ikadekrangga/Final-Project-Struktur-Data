#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Node structure
typedef struct Node {
    bool data;
    struct Node* next;
} Node;

// Queue structure
typedef struct Queue {
    Node* front;
    Node* rear;
} Queue;

// Function to create a new node
Node* createNode(bool data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) {
        printf("Memory allocation error\n");
        exit(1);
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// Function to create a new queue
Queue* createQueue() {
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    if (!queue) {
        printf("Memory allocation error\n");
        exit(1);
    }
    queue->front = queue->rear = NULL;
    return queue;
}

// Function to enqueue an element
void enqueue(Queue* queue, bool data) {
    Node* newNode = createNode(data);
    if (queue->rear == NULL) {
        queue->front = queue->rear = newNode;
        return;
    }
    queue->rear->next = newNode;
    queue->rear = newNode;
}

// Function to dequeue an element
bool dequeue(Queue* queue) {
    if (queue->front == NULL) {
        printf("Queue is empty\n");
        return false;
    }
    Node* temp = queue->front;
    bool data = temp->data;
    queue->front = queue->front->next;
    if (queue->front == NULL) {
        queue->rear = NULL;
    }
    free(temp);
    return data;
}

// Function to check if the queue is empty
bool isEmpty(Queue* queue) {
    return queue->front == NULL;
}

// Function to read and print all elements in the queue
void readQueue(Queue* queue) {
    Node* temp = queue->front;
    while (temp != NULL) {
        printf("%s ", temp->data ? "true" : "false");
        temp = temp->next;
    }
    printf("\n");
}

int main() {
    Queue* queue = createQueue();
    
    // Enqueue some true/false values
    enqueue(queue, true);
    enqueue(queue, false);
    enqueue(queue, true);
    enqueue(queue, false);
    
    // Read and print the queue
    printf("Queue contents: ");
    readQueue(queue);
    
    // Dequeue and print each element
    while (!isEmpty(queue)) {
        printf("Dequeued: %s\n", dequeue(queue) ? "true" : "false");
    }
    
    return 0;
}