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

#include "wifip2pdevicemodel.h"
#include "wificlient.h"

#include <QJsonDocument>
#include <QJsonArray>
#include <QDebug>

WifiP2PDeviceModel::WifiP2PDeviceModel(QObject *parent) :
    QAbstractListModel(parent)
{
    WifiClient *client = WifiClient::instance();
    connect(client, SIGNAL(p2pDeviceFound(QString)),
            SLOT(onDeviceFound(QString)));
}

int WifiP2PDeviceModel::rowCount(const QModelIndex &) const
{
    return m_devcies.count();
}

QVariant WifiP2PDeviceModel::data(const QModelIndex &index,
                                  int role) const
{
    if (!index.isValid() || index.row() < 0) {
        return QVariant();
    }

    if (index.row() >= m_devcies.count()) {
        qWarning() << "WifiP2PDeviceModel: Index out of bound";
        return QVariant();
    }

    QVariantMap ap = m_devcies.value(index.row()).toMap();
    return ap.value(roleNames().value(role));
}

QHash<int, QByteArray> WifiP2PDeviceModel::roleNames() const
{
    static QHash<int, QByteArray> roles = {
        {Qt::DisplayRole + 1, "name"},
        {Qt::DisplayRole + 2, "address"},
        {Qt::DisplayRole + 3, "type"}
    };

    return roles;
}

void WifiP2PDeviceModel::componentComplete()
{
    m_componentCompleted = true;
}

void WifiP2PDeviceModel::start()
{
    WifiClient *client = WifiClient::instance();
    client->p2pStart();
}

void WifiP2PDeviceModel::stop()
{
    WifiClient *client = WifiClient::instance();
    client->p2pStop();
}

void WifiP2PDeviceModel::connectPBC(const QString &address)
{
    WifiClient *client = WifiClient::instance();
    client->p2pConnectPBC(address);
}

void WifiP2PDeviceModel::onDeviceFound(const QString &device)
{
    QJsonDocument doc = QJsonDocument::fromJson(device.toUtf8());
    int count = m_devcies.length();
    beginInsertRows(QModelIndex(), count, count);
    m_devcies << doc.toVariant().toMap();
    endInsertRows();
}
