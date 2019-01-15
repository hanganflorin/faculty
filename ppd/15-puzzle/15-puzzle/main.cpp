#pragma once
#include <iostream>
#include <vector>
#include <unordered_set>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>
#include <getopt.h>
#include <unistd.h>

#include "state.cpp"
#include "tspriorityqueue.cpp"
#include "board.cpp"

State* start;
State* goal;
std::vector<State*> path;
int numThreads = 0;

int bucketMultiplier = -1;

void sequential() {
    std::vector<State*> tempPath;

    std::unordered_set<State*, stateHash, stateEqual> hash;

    PriorityQueue<State*> open;

    hash.insert(start);
    start->addOpen();
    open.push(start);

    int expanded = 0;

    while (!open.empty()) {
        if (expanded%100000 == 0) {
            printf("Finding optimal solution...\n");
        }

        expanded++;
        State* cur = open.pop();

        if (*cur == *goal) {
            while (cur != start) {
                tempPath.push_back(cur);
                cur = cur->getPrev();
            }
            tempPath.push_back(start);

            int pathLength = tempPath.size();
            for (int i = 0; i < pathLength; i++) {
                path.push_back(tempPath[pathLength-1-i]);
            }

            return;
        }

        cur->removeOpen();
        std::vector<State*> neighbors = cur->getNeighbors();

        int altG = cur->getG() + 1;
        for (int i = 0; i < neighbors.size(); i++) {
            State* neighbor = neighbors[i];
            std::unordered_set<State*, stateHash, stateEqual>::iterator it = hash.find(neighbor);
            if (it != hash.end()) {
                // found existing state
                delete neighbor;
                neighbor = *it;

                if (altG < neighbor->getG()) {
                    neighbor->setPrev(cur);
                    neighbor->setG(altG);
                    if (neighbor->checkOpen()) {
                        open.update(neighbor);
                    } else {
                        open.push(neighbor);
                    }
                }
            } else {
                // new state
                hash.insert(neighbor);
                neighbor->addOpen();

                neighbor->setPrev(cur);
                neighbor->setG(altG);
                open.push(neighbor);
            }
        }
    }

    return;
}


TSPriorityQueue<State*, stateHash, stateEqual> open;
int lock = 0;
int numBuckets;

bool handle_tick() {
    State* element;
    if ((element = open.find(goal)) == NULL) {
        return false;
    }

    int fval = element->getF();

    for (int i = 0; i < numBuckets; i++) {
        if (open.getMinKey(i) < fval) {
            return false;
        }
    }
    return true;
}


void* parallelThread(void* arg) {
    int thread_id = (int)(long long)(arg);
    int expanded = 0;
    int lock = 0;

    while (1) {

        if (thread_id == 0 && expanded%10000 == 0) {
            if (expanded % 100000 == 0) {
                printf("Finding optimal solution...\n");
            }
            if (handle_tick()) {
                lock = 1;
                return NULL;
            }
        }

        expanded++;

        State* cur = NULL;
        while (cur == NULL) {
            if (lock == 1) {
                return NULL;
            }
            if (bucketMultiplier == -1) {
                cur = open.pop(thread_id);
            } else {
                cur = open.pop(rand()%numBuckets);
            }
        }

        cur->removeOpen();
        std::vector<State*> neighbors = cur->getNeighbors();

        for (int i = 0; i < neighbors.size(); i++) {
            State* neighbor = neighbors[i];
            open.push(neighbor, cur);
        }
    }

    return NULL;
}

void createPath() {
    std::vector<State*> tempPath;

    State* cur = open.find(goal);

    while (cur != NULL && cur != start) {
        tempPath.push_back(cur);
        cur = cur->getPrev();
    }

    tempPath.push_back(start);

    int pathLength = tempPath.size();
    for (int i = 0; i < pathLength; i++) {
        path.push_back(tempPath[pathLength-1-i]);
    }

    return;
}


void parallel(int numThreads) {

    if (bucketMultiplier == -1) {
        numBuckets = numThreads;
    } else {
        numBuckets = bucketMultiplier*numThreads;
    }

    srand(time(NULL));

    open.init(numBuckets);

    pthread_t threads[numThreads];

    open.push(start, NULL);
    for (int i = 0; i < numThreads; i++) {
        pthread_create(&threads[i], NULL, &parallelThread, (void*)(long long)i);
    }

    for (int i = 0; i < numThreads; i++) {
        pthread_join(threads[i], NULL);
    }

    createPath();
}

int main(int argc, char *argv[]) {
    int size = 4;
    int moves = -1;
    std::string inputFile = "";
    int opt;
    while ((opt = getopt(argc, argv, "t:b:s:m:f:")) != -1) {
        switch (opt) {
            case 't':
                numThreads = atoi(optarg);
                break;
            case 'b':
                bucketMultiplier = atoi(optarg);
                break;
            case 's':
                size = atoi(optarg);
                break;
            case 'm':
                moves = atoi(optarg);
                break;
            case 'f':
                inputFile = optarg;
                break;
        }
    }

    if (inputFile.empty()) {
        if (moves >= 0) {
            start = (State*)(new Board(size, moves));
        } else {
            start = (State*)(new Board(size));
        }
    } else {
        start = (State*)(new Board(inputFile));
    }
    std::cout << "Start board:" << std::endl;
    std::cout << start->toString() << std::endl;

    if (numThreads == 0) {
        std::cout << "Running sequential baseline..." << std::endl;
    } else {
        std::cout << "Running parallel version with " << numThreads << " threads..." << std::endl;
    }
    if (bucketMultiplier != -1) {
        int numBuckets = bucketMultiplier * numThreads;
        std::cout << "Using " << numBuckets << " buckets..." << std::endl;
    }

    goal = (State*)(new Board(size, 0));

    time_t start_t = time(0);

    if (numThreads == 0) {
        sequential();
    } else {
        parallel(numThreads);
    }

    time_t end_t = time(0);
    double time = difftime(end_t, start_t);


    std::cout << "Optimal solution found!" << std::endl << std::endl;
    int length = path.size();
    for (int i = 0; i < length; i++) {
        std::cout << "Step " << i << ":" << std::endl;
        std::cout << path[i]->toString() << std::endl;
    }
    std::cout << "Length of path: " << length-1 << std::endl;
    std::cout << "Total time: " << time << "s" << std::endl;

    return 0;
}
