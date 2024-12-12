#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Struktur untuk node double linked list
typedef struct RiwayatNode {
    char nama_user[50];
    char id_buku[20];
    struct RiwayatNode *prev;
    struct RiwayatNode *next;
} RiwayatNode;

// Struktur untuk menyimpan head dan tail dari double linked list
typedef struct {
    RiwayatNode *head;
    RiwayatNode *tail;
} Riwayat;

// Struktur untuk queue peminjaman
typedef struct Peminjam {
    char nama_user[50];
    char id_buku[20];
    struct Peminjam *next;
} Peminjam;

typedef struct {
    Peminjam *front;
    Peminjam *rear;
} Queue;

// Fungsi untuk inisialisasi queue
void initQueue(Queue *queue) {
    queue->front = NULL;
    queue->rear = NULL;
}

// Fungsi untuk enqueue (menambahkan peminjam ke dalam queue)
void enqueue(Queue *queue, const char *nama_user, const char *id_buku) {
    Peminjam *nodeBaru = (Peminjam *)malloc(sizeof(Peminjam));
    strcpy(nodeBaru->nama_user, nama_user);
    strcpy(nodeBaru->id_buku, id_buku);
    nodeBaru->next = NULL;

    if (queue->rear == NULL) {
        queue->front = nodeBaru;
        queue->rear = nodeBaru;
    } else {
        queue->rear->next = nodeBaru;
        queue->rear = nodeBaru;
    }
}

// Fungsi untuk dequeue (menghapus peminjam dari queue)
Peminjam *dequeue(Queue *queue) {
    if (queue->front == NULL) {
        return NULL;
    }

    Peminjam *nodeDihapus = queue->front;
    queue->front = queue->front->next;

    if (queue->front == NULL) {
        queue->rear = NULL;
    }

    return nodeDihapus;
}

// Fungsi untuk inisialisasi riwayat
void initRiwayat(Riwayat *riwayat) {
    riwayat->head = NULL;
    riwayat->tail = NULL;
}

// Fungsi untuk menambahkan riwayat peminjaman ke dalam double linked list
void tambahRiwayat(Riwayat *riwayat, const char *nama_user, const char *id_buku) {
    RiwayatNode *nodeBaru = (RiwayatNode *)malloc(sizeof(RiwayatNode));
    strcpy(nodeBaru->nama_user, nama_user);
    strcpy(nodeBaru->id_buku, id_buku);
    nodeBaru->prev = NULL;
    nodeBaru->next = NULL;

    if (riwayat->head == NULL) {
        riwayat->head = nodeBaru;
        riwayat->tail = nodeBaru;
    } else {
        riwayat->tail->next = nodeBaru;
        nodeBaru->prev = riwayat->tail;
        riwayat->tail = nodeBaru;
    }
}

// Fungsi untuk memindahkan data dari queue ke riwayat
void pindahkanQueueKeRiwayat(Queue *queue, Riwayat *riwayat) {
    Peminjam *peminjam;
    while ((peminjam = dequeue(queue)) != NULL) {
        tambahRiwayat(riwayat, peminjam->nama_user, peminjam->id_buku);
        free(peminjam);
    }
}

// Fungsi untuk menampilkan semua riwayat peminjaman
void tampilkanRiwayat(Riwayat *riwayat) {
    RiwayatNode *current = riwayat->head;
    if (current == NULL) {
        printf("Tidak ada riwayat peminjaman.\n");
        return;
    }

    printf("Riwayat Peminjaman:\n");
    while (current != NULL) {
        printf("Nama User: %s, ID Buku: %s\n", current->nama_user, current->id_buku);
        current = current->next;
    }
}

// Fungsi untuk mencari siapa yang meminjam buku berdasarkan ID buku
void cariPeminjamBuku(Riwayat *riwayat, const char *id_buku) {
    RiwayatNode *current = riwayat->head;
    int ditemukan = 0;

    while (current != NULL) {
        if (strcmp(current->id_buku, id_buku) == 0) {
            printf("Buku dengan ID %s telah dipinjam oleh: %s\n", id_buku, current->nama_user);
            ditemukan = 1;
        }
        current = current->next;
    }

    if (!ditemukan) {
        printf("Buku dengan ID %s belum pernah dipinjam.\n", id_buku);
    }
}

int main() {
    Riwayat riwayat;
    Queue queue;

    initRiwayat(&riwayat);
    initQueue(&queue);


    return 0;
}
