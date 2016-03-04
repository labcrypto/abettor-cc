#include <iostream>
#include <stdexcept>

#include <naeem++/db/pgsql/driver.h>


namespace naeem {
  namespace db {
    namespace pgsql {
      Driver::Driver(ConnectionInfo *connectionInfo)
		    : ::naeem::db::Driver(connectionInfo),
          conn_(NULL) {
      }
      Driver::~Driver() {
        if (conn_) {
          PQfinish(conn_);
        }
      }

      void
      Driver::Open() {
        if (conn_) {
          Close();
        }
        char connString[1024];
        /*std::cout << connectionInfo_->databaseName_ << std::endl;
        std::cout << connectionInfo_->user_ << std::endl;
        std::cout << connectionInfo_->password_ << std::endl;
        std::cout << connectionInfo_->host_ << std::endl;*/
        sprintf(connString, 
                "dbname=%s user=%s password=%s hostaddr=%s",
                connectionInfo_->databaseName_.c_str(),
                connectionInfo_->user_.c_str(),
                connectionInfo_->password_.c_str(),
                connectionInfo_->host_.c_str()); 
        // std::cout << "Connection String: " << connString << std::endl;
        conn_ = PQconnectdb(connString);
        if (PQstatus(conn_) != CONNECTION_OK) {
          char message[256];
          sprintf(message, "Connection to database failed: %s", PQerrorMessage(conn_));
          PQfinish(conn_);
          conn_ = 0;
          throw std::runtime_error(message);
        }
      }
      void
      Driver::Execute(const char *query) {
        if (!conn_) {
          throw std::runtime_error("Connection is not opened.");
        }
        PGresult *res = PQexec(conn_, query);
        if (PQresultStatus(res) != PGRES_COMMAND_OK) {
          char message[1024];
          sprintf(message, "%s", PQerrorMessage(conn_));
          // PQclear(res);
          PQfinish(conn_);
          conn_ = 0;
          throw std::runtime_error(message);
        }
        // printf("Query - OK\n");
        PQclear(res);
      }
      void
      Driver::Execute(const char *query, std::vector<Data*> &data) {
        if (!conn_) {
          throw std::runtime_error("Connection is not opened.");
        }
        const char *values[10];
        for (uint32_t i = 0; i < data.size() && i < 10; i++) {
          values[i] = (char *)data[i]->GetData();
        }
        int lengths[10] = {0};
        for (uint32_t i = 0; i < data.size() && i < 10; i++) {
          lengths[i] = data[i]->GetLength();
        }
        int binaries[10] = {1};
        for (uint32_t i = 0; i < data.size() && i < 10; i++) {
          binaries[i] = 1;
        }
        PGresult *res = 
          PQexecParams(
            conn_, 
            query, 
            data.size() > 10 ? 10 : data.size(), 
            NULL, 
            values, 
            lengths, 
            binaries, 
            0
          );
        if (PQresultStatus(res) != PGRES_TUPLES_OK) {
          char message[1024];
          sprintf(message, "%s", PQerrorMessage(conn_));
          PQclear(res);
          PQfinish(conn_);
          conn_ = 0;
          throw std::runtime_error(message);
        }
        PQclear(res);
      }
      void
      Driver::Execute(const char *query, std::vector<Row*> &rows) {
        if (!conn_) {
          throw std::runtime_error("Connection is not opened.");
        }
        PGresult *res = PQexec(conn_, query);
        if (PQresultStatus(res) != PGRES_TUPLES_OK) {
          char message[1024];
          sprintf(message, "%s", PQerrorMessage(conn_));
          // PQclear(res);
          PQfinish(conn_);
          conn_ = 0;
          throw std::runtime_error(message);
        }
        // printf("Query - OK\n");
        uint16_t nfields = PQnfields(res);
        uint16_t ntuples = PQntuples(res);
        for(uint16_t i = 0; i < ntuples; i++) {
          Row *row = new Row();
          for(uint16_t j = 0; j < nfields; j++) {
            if (!PQgetisnull(res, i, j)) {
              row->AddValue(PQfname(res, j), new Data((unsigned char *)PQgetvalue(res, i, j), PQgetlength(res, i, j), true));
            } else {
              row->AddValue(PQfname(res, j), new Data(NULL, 0));
            }
          }
          rows.push_back(row);
        }
        PQclear(res);
      }
      void
      Driver::Execute(const char *query, std::vector<Data*> &data, std::vector<Row*> &rows) {
        if (!conn_) {
          throw std::runtime_error("Connection is not opened.");
        }
        const char *values[10];
        for (uint32_t i = 0; i < data.size() && i < 10; i++) {
          values[i] = (char *)data[i]->GetData();
        }
        int lengths[10] = {0};
        for (uint32_t i = 0; i < data.size() && i < 10; i++) {
          lengths[i] = data[i]->GetLength();
        }
        int binaries[10] = {1};
        for (uint32_t i = 0; i < data.size() && i < 10; i++) {
          binaries[i] = 1;
        }
        PGresult *res = 
          PQexecParams(
            conn_, 
            query, 
            data.size() > 10 ? 10 : data.size(), 
            NULL, 
            values, 
            lengths, 
            binaries, 
            0
          );
        if (PQresultStatus(res) != PGRES_TUPLES_OK) {
          char message[1024];
          sprintf(message, "%s", PQerrorMessage(conn_));
          PQclear(res);
          PQfinish(conn_);
          conn_ = 0;
          throw std::runtime_error(message);
        }
        // printf("Query - OK\n");
        uint16_t nfields = PQnfields(res);
        uint16_t ntuples = PQntuples(res);
        for(uint16_t i = 0; i < ntuples; i++) {
          Row *row = new Row();
          for(uint16_t j = 0; j < nfields; j++) {
            if (!PQgetisnull(res, i, j)) {
              row->AddValue(PQfname(res, j), new Data((unsigned char *)PQgetvalue(res, i, j), PQgetlength(res, i, j), true));
            } else {
              row->AddValue(PQfname(res, j), new Data(NULL, 0));
            }
          }
          rows.push_back(row);
        }
        PQclear(res);
      }
      void 
      Driver::Close() {
        if (conn_) {
          PQfinish(conn_);
          conn_ = 0;
        }
      }
    }
  }
}
