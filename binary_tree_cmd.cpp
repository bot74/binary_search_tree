#include <iostream>
#include <QDebug>
#include "binary_tree_cmd.h"
using namespace std;
/***************************************************************************
  函数名称：FindMin
  功    能：寻找排序树中的最小值
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
BinarySearchTree* BinarySearchTree::FindMin(BinarySearchTree* BST)
{
    BinarySearchTree* cur = BST;
    if (!cur)
        return NULL;
    while (cur) {
        if (!cur->lchild)
            return cur;
        else
            cur = cur->lchild;
    }
    return cur;//消除“不是所有的控件路径都有返回值”warning
}
/***************************************************************************
  函数名称：FindMax
  功    能：寻找排序树中的最大值
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
BinarySearchTree* BinarySearchTree::FindMax(BinarySearchTree* BST)
{
    BinarySearchTree* cur = BST;
    if (!cur)
        return NULL;
    while (cur) {
        if (!cur->rchild)
            return cur;
        else
            cur = cur->rchild;
    }
    return cur;//消除“不是所有的控件路径都有返回值”warning
}
/***************************************************************************
  函数名称：Find
  功    能：根据用户给定的整型数据查找二叉树中第一个与之相等的结点地址
  输入参数：指向待查找的树的指针BinarySearchTree* BST，想要匹配的值int data
  返 回 值：指向匹配结点的指针，如果搜索不到结果或者初始给定的树空则返回NULL
  说    明：
***************************************************************************/
BinarySearchTree* BinarySearchTree::Find(BinarySearchTree* BST, int data)
{
    BinarySearchTree* cur = BST;
    // 搜索树如果为空则查找不到结果，返回NULL
    if (!cur) {
        return NULL;
    }
    while (cur) {
        if (cur->data == data)//根节点值与data相等则根节点即为所求
            return cur;
        else if (cur->data < data)//data>根节点，在右子树查找
            cur = cur->rchild;
        else
            cur = cur->lchild;//data<根节点，在左子树查找
    }
    return cur;//消除“不是所有的控件路径都有返回值”warning
}
/***************************************************************************
  函数名称：Insert
  功    能：将用户给定的int data插入到排序二叉树中,如果data已经在二叉树中有相等值
            匹配则不做额外处理,如果待插入二叉树为空树则构建根结点
  输入参数：待插入的排序二叉树BinarySearchTree* BST, 待插入的值data
  返 回 值：指向根节点的指针BinarySearchTree * BST
  说    明：
***************************************************************************/
BinarySearchTree* BinarySearchTree::Insert(BinarySearchTree* BST, int data)
{
    if (!BST) {
        BST = new BinarySearchTree;
        BST->data = data;
        BST->lchild = BST->rchild = NULL;
    }
    else {
        if (data < BST->data) {
            BST->lchild = BST->Insert(BST->lchild, data);
        }
        else if (data > BST->data) {
            BST->rchild = BST->Insert(BST->rchild, data);
        }
    }
    return BST;
}
/***************************************************************************
  函数名称：Create
  功    能：根据一个给定的数组data来构造初始二叉树
  输入参数：指向数组的指针int* data， 告知数组规模的数字int size
  返 回 值：指向构造完毕后的二叉树的指针BinarySearchTree* BST
  说    明：
***************************************************************************/
BinarySearchTree* BinarySearchTree::Create(int* data, int size)
{
    BinarySearchTree* BST = NULL;		//初始化根节点指针指向NULL防止野指针
    for (int i = 0; i < size; i++) {
        BST = this->Insert(BST, data[i]);	//循环读取data数组并插入到树中
    }
    return BST;
}
/***************************************************************************
  函数名称：PreorderTraversal
  功    能：前序遍历整个排序二叉树
  输入参数：待遍历的二叉树T
  返 回 值：void
  说    明：
***************************************************************************/
void BinarySearchTree::PreorderTraversal(BinarySearchTree* T)
{
    if (!T)							//树空直接退出
        return;
    qDebug() << T->data << " ";			//访问根节点
    T->PreorderTraversal(T->lchild);//访问左子树
    T->PreorderTraversal(T->rchild);//访问右子树
}
/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
void BinarySearchTree::InorderTraversal(BinarySearchTree* T)
{

}
/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
void BinarySearchTree::PostorderTraversal(BinarySearchTree* T)
{

}
/***************************************************************************
  函数名称：Delete
  功    能：	根据用户给定的值int data寻找在树BinarySearchTree* T中的相等结点a并删除
  输入参数：待查找的树BinarySearchTree* T，要删除的值int data
  返 回 值：
  说    明：
***************************************************************************/
BinarySearchTree* BinarySearchTree::Delete(BinarySearchTree* BST, int data)
{
    if (!BST)
        return BST;
    else if (data < BST->data) {
        //data小于根节点，需要去根节点的左子树寻找并删除
        BST->lchild = this->Delete(BST->lchild, data);
    }
    else if (data > BST->data) {
        //data大于根节点，需要去根节点的右子树寻找并删除
        BST->rchild = this->Delete(BST->rchild, data);
    }
    else {
        //data等于根节点，需要删除根节点，分两种情况
        //1.左右子树非空
        //2.左子树空或右子树空或者二者皆空
        if (BST->lchild&&BST->rchild) {
            //左右子树非空，则可以用右子树的最小值来代替根节点（也可以左子树最大，这里使用右子树最小）
            //首先建立tmp指针，tmp指向根节点中右子树最小值的节点
            //然后取出该节点的值，将根节点值修改为它
            //最后从右子树中删除这一最小值节点
            BinarySearchTree* tmp = this->FindMin(BST->rchild);
            BST->data = tmp->data;
            BST->rchild = this->Delete(BST->rchild, tmp->data);
        }
        else {
            //左右子树至少有一者为空树
            //新建一个临时指针用于指向当前根节点，之后原BST指针会指向删除后的结果，并返回，tmp则会被释放
            BinarySearchTree* tmp = BST;
            if (!BST->lchild) {
                //左子树为空，那么删除根节点后指向右子树即可
                BST = BST->rchild;
            }
            else if (!BST->rchild) {
                //右子树为空，那么删除根节点后指向右子树即可
                BST = BST->lchild;
            }
            //如果左右子树都为空，那么指向NULL，此时上述两个分支，走向左子树为空的分支，指向空的右子树，则指向NULL，不需要再写第三个else if语句了
            //也就是不需要再做特殊处理
            delete tmp;
        }
    }
    return BST;//消除“不是所有的控件路径都有返回值”warning
}
/***************************************************************************
  函数名称：getData
  功    能：返回节点值
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
int BinarySearchTree::GetData(BinarySearchTree* BST)
{
    if (BST)
        return BST->data;
    qDebug() << "NULL ERROR";
    return -1;
}
/***************************************************************************
  函数名称：GetHeight
  功    能：通过递归求解返回二叉树的高度或者说深度
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
int BinarySearchTree::GetHeight(BinarySearchTree* BST)
{
    int ans = 0;
    if (BST){
        int left = BST->GetHeight(BST->lchild);
        int right = BST->GetHeight(BST->rchild);
        ans = (left>right)?left:right;
        ans++;
    }
    return ans;
}
/***************************************************************************
  函数名称：Getlchild
  功    能：返回指向左孩子的指针
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
BinarySearchTree* BinarySearchTree::Getlchild(BinarySearchTree* BST)
{
    if (!BST)
        return NULL;
    return BST->lchild;
}
/***************************************************************************
  函数名称：Getrchild
  功    能：返回指向右孩子的指针
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
BinarySearchTree* BinarySearchTree::Getrchild(BinarySearchTree* BST)
{
    if (!BST)
        return NULL;
    return BST->rchild;
}
