//
// Created by PC on 2017/6/18.
//
#include <cstdlib>
#include <assert.h>
#include <cstdio>
#include "thread_pool.h"
namespace WR {

    bool Task::setArg(void *t1, void *t2, void *t3) {
        arg1 = t1;
        arg2 = t2;
        arg3 = t3;
    }

    thread_pool::thread_pool(int num) {
        threadsNum = num;
        isRunning = switch_add = switch_take = false;
    }

    void thread_pool::start() {
        pthread_mutex_init(&muxtex, NULL);
        sem_init(&sem_tasks, 0, 0);
        createThreads();
        isRunning = switch_add = switch_take = true;

    }

    thread_pool::~thread_pool() {
        stop();
        taskQueue.clear();
    }

    void thread_pool::stop() {
        if (!isRunning)
            return;
        switch_add = false;
        while (true) {
            pthread_mutex_lock(&muxtex);
            int size = taskQueue.size();
            if (size > 0)
                pthread_mutex_unlock(&muxtex);
            else if (0 == size) {
                switch_take = false;
                for (int i = 0; i < threadsNum; i++)
                    pthread_join(threads[i], NULL);
                break;
            }
        }
        isRunning = false;
        delete[]threads;
        threads = NULL;

        pthread_mutex_destroy(&muxtex);
        sem_destroy(&sem_tasks);
    }

    bool thread_pool::addTask(Task *task) {
        if (switch_add) {
            taskQueue.push_back(task);
            sem_post(&sem_tasks);
            return true;
        }
        return false;
    }

    int thread_pool::size() {
        pthread_mutex_lock(&muxtex);
        int size = taskQueue.size();
        pthread_mutex_unlock(&muxtex);
        return size;
    }

    Task *thread_pool::take() {
        Task *task = NULL;
        pthread_mutex_lock(&muxtex);
        if (switch_add) {
            sem_wait(&sem_tasks);
            task = taskQueue.front();
            taskQueue.pop_front();
        } else if (!taskQueue.empty()) {
            sem_wait(&sem_tasks);
            task = taskQueue.front();
            taskQueue.pop_front();
        }
        pthread_mutex_unlock(&muxtex);

        return task;
    }

    int thread_pool::createThreads() {
        threads = new pthread_t[threadsNum];
        for (int i = 0; i < threadsNum; i++) {
            pthread_create(&threads[i], NULL, threadFunc, this);
        }
        return 0;

    }

    void *thread_pool::threadFunc(void *arg) {
        pthread_t tid = pthread_self();
        thread_pool *p = (thread_pool *) arg;
        while (p->switch_take) {
            Task *task =p->take();

            if(task)
            {
                task->run();
                printf("%d thread finish one task!\n", tid);
            }


        }
        return 0;
    }
}