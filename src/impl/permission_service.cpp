#include "permission_service.h"
#include "permissionoption.h"

#include <QDBusConnectionInterface>
#include <QDBusMessage>
#include <QDebug>
#include <QException>

#include "settings.h"
#include "clientinterface.h"
#include "permissionpolicy.h"

PermissionService::PermissionService(QObject *parent) : QObject(parent), QDBusContext()
{
    qRegisterMetaType<IntArray>("IntArray");
}

PermissionService::~PermissionService() {}

QStringList PermissionService::PermissionList(const QString &permissionGroup)
{
    return PermissionPolicy::getPolicyList(permissionGroup);
}

int PermissionService::Request(const QString &appId, const QString &permissionGroup, const QString &permissionId)
{
    PermissionPolicy policy(permissionGroup, permissionId);
    if (!policy.isValid()) {
        return -1;
    }

    return Request(appId, permissionGroup, permissionId, policy.title(), policy.description());
}

int PermissionService::Request(const QString &appId, const QString &permissionGroup, const QString &permissionId, const QString &title, const QString &description)
{
    PermissionPolicy policy(permissionGroup, permissionId);
    if (!policy.isValid()) {
        return -1;
    }
    // TODO: control
    // const QDBusConnection &conn = connection();
    // const QDBusMessage    &msg  = message();
    // const uint            &uid  = conn.interface()->serviceUid(msg.service()).value();
    // const uint            &pid  = conn.interface()->servicePid(msg.service()).value();

    // show the box
    auto func = [appId, permissionGroup, permissionId, policy, title, description] {
        Settings settings;
        try {
            auto result = settings.result(appId, permissionGroup, permissionId);
            return result;
        }
        catch (QException &exp) {
            // show gui
            org::desktopspec::permission::client client("org.desktopspec.permission.Client", "/org/desktopspec/permission/Client", QDBusConnection::sessionBus());
            auto                                 reply = client.Request(title.arg(appId), description, policy.prefer(), policy.options());
            reply.waitForFinished();
            if (reply.isError()) {
                qWarning() << "[DBus] [Warning] " << reply.error();
                return -2;
            }

            if (!policy.options().contains(reply.value())) {
                return -2;
            }

            SettingData data{
                appId,
                permissionGroup,
                permissionId,
                PermissionOption::getInstance()->getId(reply.value()),
            };

            if (PermissionOption::getInstance()->isNeedSaved(reply.value())) {
                settings.saveSettings(data);
            }
            return data.Result;
        }
    };

    return func();
}

IntArray PermissionService::Request(const QString &appId, const QString &permissionGroup, const QStringList &permissionId)
{
    // check valid before Request
    for (const QString &id : permissionId) {
        // TODO
        Q_UNUSED(id)
    }

    IntArray result;
    for (const QString &id : permissionId) {
        // read permission description
        result << Request(appId, permissionGroup, id);
    }

    return result;
}

void PermissionService::Reset(const QString &appId, const QString &permissiongGroup) 
{
    Settings settings;
    settings.removeSettings(appId, permissiongGroup);
}
void PermissionService::Set(const QString &appId, const QString &permissionGroup, const QString &permissionId, const int &value) 
{
    SettingData data{
        appId,
        permissionGroup,
        permissionId,
        value,
    };
    Settings settings;
    if (PermissionOption::getInstance()->isNeedSavedByIndex(value)) {
        settings.saveSettings(data);
    }
}
