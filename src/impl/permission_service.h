#ifndef AD0CF546_BF40_4B81_864F_93F98EEE99AF
#define AD0CF546_BF40_4B81_864F_93F98EEE99AF

#include <QObject>
#include <QDBusContext>
#include <QVector>

typedef QVector<int> IntArray;

class PermissionService : public QObject, protected QDBusContext {
    Q_OBJECT
public:
    PermissionService(QObject *parent = nullptr);
    ~PermissionService();

public Q_SLOTS: // METHODS
    int request(const QString &appid, const QString &permissionid);
    int request(const QString &appid, const QString &permissionid, const QString &description);
    IntArray request(const QString &appid, const QStringList &permissionid);
    void reset(const QString &appid);
    void set(const QString &appid, const QString &permission);
};

#endif /* AD0CF546_BF40_4B81_864F_93F98EEE99AF */
