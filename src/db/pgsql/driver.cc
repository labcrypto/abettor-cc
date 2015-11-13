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

      bool
      Driver::Open() {
        if (conn_) {
          Close();
        }
        conn_ = PQconnectdb("dbname=test_db user=test_user password=12345 hostaddr=192.168.1.54");
        if (PQstatus(conn_) != CONNECTION_OK) {
          fprintf(stderr, "Connection to database failed: %s",
                  PQerrorMessage(conn_));
          PQfinish(conn_);
          conn_ = 0;
          return false;
        }
        return true;
      }
      bool
      Driver::Execute(const char *query) {
        if (!conn_) {
          fprintf(stderr, "Query failed: Connection is not opened.\n");
          return false;
        }
        PGresult *res = PQexec(conn_, query);
        if (PQresultStatus(res) != PGRES_COMMAND_OK) {
          fprintf(stderr, "Query failed: %s",
                  PQerrorMessage(conn_));
          PQclear(res);
          PQfinish(conn_);
          conn_ = 0;
          return false;
        }
        printf("Query - OK\n");
        PQclear(res);
        return true;
      }
      bool 
      Driver::Close() {
        if (conn_) {
          PQfinish(conn_);
          conn_ = 0;
          return true;
        }
        return false;
      }
    }
  }
}
