#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "namebook.h"
#include <QMessageBox>
#include "mapmodel.h"
#include <QVector>
#include "mapmodel2.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    nBook = new nameBook();
    shipmentMap = new QMap<QString,int>;
    receiveMap = new QMap<QString,int>;

   shipmentSuperMap = new QMap<QString,innerInfo>;
   table2Map = new QMap<QString,innerInfo>;


    QRegExp rx("[0-9A-Fa-f]{0,24}");
    validator = new QRegExpValidator(rx,this);
    ui->lineEdit->setValidator(validator);
    ui->lineEdit_2->setValidator(validator);

    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView_2->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);


    connect(this,SIGNAL(addToMapSignal2(QString,innerInfo)),this,SLOT(addToShippingMapSlot2(QString,innerInfo)));
    connect(this,SIGNAL(addToReceiveMapSignal(QString,innerInfo)),this,SLOT(addToReceiveMapSlot(QString,innerInfo)));
    connect(this,SIGNAL(closeSignal()),nBook,SLOT(close()));


}

MainWindow::~MainWindow()
{
    delete ui;
}

void  MainWindow::nameBook_clicked()
{
   if(nBook->isVisible())
   {nBook->raise();
   nBook->activateWindow();}
   else
    nBook->show();


}



void MainWindow::addToShippingMapSlot2(QString id, innerInfo info)
{
    if(shipmentSuperMap->find(id)!=shipmentSuperMap->end())
    {

        ++(*shipmentSuperMap)[id];

        qDebug() << "shipmentMap counter: " << (*shipmentSuperMap)[id];

    }
    else{

        shipmentSuperMap->insert(id,info);

        }

    if(table2Map->find(id)!=table2Map->end())
    {
        qDebug() << "table2Map element counter: " << (*table2Map)[id];
        int x =1;
        if((*table2Map)[id]>x)
            --(*table2Map)[id];
        else table2Map->remove(id);
        receiveModel = new MapModel2;

        receiveModel->setMap(table2Map);
        ui->tableView_2->setModel(receiveModel);

    }

    shipmentModel = new MapModel2;
    shipmentModel->setMap(shipmentSuperMap);
    ui->tableView->setModel(shipmentModel);


}

void MainWindow::addToReceiveMapSlot(QString id, innerInfo info)
{
    if(table2Map->find(id)!=table2Map->end())
    {

        ++(*table2Map)[id];

        qDebug() << "ReceiveMap counter: " << (*table2Map)[id];
    }
    else{
              table2Map->insert(id,info);
        }

    if(shipmentSuperMap->find(id)!=shipmentSuperMap->end())
    {
        qDebug() << "shipmentSuperMap element counter: " << (*shipmentSuperMap)[id];
        int x =1;
        if((*shipmentSuperMap)[id]>x)
            --(*shipmentSuperMap)[id];

        else shipmentSuperMap->remove(id);

        shipmentModel = new MapModel2;
        shipmentModel->setMap(shipmentSuperMap);
        ui->tableView->setModel(shipmentModel);

    }

    receiveModel = new MapModel2;
    receiveModel->setMap(table2Map);
    ui->tableView_2->setModel(receiveModel);



}

void MainWindow::lineEditPressed()
{
    QString id = ui->lineEdit->text();
    if(id.length()==0)
    { qDebug() << "is string receive empty: " << id.isEmpty();
        QMessageBox::critical(0, "НЕВЕРНЫЙ ФОРМАТ", "ОШИБКА! Длина строки не меньше 24 символов. Формат - hex");
        return;
    }

    else if(id.length()<24){
        qDebug() << "string receive length: " << id.length();
       QMessageBox::critical(0, "НЕВЕРНЫЙ ФОРМАТ", "ОШИБКА! Длина строки не меньше 24 символов. Формат - hex");
        ui->lineEdit->clear();

       return;
    }

    id = id.toUpper();


    emit(checkId2(id));
  }



void MainWindow::lineEdit2Pressed()
{
 QString id = ui->lineEdit_2->text();
 if(id.length()==0)
 { qDebug() << "is string receive empty: " << id.isEmpty();
     QMessageBox::critical(0, "НЕВЕРНЫЙ ФОРМАТ", "ОШИБКА! Длина строки не меньше 24 символов. Формат - hex");
     return;
 }

 else if(id.length()<24){
     qDebug() << "string receive length: " << id.length();
    QMessageBox::critical(0, "НЕВЕРНЫЙ ФОРМАТ", "ОШИБКА! Длина строки не меньше 24 символов. Формат - hex");
     ui->lineEdit_2->clear();

    return;
 }

 id = id.toUpper();


 emit(checkIdReceive(id));

}

void MainWindow::checkId2(QString& id)
{

    if(nBook->bookMap->contains(id))
    {

        innerInfo subjInfo;

        subjInfo._name = nBook->bookMap->value(id);
        subjInfo._quantity = 1;
        emit(addToMapSignal2(id,subjInfo));
    }
    else{
        QMessageBox::critical(0, "id не найден", "Данный идентификатор отсутствует в справочнике");
    }

}

void MainWindow::checkIdReceive(QString& id)
{

    if(nBook->bookMap->contains(id))
    {

        innerInfo subjInfo;

        subjInfo._name = nBook->bookMap->value(id);
        subjInfo._quantity = 1;
        emit(addToReceiveMapSignal(id,subjInfo));
    }
    else{
        QMessageBox::critical(0, "id не найден", "Данный идентификатор отсутствует в справочнике");
    }

}

void MainWindow::cleanButtonClicked()
{
ui->lineEdit->clear();
ui->lineEdit_2->clear();


    if(!(shipmentSuperMap->isEmpty() && table2Map->isEmpty())){
    qDebug() << "clean button pressed";
   shipmentSuperMap->clear();
   table2Map->clear();
   qDebug() << table2Map->isEmpty();
   ui->tableView->reset();
   ui->tableView_2->reset();
   ui->tableView->repaint();
   ui->tableView_2->repaint();

   ui->tableView->clearSpans();



   receiveModel->setMap(table2Map);
   shipmentModel->setMap(shipmentSuperMap);

ui->tableView_2->setModel(receiveModel);
   ui->tableView->setModel(shipmentModel);}
    else
        qDebug() << "all right";

}

 void MainWindow::closeProgram()
 {
     emit(closeSignal());
 }
