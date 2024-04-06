#include "party.h"

#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
sem_t studentnum;//0
sem_t waitingstudent;
pthread_mutex_t room_mutex = PTHREAD_MUTEX_INITIALIZER;
static int stnum=0;
void *dean() {
    for (int i = 0; i < N; i++) {
        usleep((rand() % 500 + 200) * 1000);
        int stunum=0;
        while(true)
        {
            sem_getvalue(&studentnum,&stunum);
            if(stunum>10||stunum==0)
            {
                pthread_mutex_lock(&room_mutex);
                sem_getvalue(&studentnum,&stunum);
                if(stunum==0)
                {
                    dean_enter();
                    search();
                    dean_leave();
                    pthread_mutex_unlock(&room_mutex);
                    break;
                }
                else if(stunum>10)
                {
                    dean_enter();
                    breakup();
                    while(stunum!=0)
                    {
                        sem_getvalue(&studentnum,&stunum);
                    }
                    dean_leave();
                    pthread_mutex_unlock(&room_mutex);
                    break;
                }
                else
                {
                    pthread_mutex_unlock(&room_mutex);
                    continue;
                }
                
                
            }
        }
    }
    pthread_exit(0);
}

void *student(void *arg) {
    int id = *(int *)arg;
    sem_wait(&waitingstudent);
    pthread_mutex_lock(&room_mutex);
    student_enter(id);
    sem_post(&studentnum);
    printf("student in the room:%d\n",++stnum);
    pthread_mutex_unlock(&room_mutex);
    sem_post(&waitingstudent);
    usleep((rand() % 500 + 1000) * 1000);
    party(id);
    usleep((rand() % 500 + 1000) * 1000);
    student_leave(id);
    printf("student in the room:%d\n",--stnum);
    sem_wait(&studentnum);
    // some code goes here
    pthread_exit(0);
}

void init() {
    if (sem_init(&studentnum, 0, 0) == -1)
    {
        perror("sem_init error");
        return;
        
    }
    if (sem_init(&waitingstudent, 0, 1) == -1)
    {
        perror("sem_init error");
        return;
        
    }

}

void destroy() {
    sem_destroy(&studentnum);
    sem_destroy(&waitingstudent);
}
