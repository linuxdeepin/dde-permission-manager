set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt5 REQUIRED COMPONENTS Core DBus Widgets)
find_package(DtkCore REQUIRED)
find_package(DtkWidget REQUIRED)

qt5_add_dbus_adaptor(ADAPTER_SOURCES
                     ../DBus/org.desktopspec.permission.xml
                     impl/permission_service.h
                     PermissionService)
qt5_add_dbus_adaptor(ADAPTER_SOURCES
                     ../DBus/org.desktopspec.permission.client.xml
                     impl/permission_client.h
                     PermissionClient
                     )
qt5_add_dbus_interfaces(DBUS_INTERFACES
                     ../DBus/org.desktopspec.permission.client.xml
                     )
set(SRCS
    main.cpp
    impl/permission_service.h
    impl/permission_service.cpp
    impl/permission_client.h
    impl/permission_client.cpp
    settings/settings.h
    settings/settings.cpp
    permissionpolicy.h
    permissionpolicy.cpp
)

add_executable(deepin-permission-service ${SRCS} ${ADAPTER_SOURCES} ${DBUS_INTERFACES})
target_link_libraries(deepin-permission-service
    Qt5::Core
    Qt5::DBus
    Qt5::Widgets
    dtkcore
    dtkwidget
)
