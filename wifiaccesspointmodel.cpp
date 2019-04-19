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
    connect(client, SIGNAL(isOpenChanged()), SIGNAL(isOpenChanged()));
    connect(client, SIGNAL(statusChanged(QString)),
            SLOT(onStatusChanged(QString)));
    connect(client, SIGNAL(accessPointAdded(QString)),
            SLOT(onAccessPointAdded(QString)));
    connect(client, SIGNAL(accessPointUpdated(QString)),
            SLOT(onAccessPointUpdated(QString)));
    connect(client, SIGNAL(accessPointRemoved(QString)),
            SLOT(onAccessPointRemoved(QString)));
    connect(client, SIGNAL(accessPointCleard()), SLOT(onAccessPointCleard()));

    m_status = client->status();
    m_wifiAPs = client->accessPoints();
}

bool WifiAccessPointModel::isOpen() const
{
    WifiClient *client = WifiClient::instance();
    return client->isOpen();
}

void WifiAccessPointModel::setIsOpen(bool open)
{
    WifiClient *client = WifiClient::instance();
    client->setIsOpen(open);
}

QVariantMap WifiAccessPointModel::status() const
{
    return m_status;
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
        {Qt::DisplayRole + 3, "signalLevel"},
        {Qt::DisplayRole + 4, "type"},
        {Qt::DisplayRole + 5, "ipAddress"}
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

void WifiAccessPointModel::onStatusChanged(const QString &status)
{
    QJsonDocument doc = QJsonDocument::fromJson(status.toUtf8());
    m_status = doc.toVariant().toMap();
    Q_EMIT statusChanged();
}

void WifiAccessPointModel::onAccessPointAdded(const QString &point)
{
    QJsonDocument doc = QJsonDocument::fromJson(point.toUtf8());
    int first = m_wifiAPs.length();
    int last = first + doc.array().count() - 1;
    beginInsertRows(QModelIndex(), first, last);
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
    endInsertRows();
}

void WifiAccessPointModel::onAccessPointUpdated(const QString &point)
{
    QJsonDocument doc = QJsonDocument::fromJson(point.toUtf8());
    for(QVariant var : doc.array().toVariantList()) {
        QVariantMap map = var.toMap();
        int i = indexOf(map["ssid"].toString());

        if(i >= 0) {
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
            m_wifiAPs[i] = map;
            Q_EMIT this->dataChanged(index(i), index(i));
        }
    }
}

void WifiAccessPointModel::onAccessPointRemoved(const QString &point)
{
    QJsonDocument doc = QJsonDocument::fromJson(point.toUtf8());
    for(QVariant var : doc.array().toVariantList()) {
        QVariantMap map = var.toMap();
        int i = indexOf(map["ssid"].toString());
        if(i >= 0) {
            beginRemoveRows(QModelIndex(), i, i);
            m_wifiAPs.removeAt(i);
            endRemoveRows();
        }
    }
}

void WifiAccessPointModel::onAccessPointCleard()
{
    beginResetModel();
    m_wifiAPs.clear();
    endResetModel();
}

int WifiAccessPointModel::indexOf(const QString &ssid)
{
    for(int i = 0; i < m_wifiAPs.length(); ++i) {
        QVariantMap map = m_wifiAPs[i].toMap();
        if(map["ssid"].toString() == ssid) {
            return i;
        }
    }
    return -1;
}
