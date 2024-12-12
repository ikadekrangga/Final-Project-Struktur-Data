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

// Function to create a new node
Node* createNode(const char* idBuku, const char* judulBuku, const char* penulis, int jumlahBuku) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    strncpy(newNode->idBuku, idBuku, 10);
    strncpy(newNode->judulBuku, judulBuku, 100);
    strncpy(newNode->penulis, penulis, 50);
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
        exit(1);
    }

    char line[256];
    int isFirstLine = 1; // Skip the header line
    while (fgets(line, sizeof(line), file)) {
        if (isFirstLine) {
            isFirstLine = 0;
            continue;
        }

        char idBuku[10];
        char judulBuku[100];
        char penulis[50];
        int jumlahBuku;

        // Parse the line using sscanf
        if (sscanf(line, "%9[^,],%99[^,],%49[^,],%d", idBuku, judulBuku, penulis, &jumlahBuku) == 4) {
            appendNode(head, idBuku, judulBuku, penulis, jumlahBuku);
        } else {
            fprintf(stderr, "Malformed line: %s\n", line);
        }
    }

    fclose(file);
}

// Function to search for a node by ID
Node* searchById(Node* head, const char* id) {
    while (head != NULL) {
        if (strcmp(head->idBuku, id) == 0) {
            return head; // Return the node if found
        }
        head = head->next; // Move to the next node
    }
    return NULL; // Return NULL if not found
}

// Function to display a single record (takes a Node pointer as input)
void displayRecord(Node* node) {
    if (node == NULL) {
        printf("Record not found.\n");
        return;
    }

    printf("-----------------------------------------------------------\n");
    printf("ID Buku        Judul Buku                           Penulis           Jumlah Buku\n");
    printf("-----------------------------------------------------------\n");
    printf("%-12s %-35s %-15s %d\n", node->idBuku, node->judulBuku, node->penulis, node->jumlahBuku);
    printf("-----------------------------------------------------------\n");
}

// Function to display the linked list
void displayList(Node* head) {
    if (head == NULL) {
        printf("The list is empty.\n");
        return;
    }

    printf("-----------------------------------------------------------\n");
    printf("ID Buku        Judul Buku                           Penulis           Jumlah Buku\n");
    printf("-----------------------------------------------------------\n");

    Node* temp = head;
    while (temp != NULL) {
        printf("%-12s %-35s %-15s %d\n", temp->idBuku, temp->judulBuku, temp->penulis, temp->jumlahBuku);
        temp = temp->next;
    }
    printf("-----------------------------------------------------------\n");
}

// Function to free the linked list
void freeList(Node* head) {
    Node* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

int main() {
    Node* head = NULL;
    const char* filename = "data.csv";

    // Read the file and populate the linked list
    readFile(filename, &head);

    int choice;
    char id[10];

    while (1) {
        printf("\nMenu:\n");
        printf("1. Show all data\n");
        printf("2. Show data by ID\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Contents of the linked list:\n");
                displayList(head);
                break;
            case 2:
                printf("Enter ID to search: ");
                scanf("%s", id);
                Node* foundNode = searchById(head, id);
                displayRecord(foundNode);
                break;
            case 3:
                freeList(head);
                printf("Exiting...\n");
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
}
