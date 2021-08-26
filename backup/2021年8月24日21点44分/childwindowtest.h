#ifndef CHILDWINDOWTEST_H
#define CHILDWINDOWTEST_H

#include <QWidget>

namespace Ui {
class ChildWindowTest;
}

class ChildWindowTest : public QWidget
{
    Q_OBJECT

public:
    explicit ChildWindowTest(QWidget *parent = nullptr);
    ~ChildWindowTest();

private:
    Ui::ChildWindowTest *ui;

protected:
   void paintEvent(QPaintEvent *event) override;
};

#endif // CHILDWINDOWTEST_H
