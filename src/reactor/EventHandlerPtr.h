#ifndef __EVENTHANDLERPTR_H__
#define __EVENTHANDLERPTR_H__

#include <memory>

namespace reactor {

class EventHandler;

using EventHandlerPtr = std::shared_ptr<EventHandler>;

} // namespace reactor

#endif /* __EVENTHANDLERPTR_H__ */
