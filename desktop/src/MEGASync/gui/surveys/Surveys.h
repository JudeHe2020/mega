#ifndef SURVEYS_H
#define SURVEYS_H

#include "megaapi.h"

#include <QMap>
#include <QObject>

#include <memory>

class Surveys: public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString question READ getQuestion NOTIFY questionChanged)
    Q_PROPERTY(int commentMaxLength READ getCommentMaxLength NOTIFY commentMaxLenghtChanged)

public:
    Surveys(QObject* parent = nullptr);

    class Data
    {
    public:
        Data();
        virtual ~Data() = default;

        class Answer
        {
        public:
            Answer();
            virtual ~Answer() = default;

            void setResponse(int newResponse);
            void setMaximumCommentLength(int newMaximumCommentLength);
            void setComment(const QString& newComment);

            int response() const;
            int maximumCommentLength() const;
            QString comment() const;

        private:
            int mResponse;
            int mMaximumCommentLength;
            QString mComment;
        };

        mega::MegaHandle handle() const;
        QString question() const;
        Answer answer() const;

    private:
        mega::MegaHandle mHandle;
        QString mQuestion;
        Answer mAnswer;

        friend class SurveyController;

        void setData(mega::MegaHandle handle, const QString& question, int maximumCommentLength);
        void setAnswerData(int response, const QString& comment);
    };

    std::shared_ptr<Data> currentSurvey() const;
    QString getQuestion() const;
    int getCommentMaxLength() const;
    unsigned int currentSurveyId() const;

signals:
    void questionChanged();
    void commentMaxLenghtChanged();

private:
    QMap<unsigned int, std::shared_ptr<Data>> mSurveys;
    unsigned int mCurrentSurveyId;

    friend class SurveyController;

    std::shared_ptr<Data> survey(unsigned int triggerActionId) const;

    void addSurvey(unsigned int triggerActionId);
    void addSurvey(unsigned int triggerActionId, std::shared_ptr<Data> survey);
    void setCurrentSurveyId(unsigned int newCurrentSurveyId);
};

#endif // SURVEYS_H
