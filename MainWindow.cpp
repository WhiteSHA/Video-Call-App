#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QMessageBox>
#include <QTimer>
#include <QCameraViewfinder>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    InitTimer();
}

void MainWindow::InitTimer()
{
    QTimer *tmr = new QTimer();
    connect(tmr, SIGNAL(timeout()), this, SLOT(InitUIAndMainCamera()));
    connect(tmr, SIGNAL(timeout()), tmr, SLOT(stop()));
    tmr->start(1000);
}

void MainWindow::InitUIAndMainCamera()
{
    QList<QCameraInfo> cameras = QCameraInfo::availableCameras();

    ui->comboBox->clear();
    QStringList itemsNames;
    for(int i = 0; i < cameras.count(); ++i)
    {
        itemsNames.append(cameras.at(i).description());
    }

    scene = new QGraphicsScene(ui->graphicsView->geometry().x(), ui->graphicsView->geometry().y(),
                               ui->graphicsView->geometry().width() - 10, ui->graphicsView->geometry().height() - 10);
    viewfinder = new QVideoWidget();
    ui->graphicsView->setScene(scene);
    scene->addWidget(viewfinder);
    ui->graphicsView->show();

    camera = new QCamera(cameras.at(0));

    camera->setViewfinder(viewfinder);
    camera->start();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_comboBox_currentIndexChanged(const QString &arg1)
{
    QList<QCameraInfo> cameras = QCameraInfo::availableCameras();
    for(int i = 0; i < cameras.count(); ++i)
    {
        if(cameras.at(i).description() == arg1)
        {
            camera->stop();
            delete camera;
            camera = new QCamera(cameras.at(i));
            camera->setCaptureMode(QCamera::CaptureVideo);
            camera->setViewfinder(viewfinder);
            camera->start();
        }
    }
}
