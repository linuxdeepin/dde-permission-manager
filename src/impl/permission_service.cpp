#include "permission_service.h"

#include <QDBusConnectionInterface>
#include <QDBusMessage>
#include <QDebug>
#include <QException>

#include "../settings/settings.h"
#include "clientinterface.h"
#include "permissionpolicy.h"

PermissionService::PermissionService(QObject *parent) : QObject(parent), QDBusContext()
{
    qRegisterMetaType<IntArray>("IntArray");
}

PermissionService::~PermissionService() {}

int PermissionService::request(const QString &appid, const QString &permissionid)
{
    PermissionPolicy policy(permissionid);
    if (!policy.isValid()) {
        return -1;
    }

    return request(appid, permissionid, policy.description());
}

int PermissionService::request(const QString &appid, const QString &permissionid, const QString &description)
{
    PermissionPolicy policy(permissionid);
    if (!policy.isValid()) {
        return -1;
    }

    const QDBusConnection &conn = connection();
    const QDBusMessage    &msg  = message();
    const uint            &uid  = conn.interface()->serviceUid(msg.service()).value();
    const uint            &pid  = conn.interface()->servicePid(msg.service()).value();

    // show the box
    auto func = [appid, permissionid, policy, description] {
        Settings settings;
        try {
            auto result = settings.result(appid, permissionid);
            return result;
        }
        catch (QException exp) {
            // show gui
            org::desktopspec::permission::client client("org.desktopspec.permission.Client", "/org/desktopspec/permission/Client", QDBusConnection::sessionBus());
            auto                                 reply = client.request(description.arg(appid), policy.options());
            reply.waitForFinished();
            if (reply.isError()) {
                qWarning() << "[DBus] [Warning] " << reply.error();
                return -2;
            }

            if (!policy.options().contains(reply.value())) {
                return -2;
            }

            // fake data
            SettingData data{
                appid,
                permissionid,
                policy.options().indexOf(reply.value()),
            };

            if (reply.value() == "allow_once" || reply.value() == "deny_once") {
                return data.Result;
            }

            settings.saveSettings(data);
            return data.Result;
        }
    };

    return func();
}

IntArray PermissionService::request(const QString &appid, const QStringList &permissionid)
{
    // check valid before request
    for (const QString &id : permissionid) {
    }

    IntArray result;
    for (const QString &id : permissionid) {
        // read permission description
        result << request(appid, id);
    }

    return result;
}

void PermissionService::reset(const QString &appid) {}
void PermissionService::set(const QString &appid, const QString &permission) {}
