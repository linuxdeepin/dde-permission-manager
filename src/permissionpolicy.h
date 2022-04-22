#ifndef PERMISSIONPOLICY_H
#define PERMISSIONPOLICY_H

#include <QString>
#include <QStringList>
#include <QJsonObject>
#include <QMap>
#include <QLocale>
#include <QDebug>


struct Transactions
{
    QMap<QString, QString> titleMap;
    QMap<QString, QString> descriptionMap;
};

class PermissionPolicy
{
public:
    PermissionPolicy(const QString& permissionGroup, const QString& permissionId);
    inline bool isValid() const {
        return m_isValid;
    }

    inline QString group() const {
        return m_group;
    }

    inline QString id() const {
        return m_id;
    }

    inline bool skip_auto_allow() const {
        return m_skip_auto_allow;
    }

    inline QString name() const {
        return m_name;
    }

    inline QString title() const {
        QString language = QLocale::system().name();
        if (m_transactions.titleMap.contains(language)) {
            return m_transactions.titleMap[language];
        }
        return m_title;
    }

    inline QString description() const {
        QString language = QLocale::system().name();
        if (m_transactions.descriptionMap.contains(language)) {
            return m_transactions.descriptionMap[language];
        }
        return m_description;
    }

    inline QString prefer() const {
        return m_prefer;
    }

    inline QStringList options() const {
        return m_options;
    }

private:
    void transactionsJsonParse(const QJsonObject& obj);

private:
    bool m_isValid;
    bool m_skip_auto_allow;
    QString m_group;
    QString m_id;
    QString m_name;
    QString m_title;
    QString m_description;
    QString m_prefer;
    QStringList m_options;
    struct Transactions m_transactions;
};

#endif // PERMISSIONPOLICY_H
