#ifndef BOOK_H
#define BOOK_H

#define MAX_TITLE 100
#define MAX_AUTHOR 100
#define MAX_BOOK 100

typedef struct
{
    int id;
    char title[MAX_TITLE];
    char author[MAX_AUTHOR];
    int isBorrowed;
} 
Book_t;

void addBook(Book_t books[], int *bookCount);
void removeBook(Book_t books[], int *bookCount, int id);
void listBooks(Book_t books[], int bookCount);
Book_t* findBookById(Book_t books[], int bookCount, int Id);

#endif
