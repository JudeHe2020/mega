#ifndef TRANSFER_QUOTA_H
#define TRANSFER_QUOTA_H

#include "DesktopNotifications.h"
#include "OverQuotaDialog.h"
#include "Preferences.h"

#include <QObject>

#include <memory>

// % for almost over quota
constexpr int ALMOST_OVER_QUOTA_PER_CENT{90};
constexpr int FULL_QUOTA_PER_CENT{100};

enum class QuotaState
{
    OK        = 0,
    WARNING   = 1,
    FULL      = 2, // Account could reach full usage of quota but not enter in overquota situation yet.
    OVERQUOTA = 3,
};

class TransferQuota: public QObject
{
    Q_OBJECT
public:
    TransferQuota(std::shared_ptr<DesktopNotifications> desktopNotifications);
    void setOverQuota(std::chrono::milliseconds waitTime);
    void updateQuotaState();
    bool isOverQuota();
    bool isQuotaWarning();
    bool isQuotaFull();
    void checkQuotaAndAlerts();
    void checkImportLinksAlertDismissed(std::function<void(int)> func);
    void checkDownloadAlertDismissed(std::function<void(int)> func);
    void checkStreamingAlertDismissed(std::function<void (int)> func);
    QTime getRemainingTransferQuotaTime();
    void reset();
    QuotaState quotaState() const;

private:
    mega::MegaApi* mMegaApi;
    std::shared_ptr<Preferences> mPreferences;
    std::shared_ptr<DesktopNotifications> mOsNotifications;
    QuotaState mQuotaState;
    std::chrono::system_clock::time_point mWaitTimeUntil;
    bool overQuotaAlertVisible;
    bool almostQuotaAlertVisible;

    void sendQuotaWarningOsNotification();
    void sendOverQuotaOsNotification();
    void checkExecuteDialog();
    void checkExecuteNotification();
    void checkExecuteUiMessage();
    void checkExecuteWarningOsNotification();
    void checkExecuteWarningUiMessage();
    void checkExecuteAlerts();
    void checkAlertDismissed(OverQuotaDialogType type, std::function<void (int)> func);
    void closeUpsellTransferDialog();

public slots:
    void onTransferOverquotaVisibilityChange(bool messageShown);
    void onAlmostTransferOverquotaVisibilityChange(bool messageShown);

signals:
    // emitted when checking almost OQ and the respective UI message
    // needs to be present (hasn't been discarded by the user for a while)
    void almostOverQuotaMessageNeedsToBeShown();
    // emitted when checking OQ and the respective UI message
    // needs to be present (hasn't been discarded by the user for a while)
    void overQuotaMessageNeedsToBeShown();
    void overQuotaDialogFinished(int result);
    void sendState(QuotaState state);
    void waitTimeIsOver();
};
#endif
