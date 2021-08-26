#include "treepaint.h"
#include "ui_treepaint.h"
#include <QPainter>
#include <QIcon>

struct tNode
{
    BinarySearchTree* treeNode;
    int layer;  //标记节点属于第几层
};

TreePaint::TreePaint(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TreePaint)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_DeleteOnClose);
}

TreePaint::~TreePaint()
{
    delete ui;
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
    painter.drawPixmap(rect(),QPixmap("://image/600_400.jpg"));
    //设置字体会导致运行时错误
    QFont font;
    font.setFamily("Microsoft YaHei");  //设置字体
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

    //已知画布宽度，假设按照叶子节点用半径为R的圆画出，且叶子与叶子间隔一个叶子的宽度，并且与窗口左右边界各间隔一个叶子宽度
    //已知二叉树的高度，可以知道对应的形态下最底层需要多少个叶子宽度
    //联立就可以求解我们应该设置的节点半径R，也就是qreal R的值
    //同样已知画布高度，假设树图和窗口上下边界各间隔一个叶子高度，那么可供树图使用的高度是窗口高度减去4R
    //用这一高度除去树的层数，就可以知道每一层占用的高度，即层高，或者说垂直偏移量，用layerHeight表示
    //对于水平偏移量，观察可知，底层叶子节点圆心与上一层父节点圆心水平位置相比增加或减少了R+R（左孩子减少2R,右孩子增加2R）
    //而倒数第二层与倒数第三层相比，这个偏移量变为2R+2R即4R
    //依次类推，往上一层则偏移量翻倍，2R,4R,8R,16R.......
    //已知父节点圆心坐标和孩子节点的水平、垂直偏移量，可以确定孩子节点的圆心坐标，从而绘制节点图形，并在图形中心绘制节点数据int data
    qreal W = this->width();    //画布宽度
    qreal H = this->height();   //画布高度
    int treeHeight = BST->GetHeight(BST);//树的高度
    qreal R = W / (2*std::pow(2, treeHeight) + 2);//节点半径
    const int layerHeight = (H-4*R)/(treeHeight-1);//层高，垂直偏移量

    //QPointF是Qt中用于表示一个点坐标的数据类型，坐标用两个实数表示
    //QRectF是Qt中用于表示一个矩形区域的数据类型，可以用两个QPointF来组合
    //node为节点形状区域限制，由于我们的绘制方法是原点每次都会更新为待绘制节点的圆心，
    //所以使用(-R,R)到(R,R)的范围来作为圆形绘制的限制矩形
    QRectF node(QPointF(-R, -R), QPointF(R,R));
    //tNode结构体包括一个指向BinarySearchTree的指针treeNode
    //以及一个指示该节点在自己树中位于第几层的int变量layer
    //定义根节点层数为1
    //那么举例，根节点的右孩子节点就位于第二层，layer=2
    //为了绘制树形图，采取前序非递归遍历的方法，使用自定义栈MyStack
    MyStack<tNode> stack;//存放右孩子节点
    tNode qNode;

    //QPointF是Qt中用于表示一个点坐标的数据类型，坐标用两个实数表示
    MyStack<QPointF> points;    //存放右孩子节点相对于当前坐标系统原点的位置
    QPointF point;

    qreal Hoffset;  //水平偏移量
    BinarySearchTree* t = BST;  //getRoot();这一行感觉有问题
    const qreal Pi = 3.14159;   //定义常量Pi用于绘制圆形
    int curLayer = 1;//初始化当前层数为1，从第一层根节点开始绘制图形
    int curAngle;
    qreal deg;

    //将坐标系统的原点（下称原点）移动到初始位置，这里是窗口中心距离上边框一个叶子节点高度的地方
    painter.translate(W/2,2*R);

    while(1){
        //qDebug()<<"循环中";
        if (t){ //如果根节点非空，绘制圆形
            qDebug()<<t->GetData(t);
            painter.drawEllipse(node);//绘制节点圆形
            //painter.drawText(node,Qt::AlignHCenter, QString(QChar(t->GetData(t))));  //这句话引发了字体错误？在节点中绘制数据
            //painter.drawText(node,Qt::AlignHCenter, "test");
            //在节点中心绘制数据，我们的树使用的关键字数据类型是data，int data
            //为了使用drawText函数，我们要将int data转换成QString类型，这里调用QString::number函数，其默认进制为十进制
            //drawText函数的第一个参数是绘制区域，同样使用node即可
            //drawText函数的第二个参数是对齐位置，这里使用水平中心和垂直中心对齐，这个参数可以用or运算符来连接多个flags
            //这里的AlignHCenter就是水平中心对齐的flags
            //AlignHCenter | AlignVCenter 就是同时使用了两个flags，水平中心和垂直中心对齐
            painter.drawText(node, Qt::AlignHCenter | Qt::AlignVCenter, QString::number((t->GetData(t))));
            //painter.drawText(node, Qt::AlignHCenter | Qt::AlignVCenter, QString::number(1,10));
        }

        //设置孩子节点相对父节点的水平偏移量
        //例如树高为3，正在绘制第一层，第二层相对第一层的水平偏移量就是(3-1)^2 * R = 4R
        Hoffset = std::pow(2,(treeHeight-curLayer))*R;
        deg = std::atan(Hoffset / layerHeight); //返回了弧度
        curAngle = 180 / Pi * deg;              //转换成角度

        if (t->Getlchild(t) != NULL){   //若左孩子非空，绘制根节点连向左孩子的连线
            //坐标轴逆时针旋转
            painter.rotate(-curAngle);

            //绘制图形行路经
            painter.drawLine(0,R,0,layerHeight/std::cos(deg));

            //旋转复原
            painter.rotate(curAngle);

            //如果有右孩子
            if (t->Getrchild(t)){
                //右孩子节点数据与层数入stack栈
                qNode.treeNode=t->Getrchild(t);
                qNode.layer=curLayer+1;
                stack.push(qNode);
                //右孩子相对于当前坐标系统原点的位置入points栈
                points.push(QPointF(QPointF(0,0) + QPointF(Hoffset, layerHeight)));
                painter.save();//绘制右孩子之前的原点
            }
        }//if (t->Getlchild(t) != NULL) ends here
        if (t->Getrchild(t) != NULL){   //若右孩子非空，绘制根节点连向右孩子的连线
            //坐标轴顺时针旋转
            painter.rotate(curAngle);
            //绘制边
            painter.drawLine(0,R,0,layerHeight/std::cos(deg) - R);
            //旋转复原
            painter.rotate(-curAngle);

            //原点移动到左孩子节点的位置
            painter.translate(QPointF(QPointF(0,0) + QPointF(-Hoffset, layerHeight)));
            t=t->Getlchild(t);//准备前往绘制左孩子节点
            curLayer++;//本层已经绘制完毕，前往下一层，下一个循环迭代开始
        }//if (t->Getrchild(t) != NULL) ends here
        else{
            //右孩子为空
            //if (stack.isEmpty()) ———— 判断整棵树是否绘制完毕，如果完毕退出
            //否则
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
            if (stack.isEmpty() && t->Getlchild(t) == NULL){
                painter.resetTransform();
                return;
            }
            else if (!stack.isEmpty()){//如果有右子树，绘制右子树
                //获取到右节点的层次状态
                qNode = stack.pop();
                t=qNode.treeNode;
                curLayer=qNode.layer;

                //原点移动到右孩子节点的位置，首先让原点restore()回到右孩子的父节点圆心，再从points栈中取出偏移量，并移动原点到右孩子圆心
                painter.restore();
                point = points.pop();
                painter.translate(point);
            }
            else{

            }
        }
    }


    qDebug() << "paintEvent执行完毕";
}
