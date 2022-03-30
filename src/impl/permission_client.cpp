#include "permission_client.h"

#include <DDialog>
#include <QSharedPointer>

#include "permissionpolicy.h"

DWIDGET_USE_NAMESPACE

PermissionClient::PermissionClient(QObject *parent) : QObject(parent) {}

PermissionClient::~PermissionClient() {}

QString PermissionClient::request(const QString &title, const QStringList &options)
{
    QSharedPointer<DDialog>    dialog(new DDialog);
    std::map<QString, QString> buttonsTr{ { "allow", tr("Allow") }, { "deny", tr("Deny") }, { "deny_once", tr("Deny Once") }, { "allow_once", tr("Allow Once") } };
    for (auto const &option : options) {
        dialog->addButton(buttonsTr[option]);
    }
    dialog->setTitle(title);
    return options.value(dialog->exec(), "");
}
