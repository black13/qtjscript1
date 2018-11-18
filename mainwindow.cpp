#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtWidgets/QFileDialog>
#include <QTextStream>
#include <qqmlengine.h>
#include <QDebug>
#include <QDate>
#include <qjsengine.h>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //connect(ui->pushButton, SIGNAL(clicked()), this, SIGNAL(on_button_click()));
    QObject::connect(ui->pushButton, &QPushButton::clicked,this, &MainWindow::onbuttonclick);
    eng.globalObject().setProperty("application", eng.newQObject(this));

    QQmlEngine::setObjectOwnership(this, QQmlEngine::CppOwnership);

 
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::onbuttonclick()
{
    //eng.evaluate("application.callfromscript()");
    
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                 QDir::currentPath(),
                                                tr("*.qs"));

    
    QFile scriptFile(fileName);
    if (scriptFile.open(QIODevice::ReadOnly))
    {
        QTextStream stream(&scriptFile);
        QString contents = stream.readAll();
        scriptFile.close();
        eng.evaluate(contents, fileName);  
                                                     
    }
        // handle error
}


void MainWindow::callfromscript()
{
     qDebug() << "Date:" << QDate::currentDate();
}