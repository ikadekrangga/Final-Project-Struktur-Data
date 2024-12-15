#include <stdio.h>
#include <stdlib.h>

void option1() {
    printf("Option 1 selected.\n");
    // Add your code for option 1 here
}

void option2() {
    printf("Option 2 selected.\n");
    // Add your code for option 2 here
}

void option3() {
    printf("Option 3 selected.\n");
    // Add your code for option 3 here
}

void option4() {
    printf("Option 4 selected.\n");
    // Add your code for option 4 here
}
void option5() {
    printf("Option 5 selected.\n");
    // Add your code for option 5 here
}
void option6() {
    printf("Option 6 selected.\n");
    // Add your code for option 6 here
}

int main() {
    int choice;

    while (1) {
        printf("Menu:\n");
        printf("1. Cari buku\n");
        printf("2. Pilih buku\n");
        printf("3. Pinjam buku\n");
        printf("4. Antrian\n");
        printf("5. riwayat\n");
        printf("6. Kembalikan buku\n");
        printf("Press Q to Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                option1();
                break;
            case 2:
                option2();
                break;
            case 3:
                option3();
                break;
            case 'q':
                printf("Exiting...\n");
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}