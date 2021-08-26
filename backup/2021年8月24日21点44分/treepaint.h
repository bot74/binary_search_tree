#ifndef TREEPAINT_H
#define TREEPAINT_H

#include <QWidget>
#include <QPaintEvent>
#include "binary_tree_cmd.h"
#include "template_stack.h"

namespace Ui {
class TreePaint;
}

class TreePaint : public QWidget
{
    Q_OBJECT

public:
    explicit TreePaint(QWidget *parent = nullptr);
    bool SetTree(BinarySearchTree*);
    ~TreePaint();
protected:
    void paintEvent(QPaintEvent *event) override;
private:
    Ui::TreePaint *ui;
    BinarySearchTree* BST;
};

#endif // TREEPAINT_H
