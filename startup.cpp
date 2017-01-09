#include "startup.h"
#include "utils.h"

#include "Model/provider.h"
#include "Model/settings.h"

#include "View/mainview.h"
#include "View/setuptab.h"

namespace Ps
{
    Startup::Startup() :
        QObject(nullptr),
        m_setupTab(*new SetupTab(nullptr)),
        m_mainView(*new MainView(nullptr, m_setupTab))
    {
        Settings& my_settings = Provider::GetSettingsAsSingleton();
        my_settings.ParseJsonData();
    }

    Startup::~Startup()
    {
        Utils::DestructorMsg(this);
        delete &m_mainView;
    }

    void Startup::show() const
    {
        m_mainView.show();
    }
}
