#ifndef USER_NOTIFICATION_H
#define USER_NOTIFICATION_H

#include "UserMessage.h"

#include <QPixmap>
#include <QUrl>

#include <memory>

namespace mega
{
class MegaNotification;
}

class UserNotification : public UserMessage
{
    Q_OBJECT

public:
    UserNotification() = delete;
    UserNotification(const mega::MegaNotification* notification, QObject* parent = nullptr);
    ~UserNotification() = default;

    bool isSeen() const override;
    bool isRowAccepted(MessageType type) const override;
    bool sort(UserMessage* checkWith) const override;

    void reset(const mega::MegaNotification* notification);
    bool equals(const mega::MegaNotification* notification) const;

    void markAsSeen();
    void markAsExpired();

    QString getTitle() const;
    QString getDescription() const;

    bool showImage() const;
    bool showIcon() const;
    QString getImageNamePath() const;
    QString getIconNamePath() const;

    int64_t getStart() const;
    int64_t getEnd() const;

    // For now, call to action 2 is not used
    const QString getActionText() const;
    const QUrl getActionUrl() const;

private:
    std::unique_ptr<const mega::MegaNotification> mNotification;
    bool mSeen;

};

#endif // USER_NOTIFICATION_H
