#include <stdio.h>
#include <string.h>

int main() {
    char nama_user[50];
    int id_buku;
    int stock = 5; // Contoh stock buku
    int queue = 1; // Contoh antrian peminjaman

    printf("Nama user: ");
    fgets(nama_user, sizeof(nama_user), stdin);
        FILE *file = fopen("user_list.txt", "a");
            if (file == NULL) {
                printf("Error opening file!\n");
                return 1;
        }
            fprintf(file, "%s\n", nama_user);
        fclose(file);
        
    nama_user[strcspn(nama_user, "\n")] = 0; // Remove newline character

    printf("ID buku yang mau dipinjam: ");
    scanf("%d", &id_buku);

    if (stock <= 0) {
        printf("Buku tidak ada\n");
    } else {
        printf("Antrian peminjaman: %d -> %s\n", queue, nama_user);
        stock--;
    }

    return 0;
}