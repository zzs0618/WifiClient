import QtQuick 2.7
import QtQuick.Controls 2.1


//import QtQuick.Controls.Material 2.1
Item {
    property alias switchWLAN: switchWLAN
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
            checked: wifiAPModel.isOpen
        }
    }
    Rectangle {
        anchors.top: titleWLAN.bottom
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
        id: listWLAN
        anchors.fill: parent
        anchors.topMargin: titleWLAN.height + 10
        anchors.leftMargin: 15
        anchors.rightMargin: 15
        section.property: "type"
        section.criteria: ViewSection.FullString
        section.delegate: Component {
            Rectangle {
                width: listWLAN.width
                height: 16
                color: "lightgray"
                Text {
                    anchors.verticalCenter: parent.verticalCenter
                    text: section == "2" ? qsTr(
                                               "当前的WLAN") : (section
                                                             == "1" ? qsTr("已连接的WLAN") : qsTr(
                                                                          "选取附近的WLAN"))
                    font.pixelSize: 12
                    color: "gray"
                }
            }
        }

        model: ListModel {
            ListElement {
                type: 0
                ssid: "Net1"
                signalLevel: 3
            }
            ListElement {
                type: 1
                ssid: "Net2"
                signalLevel: 3
            }
            ListElement {
                type: 1
                ssid: "Net3"
                signalLevel: 3
            }
            ListElement {
                type: 2
                ssid: "Net4"
                signalLevel: 3
            }
            ListElement {
                type: 2
                ssid: "Net5"
                signalLevel: 3
            }
        }

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
                    text: if (type == 2)
                              return ssid + "(" + wifiAPModel.status["ipAddress"] + ")"
                          else
                              return ssid
                }
            }
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    dialog.title = ssid
                    dialog.open()
                }
            }
        }
    }

    Dialog {
        id: dialog
        width: parent.width
        height: parent.height
        modal: true
        header: Item {
        }
        background: Item {
        }

        DialogWifiInput {
            id: wifiInput
            anchors.centerIn: parent
            width: 800
            height: 500
            title: dialog.title

            onSubmit: {
                dialog.close()
                wifiAPModel.addNetwork(ssid, password)
                console.log("Ok clicked", password)
            }
            onCancel: {
                dialog.close()

                console.log("Cancel clicked")
            }
        }
    }
}
