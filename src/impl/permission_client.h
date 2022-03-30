#ifndef PERMISSION_CLIENT_H_
#define PERMISSION_CLIENT_H_

#include <QObject>

typedef QVector<int> IntArray;

class PermissionClient : public QObject {
    Q_OBJECT
public:
    PermissionClient(QObject* parent = nullptr);
    ~PermissionClient();

public Q_SLOTS: // METHODS
    QString request(const QString &title, const QStringList& options);
};

#endif  // PERMISSION_CLIENT_H_
