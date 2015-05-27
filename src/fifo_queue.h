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
 * @file fifo_queue.h
 * @author whuqin
 * @date 2013/09/11 18:31:21
 * @brief 
 *  
 **/




#ifndef  __FIFO_QUEUE_H_
#define  __FIFO_QUEUE_H_

class Queue
{
    public:
        Queue(int size); 
        Queue(const Queue& src_q);
        ~Queue();
        int push(void* data);
        int push_any(void* data);
        int get(void*& data);
        bool full()
        {
            return (tail_ + 1) % size_ == head_; 
        }

        bool empty()
        {
            return head_ == tail_;
        }
    private:
        void** items_;
        int size_;
        int tail_;
        int head_;
};
#endif  //__FIFO_QUEUE_H_

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
