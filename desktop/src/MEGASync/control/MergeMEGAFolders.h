#ifndef MERGEMEGAFOLDERS_H
#define MERGEMEGAFOLDERS_H

#include "megaapi.h"

#include <QObject>

#include <memory>

//FOLDER MERGE LOGIC
/*
   1. Detect if there are more than 1 folder with the same name in the name conflict received from the SDK
   2. Get the folder with more files (we can call it the "main" folder) as it is going to be faster moving other folders to this one
   3. Start iterating the rest of folders one by one (we can call them the "secondary" folders:
        a. If the secondary and the main folder have a file with the same name
            i.  If it is identical (same fingerpint), we skip it
            ii. It if is not identical (different fingerprint), I move the secondary folder file with a different name (%1 suffix)
        b. If the secondary folder has a file which is not in the main folder, we move it directly.
        c. If the secondary and the main folder have a folder with the same name:
            i.  We run this algorithm recursively but updating the main and the secondary folders pointer.
        d. If the secondary folder has a folder which is not in the main folder, we move it directly
*/
class MergeMEGAFolders: public QObject
{
    Q_OBJECT

public:
    enum class ActionForDuplicates
    {
        Rename,
        IgnoreAndRemove,
        IgnoreAndMoveToBin,
    };

    enum class Strategy
    {
        Move,
        Copy
    };

    MergeMEGAFolders(ActionForDuplicates action,
                     Qt::CaseSensitivity sensitivity,
                     Strategy strategy = Strategy::Move);

    int merge(mega::MegaNode* folderTarget, mega::MegaNode* folderToMerge);

signals:
    void nestedItemMerged(mega::MegaHandle handle);
    void finished();

private:
    int performMerge(mega::MegaNode* folderTarget, mega::MegaNode* folderToMerge);

    // Preparation methods
    void readTargetFolder(
        mega::MegaNode* folderTarget,
        QMap<QString, std::shared_ptr<mega::MegaNode>>& targetNodeWithoutNameConflict,
        QMap<QString, std::shared_ptr<mega::MegaNode>>& targetNodeWithNameConflict);
    int fixTargetFolderNameConflicts(
        const QMap<QString, std::shared_ptr<mega::MegaNode>>& targetNodeWithNameConflict);
    int mergeNestedNodesIntoTargetFolder(
        mega::MegaNode* folderTarget,
        mega::MegaNode* folderToMerge,
        QMap<QString, std::shared_ptr<mega::MegaNode>>& targetNodeWithoutNameConflict);
    int finishMerge(mega::MegaNode* folderTarget, mega::MegaNode* folderToMerge);

    // Utilities
    void logError(int error);
    int rename(mega::MegaNode* nodeToRename,
               mega::MegaNode* parentNode,
               QStringList& itemsBeingRenamed);
    QString getNodeName(mega::MegaNode* node);

    Qt::CaseSensitivity mCaseSensitivity;
    ActionForDuplicates mAction;
    Strategy mStrategy;
};

#endif // MERGEMEGAFOLDERS_H
