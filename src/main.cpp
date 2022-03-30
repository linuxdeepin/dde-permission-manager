#include <DApplication>

#include "clientadaptor.h"
#include "permissionadaptor.h"

DWIDGET_USE_NAMESPACE

int main(int argc, char** argv)
{
    auto               app     = DApplication::globalApplication(argc, argv);
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
