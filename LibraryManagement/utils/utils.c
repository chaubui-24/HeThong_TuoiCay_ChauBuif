#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "utils.h"

void clearInputBuffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void safeInput(char *buffer, int size)
{
    fgets(buffer, size, stdin);
    buffer[strcspn(buffer, "\n")] = '\0';
}

int inputInt(const char *prompt, int min, int max)
{
    int value;
    char line[100];
    while (1)
    {
        printf("%s", prompt);
        fgets(line, sizeof(line), stdin);
        if (sscanf(line, "%d", &value) == 1 && value >= min && value <= max)
            return value;
        printf("Vui long nhap so hop le (%d - %d)\n", min ,max);
    }
}
