#ifndef TREE_PAINT_H
#define TREE_PAINT_H
#include "binary_tree_cmd.h"
#include "template_stack.h"
#include <QPaintEvent>
#include <QWidget>
class TreePaint : public QWidget
{
public:
    explicit TreePaint(QWidget* parent = 0);//指定构造函数为显式
    bool SetTree(BinarySearchTree*);
protected:
    void paintEvent(QPaintEvent *event) override;
private:
    BinarySearchTree* BST;
};
#endif // TREE_PAINT_H
