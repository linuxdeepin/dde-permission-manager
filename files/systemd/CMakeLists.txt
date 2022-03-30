set(SERVICES
    org.desktopspec.permission.service
)

install(FILES ${SERVICES}
        DESTINATION lib/systemd/user/)
