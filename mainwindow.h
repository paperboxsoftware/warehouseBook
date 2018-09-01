#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QValidator>

#include "mapmodel2.h"
#include "namebook.h"
#include "mapmodel.h"


#include <QMap>

struct element;
struct innerInfo;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
public slots:
    void nameBook_clicked();

    void checkId2(QString& id);
    void checkIdReceive(QString& id);
    void lineEditPressed();
    void lineEdit2Pressed();
    void cleanButtonClicked();


     void addToShippingMapSlot2(QString id, innerInfo info);
     void addToReceiveMapSlot(QString id, innerInfo info);
     void closeProgram();
signals:
    QString addToMapSignal(QString);
    void addToMapSignal2(QString,innerInfo);
    void addToReceiveMapSignal(QString,innerInfo);
    void closeSignal();


private:
    Ui::MainWindow *ui;
    QValidator* validator;
    nameBook* nBook;
    QMap<QString,int>* shipmentMap;
    QMap<QString,int>* receiveMap;

    QMap<QString,innerInfo>* shipmentSuperMap;
    QMap<QString,innerInfo>* table2Map;



    MapModel2* shipmentModel;
    MapModel2* receiveModel;
};

struct element{
    QString _id;
    QString _name;
    std::size_t _quantity;
};



#endif // MAINWINDOW_H
