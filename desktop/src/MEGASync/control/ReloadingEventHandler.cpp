#include "ReloadingEventHandler.h"

std::shared_ptr<ReloadingEventHandler> ReloadingEventHandler::instance()
{
    static std::shared_ptr<ReloadingEventHandler> reloadEventHandler(new ReloadingEventHandler());
    return reloadEventHandler;
}

void ReloadingEventHandler::processEvent(std::unique_ptr<mega::MegaEvent> event,
                                         std::shared_ptr<DesktopNotifications> osNotificatons)
{
    mega::MegaApi::log(mega::MegaApi::LOG_LEVEL_WARNING,
                       QString::fromUtf8("Reloading event from SDK").toUtf8().constData());

    mOsNotifications = std::move(osNotificatons);

    // Process event: request RELOADING app state
    mReloadingRequested = true;
    emit requestAppState(AppState::RELOADING);
}

ReloadingEventHandler::ReloadingEventHandler():
    QObject{nullptr},
    mReloadingRequested{false}
{
    // Plug into AppStates
    connect(this,
            &ReloadingEventHandler::requestAppState,
            AppState::instance().get(),
            &AppState::setAppState);
    connect(AppState::instance().get(),
            &AppState::appStateChanged,
            this,
            &ReloadingEventHandler::onAppStateChanged);
}

void ReloadingEventHandler::clear()
{
    mReloadingRequested = false;
    mOsNotifications.reset();
}

void ReloadingEventHandler::onAppStateChanged(AppState::AppStates oldAppState,
                                              AppState::AppStates newAppState)
{
    if (mReloadingRequested)
    {
        if (newAppState == AppState::RELOADING)
        {
            // Show a desktop notification
            mOsNotifications->sendInfoNotification(
                tr("MEGA is reloading"),
                tr("The app has detected an issue and is reloading your account. Please wait…"));
        }
        else if (oldAppState == AppState::RELOADING)
        {
            // Show a desktop notification
            mOsNotifications->sendInfoNotification(tr("MEGA has reloaded"),
                                                   tr("The app has reloaded. If you experience any "
                                                      "further issues, please contact Support."));
            clear();
        }
    }
}
