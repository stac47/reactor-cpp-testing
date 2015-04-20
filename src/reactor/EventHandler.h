#ifndef __EVENTHANDLER_H__
#define __EVENTHANDLER_H__

#include "EventType.h"

namespace reactor {

class EventHandler {
public:
    void operator()(int iFd, EventType iEventType);

protected:
    virtual void handle(int iFd, EventType iEventType) = 0;
};

} // namespace reactor

#endif /* __EVENTHANDLER_H__ */
