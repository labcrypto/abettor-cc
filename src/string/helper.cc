#include <algorithm>
#include <functional> 
#include <cctype>
#include <locale>

#include <naeem/string/helper.h>


namespace naeem {
  namespace string {
    namespace helper {
      bool 
      StartsWith(std::string &str, 
                 std::string s) {
        const char *strCharArray = str.c_str();
        const char *sCharArray = s.c_str();
        return strncmp((char *)sCharArray, (char *)strCharArray, strlen(sCharArray)) == 0;
      } 
      std::string 
      Replace(std::string s,
              const std::string toReplace,
              const std::string replaceWith) {
        std::string result = s;
        std::size_t index = result.find(toReplace);
        while (index != std::string::npos) {
          result = result.replace(index, toReplace.length(), replaceWith);
          index = result.find(toReplace);
        }
        return result;
      }
      std::vector<std::string> 
      Split(std::string str, 
            char separator) {
        std::vector<std::string> tokens;
        std::istringstream f(str);
        std::string s;    
        while (getline(f, s, separator)) {
          tokens.push_back(s);
        }
        return tokens;
      }
      std::string
      Concat(std::vector<std::string> strs, 
             std::string separator) {
        std::string result;
        std::string del = "";
        for (uint32_t i = 0; i < strs.size(); i++) {
          result += del + strs[i];
          del = separator;
        }
        return result;
      }
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
