#ifndef AD0CF546_BF40_4B81_864F_93F98EEE99AF
#define AD0CF546_BF40_4B81_864F_93F98EEE99AF

#include <QObject>
#include <QDBusContext>
#include <QVector>

typedef QVector<int> IntArray;

class PermissionService : public QObject, protected QDBusContext {
    Q_OBJECT
public:
    explicit PermissionService(QObject *parent = nullptr);
    ~PermissionService();

public Q_SLOTS: // METHODS
    int Request(const QString &appId, const QString &permissionGroup,const QString &permissionId);
    int Request(const QString &appId, const QString &permissionGroup, const QString &permissionId, const QString &title, const QString &description);
    IntArray Request(const QString &appId, const QString &permissiongGroup, const QStringList &permissionId);
    void Reset(const QString &appId, const QString &permissiongGroup);
    void Set(const QString &appId, const QString &permissiongGroup, const QString &permissionId, const int &value);
};

#endif /* AD0CF546_BF40_4B81_864F_93F98EEE99AF */
