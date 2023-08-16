#include "MyApp.h"
#include "connection.h"
int main()
{
  MyApp app;
  app.Run();
  cosc345::Connection con;
  con.est_conn();
  cout << "Here" << endl;
  cout << con.getSizeFood() << endl;
  return 0;
}
