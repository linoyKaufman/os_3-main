#ifndef REACTOR_HPP
#define REACTOR_HPP

#include <functional>
#include <unordered_map>
#include <sys/epoll.h>

class Reactor {
public:
    Reactor();
    ~Reactor();
    
    int addFd(int fd, std::function<void(int)> callback);
    int removeFd(int fd);
    void start();
    
private:
    int epoll_fd;  // Define epoll_fd here as a member variable
    std::unordered_map<int, std::function<void(int)>> callbacks;

    void eventLoop();
};

#endif // REACTOR_HPP
