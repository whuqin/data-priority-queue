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
 * @file data_backup.h
 * @author whuqin
 * @date 2013/09/11 18:53:16
 * @brief 
 *  
 **/




#ifndef  __DATA_BACKUP_H_
#define  __DATA_BACKUP_H_

#include <stdio.h>
#include <vector>
using namespace std;

#define DATA_PQ_FILENAME_MAXLEN 256
class FileBak
{
    public:
        FileBak(int data_size, int size, const char* file_name);
        FileBak(const FileBak& file_bak);
        int reload(vector<void*>& items);
        int push(void* data);
    private:
        int reload(vector<void*>& items, const char* file_name);
        int open_file();
    private:
        int data_size_;       /**< the size of a data **/
        int max_size_;
        int size_;
        FILE* file_;
        char file_now_[DATA_PQ_FILENAME_MAXLEN];
        char file_old_[DATA_PQ_FILENAME_MAXLEN];

};
#endif  //__DATA_BACKUP_H_

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
