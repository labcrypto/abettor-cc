#include <string.h>

#include <limits.h>
#include <unistd.h>

#include <org/labcrypto/abettor++/compat/types.h>
#include <org/labcrypto/abettor++/string/helper.h>
#include <org/labcrypto/abettor++/os/proc.h>


namespace naeem {
  namespace os {
    std::string 
    GetExecDir() {
      char result[PATH_MAX];
      ssize_t count = readlink("/proc/self/exe", result, PATH_MAX);
      std::string execPath(result, (count > 0) ? count : 0);
      std::string::size_type pos = execPath.find_last_of("/");
      return execPath.substr(0, pos);
    }
  }
}
