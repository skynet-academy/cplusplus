#include <iostream>
#include<pthread.h>
#include<stdio.h>
#include<thread>
#include<vector>
#include<future>
#include<mutex>
#include<signal.h>
#include<unistd.h>
#include<string.h>

typedef struct stage_tag{
    pthread_mutex_t mutex;
    pthread_cond_t avail;
    pthread_cond_t ready;
    int data_ready;
    long data;
    pthread_t thread;
    struct stage_tag *next;
} stage_t;

typedef struct pipe_tag{
    pthread_mutex_t mutex;
    stage_t *head;
    stage_t *tail;
    int stages;
    int active;
} pipe_t;

int pipe_send(stage_t *stage, long data){
    pthread_mutex_lock(&stage->mutex);
    while(stage->data_ready)
        pthread_cond_wait(&stage->ready, &stage->mutex);
    stage->data = data;
    stage->data_ready = 1;
    pthread_cond_signal(&stage->avail);
    pthread_mutex_unlock (&stage->mutex);
    return rc;
}

void *pipe_stage(void *arg){
    stage_t *stage = (stage_t*)arg;
    stage_t *next_stage = stage->next;
    pthread_mutex_lock(&stage->mutex);
    for(;;){
        while(stage->data_ready !=1)
            pthread_cond_wait(&stage->avail, &stage->mutex);
        pipe_send(next_stage, stage->data + 1);
        pthread_cond_signal(&stage->ready);
    }
}

int pipe_result(pipe_t *pipe, long *result){
    stage_t *tail = pipe->tail;
    long value; int empty = 0, rc;
    pthread_mutex_lock(&pipe->mutex);
    if(pipe->active <=0){empty = 1;}
    else pipe->active--;
    pthread_mutex_unlock(&pipe->mutex);
    if(empty){return 0;}
    pthread_mutex_lock(&tail->mutex);
    while(!tail->data_ready)
        pthread_cond_wait(&tail->avail,&tail->mutex);
    *result = tail->data;
    tail->data_ready = 0;
    pthread_cond_signal(&tail->ready);
    pthread_mutex_unlock(&tail->mutex);
    return 1;
}

int pipe_create(pipe_t *pipe, int stages){
    int pipe_index;
    stage_t **link = &pipe->head, *new_stage, *stage;
    pthread_mutex_init(&pipe->mutex, NULL);
    pipe->stages = stages;
    pipe->active = 0;
    for(pipe_index = 0; pipe_index <=stages; pipe_index++){
        new_stage = (stage_t*)malloc (sizeof(stage_t));
        pthread_mutex_init(&new_stage-> mutex, NULL);
        rc = pthread_cond_init(&new_stage->avail, NULL);
        rc = pthread_cond_init(&new_stage->ready, NULL);
        new_stage->data_ready = 0;
        *link = new_stage;
        link = &new_stage->next;
    }
    *link = (stage_t *)NULL;
    pipe->tail = new_stage;
    for(stage = pipe->head; stage->next !=NULL;stage = stage->next){
        rc = pthread_create(&stage->thread, NULL, pipe_stage, (void *)stage);
        if(rc !=0){
            std::cout<<"Error process ";
        }
    }
    return 0;
}


int pipe_start(pipe_t *pipe, long value){
    pthread_mutex_lock(&pipe->mutex);
    pipe->active++;
    pthread_mutex_unlock(&pipe->mutex);
    pipe_send(pipe->head, value);
    return 0;
}


int main(int argc, char *argv[]){
    pipe_t my_pipe;
    long value, result;
    int status;
    char line[128];
    pipe_create(&my_pipe, 10);
    printf("enter int values, or \"=\" for next result\n");
    for(;;){
        if(fgets(line,sizeof(line),stdin)== NULL) exit(0);
        if(strlen(line)<=1) continue;
        if(strlen(line)<=2 && line[0] == '='){
            if(pipe_result(&my_pipe, &result))
                printf("Result is %1d \n", result);
            else
                printf("Pipe is empty");
        } else{
            if(sscanf(line,"%1d", &value)< 1)
                fprintf(stderr, "Enter an integer value\n");
            else
                pipe_start(&my_pipe, value);
        }
    }
}
