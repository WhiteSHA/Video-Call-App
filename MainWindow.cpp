#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QMessageBox>
#include <QTimer>
#include <QCameraViewfinder>
#include <QVBoxLayout>

#include <QAudioDeviceInfo>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    InitUi();

    InitTimer();

    InitAudioDevice();
}

void MainWindow::InitUi()
{
    QList<QCameraInfo> cameras = QCameraInfo::availableCameras();

    disconnect(ui->comboBox, SIGNAL(currentIndexChanged(QString)), this, SLOT(on_comboBox_currentIndexChanged(QString)));
    ui->comboBox->clear();
    for(int i = 0; i < cameras.count(); ++i)
        ui->comboBox->addItem(cameras.at(i).description());
    connect(ui->comboBox, SIGNAL(currentIndexChanged(QString)), this, SLOT(on_comboBox_currentIndexChanged(QString)));
}

void MainWindow::InitTimer()
{
    QTimer *tmr = new QTimer();
    connect(tmr, SIGNAL(timeout()), this, SLOT(InitMainCamera()));
    connect(tmr, SIGNAL(timeout()), tmr, SLOT(stop()));
    tmr->start(1000);
}

void MainWindow::InitMainCamera()
{
    viewfinder = new QVideoWidget();
    camera = new QCamera(QCameraInfo::defaultCamera());
    QVBoxLayout *lay = new QVBoxLayout(ui->widget);
    lay->addWidget(viewfinder);
    camera->setViewfinder(viewfinder);
    camera->start();
}

void MainWindow::InitAudioDevice()
{
    QList<QAudioDeviceInfo> microphones = QAudioDeviceInfo::availableDevices(QAudio::AudioInput);
    for(int i = 0; i < microphones.count(); ++i)
        ui->audioComboBox->addItem(microphones.at(i).deviceName());
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
            camera->setViewfinder(viewfinder);
            camera->start();
        }
    }
}
