#ifndef MANAGEMENT_H
#define MANAGEMENT_H

#include "../book/book.h"
#include "../user/user.h"

void runLibrary();
void borrowBook(User_t *user, Book_t *book);
void returnBook(User_t *user, Book_t *book);

#endif