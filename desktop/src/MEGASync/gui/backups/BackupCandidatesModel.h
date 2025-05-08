#ifndef BACKUPCANDIDATESMODEL_H
#define BACKUPCANDIDATESMODEL_H

#include "DataModel.h"
#include "SyncController.h"

#include <QSortFilterProxyModel>
#include <QTimer>

class BackupCandidatesController;

class BackupCandidatesModel: public DataModel
{
    Q_OBJECT

public:
    explicit BackupCandidatesModel(std::shared_ptr<BackupCandidatesController> controller,
                                   QObject* parent = nullptr);
    ~BackupCandidatesModel();

    QHash<int, QByteArray> roleNames() const override;
    void reset();
};

class BackupCandidatesProxyModel: public QSortFilterProxyModel
{
    Q_OBJECT

    Q_PROPERTY(bool selectedFilterEnabled READ selectedFilterEnabled WRITE setSelectedFilterEnabled
                   NOTIFY selectedFilterEnabledChanged)

public:
    explicit BackupCandidatesProxyModel(std::shared_ptr<BackupCandidatesController> controller);
    BackupCandidatesProxyModel() = default;

    bool selectedFilterEnabled() const;
    void setSelectedFilterEnabled(bool enabled);

signals:
    void selectedFilterEnabledChanged();

protected:
    bool filterAcceptsRow(int source_row, const QModelIndex& source_parent) const;

private:
    bool mSelectedFilterEnabled;
    std::shared_ptr<BackupCandidatesModel> mBackupsModel;
};

#endif // BACKUPCANDIDATESMODEL_H
