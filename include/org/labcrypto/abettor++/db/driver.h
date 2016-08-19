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

#ifndef _ORG_LABCRYPTO_ABETTOR__CC__DB__DRIVER_H_
#define _ORG_LABCRYPTO_ABETTOR__CC__DB__DRIVER_H_

#include <vector>
#include <string>
#include <map>

#include <org/labcrypto/abettor++/compat/types.h>


namespace org {
namespace labcrypto {
namespace abettor {
namespace db {
  class Data {
  public:
    Data(unsigned char *data = NULL, uint32_t length = 0, bool copy = false)
      : copy_(copy),
        data_(data),
        length_(length) {
      if (copy && length > 0) {
        data_ = new unsigned char[length];
        for (uint32_t i = 0; i < length; i++) {
          data_[i] = data[i];
        }
      }
    }
    virtual ~Data() {
      if (copy_) {
        delete [] data_;
      }
    }
  public:
    inline unsigned char* GetData() {
      return data_;
    }
    inline uint32_t GetLength() {
      return length_;
    }
    inline void SetData(unsigned char *data, uint32_t length) {
      data_ = data;
      length_ = length;
    }
  private:
    bool copy_;
    unsigned char *data_;
    uint32_t length_;
  };
  class ConnectionInfo {
  public:
    ConnectionInfo(std::string host,
                   uint16_t port,
                   std::string databaseName,
                   std::string user,
                   std::string password)
      : host_(host),
        port_(port),
        databaseName_(databaseName),
        user_(user),
        password_(password) {
    }
  public:
    std::string host_;
    uint16_t port_;
    std::string databaseName_;
    std::string user_;
    std::string password_;
  };
  class Row {
  public:
    Row() {}
    virtual ~Row() {
      for (uint32_t i = 0; i < buffers_.size(); i++) {
        delete buffers_[i];
      }
    }
  public:
    inline virtual void AddValue(std::string columnName, Data *data) {
      values_.insert(std::pair<std::string, Data*>(columnName, data));
      buffers_.push_back(data);
    }
    inline virtual Data* GetValue(std::string columnName) {
      return values_[columnName];
    }
    inline virtual uint32_t Size() {
      return values_.size();
    }
  public:
    inline virtual std::string GetValueAsStdString(std::string columnName) {
      Data *actualValue = GetValue(columnName);
      if (actualValue->GetLength() == 0) {
        return "";
      }
      return std::string((char *)actualValue->GetData());
    }
    inline virtual bool GetValueAsBoolean(std::string columnName) {
      std::string value = GetValueAsStdString(columnName);
      return value == "true"; 
    }
    inline virtual Data* GetValueAsByteArray(std::string columnName) {
      Data *actualValue = GetValue(columnName);
      if (actualValue->GetLength() == 0) {
        return new Data;
      }
      uint32_t length = (actualValue->GetLength() - 2) / 2;
      unsigned char *data = new unsigned char[length];
      uint32_t j = 0;
      for (uint32_t i = 2; i < actualValue->GetLength(); i += 2, j++) {
        uint8_t a = 0;
        if (actualValue->GetData()[i] >= 0x30 && actualValue->GetData()[i] <= 0x39) {
          a = actualValue->GetData()[i] - 0x30;
        } else if (actualValue->GetData()[i] == 'a' || actualValue->GetData()[i] == 'A') {
          a = 10;
        } else if (actualValue->GetData()[i] == 'b' || actualValue->GetData()[i] == 'B') {
          a = 11;
        } else if (actualValue->GetData()[i] == 'c' || actualValue->GetData()[i] == 'C') {
          a = 12;
        } else if (actualValue->GetData()[i] == 'd' || actualValue->GetData()[i] == 'D') {
          a = 13;
        } else if (actualValue->GetData()[i] == 'e' || actualValue->GetData()[i] == 'E') {
          a = 14;
        } else if (actualValue->GetData()[i] == 'f' || actualValue->GetData()[i] == 'F') {
          a = 15;
        }
        uint8_t b = 0;
        if (actualValue->GetData()[i + 1] >= 0x30 && actualValue->GetData()[i + 1] <= 0x39) {
          b = actualValue->GetData()[i + 1] - 0x30;
        } else if (actualValue->GetData()[i + 1] == 'a' || actualValue->GetData()[i + 1] == 'A') {
          b = 10; 
        } else if (actualValue->GetData()[i + 1] == 'b' || actualValue->GetData()[i + 1] == 'B') {
          b = 11;
        } else if (actualValue->GetData()[i + 1] == 'c' || actualValue->GetData()[i + 1] == 'C') {
          b = 12;
        } else if (actualValue->GetData()[i + 1] == 'd' || actualValue->GetData()[i + 1] == 'D') {
          b = 13;
        } else if (actualValue->GetData()[i + 1] == 'e' || actualValue->GetData()[i + 1] == 'E') {
          b = 14;
        } else if (actualValue->GetData()[i + 1] == 'f' || actualValue->GetData()[i + 1] == 'F') {
          b = 15;
        }
        data[j] = 16 * a + b;
      }
      Data *result = new Data(data, length, true);
      delete [] data;
      return result;
    }
  private:
    std::map<std::string, Data*> values_;
    std::vector<Data*> buffers_;
  };
  class Driver {
  public:
    Driver(ConnectionInfo *connnectionInfo) 
      : connectionInfo_(connnectionInfo){
    }
    virtual ~Driver() {
      delete connectionInfo_;
    }
  public:
    virtual void Open() = 0;
    virtual void Execute(const char *) = 0;
    virtual void Execute(const char *, std::vector<Data*> &) = 0;
    virtual void Execute(const char *, std::vector<Row*> &) = 0;
    virtual void Execute(const char *, std::vector<Data*> &, std::vector<Row*> &) = 0;
    virtual void Close() = 0;
  protected:
    ConnectionInfo *connectionInfo_;
  };
}
}
}
}

#endif
