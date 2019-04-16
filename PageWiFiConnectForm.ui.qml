import QtQuick 2.7
import QtQuick.Controls 2.1
//import QtQuick.Controls.Material 2.1

Item {
    property alias listWLAN: listWLAN

    Rectangle {
        id: titleWLAN
        width: parent.width
        height: 50
//        Material.elevation: 5
        z: 1

        Text {
            anchors.left: parent.left
            anchors.leftMargin: 10
            anchors.verticalCenter: parent.verticalCenter
            font.bold: true
            color: switchWLAN.checked ? "#E91E63" : "#9E9E9E"
            text: qsTr("开启WLAN")
        }

        Switch {
            id: switchWLAN
            anchors.verticalCenter: parent.verticalCenter
            anchors.right: parent.right
            anchors.rightMargin: 10
        }
    }
    Rectangle {
        anchors.top: titleWLAN.bottom
        width: parent.width
        height: 10
        z: 1
        gradient: Gradient {
            GradientStop { position: 0.0; color: "lightgray" }
            GradientStop { position: 1.0; color: "white" }
        }
    }

    ListView {
        id: listWLAN
        anchors.fill: parent
        anchors.topMargin: titleWLAN.height + 10
        anchors.leftMargin: 15
        anchors.rightMargin: 15
        delegate: Item {
            x: 5
            width: listWLAN.width
            height: 40
            Row {
                spacing: 10
                Image {
                    id: icon
                    source: "qrc:/res/wifi_level_" + signalLevel + ".png"
                }
                Text {
                    width: listWLAN.width - icon.width - 10
                    anchors.verticalCenter: parent.verticalCenter
                    elide: Text.ElideRight
                    color: "#4CAF50"
                    text: ssid
                }
            }
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    dialog.title = ssid
                    dialog.open();
                }
            }
        }
    }

    Dialog {
        id: dialog
        width: parent.width
        height: parent.height
        modal: true
        header: Item{}
        background: Item{}

        DialogWifiInput {
            id: wifiInput
            anchors.centerIn: parent
            width: 800
            height: 500
            title: dialog.title

            onSubmit: {
                dialog.close();

                console.log("Ok clicked", password)
            }
            onCancel: {
                dialog.close();

                console.log("Cancel clicked")
            }
        }
    }
}
