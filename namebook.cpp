#include "namebook.h"
#include "ui_namebook.h"
#include "mainwindow.h"
#include <QFile>
#include <QString>
#include <QMessageBox>
#include <QPair>
#include <QFlag>
#include "mapmodel.h"
#include <QXmlStreamWriter>
#include <QFileDialog>

nameBook::nameBook(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::nameBook)
{
    ui->setupUi(this);

    QRegExp rx("[0-9A-Fa-f]{0,24}");
    validator = new QRegExpValidator(rx,this);
    ui->lineEdit->setValidator(validator);
    bookMap=new QMap<QString,QString>;


ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    connect(this,SIGNAL(sendNewElementSignal(QPair<QString,QString>)),this,SLOT(checkElement(QPair<QString,QString>)));

}

nameBook::~nameBook()
{
    delete ui;
}

void nameBook::addElementClicked()
{
QString id = ui->lineEdit->text();

if(id.length()==0)
  return;
else if(id.length()<24){
    ui->lineEdit->clear();
    ui->lineEdit_2->clear();
   QMessageBox::critical(0, "НЕВЕРНЫЙ ФОРМАТ", "ОШИБКА! Длина строки не меньше 24 символов. Формат - hex");
   return;}

id = id.toUpper();

QString name = ui->lineEdit_2->text();
QPair<QString,QString> addElement(id,name);
emit(sendNewElementSignal(addElement));
ui->lineEdit->clear();
ui->lineEdit_2->clear();

}

void nameBook::checkElement(QPair<QString,QString> newElement)
{
    if(bookMap->contains(newElement.first))
    {
        QMessageBox::critical(0, "ДУБЛИКАТ", "Элемент с данным идентификатором уже существует");
        return;
    }
    else
    {

        bookMap->insert(newElement.first,newElement.second);
        QMessageBox::information(0,"id added",newElement.first);

    }
    nmBookModel = new MapModel;

    nmBookModel->setMap(bookMap);
    ui->tableView->setModel(nmBookModel);

}

void nameBook::deleteButtonClicked()
{
   if(!bookMap->isEmpty())
   {


    QModelIndex index=ui->tableView->selectionModel()->currentIndex();
    int correction = 0;
    if(index.column()>0)
        correction = index.column()-1;
    QVariant value=index.sibling(index.row(),correction).data();

    QString id = value.toString();
    qDebug() << value;
    qDebug() << id;
    if(bookMap->find(id)!=bookMap->end())
    {
        bookMap->remove(id);

        ui->tableView->reset();

        nmBookModel = new MapModel;
        nmBookModel->setMap(bookMap);
        ui->tableView->setModel(nmBookModel);
    }

}
   qDebug() << "all right bookMap";
}






void nameBook::saveToFile()
{

    QString filename = QFileDialog::getSaveFileName(this,
                                           tr("Save Xml"), ".",
                                           tr("Xml files (*.xml)"));
     QString path;

    if(filename != ""){
        path = filename;
    }



       QFile file(path);
       file.open(QIODevice::WriteOnly);


       QXmlStreamWriter xmlWriter(&file);
       xmlWriter.setAutoFormatting(true);
       xmlWriter.writeStartDocument();
       xmlWriter.writeStartElement("nameBook");


       QMap<QString,QString>::iterator itB = bookMap->begin();
       while(itB!=bookMap->end())
       {
           xmlWriter.writeStartElement("item");
           xmlWriter.writeAttribute("id",
                                    (itB.key()));

           xmlWriter.writeCharacters(itB.value());
           xmlWriter.writeEndElement();
           ++itB;
       }






       xmlWriter.writeEndElement();

       xmlWriter.writeEndDocument();
       file.close();
   }


void nameBook::readFromFile()
{


        QString filename = QFileDialog::getOpenFileName(this);
//        ,
//                                                   tr("Open Xml"), ".",
//                                                   tr("Xml files (*.xml)")
        QString checkFileName;

        if(filename != ""){
           checkFileName = filename;
        }



    QFile file(checkFileName);
    if (!file.open(QFile::ReadOnly | QFile::Text))
    {
        QMessageBox::warning(this,
                             "Ошибка файла",
                             "Не удалось открыть файл",
                             QMessageBox::Ok);
    } else {

        if(!bookMap->isEmpty()){

    }







        QXmlStreamReader xmlReader;
        xmlReader.setDevice(&file);
        xmlReader.readNext();
        while(!xmlReader.atEnd())
        {

            QString attribute_value = 0;
            if(xmlReader.isStartElement())
            {

                if(xmlReader.name() == "item")
                {

                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes()) {

                        if (attr.name().toString() == "id") {
                            attribute_value = attr.value().toString();
                            qDebug() << attribute_value;
                                                }}
                    QString secondValue = xmlReader.readElementText();
                 bookMap->insert(attribute_value,secondValue);
                }
            }


            xmlReader.readNext();
        }


        file.close();
        QMap<QString,QString>::iterator itB = bookMap->begin();
while(itB!=bookMap->end())
{
    qDebug() << "bookmap is :";
    qDebug() << (itB).key() << (itB).value();
    ++itB;
}



nmBookModel = new MapModel;
nmBookModel->setMap(bookMap);
ui->tableView->setModel(nmBookModel);
    }



    }



