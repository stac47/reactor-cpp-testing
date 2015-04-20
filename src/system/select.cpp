#include <sys/time.h>
#include <sys/select.h>

#include <vector>
#include <algorithm>
#include <functional>

namespace {

void FdSet(int iFd, fd_set& oFds) {
    FD_SET(iFd, &oFds);
}

bool FdIsSet(int iFd, const fd_set& iFds) {
    return FD_ISSET(iFd, &iFds) == 1;
}

} // namespace

namespace sys {

int select(std::vector<int>& ioReadFds,
           std::vector<int>& ioWriteFds,
           std::vector<int>& ioExceptFds,
           int timeoutSeconds = 0) {
    fd_set readFds, writeFds, exceptFds;
    FD_ZERO(&readFds);
    FD_ZERO(&writeFds);
    FD_ZERO(&exceptFds);

    using namespace std::placeholders;
    std::for_each(ioReadFds.begin(), ioReadFds.end(),
            std::bind(FdSet, _1, readFds));
    std::for_each(ioWriteFds.begin(), ioWriteFds.end(),
            std::bind(FdSet, _1, writeFds));
    std::for_each(ioExceptFds.begin(), ioExceptFds.end(),
            std::bind(FdSet, _1, exceptFds));

    // Find the max in the 3 file descriptons sets
    int aMaxReadFd = 0;
    if (!ioReadFds.empty()) {
        aMaxReadFd = *std::max_element(ioReadFds.begin(), ioReadFds.end());
    }
    int aMaxWriteFd = 0;
    if (!ioWriteFds.empty()) {
        aMaxWriteFd = *std::max_element(ioWriteFds.begin(), ioWriteFds.end());
    }
    int aMaxExceptFd = 0;
    if (!ioExceptFds.empty()) {
        aMaxExceptFd = *std::max_element(ioExceptFds.begin(), ioExceptFds.end());
    }

    int aMax = std::max(aMaxReadFd, std::max(aMaxWriteFd, aMaxExceptFd));

    // timeout conversion
    timeval timeout;
    timeout.tv_sec = timeoutSeconds;
    timeout.tv_usec = 0;

    // The system call to 'select()'
    int result = select(aMax, &readFds, &writeFds, &exceptFds, &timeout);

    // Filter the ready for I/O fds.
    ioReadFds.erase(std::remove_if(ioReadFds.begin(), ioReadFds.end(),
                                   std::bind(FdIsSet, _1, readFds)),
                    ioReadFds.end());
    ioWriteFds.erase(std::remove_if(ioWriteFds.begin(), ioWriteFds.end(),
                                    std::bind(FdIsSet, _1, writeFds)),
                     ioWriteFds.end());
    ioExceptFds.erase(std::remove_if(ioExceptFds.begin(), ioExceptFds.end(),
                                     std::bind(FdIsSet, _1, exceptFds)),
                      ioExceptFds.end());
    return result;
}

} // namespace sys
