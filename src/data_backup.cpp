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
 * @file data_backup.cpp
 * @author whuqin
 * @date 2013/09/11 18:53:31
 * @brief 
 *  
 **/
#include "data_backup.h"
#include <stdlib.h>
#include <unistd.h> 

/**
 * @brief init 
 *
 * @param [in/out] size   : int capacity of a queue
 * @param [in/out] file_name   : const char* the prefix name of backup file
 * @see 
 * @note 
 * @author whuqin
 * @date 2013/09/12 15:29:11
**/
FileBak::FileBak(int data_size, int size, const char* file_name): 
    data_size_(data_size), max_size_(size), size_(0), file_(NULL)
{
    snprintf(file_now_, DATA_PQ_FILENAME_MAXLEN, "%s_now", file_name);
    snprintf(file_old_, DATA_PQ_FILENAME_MAXLEN, "%s_old", file_name);
}

FileBak::FileBak(const FileBak& file_bak)
{
    data_size_ = file_bak.data_size_;
    max_size_ = file_bak.max_size_;
    size_ = file_bak.size_;
    file_ = file_bak.file_;
    snprintf(file_now_, DATA_PQ_FILENAME_MAXLEN, "%s", file_bak.file_now_);
    snprintf(file_old_, DATA_PQ_FILENAME_MAXLEN, "%s", file_bak.file_old_);
}

/**
 * @brief open the file_now_
 * 
 *
 * @return  int -1 failed, 0 succeed
 * @retval   
 * @see 
 * @note 
 * @author whuqin
 * @date 2013/09/23 15:51:16
**/
int FileBak::open_file()
{
    if (0 != access(file_now_, F_OK))
    {
        file_ = fopen(file_now_, "w+b");
        if (file_ == NULL)
        {
            return -1;
        }
        size_ = 0;
    } 
    else
    {
        file_ = fopen(file_now_, "r+b");
        if (file_ == NULL)
        {
            return -1;
        }
        //set the pos to the end of the last valid element
        fseek(file_, 0, SEEK_END);
        long file_size = ftell(file_);
        long valid_pos = (file_size / data_size_) * data_size_;
        fseek(file_, valid_pos, SEEK_SET);

        size_ = file_size / data_size_;
        if (size_ == max_size_)
        {
            fclose(file_);
            file_ = NULL;

            rename(file_now_, file_old_);
            size_ = 0;
            file_ = fopen(file_now_, "w+b");
            if (file_ == NULL)
            {
                return -1;
            }
        }
    }
    return 0;
}

/**
 * @brief push data, if the file is full, remove file_now_ to file_old_
 *
 * @param [in/out] data   : void*
 * @return  int 0 succeed, -1 failed
 * @retval   
 * @see 
 * @note 
 * @author whuqin
 * @date 2013/09/12 15:29:43
**/
int FileBak::push(void* data)
{
    if (file_ == NULL && (0 != open_file()))
    {
        return -1;
    }

    fwrite(data, data_size_, 1, file_);
    fflush(file_);
    ++size_;
    if (size_ == max_size_)
    {
        fclose(file_);
        file_ = NULL;

        rename(file_now_, file_old_);
        size_ = 0;
    }
    return 0;
}

/**
 * @brief reload data into items from the backup file
 *
 * @param [in/out] items   : vector<void* >&
 * @return  int 0 succeed, -1 failed
 *              
 * @retval   
 * @see 
 * @note 
 * @author whuqin
 * @date 2013/09/12 15:30:41
**/
int FileBak::reload(vector<void*>& items)
{
    int ret = 0;
    ret = reload(items, file_old_);
    if (0 != ret)
    {
        return -1;
    }
    ret = reload(items, file_now_);
    if (0 != ret)
    {
        return -1;
    }
    return 0;
}

/**
 * @brief the implementation for reloading a file
 *
 * @param [in/out] items   : vector<void* >&
 * @param [in/out] file_name   : const char*
 * @return  int 
 * @retval   
 * @see 
 * @note 
 * @author whuqin
 * @date 2013/09/12 15:49:07
**/
int FileBak::reload(vector<void*>& items, const char* file_name)
{
    if (0 != access(file_name, F_OK))
    {
        return 0;
    }
    FILE* file = fopen(file_name, "rb");
    if ( NULL == file)
    {
        return -1;
    }

    char* data = new char[data_size_];
    while (1 == fread(data, data_size_, 1, file))
    {
        items.push_back(data);
        data = new char[data_size_];
    }
    delete []data;
    fclose(file);
    return 0;
}
/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
