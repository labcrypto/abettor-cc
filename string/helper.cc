/*  The MIT License (MIT)
 *
 *  Copyright (c) 2015 LabCrypto Org.
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a copy
 *  of this software and associated documentation files (the "Software"), to deal
 *  in the Software without restriction, including without limitation the rights
 *  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *  copies of the Software, and to permit persons to whom the Software is
 *  furnished to do so, subject to the following conditions:
 *  
 *  The above copyright notice and this permission notice shall be included in all
 *  copies or substantial portions of the Software.
 *  
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 *  SOFTWARE.
 */
 
#include <string.h>

#include <sstream>
#include <algorithm>
#include <functional> 
#include <cctype>
#include <locale>

#include <org/labcrypto/abettor++/compat/types.h>
#include <org/labcrypto/abettor++/string/helper.h>


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
