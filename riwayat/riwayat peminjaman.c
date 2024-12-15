#include <stdio.h>
#include <string.h>

#define MAX_NAME_LENGTH 50

// Fungsi untuk menampilkan seluruh riwayat peminjaman
void tampilkanRiwayat()
{
    FILE *file = fopen("user_list.csv", "r"); // Buka file untuk membaca
    if (file == NULL)
    {
        printf("Gagal membuka file user_list.csv\n");
        return;
    }

    char nama[50];
    int id_buku;

    printf("Riwayat Peminjaman:\n");
    // Membaca setiap baris dalam file dan menampilkan data
    while (fscanf(file, "%49[^,], %d\n", nama, &id_buku) == 2)
    {
        printf("Nama: %s, ID Buku: %d\n", nama, id_buku);
    }

    fclose(file); // Tutup file setelah selesai membaca
}

// Fungsi untuk mencari ID buku berdasarkan nama pengguna
int cariIDBuku(const char *nama_user)
{
    FILE *file = fopen("user_list.csv", "r"); // Buka file untuk membaca
    if (file == NULL)
    {
        printf("Gagal membuka file user_list.csv\n");
        return -1; // Return -1 jika file tidak ditemukan
    }

    char nama[50];
    int id_buku;
    // Membaca setiap baris dalam file
    while (fscanf(file, "%49[^,], %d\n", nama, &id_buku) == 2)
    {
        if (strcmp(nama, nama_user) == 0)
        {                 // Jika nama ditemukan
            fclose(file); // Tutup file sebelum return
            return id_buku;
        }
    }

    fclose(file); // Tutup file jika nama tidak ditemukan
    return -1;    // Return -1 jika nama tidak ditemukan
}

int main()
{
    int pilihan;
    char nama_user[MAX_NAME_LENGTH];

    // Menu Pilihan
    do
    {
        printf("\nMenu:\n");
        printf("1. Tampilkan seluruh riwayat peminjaman\n");
        printf("2. Cari ID buku berdasarkan nama pengguna\n");
        printf("3. Keluar\n");
        printf("Pilih menu (1-3): ");
        scanf("%d", &pilihan);
        getchar(); // Mengambil karakter newline setelah input pilihan

        switch (pilihan)
        {
        case 1:
            tampilkanRiwayat();
            break;

        case 2:
            printf("Masukkan nama pengguna untuk mencari ID buku: ");
            fgets(nama_user, sizeof(nama_user), stdin);
            nama_user[strcspn(nama_user, "\n")] = 0; // Menghapus newline karakter jika ada

            int id_buku = cariIDBuku(nama_user);
            if (id_buku == -1)
            {
                printf("Nama pengguna tidak ditemukan dalam riwayat peminjaman.\n");
            }
            else
            {
                printf("ID Buku yang dipinjam oleh %s adalah: %d\n", nama_user, id_buku);
            }
            break;

        case 3:
            printf("Terima kasih! Program selesai.\n");
            break;

        default:
            printf("Pilihan tidak valid! Silakan pilih antara 1-3.\n");
            break;
        }
    } while (pilihan != 3);

    return 0;
}
