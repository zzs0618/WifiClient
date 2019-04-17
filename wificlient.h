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

#ifndef WIFICLIENT_H
#define WIFICLIENT_H

#include <QObject>

class WifiClient : public QObject
{
    Q_OBJECT
public:
    static WifiClient *instance();

    QVariantMap status() const;

    QVariantList accessPoints() const;

    void addNetwork(const QString &ssid, const QString &password);

signals:
    void accessPointAdded(const QString &point);
    void accessPointUpdated(const QString &point);
    void accessPointRemoved(const QString &point);
    void statusChanged(const QString &status);

public slots:

protected slots:
    void onAccessPointUpdated(const QString &point);
    void onStatusChanged(const QString &status);

private:
    explicit WifiClient(QObject *parent = nullptr);
};

#endif // WIFICLIENT_H
