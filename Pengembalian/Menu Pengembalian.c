#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define the structure for a node in the linked list
typedef struct Node {
    char idBuku[10];
    char judulBuku[100];
    char penulis[50];
    int jumlahBuku;
    struct Node* next;
} Node;

// Structure for queue (Borrowing Queue)
typedef struct QueueNode {
    char namaUser[50];
    char idBuku[10];
    struct QueueNode *next;
} QueueNode;

typedef struct Queue {
    int count;
    QueueNode *front;
    QueueNode *rear;
} Queue;

// Function to create a new node
Node* createNode(const char* idBuku, const char* judulBuku, const char* penulis, int jumlahBuku) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    strncpy(newNode->idBuku, idBuku, sizeof(newNode->idBuku) - 1);
    strncpy(newNode->judulBuku, judulBuku, sizeof(newNode->judulBuku) - 1);
    strncpy(newNode->penulis, penulis, sizeof(newNode->penulis) - 1);
    newNode->idBuku[sizeof(newNode->idBuku) - 1] = '\0';
    newNode->judulBuku[sizeof(newNode->judulBuku) - 1] = '\0';
    newNode->penulis[sizeof(newNode->penulis) - 1] = '\0';
    newNode->jumlahBuku = jumlahBuku;
    newNode->next = NULL;
    return newNode;
}

// Function to append a node to the linked list
void appendNode(Node** head, const char* idBuku, const char* judulBuku, const char* penulis, int jumlahBuku) {
    Node* newNode = createNode(idBuku, judulBuku, penulis, jumlahBuku);
    if (*head == NULL) {
        *head = newNode;
    } else {
        Node* temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

// Function to read data from a file and populate the linked list
void readFile(const char* filename, Node** head) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        fprintf(stderr, "Failed to open file: %s\n", filename);
        return;
    }

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        char idBuku[10], judulBuku[100], penulis[50];
        int jumlahBuku;

        if (sscanf(line, "%9[^,],%99[^,],%49[^,],%d", idBuku, judulBuku, penulis, &jumlahBuku) == 4) {
            appendNode(head, idBuku, judulBuku, penulis, jumlahBuku);
        }
    }

    fclose(file);
}

// Function to search for a node by ID
Node* searchById(Node* head, const char* id) {
    while (head != NULL) {
        if (strcmp(head->idBuku, id) == 0) {
            return head;
        }
        head = head->next;
    }
    return NULL;
}

// Function to create a queue node
QueueNode* createQueueNode(const char* namaUser, const char* idBuku) {
    QueueNode* newNode = (QueueNode*)malloc(sizeof(QueueNode));
    if (!newNode) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    strncpy(newNode->namaUser, namaUser, sizeof(newNode->namaUser) - 1);
    strncpy(newNode->idBuku, idBuku, sizeof(newNode->idBuku) - 1);
    newNode->namaUser[sizeof(newNode->namaUser) - 1] = '\0';
    newNode->idBuku[sizeof(newNode->idBuku) - 1] = '\0';
    newNode->next = NULL;
    return newNode;
}

// Function to initialize the queue
void initQueue(Queue* q) {
    q->count = 0;
    q->front = NULL;
    q->rear = NULL;
}

// Function to enqueue a node
void enqueue(Queue* q, const char* namaUser, const char* idBuku) {
    QueueNode* newNode = createQueueNode(namaUser, idBuku);
    if (q->rear == NULL) {
        q->front = q->rear = newNode;
    } else {
        q->rear->next = newNode;
        q->rear = newNode;
    }
    q->count++;
}

// Function to dequeue a node
QueueNode* dequeue(Queue* q) {
    if (q->front == NULL) {
        return NULL;
    }
    QueueNode* temp = q->front;
    q->front = q->front->next;
    if (q->front == NULL) {
        q->rear = NULL;
    }
    q->count--;
    return temp;
}

// Function to free the queue
void freeQueue(Queue* q) {
    while (q->front != NULL) {
        QueueNode* temp = dequeue(q);
        free(temp);
    }
}

// Function to return a book
void returnBook(Queue* q, Node* bookList) {
    if (q->front == NULL) {
        printf("No borrow records available.\n");
        return;
    }

    QueueNode* returnedNode = dequeue(q);
    if (returnedNode) {
        Node* book = searchById(bookList, returnedNode->idBuku);
        if (book) {
            book->jumlahBuku++;
            printf("Book %s (%s) has been returned by %s.\n", returnedNode->idBuku, book->judulBuku, returnedNode->namaUser);
        } else {
            printf("Book with ID %s not found in the list.\n", returnedNode->idBuku);
        }
        free(returnedNode);
    }
}

int main() {
    Node* bookList = NULL;
    Queue borrowQueue;
    initQueue(&borrowQueue);

    // Load books from a file
    const char* filename = "data.csv";
    readFile(filename, &bookList);

    int choice;
    char namaUser[50];
    char idBuku[10];

    while (1) {
        printf("\nMenu:\n");
        printf("1. Show all books\n");
        printf("2. Borrow book\n");
        printf("3. Return book\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter a number.\n");
            while (getchar() != '\n'); // Clear input buffer
            continue;
        }

        switch (choice) {
            case 1: {
                // Display all books
                if (bookList == NULL) {
                    printf("No books available in the library.\n");
                } else {
                    printf("\nList of Available Books:\n");
                    printf("-----------------------------------------------------------\n");
                    printf("ID Buku        Judul Buku                           Penulis           Jumlah Buku\n");
                    printf("-----------------------------------------------------------\n");
                    Node* temp = bookList;
                    while (temp != NULL) {
                        printf("%-12s %-35s %-15s %d\n", temp->idBuku, temp->judulBuku, temp->penulis, temp->jumlahBuku);
                        temp = temp->next;
                    }
                    printf("-----------------------------------------------------------\n");
                }
                break;
            }
            case 2: {
                // Borrow a book
                printf("Enter your name: ");
                scanf(" %[^\n]", namaUser);
                printf("Enter the ID of the book to borrow: ");
                scanf("%s", idBuku);

                Node* book = searchById(bookList, idBuku);
                if (book == NULL) {
                    printf("Book with ID %s not found.\n", idBuku);
                } else if (book->jumlahBuku <= 0) {
                    printf("Book %s is out of stock.\n", book->judulBuku);
                } else {
                    enqueue(&borrowQueue, namaUser, idBuku);
                    book->jumlahBuku--;
                    printf("Book %s has been borrowed by %s.\n", book->judulBuku, namaUser);
                }
                break;
            }
            case 3: {
                // Return a book
                returnBook(&borrowQueue, bookList);
                break;
            }
            case 4: {
                // Exit the program
                printf("Exiting program. Freeing memory...\n");
                freeQueue(&borrowQueue);
                Node* temp;
                while (bookList != NULL) {
                    temp = bookList;
                    bookList = bookList->next;
                    free(temp);
                }
                return 0;
            }
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
}
