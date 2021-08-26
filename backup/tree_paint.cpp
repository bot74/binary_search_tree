#include "tree_paint.h"
#include <QPainter>
#include <QIcon>

struct tNode
{
    BinarySearchTree* treeNode;
    int layer;  //标记节点属于第几层
};

TreePaint::TreePaint(QWidget* parent):QWidget(parent)
{
    qDebug() << "TreePaint初始化函数调用开始";
    resize(600, 400);//num to be edit
    setWindowTitle("排序二叉树绘制结果");
    qDebug() << "TreePaint初始化函数调用结束";
}
bool TreePaint::SetTree(BinarySearchTree* t)
{
    qDebug() << "SetTree初始化函数调用开始";
    if (t){
        this->BST = t;
        return true;
    }
    return false;
}
void TreePaint::paintEvent(QPaintEvent *event)
{
    qDebug() << "paintEvent开始执行";
    QPainter painter(this);//创建QPainter对象
    //设置反锯齿
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::TextAntialiasing);
    //背景图
    //painter.drawPixmap(rect(),QPixmap("://image/600_400.jpg"));
    //设置字体
    QFont font;
    font.setPointSize(12);
    font.setBold(true);
    painter.setFont(font);
    //设置画笔
    QPen penLine;
    penLine.setWidth(2);//线宽
    penLine.setColor(Qt::blue);
    penLine.setStyle(Qt::SolidLine);
    penLine.setCapStyle(Qt::FlatCap);
    penLine.setJoinStyle(Qt::BevelJoin);
    painter.setPen(penLine);

    qreal W = this->width();    //画布宽度
    qreal H = this->height();   //画布高度
    int treeHeight = BST->GetHeight(BST);//树的高度
    qreal R = W / (2*std::pow(2, treeHeight) + 2);//节点半径
    const int layerHeight = (H-4*R)/(treeHeight-1);//层高，垂直偏移量

    QRectF node(QPointF(-R, -R), QPointF(R,R));
    MyStack<tNode> stack;//存放右孩子节点
    tNode qNode;

    MyStack<QPointF> points;    //存放右孩子节点相对于当前坐标系统原点的位置
    QPointF point;

    qreal Hoffset;  //水平偏移量
    BinarySearchTree* t = BST;  //getRoot();
    const qreal Pi = 3.14159;
    int curLayer = 1;
    int curAngle;
    qreal deg;

    //将坐标系统的原点（下称原点）移动到初始位置
    painter.translate(W/2,2*R);

    while(1){
        painter.drawEllipse(node);
        painter.drawText(node,Qt::AlignHCenter, QChar(t->GetData(t)));

        //设置孩子节点相对父节点的水平偏移量
        Hoffset = std::pow(2,(treeHeight-curLayer))*R;
        deg = std::atan(Hoffset/layerHeight);
        curAngle = 190 / Pi * deg;

        if (t->Getlchild(t) != NULL){
            //坐标轴逆时针旋转
            painter.rotate(-curAngle);

            //绘制图形行路经
            painter.drawLine(0,R,0,layerHeight/std::cos(deg));

            //旋转复原
            painter.rotate(curAngle);

            //右孩子节点压栈
            qNode.treeNode=t->Getrchild(t);
            qNode.layer=curLayer+1;
            stack.push(qNode);

            //右孩子相对于当前坐标系统原点的位置压栈
            points.push(QPointF(QPointF(0,0) + QPointF(Hoffset, layerHeight)));
            painter.save();
        }
        if (t->Getlchild(t) != NULL){
            //坐标轴顺时针旋转
            painter.rotate(curAngle);
            //绘制边
            painter.drawLine(0,R,0,layerHeight/std::cos(deg) - R);
            //旋转复原
            painter.rotate(-curAngle);
            //原点移动到左孩子节点的位置

            painter.translate(QPointF(QPointF(0,0) + QPointF(-Hoffset, layerHeight)));
            t=t->Getlchild(t);//层次+1
            curLayer++;
        }
        else{
            /*try {
                //获取到右节点的层次状态
                qNode = stack.pop();
                t=qNode.treeNode;
                curLayer=qNode.layer;

                //原点移动到右孩子节点的位置
                painter.restore();
                point = points.pop();
                painter.translate(point);
            }  catch (stackEmptyException) {
                painter.resetTransform();
                return;*/
            if (stack.isEmpty()){
                painter.resetTransform();
                return;
            }
            else{
                //获取到右节点的层次状态
                qNode = stack.pop();
                t=qNode.treeNode;
                curLayer=qNode.layer;

                //原点移动到右孩子节点的位置
                painter.restore();
                point = points.pop();
                painter.translate(point);
            }
        }
    }


    qDebug() << "paintEvent执行完毕";
}
