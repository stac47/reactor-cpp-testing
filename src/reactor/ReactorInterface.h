#ifndef __REACTORINTERFACE_H__
#define __REACTORINTERFACE_H__

#include <memory>
#include <map>
#include <list>

#include "EventHandlerPtr.h"

namespace reactor {

class ReactorInterface {
public:
    void operator()();

    void registerEventHandler(int iFd,
                              const EventHandlerPtr& iHandler);

    void getEventHandlerFor(int iFd,
                            std::list<EventHandlerPtr>& oHandlers) const;

    /* virtual bool unregisterEventHandler(const EventHandlerPtr& iHandler); */

protected:
    virtual void run() = 0;

private:
    std::map<int, std::list<EventHandlerPtr>> _events;
};

} // namespace reactor
#endif /* __REACTORINTERFACE_H__ */
