#include "permissions_info.h"
void registerPermissionsInfoMetaType()
{
    qRegisterMetaType<PermissionsInfo>("PermissionsInfo");
    qDBusRegisterMetaType<PermissionsInfo>();
}
