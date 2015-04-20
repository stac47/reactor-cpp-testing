#include <map>
#include <list>
#include <algorithm>
#include <iterator>

#include "EventHandlerPtr.h"
#include "ReactorInterface.h"

namespace reactor {

void ReactorInterface::operator()() {
    while(true) {
        this->run();
    }
}

void ReactorInterface::registerEventHandler(
        int iFd,
        const EventHandlerPtr& iHandler) {
    // TODO: Need a mutex here
    auto aSearch = _events.find(iFd);
    if (aSearch == _events.end()) {
        std::list<EventHandlerPtr> aHandlerList{iHandler};
        _events[iFd] = aHandlerList;
    }
    else {
        aSearch->second.push_back(iHandler);
    }
}


void ReactorInterface::getEventHandlerFor(
        int iFd,
        std::list<EventHandlerPtr>& oHandlers) const {
    // TODO put a mutex here
    auto aSearch = _events.find(iFd);
    if (aSearch != _events.end()) {
        std::copy(aSearch->second.cbegin(),
                  aSearch->second.cend(),
                  std::back_inserter(oHandlers));
    }
}

} // namespace reactor
