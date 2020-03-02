[toc]

# WinSocket

## TCP连接

* 主机连接流程
  1. 建立流式套接字
  2. 套接字：与本地地址绑定
  3. 通知TCP服务器准备好连接
  4. 等待客户端的连接
  5. 建立连接
  6. 在套接字上读写数据
  7. 关闭套接字
  8. 关闭最初套接字，清理环境

* 客户端流程
   1. 建立流式套接字
   2. 将套接字与远程主机连接
   3. 在套接字上读/写数据
   4. 关闭套接字，结束会话

## UDP连接

* 面向非连续连接的特点

1. 不需要在服务器和客户端之间建立连接
2. 不对收到的数据进行排序
3. 对接收到的数据包不发送确认信息，发送端无法知道数据是否被正确接收，也不会重发数据
4. 发送数据比TCP快，系统开销也少

* 建立流程

| 主机流程               | 客户端流程         |
| ---------------------- | ------------------ |
| 建立流式套接字         | 建立流式套接字     |
| 套接字：与本地地址绑定 |                    |
| 在套接字上读写数据     | 在套接字上读写数据 |
| 关闭套接字             | 关闭套接字         |

* UDP的收发函数

```cpp
int
WSAAPI
sendto(
    _In_ SOCKET s,
    _In_reads_bytes_(len) const char FAR * buf,
    // 要传送的数据
    _In_ int len,
    // 长度
    _In_ int flags,
    // 指定函数的方式，一般为0
    _In_reads_bytes_(tolen) const struct sockaddr FAR * to,
    // 目标地址
    _In_ int tolen
    // 指定地址的长度
    );


int
WSAAPI
recvfrom(
    _In_ SOCKET s,
    _Out_writes_bytes_to_(len, return) __out_data_source(NETWORK) char FAR * buf,
    // 要接收的数据
    _In_ int len,
    // 长度
    _In_ int flags,
    // 方式，同为0
    _Out_writes_bytes_to_opt_(*fromlen, *fromlen) struct sockaddr FAR * from,
    // 客户端地址
    _Inout_opt_ int FAR * fromlen
    // 地址长度
    );
```



## 阻塞式模型

* 什么是阻塞式模型

在创建套接字后，默认都是阻塞式的WinSocket的**IO**函数，必须等函数完成相应的I/O操作之后才能继续。

* **阻塞式迭代模式**：每次只服务一个连接，只有服务完成当前客户端连接后才会继续服务下一个客户端连接

  **步骤**

  1. 

* **阻塞式并发连接模式**：通过多线程，可以同时服务多个连接，每一个线程处理一个客户端连接