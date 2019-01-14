#include <stdlib.h>
#include <stdio.h>

static const int CIRCLE_QUEUE_SIZE = 9;  //ѭ�����д�С
typedef struct
{
	int data[CIRCLE_QUEUE_SIZE];
	int front;  // ��ͷ����
	int rear;   //��β��һλ�������������в�Ϊ�գ�ָ���β����һ��λ��
}CIRCLE_QUEUE;

/*��ʼ��һ���յ�ѭ������*/
bool Circle_Queue_Init(CIRCLE_QUEUE* circle_q)
{
	circle_q->front = 0;
	circle_q->rear = 0;
	return true;
}

/*�ж�ѭ�������Ƿ�Ϊ��*/
bool Circle_Queue_IsEmpty(const CIRCLE_QUEUE* circle_q)
{
	if (circle_q->front == circle_q->rear) {
		return true;
	}
	else
		return false;
}

/*�ж�ѭ�������Ƿ�����*/
bool Circle_Queue_IsFull(const CIRCLE_QUEUE* circle_q)
{
	if ((circle_q->rear + 1) % CIRCLE_QUEUE_SIZE == circle_q->front) {
		return true;
	}
	else
		return false;
}
/*��ѭ�������ж�β����һ��Ԫ��*/
bool Circle_Queue_Push(CIRCLE_QUEUE* circle_q, int e)
{
	if (Circle_Queue_IsFull(circle_q)) {
		return false;
	}
	circle_q->data[circle_q->rear] = e;
	circle_q->rear = (circle_q->rear + 1) % CIRCLE_QUEUE_SIZE;
	return true;
}

/*����ͷԪ�ص���*/
bool Circle_Queue_Pop(CIRCLE_QUEUE* circle_q, int* e)
{
	if (Circle_Queue_IsEmpty(circle_q)) {
		return false;
	}
	*e = circle_q->data[circle_q->front];
	circle_q->front = (circle_q->front + 1) % CIRCLE_QUEUE_SIZE;
	return true;
}

int main()
{
	CIRCLE_QUEUE Circle_q;
	int temp = 0;
	Circle_Queue_Init(&Circle_q);
	Circle_Queue_Push(&Circle_q, 1);
	Circle_Queue_Push(&Circle_q, 2);
	Circle_Queue_Push(&Circle_q, 3);
	Circle_Queue_Push(&Circle_q, 4);
	Circle_Queue_Push(&Circle_q, 5);
	while (!Circle_Queue_IsEmpty(&Circle_q))
	{
		Circle_Queue_Pop(&Circle_q,&temp);
		printf("%d \n", temp);
	}
	system("pause");
}