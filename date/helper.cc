#include <string>
#include <time.h>

#include <naeem++/date/helper.h>


namespace naeem {
  namespace date {
    namespace helper {
      std::string 
      GetCurrentTime() {
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
