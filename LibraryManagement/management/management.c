#include <stdio.h>
#include "../utils/utils.h"
#include "management.h"

void borrowBook(User_t *user, Book_t *book)
{
    if (book->isBorrowed)
    {
        printf("Sach nay da duoc muon!\n");
        return;
    }
    if (user->borrowedCount >= MAX_BORROWED)
    {
        printf("%s da muon toi da so sach cho phep!\n", user->name);
        return;
    }

    user->borrowedBook[user->borrowedCount++] = book->id;
    book->isBorrowed = 1;
    printf("%s da muon sach \"%s\"\n", user->name, book->title);
}

void returnBook(User_t *user, Book_t *book)
{
    for (int i = 0; i < user->borrowedCount; i++)
    {
        if (user->borrowedBook[i] == book->id)
        {
            for (int j = i; j < user->borrowedCount -1; j++)
                user->borrowedBook[j] = user->borrowedBook[j + 1];
            user->borrowedCount--;
            book->isBorrowed = 0;
            printf("%s da tra sach \"%s\"\n", user->name, book->title);
            return; 
        }
    }
    printf("%s khong muon sach nay!\n", user->name);
}

void runLibrary()
{
    Book_t books[MAX_BOOK];
    User_t users[MAX_USER];
    int bookCount = 0, userCount = 0;

    while(1)
    {
        printf("\n======== Quan Ly Thu Vien ========\n");
        printf("1. Them sach\n");
        printf("2. Danh sach sach\n");
        printf("3. Them nguoi dung\n");
        printf("4. Danh sach nguoi dung\n");
        printf("5. Muon sach\n");
        printf("6. Tra sach\n");
        printf("0. Thoat\n");

        int choice = inputInt("Nhap lua chon: ", 0, 6);
        
        switch (choice)
        {
            case 1: addBook(books, &bookCount);
            break;

            case 2: listBooks(books, bookCount);
            break;

            case 3: addUser(users, &userCount);
            break;

            case 4: listUsers(users, userCount);
            break;

            case 5:
            {
                if(userCount == 0 || bookCount == 0)
                {
                    printf("Can co it nhat 1 nguoi dung va 1 sach\n");
                    break;
                }
                int uid = inputInt("Nhap ID nguoi dung: ", 1, userCount);
                int bid = inputInt("Nhap ID sach: ", 1, bookCount);
                User_t *u = findUserById(users, userCount, uid);
                Book_t *b = findBookById(books, bookCount, bid);
                if (u && b) 
                    borrowBook(u, b);
                break;
            }

            case 6:
            {
                int uid = inputInt("Nhap ID nguoi dung: ",1, userCount);
                int bid = inputInt("Nhap ID sach: ", 1, bookCount);
                User_t *u = findUserById(users, userCount, uid);
                Book_t *b = findBookById(books, bookCount, bid);
                if (u && b)
                    returnBook(u, b);
                break;
            }
            case 0: printf("Tam biet!\n");
            return;
        }
    }
}