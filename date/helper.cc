#include <string>
#include <time.h>

#include <org/labcrypto/abettor++/date/helper.h>


namespace naeem {
  namespace date {
    namespace helper {
      std::string 
      GetCurrentUTCTimeString() {
        time_t     now = time(0);
        struct tm  tstruct;
        char       buffer[80];
        tstruct = *gmtime(&now);
        strftime(buffer, sizeof(buffer), "%Y-%m-%d.%X UTC", &tstruct);
        return buffer;
      }
    }
  }
}
