#include <stdlib.h>

#include <iostream>
#include <sstream>
#include <string>
#include <fstream>

#include <naeem/conf/config_manager.h>
#include <naeem/string/helper.h>


namespace naeem {
namespace conf {
  std::map<std::string, std::map<std::string, std::string>*> ConfigManager::values_;
  void
  ConfigManager::LoadFromFile(std::string confFilePath) {
    for (std::map<std::string, std::map<std::string, std::string>*>::iterator it = values_.begin();
         it != values_.end();
         it++) {
      delete it->second;
    }
    values_.clear();
    try {
      std::ifstream infile(confFilePath.c_str());
      std::string line;
      std::string currentSectionName = "general";
      values_.insert(std::pair<std::string, std::map<std::string, std::string>*>(
                  "general", new std::map<std::string, std::string>()));
      uint32_t lineCounter = 1;
      while (std::getline(infile, line)) {
        std::string trimmedLine = ::naeem::string::helper::Trim(line);
        if (trimmedLine.size() > 0) {
          if (!::naeem::string::helper::StartsWith(trimmedLine, "#")) {
            if (::naeem::string::helper::StartsWith(trimmedLine, "[")) {
              if (trimmedLine.size() <= 2) {
                std::cout << "ERROR: Invalid section name at line " << lineCounter << "." << std::endl;
                exit(1);
              }
              std::string sectionName = trimmedLine.substr(1, trimmedLine.size() - 2);
              if (!HasSection(sectionName)) {
                values_.insert(std::pair<std::string, std::map<std::string, std::string>*>(
                  sectionName, new std::map<std::string, std::string>()));
              }
            } else {
              std::vector<std::string> tokens = ::naeem::string::helper::Split(trimmedLine, '=');
              if (tokens.size() != 2) {
                std::cout << "ERROR: Invalid configuration at line " << lineCounter << "." << std::endl;
                exit(1);
              }
              values_[currentSectionName]->insert(std::pair<std::string, std::string>(
                ::naeem::string::helper::Trim(tokens[0]), 
                ::naeem::string::helper::Trim(tokens[1])));
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
    return values_[section]->find(entry) != values_[section]->end();

  }
  std::map<std::string, std::string>*
  ConfigManager::GetSection(std::string section) {
    if (!HasSection(section)) {
      return NULL;
    }
    return values_[section];
  }
  uint32_t
  ConfigManager::GetValueAsUInt32(std::string section, std::string etnry) {
    // TODO
    return 0;
  }
  uint32_t
  ConfigManager::GetValueAsInt32(std::string section, std::string etnry) {
    // TODO
    return 0;
  }
  std::string
  ConfigManager::GetValueAsString(std::string section, std::string etnry) {
    // TODO
    return "";
  }
}
}