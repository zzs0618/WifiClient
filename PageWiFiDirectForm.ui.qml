import QtQuick 2.7
import QtQuick.Controls 2.1

Item {
    property alias listP2PDevices: listP2PDevices

    Rectangle {
        id: titleP2P
        width: parent.width
        height: 50
        z: 1

        Text {
            anchors.left: parent.left
            anchors.leftMargin: 10
            anchors.verticalCenter: parent.verticalCenter
            font.bold: true
            color: switchP2P.checked ? "#E91E63" : "#9E9E9E"
            text: qsTr("开启P2P")
        }

        Switch {
            id: switchP2P
            anchors.verticalCenter: parent.verticalCenter
            anchors.right: parent.right
            anchors.rightMargin: 10
        }
    }
    Rectangle {
        anchors.top: titleP2P.bottom
        width: parent.width
        height: 10
        z: 1
        gradient: Gradient {
            GradientStop {
                position: 0.0
                color: "lightgray"
            }
            GradientStop {
                position: 1.0
                color: "white"
            }
        }
    }

    ListView {
        id: listP2PDevices
        anchors.fill: parent
        anchors.topMargin: titleP2P.height + 10
        anchors.leftMargin: 15
        anchors.rightMargin: 15

        model: ListModel {
            ListElement {
                name: "Net1"
                address: 3
                type: 0
            }
            ListElement {
                name: "Net2"
                address: 3
                type: 0
            }
            ListElement {
                name: "Net3"
                address: 3
                type: 0
            }
            ListElement {
                name: "Net4"
                address: 3
                type: 0
            }
            ListElement {
                name: "Net5"
                address: 3
                type: 0
            }
        }

        delegate: Item {
            x: 5
            width: listP2PDevices.width
            height: 40
            Row {
                spacing: 10
                Image {
                    id: icon
                    source: "qrc:/res/p2p_device_" + type + ".png"
                }
                Text {
                    width: listP2PDevices.width - icon.width - 10
                    anchors.verticalCenter: parent.verticalCenter
                    elide: Text.ElideRight
                    color: "#4CAF50"
                    text: name
                }
            }
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    p2pDevice.connectPBC(address)
                }
            }
        }
    }
}
