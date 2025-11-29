#ifndef USER_H
#define USER_H

#define MAX_USER 100
#define MAX_NAME 100
#define MAX_BORROWED 10

typedef struct
{
    int id;
    char name[MAX_NAME];
    int borrowedBook[MAX_BORROWED];
    int borrowedCount;
} User_t;

void addUser(User_t users[], int *userCount);
User_t* findUserById(User_t users[], int userCount, int id);
void listUsers(User_t users[], int userCount);

#endif
