#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    server = new QTcpServer(this);
    connect(server,SIGNAL(newConnection()),this,SLOT(newConnection()));
    if (!server->listen(QHostAddress::Any,1234))
    {
        ui->textEdit->append("Cannot connect to server!");
    }
    else
    {
        ui->textEdit->append("Server started!");
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::newConnection()
{
    socket = server->nextPendingConnection();
    socket->waitForReadyRead(3000);
    ui->textEdit->append(socket->readAll());
    socket->write("Server: Hello client!");
    socket->flush();
    socket->waitForBytesWritten(3000);
    socket->close();
}

void MainWindow::on_pushButtonSend_clicked()
{
    QString msg = ui->lineEditSend->text();
    socket->write("Hello");
}
