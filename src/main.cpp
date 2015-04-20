#include <iostream>
#include <thread>
#include <iostream>

#include "threads/ConnectionAcceptor.h"
#include "reactor/ReactorInterface.h"
#include "reactor/ReactorSelectImpl.h"

int main(int , const char**) {
    auto aTrafficManager = std::make_shared<reactor::ReactorSelectImpl>();
    ConnectionAcceptor aConnectionAcceptor{"localhost", "4747",
                                           aTrafficManager};
    std::thread aAcceptorThread(aConnectionAcceptor);
    std::thread aTrafficManagerThread(*aTrafficManager);
    aAcceptorThread.join();
    aTrafficManagerThread.join();
    return 0;
}

