import QtQuick 2.4
import QtQuick.Controls 2.0
import Wifi 1.0

PageWiFiDirectForm {

    property bool active: SwipeView.isCurrentItem

    onActiveChanged: {
        if(active)
            p2pDevice.start()
        else
            p2pDevice.stop()
    }

    listP2PDevices.model: WifiP2PDeviceModel {
        id: p2pDevice
    }
}
