# data-priority-queue 
=====================================================
##用于服务端的可恢复的消息优先级队列

应用场景
------------------------------------------------------
流水线式的消息/数据处理系统(A -> B -> C)往往需要处理大量的消息，但消息类型间又有优先级的高低之分。
为确保高优先级的消息类型优先通过该系统，各模块都需要确保对高优先级消息的优先处理。
data-priority-queue用于各模块内部，接收、排序到来的消息，并吐出高优先级的消息供模块处理。
配合消息队列使用更好，消息队列往往只对消息进行分类或者分通道，无法区别高低优先级，data-pq是对消息队列的补充。


实现原理
------------------------------------------------------
### 排序
data-pq内部有多个子队列组成，不同的子队列有优先级高低之分，同一个子队列内消息有先后之分。
对应的消息进入各自相应优先级的子队列，取消息时按优先级高低依次遍历，返回data-pq中当前最高优先级的消息。

### 可恢复
data-pq的子队列每收到一个消息都以二进制格式持久化到硬盘，然后存入子队列。子
队列的备份文件分为2个（新旧），用于存储队列的最近消息，新文件的大小小于等于子队列的容量，旧文件的大小等于子队列的容量。
当服务重启时，data-pq会为每个子队列恢复其内存现场。读取对应备份文件，先从old file，然后是new file，达到一个最近的满队列场景。

### 子队列
子队列基于固定数组实现，通过循环完成队列功能。


编译
------------------------------------------------------
根目录运行make，得到output目录，里面的include和lib为所需。
