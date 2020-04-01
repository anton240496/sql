#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include<QtSql/QSqlError>
#include<QtSql/QSqlRecord>

#include<QtSql/QSqlQuery>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    db = QSqlDatabase:: addDatabase("QPSQL");
    db.setHostName("127.0.0.1");
    db.setDatabaseName("postgres");
    db.setUserName("postgres");
    db.setPassword("vacada14");
    if (!db.open()){
        qDebug()<< db.lastError().text();
        return;

    }
    else {
        qDebug() << "Success!";
    }

    model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM auto");

    ui->primer->setModel(model);
    ui->primer->show();

}




void MainWindow::on_primer_clicked(const QModelIndex &index)
{
        int temp_non;
        temp_non = ui->primer->model()->data(ui->primer->model()->index(index.row(),0)).toInt();
        ui->line->setText(QString::number(temp_non));





        QSqlQuery* query = new QSqlQuery();
        query->prepare("SELECT num FROM auto WHERE id =id");
        query->bindValue("id", temp_non);


        if (query->exec()){
            query->next();
            ui->lineEdit->setText(query->value(0).toString());
        }
        }



MainWindow::~MainWindow()
{
    delete ui;
}




