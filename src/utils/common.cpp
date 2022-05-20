#include "common.h"

#include <QDBusInterface>
#include <QDBusConnectionInterface>
#include <QDBusMessage>

#include <QDebug>

UserType checkUserIsAdmin() {
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
