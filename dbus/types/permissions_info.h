#ifndef PERMISSIONSINFO
#define PERMISSIONSINFO

#include <QMap>
#include <QDBusMetaType>

typedef QMap<QString, QString> PermissionsInfo;
Q_DECLARE_METATYPE(PermissionsInfo)

void registerPermissionsInfoMetaType();

#endif // PERMISSIONSINFO
