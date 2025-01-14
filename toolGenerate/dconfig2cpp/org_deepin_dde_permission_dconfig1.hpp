/**
 * This file is generated by dconfig2cpp.
 * Command line arguments: ./dconfig2cpp -p ./dde-permission-manager/toolGenerate/dconfig2cpp ./dde-permission-manager/misc/dconf/org.deepin.dde.permission.dconfig1.json
 * Generation time: 2025-01-14T10:54:57
 * JSON file version: 1.0
 * 
 * WARNING: DO NOT MODIFY THIS FILE MANUALLY.
 * If you need to change the content, please modify the dconfig2cpp tool.
 */

#ifndef ORG_DEEPIN_DDE_PERMISSION_DCONFIG1_H
#define ORG_DEEPIN_DDE_PERMISSION_DCONFIG1_H

#include <QThread>
#include <QVariant>
#include <QDebug>
#include <QAtomicPointer>
#include <QAtomicInteger>
#include <DConfig>

class org_deepin_dde_permission_dconfig1 : public QObject {
    Q_OBJECT

    Q_PROPERTY(QVariantMap Session_App_Permissions_List READ Session_App_Permissions_List WRITE setSession_App_Permissions_List NOTIFY Session_App_Permissions_ListChanged)
    Q_PROPERTY(QVariantMap Session_Permissions_Enable READ Session_Permissions_Enable WRITE setSession_Permissions_Enable NOTIFY Session_Permissions_EnableChanged)
    Q_PROPERTY(QVariantMap System_App_Permissions_List READ System_App_Permissions_List WRITE setSystem_App_Permissions_List NOTIFY System_App_Permissions_ListChanged)
    Q_PROPERTY(QVariantMap System_App_Permissions_Regist_Info READ System_App_Permissions_Regist_Info WRITE setSystem_App_Permissions_Regist_Info NOTIFY System_App_Permissions_Regist_InfoChanged)
    Q_PROPERTY(QVariantMap System_Permissions_Enable READ System_Permissions_Enable WRITE setSystem_Permissions_Enable NOTIFY System_Permissions_EnableChanged)
public:
    explicit org_deepin_dde_permission_dconfig1(QThread *thread, const QString &appId, const QString &name, const QString &subpath, QObject *parent = nullptr)
        : QObject(parent) {

        if (!thread->isRunning()) {
            qWarning() << QStringLiteral("Warning: The provided thread is not running.");
        }
        Q_ASSERT(QThread::currentThread() != thread);
        auto worker = new QObject();
        worker->moveToThread(thread);
        QMetaObject::invokeMethod(worker, [=]() {
            auto config = DTK_CORE_NAMESPACE::DConfig::create(appId, name, subpath, nullptr);
            if (!config) {
                qWarning() << QStringLiteral("Failed to create DConfig instance.");
                worker->deleteLater();
                return;
            }
            config->moveToThread(QThread::currentThread());
            initialize(config);
            worker->deleteLater();
        });
    }
    explicit org_deepin_dde_permission_dconfig1(QThread *thread, DTK_CORE_NAMESPACE::DConfigBackend *backend, const QString &appId, const QString &name, const QString &subpath, QObject *parent = nullptr)
        : QObject(parent) {

        if (!thread->isRunning()) {
            qWarning() << QStringLiteral("Warning: The provided thread is not running.");
        }
        Q_ASSERT(QThread::currentThread() != thread);
        auto worker = new QObject();
        worker->moveToThread(thread);
        QMetaObject::invokeMethod(worker, [=]() {
            auto config = DTK_CORE_NAMESPACE::DConfig::create(backend, appId, name, subpath, nullptr);
            if (!config) {
                qWarning() << QStringLiteral("Failed to create DConfig instance.");
                worker->deleteLater();
                return;
            }
            config->moveToThread(QThread::currentThread());
            initialize(config);
            worker->deleteLater();
        });
    }
    explicit org_deepin_dde_permission_dconfig1(QThread *thread, const QString &name, const QString &subpath, QObject *parent = nullptr)
        : QObject(parent) {

        if (!thread->isRunning()) {
            qWarning() << QStringLiteral("Warning: The provided thread is not running.");
        }
        Q_ASSERT(QThread::currentThread() != thread);
        auto worker = new QObject();
        worker->moveToThread(thread);
        QMetaObject::invokeMethod(worker, [=]() {
            auto config = DTK_CORE_NAMESPACE::DConfig::create(name, subpath, nullptr);
            if (!config) {
                qWarning() << QStringLiteral("Failed to create DConfig instance.");
                worker->deleteLater();
                return;
            }
            config->moveToThread(QThread::currentThread());
            initialize(config);
            worker->deleteLater();
        });
    }
    explicit org_deepin_dde_permission_dconfig1(QThread *thread, DTK_CORE_NAMESPACE::DConfigBackend *backend, const QString &name, const QString &subpath, QObject *parent = nullptr)
        : QObject(parent) {

        if (!thread->isRunning()) {
            qWarning() << QStringLiteral("Warning: The provided thread is not running.");
        }
        Q_ASSERT(QThread::currentThread() != thread);
        auto worker = new QObject();
        worker->moveToThread(thread);
        QMetaObject::invokeMethod(worker, [=]() {
            auto config = DTK_CORE_NAMESPACE::DConfig::create(backend, name, subpath, nullptr);
            if (!config) {
                qWarning() << QStringLiteral("Failed to create DConfig instance.");
                worker->deleteLater();
                return;
            }
            config->moveToThread(QThread::currentThread());
            initialize(config);
            worker->deleteLater();
        });
    }
    ~org_deepin_dde_permission_dconfig1() {
        if (m_config.loadRelaxed()) {
            m_config.loadRelaxed()->deleteLater();
        }
    }

    QVariantMap Session_App_Permissions_List() const {
        return p_Session_App_Permissions_List;
    }
    void setSession_App_Permissions_List(const QVariantMap &value) {
        auto oldValue = p_Session_App_Permissions_List;
        p_Session_App_Permissions_List = value;
        markPropertySet(0);
        if (auto config = m_config.loadRelaxed()) {
            QMetaObject::invokeMethod(config, [this, value]() {
                m_config.loadRelaxed()->setValue(QStringLiteral("Session_App_Permissions_List"), value);
            });
        }
        if (p_Session_App_Permissions_List != oldValue) {
            Q_EMIT Session_App_Permissions_ListChanged();
        }
    }
    QVariantMap Session_Permissions_Enable() const {
        return p_Session_Permissions_Enable;
    }
    void setSession_Permissions_Enable(const QVariantMap &value) {
        auto oldValue = p_Session_Permissions_Enable;
        p_Session_Permissions_Enable = value;
        markPropertySet(1);
        if (auto config = m_config.loadRelaxed()) {
            QMetaObject::invokeMethod(config, [this, value]() {
                m_config.loadRelaxed()->setValue(QStringLiteral("Session_Permissions_Enable"), value);
            });
        }
        if (p_Session_Permissions_Enable != oldValue) {
            Q_EMIT Session_Permissions_EnableChanged();
        }
    }
    QVariantMap System_App_Permissions_List() const {
        return p_System_App_Permissions_List;
    }
    void setSystem_App_Permissions_List(const QVariantMap &value) {
        auto oldValue = p_System_App_Permissions_List;
        p_System_App_Permissions_List = value;
        markPropertySet(2);
        if (auto config = m_config.loadRelaxed()) {
            QMetaObject::invokeMethod(config, [this, value]() {
                m_config.loadRelaxed()->setValue(QStringLiteral("System_App_Permissions_List"), value);
            });
        }
        if (p_System_App_Permissions_List != oldValue) {
            Q_EMIT System_App_Permissions_ListChanged();
        }
    }
    QVariantMap System_App_Permissions_Regist_Info() const {
        return p_System_App_Permissions_Regist_Info;
    }
    void setSystem_App_Permissions_Regist_Info(const QVariantMap &value) {
        auto oldValue = p_System_App_Permissions_Regist_Info;
        p_System_App_Permissions_Regist_Info = value;
        markPropertySet(3);
        if (auto config = m_config.loadRelaxed()) {
            QMetaObject::invokeMethod(config, [this, value]() {
                m_config.loadRelaxed()->setValue(QStringLiteral("System_App_Permissions_Regist_Info"), value);
            });
        }
        if (p_System_App_Permissions_Regist_Info != oldValue) {
            Q_EMIT System_App_Permissions_Regist_InfoChanged();
        }
    }
    QVariantMap System_Permissions_Enable() const {
        return p_System_Permissions_Enable;
    }
    void setSystem_Permissions_Enable(const QVariantMap &value) {
        auto oldValue = p_System_Permissions_Enable;
        p_System_Permissions_Enable = value;
        markPropertySet(4);
        if (auto config = m_config.loadRelaxed()) {
            QMetaObject::invokeMethod(config, [this, value]() {
                m_config.loadRelaxed()->setValue(QStringLiteral("System_Permissions_Enable"), value);
            });
        }
        if (p_System_Permissions_Enable != oldValue) {
            Q_EMIT System_Permissions_EnableChanged();
        }
    }
Q_SIGNALS:
    void Session_App_Permissions_ListChanged();
    void Session_Permissions_EnableChanged();
    void System_App_Permissions_ListChanged();
    void System_App_Permissions_Regist_InfoChanged();
    void System_Permissions_EnableChanged();
private:
    void initialize(DTK_CORE_NAMESPACE::DConfig *config) {
        Q_ASSERT(!m_config.loadRelaxed());
        m_config.storeRelaxed(config);
        if (testPropertySet(0)) {
            config->setValue(QStringLiteral("Session_App_Permissions_List"), QVariant::fromValue(p_Session_App_Permissions_List));
        } else {
            updateValue(QStringLiteral("Session_App_Permissions_List"), QVariant::fromValue(p_Session_App_Permissions_List));
        }
        if (testPropertySet(1)) {
            config->setValue(QStringLiteral("Session_Permissions_Enable"), QVariant::fromValue(p_Session_Permissions_Enable));
        } else {
            updateValue(QStringLiteral("Session_Permissions_Enable"), QVariant::fromValue(p_Session_Permissions_Enable));
        }
        if (testPropertySet(2)) {
            config->setValue(QStringLiteral("System_App_Permissions_List"), QVariant::fromValue(p_System_App_Permissions_List));
        } else {
            updateValue(QStringLiteral("System_App_Permissions_List"), QVariant::fromValue(p_System_App_Permissions_List));
        }
        if (testPropertySet(3)) {
            config->setValue(QStringLiteral("System_App_Permissions_Regist_Info"), QVariant::fromValue(p_System_App_Permissions_Regist_Info));
        } else {
            updateValue(QStringLiteral("System_App_Permissions_Regist_Info"), QVariant::fromValue(p_System_App_Permissions_Regist_Info));
        }
        if (testPropertySet(4)) {
            config->setValue(QStringLiteral("System_Permissions_Enable"), QVariant::fromValue(p_System_Permissions_Enable));
        } else {
            updateValue(QStringLiteral("System_Permissions_Enable"), QVariant::fromValue(p_System_Permissions_Enable));
        }

        connect(config, &DTK_CORE_NAMESPACE::DConfig::valueChanged, this, [this](const QString &key) {
            updateValue(key);
        }, Qt::DirectConnection);
    }
    void updateValue(const QString &key, const QVariant &fallback = QVariant()) {
        Q_ASSERT(QThread::currentThread() == m_config.loadRelaxed()->thread());
        const QVariant &value = m_config.loadRelaxed()->value(key, fallback);
        if (key == QStringLiteral("Session_App_Permissions_List")) {
            auto newValue = qvariant_cast<QVariantMap>(value);
            QMetaObject::invokeMethod(this, [this, newValue]() {
                if (p_Session_App_Permissions_List != newValue) {
                    p_Session_App_Permissions_List = newValue;
                    Q_EMIT Session_App_Permissions_ListChanged();
                }
            });
            return;
        }
        if (key == QStringLiteral("Session_Permissions_Enable")) {
            auto newValue = qvariant_cast<QVariantMap>(value);
            QMetaObject::invokeMethod(this, [this, newValue]() {
                if (p_Session_Permissions_Enable != newValue) {
                    p_Session_Permissions_Enable = newValue;
                    Q_EMIT Session_Permissions_EnableChanged();
                }
            });
            return;
        }
        if (key == QStringLiteral("System_App_Permissions_List")) {
            auto newValue = qvariant_cast<QVariantMap>(value);
            QMetaObject::invokeMethod(this, [this, newValue]() {
                if (p_System_App_Permissions_List != newValue) {
                    p_System_App_Permissions_List = newValue;
                    Q_EMIT System_App_Permissions_ListChanged();
                }
            });
            return;
        }
        if (key == QStringLiteral("System_App_Permissions_Regist_Info")) {
            auto newValue = qvariant_cast<QVariantMap>(value);
            QMetaObject::invokeMethod(this, [this, newValue]() {
                if (p_System_App_Permissions_Regist_Info != newValue) {
                    p_System_App_Permissions_Regist_Info = newValue;
                    Q_EMIT System_App_Permissions_Regist_InfoChanged();
                }
            });
            return;
        }
        if (key == QStringLiteral("System_Permissions_Enable")) {
            auto newValue = qvariant_cast<QVariantMap>(value);
            QMetaObject::invokeMethod(this, [this, newValue]() {
                if (p_System_Permissions_Enable != newValue) {
                    p_System_Permissions_Enable = newValue;
                    Q_EMIT System_Permissions_EnableChanged();
                }
            });
            return;
        }
    }
    inline void markPropertySet(const int index) {
        if (index < 32) {
            m_propertySetStatus0.fetchAndOrOrdered(1 << (index - 0));
            return;
        }
        Q_UNREACHABLE();
    }
    inline bool testPropertySet(const int index) const {
        if (index < 32) {
            return (m_propertySetStatus0.loadRelaxed() & (1 << (index - 0)));
        }
        Q_UNREACHABLE();
    }
    QAtomicPointer<DTK_CORE_NAMESPACE::DConfig> m_config = nullptr;
    QVariantMap p_Session_App_Permissions_List { QVariantMap{} };
    QVariantMap p_Session_Permissions_Enable { QVariantMap{} };
    QVariantMap p_System_App_Permissions_List { QVariantMap{} };
    QVariantMap p_System_App_Permissions_Regist_Info { QVariantMap{} };
    QVariantMap p_System_Permissions_Enable { QVariantMap{} };
    QAtomicInteger<quint32> m_propertySetStatus0 = 0;
};

#endif // ORG_DEEPIN_DDE_PERMISSION_DCONFIG1_H