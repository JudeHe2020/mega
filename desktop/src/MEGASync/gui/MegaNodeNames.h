#ifndef MEGANODENAMES_H
#define MEGANODENAMES_H

#include "megaapi.h"

#include <QCoreApplication>
#include <QObject>

class MegaNodeNames : public QObject
{
    Q_OBJECT

public:

    MegaNodeNames() = default;
    ~MegaNodeNames() = default;

    static QString getCloudDriveName()
    {
        return tr("Cloud Drive");
    }

    static QString getIncomingSharesName()
    {
        return tr("Incoming shares");
    }

    static QString getBackupsName()
    {
        return tr("Backups");
    }

    static QString getRubbishName()
    {
        return tr("Rubbish bin");
    }

    static QString getRootNodeName(mega::MegaNode* node)
    {
        if(node)
        {
            return tr(node->getName());
        }

        return QString();
    }

    static QString getNodeName(mega::MegaNode* node)
    {
        if(node)
        {
            if(node->isNodeKeyDecrypted())
            {
                return QString::fromUtf8(node->getName());
            }
            else
            {
                return getUndecryptedName();
            }
        }

        return QString();
    }

    static QString getUndecryptedName()
    {
        return QCoreApplication::translate("MegaError", "Decryption error");
    }
};

#endif // MEGANODENAMES_H
