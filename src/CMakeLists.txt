set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_FLAGS "-W -Wall -fPIC -fstack-protector-all -z relro -z noexecstack -z now -pie")

find_package(Qt5 REQUIRED COMPONENTS Core DBus Widgets)
find_package(DtkCore REQUIRED)
find_package(DtkWidget REQUIRED)

qt5_add_dbus_adaptor(ADAPTER_SOURCES
                     ../dbus/org.desktopspec.permission.xml
                     impl/permission_service.h
                     PermissionService)
qt5_add_dbus_adaptor(ADAPTER_SOURCES
                     ../dbus/org.desktopspec.permission.client.xml
                     impl/permission_client.h
                     PermissionClient
                     )
qt5_add_dbus_interfaces(DBUS_INTERFACES
                     ../dbus/org.desktopspec.permission.client.xml
                     )
set(SRCS
    main.cpp
    settings.h
    settings.cpp
    permissionpolicy.h
    permissionpolicy.cpp
    permissionoption.h
    permissionoption.cpp
    impl/permission_service.h
    impl/permission_service.cpp
    impl/permission_client.h
    impl/permission_client.cpp
    widgets/clientdialog.h
    widgets/clientdialog.cpp
)

add_executable(dde-permission-manager ${SRCS} ${ADAPTER_SOURCES} ${DBUS_INTERFACES})
target_link_libraries(dde-permission-manager
    Qt5::Core
    Qt5::DBus
    Qt5::Widgets
    dtkcore
    dtkwidget
)

install(DIRECTORY DESTINATION share/permission/policy)
#file(MAKE_DIRECTORY defaultapppermission)
#install(DIRECTORY defaultapppermission DESTINATION share/permission
#    DIRECTORY_PERMISSIONS OWNER_WRITE OWNER_READ GROUP_READ GROUP_WRITE WORLD_READ WORLD_WRITE)
install(TARGETS dde-permission-manager DESTINATION bin)
