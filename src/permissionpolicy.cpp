#include "permissionpolicy.h"

#include <QDir>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QVariant>

PermissionPolicy::PermissionPolicy(const QString& permissionid)
    : m_isValid(false)
{
        QFile file("/usr/share/permission/" + permissionid + ".json");
        if (!file.open(QFile::Text | QFile::ReadOnly)) {
            return;
        }
        const QJsonObject& obj = QJsonDocument::fromJson(file.readAll()).object();
        m_id = obj["id"].toString();
        m_skip_auto_allow = obj["skip_auto_allow"].toBool();
        m_name = obj["name"].toString();
        m_description = obj["description"].toString();
        m_prefer = obj["prefer"].toString();
        m_options = obj["options"].toVariant().toStringList();
        m_isValid = true;
}
