import QtQuick 2.4

Item {
    id: root
    width: 510
    height: 510

    property string title: qsTr("SSID")
    property bool shift: false
    property var keyCodes: ["0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z"]
    signal submit(string ssid, string password)
    signal cancel

    property int buttonWidth: (root.width - 10) / 10

    Rectangle {
        id: titleBg
        width: parent.width
        height: 100
        color: "lightblue"
        border.color: "blue"
        border.width: 1
        radius: 10

        Text {
            anchors.centerIn: parent
            verticalAlignment: Text.AlignVCenter
            font.pixelSize: 48
            text: root.title
        }
    }

    Rectangle {
        id: rectangle
        anchors.top: titleBg.bottom
        width: parent.width
        height: 70
        color: "lightgreen"
        border.color: "green"
        border.width: 1

        Text {
            id: input
            anchors.rightMargin: 5
            anchors.leftMargin: 5
            verticalAlignment: Text.AlignVCenter
            anchors.fill: parent
            font.pixelSize: 32
            onTextChanged: {
                if(input.text.length >= 8)
                    btnSubmit.enabled = true
                else
                    btnSubmit.enabled = false
            }
        }
    }

    Grid {
        anchors.top: rectangle.bottom
        anchors.topMargin: 2
        columns: 10
        spacing: 1
        Repeater {
            model: 36
            delegate: Component {
                Rectangle {
                    width: buttonWidth
                    height: buttonWidth
                    border.color: "blue"
                    border.width: 1
                    Text {
                        id: txt_button
                        anchors.centerIn: parent
                        text: shift ? keyCodes[index].toUpperCase(
                                          ) : keyCodes[index]
                    }
                    MouseArea {
                        anchors.fill: parent
                        onClicked: input.text += txt_button.text
                    }
                }
            }
        }
        Rectangle {
            width: buttonWidth
            height: buttonWidth
            border.color: "blue"
            border.width: 1
            Text {
                anchors.centerIn: parent
                color: "blue"
                text: "Shift"
            }
            MouseArea {
                anchors.fill: parent
                onClicked: shift = !shift
            }
        }
        Rectangle {
            width: buttonWidth
            height: buttonWidth
            border.color: "blue"
            border.width: 1
            Text {
                anchors.centerIn: parent
                color: "blue"
                text: "DEL"
            }
            MouseArea {
                anchors.fill: parent
                onClicked: input.text = input.text.substring(
                               0, input.text.length - 1)
            }
        }
        Rectangle {
            id: btnSubmit
            width: buttonWidth
            height: buttonWidth
            border.color: "blue"
            border.width: 1
            enabled: false
            Text {
                anchors.centerIn: parent
                color: btnSubmit.enabled ? "blue" : "gray"
                text: "Submit"
            }
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    root.submit(root.title, input.text)
                    input.text = ""
                }
            }
        }
        Rectangle {
            width: buttonWidth
            height: buttonWidth
            border.color: "blue"
            border.width: 1
            Text {
                anchors.centerIn: parent
                color: "blue"
                text: "Cancel"
            }
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    root.cancel()
                    input.text = ""
                }
            }
        }
    }
}
