/*
 * =====================================================================================
 *
 *       Filename:  graph2.c
 *
 *    Description:  重新备份的无向图的信息
 *
 *        Version:  1.0
 *        Created:  2013年12月17日 21时17分35秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  cuijiaojiao, cuijiaojiaofendou@gmail.com
 *        Company:  Class 1204 of Software
 *
 * =====================================================================================
 */

#include <string.h>
#include "graph.h"
#include "queue.h"
#include "menue.h"

void F_write(char name[], char informa[]);

int Locate(AdjList *G, char name[])        //通过景点名获取景点下标
{
	int i;
	for (i = 1; i <= G->vexnum; i++)
	{
		if(strcmp(name, G->vexter[i].vexdata) == 0)
			return i;
	}
	return -1;
}

void Error(AdjList *G, int *i, int *j, int *weight)  //错误函数处理
{
	char name[20];
	int t1, t2, w;
	if (*i == -1 || *j == -1 || *weight <= 0)
	{
		printf("输入有误，请重新输入:\n");
		printf("起点:");
		scanf("%s", name);
		t1 = Locate(G, name);
		*i = t1;
		printf("终点:");
		scanf("%s", name);
		t2 = Locate(G, name);
		*j = t2;
		printf("路线长度");
		scanf("%d", &w);
		*weight = w;
		Error(G, &t1, &t2, &w);
	}
}

AdjList *Creat()        //无向图
{
	AdjList *G;
	int i, j, k, weight;
	int vexnum, arcnum;
	ArcNode *s, *r;
	char name[256];

	G = (AdjList *)malloc(sizeof(AdjList));
	
	printf("请输入景点个数和各景点之间的关系:\n");
	scanf("%d%d", &G->vexnum, &G->arcnum);
	getchar();

	printf("请输入景点的名称和信息:\n");

	for (i = 1; i <= G->vexnum; i++)
	{
		F_write(G->vexter[i].vexdata, G->vexter[i].info);
	//	G->vexter[i].head = (ArcNode *)malloc(sizeof(ArcNode));
		G->vexter[i].head = NULL;
	}

	printf("请输入各景区之间的%d条边\n", G->arcnum);
	for (k = 1; k <= G->arcnum; k++)
	{
		printf("No.%d条边：", k);
		printf("起点：");
		scanf("%s", name);
		i = Locate(G, name);
//		printf("i = %d", i);
		printf("终点:");
		scanf("%s", name);
		getchar();
		j = Locate(G, name);
//		printf("j = %d", j);
		printf("路线长度:");
		scanf("%d", &weight);

		Error(G, &i, &j, &weight);

		printf("i = %d, j = %d, weight = %d\n", i, j, weight);
		getchar();

		if (i != -1 && j != -1 && weight > 0)
		{
			s = (ArcNode *)malloc(sizeof(ArcNode));

			s->adjvex = j;
			s->weight = weight;
			s->next = G->vexter[i].head;      //头叉法建立单链表
			G->vexter[i].head = s;

			r = (ArcNode *)malloc(sizeof(ArcNode));

			r->adjvex = i;
			r->weight = weight;
			r->next = G->vexter[j].head;
			G->vexter[j].head = r;
		}

	}
	return G;
}

//写文件，将景点名和景点信息写入文件2.txt中
void F_write(char name[], char informa[])
{
	FILE *fp;

	scanf("%s%s", name, informa);
	fp = fopen("2.txt", "a");
	fprintf(fp, "%s %s ", name, informa);
	fclose(fp);
}

void visit(int w)
{
	printf("%d", w);
}
/*
int FirstAdj(AdjList *G, int v)
{
	ArcNode *p;
	p = G->vexter[v].head;
	if (G->vexter[v].head != NULL)
	{
		while (p->next != NULL && visited[p->adjvex] != 0)
		      p = p->next;
		if (visited[p->adjvex] == 0)
		      return (p->adjvex);
	}

	return -1;
}

//求下一个邻接点
int NextAdj(AdjList *G, int v, int w)
{
	ArcNode *p;
	if (G->vexter[v].head != NULL)
	{
		p = G->vexter[v].head;
		while (p->next != NULL)
		{
			p = p->next;
			if (p->adjvex == w && p->next != NULL)
			      return (p->next->adjvex);
		}
	}

	return -1;
}
*/


//广度优先遍历，求一个景点到每个景点的一条路径
void BFS(AdjList *G, int v0)
{
	LQueue *Q;
	ArcNode *p;
	int v, w, i;

	if(v0 == -1)
	{
		printf("糟糕，你的起始点没有哦!\n");
	} else {
//	visit(v0);
	visited[v0] = 1;
	
	Q = InitQueue();
	EnterQueue(Q, v0);

	for (i = 1; i <= G->vexnum; i++)         //为了确保每个景点都被访问过了
	{
		while(Empty(Q))
		{
			DeleteQueue(Q, &v);

			printf("%s---", G->vexter[v].vexdata);
			
			p = G->vexter[v].head;
			w = p->adjvex;
		
//			printf("%d\n", w);

			while(w && p->next != NULL)
			{
				if(!visited[w])
				{
//					visit(w);
					visited[w] = 1;
					EnterQueue(Q, w);
				}

				p = p->next;
				w = p->adjvex;
			}

		}

		if(!visited[i] && !Empty(Q))
		{
			BFS(G, i);
		}
	}
	}
}

//广度优先遍历搜索
void TraversetG(AdjList *G)
{
	int v;
	char name[20];

	for (v = 1; v <= G->vexnum; v++)   //初始化标志数组
	      visited[v] = 0;
	
	printf("请输入起点名:\n");
	scanf("%s", name);
	v = Locate(G, name);           //获取起点景点下标
	

	BFS(G, v);
	
	printf("\n");
}

//显示图中的信息
void Display(AdjList *G)
{
	int i;
	ArcNode *p;

	printf("\n景点的交通路线情况:\n");
	for (i = 1; i <= G->vexnum; i++)
	{
		p = G->vexter[i].head;       //p指向链表头结点
		while(p != NULL)         //这有点问题
		{
			printf("%s<-->%s: %6dkm\n", G->vexter[i].vexdata, 
			G->vexter[p->adjvex].vexdata, p->weight);
				
			p = p->next ;       //循环
		}
		
	}

}

//对某个景点的查询，相关信息及道路类别
void Search(AdjList *G, char name[])
{
	int i, t;
	ArcNode *p;

	printf("请输入要查询的景点名:\n");
	scanf("%s", name);
	
	for (i = 1; i <= G->vexnum; i++)
	{
		if (strcmp(G->vexter[i].vexdata, name) == 0)        //比较并查找图中是否有该景点
		{
			p = G->vexter[i].head;
			t = 1;                               //标志，说明存在该景点
		      	printf("%s  %s\n", G->vexter[i].vexdata, G->vexter[i].info);
			while (p != NULL)
			{
				printf("%s<-->%s: %6dkm\n", G->vexter[i].vexdata, 
				G->vexter[p->adjvex].vexdata, p->weight);
				p = p->next ;
			}
		}
	}

	if (t != 1 && i > G->vexnum)            //不存在该景点的情况
	      printf("没有您要查的景点\n");
}

//求Floyed 算法中得到的路径
void Path_Adj(AdjList *G, int F[][MAXVEX], int Path[MAXVEX][MAXVEX])
{
	int v = 1, w = 1, k = 1;
	char name1[20], name2[20];
	printf("请输入起点名和终点名:");
	scanf("%s %s", name1, name2);

	v = Locate(G, name1);
	w = Locate(G, name2);

	if (v == -1 || w == -1)
	{

	//	printf("v = %d, w = %d\n", v, w);
		printf("sorry,起点或终点不存在~，请重新输入:\n");
		Path_Adj(G, F, Path);
	} else {
			
		k = Path[v][w];    //获得第一个景点的下标
		printf(" path : %s ", G->vexter[v].vexdata);

		while (k != w)
		{
			printf(" ——> %s", G->vexter[k].vexdata);
			k = Path[k][w];
		}
		printf(" ——> %s  ", G->vexter[w].vexdata);
		
		printf("  %d\n\n", F[v][w]);
	}
}


//Floyed 算法求最短路径
void Floyed_Adj(AdjList *G, int F[][MAXVEX])
{
	int Path[MAXVEX][MAXVEX];
	int i, j, k;
	ArcNode *p;
	
	//初始化
	for (i = 1; i <= G->vexnum; i++)
	     for (j = 1; j <= G->vexnum; j++)
	      {
		      if ( i != j)
	      	    	F[i][j] = INFINITY;              //正对角线上的元素权值为0

		      else
			    F[i][j] = 0;            //初始化，所有结点的之都是无穷大
		      Path[i][j] = INFINITY;
		     
	      }

	//二次初始F矩阵，并初始化路径
	for (i = 1; i <= G->vexnum; i++)
	{
		p = G->vexter[i].head;       //p指向链表头结点
		while (p != NULL)         
		{
			j = p->adjvex;
			F[i][j] = p->weight;         //二位数组的初始化
			Path[i][j] = j;
			p = p->next ;       //循环
		}
	}

	for (i = 1; i <= G->vexnum; i ++)
		for (j = 1; j <= G->vexnum; j++)
		{
		      for (k = 1; k <= G->vexnum; k++)
			    if (F[i][j] > F[i][k] + F[k][j])
			    {
			    	F[i][j] = F[i][k] + F[k][j];
				Path[i][j]  = Path[i][k];             //如何记录路径?
			    }
		}
	Path_Adj(G,F, Path);
		
}

//将图中的信息写入文件里
void File_write(AdjList *G)
{
	FILE *fp;
	ArcNode *p;
	char ch = '#';
	int i;

	fp = fopen("2.txt", "w");

	if (fp == NULL)
	{
		printf("can't open 2.txt");
		exit(0);
	}

	fprintf(fp, "%d  %d\n", G->vexnum, G->arcnum);     //将顶点个数和边的条数存入文件中

	for (i = 1; i <= G->vexnum; i++)
	{
		p = G->vexter[i].head;

		fprintf(fp, "%s  %s ", G->vexter[i].vexdata, G->vexter[i].info);       //景点名称和景点信息

		while (p != NULL)
		{
			fprintf(fp, "%d  %d ", p->adjvex, p->weight);                    //将邻接点和邻接关系写入
			p = p->next;
		}

		fprintf(fp,"%c", ch);
	}

	fclose(fp);
}

//将图从文件中读出来
AdjList *File_read(void)
{
	FILE *fp;
	int i;
	char ch;
	AdjList *G;
	ArcNode *p;

	fp = fopen("2.txt", "r");
	if (fp == NULL)
	{
		printf("can't open 2.txt.");
		exit(0);
	}

	G = (AdjList *)malloc(sizeof(AdjList));

	fscanf(fp, "%d %d\n", &G->vexnum, &G->arcnum);      //读出景点的个数和边数
	
	for (i = 1; i <= G->vexnum; i++)
	{
		fscanf(fp, "%s %s ",G->vexter[i].vexdata, G->vexter[i].info);    //读出景点信息
		G->vexter[i].head = NULL;

		do{
			p = (ArcNode *)malloc(sizeof(ArcNode));
			fscanf(fp, "%d %d ", &p->adjvex, &p->weight);
			
			p->next = G->vexter[i].head;
			G->vexter[i].head = p;

			fscanf(fp, "%c", &ch);

			if(ch != '#')
			      fseek(fp, -1L, SEEK_CUR);
		} while(ch != '#');
	}

	fclose(fp);

	return G;

}

//添加路线
AdjList *Add_Line(AdjList *G)
{
	ArcNode *r, *s;
	char name1[20], name2[20];
	int weight;
	int i, j;

	printf("想要添加哪两个景点之间的路线？请依次输入景点名1、景点名2、路线长度:\n");
	scanf("%s %s %d",name1, name2, &weight);

	i = Locate(G, name1);            
	j = Locate(G, name2);

	Error(G, &i, &j, &weight);         //判断两景点之间有没有在景区内


	if (i != -1 && j != -1 && weight > 0)
	{
		s = (ArcNode *)malloc(sizeof(ArcNode));

		s->adjvex = j;
		s->weight = weight;
		s->next = G->vexter[i].head;      //头叉法建立单链表
		G->vexter[i].head = s;

		r = (ArcNode *)malloc(sizeof(ArcNode));

		r->adjvex = i;
		r->weight = weight;
		r->next = G->vexter[j].head;
		G->vexter[j].head = r;
	
		G->arcnum += 1;       //并加上边数
	}
	
	return G;
}

ArcNode *Delete(ArcNode *head, int x)
{
	ArcNode *r, *q;

	if (head == NULL)
	{
		printf("\n已不存在可删除的路线了!\n");
		goto end;
	}
	r = head;

	while (x != r->adjvex && r->next != NULL)               //r指向的不是要找的结点，并且后面还有结点
	{
		q = r;                        
		r = r->next;                                     //r指向下一个结点
	}

	if(x == r->adjvex)
	{
		if (r == head)              //r指向的是首结点
		      head = r->next;
		else
		      q->next = r->next;
		      free(r);
	} else {
	
		printf("\n不存在该路线!\n");
	}

	end:

		return head;
}

//删除路线
AdjList *Delete_Line(AdjList *G)
{
	ArcNode *r, *s, *q;
	char name1[20], name2[20];
	int i, j;

	printf("想要删除哪两个景点之间的路线？请依次输入景点名1、景点名2\n");
	scanf("%s %s", name1, name2);

	
	i = Locate(G, name1);
	j = Locate(G, name2);

	G->vexter[i].head = Delete(G->vexter[i].head, j);
	G->vexter[j].head = Delete(G->vexter[j].head, i);

	G->arcnum -= 1;
	
	return G;
}

//更新图库信息
AdjList *Update_Graph(AdjList *G)
{
	int number, count, i;

	//从文件中读出图的所有信息
	G = File_read();
	
	printf(" YOU WANT TO ADD OR DELETE THE LINE ？\n");
	
	scanf("%d", &number);
	
	//选择方式，增添路线还是删除路线
	switch (number)
	{
		//增添路线
		case 1:
			printf("HOW MANY LINE YOU WANT ADD？please input:\n");

			//增添的路线总数
			scanf("%d", &count);
			
			for (i = 0; i < count; i++)
			      G = Add_Line(G);

		break;
		case 2:
			printf("HOW MANY LINE YOU WANGT DELETE？please input:\n");
		
			//删除路线的函数
			scanf("%d", &count);
			
			for(i = 0; i < count; i++)
				G = Delete_Line(G);

		break;
		case 0:
				printf("回到主页单喽！\n");
			break;
	}

	return G;
}

int Screct(char name[])
{
	printf("请输入VIP密码：\n");
	scanf("%s", name);
	if (strcmp(name, "123456") != 0)
	{
		printf("密码错误!\n");
		return 0;
	} else {
		printf("亲爱的VIP成员，您可以进行此操作了~~\n");
		return 1;
	}

}

int path[MAXSIZE] = {0};  //暂存遍历过程中的路径

int Find_All_Path(AdjList *G, int u, int v, int k)     //求无向图G中顶点u到v的所有简单路径, k表示当前路径
{
	int i, t;
	ArcNode *p;
	path[k] = u;
	visited[u] = 1;

	if (u == v)
	{
		printf("\n");
		for(i = 0;path[i]; i++)
//		      printf("%d", path[i]);
			printf("%s   ", G->vexter[path[i]].vexdata);
		printf("\n");
	} else {
		for (p = G->vexter[u].head; p; p = p->next)
		{
			t = p->adjvex;
			if(!visited[t])
			      Find_All_Path(G, t, v, k+1);      //继续寻找
		}
	}

	visited[u] = 0;
	path[k] = 0;
}

//输入名称并验证是否正确
void Scanf(AdjList *G)
{
	int i, j, k;
	char name[20];
	printf("请输入第一个景点名:\n");
	scanf("%s", name);
	i = Locate(G, name);
	printf("请输入第二个景点名:\n");
	scanf("%s", name);
	j = Locate(G, name);

	//标志数组初始化
	for (k = 1; k <= G->vexnum; k++)
	      visited[k] = 0;

	k = 0;

	//景点名不存在的情况
	if (i == -1 || j == -1)        
	{
		printf("糟糕,景点名不存在！\n");
	} else {
		//进行多路径查找
		Find_All_Path(G, i, j, k);     
	}
}

void Road(AdjList *G, int start);

//从某一景点出发，访问所有景点的最佳方案
void BestRoad(AdjList *G, char name[])
{
	int start;

	printf("请输入初始景点名:");
	scanf("%s", name);

	start = Locate(G, name);            //得到起点景点下标

	if(start == -1)                     //判断该景点是否存在
	{
		printf("糟糕，没有这个景点!\n");
	} else {
		Road(G, start);              //存在就去找它的最短路径
	}
}

void Road(AdjList *G, int start)
{
	struct 
	{
		int adjvex;        //存放U中与v最近的顶点序号
		int lowcost;       //记录权值信息
	}closedge[MAXVEX];          //辅助数组
	int i, e, k, m, min;
	ArcNode *p;
	int F[MAXSIZE][MAXSIZE];

	closedge[start].lowcost = 0;   //标志顶点u已加入到U-生成树集合
	
	printf("%s   ", G->vexter[start].vexdata);
	//将权值信息以矩阵的方式存入
	for (i = 1; i <= G->vexnum; i++)     //给F[MAX][MAX]数组初始化
	      for (k = 1; k <= G->vexnum; k++)
	      {
		    if (i == k)
			F[i][k] = 0;      //对角线上的点的权值为0

		    F[i][k] = INFINITY;
	      }

	for (i = 1; i <= G->vexnum; i++)
	{
		p = G->vexter[i].head;       //p指向链表头结点
		while (p != NULL)         
		{
			k = p->adjvex;
			F[i][k] = p->weight;         //二位数组的初始化
			p = p->next ;       //循环
		}
	}

	//对除起点以外的所有景点初始化对应的closedge数组
	for (i = 1; i <= G->vexnum; i++)
	      if (i != start)
	      {
	      	closedge[i].adjvex = start;
		closedge[i].lowcost = F[start][i];
	      }
	
	//控制选中的n-1条符合条件的边
	for (e = 1; e <= G->vexnum - 1; e++)
	{
		//选择最小权值的边
		min = INFINITY;

		for (k = 1; k <= G->vexnum; k++)
		{
			if(closedge[k].lowcost != 0 && closedge[k].lowcost < min)
			{
				m = k;
				min = closedge[k].lowcost;
			}
		}

		//标志顶点v0加入到U—生成树中
		closedge[m].lowcost = 0;
		printf("%s   ", G->vexter[m].vexdata);
		
		//当v0加入后，更新closedge数组信息
		for (i = 1; i <= G->vexnum; i++)
		{
			//一旦发现更小的权值边出现，则替换原有信息
			if (i != m && F[m][i] < closedge[i].lowcost)
			{
				closedge[i].lowcost = F[m][i];
				closedge[i].adjvex = m;
			}
		}
	}

	printf("\n");

}
int main()
{
	AdjList *G;
	int F[MAXVEX][MAXVEX];
	char name[20];
	int number;

	system("clear");
	menue();
	while (1)
	{
		printf("\n-------------------------------------------------------\n");
		printf("请输入你的选择：\n");
		scanf("%d", &number);
		if (number < 0 || number > 9)
		      printf("糟糕，输入错误~，请重新输入:\n");
		switch (number)
		{
			case 1 :
				printf("没有图哦，需要自己创建.\n");
				number = Screct(name);
				if (number == 1)
				{
					G = Creat();
					File_write(G);
				} else {
					printf("非VIP客户，不能创建图!\n");
				}
			break;
			case 2:
				printf("想知道都有什么景点吗？\n");
				G = File_read();
				Display(G);
			break;
			case 3:
				printf("想知道某个景点的详细信息吗？\n");
				G = File_read();
				Search(G, name);
			break;
			case 4:
				printf("想知道某个景点开始到其他景点的一条访问行走方案吗？\n");
				G = File_read();
				TraversetG(G);
			break;
			case 5:
				printf("任意两个景点之间的一条最短路径:\n");
				G = File_read();
				Floyed_Adj(G, F);
			break;
			case 6:
				printf("想知道景点之间的最佳路径吗？\n");
				G = File_read();
				BestRoad(G, name);
			break;
			case 7:
				number = Screct(name);
				if(number == 1)
				{
					G = File_read();
					G = Update_Graph(G);
					File_write(G);
				} else {
					printf("非VIP客户，不能进行图像更新!\n");
				}
			break;
			case 8:
				G = File_read();
				Scanf(G);
			break;
			case 9:
				menue();
			break;
			case 0:
				exit(0);
//			default:
		//		menue();

		}
	}

	return 0;
}
