#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct Node
{
    char nama_user[50];
    char id_buku[10];
    struct Node *left;
    struct Node *right;
} Node;

void tambahRiwayat(Node **head, Node **tail, const char *nama, const char *id)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (!newNode)
    {
        printf("Gagal alokasi memori!\n");
        return;
    }

    strcpy(newNode->nama_user, nama);
    strcpy(newNode->id_buku, id);
    newNode->right = NULL;
    newNode->left = *tail;

    if (*tail != NULL)
    {
        (*tail)->right = newNode;
    }
    *tail = newNode;

    if (*head == NULL)
    {
        *head = newNode;
    }
}

void tampilkanRiwayat(Node *head)
{
    if (head == NULL)
    {
        printf("Riwayat peminjaman kosong.\n");
        return;
    }

    printf("---------------------------------------------------\n");
    printf("Nama Pengguna                 ID Buku\n");
    printf("---------------------------------------------------\n");

    Node *current = head;
    while (current != NULL)
    {
        // Menampilkan nama dan ID buku
        printf("%-30s %-10s\n", current->nama_user, current->id_buku);
        current = current->right;
    }
}

const char *cariIDBuku(Node *head, const char *nama)
{
    Node *current = head;
    while (current != NULL)
    {
        if (strcmp(current->nama_user, nama) == 0)
        {
            return current->id_buku;
        }
        current = current->right;
    }
    return NULL;
}

void loadRiwayat(Node **head, Node **tail)
{
    FILE *file = fopen("user_list.csv", "r");
    if (file == NULL)
    {
        printf("Gagal membuka file user_list.csv\n");
        return;
    }

    char nama[50];
    char id_buku_temp[10];

    while (fscanf(file, " %50[^,],%9s\n", nama, id_buku_temp) == 2)
    {
        tambahRiwayat(head, tail, nama, id_buku_temp);
    }

    fclose(file);
}

void freeList(Node *head)
{
    Node *current = head;
    while (current != NULL)
    {
        Node *temp = current;
        current = current->right;
        free(temp);
    }
}

int main()
{
    Node *head = NULL;
    Node *tail = NULL;

    // Memuat riwayat peminjaman dari file CSV
    loadRiwayat(&head, &tail);

    int pilihan;
    char input_nama[50];
    const char *id_buku_result = NULL;

    while (1)
    {
        printf("\nMenu Riwayat:\n");
        printf("1. Tampilkan seluruh riwayat peminjaman\n");
        printf("2. Cari ID buku berdasarkan nama pengguna\n");
        printf("3. Keluar\n");
        printf("Masukkan pilihan (1-3): ");
        scanf("%d", &pilihan);
        getchar();

        switch (pilihan)
        {
        case 1:
            tampilkanRiwayat(head);
            break;

        case 2:
            printf("Masukkan nama pengguna untuk mencari ID buku: ");
            fgets(input_nama, sizeof(input_nama), stdin);
            input_nama[strcspn(input_nama, "\n")] = 0;
            id_buku_result = cariIDBuku(head, input_nama);

            if (id_buku_result == NULL)
            {
                printf("Nama pengguna tidak ditemukan dalam riwayat peminjaman.\n");
            }
            else
            {
                printf("ID Buku yang dipinjam oleh %s adalah: %s\n", input_nama, id_buku_result);
            }
            break;

        case 3:
            freeList(head);
            printf("Keluar dari program.\n");
            return 0;

        default:
            printf("Pilihan tidak valid! Kembali ke menu utama.\n");
            break;
        }
    }
}
