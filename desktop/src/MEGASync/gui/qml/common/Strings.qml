pragma Singleton
import QtQuick 2.15

QtObject {
    id: root

    readonly property string cancel: qsTr("Cancel")
    readonly property string continueText: /*qsTr*/("Continue")
    readonly property string choose: qsTr("Choose")
    readonly property string done: qsTr("Done")
    readonly property string dismiss: qsTr("Dismiss")
    readonly property string next: qsTr("Next")
    readonly property string skip: qsTr("Skip")
    readonly property string previous: qsTr("Previous")
    readonly property string tryAgain: qsTr("Try again")
    readonly property string viewInSettings: qsTranslate("OnboardingStrings", "View in Settings")
    readonly property string setExclusions: qsTr("Set Exclusions")
    readonly property string deviceNameSpecialCharactersErr: qsTr("The following characters are not allowed: %1")
    readonly property string deviceNameTooLongErr: qsTr("Maximum 32 characters")
    readonly property string deviceNameExistErr: qsTr("A device with this name already exists. Enter a different name.")
    readonly property string deviceNameEmptyErr: qsTr("Enter a device name")
    readonly property string ok: /*qsTr*/("Ok")

}
