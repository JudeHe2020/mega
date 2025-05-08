#include "QmlWidgetWrapper.h"

#include "QmlManager.h"

namespace
{
const QLatin1String NAMESPACE_SEPARATOR("::");
}

// ************************************************************************************************
// * QMLWidgetComponent
// ************************************************************************************************

QString QMLWidgetComponent::contextName() const
{
    // Get Child class name.
    QString className(QString::fromLatin1(metaObject()->className()));

    // Remove namespace prefix if necessary.
    int index(className.lastIndexOf(NAMESPACE_SEPARATOR));
    if (index != -1)
    {
        // Ignore namespace separator.
        className = className.mid(index + NAMESPACE_SEPARATOR.size());
    }

    return className;
}

QList<QObject*> QMLWidgetComponent::getInstancesFromContext()
{
    return QList<QObject*>();
}

// ************************************************************************************************
// * QmlWidgetWrapperBase
// ************************************************************************************************

QmlWidgetWrapperBase::QmlWidgetWrapperBase(QWidget* parent):
    QQuickWidget(QmlManager::instance()->getEngine(), parent),
    mItem(nullptr)
{}

QmlWidgetWrapperBase::~QmlWidgetWrapperBase()
{
    mItem->deleteLater();
}
