#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVideoWidget>
#include <QCameraInfo>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void InitTimer();

private slots:
    void on_comboBox_currentIndexChanged(const QString &arg1);

    void InitMainCamera();

    void InitUi();

    void InitAudioDevice();

private:
    Ui::MainWindow *ui;

    QVideoWidget *viewfinder;
    QCamera *camera;
};
#endif // MAINWINDOW_H
