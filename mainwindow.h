#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "binary_tree_cmd.h"
#include "treepaint.h"
#include "childwindowtest.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
class QTreeView;//forward declarations
class QStandardItemModel;
class QStandardItem;
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_new_clicked();

    void on_pushButton_del_clicked();

    void on_pushButton_init_clicked();

private:
    Ui::MainWindow *ui;
    //QStandardItemModel *standardModel;
   // QList<QStandardItem *> prepareRow(const QString &first,
                                    //  const QString &second,
                                     // const QString &third) const;
    BinarySearchTree* bst;
    ChildWindowTest * cw;
};
#endif // MAINWINDOW_H
