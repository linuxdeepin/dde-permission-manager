#ifndef E19812E8_52FA_47ED_9D70_A707CE2E25E2
#define E19812E8_52FA_47ED_9D70_A707CE2E25E2

#include <QString>
#include <QDateTime>
#include <memory>

struct SettingData {
    typedef int AccessResult;

    QString AppId;
    QString PermissionId;
    AccessResult Result;
    QDateTime Modified = QDateTime::currentDateTimeUtc();
};

class SettingsPrivate;
class Settings {
public:
    Settings();
    ~Settings();

    bool saveSettings(const SettingData& data);
    SettingData::AccessResult result(const QString& id, const QString& PermissionId);

private:
    std::unique_ptr<SettingsPrivate> d_ptr;
};

#endif /* E19812E8_52FA_47ED_9D70_A707CE2E25E2 */
