#include <stdlib.h>
#include <pthread.h>

typedef struct StructForParallelFor {
    int start;
    int end;
    void (*funcToRun)(int);
}SFPF;

void* FuncForParallelFor(void* arg) {
    SFPF* data = (SFPF*)arg;
    for (int i = data->start; i < data->end; i++) {
        data->funcToRun(i);
    }
    free(arg);
}

void ParallelFor(int startInclusive, int endExclusive, int threadCount, void (*funcToRun)(int)) {
    pthread_t th[threadCount];
    int countPerThread = (endExclusive - startInclusive) / threadCount;

    for (int i = 0; i < threadCount; i++) {
        SFPF* tempArgument = (SFPF*)calloc(1, sizeof(SFPF));
        if (tempArgument == NULL) {
            exit(-1);
        }
        tempArgument->start = countPerThread * i;
        tempArgument->end = tempArgument->start + countPerThread;
        if (i == threadCount - 1) {
            tempArgument->end = endExclusive;
        }
        else {
            tempArgument->end = tempArgument->start + countPerThread;
        }
        tempArgument->funcToRun = funcToRun;
        if (pthread_create(th + i, NULL, FuncForParallelFor, (void*)tempArgument)) {
            perror("Coudln't creat thread\n");
        }
    }

    for (int i = 0; i < threadCount; i++) {
        if (pthread_join(*(th + i), NULL)) {
            perror("Coudln't join thread\n");
        }
    }
}