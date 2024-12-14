#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char idBuku[10];
    char judulBuku[100];
    char penulis[50];
    int jumlahBuku;
    struct Node* next;
} Node;

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

void readFile(const char* filename, Node** head) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        fprintf(stderr, "Gagal Membuka File: %s\n", filename);
        exit(1);
    }

    char line[256];
    int isFirstLine = 1; 
    while (fgets(line, sizeof(line), file)) {
        if (isFirstLine) {
            isFirstLine = 0;
            continue;
        }

        char idBuku[10];
        char judulBuku[100];
        char penulis[50];
        int jumlahBuku;

        if (sscanf(line, "%9[^,],%99[^,],%49[^,],%d", idBuku, judulBuku, penulis, &jumlahBuku) == 4) {
            appendNode(head, idBuku, judulBuku, penulis, jumlahBuku);
        } else {
            fprintf(stderr, "Warning: Baris Bermasalah, Tolong Check Format CSV: %s\n", line);
        }
    }

    fclose(file);
}

Node* searchById(Node* head, const char* id) {
    while (head != NULL) {
        if (strcmp(head->idBuku, id) == 0) {
            return head; 
        }
        head = head->next; 
    }
    return NULL; 
}

void displayRecord(Node* node) {
    if (node == NULL) {
        printf("Record Tidak Ditemukan\n");
        return;
    }

    printf("---------------------------------------------------------------------------------\n");
    printf("ID Buku        Judul Buku                           Penulis           Jumlah Buku\n");
    printf("---------------------------------------------------------------------------------\n");
    printf("%-12s %-35s %-15s ", node->idBuku, node->judulBuku, node->penulis);
    if (node->jumlahBuku == 0) {
        printf("Stok Buku Kosong\n");
    } else {
        printf("%d\n", node->jumlahBuku);
    }
    printf("---------------------------------------------------------------------------------\n\n");
}

void displayList(Node* head) {
    if (head == NULL) {
        printf("The list is empty.\n");
        return;
    }

    printf("---------------------------------------------------------------------------------\n");
    printf("ID Buku        Judul Buku                           Penulis           Jumlah Buku\n");
    printf("---------------------------------------------------------------------------------\n");

    Node* temp = head;
    while (temp != NULL) {
        printf("%-12s %-35s %-15s ", temp->idBuku, temp->judulBuku, temp->penulis);
        if (temp->jumlahBuku == 0) {
            printf("Stok Buku Kosong\n");
        } else {
            printf("%d\n", temp->jumlahBuku);
        }
        temp = temp->next;
    }
    printf("---------------------------------------------------------------------------------\n");
}

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

    readFile(filename, &head);

    int choice;
    char id[10];

    while (1) {
    	printf("-------------------------");
        printf("\n         Menu:         \n");
        printf("-------------------------\n");
        printf("1. Tampilkan Semua Buku\n");
        printf("2. Cari Buku\n");
        printf("3. Keluar\n");
        printf("-------------------------\n");
        printf("Tips: \nEdit Data.csv Untuk Menambahkan atau Menghapus Data Buku\n");
        printf("-------------------------\n");
        printf("Masukkan Pilihan: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Data Buku:\n");
                displayList(head);
                break;
            case 2:
                printf("Masukkan ID Buku: ");
                scanf("%s", id);
                Node* foundNode = searchById(head, id);
                displayRecord(foundNode);
                break;
            case 3:
                freeList(head);
                printf("Keluar...\n");
                return 0;
            default:
                printf("Masukkan Pilihan 1, 2 Atau 3.\n");
        }
    }
}
