#ifndef TEMPLATE_STACK_H
#define TEMPLATE_STACK_H
#include <iostream>
#include <exception>
using namespace std;
//自定义异常stackEmptyExcpetion以及stackFullException
/*
class stackEmptyException: public exception
{
    virtual const char* emptyPrompt() const throw()
    {
        return "自定义栈空";
    }
};
class stackFullException: public exception
{
    virtual const char* emptyPrompt() const throw()
    {
        return "自定义栈满";
    }
};
extern stackEmptyException stackEmpty;  //声明
extern stackFullException stackFull;*/
template<typename T>
struct stackNode
{
	T data;//存储的具体元素
	stackNode* next;
};
template<typename T>
class MyStack
{
private:
	unsigned int count;	//当前stack中元素个数
	unsigned int maxSize;//stack最大存储的元素个数
	stackNode<T>* top;//stack头结点的指针
public:
	MyStack();
	MyStack(unsigned int num);
	~MyStack();
	int push(T data);
    T pop(void);
	T getTop(void);
	bool isEmpty(void);
	bool isFull(void);
};
template<typename T>
MyStack<T>::MyStack()
{
	count = 0;
	maxSize = 10;
	top = NULL;
}
template<typename T>
MyStack<T>::MyStack(unsigned int num)
{
	count = 0;
	maxSize = num;
	top = NULL;
}
template<typename T>
MyStack<T>::~MyStack()
{
	stackNode<T>* p = new stackNode<T>;
	for (unsigned int i = count; i > 0; i--) {
		p = top;
		top = p->next;
		delete p;
	}
}
template<typename T>
int MyStack<T>::push(T data)
{
	count++;
	if (isFull()) {
		cout << "错误：栈溢出" << endl;
		cout << "文件路径=" << __FILE__ << endl;
		cout << "函数名=" << __FUNCTION__ << endl;
		cout << "行=" << __LINE__ << endl;
		return 1;
	}
	stackNode<T>* node = new stackNode<T>;
	node->data = data;
	node->next = top;
	top = node;
	return 0;
}
template<typename T>
T MyStack<T>::pop()
{
	if (isEmpty()) {
		cout << "错误：栈空" << endl;
		cout << "文件路径=" << __FILE__ << endl;
		cout << "函数名=" << __FUNCTION__ << endl;
		cout << "行=" << __LINE__ << endl;
        //return 1;
	}
	stackNode<T>* p = top;
    T tmp = p->data;  //取值临时存储到tmp中
	top = top->next;
	delete p;
	count--;
    return tmp; //返回取出的值
}
template<typename T>
T MyStack<T>::getTop(void)
{
	return top->data;
}
template<typename T>
bool MyStack<T>::isFull(void)
{
    //if (count > maxSize)
      //  throw stackFull;
    return (count > maxSize);
}
template<typename T>
bool MyStack<T>::isEmpty(void)
{
    //if (count == 0)
      //  throw stackEmpty;
    return (count == 0);
}
#endif  //TEMPLATE_STACK_H
