#include "reactor.hpp"
#include <unistd.h>
#include <iostream>
#include <cstring>

// Initializes the Reactor and creates a kqueue instance
Reactor::Reactor() {
    epoll_fd = epoll_create1(0);
    if (epoll_fd < 0) {
        perror("epoll_create1");
        exit(1);
    }
}

// Destructor: Closes the kqueue to release resources
Reactor::~Reactor() {
    close(epoll_fd);
}

// Adds a file descriptor to the kqueue for monitoring and connect it with a callback function
int Reactor::addFd(int fd, std::function<void(int)> callback) {
    struct epoll_event ev;
    ev.events = EPOLLIN;  // Monitor for read events
    ev.data.fd = fd;

    if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, fd, &ev) == -1) {
        perror("epoll_ctl");
        return -1;
    }

    // Store the callback associated with the fd
    callbacks[fd] = callback;
    return 0;
}

// Removes a file descriptor from the kqueue and its connected callback
int Reactor::removeFd(int fd) {
    if (epoll_ctl(epoll_fd, EPOLL_CTL_DEL, fd, nullptr) == -1) {
        perror("epoll_ctl");
        return -1;
    }

    callbacks.erase(fd);
    return 0;
}

// Starts the event loop to handle events
void Reactor::start() {
    // Begin monitoring and processing events
    eventLoop(); 
}

// Stops the Reactor by closing the kqueue file descriptor
void Reactor::stop() {
    // This will end the event loop as kqueue becomes invalid
    close(epoll_fd); 
}

// Main event loop: Monitors file descriptors and invokes their callbacks on events
void Reactor::eventLoop() {
     // Array to store triggered events
   struct epoll_event events[10];

    while (true) {
        // Wait for events on the kqueue
         int n = epoll_wait(epoll_fd, events, 10, -1);
        if (n < 0) {
            perror("epoll_wait");
            break;
        }
         // Process each triggered event
         for (int i = 0; i < n; i++) {
            int fd = events[i].data.fd;
            if (callbacks.find(fd) != callbacks.end()) {
                callbacks[fd](fd);
            }
        }
    }
}
