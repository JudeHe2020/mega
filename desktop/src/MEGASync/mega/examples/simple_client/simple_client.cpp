/**
 * @file examples/simple_client/simple_client.cpp
 * @brief Example app
 *
 * (c) 2013-2025 by Mega Limited, Auckland, New Zealand
 *
 * This file is part of the MEGA SDK - Client Access Engine.
 *
 * Applications using the MEGA API must present a valid application key
 * and comply with the the rules set forth in the Terms of Service.
 *
 * The MEGA SDK is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 * @copyright Simplified (2-clause) BSD License.
 *
 * You should have received a copy of the license along with this
 * program.
 */

/*
this example shows how to upload a file to MEGA using the C++ SDK.
1. creates a file fileforUpload.txt with 5MB of content,
2. set porxy settings,
3. login using a session key
4. fetche the nodes in the root folder
5. show the files/folders in the root folder
6. upload the file fileforUpload.txt to the root folder
7. show the progress of the upload
8. when the upload is finished, it shows the result of the upload
9. delete the file fileforUpload.txt

*/

#include <QNetworkProxy>

#include <chrono>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <megaapi.h>
#include <sstream>
#include <string>
#include <thread>

// ENTER YOUR CREDENTIALS HERE
// #define MEGA_EMAIL "EMAIL"
// #define MEGA_PASSWORD "PASSWORD"

#define SESSION_KEY \
    "ATrUgZcI2Tb6YRGudQ9svoFwwkTIuTlg8RfyTBX7BBXaWlFVOWN1alo4b2_PS2diYaKyZeABpvHMusLG"

// Get yours for free at https://mega.io/developers#source-code
// #define APP_KEY "9gETCbhB"
// #define USER_AGENT "Simple-Client example app"
#define APP_KEY "FhMgXbqb"
#define USER_AGENT "MEGAsync/5.11.0.3"

#define LOG_LOCATION() \
    std::cout << displayTime() << "[" << __func__ << "][" \
              << (std::string(__FILE__).substr(std::string(__FILE__).find_last_of("/\\") + 1)) \
              << ":" << __LINE__ << "] "

using namespace mega;
using namespace std;

std::string displayTime()
{
    auto now = std::chrono::system_clock::now();
    std::time_t now_time_t = std::chrono::system_clock::to_time_t(now);
    std::tm local_tm;
#ifdef _WIN32
    localtime_s(&local_tm, &now_time_t); // Windows
#else
    localtime_r(&now_time_t, &local_tm); // Linux/Unix
#endif
    auto duration = now.time_since_epoch();
    auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(duration) % 1000;

    std::ostringstream oss;
    oss << std::put_time(&local_tm, "[%Y-%m-%d %H:%M:%S") << '.' << std::setfill('0')
        << std::setw(3) << milliseconds.count() << "]";

    return oss.str();
}

class MyListener: public MegaListener, public MegaRequestListener
{
public:
    bool finished{};

    MyListener(std::string filename)
    {
        mFileForUpload = filename;
        if (!creatFileForUpload())
        {
            return;
        }
        finished = false;
    }

    virtual void onRequestFinish(MegaApi* api, MegaRequest* request, MegaError* e)
    {
        LOG_LOCATION() << request->toString() << " ErrorCode:" << e->getErrorString() << std::endl;

        if (e->getErrorCode() != MegaError::API_OK)
        {
            finished = true;
            return;
        }

        switch (request->getType())
        {
            case MegaRequest::TYPE_LOGIN:
            {
                api->fetchNodes();
                break;
            }
            case MegaRequest::TYPE_FETCH_NODES:
            {
                LOG_LOCATION() << request->toString()
                               << "Showing files/folders in the root folder:" << std::endl;
                MegaNode* root = api->getRootNode();
                MegaNodeList* list = api->getChildren(root);

                for (int i = 0; i < list->size(); i++)
                {
                    MegaNode* node = list->get(i);
                    if (node->isFile())
                        LOG_LOCATION() << request->toString() << "File:";
                    else
                        LOG_LOCATION() << "Folder: ";

                    LOG_LOCATION() << node->getName() << std::endl;
                }

                delete list;

                LOG_LOCATION() "Uploading " << mFileForUpload << std::endl;

                api->startUpload(mFileForUpload.c_str() /*localPath*/,
                                 root /*parent*/
                                 ,
                                 nullptr /*filename*/
                                 ,
                                 0 /*mtime*/
                                 ,
                                 nullptr /*appData*/
                                 ,
                                 false /*isSourceTemporary*/
                                 ,
                                 false /*startFirst*/
                                 ,
                                 nullptr); /*cancelToken*/

                delete root;
                break;
            }
            default:
                break;
        }
        LOG_LOCATION() << request->toString() << " Done " << std::endl;
    }

    // Currently, this callback is only valid for the request fetchNodes()
    virtual void onRequestUpdate(MegaApi*, MegaRequest* request)
    {
        LOG_LOCATION() << "Loading filesystem " << request->getTransferredBytes() << " / "
                       << request->getTotalBytes() << std::endl;
    }

    virtual void onRequestTemporaryError(MegaApi*, MegaRequest* request, MegaError* error)
    {
        LOG_LOCATION() << "Temporary error in request: " << request->toString()
                       << error->getErrorString() << std::endl;
    }

    virtual void onTransferFinish(MegaApi*, MegaTransfer*, MegaError* error)
    {
        if (error->getErrorCode())
        {
            LOG_LOCATION() << "Transfer finished with error: " << error->getErrorString()
                           << std::endl;
        }
        else
        {
            LOG_LOCATION() << "Transfer finished OK" << std::endl;
        }
        removeFileForUpload();
        finished = true;
    }

    virtual void onTransferUpdate(MegaApi*, MegaTransfer* transfer)
    {
        LOG_LOCATION() << "Transfer progress: " << transfer->getTransferredBytes() << "/"
                       << transfer->getTotalBytes() << std::endl;
    }

    virtual void onTransferTemporaryError(MegaApi*, MegaTransfer*, MegaError* error)
    {
        LOG_LOCATION() << "Temporary error in transfer: " << error->getErrorString() << std::endl;
    }

    virtual void onUsersUpdate(MegaApi*, MegaUserList* users)
    {
        if (users == NULL)
        {
            // Full account reload
            return;
        }
        LOG_LOCATION() << "There are " << users->size() << " new or updated users in your account"
                       << std::endl;
    }

    virtual void onNodesUpdate(MegaApi*, MegaNodeList* nodes)
    {
        if (nodes == NULL)
        {
            // Full account reload
            return;
        }

        LOG_LOCATION() << "There are " << nodes->size() << " new or updated node/s in your account"
                       << std::endl;
    }

    virtual void onSetsUpdate(MegaApi*, MegaSetList* sets)
    {
        if (sets)
        {
            LOG_LOCATION() << "There are " << sets->size()
                           << " new or updated Set/s in your account" << std::endl;
        }
    }

    virtual void onSetElementsUpdate(MegaApi*, MegaSetElementList* elements)
    {
        if (elements)
        {
            LOG_LOCATION() << "There are " << elements->size()
                           << " new or updated Set-Element/s in your account" << std::endl;
        }
    }

private:
    string mFileForUpload;

    bool creatFileForUpload()
    {
        if (mFileForUpload.empty())
        {
            LOG_LOCATION() << "mFileForUpload undefined" << std::endl;
            return false;
        }
        std::ofstream file(mFileForUpload, std::ios::out | std::ios::binary);
        if (!file.is_open())
        {
            LOG_LOCATION() << "Failed to open file: " << mFileForUpload << std::endl;
            return false;
        }

        const size_t size = 1024 * 1024 * 5; // 5MB
        std::string content(size, 'H');

        file.write(content.c_str(), content.size());

        if (file.fail())
        {
            LOG_LOCATION() << "Failed to write to file: " << mFileForUpload << std::endl;
            return false;
        }

        file.close();

        LOG_LOCATION() << "File " << mFileForUpload << " created successfully with 5MB of content."
                       << std::endl;
        return true;
    }

    bool removeFileForUpload()
    {
        if (mFileForUpload.empty())
        {
            LOG_LOCATION() << "mFileForUpload undefined" << std::endl;
            return false;
        }

        if (std::remove(mFileForUpload.c_str()) == 0)
        {
            LOG_LOCATION() << "File " << mFileForUpload << " deleted successfully." << std::endl;
        }
        else
        {
            LOG_LOCATION() << "Error deleting file " << mFileForUpload << std::endl;
            return false;
        }
        return true;
    }
};

void applyProxySettings(MegaApi* megaApi)
{
    QNetworkProxy proxy(QNetworkProxy::NoProxy);
    MegaProxy* proxySettings = new MegaProxy();
    proxySettings->setProxyType(MegaProxy::PROXY_AUTO);

    MegaProxy* autoProxy = megaApi->getAutoProxySettings();
    delete proxySettings;
    proxySettings = autoProxy;

    if (proxySettings->getProxyType() == MegaProxy::PROXY_CUSTOM)
    {
        string sProxyURL = proxySettings->getProxyURL();
        QString proxyURL = QString::fromUtf8(sProxyURL.data());

        QStringList arguments = proxyURL.split(QString::fromUtf8(":"));
        if (arguments.size() == 2)
        {
            proxy.setType(QNetworkProxy::HttpProxy);
            proxy.setHostName(arguments[0]);
            proxy.setPort(arguments[1].toUShort());
        }
    }

    megaApi->setProxySettings(proxySettings);
    delete proxySettings;
    QNetworkProxy::setApplicationProxy(proxy);
    megaApi->retryPendingConnections(true, true);
}

void loginAndUploadFile(string filename)
{
    MyListener listener(filename);
    string basePath = ".";
    LOG_LOCATION() << "start with basePath: " << basePath << std::endl;
    MegaApi* api = new MegaApi(APP_KEY, nullptr, basePath.c_str(), USER_AGENT);
    api->addListener(&listener);
    applyProxySettings(api);
    api->setLogLevel(MegaApi::LOG_LEVEL_INFO);
    long long newPayLoadLogSize = 10240;
    api->setMaxPayloadLogSize(newPayLoadLogSize);
    api->setLanguage("en");
    api->setDefaultFilePermissions(0);
    api->setDefaultFolderPermissions(0);
    api->retrySSLerrors(true);
    api->setPublicKeyPinning(true);

    // Login. You can get the result in the onRequestFinish callback of your listener
    api->fastLogin(SESSION_KEY, &listener);

    // wait for login and upload file finish
    while (!listener.finished)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
}

int main()
{
    std::string fileForUpload = "fileforUpload.txt";
    loginAndUploadFile(fileForUpload);
    return 0;
}
