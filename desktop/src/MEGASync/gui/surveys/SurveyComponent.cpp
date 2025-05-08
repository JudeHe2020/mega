#include "SurveyComponent.h"

#include "SurveyController.h"
#include "Surveys.h"

#include <QUrl>

SurveyComponent::SurveyComponent(QObject* parent, int type):
    QMLWidgetComponent(parent),
    mController(std::make_shared<SurveyController>(type))
{
    connect(mController.get(),
            &SurveyController::surveySubmitted,
            this,
            &SurveyComponent::surveySubmitted,
            Qt::UniqueConnection);
}

QUrl SurveyComponent::getQmlUrl()
{
    return QUrl(QStringLiteral("qrc:/surveys/SurveyItem.qml"));
}

QList<QObject*> SurveyComponent::getInstancesFromContext()
{
    QList<QObject*> instances;
    QObject* surveysObject = qobject_cast<QObject*>(mController->surveys().get());
    if (surveysObject)
    {
        instances.append(surveysObject);
    }
    return instances;
}

void SurveyComponent::submitButtonClicked(int response, const QString& comment)
{
    mController->updateCurrentAnwer(response, comment);
    mController->submitSurvey();
}
