#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Struktur Buku untuk Single Linked List
typedef struct Buku
{
    char id[10];
    char judul[45];
    char penulis[20];
    int jumlah;
    struct Buku *next;
} Buku;

// Fungsi untuk membuat node buku baru
Buku *buatBuku(char *id, char *judul, char *penulis, int jumlah)
{
    Buku *newBuku = (Buku *)malloc(sizeof(Buku));
    strcpy(newBuku->id, id);
    strcpy(newBuku->judul, judul);
    strcpy(newBuku->penulis, penulis);
    newBuku->jumlah = jumlah;
    newBuku->next = NULL;
    return newBuku;
}

// Fungsi untuk menambahkan buku ke linked list
void tambahBuku(Buku **head, char *id, char *judul, char *penulis, int jumlah)
{
    Buku *newBuku = buatBuku(id, judul, penulis, jumlah);
    if (*head == NULL)
    {
        *head = newBuku;
    }
    else
    {
        Buku *temp = *head;
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = newBuku;
    }
}

// Fungsi untuk membaca data buku dari file CSV
void bacaCSV(Buku **head, const char *namaFile)
{
    FILE *file = fopen(namaFile, "r");
    if (!file)
    {
        printf("File tidak ditemukan.\n");
        return;
    }

    char buffer[128];
    fgets(buffer, sizeof(buffer), file); // Membaca header dan melewatinya

    while (fgets(buffer, sizeof(buffer), file))
    {
        char id[10], judul[45], penulis[20];
        int jumlah;

        // Menghapus tanda kutip dan memparsing data
        sscanf(buffer, "\"%[^\"]\",\"%[^\"]\",\"%[^\"]\",\"%d\"", id, judul, penulis, &jumlah);
        tambahBuku(head, id, judul, penulis, jumlah);
    }

    fclose(file);
}

// Fungsi untuk mencetak semua buku di linked list
void cetakBuku(Buku *head)
{
    if (head == NULL)
    {
        printf("Tidak ada buku dalam daftar.\n");
        return;
    }

    Buku *temp = head;
    printf("Daftar Buku:\n");
    while (temp != NULL)
    {
        printf("ID: %s, Judul: %s, Penulis: %s, Jumlah: %d\n",
               temp->id, temp->judul, temp->penulis, temp->jumlah);
        temp = temp->next;
    }
}

// Fungsi utama
int main()
{
    Buku *daftarBuku = NULL; // Inisialisasi linked list kosong

    // Membaca data buku dari file CSV
    bacaCSV(&daftarBuku, "C:\\path\\ke\\data perpus.csv");

    // Menampilkan daftar buku
    cetakBuku(daftarBuku);

    return 0;
}
