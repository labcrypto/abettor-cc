#include <algorithm>
#include <functional> 
#include <cctype>
#include <locale>

#include <naeem/string/helper.h>


namespace naeem {
  namespace string {
    namespace helper {
      std::string& 
      LeftTrim(std::string &s) {
        s.erase(s.begin(), std::find_if(s.begin(), s.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
        return s;
      }
      std::string&
      RightTrim(std::string &s) {
        s.erase(std::find_if(s.rbegin(), s.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
        return s;
      }
      std::string& 
      Trim(std::string &s) {
        return LeftTrim(RightTrim(s));
      }
    }
  }
}
