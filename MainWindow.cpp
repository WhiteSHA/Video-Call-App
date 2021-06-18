#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QMessageBox>

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

void MainWindow::on_pushButton_clicked()
{
    QList<QCameraInfo> cameras = QCameraInfo::availableCameras();

    QMessageBox::warning(this, "count of avilable cameras", QString::number(cameras.count()));

    view = new QGraphicsView(this);
    view->setGeometry(50, 50, 700, 500);
    scene = new QGraphicsScene();
    widget = new QVideoWidget();
    view->setScene(scene);
    scene->addWidget(widget);
    view->show();

    ui->comboBox->clear();
    for(int i = 0; i < cameras.count(); ++i)
    {
        ui->comboBox->addItem(cameras.at(i).description());
    }

    camera = new QCamera(cameras.at(0));

    camera->setViewfinder(widget);
    camera->start();
}

void MainWindow::on_pushButton_2_clicked()
{
    view = new QGraphicsView();
    scene = new QGraphicsScene();
    widget = new QVideoWidget();
    view->setScene(scene);
    scene->addWidget(widget);
    view->show();

    if(QCamera::availableDevices().count() > 0)
    {
        camera = new QCamera(this);
        camera->setViewfinder(widget);
        camera->start();
    }
}

void MainWindow::on_pushButton_3_clicked()
{
    QList<QCameraInfo> cameras = QCameraInfo::availableCameras();
    for(int i = 0; i < cameras.count(); ++i)
    {
        if(cameras.at(i).description() == ui->comboBox->currentText())
        {
            camera->stop();
            camera = new QCamera(cameras.at(i));
            camera->setCaptureMode(QCamera::CaptureVideo);
            camera->setViewfinder(widget);
            camera->start();
        }
    }
}
