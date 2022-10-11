#include <iostream>
#include <math.h>
#include <cstring>
#define MAX 81
#define INF 666
using namespace std;
int n;//墙的个数
double e[MAX][MAX];//储存图中边的权值

struct Wall
{
    double x;
    double y[4];
}w[20];

bool isAccess(int i, int j, int n1, int n2)//判断第i堵墙的第n1个点到第j堵墙的第n2个点是否可行
{//可以用跨立的方法求两直线是否相交  这里用的是几何的方法 计算量更小
        if(i + 1 == j) return true;//两堵墙相邻则可以连线

        //首先求出两点之间的直线 y = kx + b
        double x1 = w[i].x,   x2 = w[j].x;
        double y1 = w[i].y[n1],   y2 = w[j].y[n2];//两个点的横纵坐标
        double k = (y1 - y2) / (x1 - x2);//算出两点之间的斜率
        double b = y1 - k * x1;//公式里的b

        for(int  m = i + 1; m < j; m++){//遍历i 到 j 墙之间的所有墙 观察是否可行
            double mx = w[m].x;//第m个墙的横坐标
            double my = k * mx + b;//直线经过第m个墙时的纵坐标
            if( !   (  (my >= w[m].y[0] && my <= w[m].y[1]) || (my >= w[m].y[2] && my <= w[m].y[3]) ) )
                return false;
        }

        return true;
}

void addEdge(int i, int j, int m,int n)//第i个墙的第m个点 向 第j个墙的第n个点 建边
{
    if(isAccess(i, j, m, n))//判断两个点之间是否可以到达
    {
        double x1 = w[i].x, x2 = w[j].x;
        double y1 = w[i].y[m], y2 = w[j].y[n];
        double distance = sqrt( (x1 - x2) * (x1 - x2) +   (y1 - y2) * (y1 - y2)  );
        e[i * 4 + m][j * 4 + n] = distance;//这里对每个点都进行了编号
    }
}

int main()
{
    cout << "Please input the number of walls and  the range of each door's Y : " << endl;
    cin >> n;

    //初始化图
    for(int i = 0; i < 4 * n + 8  ; i++)  for(int j = 0; j < 4 * n + 8; j++)  e[i][j] = INF;//开始假设所有边都不通 初始化所有权值为无穷大
    w[0].x = 0, w[n + 1].x = 10;//起点和终点墙的横坐标
    for(int i = 0; i < 4; i ++) w[0].y[i] = w[n + 1].y[i] = 5;//将起点和终点门的纵坐标赋值
    for(int i = 1; i <= n ; i++){
        cin >> w[i].x;//输入墙的横坐标
        for(int j = 0; j < 4; j++) cin >> w[i].y[j];//输入墙两个门的纵坐标范围
    }
    for(int i = 0; i <= n; i++){//第i堵墙 从第0堵即入口 到第n 堵结束 n+1堵为出口
            for(int j = i + 1; j <= n + 1; j++){//从i堵墙到第j堵墙建边
                for(int m = 0; m < 4; m++){//第i堵墙的第m个点
                    for(int n = 0; n < 4; n++){//到第j堵墙的第n个点
                        addEdge(i, j, m, n);//i堵墙的第m个端口 到j堵墙的n个端口建边
                    }
                }
            }
    }
    //Floyd算法求最短路径  这里其实用DFS BFS 都可以 只不过Floyed 效率更高
    for(int k = 0; k < n * 4 + 8; k++)
        for(int i = 0; i < n * 4 + 8; i++)
            for(int j = 0;j < n * 4 +8; j++)
                if(e[i][j] > e[i][k] + e[k][j])
                        e[i][j] = e[i][k] + e[k][j];
     cout<<"The min distance is : %.2lf\n"<<e[0][n * 4 + 7]<<endl;

    return 0;
}

