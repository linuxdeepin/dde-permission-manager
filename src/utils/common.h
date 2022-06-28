#ifndef COMMON_H
#define COMMON_H
#include <unistd.h>
#include <pwd.h>

#include <QString>
#include <QVariantMap>
#include <QMetaType>

enum UserType {
    UserTypeStandard = 0,
    UserTypeAdmin,
    UserTypeUdcp,

    UserTypeInvalid,
};

UserType checkUserIsAdmin();
bool checkAuth(const QString &actionId);

#endif // COMMON_H
