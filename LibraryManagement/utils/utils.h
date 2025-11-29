#ifndef UTILS_H
#define UTILS_H

void clearInputBuffer();
void safeInput(char *buffer, int size);
int inputInt(const char *prompt, int min, int max);

#endif