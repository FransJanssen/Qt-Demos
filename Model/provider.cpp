#include "provider.h"
#include "utils.h"

#include "Model/settings.h"

#include <QString>

namespace Ps
{
    static QString SETTINGS_FILE = QStringLiteral("settings.json");
    std::unique_ptr<Settings> Provider::m_instanceSettings = nullptr;

    Settings& Provider::GetSettingsAsSingleton()
    {
        if (nullptr == m_instanceSettings)
        {
            m_instanceSettings = Utils::make_unique<Settings>(nullptr, SETTINGS_FILE);
        }

        return *m_instanceSettings;
    }
}
