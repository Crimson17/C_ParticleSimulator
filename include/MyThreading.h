#ifndef MYTHREADING_H
#define MYTHREADING_H

void ParallelFor(int startInclusive, int endExclusive, int threadCount, void (*funcToRun)(int));

#endif