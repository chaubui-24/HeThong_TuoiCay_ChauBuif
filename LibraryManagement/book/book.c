#include <stdio.h>
#include <string.h>
#include "book.h"
#include "../utils/utils.h"

void addBook(Book_t books[], int *bookCount)
{
    if (*bookCount >= MAX_BOOK)
    {
        printf("Thu vien da day!\n");
        return;
    }

Book_t *b = &books[*bookCount];
b->id = *bookCount + 1;

printf("Nhap tieu de sach: ");
safeInput(b->title, MAX_TITLE);

printf("Nhap ten tac gia: ");
safeInput(b->author, MAX_AUTHOR);

b->isBorrowed = 0;
(*bookCount)++;
printf("Da them sach \"%s\" vao thu vien!\n", b->title);
}

void removeBook(Book_t books[], int *bookCount, int id)
{
    for (int i = 0; i < *bookCount; i++)
    {
        if (books[i].id == id)
        {
            for (int j = i; j < *bookCount - 1; j++)
                books[j] = books[j + 1];
            (*bookCount)--;
            printf("Da xoa sach co id %d\n", id);
            return;
        }
    }
    printf("Khong tim thay sach co ID %d\n", id);
}

void listBooks(Book_t books[], int bookCount)
{
    if (bookCount == 0)
    {
        printf("Thu vien sach trong.\n");
        return;
    }
    printf("\nDanh sach sach:\n");
    for (int i = 0; i < bookCount; i++)
    {
        printf("[%d] %s - %s [%s]\n",
            books[i].id, books[i].title, books[i].author,
            books[i].isBorrowed ? "Da muon" : "Con trong");
    }
}

Book_t* findBookById(Book_t books[], int bookCount, int id)
{
    for (int i = 0; i < bookCount; i++)
        if (books[i].id == id)
            return &books[i];
    return NULL;
}
