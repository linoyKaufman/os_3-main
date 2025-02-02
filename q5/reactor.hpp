#ifndef REACTOR_HPP
#define REACTOR_HPP

#include <unordered_map>
#include <functional>
#include <sys/epoll.h>
#include <vector>

class Reactor {
    int epoll_fd;  
    std::unordered_map<int, std::function<void(int)>> callbacks;

    void eventLoop(); 

public:
    Reactor();   
    ~Reactor();  

    int addFd(int fd, std::function<void(int)> callback); 
    int removeFd(int fd);  
    void start();  
    void stop();  
};

#endif
