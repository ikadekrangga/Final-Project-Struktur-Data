> [!NOTE]
> **Main Code sudah bisa di run. Jadi jika ingin push, pastikan kode tidak terdapat error untuk memudahkan pengisian menu lainnya.**

## Struktur Kode
- Untuk memudahkan, setiap deklarasi fungsi untuk menu diberikan bagiannya masing-masing. Pastikan untuk menambahkan fungsi ditempatnya masing masing. Contoh:
```
// Cari Buku -----------------------------------------------------------------------------------------------------------
void option1() {
    printf("Cari Buku.\n");
}
```
- Pada ```int main()``` juga terdapat hal yang sama. Jika butuh mendeklarasikan variabel dalam ```int main()```, pastikan untuk mendeklarasikannya di bagian yang tepat untuk memudahkan. Contoh:
```
// Cari Data --------------------------------------------------------------------------------------------------
    find_node* head = NULL;
    const char* filename = "data.csv";

    readFile(filename, &head);

    int find_choice;

    char id[10];
```
