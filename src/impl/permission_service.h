#ifndef AD0CF546_BF40_4B81_864F_93F98EEE99AF
#define AD0CF546_BF40_4B81_864F_93F98EEE99AF

#include <QObject>
#include <QDBusContext>
#include <QVector>

#include "../utils/dconfig_settings.h"
#include "../../dbus/types/permissions_info.h"
#include "permissionpolicy.h"

DCORE_USE_NAMESPACE

class PermissionService : public QObject, protected QDBusContext {
    Q_OBJECT
public:
    explicit PermissionService(QObject *parent = nullptr);
    ~PermissionService();

public Q_SLOTS: // METHODS
    QStringList PermissionList(const QString &permissionGroup);
    QString Request(const QString &appId, const QString &permissionGroup,const QString &permissionId);
    QString Request(const QString &appId, const QString &permissionGroup, const QString &permissionId, const QString &title, const QString &description);
    QStringList Request(const QString &appId, const QString &permissionGroup, const QStringList &permissionId);
    void Reset(const QString &appId, const QString &permissionGroup);
    void Set(const QString &appId, const QString &permissionGroup, const QString &permissionId, const QString &value);
    QStringList GetRegisterAppPermissionIds(const QString &appId, const QString &permissionGroup);
    void RegistAppPermissions(const QString &appId, const QString &permissionGroup, const PermissionsInfo &permissionsInfo);
    void ShowDisablePesmissionDialog(const QString &appId, const QString &permissionGroup, const QString &permissionId);

private:
    QString parseAppPermissionKeyDconf(const QString& appPermissionDconfKey, const QString &appId, const QString &permissionGroup, const QString &permissionId, const PermissionPolicy& policy, const QString &title, const QString &description);
};

#endif /* AD0CF546_BF40_4B81_864F_93F98EEE99AF */
