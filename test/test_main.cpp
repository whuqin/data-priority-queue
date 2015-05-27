 
/**
 * @file test_main.cpp
 * @author whuqin
 * @date 2013/09/13 15:27:02
 * @brief 
 *  
 **/

#include <pthread.h>
#include <iostream>
#include <cstdlib>
#include "pri_queue.h"
#include "common.h"
using namespace std;
PriQueue* pq;
void* worker_fun(void* data)
{
    while(true)
    {
        student* st = new student;
        int r = rand() % 5;
        st->age = r;
        snprintf(st->name, 20, "%d", r);

        int ret = pq->push(st, r);
        if (ret == 0)
        {
            char temp[100];
            snprintf(temp, 100, "push age:%d, name:%s", st->age, st->name);
            cout << temp << endl;
        }  
        /*if (ret == -1)
        {
            cout << "level " << level << " is full" << endl;
        }*/
    }
    return NULL;
}

void* consumer_fun(void* data)
{
    while(true)
    {
        student* st = (student*)pq->get();
        char temp[100];
        snprintf(temp, 100, "get age:%d, name:%s", st->age, st->name);
        cout << temp << endl;
        delete st;
    }
    return NULL;
}

int main()
{
    srand(time(NULL));
    pq = new PriQueue;
    int i = pq->init(sizeof(student), 10, 5, "./test", "test_pri");
    if (i != 0)
        cout << "init wrong" << endl;
    
    student* st1 = new student;
    st1->age = 5;
    snprintf(st1->name, 20, "%s", "zhang san");

    pq->push(st1, 1);

    /*void* st2 = pq->get();
    student* st = (student*)st2;
    cout <<"age:" << st->age << ", name:" << st->name << endl;
    delete st;*/

/*    vector<pthread_t> vec;
    for (int i = 0; i < 5; i++)
    {
          pthread_t t1;
          vec.push_back(t1);
          pthread_create(&t1, NULL, consumer_fun, NULL);
    }

    for (int i = 0; i < 10; i++)
    {
        pthread_t t2;
        vec.push_back(t2);
        pthread_create(&t2, NULL, worker_fun, NULL);
    }

    while(true)
    {
        sleep(10);
    }*/
    //pthread_join(vec[0], NULL);
    return 0;
}
/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
