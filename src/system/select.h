#include <vector>

namespace sys {

int select(std::vector<int>& ioReadFds,
           std::vector<int>& ioWriteFds,
           std::vector<int>& ioExceptFds,
           int timeoutSeconds = 0);

} // namespace sys
