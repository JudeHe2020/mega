#include "ChooseFile.h"

#include "Platform.h"

#include <QDir>

ChooseLocalFile::ChooseLocalFile(QObject *parent)
    : QObject(parent)
    , mTitle(QString::fromUtf8(""))
{
}

void ChooseLocalFile::openFileSelector(const QString& folderPath)
{
    auto openFromFolder = QDir::toNativeSeparators(Utilities::getDefaultBasePath());

    if (!folderPath.isEmpty())
    {
        openFromFolder = QDir::toNativeSeparators(folderPath);
        QDir openFromFolderDir(openFromFolder);
        if (openFromFolderDir.cdUp())
        {
            openFromFolder = openFromFolderDir.path();
        }
        else
        {
            openFromFolder = QDir::toNativeSeparators(Utilities::getDefaultBasePath());
        }
    }

    SelectorInfo info;
    info.title = mTitle;
    info.defaultDir = openFromFolder;
    info.canCreateDirectories = true;

    QPointer<const QObject> context = this;
    info.func = [this, context, openFromFolder](QStringList selection)
    {
        if(context && !selection.isEmpty())
        {
            sendFileChosenSignal(Platform::getInstance()->preparePathForSync(selection.first()));
        }
    };

    Platform::getInstance()->fileSelector(info);
}

void ChooseLocalFile::openRelativeFileSelector(const QString& folderPath)
{
    auto openFromFolder = QDir::toNativeSeparators(Utilities::getDefaultBasePath());
    if (!folderPath.isEmpty())
    {
        openFromFolder = QDir::toNativeSeparators(folderPath);
    }

    SelectorInfo info;
    info.title = mTitle;
    info.multiSelection = false;
    info.defaultDir = openFromFolder;

    QPointer<const QObject> context = this;
    info.func = [this, context, openFromFolder](QStringList selection)
    {
        if(context && !selection.isEmpty())
        {
            sendFileChosenSignal(Platform::getInstance()->preparePathForSync(selection.first()),
                                 openFromFolder);
        }
    };

    Platform::getInstance()->fileSelector(info);
}

void ChooseLocalFile::sendFileChosenSignal(const QString& file, const QString& relativePath)
{
    if (!file.isNull() && !file.isEmpty())
    {
        if (relativePath.isEmpty())
        {
            emit fileChosen(file);
        }
        else
        {
            emit fileChosen(QDir(relativePath).relativeFilePath(file));
        }
    }
}
