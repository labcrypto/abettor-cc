#include <naeem/db/pgsql/driver.h>

namespace naeem {
  namespace db {
    namespace pgsql {
      Driver::Driver(ConnectionInfo &connectionInfo)
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
        conn_ = PQconnectdb("dbname=test_db user=test_user password=12345 hostaddr=192.168.1.54");
        if (PQstatus(conn_) != CONNECTION_OK) {
              fprintf(stderr, "Connection to database failed: %s",
                      PQerrorMessage(conn_));
              PQfinish(conn_);
          exit(1);
          }
      }

      void
      Driver::Execute(std::wstring &query) {
        char queryStr[1024];
          std::wcstombs(queryStr, query.c_str(), 1024);
        PGresult *res = PQexec(conn_, queryStr);
        if (PQresultStatus(res) != PGRES_COMMAND_OK) {
              fprintf(stderr, "Query failed: %s",
                      PQerrorMessage(conn_));
              PQclear(res);
              PQfinish(conn_);
          exit(1);
          }
        printf("Query - OK\n");
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
