#include "ScanningWidget.h"

#include "BlurredShadowEffect.h"
#include "TransferMetaData.h"
#include "ui_ScanningWidget.h"
#include "Utilities.h"

#include <QMovie>

namespace
{
constexpr qreal RATIO_2X(2.0);
constexpr qreal RATIO_3X(3.0);
const QLatin1String SCANNING_FILE(":/animations/scanning.gif");
const QLatin1String SCANNING_FILE_2X(":/animations/scanning@2x.gif");
const QLatin1String SCANNING_FILE_3X(":/animations/scanning@3x.gif");
}

ScanningWidget::ScanningWidget(QWidget *parent) :
    QWidget(parent),
    mUi(new Ui::ScanningWidget)
{
    mUi->setupUi(this);
    mMovie = new QMovie(this);
    mMovie->setCacheMode(QMovie::CacheAll);
    mMovie->setFileName(getScanningFileName());

    setRole(mUi->lStepTitle, "title");
    setRole(mUi->lStepDescription, "details");

    mUi->pBlockingStageCancel->setGraphicsEffect(CreateBlurredShadowEffect());
    connect(mUi->pBlockingStageCancel, &QPushButton::clicked,
            this, &ScanningWidget::onCancelClicked);

    mPreviousStage = mega::MegaTransfer::STATE_NONE;
}

ScanningWidget::~ScanningWidget()
{
    delete mUi;
    delete mMovie;
}

void ScanningWidget::show()
{
    startAnimation();

    mUi->pBlockingStageCancel->show();
    mUi->pBlockingStageCancel->setEnabled(true);
    mUi->lStepTitle->setText(tr("Scanning"));
    mUi->lStepDescription->setText(QString());
}

void ScanningWidget::hide()
{
    mMovie->stop();
    mUi->lAnimation->setMovie(nullptr);
}

void ScanningWidget::disableCancelButton()
{
    mUi->pBlockingStageCancel->setEnabled(false);
}

void ScanningWidget::updateAnimation()
{
    if(mMovie->state() == QMovie::Running)
    {
        mMovie->stop();
        mUi->lAnimation->setMovie(nullptr);
    }
    startAnimation();
}

void ScanningWidget::onReceiveStatusUpdate(const FolderTransferUpdateEvent &event)
{
    const auto metaData = TransferMetaDataContainer::getAppDataByAppData(event.appData.c_str());
    if (metaData && (metaData->getPendingFiles() + metaData->getFileTransfersOK()) > 0)
    {
        const auto addedTransfers = metaData->getPendingFiles() + metaData->getFileTransfersOK();
        mUi->lStepTitle->setText(tr("Adding transfers…"));
        mUi->lStepDescription->setText(tr("%1/%2").arg(addedTransfers).arg(event.filecount));
    }
    else
    {
        switch (event.stage)
        {
            case mega::MegaTransfer::STAGE_SCAN:
            {
                mUi->lStepTitle->setText(tr("Scanning"));
                mUi->lStepDescription->setText(buildScanDescription(event.foldercount, event.filecount));
                break;
            }
            case mega::MegaTransfer::STAGE_CREATE_TREE:
            {
                mUi->lStepTitle->setText(tr("Creating folders"));
                mUi->lStepDescription->setText(tr("%1/%2").arg(event.createdfoldercount).arg(event.foldercount));
                break;
            }
        }
    }
    mPreviousStage = event.stage;
}

void ScanningWidget::onCancelClicked()
{
    emit cancel();
}

void ScanningWidget::changeEvent(QEvent* event)
{
    if (event->type() == QEvent::LanguageChange)
    {
        mUi->retranslateUi(this);
    }
    QWidget::changeEvent(event);
}

void ScanningWidget::startAnimation()
{
    if (mMovie->isValid())
    {
        mUi->lAnimation->setMovie(mMovie);
        mMovie->start();
    }
}

QString ScanningWidget::buildScanDescription(const unsigned int& folderCount, const unsigned int& fileCount)
{
    QString folderStr = tr("%n folder", "", static_cast<int>(folderCount));
    QString fileStr = tr("%n file", "", static_cast<int>(fileCount));
    return tr("found %1, %2").arg(folderStr, fileStr);
}

void ScanningWidget::setRole(QObject *object, const char *name)
{
    object->setProperty("role", QString::fromLatin1(name));
}

QString ScanningWidget::formattedNode(const QString &name)
{
    const QString quote = QString::fromLatin1("");
    const QChar ellipsis(0x2026);
    return quote + name + quote + ellipsis;
}

QString ScanningWidget::getScanningFileName() const
{
    QString gifFile;
    qreal ratio(Utilities::getDevicePixelRatio());
    if (ratio >= RATIO_2X && ratio < RATIO_3X)
    {
        gifFile = SCANNING_FILE_2X;
    }
    else if (ratio >= RATIO_3X)
    {
        gifFile = SCANNING_FILE_3X;
    }
    else
    {
        gifFile = SCANNING_FILE;
    }
    return gifFile;
}
