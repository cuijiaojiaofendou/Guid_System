/*
 * =====================================================================================
 *
 *       Filename:  queue.h
 *
 *    Description:  队列处理
 *
 *        Version:  1.0
 *        Created:  2013年11月17日 11时24分27秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  cuijiaojiao, cuijiaojiaofendou@gmail.com
 *        Company:  Class 1204 of Software
 *
 * =====================================================================================
 */

#ifndef __ABC
#define __ABC

typedef struct node
{
	int data;
	struct node *next;
}QNode;
typedef struct 
{
	QNode *front;
	QNode *rear;
}LQueue;

LQueue* InitQueue()
{
	LQueue *p;
	QNode *q;
	p = malloc(sizeof(LQueue));    //申请头尾指针结点
	q = malloc(sizeof(QNode));
	q->next = NULL;
	p->front = p->rear = q;

	return p;
}
	
void EnterQueue(LQueue *Q, int x)   //入队
{
	QNode *p;
	p = malloc(sizeof(QNode));
	p->data = x;
	p->next = NULL;
	Q->rear->next =p;
	Q->rear = p;
}

int Empty(LQueue *Q)
{
	if(Q->front == Q->rear)
	      return 0;
	else
	      return 1;
}
int DeleteQueue(LQueue *Q, int *x)
{
	QNode *p;
	if(!Empty(Q))
	{
		printf("队空!\n");
		return 0;
	} else {
		p = Q->front->next;
		Q->front->next = p->next;
		*x = p->data;
		if(Q->front->next == NULL)
		      Q->rear = Q->front;
		return 1;
	}
}

#endif
