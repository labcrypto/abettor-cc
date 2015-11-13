#include <naeem/db/pgsql/driver.h>
#include <naeem/db/exception.h>

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
        if (conn_) {
          Close();
        }
        conn_ = PQconnectdb("dbname=test_db user=test_user password=12345 hostaddr=192.168.1.54");
        if (PQstatus(conn_) != CONNECTION_OK) {
          char message[256];
          sprintf(message, "Connection to database failed: %s", PQerrorMessage(conn_));
          PQfinish(conn_);
          conn_ = 0;
          throw ::naeem::db::Exception(message);
        }
      }
      void
      Driver::Execute(const char *query) {
        if (!conn_) {
          throw new ::naeem::db::Exception("Query failed: Connection is not opened.");
        }
        PGresult *res = PQexec(conn_, query);
        if (PQresultStatus(res) != PGRES_COMMAND_OK) {
          char message[256];
          sprintf(message, "Query failed: %s", PQerrorMessage(conn_));
          PQclear(res);
          PQfinish(conn_);
          conn_ = 0;
          throw ::naeem::db::Exception(message);
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
