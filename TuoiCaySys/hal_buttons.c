#define _POSIX_C_SOURCE 200809L
#include "hal_buttons.h"
#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

static pthread_t th;
static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
static int btn1 = 0;
static int btn2 = 0;

static void* input_thread(void* arg)
{
    (void)arg;
    char buf[128];
    printf("[BTN] Go \n'1' + Enter: Toggle AUTO/MANUAL.\n'2' + Enter: Manual watering. \n'q' de thoat.\n");
    while (fgets(buf, sizeof(buf), stdin) != NULL)
    {
        char *p = strchr(buf, '\n'); if (p) *p = '\0';
        if (strcmp(buf, "1")==0)
        {
            pthread_mutex_lock(&mutex);
            btn1 = 1;
            pthread_mutex_unlock(&mutex);
        }
        else if (strcmp(buf, "2")==0)
        {
            pthread_mutex_lock(&mutex);
            btn2 = 1;
            pthread_mutex_unlock(&mutex);
        }
        else if (strcmp(buf, "q")==0 || strcmp(buf, "quit")==0)
        {
            exit(0);
        }
        else
        {
            printf("[BTN] Lenh khong hop le. Dung 1/2/q\n");
        }
    }
    return NULL;
}

void HAL_Buttons_Init(void)
{
    pthread_create(&th, NULL, input_thread, NULL);
}

bool HAL_Button1_Pressed(void)
{
    bool ret = false;
    pthread_mutex_lock(&mutex);
    if (btn1)
    {
        ret = true;
        btn1 = 0;
    }
    pthread_mutex_unlock(&mutex);
    return ret;
}

bool HAL_Button2_Pressed(void)
{
    bool ret = false;
    pthread_mutex_lock(&mutex);
    if (btn2)
    {
        ret = true; 
        btn2 = 0;
    }
    pthread_mutex_unlock(&mutex);
    return ret;
}