#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct node {
    struct node *next;
    char nama_user[50];
    int id_buku;
} node;

typedef struct queue {
    int count;
    node *front;
    node *rear;
} queue;

void initqueue(queue *q) {
    q->count = 0;
    q->front = NULL;
    q->rear = NULL;
}

void enqueue(queue *q, char nama_user[50], int id_buku) {
    node *newNode = (node *)malloc(sizeof(node));
    if (newNode == NULL) {
        printf("Alokasi memori gagal!\n");
        return;
    }
    strcpy(newNode->nama_user, nama_user);
    newNode->id_buku = id_buku;
    newNode->next = NULL;

    if (q->rear == NULL) {
        q->front = q->rear = newNode;
    } else {
        q->rear->next = newNode;
        q->rear = newNode;
    }
    q->count++;
}

void displayQueue(queue *q) {
    char buffer[255];
    FILE *file = fopen("user_list.csv", "r");
    if (file == NULL) {
        printf("File error, tidak dapat ditemukan!\n");
        return;
    }
    printf("Isi File 'user_list.csv':\n");
    while (fgets(buffer, sizeof(buffer), file)) {
        printf("%s", buffer);
    }
    fclose(file);
}

int main() {
    char nama_user[50];
    int id_buku;
    int stock = 5;
    int choice;
    queue antrian;
    initqueue(&antrian);

    do {
        printf("\nMenu Peminjaman:");
        printf("\n1. Pinjam Buku");
        printf("\n2. Tampilkan antrian");
        printf("\n3. Keluar");
        printf("\nPilih menu: ");
        scanf("%d", &choice);

        // Pastikan semua inisialisasi terjadi sebelum switch-case
        switch (choice) {
            case 1:
                printf("Nama user: ");
                getchar(); // Membersihkan newline
                fgets(nama_user, sizeof(nama_user), stdin);
                nama_user[strcspn(nama_user, "\n")] = 0;

                printf("ID buku yang mau dipinjam: ");
                scanf("%d", &id_buku);

                // Membuka file di dalam case 1
                FILE *file = fopen("user_list.csv", "a");
                if (file == NULL) {
                    printf("Error opening file!\n");
                    break;
                }
                fprintf(file, "%s, %d\n", nama_user, id_buku);
                fclose(file);

                if (stock <= 0) {
                    printf("Buku tidak tersedia.\n");
                } else {
                    enqueue(&antrian, nama_user, id_buku);
                    stock--;
                    printf("Antrian peminjaman: %d. %s\n", antrian.count, antrian.front->nama_user);
                }
                break;

            case 2:
                displayQueue(&antrian);
                break;

            case 3:
                printf("Keluar dari program.\n");
                break;

            default:
                printf("Pilihan tidak valid.\n");
        }
    } while (choice != 3);

    return 0;
}
