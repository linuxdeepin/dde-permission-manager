#include <DApplication>
#include <QTranslator>

#include "clientadaptor.h"
#include "permissionadaptor.h"

DWIDGET_USE_NAMESPACE

int main(int argc, char** argv)
{
    auto               app     = DApplication::globalApplication(argc, argv);

    QTranslator translator;
    qDebug() << "language:" << QLocale::system().name();
    translator.load("/usr/share/permission/translations/deepin-permission-service_" + QLocale::system().name());
    app->installTranslator(&translator);

    PermissionClient*  client  = new PermissionClient;
    PermissionService* service = new PermissionService;

    new ClientAdaptor(client);
    new PermissionAdaptor(service);

    QDBusConnection::sessionBus().registerService("org.desktopspec.permission.Client");
    QDBusConnection::sessionBus().registerObject("/org/desktopspec/permission/Client", client);

    QDBusConnection::sessionBus().registerService("org.desktopspec.permission");
    QDBusConnection::sessionBus().registerObject("/org/desktopspec/permission", service);

    app->setQuitOnLastWindowClosed(false);

    return app->exec();
}
