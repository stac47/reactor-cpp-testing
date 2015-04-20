#ifndef __REACTORSELECTIMPL_H__
#define __REACTORSELECTIMPL_H__

#include "ReactorInterface.h"

namespace reactor {

class ReactorSelectImpl : public ReactorInterface {
protected:
    virtual void run() override;
};

} // namespace reactor
#endif /* __REACTORSELECTIMPL_H__ */
