#include <DApplication>
#include <QTranslator>

#include "clientadaptor.h"
#include "permission1adaptor.h"

DWIDGET_USE_NAMESPACE

int main(int argc, char** argv)
{
    auto               app     = DApplication::globalApplication(argc, argv);

    QTranslator translator;
    qDebug() << "language:" << QLocale::system().name();
    translator.load("/usr/share/permission/translations/dde-permission-manager_" + QLocale::system().name());
    app->installTranslator(&translator);

    PermissionClient*  client  = new PermissionClient;
    PermissionService* service = new PermissionService;

    new ClientAdaptor(client);
    new Permission1Adaptor(service);

    QDBusConnection::sessionBus().registerService("org.deepin.dde.Permission1.Client");
    QDBusConnection::sessionBus().registerObject("/org/deepin.dde/Permission1/Client", client);

    QDBusConnection::sessionBus().registerService("org.deepin.dde.Permission1");
    QDBusConnection::sessionBus().registerObject("/org/deepin.dde/Permission1", service);

    app->setQuitOnLastWindowClosed(false);

    return app->exec();
}
