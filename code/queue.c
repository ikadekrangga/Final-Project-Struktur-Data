#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Book {
    char title[100];
    int available;
    struct Book *next;
} Book;

typedef struct User {
    char name[100];
    struct User *next;
    struct User *prev;
} User;

Book *readCSV(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Unable to open file");
        return NULL;
    }

    Book *head = NULL, *tail = NULL;
    char line[256];
    while (fgets(line, sizeof(line), file)) {
        Book *newBook = (Book *)malloc(sizeof(Book));
        sscanf(line, "%[^,],%d", newBook->title, &newBook->available);
        newBook->next = NULL;
        if (!head) {
            head = tail = newBook;
        } else {
            tail->next = newBook;
            tail = newBook;
        }
    }
    fclose(file);
    return head;
}

int isBookAvailable(Book *head, const char *title) {
    while (head) {
        if (strcmp(head->title, title) == 0) {
            return head->available;
        }
        head = head->next;
    }
    return 0;
}

void addUserToQueue(User **queue, const char *name) {
    User *newUser = (User *)malloc(sizeof(User));
    strcpy(newUser->name, name);
    newUser->next = NULL;
    newUser->prev = NULL;

    if (!*queue) {
        *queue = newUser;
    } else {
        User *temp = *queue;
        while (temp->next) {
            temp = temp->next;
        }
        temp->next = newUser;
        newUser->prev = temp;
    }
}

void borrowBook(User **borrowedList, const char *name) {
    User *newUser = (User *)malloc(sizeof(User));
    strcpy(newUser->name, name);
    newUser->next = NULL;
    newUser->prev = NULL;

    if (!*borrowedList) {
        *borrowedList = newUser;
    } else {
        User *temp = *borrowedList;
        while (temp->next) {
            temp = temp->next;
        }
        temp->next = newUser;
        newUser->prev = temp;
    }
}

void printBorrowedList(User *borrowedList) {
    while (borrowedList) {
        printf("%s\n", borrowedList->name);
        borrowedList = borrowedList->next;
    }
}

int main() {
    Book *bookList = readCSV("books.csv");
    if (!bookList) {
        return 1;
    }

    User *queue = NULL;
    User *borrowedList = NULL;

    char bookTitle[100];
    char userName[100];

    printf("Enter book title to borrow: ");
    scanf("%99[^\n]%*c", bookTitle);

    if (isBookAvailable(bookList, bookTitle)) {
        printf("Book is available. Enter your name: ");
        scanf("%99[^\n]%*c", userName);
        addUserToQueue(&queue, userName);
        borrowBook(&borrowedList, userName);
        printf("Book borrowed successfully!\n");
    } else {
        printf("Book is not available.\n");
    }

    printf("Borrowed List:\n");
    printBorrowedList(borrowedList);

    return 0;
}