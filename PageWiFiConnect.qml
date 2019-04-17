import QtQuick 2.7
import Wifi 1.0

PageWiFiConnectForm {

    WifiAccessPointModel {
        id: wifiAPModel
    }

    listWLAN.model: SortFilterProxyModel {
        id: proxyModel
        source: wifiAPModel
        sortRole: "type,signalLevel"
        sortOrder: Qt.DescendingOrder
    }

}
