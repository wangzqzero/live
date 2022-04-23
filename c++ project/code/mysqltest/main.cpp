//#include <stdio.h>

// #include <mysql.h>
//#include <mysql++/mysql++.h>



// int main(int argc,char *argv[])

// {

//     MYSQL conn;

//     int res;

//     mysql_init(&conn);

//     if(mysql_real_connect(&conn,"localhost","root","","test",0,NULL,CLIENT_FOUND_ROWS)) //"root":数据库管理员 "":root密码 "test":数据库的名字

//     {
//        printf("connect success!\n");
//        res=mysql_query(&conn,"insert into test values(\'userf\',\'1234568\')");
//        if(res)
//        {
//            printf("error\n");
//        }else{
//            printf("OK\n");
//        }
//        mysql_close(&conn);

//     }

//     return 0;

// }

#include <mysql++/mysql++.h>
#include <iostream>

using namespace std;
int main()
{
  const char* db = 0, *server = 0, *user = 0, *password = "";
  db = "test";
  server = "localhost";
  user = "root";
  password = "";

  mysqlpp::Connection conn(false);
  if (conn.connect(db, server, user, password))
  {
    cout << "connect db succeed. " << endl;
    mysqlpp::Query query = conn.query("SELECT * FROM test");
    if (mysqlpp::StoreQueryResult res = query.store())
    {
      cout.setf(ios::left);
      cout << setw(31) << "Sid" <<
      setw(10) << "Sname" << endl;

      mysqlpp::StoreQueryResult::const_iterator it;
      for (it = res.begin(); it != res.end(); ++it)
      {
        mysqlpp::Row row = *it;
        cout << setw(30) << row[0] << ' ' <<
        setw(9) << row[1] << ' ' <<endl;
      }
    }
  }
  else
  {
      cout << "connect db fail. " << endl;
  }
  return 0;
}

