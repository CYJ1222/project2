#include "lcm.h"

#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
sem_t shovel;       // 铲子信号量
sem_t hole_to_seed; //未种的坑
sem_t hole_to_fill; //种了但未填坑
sem_t unfilled_avalid;//所有未填的坑
void *larry()
{
    int id = 0;
    while (N > id)
    {
        sem_wait(&unfilled_avalid);
        sem_wait(&shovel);
        get_shovel(LARRY);
        sleep(rand() % MAX); // add random delay
        dig(LARRY, ++id);
        drop_shovel(LARRY);
        sem_post(&shovel);
        sem_post(&hole_to_seed);
    }
    pthread_exit(NULL);
}
void *moe()
{
    int id = 0;
    while (N > id)
    {
        sem_wait(&hole_to_seed);
        sleep(rand() % MAX); // add random delay
        plant(MOE, ++id);
        sem_post(&hole_to_fill);
    }
    pthread_exit(NULL);
}
void *curly()
{

    int id = 0;
    while (N > id)
    {
        sem_wait(&hole_to_fill);
        sem_wait(&shovel);
        get_shovel(CURLY);
        fill(CURLY, ++id);
        sleep(rand() % MAX); // add random delay
        drop_shovel(CURLY);
        sem_post(&shovel);
        sem_post(&unfilled_avalid);
    }
    pthread_exit(NULL);
}

void init()
{
    // some code goes here
    if (sem_init(&shovel, 0, 1) == -1)
    {
        perror("sem_init error");
        return;
    }
    if (sem_init(&hole_to_seed, 0, 0) == -1)
    {
        perror("sem_init error");
        return;
    }
    if (sem_init(&hole_to_fill, 0, 0) == -1)
    {
        perror("sem_init error");
        return;
    }
    if (sem_init(&unfilled_avalid, 0, MAX) == -1)
    {
        perror("sem_init error");
        return;
    }

    // sem_init(&shovel, 0, 0);
}

void destroy()
{
    // some code goes here
    sem_destroy(&shovel);
    sem_destroy(&hole_to_seed);
    sem_destroy(&hole_to_fill);
    sem_destroy(&unfilled_avalid);
}
