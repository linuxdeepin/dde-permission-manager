#ifndef PERMISSIONPOLICY_H
#define PERMISSIONPOLICY_H

#include <QString>
#include <QStringList>

class PermissionPolicy
{
public:
    PermissionPolicy(const QString& permissionid);
    inline bool isValid() const {
        return m_isValid;
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

    inline QString description() const {
        return m_description;
    }

    inline QString prefer() const {
        return m_prefer;
    }

    inline QStringList options() const {
        return m_options;
    }

private:
    bool m_isValid;
    bool m_skip_auto_allow;
    QString m_id;
    QString m_name;
    QString m_description;
    QString m_prefer;
    QStringList m_options;
};

#endif // PERMISSIONPOLICY_H
