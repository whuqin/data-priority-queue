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
 * @file fifo_queue.cpp
 * @author whuqin
 * @date 2013/09/11 18:31:26
 * @brief 
 *  
 **/
#include "fifo_queue.h"
#include <cstdlib>
/**
 * @brief ¹
 *
 * @param [in/out] size   : int
 * @see 
 * @note 
 * @author qinbin
 * @date 2013/09/12 15:49:52
**/
Queue::Queue(int size):size_(size + 1),tail_(0), head_(0)
{
    items_ = new void*[size_];
}

Queue::Queue(const Queue& src_q)
{
    size_ = src_q.size_;
    tail_ = src_q.tail_;
    head_ = src_q.head_;
    if (NULL != items_)
    {
        delete[] items_;
        items_ = NULL;
    }
    items_ =  new void*[size_];
    for (int i = 0; i < size_; ++i)
    {
        items_[i] = src_q.items_[i];
    }
}

/**
 * @brief push a data
 *
 * @param [in/out] data   : void*
 * @return  int -1 full, 0 succeed
 * @retval   
 * @see 
 * @note 
 * @author whuqin
 * @date 2013/09/12 15:50:11
**/
int Queue::push(void* data)
{
   if (full())
   {
       return -1;
   }
   items_[tail_] = data;
   tail_ = (tail_ + 1) % size_;
   return 0;
}

/**
 * @brief push a data, if queue is full, overwrite the head.
 *        this function is just for restoring the queue from the backup files
 *
 * @param [in/out] data   : void*
 * @return  int 
 * @retval   
 * @see 
 * @note 
 * @author qinbin
 * @date 2013/09/12 15:50:36
**/
int Queue::push_any(void* data)
{
    if (full())
    {
        char* head =(char*)items_[head_];
        delete[] head;
        head_ = (head_ + 1) % size_; 
    }
    items_[tail_] = data;
    tail_ = (tail_ + 1) % size_;
    return 0;
}

/**
 * @brief get a data from the queue
 *
 * @param [in/out] data   : void* &
 * @return  int 0 succeed, -1 failed
 * @retval   
 * @see 
 * @note 
 * @author qinbin
 * @date 2013/09/12 16:07:02
**/
int Queue::get(void*& data)
{
    if (empty())
    {
        return -1;
    }
    data = items_[head_];
    head_ = (head_ + 1) % size_;
    return 0;
}

Queue::~Queue()
{
    delete[] items_;
}
/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
