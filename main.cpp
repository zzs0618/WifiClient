/**
 ** This file is part of the WifiHelper project.
 ** Copyright 2019 张作深 <zhangzuoshen@hangsheng.com.cn>.
 **
 ** This program is free software: you can redistribute it and/or modify
 ** it under the terms of the GNU General Public License as published by
 ** the Free Software Foundation, either version 3 of the License, or
 ** (at your option) any later version.
 **
 ** This program is distributed in the hope that it will be useful,
 ** but WITHOUT ANY WARRANTY; without even the implied warranty of
 ** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 ** GNU General Public License for more details.
 **
 ** You should have received a copy of the GNU General Public License
 ** along with this program.  If not, see <http://www.gnu.org/licenses/>.
 **/

#include <QGuiApplication>
#include <QQmlContext>
#include <QQmlApplicationEngine>

#include "sortfilterproxymodel.h"
#include "wifiaccesspointmodel.h"
#include "wifip2pdevicemodel.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    qmlRegisterType<SortFilterProxyModel>("Wifi", 1, 0, "SortFilterProxyModel");
    qmlRegisterType<WifiAccessPointModel>("Wifi", 1, 0, "WifiAccessPointModel");
    qmlRegisterType<WifiP2PDeviceModel>("Wifi", 1, 0, "WifiP2PDeviceModel");

    QQmlApplicationEngine engine;
    engine.load(QUrl(QLatin1String("qrc:/main.qml")));

    if (engine.rootObjects().isEmpty()) {
        return -1;
    }

    return app.exec();
}
