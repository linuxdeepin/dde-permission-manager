#include "permissionpolicy.h"

#include <QDir>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QVariant>

PermissionPolicy::PermissionPolicy(const QString& permissionGroup, const QString& permissionId)
    : m_isValid(false)
    , m_group(permissionGroup)
{
        QFile file("/usr/share/permission/policy/" + permissionGroup + "/" + permissionId + ".json");
        if (!file.open(QFile::Text | QFile::ReadOnly)) {
            return;
        }
        const QJsonObject& obj = QJsonDocument::fromJson(file.readAll()).object();
        m_id = obj["id"].toString();
        m_skip_auto_allow = obj["skip_auto_allow"].toBool();
        m_name = obj["name"].toString();
        m_title = obj["title"].toString();
        m_description = obj["description"].toString();
        m_prefer = obj["prefer"].toString();
        m_options = obj["options"].toVariant().toStringList();
        m_isValid = true;

        transactionsJsonParse(obj);
}

QStringList PermissionPolicy::getPolicyList(const QString& permissionGroup)
{
    QStringList ids;
    QDir dir("/usr/share/permission/policy/" + permissionGroup);
    QFileInfoList fileInfoList = dir.entryInfoList(QDir::Files | QDir::NoDotAndDotDot);
    for (auto fileInfo : fileInfoList) {
        if (fileInfo.suffix() != "json") {
            continue;
        }
        QFile file(fileInfo.absoluteFilePath());
        if (!file.open(QFile::Text | QFile::ReadOnly)) {
            qWarning() << "open file failed";
            continue;
        }
        const QJsonObject& obj = QJsonDocument::fromJson(file.readAll()).object();
        file.close();
        QString id = obj["id"].toString();
        if (!id.isEmpty()) {
            ids << id;
        }
    }
    return ids;
}

void PermissionPolicy::transactionsJsonParse(const QJsonObject& obj)
{
        if(obj.contains("translations")) {
            const QJsonObject &tsObj = obj["translations"].toObject();
            if(tsObj.contains("title"))
            {
                if(tsObj["title"].isArray())
                {
                    const QJsonArray &titleArray = tsObj["title"].toArray();
                    for (int i = 0; i < titleArray.size(); i++) {
                        if (titleArray.at(i).isObject()) {
                            const QJsonObject &titleObj = titleArray.at(i).toObject();
                            m_transactions.titleMap[titleObj["language"].toString()] = titleObj["text"].toString();
                        }
                    }
                }
            }
            if(tsObj.contains("description"))
            {
                if(tsObj["description"].isArray())
                {
                    const QJsonArray &descriptionArray = tsObj["description"].toArray();
                    for (int i = 0; i < descriptionArray.size(); i++) {
                        if (descriptionArray.at(i).isObject()) {
                            const QJsonObject &descObj = descriptionArray.at(i).toObject();
                            m_transactions.descriptionMap[descObj["language"].toString()] = descObj["text"].toString();
                        }
                    }
                }
            }
        }
}