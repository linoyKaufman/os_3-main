#include "reactor.hpp"
#include <unistd.h>
#include <iostream>
#include <cstring>
#include <sys/epoll.h>

Reactor::Reactor() {
    epoll_fd = epoll_create1(0);
    if (epoll_fd < 0) {
        perror("epoll_create1");
        exit(1);
    }
}

Reactor::~Reactor() {
    close(epoll_fd);
}

int Reactor::addFd(int fd, std::function<void(int)> callback) {
    struct epoll_event ev;
    ev.events = EPOLLIN; // Monitor for read events
    ev.data.fd = fd;

    if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, fd, &ev) < 0) {
        perror("epoll_ctl");
        return -1;
    }

    callbacks[fd] = callback;
    return 0;
}

int Reactor::removeFd(int fd) {
    if (epoll_ctl(epoll_fd, EPOLL_CTL_DEL, fd, nullptr) < 0) {
        perror("epoll_ctl");
        return -1;
    }

    callbacks.erase(fd);
    return 0;
}

void Reactor::start() {
    eventLoop();
}

void Reactor::eventLoop() {
    struct epoll_event events[10];

    while (true) {
        int n = epoll_wait(epoll_fd, events, 10, -1);
        if (n < 0) {
            perror("epoll_wait");
            break;
        }

        for (int i = 0; i < n; ++i) {
            int fd = events[i].data.fd;
            if (callbacks.find(fd) != callbacks.end()) {
                callbacks[fd](fd);
            }
        }
    }
}
