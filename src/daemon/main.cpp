#include "lpsdbus.h"
#include "lpsmagicadaptor.h"
#include <QCoreApplication>
#include <QDBusConnection>

int main(int argc, char **argv){
  QCoreApplication app(argc,argv);
  LpsDbus *dbus=new LpsDbus;
  new LpsmagicAdaptor(dbus);
  if(!QDBusConnection::systemBus().registerService("org.admiral0.lpsmagic")){
     return 1;
  }
  QDBusConnection::systemBus().registerObject("/",dbus);
  return app.exec();
}