#include "mainwindow.h"
#include "ui_mainwindow.h"




MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked(bool)
{
    int i=0;
    QFile datos("/home/alse/Documents/Proyecto_Final/datos3.txt");
    if (!datos.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "Open Failed" << endl;
    }
    QTextStream txtInput (&datos);
    QString lineStr;
    while (!txtInput.atEnd())
    {
        lineStr = txtInput.readLine();
        qDebug() << lineStr << endl;
    }
    datos.close();

    QStringList datos_act;
    datos_act = lineStr.split(";");

    QStringList datos_r;
    QString datosD[5];
    for (i=0;i<(datos_act.size());i++){
        datos_r = datos_act[i].split(":");
        datosD[i] = datos_r[1];
    }
    float Datos_num[5];
    ui-> text_velocidad->setText(datosD[0]);
    ui-> text_frecuencia->setText(datosD[1]);
    ui-> text_voltaje->setText(datosD[2]);
    ui-> text_temperatura->setText(datosD[3]);
    datos_r = datosD[4].split("}");
    ui-> text_tiempo->setText(datos_r[0]);

    Datos_num[0]= datosD[0].toFloat();
    Datos_num[1]= datosD[1].toFloat();
    Datos_num[2]= datosD[2].toFloat();
    Datos_num[3]= datosD[3].toFloat();
    Datos_num[4]= datos_r[0].toFloat();

   if (Datos_num[0] > 1890 | Datos_num [0] < 1710){
       ui-> textBrowser_6 ->setText("Critico");
       QPalette est = ui -> textBrowser_6 -> palette();
       est.setColor(QPalette::Base, Qt::red);
       ui -> textBrowser_6 -> setPalette(est);
   }
   else {
       ui-> textBrowser_6 ->setText("Normal");
       QPalette est = ui -> textBrowser_6 -> palette();
       est.setColor(QPalette::Base, Qt::green);
       ui -> textBrowser_6 -> setPalette(est);
   }

   if (Datos_num[1] > 63 | Datos_num [1] < 57){
       ui-> textBrowser_7 ->setText("Critico");
       QPalette est = ui -> textBrowser_7 -> palette();
       est.setColor(QPalette::Base, Qt::red);
       ui -> textBrowser_7 -> setPalette(est);
   }
   else {
       ui-> textBrowser_7 ->setText("Normal");
       QPalette est = ui -> textBrowser_7 -> palette();
       est.setColor(QPalette::Base, Qt::green);
       ui -> textBrowser_7 -> setPalette(est);
   }

   if (Datos_num[2] > 231 | Datos_num [2] < 209){
       ui-> textBrowser_8 ->setText("Critico");
       QPalette est = ui -> textBrowser_8 -> palette();
       est.setColor(QPalette::Base, Qt::red);
       ui -> textBrowser_8 -> setPalette(est);
   }

   else {
       ui-> textBrowser_8 ->setText("Normal");
       QPalette est = ui -> textBrowser_8 -> palette();
       est.setColor(QPalette::Base, Qt::green);
       ui -> textBrowser_8 -> setPalette(est);
   }

   if (Datos_num[3] > 63 | Datos_num [3] < 57){
       ui-> textBrowser_9 ->setText("Critico");
       QPalette est = ui -> textBrowser_9 -> palette();
       est.setColor(QPalette::Base, Qt::red);
       ui -> textBrowser_9 -> setPalette(est);

   }
   else {
       ui-> textBrowser_9 ->setText("Normal");
       QPalette est = ui -> textBrowser_9 -> palette();
       est.setColor(QPalette::Base, Qt::green);
       ui -> textBrowser_9 -> setPalette(est);
   }

}

void MainWindow::on_tableWidget_cellActivated(int, int)
{

}



QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");

void MainWindow::on_pushButton_2_clicked(bool)
{
    db.setDatabaseName("/home/alse/Documents/testdatabase2.db");

    if (!db.open())
    {
        qDebug() << db.lastError();
        qFatal ("Conexion fallida a la base de datos");
    }

    QSqlQuery query;
    query.prepare("CREATE TABLE tabla1 (id INTEGER PRIMARY KEY, col1 VARCHAR(20) NOT NULL, col2 INTEGER)");
    query.exec();
    QString query_to_insert = "INSERT INTO tabla1 VALUES (" + ui->lineEdit->text() + ", 'valor col 1', 3)";
    query.prepare(query_to_insert);
    if (!query.exec())
        qDebug() << query.lastError();
    db.close();
}
