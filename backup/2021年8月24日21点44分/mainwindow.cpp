#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QWidget>

#include <QStandardItem>
#include <QStandardItemModel>
#include <QItemSelectionModel>
#include <QTreeView>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    //, ui->treeView(new QTreeView(this))
    //, standardModel(new QStandardItemModel(this))
{
    //ui settings
    ui->setupUi(this);
    ui->lineEdit_new->setValidator(new QDoubleValidator(this));
    ui->lineEdit_del->setValidator(new QDoubleValidator(this));
    /*//model settings
    QList<QStandardItem *> preparedRow = prepareRow("first", "second", "third");

    QStandardItem *item = standardModel->invisibleRootItem();
    // adding a row to the invisible root item produces a root element
    item->appendRow(preparedRow);

    QList<QStandardItem *> secondRow = prepareRow("111", "222", "333");
    // adding a row to an item starts a subtree
    preparedRow.first()->appendRow(secondRow);

    ui->treeView->setModel(standardModel);
    ui->treeView->expandAll();*/
}

/*填充QList
QList<QStandardItem *> MainWindow::prepareRow(const QString &first,
                                              const QString &second,
                                              const QString &third) const
{
    return {new QStandardItem(first),
            new QStandardItem(second),
            new QStandardItem(third)};
}*/

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_new_clicked()
{
    //在ui中已经调用了setValidator来确保输入是数字，所以必定合法，原先的非法提示可以不用
    /*
    QMessageBox msgBox(QMessageBox::Icon::Critical,     //图标
                       "错误",                        //标题
                       "输入非法",                      //内容
                       QMessageBox::Ok,                 //按钮
                       this);                           //停靠父窗口
    //显示消息窗口
    msgBox.exec();
    */
    double num = ui->lineEdit_new->text().toDouble();//获取数字
    bst->Insert(bst,num);
    bst->PreorderTraversal(bst);                        //目前先序遍历会调用qDebug输出调试信息
    ui->lineEdit_new->clear();                      //读入完毕，清空输入条

    cw = new ChildWindowTest();
    cw->show();
    //this->hide();

    QMessageBox msgBox(QMessageBox::Icon::Information,     //图标
                       "成功",                        //标题
                       "已将节点添加到树中",                      //内容
                       QMessageBox::Ok,                 //按钮
                       this);                           //停靠父窗口
    //显示消息窗口
    msgBox.exec();
}

//在点击删除按钮以后，查找并删除对应节点，如果存在则删除并返回成功信息，否则返回失败信息
//目前未完成，只会提示成功
void MainWindow::on_pushButton_del_clicked()
{
    /*
    QMessageBox msgBox(QMessageBox::Icon::Critical,     //图标
                       "错误",                        //标题
                       "输入非法",                      //内容
                       QMessageBox::Ok,                 //按钮
                       this);                           //停靠父窗口
    //显示消息窗口
    msgBox.exec();
    */
    double num = ui->lineEdit_del->text().toDouble();//获取数字
    bst = bst->Delete(bst, num);//删除节点
    bst->PreorderTraversal(bst);                        //目前先序遍历会调用qDebug输出调试信息
    ui->lineEdit_del->clear();
    QMessageBox msgBox(QMessageBox::Icon::Information,     //图标
                       "成功",                        //标题
                       "已将节点从树中删除",                      //内容
                       QMessageBox::Ok,                 //按钮
                       this);                           //停靠父窗口
    //显示消息窗口
    msgBox.exec();
}



void MainWindow::on_pushButton_init_clicked()
{
    QString init_str = ui->lineEdit_init->text();//从初始化输入框中读取字符串
    QStringList list1 = init_str.split(" ");//我们规定分隔符为空格，将用户的排序二叉树初始值拆分到列表中

    int* data;                              //接下来就和cmd的操作接轨，先初始化动态数组
    int size = list1.size();                //获取节点个数
    data = new int [size];
    for (int i = 0; i < list1.size(); ++i)
         data[i] = list1.at(i).toDouble();  //将列表中的数据读入到数组中
    if (bst)
        bst->~BinarySearchTree();
    bst = new BinarySearchTree;
    bst = bst->Create(data, size);
    ui->lineEdit_init->clear();
    QMessageBox msgBox(QMessageBox::Icon::Information,     //图标
                       "成功",                        //标题
                       "已根据初始化序列初始化排序二叉树",                      //内容
                       QMessageBox::Ok,                 //按钮
                       this);                           //停靠父窗口
    bst->PreorderTraversal(bst);                        //目前先序遍历会调用qDebug输出调试信息
    msgBox.exec();//显示消息窗口

    TreePaint* p = new TreePaint();
    if (p->SetTree(bst)){
        p->show();  //显示绘制结果
        //this->hide();   //隐藏主界面
    }
    //delete p;   //回到主界面后释放绘画占用的动态内存
    delete[] data;    //初始化二叉树以后，将临时使用的data数组占用的动态内存释放，防止内存泄漏

}

