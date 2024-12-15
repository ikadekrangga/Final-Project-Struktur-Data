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

int main() {
    char nama_user[50];
    int id_buku;
    int stock = 5; // Contoh stock buku
    queue antrian;
    initqueue(&antrian);

    printf("Nama user: ");
    fgets(nama_user, sizeof(nama_user), stdin);



    nama_user[strcspn(nama_user, "\n")] = 0; // Remove newline character

    printf("ID buku yang mau dipinjam: ");
    scanf("%d", &id_buku);

        FILE *file = fopen("user_list.csv", "a");
    if (file == NULL) {
        printf("Error opening file!\n");
        return 1;
    }
    fprintf(file, "%s, %d\n", nama_user, id_buku);
    fclose(file);

    if (stock <= 0) {
        printf("Buku tidak ada\n");
    } else {
        enqueue(&antrian, nama_user, id_buku); // Pemanggilan fungsi yang benar
        stock--;
    }

    printf("Antrian peminjaman: %d. %s\n",antrian.count, antrian.front->nama_user);
    return 0;
}
