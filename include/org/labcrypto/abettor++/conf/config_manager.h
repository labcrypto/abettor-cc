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

#ifndef _ORG_LABCRYPTO_ABETTOR__CC__CONF__CONF_MANAGER_H_
#define _ORG_LABCRYPTO_ABETTOR__CC__CONF__CONF_MANAGER_H_

#include <vector>
#include <string>
#include <map>

#include <org/labcrypto/abettor++/compat/types.h>


namespace org {
namespace labcrypto {
namespace abettor {
namespace conf {
  class ConfigManager {
  public:
    static void Clear();
    static void LoadFromFile(std::string confFilePath);
    static void LoadFromEnvironmentVariables();
    static void LoadFromCommandLineArguments(int argc, char **argv);
    static bool HasSection(std::string section);
    static bool HasValue(std::string section, std::string entry);
    static std::map<std::string, std::string>* GetSection(std::string section);
    static uint32_t GetValueAsUInt32(std::string section, std::string entry);
    static int32_t GetValueAsInt32(std::string section, std::string entry);
    static std::string GetValueAsString(std::string section, std::string entry);
    static bool GetValueAsBoolean(std::string section, std::string entry);
    static void Print();
  private:
    static std::map<std::string, std::map<std::string, std::string>*> values_;
  };
}
}
}
}

#endif