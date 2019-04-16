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
    Q_INTERFACES(QQmlParserStatus)
public:
    explicit WifiAccessPointModel(QObject *parent = nullptr);

    //From QAbstractListModel
    int rowCount(const QModelIndex & = QModelIndex()) const Q_DECL_OVERRIDE;
    QVariant data(const QModelIndex &index,
                  int role = Qt::DisplayRole) const Q_DECL_OVERRIDE;
    QHash<int, QByteArray> roleNames() const Q_DECL_OVERRIDE;

    //From QQmlParserStatus
    void classBegin() {}
    void componentComplete();

protected slots:
    void onAccessPointUpdate(const QString &point);

private:
    bool m_componentCompleted = false;
    QVariantList m_wifiAPs;
};

#endif // WIFIACCESSPOINTMODEL_H