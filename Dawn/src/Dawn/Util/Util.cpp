#include "Util.h"

#ifdef __GNUC__ || __MINGW32__ || __MINGW64__

#include <unistd.h>

namespace Dawn
{
    //Note that this may not work on all platforms
#define MAX_DIR_BUF_SIZE 200
    std::string GetWorkingDirectory()
    {
        char buf[MAX_DIR_BUF_SIZE];
        getcwd(buf, MAX_DIR_BUF_SIZE);
        std::string currentDir(buf);
        return currentDir;
    }
}  // namespace Dawn

#endif