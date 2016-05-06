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
 
#include <stdlib.h>

#include <iostream>
#include <stdexcept>
#include <sstream>
#include <string>
#include <fstream>
#include <algorithm>

#include <org/labcrypto/abettor++/conf/config_manager.h>
#include <org/labcrypto/abettor++/string/helper.h>
#include <org/labcrypto/abettor++/date/helper.h>


namespace org {
namespace labcrypto {
namespace abettor {
namespace conf {
  std::map<std::string, std::map<std::string, std::string>*> ConfigManager::values_;
  void
  ConfigManager::Clear() {
    for (std::map<std::string, std::map<std::string, std::string>*>::iterator it = values_.begin();
         it != values_.end();
         it++) {
      delete it->second;
    }
    values_.clear();
  }
  void
  ConfigManager::LoadFromFile(std::string confFilePath) {
    try {
      std::ifstream infile(confFilePath.c_str());
      std::string line;
      std::string currentSectionName = "general";
      values_.insert(std::pair<std::string, std::map<std::string, std::string>*>(
                  "general", new std::map<std::string, std::string>()));
      uint32_t lineCounter = 1;
      while (std::getline(infile, line)) {
        std::string trimmedLine = ::org::labcrypto::abettor::string::helper::Trim(line);
        if (trimmedLine.size() > 0) {
          if (!::org::labcrypto::abettor::string::helper::StartsWith(trimmedLine, "#")) {
            if (::org::labcrypto::abettor::string::helper::StartsWith(trimmedLine, "[")) {
              if (trimmedLine.size() <= 2) {
                std::cout << "ERROR: Invalid section name at line " << lineCounter << "." << std::endl;
                exit(1);
              }
              std::string sectionName = trimmedLine.substr(1, trimmedLine.size() - 2);
              // std::cout << "Section found: " << sectionName << std::endl;
              if (!HasSection(sectionName)) {
                values_.insert(std::pair<std::string, std::map<std::string, std::string>*>(
                  sectionName, new std::map<std::string, std::string>()));
              }
              currentSectionName = sectionName;
            } else {
              std::vector<std::string> tokens = ::org::labcrypto::abettor::string::helper::Split(trimmedLine, '=');
              if (tokens.size() != 2) {
                std::cout << "ERROR: Invalid configuration at line " << lineCounter << "." << std::endl;
                exit(1);
              }
              std::string key = ::org::labcrypto::abettor::string::helper::Trim(tokens[0]);
              std::string value = ::org::labcrypto::abettor::string::helper::Trim(tokens[1]);
              // std::cout << "Adding pair: '" << tokens[0] << "' -> '" << tokens[1] << "'" << std::endl;
              values_[currentSectionName]->insert(std::pair<std::string, std::string>(key, value));
            }
          }
        }
        lineCounter++;
      }
    } catch (...) {
      std::cout << "ERROR: Error while processing configuration file." << std::endl;
      exit(1);
    }
  }
  void
  ConfigManager::LoadFromEnvironmentVariables() {
    // TODO
  }
  void
  ConfigManager::LoadFromCommandLineArguments(int argc, char **argv) {
    // TODO
  }
  bool
  ConfigManager::HasSection(std::string section) {
    return values_.find(section) != values_.end();
  }
  bool
  ConfigManager::HasValue(std::string section, std::string entry) {
    if (!HasSection(section)) {
      return false;
    }
    std::map<std::string, std::string> *m = GetSection(section);
    return (*m).find(entry) != (*m).end();

  }
  std::map<std::string, std::string>*
  ConfigManager::GetSection(std::string section) {
    if (!HasSection(section)) {
      std::stringstream ss;
      ss << "Section '" << section << "' is not found.";
      throw std::runtime_error(ss.str());
    }
    return values_[section];
  }
  uint32_t
  ConfigManager::GetValueAsUInt32(std::string section, std::string entry) {
    if (!HasValue(section, entry)) {
      std::stringstream ss;
      ss << "Value '" << section << "." << entry << "' is not found.";
      throw std::runtime_error(ss.str());
    }
    std::map<std::string, std::string> *m = GetSection(section);
    return strtoul((*m)[entry].c_str(), NULL, 0);
  }
  int32_t
  ConfigManager::GetValueAsInt32(std::string section, std::string entry) {
    if (!HasValue(section, entry)) {
      std::stringstream ss;
      ss << "Value '" << section << "." << entry << "' is not found.";
      throw std::runtime_error(ss.str());
    }
    std::map<std::string, std::string> *m = GetSection(section);
    return atol((*m)[entry].c_str());
  }
  std::string
  ConfigManager::GetValueAsString(std::string section, std::string entry) {
    if (!HasValue(section, entry)) {
      std::stringstream ss;
      ss << "Value '" << section << "." << entry << "' is not found.";
      throw std::runtime_error(ss.str());
    }
    std::map<std::string, std::string> *m = GetSection(section);
    return (*m)[entry];
  }
  bool
  ConfigManager::GetValueAsBoolean(std::string section, std::string entry) {
    if (!HasValue(section, entry)) {
      std::stringstream ss;
      ss << "Value '" << section << "." << entry << "' is not found.";
      throw std::runtime_error(ss.str());
    }
    std::map<std::string, std::string> *m = GetSection(section);
    std::string val = (*m)[entry];
    std::transform(val.begin(), val.end(), val.begin(), ::tolower);
    if (val == "false" || val == "f" || val == "0") {
      return false;
    }
    return true;
  }
  void
  ConfigManager::Print() {
    std::cout << "==========================================" << std::endl;
    std::cout << "Configuration" << std::endl;
    std::cout << "Time: [" << ::org::labcrypto::abettor::date::helper::GetCurrentUTCTimeString() << "]" << std::endl;
    std::cout << "==========================================" << std::endl;
    for (std::map<std::string, std::map<std::string, std::string>*>::iterator it = values_.begin();
         it != values_.end();
         it++) {
      std::cout << "[" << it->first << "]" << std::endl;
      for (std::map<std::string, std::string>::iterator it2 = it->second->begin();
           it2 != it->second->end();
           it2++) {
        std::cout << "  '" << it2->first << "' -> '" << it2->second << "'" << std::endl;
      }
    }
    std::cout << "==========================================" << std::endl;
  }
}
}
}
}
