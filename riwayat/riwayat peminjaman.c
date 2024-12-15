#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Struktur untuk queue
typedef struct Peminjam
{
    char nama_user[50];
    char id_buku[20];
    struct Peminjam *next;
} Peminjam;

typedef struct
{
    Peminjam *front;
    Peminjam *rear;
} Queue;

// Inisialisasi queue
void initQueue(Queue *queue)
{
    queue->front = NULL;
    queue->rear = NULL;
}

// Fungsi enqueue
void enqueue(Queue *queue, const char *nama_user, const char *id_buku)
{
    Peminjam *nodeBaru = (Peminjam *)malloc(sizeof(Peminjam));
    strcpy(nodeBaru->nama_user, nama_user);
    strcpy(nodeBaru->id_buku, id_buku);
    nodeBaru->next = NULL;

    if (queue->rear == NULL)
    {
        queue->front = nodeBaru;
        queue->rear = nodeBaru;
    }
    else
    {
        queue->rear->next = nodeBaru;
        queue->rear = nodeBaru;
    }
}

// Fungsi membaca data dari file CSV
void bacaCSVKeQueue(const char *filename, Queue *queue)
{
    FILE *file = fopen(filename, "r");
    if (!file)
    {
        perror("Gagal membuka file CSV");
        return;
    }

    char line[100];
    fgets(line, sizeof(line), file); // Membaca header, abaikan

    while (fgets(line, sizeof(line), file))
    {
        char nama_user[50], id_buku[20];
        sscanf(line, "%49[^,],%19[^\n]", nama_user, id_buku); // Parsing CSV
        enqueue(queue, nama_user, id_buku);
    }

    fclose(file);
    printf("Data dari file CSV berhasil dimasukkan ke dalam queue.\n");
}

// Fungsi untuk menampilkan queue
void tampilkanQueue(Queue *queue)
{
    Peminjam *current = queue->front;
    if (current == NULL)
    {
        printf("Queue kosong.\n");
        return;
    }

    printf("Data dalam queue:\n");
    while (current != NULL)
    {
        printf("Nama User: %s, ID Buku: %s\n", current->nama_user, current->id_buku);
        current = current->next;
    }
}

int main()
{
    Queue queue;
    initQueue(&queue);

    // Membaca data dari CSV ke queue
    bacaCSVKeQueue("peminjam.csv", &queue);

    // Menampilkan isi queue
    printf("\n--- Menampilkan Queue ---\n");
    tampilkanQueue(&queue);

    return 0;
}
