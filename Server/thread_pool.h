//
// Created by PC on 2017/6/18.
//

#include <pthread.h>
#include <semaphore.h>
#include <deque>

#ifndef P2P_SERVER_THREAD_POOL_H
#define P2P_SERVER_THREAD_POOL_H

#endif //P2P_SERVER_THREAD_POOL_H
using namespace std;
namespace WR {
    class Task {
    public:
        Task(){};
        virtual void run()=0;

        bool setArg(void *t1, void *t2, void *t3);

    protected:
        void *arg1 = NULL;
        void *arg2 = NULL;
        void *arg3 = NULL;
    };

    class thread_pool {
    public:


        thread_pool(int num = 10);

        ~thread_pool();

        bool addTask(Task *task);

        void start();

        void stop();

        int size();

        Task *take();


    private:
        bool isRunning, switch_add, switch_take;
        int threadsNum;
        pthread_t *threads;
        deque<Task *> taskQueue;
        pthread_mutex_t muxtex;
        sem_t sem_tasks;

        int createThreads();

        static void *threadFunc(void *);

        thread_pool &operator=(const thread_pool &);

        thread_pool(const thread_pool &);

    };
}