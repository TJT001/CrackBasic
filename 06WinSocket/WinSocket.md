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

* **阻塞式并发连接模式**：通过多线程，可以同时服务多个连接，每一个线程处理一个客户端连接

## 非阻塞式模型

* 函数原型

```cpp
WINSOCK_API_LINKAGE
int WSAAPI
ioctlsocket(
    _In_ SOCKET s,
    _In_ long cmd,
    _Inout_ u_long FAR * argp  // 1表示非阻塞, 0表示阻塞
    );
```

## Select模型

* 函数原型

```cpp
WINSOCK_API_LINKAGE
int WSAAPI
select(
    _In_ int nfds,                      // 直接为o
    _Inout_opt_ fd_set FAR * readfds,   // 套接字集合 针对读操作 accept recv
    _Inout_opt_ fd_set FAR * writefds,  // 针对写操作    connect send等
    _Inout_opt_ fd_set FAR * exceptfds, // 针对异常
    _In_opt_ const struct timeval FAR * timeout  // 超时设置，为NULL一直等待
    );
// 返回值 1 如果超时则返回0，如果出现错误则返回 SOCKET_ERROR
// 结构体 fs_set

typedef struct fd_set {
        u_int fd_count;               /* how many are SET?  多少个套接字*/
        SOCKET  fd_array[FD_SETSIZE];   /* an array of SOCKETs 套接字数组*/
} fd_set;

#define FD_SETSIZE 64   //所以最大处理的套接字不超过64个，可并发处理64个套接字
FD_ZERO   // 清0
FD_SET    // 添加套接字
FD_ISSET  // 如果参数世界和的成员 返回非0 否则返回0 
```

* 查询socket状态的函数

```cpp
WINSOCK_API_LINKAGE
int WSAAPI
getsockopt(
    _In_ SOCKET s,    // 套接字
    _In_ int level,   // 选项的等级 包括SOL_SOCKET IPPROTO_TCP
    _In_ int optname, // SOCKET选项的名称
    _Out_writes_bytes_(*optlen) char FAR * optval,   // 用于接收的缓冲区
    _Inout_ int FAR * optlen    // 大小
    );

返回值： 成功返回0 失败返回SOCKET_ERROR
```



## WSAAsyncSelect

* 函数原型

```cpp
WINSOCK_API_LINKAGE
int WSAAPI
WSAAsyncSelect(
    _In_ SOCKET s,
    _In_ HWND hWnd,
    _In_ u_int wMsg,
    _In_ long lEvent
    );
```

# OPENSSL的使用

## 搭建环境

