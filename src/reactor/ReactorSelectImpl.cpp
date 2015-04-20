#include <vector>
#include <iostream>

#include "../system/select.h"

#include "ReactorSelectImpl.h"

namespace reactor {

void ReactorSelectImpl::run() {
    std::cout << "ReactorSelectImpl running" << std::endl;
    std::vector<int> aReadFds;
    std::vector<int> aWriteFds;
    std::vector<int> aExceptFds;

    int aResult = sys::select(aReadFds, aWriteFds, aExceptFds, 0);

    switch(aResult) {
        case -1:
            std::cout << "Error in select" << std::endl;
            break;
        case 0:
            std::cout << "Timeout in select" << std::endl;
            break;
        default:
            for (auto aFd : aReadFds) {
                std::cout << "Ready to READ: " << aFd << std::endl;
            }
            for (auto aFd : aWriteFds) {
                std::cout << "Ready to WRITE: " << aFd << std::endl;
            }
            break;
    }
}

} // namespace reactor
