#include "TestWindow.h"
#include "ui_TestWindow.h"

#include <QMessageBox>
#include <QKeyEvent>
#include <QDebug>

TestWindow::TestWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TestWindow)
{
    ui->setupUi(this);
}

TestWindow::~TestWindow()
{
    delete ui;
}

bool TestWindow::event(QEvent *eve)
{
    //ui->label->setText(QString::number(eve->type()));
    qDebug() << __func__ << " " << __LINE__ << " event->text() = " << eve->type();

    return QWidget::event(eve);
}
