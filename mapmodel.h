#ifndef MAPMODEL_H
#define MAPMODEL_H

#include <QAbstractTableModel>
#include <QMap>
//#include "mapmodel.h"
//#include "namebook.h"
//#include "mainwindow.h"
struct innerInfo;
class MapModel : public QAbstractTableModel
{
    Q_OBJECT
public:

    enum MapRoles {
        KeyRole = Qt::UserRole + 1,
        ValueRole
    };

    explicit MapModel(QObject *parent = 0);
    int rowCount(const QModelIndex& parent = QModelIndex()) const;
    int columnCount(const QModelIndex& parent = QModelIndex()) const;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;
    inline void setMap(QMap<QString,QString>* map) { _map = map; }
    //inline void setMap(QMap<QString,innerInfo>* map) { _map = map; }
    QVariant headerData(int, Qt::Orientation ,
                        int  ) const;

private:
    QMap<QString, QString>* _map;
};
#endif // MAPMODEL_H
