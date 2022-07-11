#include <QDBusInterface>
#include <QDBusConnectionInterface>
#include <QDBusMessage>
#include <QDebug>
#include <QVariant>

#include <polkit-qt5-1/PolkitQt1/Authority>

#include "common.h"

using namespace PolkitQt1;

bool checkAuth(const QString &actionId)
{
    Authority::Result authenticationResult;
    authenticationResult = Authority::instance()->checkAuthorizationSync(actionId, UnixProcessSubject(getpid()),
                                                           Authority::AllowUserInteraction);

    qWarning() << "authenticationResult: " << authenticationResult;
    if (Authority::Result::Yes != authenticationResult) {
        return false;
    }

    return true;
}

UserType checkUserIsAdmin()
{
    struct passwd *user = getpwuid(getuid());
    if (!user) {
        qWarning() << "call getpwuid failed";
        return UserTypeInvalid;
    }

    QDBusInterface inter = QDBusInterface("com.deepin.daemon.Accounts",
                "/com/deepin/daemon/Accounts",
                "com.deepin.daemon.Accounts",
                QDBusConnection::systemBus());

    QDBusReply<QString> reply = inter.call("FindUserByName", QString(user->pw_name));
    if (!reply.isValid()) {
        qWarning() << "call FindUserByName failed: " << reply.error();
        return UserTypeInvalid;
    }

    QString path = reply.value();
    QDBusInterface inter1 = QDBusInterface("com.deepin.daemon.Accounts",
                path,
                "com.deepin.daemon.Accounts.User",
                QDBusConnection::systemBus());

    QVariant ret = inter1.property("AccountType");
    return UserType(ret.toInt());
}