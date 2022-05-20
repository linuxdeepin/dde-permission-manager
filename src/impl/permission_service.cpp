#include "permission_service.h"
#include "permissionoption.h"

#include <QDBusConnectionInterface>
#include <QDBusMessage>
#include <QDebug>
#include <QException>

#include "settings.h"
#include "clientinterface.h"
#include "../utils/common.h"
#include "../utils/phase_pm_dconfig.h"

DCORE_USE_NAMESPACE
const QString systemAppPermissionRegistKey = "System_App_Permissions_Regist_Info";
const QString sessionAppPermissionDconfKey = "Session_App_Permissions_List";
const QString systemAppPermissionDconfKey = "System_App_Permissions_List";
const QString dbusErrorName = "org.desktopspec.permission.";

PermissionService::PermissionService(QObject *parent) : QObject(parent), QDBusContext()
{
    registerPermissionsInfoMetaType();
}

PermissionService::~PermissionService()
{
}

QStringList PermissionService::PermissionList(const QString &permissionGroup)
{
    return PermissionPolicy::getPolicyList(permissionGroup);
}

QString PermissionService::Request(const QString &appId, const QString &permissionGroup, const QString &permissionId)
{
    PermissionPolicy policy(permissionGroup, permissionId);
    if (!policy.isValid()) {
        qWarning() << "Request policy invalid.";
        sendErrorReply(dbusErrorName + "PermissionPolicyError","Permission instance JSON file error.");
        return "";
    }

    return Request(appId, permissionGroup, permissionId, policy.title("requestPermission"), policy.description("requestPermission"));
}

QString PermissionService::Request(const QString &appId, const QString &permissionGroup, const QString &permissionId, const QString &title, const QString &description)
{
    PermissionPolicy policy(permissionGroup, permissionId);
    if (!policy.isValid()) {
        qWarning() << "Request policy invalid.";
        sendErrorReply(dbusErrorName + "PermissionPolicyError","Permission instance JSON file error.");
        return "";
    }

    QString ret = "";
    if (policy.type() == "session") {
        ret = parseAppPermissionKeyDconf(sessionAppPermissionDconfKey, appId, permissionGroup, permissionId, policy, title, description);
    } else if (policy.type() == "system") {
        ret = parseAppPermissionKeyDconf(systemAppPermissionDconfKey, appId, permissionGroup, permissionId, policy, title, description);
    } else {
        sendErrorReply(dbusErrorName + "PermissionPolicyError","Permission instance JSON file error.");
        return "";
    }

    return ret;
}

QStringList PermissionService::Request(const QString &appId, const QString &permissionGroup, const QStringList &permissionId)
{
    // check valid before Request
    for (const QString &id : permissionId) {
        // TODO
        Q_UNUSED(id)
    }

    QStringList result;
    for (const QString &id : permissionId) {
        // read permission description
        result << Request(appId, permissionGroup, id);
    }

    return result;
}

void PermissionService::Reset(const QString &appId, const QString &permissionGroup)
{
    Settings settings;
    settings.removeSettings(appId, permissionGroup);
}
void PermissionService::Set(const QString &appId, const QString &permissionGroup, const QString &permissionId, const QString &value)
{
    // todo
    Q_UNUSED(appId);
    Q_UNUSED(permissionGroup);
    Q_UNUSED(permissionId);
    Q_UNUSED(value);
//    SettingData data{
//        appId,
//        permissionGroup,
//        permissionId,
//        value,
//    };
//    Settings settings;
//    if (PermissionOption::getInstance()->isNeedSavedByIndex(value)) {
//        settings.saveSettings(data);
//    }
}

void PermissionService::RegistAppPermissions(const QString &appId, const QString &permissionGroup, const PermissionsInfo &permissionsInfo)
{
    if (!PhasePMDconfig::setPermissionInfo(appId, permissionGroup, systemAppPermissionRegistKey, permissionsInfo)) {
        sendErrorReply(dbusErrorName + "RegistPermissionValueError","The registered permission value is incorrect");
    }
}

QStringList PermissionService::GetRegisterAppPermissionIds(const QString &appId, const QString &permissionGroup)
{
    return PhasePMDconfig::getPermissionList(appId, permissionGroup, systemAppPermissionRegistKey);
}

void PermissionService::ShowDisablePesmissionDialog(const QString &appId, const QString &permissionGroup, const QString &permissionId)
{
    PermissionPolicy policy(permissionGroup, permissionId);
    if (!policy.isValid()) {
        return;
    }
    const QStringList options = {"Cancel", "Go to Settings"};
    org::desktopspec::permission::client client("org.desktopspec.permission.Client", "/org/desktopspec/permission/Client", QDBusConnection::sessionBus());
    auto reply = client.ShowDisablePesmissionDialog(policy.title("denyPrompt").arg(appId), policy.description("denyPrompt"), options);
    reply.waitForFinished();
    if (reply.isError()) {
        qWarning() << "[DBus] [Warning] " << reply.error();
        return;
    }

    if (reply.value() == options[1]) {
        QProcess p;
        // TODO 后面准确跳到隐私安全模块
        p.start("busctl --user call com.deepin.dde.ControlCenter /com/deepin/dde/ControlCenter com.deepin.dde.ControlCenter Show");
        p.waitForFinished(10000);
        p.close();
    }

    return;
}

int showRequestDialog(const QString &appId, const PermissionPolicy& policy, const QString &title, const QString &description) {
    org::desktopspec::permission::client client("org.desktopspec.permission.Client", "/org/desktopspec/permission/Client", QDBusConnection::sessionBus());
    auto                                 reply = client.Request(title.arg(appId), description, policy.prefer(), policy.options());
    reply.waitForFinished();
    if (reply.isError()) {
        qWarning() << "[DBus] [Warning] " << reply.error();
        return -1;
    }

    if (!policy.options().contains(reply.value())) {
        qWarning() << "the error button is pressed";
        return -1;
    }


    return PermissionOption::getInstance()->getId(reply.value());
}

QString PermissionService::parseAppPermissionKeyDconf(const QString& appPermissionDconfKey, const QString &appId, const QString &permissionGroup, const QString &permissionId, const PermissionPolicy& policy, const QString &title, const QString &description) {
    const QString& registerMode = policy.registerMode();
    bool needShowDialog = false;
    bool allowSkipLimitCheck = false;
    int appPmDconfRet = PhasePMDconfig::getPermissionValue(appId, permissionGroup, appPermissionDconfKey, permissionId);
    int registPmDconfRet = PhasePMDconfig::getPermissionValue(appId, permissionGroup, systemAppPermissionRegistKey, permissionId);
    QString strAppPmDconfRet = QString::number(appPmDconfRet);
    QString strRegistPmDconfRet = QString::number(registPmDconfRet);

    if (appPmDconfRet < dconfValueInvalid || appPmDconfRet > dconfMax) {
        qWarning() << QString("get [%1] failed [%2].").arg(appPermissionDconfKey, appPmDconfRet);
        sendErrorReply(dbusErrorName + "RegistPermissionValueError","The registered permission value is incorrect");
        return "";
    }

    if (registPmDconfRet < dconfValueInvalid || appPmDconfRet > dconfMax) {
        qWarning() << QString("get [%1] failed [%2].").arg(appPermissionDconfKey, registPmDconfRet);
        sendErrorReply(dbusErrorName + "RegistPermissionValueError","The registered permission value is incorrect");
        return "";
    }

    if (appPmDconfRet == dconfKeyInvalid) {
        if (registPmDconfRet == dconfKeyInvalid) {
            needShowDialog = true;
        } else {
            QVariantMap mapTmp = PhasePMDconfig::getPermissionMap(appId, permissionGroup, systemAppPermissionRegistKey);
            PhasePMDconfig::setPermissionMap(appId, permissionGroup, appPermissionDconfKey, mapTmp);
            if (registPmDconfRet == dconfValueInvalid || registPmDconfRet == dconfNullValue) {
                needShowDialog = true;
                allowSkipLimitCheck = true;
            } else {
                return strRegistPmDconfRet;
            }
        }
    } else if (appPmDconfRet == dconfValueInvalid) {
        if (registPmDconfRet == dconfKeyInvalid) {
            needShowDialog = true;
        } else if (registPmDconfRet == dconfValueInvalid) {
            needShowDialog = true;
        } else if (registPmDconfRet == dconfNullValue) {
            needShowDialog = true;
            allowSkipLimitCheck = true;
        } else {
            PhasePMDconfig::setPermissionValue(appId, permissionGroup, appPermissionDconfKey, permissionId, QString::number(registPmDconfRet));
            return strRegistPmDconfRet;
        }
    } else if (appPmDconfRet == dconfNullValue) {
        needShowDialog = true;
        allowSkipLimitCheck = true;
    } else {
        return strAppPmDconfRet;
    }

    if (needShowDialog) {
        if (registerMode == "limit" && !allowSkipLimitCheck) {
            qWarning() << QString("Currently in limit mode, the permissionId [%1] is not registered").arg(permissionId);
            sendErrorReply(dbusErrorName + "RegistModeError","This permission instance needs to be registered.");
            return "";
        }

        // 普通用户想要访问系统级权限，直接返回-1
        if (checkUserIsAdmin() == UserType::UserTypeStandard && policy.type() == "system") {
            sendErrorReply(dbusErrorName + "SystemLevelRestrictions","users want access to system-level permissions.");
            return "";
        }

        org::desktopspec::permission::client client("org.desktopspec.permission.Client", "/org/desktopspec/permission/Client", QDBusConnection::sessionBus());
        auto                                 reply = client.Request(title.arg(appId), description, policy.prefer(), policy.options());
        reply.waitForFinished();
        if (reply.isError()) {
            qWarning() << "[DBus] [Warning] " << reply.error();
            sendErrorReply(reply);
            return "";
        }

        if (!policy.options().contains(reply.value())) {
            qWarning() << "the error button is pressed";
            return "";
        }

        QString ret = QString::number(PermissionOption::getInstance()->getId(reply.value()));
        PhasePMDconfig::setPermissionValue(appId, permissionGroup, appPermissionDconfKey, permissionId, ret);
        return ret;
    }

    // 不可能走到此逻辑，特此加打印
    qWarning() << "error...";
    return "";
}

