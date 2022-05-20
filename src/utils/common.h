#ifndef COMMON_H
#define COMMON_H
#include <unistd.h>
#include <pwd.h>

enum UserType {
    UserTypeStandard = 0,
    UserTypeAdmin,
    UserTypeUdcp,

    UserTypeInvalid,
};

UserType checkUserIsAdmin();


#endif // COMMON_H
