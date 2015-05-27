/***************************************************************************
 * 
 * Copyright (c) 2013-2015, whuqin. All Rights Reserved
 * 
 * This file is part of data-pq (data-priority-queue).
 *
 * data-pq is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * data-pq is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Foobar.  If not, see <http://www.gnu.org/licenses/>.
 **************************************************************************/
 
 
 
/**
 * @file pri_queue.h
 * @author whuqin
 * @date 2013/09/11 19:33:49
 * @brief priority queue
 *  
 **/




#ifndef  __PRI_QUEUE_H_
#define  __PRI_QUEUE_H_
#include <vector>
#include <pthread.h>
#include "fifo_queue.h"
#include "data_backup.h"

using namespace std;

class PriQueue
{
    public:
        PriQueue();
//        PriQueue(const PriQueue& pri_q);
        ~PriQueue();
        int init(int data_size, int size, int levels, const char* path, const char* file_name);
        int push(void* data, int level);
        void* get();
        bool empty()
        {
            return now_size_ == 0;
        }

    private:
        int reload();
    private:
        vector<Queue*> queue_vec_;
        vector<FileBak*> bak_vec_;

        pthread_mutex_t mutex_;
        pthread_cond_t notempty_;

        int data_size_;       /**< the size of elements, Byte **/
        int now_size_;
        int size_;
        int levels_;
        char path_[DATA_PQ_FILENAME_MAXLEN];
        char file_name_[DATA_PQ_FILENAME_MAXLEN];

        bool is_ok_;
};
#endif  //__PRI_QUEUE_H_

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
