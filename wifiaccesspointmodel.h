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

#ifndef WIFIACCESSPOINTMODEL_H
#define WIFIACCESSPOINTMODEL_H

#include <QAbstractListModel>
#include <QQmlParserStatus>

class WifiAccessPointModel : public QAbstractListModel, public QQmlParserStatus
{
    Q_OBJECT
    Q_PROPERTY(bool isOpen READ isOpen WRITE setIsOpen NOTIFY isOpenChanged)
    Q_PROPERTY(QVariantMap status READ status NOTIFY statusChanged)
    Q_INTERFACES(QQmlParserStatus)
public:
    explicit WifiAccessPointModel(QObject *parent = nullptr);

    bool isOpen() const;
    void setIsOpen(bool open);

    QVariantMap status() const;

    //From QAbstractListModel
    int rowCount(const QModelIndex & = QModelIndex()) const Q_DECL_OVERRIDE;
    QVariant data(const QModelIndex &index,
                  int role = Qt::DisplayRole) const Q_DECL_OVERRIDE;
    QHash<int, QByteArray> roleNames() const Q_DECL_OVERRIDE;

    //From QQmlParserStatus
    void classBegin() {}
    void componentComplete();

    Q_INVOKABLE void addNetwork(const QString &ssid, const QString &password);

signals:
    void isOpenChanged();
    void statusChanged();

protected slots:
    void onStatusChanged(const QString &status);
    void onAccessPointAdded(const QString &point);
    void onAccessPointUpdated(const QString &point);
    void onAccessPointRemoved(const QString &point);
    void onAccessPointCleard();

protected:
    int indexOf(const QString &ssid);

private:
    bool m_componentCompleted = false;
    QVariantMap m_status;
    QVariantList m_wifiAPs;
};

#endif // WIFIACCESSPOINTMODEL_H
