#ifndef __CONNECTIONACCEPTOR_H__
#define __CONNECTIONACCEPTOR_H__

#include <string>
#include <memory>

#include "../reactor/ReactorInterface.h"

class ConnectionAcceptor {
public:
    ConnectionAcceptor(const std::string& address,
                       const std::string& port,
                       const std::shared_ptr<reactor::ReactorInterface>& trafficManager)
      : _address(address),
        _port(port),
        _trafficManager(trafficManager) {};

    void operator()();
private:
    std::string _address;
    std::string _port;
    std::shared_ptr<reactor::ReactorInterface> _trafficManager;
};
#endif /* __CONNECTIONACCEPTOR_H__ */
