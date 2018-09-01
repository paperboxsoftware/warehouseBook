#ifndef MAPMODEL2_H
#define MAPMODEL2_H

#include <QAbstractTableModel>
#include <QMap>
#include "mapmodel.h"
#include "namebook.h"
#include "innerinfo.h"
class MapModel2 : public QAbstractTableModel
{
    Q_OBJECT
public:

    enum MapRoles {
        KeyRole = Qt::UserRole + 1,
        ValueRole
    };

    explicit MapModel2(QObject *parent = 0);
    int rowCount(const QModelIndex& parent = QModelIndex()) const;
    int columnCount(const QModelIndex& parent = QModelIndex()) const;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;
    //inline void setMap(QMap<QString,QString>* map) { _map = map; }
    inline void setMap(QMap<QString,innerInfo>* map) { _map = map; }
    QVariant headerData(int, Qt::Orientation ,
                        int  ) const;

private:
    QMap<QString, innerInfo>* _map;
};
#endif // MAPMODEL2_H
