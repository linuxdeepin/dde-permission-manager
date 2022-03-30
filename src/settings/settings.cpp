#include "settings.h"

#include <QException>
#include <QDebug>
#include <QFile>
#include <QSettings>
#include <QStandardPaths>
#include <QDir>

struct SettingsPrivate {
    Settings* q_ptr;
    QString   configPath;
    SettingsPrivate(Settings* settings) : q_ptr(settings)
    {
        const QString path = QStandardPaths::standardLocations(QStandardPaths::ConfigLocation).first();
        configPath         = QString("%1/%2/").arg(path, "applications");
    }

    ~SettingsPrivate() {}

    bool saveSettings(const SettingData& data) {
        QDir().mkpath(configPath);
        const QString appConfig = QString("%1/%2").arg(configPath, data.AppId);
        QSettings settings(appConfig, QSettings::IniFormat);
        settings.beginGroup("Permission");
        settings.setValue(data.PermissionId, data.Result);

        return settings.value(data.PermissionId).value<SettingData::AccessResult>() == data.Result;
    }

    SettingData::AccessResult result(const QString& id, const QString& PermissionId)
    {
        const QString appConfig = QString("%1/%2").arg(configPath, id);
        if (!QFile::exists(appConfig)) {
            throw QException();
        }

        QSettings settings(appConfig, QSettings::IniFormat);
        settings.beginGroup("Permission");
        const QVariant value = settings.value(PermissionId);
        if (!value.isValid()) {
            throw QException();
        }

        return value.value<SettingData::AccessResult>();
    }
};

Settings::Settings() : d_ptr(new SettingsPrivate(this)) {}
Settings::~Settings() {}

bool Settings::saveSettings(const SettingData& data)
{
    return d_ptr->saveSettings(data);
}

SettingData::AccessResult Settings::result(const QString& id, const QString& PermissionId)
{
    try {
        auto result = d_ptr->result(id, PermissionId);
        return result;
    }
    catch (QException exp) {
        throw exp;
    }
}
