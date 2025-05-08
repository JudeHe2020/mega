import QtQuick 2.15
import QtQuick.Controls 2.15

import common 1.0

import components.texts 1.0
import components.textAreas 1.0
import components.buttons 1.0
import components.views 1.0

import QmlItem 1.0

QmlItem {
    id: root

    property QtObject widgetAccess: instancesManager.instances["qmlWidgetWrapperBaseAccess"] || null
    property QtObject surveyComponentAccess: instancesManager.instances["surveyComponentAccess"] || null
    property QtObject surveysAccess: instancesManager.instances["surveysAccess"] || null

    Rectangle {

        anchors.fill: parent
        color: ColorTheme.backgroundBlur

        Rectangle {
            id: content

            readonly property string inputDataView: "inputDataView"
            readonly property string finalView: "finalView"
            readonly property int contentBorderWidth: 1
            readonly property real contentMargin: 24.0
            readonly property real contentRadius: 8.0
            readonly property real contentWidth: 250.0
            readonly property real contentSpacing: 20.0
            readonly property real titleLineHeight: 24.0
            readonly property real descriptionLineHeight: 20.0
            readonly property real commentItemMaxHeight: 60.0

            anchors.centerIn: parent
            width: stackViewItem.width + 2 * content.contentMargin
            height: stackViewItem.height + 2 * content.contentMargin
            radius: content.contentRadius
            border {
                color: ColorTheme.borderStrong
                width: content.contentBorderWidth
            }
            color: ColorTheme.pageBackground

            state: content.inputDataView
            states: [
                State {
                    name: content.inputDataView
                    StateChangeScript {
                        script: stackViewItem.replace(inputDataViewComponent);
                    }
                },
                State {
                    name: content.finalView
                    StateChangeScript {
                        script: stackViewItem.replace(finalViewComponent);
                    }
                }
            ]

            StackViewBase {
                id: stackViewItem

                anchors {
                    centerIn: parent
                    margins: content.contentMargin
                }
                width: content.contentWidth
                height: currentItem.implicitHeight

                Component {
                    id: inputDataViewComponent

                    Column {
                        id: inputDataViewColumn

                        spacing: content.contentSpacing

                        Text {
                            id: titleItem

                            width: parent.width
                            font {
                                pixelSize: Text.Size.MEDIUM_LARGE
                                weight: Font.Bold
                            }
                            lineHeight: content.titleLineHeight
                            lineHeightMode: Text.FixedHeight
                            horizontalAlignment: Text.AlignHCenter
                            text: surveysAccess ? surveysAccess.question : ""
                        }

                        RateScaleItem {
                            id: rateScale

                            width: parent.width
                        }

                        TextArea {
                            id: commentItem

                            anchors {
                                left: parent.left
                                right: parent.right
                                margins: Constants.focusAdjustment
                            }
                            sizes {
                                adaptableHeight: true
                                maxHeight: content.commentItemMaxHeight
                                textSize: Text.Size.MEDIUM
                            }
                            maxCharLength: surveysAccess ? surveysAccess.commentMaxLength : 0
                            placeholderText: SurveyStrings.tellUsMore
                            visible: rateScale.score >= 1 && rateScale.score <= 2
                        }

                        Column {
                            id: buttonsItem

                            anchors {
                                left: parent.left
                                right: parent.right
                                margins: Constants.focusAdjustment
                            }
                            spacing: 0

                            PrimaryButton {
                                anchors {
                                    left: parent.left
                                    right: parent.right
                                }
                                sizes.fillWidth: true
                                text: SurveyStrings.submit
                                onClicked: {
                                    surveyComponentAccess.submitButtonClicked(rateScale.score,
                                                                              commentItem.text);
                                }
                                enabled: rateScale.score >= 0
                            }

                            TextButton {
                                anchors {
                                    left: parent.left
                                    right: parent.right
                                }
                                sizes.fillWidth: true
                                text: Strings.dismiss
                                onClicked: {
                                    widgetAccess.close();
                                }
                            }
                        }

                    }

                } // Component: inputDataViewComponent

                Component {
                    id: finalViewComponent

                    Column {
                        spacing: content.contentSpacing
                        anchors.fill: parent

                        Text {
                            width: parent.width
                            font {
                                pixelSize: Text.Size.MEDIUM_LARGE
                                bold: true
                            }
                            lineHeight: content.titleLineHeight
                            lineHeightMode: Text.FixedHeight
                            horizontalAlignment: Text.AlignHCenter
                            text: SurveyStrings.title
                        }

                        Text {
                            width: parent.width
                            font.pixelSize: Text.Size.MEDIUM
                            lineHeight: content.descriptionLineHeight
                            lineHeightMode: Text.FixedHeight
                            horizontalAlignment: Text.AlignHCenter
                            text: SurveyStrings.description
                        }

                        PrimaryButton {
                            anchors {
                                left: parent.left
                                right: parent.right
                                margins: Constants.focusAdjustment
                            }
                            sizes.fillWidth: true
                            text: SurveyStrings.okGotIt
                            onClicked: {
                                widgetAccess.close();
                            }
                        }
                    }

                } // Component: finalViewComponent

            } // StackView: stackViewItem

        } // Rectangle: content

        Connections {
            target: surveyComponentAccess

            function onSurveySubmitted() {
                content.state = content.finalView;
            }
        }

    }

}
