#include "childwindowtest.h"
#include "ui_childwindowtest.h"
#include <QDebug>

ChildWindowTest::ChildWindowTest(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChildWindowTest)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_DeleteOnClose); //关闭时自动删除
    //Qt::WindowFlags m_flags = windowFlags();
    //setWindowFlags(m_flags | Qt::WindowStaysOnTopHint);
    //show();
}

ChildWindowTest::~ChildWindowTest()
{
    qDebug() << "widget窗口关闭\n";
    delete ui;
}

void ChildWindowTest::paintEvent(QPaintEvent *event)
{
    qDebug()<<"ChildWindowTest paintEvent调用开始";
    qDebug()<<"ChildWindowTest paintEvent调用结束";
    return;
}

