#include <stdio.h>
#include <string.h>
#include "../utils/utils.h"
#include "user.h"

void addUser(User_t users[], int *userCount)
{
    if(*userCount >= MAX_USER)
    {
        printf("Danh sach nguoi dung da day!\n");
        return;
    }

    User_t *u = &users[*userCount];
    u -> id = *userCount + 1;
    
    printf("Nhap ten nguoi dung: ");
    safeInput(u->name, MAX_NAME);

    u -> borrowedCount = 0;
    (*userCount)++;
    printf("Da them nguoi dung \"%s\"\n", u->name);
}

User_t* findUserById(User_t users[], int userCount, int id)
{
    for (int i = 0; i < userCount; i++)
        if(users[i].id == id)
            return &users[i];
    return NULL;
}

void listUsers(User_t users[], int userCount)
{
    if (userCount == 0)
    {
        printf("Danh sach nguoi dung trong!\n");
        return;
    }
    printf("\nDanh sach nguoi dung:\n");
    for (int i = 0; i < userCount; i++)
    {
        printf("[%d] %s - Da muon %d sach\n", users[i].id, users[i].name, users[i].borrowedCount);
    }
}
