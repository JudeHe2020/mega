# This is offline test for Mega.
## test 1. Understand the JSON processing logic that is used for the f response and apply the same logic to actionpackets.
    I rewrite simple_client.cpp 
    mega\desktop\src\MEGASync\mega\examples\simple_client\simple_client.cpp
    it will do following tasks
        1. creates a file fileforUpload.txt with 5MB of content,
        2. set porxy settings,
        3. login using a session key
        4. fetche the nodes in the root folder
        5. show the files/folders in the root folder
        6. upload the file fileforUpload.txt to the root folder
        7. show the progress of the upload
        8. when the upload is finished, it shows the result of the upload
        9. delete the file fileforUpload.txt
## test 2. Enable Dark mode for MEGASync.
    this is a easy job, go 
    mega\desktop\src\MEGASync\gui\SettingsDialog.cpp, and do following modification
    SettingsDialog::SettingsDialog(MegaApplication* app, bool proxyOnly, QWidget* parent)
    {
          // mUi->gThemeSelector->hide();
          mUi->gThemeSelector->show();
    }

# built it 
mkdir c:\mega\

cd c:\mega\

git clone https://github.com/JudeHe2020/mega.git

git clone https://github.com/microsoft/vcpkg 

cd desktop

cmake -DCMAKE_GENERATOR_PLATFORM=x64 -DCMAKE_PREFIX_PATH=C:\Qt\5.15.2\msvc2019_64 -DVCPKG_ROOT=c:\mega\vcpkg -S c:\mega\desktop -B c:\mega\build-x64

cmake --build c:\mega\build-x64 --config Debug --target MEGAsync --target simple_client





