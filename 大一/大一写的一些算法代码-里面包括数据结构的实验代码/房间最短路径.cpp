#include <iostream>
#include <math.h>
#include <cstring>
#define MAX 81
#define INF 666
using namespace std;
int n;//ǽ�ĸ���
double e[MAX][MAX];//����ͼ�бߵ�Ȩֵ

struct Wall
{
    double x;
    double y[4];
}w[20];

bool isAccess(int i, int j, int n1, int n2)//�жϵ�i��ǽ�ĵ�n1���㵽��j��ǽ�ĵ�n2�����Ƿ����
{//�����ÿ����ķ�������ֱ���Ƿ��ཻ  �����õ��Ǽ��εķ��� ��������С
        if(i + 1 == j) return true;//����ǽ�������������

        //�����������֮���ֱ�� y = kx + b
        double x1 = w[i].x,   x2 = w[j].x;
        double y1 = w[i].y[n1],   y2 = w[j].y[n2];//������ĺ�������
        double k = (y1 - y2) / (x1 - x2);//�������֮���б��
        double b = y1 - k * x1;//��ʽ���b

        for(int  m = i + 1; m < j; m++){//����i �� j ǽ֮�������ǽ �۲��Ƿ����
            double mx = w[m].x;//��m��ǽ�ĺ�����
            double my = k * mx + b;//ֱ�߾�����m��ǽʱ��������
            if( !   (  (my >= w[m].y[0] && my <= w[m].y[1]) || (my >= w[m].y[2] && my <= w[m].y[3]) ) )
                return false;
        }

        return true;
}

void addEdge(int i, int j, int m,int n)//��i��ǽ�ĵ�m���� �� ��j��ǽ�ĵ�n���� ����
{
    if(isAccess(i, j, m, n))//�ж�������֮���Ƿ���Ե���
    {
        double x1 = w[i].x, x2 = w[j].x;
        double y1 = w[i].y[m], y2 = w[j].y[n];
        double distance = sqrt( (x1 - x2) * (x1 - x2) +   (y1 - y2) * (y1 - y2)  );
        e[i * 4 + m][j * 4 + n] = distance;//�����ÿ���㶼�����˱��
    }
}

int main()
{
    cout << "Please input the number of walls and  the range of each door's Y : " << endl;
    cin >> n;

    //��ʼ��ͼ
    for(int i = 0; i < 4 * n + 8  ; i++)  for(int j = 0; j < 4 * n + 8; j++)  e[i][j] = INF;//��ʼ�������б߶���ͨ ��ʼ������ȨֵΪ�����
    w[0].x = 0, w[n + 1].x = 10;//�����յ�ǽ�ĺ�����
    for(int i = 0; i < 4; i ++) w[0].y[i] = w[n + 1].y[i] = 5;//�������յ��ŵ������긳ֵ
    for(int i = 1; i <= n ; i++){
        cin >> w[i].x;//����ǽ�ĺ�����
        for(int j = 0; j < 4; j++) cin >> w[i].y[j];//����ǽ�����ŵ������귶Χ
    }
    for(int i = 0; i <= n; i++){//��i��ǽ �ӵ�0�¼���� ����n �½��� n+1��Ϊ����
            for(int j = i + 1; j <= n + 1; j++){//��i��ǽ����j��ǽ����
                for(int m = 0; m < 4; m++){//��i��ǽ�ĵ�m����
                    for(int n = 0; n < 4; n++){//����j��ǽ�ĵ�n����
                        addEdge(i, j, m, n);//i��ǽ�ĵ�m���˿� ��j��ǽ��n���˿ڽ���
                    }
                }
            }
    }
    //Floyd�㷨�����·��  ������ʵ��DFS BFS ������ ֻ����Floyed Ч�ʸ���
    for(int k = 0; k < n * 4 + 8; k++)
        for(int i = 0; i < n * 4 + 8; i++)
            for(int j = 0;j < n * 4 +8; j++)
                if(e[i][j] > e[i][k] + e[k][j])
                        e[i][j] = e[i][k] + e[k][j];
     cout<<"The min distance is : %.2lf\n"<<e[0][n * 4 + 7]<<endl;

    return 0;
}

