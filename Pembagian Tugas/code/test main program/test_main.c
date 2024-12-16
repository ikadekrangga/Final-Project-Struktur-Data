#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//-----------------------------------------------------------------------------------------------------------

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

typedef struct nodee {
    struct nodee *next;
    struct nodee *prev;
    char nama_user[80];
    int id_buku;
} nodee;

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

void dequeue(queue *q) {
    if (q->front == NULL) {
        printf("Antrian kosong!\n");
        return;
    }

    node *temp = q->front;
    q->front = q->front->next;

    if (q->front == NULL) {
        q->rear = NULL;
    }

    free(temp);
    q->count--;
}

// Global queue instance
queue antrian;
int stock = 5; // Example stock for books

// Cari Data -----------------------------------------------------------------------------------------------------------

typedef struct find_node {
    char idBuku[10];
    char judulBuku[100];
    char penulis[50];
    int jumlahBuku;
    struct find_node* next;
} find_node;

find_node* createfind_node(const char* idBuku, const char* judulBuku, const char* penulis, int jumlahBuku) {
    find_node* newfind_node = (find_node*)malloc(sizeof(find_node));
    if (!newfind_node) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    strncpy(newfind_node->idBuku, idBuku, 10);
    strncpy(newfind_node->judulBuku, judulBuku, 100);
    strncpy(newfind_node->penulis, penulis, 50);
    newfind_node->jumlahBuku = jumlahBuku;
    newfind_node->next = NULL;
    return newfind_node;
}

void appendfind_node(find_node** head, const char* idBuku, const char* judulBuku, const char* penulis, int jumlahBuku) {
    find_node* newfind_node = createfind_node(idBuku, judulBuku, penulis, jumlahBuku);
    if (*head == NULL) {
        *head = newfind_node;
    } else {
        find_node* temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newfind_node;
    }
}

void readFile(const char* filename, find_node** head) {
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
            appendfind_node(head, idBuku, judulBuku, penulis, jumlahBuku);
        } else {
            fprintf(stderr, "Warning: Baris Bermasalah, Tolong Check Format CSV: %s\n", line);
        }
    }

    fclose(file);
}

find_node* searchById(find_node* head, const char* id) {
    while (head != NULL) {
        if (strcmp(head->idBuku, id) == 0) {
            return head; 
        }
        head = head->next; 
    }
    return NULL; 
}

void displayRecord(find_node* find_node) {
    if (find_node == NULL) {
        printf("Record Tidak Ditemukan\n");
        return;
    }

    printf("---------------------------------------------------------------------------------\n");
    printf("ID Buku        Judul Buku                           Penulis           Jumlah Buku\n");
    printf("---------------------------------------------------------------------------------\n");
    printf("%-12s %-35s %-15s ", find_node->idBuku, find_node->judulBuku, find_node->penulis);
    if (find_node->jumlahBuku == 0) {
        printf("Stok Buku Kosong\n");
    } else {
        printf("%d\n", find_node->jumlahBuku);
    }
    printf("---------------------------------------------------------------------------------\n\n");
}

void displayList(find_node* head) {
    if (head == NULL) {
        printf("The list is empty.\n");
        return;
    }

    printf("---------------------------------------------------------------------------------\n");
    printf("ID Buku        Judul Buku                           Penulis           Jumlah Buku\n");
    printf("---------------------------------------------------------------------------------\n");

    find_node* temp = head;
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

void freeList(find_node* head) {
    find_node* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

//-----------------------------------------------------------------------------------------------------------

void option2(find_node *head) {
    if (head == NULL) {
        printf("Tidak ada buku dalam daftar.\n");
        return;
    }

    printf("Daftar Buku yang Tersedia:\n");
    printf("---------------------------------------------------------------------------------\n");
    printf("ID Buku        Judul Buku                           Penulis           Jumlah Buku\n");
    printf("---------------------------------------------------------------------------------\n");

    find_node *temp = head;
    while (temp != NULL) {
        if (temp->jumlahBuku > 0) { // Hanya menampilkan buku yang tersedia
            printf("%-12s %-35s %-15s %d\n", temp->idBuku, temp->judulBuku, temp->penulis, temp->jumlahBuku);
        }
        temp = temp->next;
    }
    printf("---------------------------------------------------------------------------------\n");
}

//-----------------------------------------------------------------------------------------------------------

void option3() {
    char nama_user[50];
    int id_buku;

    printf("Nama user: ");
    getchar(); // Consume newline from the previous input
    fgets(nama_user, sizeof(nama_user), stdin);
    nama_user[strcspn(nama_user, "\n")] = 0; // Remove newline character

    printf("ID buku yang mau dipinjam: ");
    scanf("%d", &id_buku);

    // Append to file
    FILE *file = fopen("user_list.csv", "a");
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }
    fprintf(file, "%s, %d\n", nama_user, id_buku);
    fclose(file);

    if (stock <= 0) {
        printf("Buku tidak ada\n");
    } else {
        enqueue(&antrian, nama_user, id_buku);
        stock--;
        printf("Buku berhasil dipinjam oleh %s (ID Buku: %d). Stock tersisa: %d\n", nama_user, id_buku, stock);
    }

    if (antrian.front != NULL) {
        printf("Antrian peminjaman: %d. User pertama: %s\n", antrian.count, antrian.front->nama_user);
    }
}

//-----------------------------------------------------------------------------------------------------------

// Option4: Menampilkan seluruh antrian peminjaman
void option4(queue *q) {
    if (q->count == 0) {
        printf("Antrian kosong.\n");
        return;
    }

    printf("Daftar Antrian Peminjaman:\n");
    printf("---------------------------------------------------------------------------------\n");
    printf("Nama Pengguna                           ID Buku\n");
    printf("---------------------------------------------------------------------------------\n");

    node *current = q->front;
    while (current != NULL) {
        printf("%-40s %d\n", current->nama_user, current->id_buku);
        current = current->next;
    }
    printf("---------------------------------------------------------------------------------\n");
    printf("Total antrian: %d\n", q->count);
}

//-----------------------------------------------------------------------------------------------------------

void tampilkanRiwayat(nodee *head) {
    if (head == NULL) {
        printf("Riwayat peminjaman kosong.\n");
        return;
    }

    printf("Riwayat Peminjaman:\n");
    nodee *current = head;
    while (current != NULL) {
        printf("Nama: %s, ID Buku: %d\n", current->nama_user, current->id_buku);
        current = current->next;
    }
}

void tambahRiwayat(nodee **head, const char *nama_user, int id_buku) {
    nodee *newNode = (nodee *)malloc(sizeof(nodee));
    if (newNode == NULL) {
        printf("Alokasi memori gagal!\n");
        return;
    }
    strcpy(newNode->nama_user, nama_user);
    newNode->id_buku = id_buku;
    newNode->next = NULL;
    newNode->prev = NULL;

    if (*head == NULL) {
        *head = newNode;
    } else {
        nodee *temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode;
        newNode->prev = temp;
    }
}

void option3(nodee **riwayat) {
    char nama_user[50];
    int id_buku;

    printf("Nama user: ");
    getchar(); // Consume newline from the previous input
    fgets(nama_user, sizeof(nama_user), stdin);
    nama_user[strcspn(nama_user, "\n")] = 0; // Remove newline character

    printf("ID buku yang mau dipinjam: ");
    scanf("%d", &id_buku);

    // Append to file
    FILE *file = fopen("user_list.csv", "a");
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }
    fprintf(file, "%s, %d\n", nama_user, id_buku);
    fclose(file);

    if (stock <= 0) {
        printf("Buku tidak ada\n");
    } else {
        enqueue(&antrian, nama_user, id_buku);
        stock--;
        printf("Buku berhasil dipinjam oleh %s (ID Buku: %d). Stock tersisa: %d\n", nama_user, id_buku, stock);

        // Tambahkan ke riwayat
        tambahRiwayat(riwayat, nama_user, id_buku);
    }

    if (antrian.front != NULL) {
        printf("Antrian peminjaman: %d. User pertama: %s\n", antrian.count, antrian.front->nama_user);
    }
}

void pengembalianBuku(queue *q, find_node *bookList) {
    if (q->front == NULL) {
        printf("Tidak ada buku yang sedang dipinjam.\n");
        return;
    }

    char nama_user[50];
    int id_buku;

    printf("Nama user yang mengembalikan: ");
    getchar(); // Consume newline from the previous input
    fgets(nama_user, sizeof(nama_user), stdin);
    nama_user[strcspn(nama_user, "\n")] = 0; // Remove newline character

    printf("ID buku yang dikembalikan: ");
    scanf("%d", &id_buku);

    // Cari buku berdasarkan ID
    find_node *book = bookList;
    while (book != NULL) {
        if (atoi(book->idBuku) == id_buku) {
            book->jumlahBuku++;
            printf("Buku dengan ID %d berhasil dikembalikan. Stock sekarang: %d\n", id_buku, book->jumlahBuku);

            // Hapus dari antrian peminjaman jika ditemukan
            node *prev = NULL;
            node *current = q->front;
            while (current != NULL) {
                if (strcmp(current->nama_user, nama_user) == 0 && current->id_buku == id_buku) {
                    if (prev == NULL) {
                        q->front = current->next; // Hapus dari front
                    } else {
                        prev->next = current->next; // Hapus node tengah/akhir
                    }

                    if (current == q->rear) {
                        q->rear = prev; // Update rear jika elemen terakhir dihapus
                    }

                    free(current);
                    q->count--;
                    printf("Antrian peminjaman diperbarui.\n");
                    return;
                }
                prev = current;
                current = current->next;
            }
            printf("Data peminjaman tidak ditemukan dalam antrian.\n");
            return;
        }
        book = book->next;
    }

    printf("ID Buku tidak ditemukan dalam daftar buku.\n");
}

int main() {
    find_node *bookList = NULL;
    nodee *riwayatPeminjaman = NULL;

    // Baca data buku dari file
    readFile("data.csv", &bookList);

    // Inisialisasi antrian
    initqueue(&antrian);

    int pilihan;
    do {
        system("cls"); // Clear screen di awal menu utama
        printf("\nMenu Perpustakaan:\n");
        printf("1. Cari Buku\n");
        printf("2. Tampilkan Daftar Buku Tersedia\n");
        printf("3. Pinjam Buku\n");
        printf("4. Tampilkan Antrian Peminjaman\n");
        printf("5. Tampilkan Riwayat Peminjaman\n");
        printf("6. Kembalikan Buku\n");
        printf("7. Keluar\n");
        printf("Pilihan Anda: ");
        fflush(stdin);
        scanf("%d", &pilihan);

        switch (pilihan) {
            case 1: {
                system("cls"); // Clear screen untuk menu Cari Buku
                char id[10];
                printf("Masukkan ID Buku: ");
                scanf("%s", id);
                find_node *result = searchById(bookList, id);
                displayRecord(result);
                break;
            }
            case 2:
                system("cls"); // Clear screen untuk menu Tampilkan Daftar Buku Tersedia
                option2(bookList);
                break;
            case 3:
                system("cls"); // Clear screen untuk menu Pinjam Buku
                option3(&riwayatPeminjaman);
                break;
            case 4:
                system("cls"); // Clear screen untuk menu Tampilkan Antrian Peminjaman
                option4(&antrian);
                break;
            case 5:
                system("cls"); // Clear screen untuk menu Tampilkan Riwayat Peminjaman
                tampilkanRiwayat(riwayatPeminjaman);
                break;
            case 6:
                system("cls"); // Clear screen untuk menu Kembalikan Buku
                pengembalianBuku(&antrian, bookList);
                break;
            case 7:
                system("cls"); // Clear screen sebelum keluar
                printf("Terima kasih telah menggunakan sistem perpustakaan.\n");
                break;
            default:
                system("cls"); // Clear screen untuk input tidak valid
                printf("Pilihan tidak valid. Silakan coba lagi.\n");
        }
        if (pilihan != 7) {
            printf("\nTekan Enter untuk kembali ke menu utama...");
            getchar();
            getchar(); // Pause untuk menunggu input sebelum kembali ke menu
        }
    } while (pilihan != 7);

    // Bebaskan memori
    freeList(bookList);
    while (antrian.count > 0) {
        dequeue(&antrian);
    }
    while (riwayatPeminjaman != NULL) {
        nodee *temp = riwayatPeminjaman;
        riwayatPeminjaman = riwayatPeminjaman->next;
        free(temp);
    }

    return 0;
}
