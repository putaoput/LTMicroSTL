# LTSimpleSTL

#### 简介
   这是一个简易的STL，实现了STL中的绝大多数的容器和常见算法。加入了一些C++标准库中的内容如std::string，动手设计并拙劣实现两个线程安全的模板类。
   
   这个STL实现的用途是个人学习，主要是学习数据结构和算法，模板编程还有C++11新特性
   
   由于大部分函数的实现方法都是了解原理之后，自己构思的实现思路，因此很多地方都不是最佳实现方法。除红黑树部分平衡调整算法部分代码外，其余代码都是自己一行一行的敲出来的，经统计代码量10000+，
   由于代码量庞大，因此目前代码中仍有大量的bug，目前我仍然在调试查找并解决。
#### 初衷
  在接触C++之后，一直想找项目练手，后来查阅了一些资料，发现动手实现STL是常见项目里面难度最高的一个，当时不知天高的我决定挑战自己，动手开始实现STL第二个出发点源于之前编写Linux高性能服务器时，始终想在编写的服务器上获得更好的性能。调试程序时发现大量的资源花费到了互斥锁上，因此有了自己动手实现底层容器，通过实现为服务器定制线程安全的容器来实现无锁编程(期望提高线程池的任务队列性能)，通过改造标准库容器如string(期望减少解析HTTP头部的资源消耗)，当然我的终极目标是把自己编写的STL用在自己编写的服务器上（目前只实现了部分）。
   比较遗憾的是我大大低估了自己动手写STL的开发难度和开发时间，因此目前仍然在坚持改进，在不断完善。
#### 关于thread_safe_vector
简单的性能测试结果如下：
   * 写入：两百万次。 读取：两百万次。   
   * 使用mutex用时：2120ms
   * 使用thread_safe_vector用时：1291ms
   
运行截图见语雀链接。
#### 编译环境
   * 本机测试环境
      * OS:  Windows 10
      * IDE: Visual Studio 2019
   * (测试代码部分直接使用了其他人编写的测试用例)
___
## 文件列表
* [配置器](#配置器)
  * allocator   
  * constructor
  * alloc (内存池:未完成，已放弃)
* [迭代器](#迭代器)
  * iterator 
* [仿函数](#仿函数)
  * functional 
* [容器](#容器)
  * vector
  * list
  * deque
  * hashtable
  * rb_tree(因时间不足，平衡调整部分参考了已有开源代码)
  * basic_string
  * thread_safe_vector(基于循环数组实现的无锁任务队列)
* [算法](#算法)
  * 基本算法
  * 数值算法
  * heap 算法
  * 其他算法
* [配接器](#配接器)
  * container adapters
    * stack
    * queue
    * priority_queue
    * unordered_map(包装了hashtable)
    * unordered_set
    * set(包装了rb_tree)
    * map
    * thread_safe_deque
  * iterator adapters
    * reverse_iterator
    
___

## 测试结果
https://www.yuque.com/putaoput/umu9u4/ucdik6

## 相关文档
https://www.yuque.com/putaoput/umu9u4
