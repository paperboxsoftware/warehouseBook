#ifndef NAMEBOOK_H
#define NAMEBOOK_H
//#include "mainwindow.h"
#include <QWidget>
#include <QValidator>
#include <QtXml/QDomComment>
#include <QtXml/QtXml>
#include <QMap>
#include "mapmodel.h"
#include "innerinfo.h"
namespace Ui {
class nameBook;
}

class nameBook : public QWidget
{
    Q_OBJECT
friend class MainWindow;
public:
    explicit nameBook(QWidget *parent = 0);
    ~nameBook();
public slots:
    void addElementClicked();
    void checkElement(QPair<QString,QString>);
    void deleteButtonClicked();

    void saveToFile();
    void readFromFile();

signals:
    void sendNewElementSignal(QPair<QString,QString>);
private:
    Ui::nameBook *ui;
    QDomDocument* xmlBook;
    QValidator* validator;
protected:
    QMap<QString,QString>* bookMap;
public:
    MapModel* nmBookModel;
};



#endif // NAMEBOOK_H
