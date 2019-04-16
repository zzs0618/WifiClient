/**
 ** This file is part of the WifiClient project.
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

#include "wifiaccesspointmodel.h"
#include "wificlient.h"

#include <QJsonDocument>
#include <QJsonArray>
#include <QDebug>

WifiAccessPointModel::WifiAccessPointModel(QObject *parent) :
    QAbstractListModel(parent)
{
    WifiClient *client = WifiClient::instance();
    connect(client, SIGNAL(accessPointUpdate(QString)),
            SLOT(onAccessPointUpdate(QString)));
}

int WifiAccessPointModel::rowCount(const QModelIndex &) const
{
    return m_wifiAPs.count();
}

QVariant WifiAccessPointModel::data(const QModelIndex &index,
                                    int role) const
{
    if (!index.isValid() || index.row() < 0) {
        return QVariant();
    }

    if (index.row() >= m_wifiAPs.count()) {
        qWarning() << "WifiAccessPointModel: Index out of bound";
        return QVariant();
    }

    QVariantMap ap = m_wifiAPs.value(index.row()).toMap();
    return ap.value(roleNames().value(role));
}

QHash<int, QByteArray> WifiAccessPointModel::roleNames() const
{
    static QHash<int, QByteArray> roles = {
        {Qt::DisplayRole + 1, "ssid"},
        {Qt::DisplayRole + 2, "bssid"},
        {Qt::DisplayRole + 3, "signalLevel"}
    };

    return roles;
}

void WifiAccessPointModel::componentComplete()
{
    m_componentCompleted = true;
}

void WifiAccessPointModel::addNetwork(const QString &ssid,
                                      const QString &password)
{
    WifiClient *client = WifiClient::instance();
    client->addNetwork(ssid, password);
}

void WifiAccessPointModel::onAccessPointUpdate(const QString &point)
{
    beginResetModel();

    QJsonDocument doc = QJsonDocument::fromJson(point.toUtf8());
    m_wifiAPs.clear();
    for(QVariant var : doc.array().toVariantList()) {
        QVariantMap map = var.toMap();
        int rssi = map.value("rssi").toInt();
        int level = 0;
        if(rssi < -85) {
            level = 0;
        } else if(rssi < -70) {
            level = 1;
        } else if(rssi < -55) {
            level = 2;
        } else {
            level = 3;
        }
        map.insert("signalLevel", level);
        m_wifiAPs << map;
    }

    endResetModel();
}

