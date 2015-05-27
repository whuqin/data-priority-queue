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
 * @file pri_queue.cpp
 * @author whuqin
 * @date 2013/09/11 19:37:54
 * @brief 
 *  
 **/

#include "pri_queue.h"
#include <unistd.h> 

PriQueue::PriQueue()
{
    is_ok_ = false;
}

/**
 * @brief init the queue and backup file
 *
 * @param [in/out] data_size   : int  the size of one element
 * @param [in/out] size   : int capacity of the queue
 * @param [in/out] levels   : int the priority levels of the queue
 * @param [in/out] path   : const char* the file path for storing messages
 * @param [in/out] file_name   : const char* the file name for storing messages
 * @return  int 0 succeed, -1 failed
 * @retval   
 * @see 
 * @note 
 * @author whuqin
 * @date 2013/09/12 15:44:19
**/
int PriQueue::init(int data_size, int size, int levels, const char* path, const char* file_name)
{

    if ( 0 != access(path, F_OK|R_OK|W_OK))
    {
        return -1;
    }
    data_size_ = data_size;
    size_ = size;
    levels_ = levels;
    now_size_ = 0;
    snprintf(path_, DATA_PQ_FILENAME_MAXLEN, "%s", path);
    snprintf(file_name_, DATA_PQ_FILENAME_MAXLEN, "%s", file_name);

    pthread_mutex_init(&mutex_, NULL);
    pthread_cond_init(&notempty_, NULL);

    for(int i = 0; i< levels; ++i)
    {
        char temp[DATA_PQ_FILENAME_MAXLEN];
        snprintf(temp, DATA_PQ_FILENAME_MAXLEN, "%s/%s_%d", path, file_name, i);

        Queue* q_ptr = new Queue(size);
        FileBak* bak_ptr = new FileBak(data_size, size, temp);
        queue_vec_.push_back(q_ptr);
        bak_vec_.push_back(bak_ptr);
    }

    if (0 != reload())
    {
        return -1;
    }
    is_ok_ = true;
    return 0;
}

/**
 * @brief restore the queue from the backup file
 *
 * @return  void 
 * @retval   
 * @see 
 * @note 
 * @author whuqin
 * @date 2013/09/12 15:45:21
**/
int PriQueue::reload()
{
    for(int i = 0; i < levels_; ++i)
    {
        vector<void*> items;
        int ret = bak_vec_[i]->reload(items);
        if (0 != ret)
        {
            return -1;
        }
        vector<void*>::iterator it = items.begin();
        for (; it != items.end(); ++it)
        {
            queue_vec_[i]->push_any(*it);
        }
        int items_size = items.size();
        now_size_ += items_size > size_ ? size_ : items_size;
    }

    if (now_size_ > 0)
    {
        pthread_cond_signal(&notempty_);
    }
    return 0;
}

/**
 * @brief push a message into the queue
 *
 * @param [in/out] data   : void* one message
 * @param [in/out] level   : int the priority level of the message
 * @return  int 0 succeed, -1 the queue is full
 *              1 the data is invalid
 * @retval   
 * @see 
 * @note 
 * @author whuqin
 * @date 2013/09/12 15:45:56
**/
int PriQueue::push(void* data, int level)
{
    if (data == NULL || level < 0 || level >= levels_)
    {
        return 1;
    }

    if (!is_ok_)
    {
        return -1;
    }

    pthread_mutex_lock(&mutex_);
    
    if( 0 != queue_vec_[level]->push(data))
    {
        pthread_mutex_unlock(&mutex_);
        return -1;
    }
    ++now_size_;
    bak_vec_[level]->push(data);

    pthread_mutex_unlock(&mutex_);
    pthread_cond_signal(&notempty_);
    return 0;
}

/**
 * @brief try to get the topest prior message; wait if the queue is empty
 * 
 * @return  void* 
 * @retval   
 * @see 
 * @note 
 * @author whuqin
 * @date 2013/09/12 15:47:25
**/
void* PriQueue::get()
{
    if (!is_ok_)
    {
        return NULL;
    }
    pthread_mutex_lock(&mutex_);
    while (empty())
    {
        pthread_cond_wait(&notempty_,&mutex_);
    }
    void* data = NULL;
    for (int i = levels_ - 1; i >= 0; --i)
    {
        int ret = queue_vec_[i]->get(data);
        if (0 ==  ret)
        {
            --now_size_;
            break;
        }
    }
    pthread_mutex_unlock(&mutex_);
    return data;
}

PriQueue::~PriQueue()
{
   for (size_t i = 0; i < queue_vec_.size(); ++i)
    {
        delete queue_vec_[i];
        queue_vec_[i] = NULL;
    }
    queue_vec_.clear();
    for (size_t i = 0; i < bak_vec_.size(); ++i)
    { 
        delete bak_vec_[i];
        bak_vec_[i] = NULL;
    }
    bak_vec_.clear();
}
/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
