#include<iostream>
#include<stdio.h> 
#include<conio.h>
#include<windows.h>
#include<iomanip>
#include<string>
#include<fstream>
#include<tchar.h>
#include<lmaccess.h> 
#include<lmapibuf.h>
#include<assert.h>
#include<unistd.h>   //��POSIX����ϵͳAPI�ķ��ʹ��ܵ�ͷ�ļ�������
#include<lm.h>  // 
using namespace std;
#pragma comment(lib,"netapi32.lib")
#pragma comment(lib, "Wtsapi32.lib")
#pragma comment(lib, "Userenv.lib")
char buf[100],path[100],path1[100],path2[100];//ȫ�ֱ�����buf���ڻ������ݣ�3��path���ڱ���·��
bool is_login=0;   //�Ƿ��¼ 
#define G_LEN_CMD_LINE  1024    //��������󳤶�
// ����wchar_t �����size, ��wchar_tΪ��λ
#define SIZE_OF_WCHAR_ARRAY(x) (sizeof(x) / sizeof(wchar_t))
/***************************************************����Ϊ������İ����ĵ�***********************************************/
#define PRINTLSHELP		"�÷���ls  [ѡ��]\n\
�г��ļ���Ϣ(Ĭ��Ϊ��ǰĿ¼)\n\
ls�޲�         ��ʾһ��Ŀ¼�е��ļ�����Ŀ¼\n\
ls -l          ÿ�н���ʾһ��Ŀ¼������\n\
ls --help      ��ʾ�˰�����Ϣ���뿪"
#define PRINTPASSWDHELP "�÷���passwd [ѡ��]\n\
���û�������     ��ʾ�û�������\n\
passwd �û���    ����[�û���]������\n\
passwd -s �û��� ��ʾ�˺�������Ϣ\n\
passwd -d �û��� ɾ���û�����\n\
passwd --help    ��ʾ�˰�����Ϣ�����뿪" 
#define PRINTMKDIRHELP	"�÷���mkdir  Ŀ¼\n\
��Ŀ¼�������򴴽�Ŀ¼\n\
mkdir --help   ��ʾ�˰�����Ϣ���뿪"
#define PRINTRMDIRHELP		"�÷���rmdir  Ŀ¼\n\
��Ŀ¼û��������ɾ��Ŀ¼\n\
rmdir --help   ��ʾ�˰�����Ϣ���뿪"
#define PRINTCPHELP		"�÷���cp  ��Դ�ļ� Ŀ���ļ�\n\
����Դ�ļ����Ƶ�Ŀ���ļ�\n\
cp --help   ��ʾ�˰�����Ϣ���뿪"
#define PRINTCATHELP	"�÷���cat  �ļ�\n\
  ��cat  �ļ�1 >> �ļ�2\n\
��ʾ�ļ����ݻ����������ļ�����������������ʾ����\n\
cat �ļ�            ���ļ��������������ʾ����\n\
cat �ļ�1 >> �ļ�2  ���ļ�1���ӵ��ļ�2�Ľ�β�����������ʾ����\n\
cat --help          ��ʾ�˰�����Ϣ���뿪"
#define PRINTMOREHELP		"�÷���more  �ļ�\n\
ʹ�ļ�������(�س���)����ҳ(�ո��)��ʾ����ʾ��ǰ�ļ���ռ���ļ��İٷֱ�\n\
more --help		��ʾ�˰�����Ϣ���뿪"
#define PRINTMVHELP		"�÷���mv �ļ�1 �ļ�2\n\
  ��mv �ļ� Ŀ¼(��ʽΪ��Ҫ�ƶ�����Ŀ¼�ľ���·��+Ҫ�ƶ����ļ�)\n\
���������ƶ��ļ�\n\
mv  �ļ�1  �ļ�2         ���ļ�1���ָ�Ϊ�ļ�2������\n\
mv  �ļ�   Ŀ¼          ��ָ���ļ��ƶ���ָ��Ŀ¼��\n\
mv --help                ��ʾ�˰�����Ϣ���뿪"
#define PRINTSORTHELP		"�÷���sort �ļ�\n\
���ı��ļ����ݼ�������\n\
sort --help       ��ʾ�˰�����Ϣ���뿪"
/*******************************************����Ϊ������ľ���ʵ�ֺ���***************************************************/
char* getUsername()  //��ȡ��ǰ�û����� 
{
    DWORD size=UNLEN+1;
    char buf[size];
    GetUserName(buf, &size);
    return buf;
}
/*cd����*/
void cd_cmd(char * route)
{
	if(!SetCurrentDirectory(route))
	{	
		cout<<"·��������!"<<endl;
		if(is_login)
		{
			printf("[%s@LAPTOP-TB7M6EQ2 %s]#",getUsername(),path);
		}   
		else
		{
			printf("%s>",path);
		} 
	//	GetLastError();
	}
	else 
	{
		SetCurrentDirectory(route);
		GetCurrentDirectory(100,path);
		if(is_login)
		{
			printf("[%s@LAPTOP-TB7M6EQ2 %s]#",getUsername(),path);
		}   
		else
		{
			printf("%s>",path);
		} 
	}
}
/*************************************
* Login
* ����    �л��û�Ȩ�ޣ��û������˺�����
**************************************/
wchar_t* char2wchar_t(char* buff)
{
	int bufSize = strlen(buff) + 1;
	wchar_t* result = (wchar_t*)malloc(sizeof(wchar_t*) * bufSize);
	mbstowcs(result, buff, bufSize);
	return result;
}
//void ListUsers(LPWSTR pszServerName)
//{
//    LPUSER_INFO_0 pBuf = NULL;
//    LPUSER_INFO_0 pTmpBuf;
//    DWORD dwLevel = 0;
//    DWORD dwPrefMaxLen = MAX_PREFERRED_LENGTH;
//    DWORD dwEntriesRead = 0;
//    DWORD dwTotalEntries = 0;
//    DWORD dwResumeHandle = 0;
//    DWORD i;
//    DWORD dwTotalCount = 0;
//    NET_API_STATUS nStatus;
//
//    // ѭ����ֱ�����Գɹ����� NetUserEnum  
//    do
//    {
//        // ����NetUserEnum����  
//        nStatus = NetUserEnum(pszServerName,
//            dwLevel,// ��������Ϊ0��ʹ�� LPUSER_INFO_0 ���ؽ��  
//            FILTER_NORMAL_ACCOUNT, // ֻ�о١����������͵��û�  
//            (LPBYTE*)&pBuf,// LPUSER_INFO_0 ���淵�ؽ��  
//            // MAX_PREFERRED_LENGTH���ڴ���API���䣬��Ҫ��֮�����NetApiBufferFree�ͷ�  
//            dwPrefMaxLen,
//            &dwEntriesRead,// ���˵� Entries  
//            &dwTotalEntries,// һ���� Entries  
//            &dwResumeHandle);
//        // �ж��Ƿ�ɹ�  
//        if ((nStatus == NERR_Success) || (nStatus == ERROR_MORE_DATA))
//        {
//            if ((pTmpBuf = pBuf) != NULL)
//            {
//                // ѭ����ȡ�û���Ϣ  
//                for (i = 0; (i < dwEntriesRead); i++)
//                {
//                    assert(pTmpBuf != NULL);
//                    if (pTmpBuf == NULL)
//                    {
//                        fprintf(stderr, "An access violation has occurred\n");
//                        break;
//                    }
//                    // ���  
//                    wprintf(L"\t-- %s\n", pTmpBuf->usri0_name);
//                    // ��һ��  
//                    pTmpBuf++;
//                    dwTotalCount++;
//                }
//            }
//        }
//        else
//            fprintf(stderr, "A system error has occurred: %d\n", nStatus);
//        // �ͷ��ڴ�  
//        if (pBuf != NULL)
//        {
//            NetApiBufferFree(pBuf);
//            pBuf = NULL;
//        }
//    } while (nStatus == ERROR_MORE_DATA); // end do  
//
//    // �ͷ��ڴ�  
//    if (pBuf != NULL)
//        NetApiBufferFree(pBuf);
//
//    fprintf(stderr, "Total of %d users\n\n", dwTotalCount);
//
//    return ;
//}
bool check_Login(char *array)
{
	char data[100];
	const char* fileNamePath = "D:\\ceshi\\account.txt";
	ifstream infile;
	infile.open(fileNamePath);
	if (infile.fail()) {
		cout << "�ļ�" << fileNamePath << "��ʧ�ܻ��߲����ڣ�" << endl;
	} else {
		while (!infile.eof()) {
			infile.getline(data,100);
			if(strstr(data,array))
			{
				return TRUE;
			}
		}
	}
	return FALSE;
	infile.close();
}  
void Login()
{   
	char buff[1024] = { 0 };
    printf("Please enter username:");
	gets(buff);
	if(!check_Login(buff))
	{
		cout<<"Login failed"<<endl;
		return;
	} 
	wchar_t* G_LOGIN_NAME = char2wchar_t(buff);
    printf("Please enter password:");
	char buff1[1024] = { 0 };
	char c;
	int i = 0;
	while (TRUE)
	{
		c = getch(); //�ӿ���̨��ȡһ���ַ����ǲ���ʾ 
		if (c == '\n' || c == '\r')  //windows��getch����س��᷵��\r\n
		{
			printf("\n");
			break;
		}
		putchar('*');
		buff1[i++] = c;
	}
	wchar_t * G_LOGIN_PWD = char2wchar_t(buff1);
	is_login=1; 
}
/*logout����*/
void Logout()
{
	is_login=0;  
 } 
 /*�޸�����*/ 
 void passwd() 
 {
 	
  } 
/*ls����*/
void ls_cmd(char *array)
{
	HANDLE	handle;
	int filenum=0;
	FILETIME lpCreationTime,lpLastAccessTime,lpLastWriteTime;
	SYSTEMTIME stime;
	WIN32_FIND_DATA* path2 = new WIN32_FIND_DATA();
	if(!GetCurrentDirectory(50,path1))
	{
		cout<<"·��������!"<<endl;
		return;
	}

	strcat(path1,"\\*.*");        //DOSͨ���
	if((handle = FindFirstFile(path1, path2)) != INVALID_HANDLE_VALUE)
	{
		do{
			HANDLE hDir = CreateFile(path2->cFileName,GENERIC_READ,FILE_SHARE_READ | FILE_SHARE_DELETE,NULL,OPEN_EXISTING,FILE_FLAG_BACKUP_SEMANTICS,  NULL);  
			if(GetFileTime(hDir,  &lpCreationTime,  &lpLastAccessTime,  &lpLastWriteTime)){  
				FILETIME  ftime;  
				FileTimeToLocalFileTime(&lpLastWriteTime,  &ftime);  //  ת���ɱ���ʱ��  
				FileTimeToSystemTime(&ftime,  &stime);  //  ת����ϵͳʱ���ʽ  
			}
			//cout<<setfill('0');
			if(strcmp(array,"ls")==0)
			{
				cout.setf(ios::left);
				if(filenum%3!=0)
					cout<<setw(20)<<path2->cFileName<<"	";
				else
					cout<<setw(20)<<path2->cFileName<<endl;
				filenum++;
			}
			else
			{
				cout<<stime.wYear<<"-"<<setw(2)<<stime.wMonth<<"-"<<setw(2)<<stime.wDay<<"	"<<setfill('0')<<setw(2)<<stime.wHour<<":"<<setw(2)<<stime.wMinute;
				cout<<"       "<<path2->cFileName<<endl;
			}
			
			CloseHandle(hDir);
			}while (FindNextFile(handle, path2));
	}
	FindClose(handle);
	cout<<endl;
	GetCurrentDirectory(100,path1);
	if(is_login)
	{
		printf("[%s@LAPTOP-TB7M6EQ2 %s]#",getUsername(),path);
	}   
	else
	{
		printf("%s>",path);
	} 
	
}
/*mkdir����*/
void mkdir_cmd(char *array)	
{
	GetCurrentDirectory(100,path);
	strcat(path,"\\");
	strcat(path,array);
	WIN32_FIND_DATA wfd;
	HANDLE hFind;
	hFind=FindFirstFile(path,&wfd);
	if(hFind!=INVALID_HANDLE_VALUE)
	{
		cout<<"��Ŀ¼�Ѵ��ڣ�����ʧ��!"<<endl;
		GetCurrentDirectory(100,path);
		if(is_login)
		{
			printf("[%s@LAPTOP-TB7M6EQ2 %s]#",getUsername(),path);
		}   
		else
		{
			printf("%s>",path);
		} 
	}
	else
	{
		CreateDirectory(array,NULL);
		GetCurrentDirectory(100,path);
		if(is_login)
		{
			printf("[%s@LAPTOP-TB7M6EQ2 %s]#",getUsername(),path);
		}   
		else
		{
			printf("%s>",path);
		} 
	}
}
/*rmdir����*/
void rmdir_cmd(char *array)
{
	GetCurrentDirectory(100,path);
	strcat(path,"\\");
	strcat(path,array);
	WIN32_FIND_DATA wfd;
	HANDLE hFind;
	hFind=FindFirstFile(path,&wfd);
	if(hFind==INVALID_HANDLE_VALUE)
	{
		cout<<"��Ŀ¼�����ڣ�ɾ��ʧ��!"<<endl;
		GetCurrentDirectory(100,path);
		if(is_login)
		{
			printf("[%s@LAPTOP-TB7M6EQ2 %s]#",getUsername(),path);
		}   
		else
		{
			printf("%s>",path);
		} 
	}
	else
	{
		RemoveDirectory(array);
		GetCurrentDirectory(100,path);
		if(is_login)
		{
			printf("[%s@LAPTOP-TB7M6EQ2 %s]#",getUsername(),path);
		}   
		else
		{
			printf("%s>",path);
		} 
	}
}
/*cp����*/
void cp_cmd(char *array1,char *array2)
{
	GetCurrentDirectory(100,path);
	strcat(path,"\\");
	strcat(path,array1);
	WIN32_FIND_DATA wfd;
	HANDLE hFind;
	hFind=FindFirstFile(path,&wfd);
	if(hFind==INVALID_HANDLE_VALUE)
	{
		cout<<"����ʧ�ܣ�û���Ǹ��ļ���Ŀ¼!"<<endl;
		GetCurrentDirectory(100,path);
		if(is_login)
		{
			printf("[%s@LAPTOP-TB7M6EQ2 %s]#",getUsername(),path);
		}   
		else
		{
			printf("%s>",path);
		} 
	}
	else
	{
		CopyFile(array1,array2,FALSE);//FALSE���ã����Ŀ���ļ����ڣ��򸲸ǵ�
		GetCurrentDirectory(100,path);
		if(is_login)
		{
			printf("[%s@LAPTOP-TB7M6EQ2 %s]#",getUsername(),path);
		}   
		else
		{
			printf("%s>",path);
		} 
	}
}
/*cat����*/
void cat_cmd1(char *array)//������ʾ�ļ�
{
	char ch[1000];
	GetCurrentDirectory(100,path);
	strcat(path,"\\");
	strcat(path,array);
	ifstream infile(path);
	if(!infile)
	{
		cout<<"�޷����ļ�"<<path<<endl;
		GetCurrentDirectory(100,path);
		if(is_login)
		{
			printf("[%s@LAPTOP-TB7M6EQ2 %s]#",getUsername(),path);
		}   
		else
		{
			printf("%s>",path);
		} 
	}
	else
	{
		infile.getline(ch,1000,EOF);
		cout<<ch<<endl;
		GetCurrentDirectory(100,path);
		if(is_login)
		{
			printf("[%s@LAPTOP-TB7M6EQ2 %s]#",getUsername(),path);
		}   
		else
		{
			printf("%s>",path);
		} 
	}
	infile.close();
}
 
void cat_cmd2(char *array1,char *array2)//�������Ӳ���ʾ�ļ�
{ 
	char ch[1000];
	char ch2[1000];
	GetCurrentDirectory(100,path);//����cat����֮ǰ��·��
	GetCurrentDirectory(100,path1);
	strcat(path1,"\\");
	GetCurrentDirectory(100,path2);
	strcat(path1,array1);
	ifstream infile1(path1);
	if(!infile1)
	{
		cout<<"�޷����ļ�"<<path1<<endl;
		GetCurrentDirectory(100,path1);
		printf("%s>",path1);
	}
	else
	{
		strcat(path2,array2);
		ofstream outfile2(path2,ios::app);
		if(!outfile2)
		{
			cout<<"�޷����ļ�"<<path2<<endl;
			GetCurrentDirectory(100,path2);
			printf("%s>",path2);
		}
		else
		{
			infile1.getline(ch,1000,EOF);
			printf("%s",ch); 
			outfile2<<" "<<ch;
			infile1.close();
			outfile2.close();
			ifstream infile2(path2);
			infile2.getline(ch2,1000,EOF);
			cout<<ch2<<endl;
			infile2.close();
		}
	}
	if(is_login)
	{
		printf("[%s@LAPTOP-TB7M6EQ2 %s]#",getUsername(),path);
	}   
	else
	{
		printf("%s>",path);
	} 	
}
/*more����*/
void more_cmd(char *array)
{
	char ch[1000];
	GetCurrentDirectory(100,path);
	strcat(path,"\\");
	strcat(path,array);
	ifstream infile(path);
	if(!infile)
	{
		cout<<"�޷����ļ�"<<path<<endl;
		GetCurrentDirectory(100,path);
		if(is_login)
		{
			printf("[%s@LAPTOP-TB7M6EQ2 %s]#",getUsername(),path);
		}   
		else
		{
			printf("%s>",path);
		} 
	}
	else
	{	
		int count1=0,count2=0,l;//count1������ʾ�ļ���������count2������ʾ��ǰ�������ļ�����
		while(!infile.eof())
		{
			infile.getline(ch,1000,'\n');
			count1++;
		}
		infile.clear();//����clear��֮ǰ���ļ�״̬���Բ���仯
		infile.seekg(0,ios::beg);//����ָ�����¶�λ���ļ�ͷ
		if(count1<24)
		{
			for(l=0;l<count1;l++)
			{
				infile.getline(ch,1000,'\n');
				cout<<ch<<endl;
			}
			
			GetCurrentDirectory(100,path);
			if(is_login)
			{
				printf("[%s@LAPTOP-TB7M6EQ2 %s]#",getUsername(),path);
			}   
			else
			{
				printf("%s>",path);
			} 
		}
		else
		{
			for(l=0;l<24;l++)
			{
				infile.getline(ch,1000,'\n');
				cout<<ch<<endl;
				count2++;
			}
			cout<<"--More--"<<int((double)count2/count1*100)<<"%";
			while(!infile.eof())
			{
				if(cin.get()=='\n')
				{
					infile.getline(ch,1000,'\n');
					cout<<ch<<endl;
					count2++;
					cout<<"--More--"<<int((double)count2/count1*100)<<"%";
				}
				else if(getchar()==32)//�������οո�һ�λس�
				{
					if(cin.get()=='\n')//���Ӵ��ж���������ѻس������ͳ�������ʾ�ļ�������
					{
						if((count1-count2)>0&&(count1-count2)<24)
						{
							for(l=0;l<(count1-count2);l++)
							{
								infile.getline(ch,1000,'\n');
								cout<<ch<<endl;
								count2++;
							}
						}
						else if((count1-count2)>24)
						{
							for(l=0;l<24;l++)
							{
								infile.getline(ch,1000,'\n');
								cout<<ch<<endl;
								count2++;
							}
						}
						cout<<"--More--"<<int((double)count2/count1*100)<<"%"<<'\n';
					}
				}
				 
				if(int((double)count2/count1*100)==100)
				{
					cout<<endl;
					GetCurrentDirectory(100,path);
					if(is_login)
					{
						printf("[%s@LAPTOP-TB7M6EQ2 %s]#",getUsername(),path);
					}   
					else
					{
						printf("%s>",path);
					} 
					break;
				}
			}
		}
	}
	infile.close();
}
/*mv����*/	
void mv_cmd1(char *array1,char *array2)
{
	GetCurrentDirectory(100,path);
	GetCurrentDirectory(100,path1);
	strcat(path1,"\\");
	strcat(path1,array1);
	ifstream infile1(path1);
	if(!infile1)
	{
		cout<<"�ļ�"<<array1<<"�����ڣ��޷�ִ�в���"<<endl;
		GetCurrentDirectory(100,path1);
		if(is_login)
		{
			printf("[%s@LAPTOP-TB7M6EQ2 %s]#",getUsername(),path);
		}   
		else
		{
			printf("%s>",path1);
		} 
	}
	else
	{
		infile1.close();
		if(!SetCurrentDirectory(array2))  // 
		{
			if(!MoveFile(array1,array2))
				cout<<"�ļ�"<<array2<<"�Ѵ��ڣ��޷�ִ�в���"<<endl;
			GetCurrentDirectory(100,path);
			if(is_login)
			{
				printf("[%s@LAPTOP-TB7M6EQ2 %s]#",getUsername(),path);
			}   
			else
			{
				printf("%s>",path);
			} 
		}
		else
		{
			if(!MoveFile(array1,path2))
				cout<<"Ŀ¼"<<array2<<"�����ڣ��޷�ִ�в���"<<endl;
			GetCurrentDirectory(100,path);
			if(is_login)
			{
				printf("[%s@LAPTOP-TB7M6EQ2 %s]#",getUsername(),path);
			}   
			else
			{
				printf("%s>",path);
			} 
		}
	}
}
/*sort����*/
void cmd_sort(char *array)
{
	int lnum=0,min;
	char line[100][100],tmp[100];//������ÿ���ַ���
	string s[100];
	GetCurrentDirectory(100,path);
	strcat(path,"\\");
	strcat(path,array);
	ifstream infile(path);
	if(!infile)
	{
		cout<<"�޷����ļ�"<<array<<endl;
		GetCurrentDirectory(100,path);
		if(is_login)
		{
			printf("[%s@LAPTOP-TB7M6EQ2 %s]#",getUsername(),path);
		}   
		else
		{
			printf("%s>",path);
		} 
	}
	else
	{
		while(!infile.eof())
		{
			infile.getline(line[lnum],100,'\n');
			lnum++;//��¼������
		}
		infile.close();
		for(int x=0;x<lnum-1;x++)   //����ascii���С����Ƚ�ÿ���ַ��� 
		{
			min=x;
			for(int y=x+1;y<lnum;y++)
				if(strcmp(line[y],line[min])<0)
					min=y;
				if(min!=x) //min�ı䣬�ͽ������ַ����н��� 
				{
					for(int a=0;a<100;a++)
					{
						tmp[a]=line[x][a];
						line[x][a]=line[min][a];
						line[min][a]=tmp[a];
					}
				}
		}
		ofstream outfile(path,ios::out);
		if(!outfile)
		{
			cout<<"�ļ���ʧ��"<<endl;
		}
		else
		{
			for(int c=0;c<lnum;c++)
				outfile<<line[c]<<endl;
			outfile.close();
		}
		GetCurrentDirectory(100,path);
		if(is_login)
		{
			printf("[%s@LAPTOP-TB7M6EQ2 %s]#",getUsername(),path);
		}   
		else
		{
			printf("%s>",path);
		} 
	}
}
/******************************************************����Ϊ������******************************************************/	
int main()
{
	char * input,*arg[4],c;
	int input_len=0,i,j,k,m,n,count,label,label2,label3;
	cout<<"*******************************************************************************"<<endl<<endl;
	cout<<"    �˳��������Linux��ls,cat,cp,mv,mkdir,rmdir,cd,sort,more�����ӭʹ��!    "<<endl<<endl;
	cout<<"*******************************************************************************"<<endl;
	SetCurrentDirectory("C:\\");//��Ĭ��·����Ϊc�̸�Ŀ¼
	GetCurrentDirectory(100,path);//��һ����������װ�ص�ǰĿ¼����windows,ͷ�ļ��� 
	printf("%s>",path); 
	while(1)  
	{
		for(i=0;i<2;i++)
		arg[i]=NULL;
		while((c=getchar())==' ' || c=='\t' || c==EOF||c=='\n')//��������
		{
			if(c=='\n')
			{   
				if(is_login)
				{
					printf("[%s@LAPTOP-TB7M6EQ2 %s]#",getUsername(),path);
				}   
				else
				{
					printf("%s>",path);
				} 
				continue;
			}
			
		}
		while(c!='\n')
		{
			buf[input_len++]=c;
			c=getchar();
		}
		buf[input_len++]='\0';
		input=new char[input_len];    
		strcpy(input,buf);//������ӻ��渴�Ƶ�input��
/**********************************************����������ɣ�����+[����]����ʽ*******************************************/
		for(i=0,j=0,k=0;i<input_len;i++)//�˴����������arg[0],������������µ�if�����д���
		{
			if((input[i]==' ' || input[i]=='\0')&&(k==0))
			{
				if(j==0)          //ȥ������һ��Ķ���ո�
					continue;
				else
				{
					buf[j++]='\0';
					arg[k]=new char[j];
					strcpy(arg[k++],buf);
					j=0;          //׼��ȡ��һ������
				}
			}
			else
				buf[j++]=input[i];
		}
	   
/********************cd����********************/
		if(strcmp(arg[0],"cd")==0)
		{
			for(i=3;(input[i]==' ')&&(i<=input_len);i++)
			{
				continue;
			}
			if(i==input_len)//������cd���ظ�Ŀ¼(linux����)
			{
				SetCurrentDirectory("C:\\");
				GetCurrentDirectory(100,path);
				if(is_login)
				{
					printf("[%s@LAPTOP-TB7M6EQ2 %s]#",getUsername(),path);
				}   
				else
				{
					printf("%s>",path);
				} 
			}
			else
			{
				label3=0;
				for(int m=i;m<=input_len;m++)//��ȡcd����Ĳ���
					buf[label3++]=input[m];
				buf[label3]='\0';
				arg[1]=new char[label3+1];
				strcpy(arg[1],buf);//�������浽arg[1]��
				cd_cmd(arg[1]);
			}
			delete(input);
			delete(arg[0]);
			delete(arg[1]);
			input_len=0;
		}
/*********************ls����*******************/
		else if(strcmp(arg[0],"ls")==0)
		{
			for(i=3;(input[i]==' ')&&(i<=input_len);i++)
			{
				continue;
			}
			if(i==input_len)//ls�޲�
				ls_cmd(arg[0]);
			else			//ls�в�
			{
				label3=0;
				for(int m=i;m<=input_len;m++)//��ȡls����Ĳ���
					buf[label3++]=input[m];
				buf[label3]='\0';
				arg[1]=new char[label3+1];
				strcpy(arg[1],buf);//�������浽arg[1]��
				if(strcmp(arg[1], "--help" )==0)
				{
					cout<<PRINTLSHELP<<endl;
					GetCurrentDirectory(100,path);
					if(is_login)
					{
						printf("[%s@LAPTOP-TB7M6EQ2 %s]#",getUsername(),path);
					}   
					else
					{
						printf("%s>",path);
					} 
				}
				else if(strcmp(arg[1], "-l")==0)
				{
					ls_cmd(arg[1]);
				}
				else 
				{
					cout<<"��Ч������!"<<endl;
					GetCurrentDirectory(100,path);
					if(is_login)
					{
						printf("[%s@LAPTOP-TB7M6EQ2 %s]#",getUsername(),path);
					}   
					else
					{
						printf("%s>",path);
					} 
				}
					//ls_cmd(arg[1]);
			}
			delete(input);
			delete(arg[0]);
			delete(arg[1]);
			input_len=0;
		}
/********************mkdir����********************/
		else if(strcmp(arg[0],"mkdir")==0)
		{
			for(i=6;(input[i]==' ')&&(i<=input_len);i++)
			{
				continue;
			}
			if(i==input_len)//mkdir�޲�
			{
				cout<<"mkdir������̫��"<<'\n'<<"�볢��ִ��mkdir --help����ȡ������Ϣ"<<endl;
				GetCurrentDirectory(100,path);
				if(is_login)
				{
					printf("[%s@LAPTOP-TB7M6EQ2 %s]#",getUsername(),path);
				}   
				else
				{
					printf("%s>",path);
				} 
			}
			else
			{
				label3=0;
				for(int m=i;m<=input_len;m++)//��ȡmkdir����Ĳ���
					buf[label3++]=input[m];
				buf[label3]='\0';
				arg[1]=new char[label3+1];
				strcpy(arg[1],buf);//�������浽arg[1]��
				if(strcmp(arg[1],"--help")==0)
				{
					cout<<PRINTMKDIRHELP<<endl;
					GetCurrentDirectory(100,path);
					if(is_login)
					{
						printf("[%s@LAPTOP-TB7M6EQ2 %s]#",getUsername(),path);
					}   
					else
					{
						printf("%s>",path);
					} 
				}
				else
				{
					mkdir_cmd(arg[1]);
				}
			}
				delete(input);
				delete(arg[0]);
				delete(arg[1]);
				input_len=0;
		}
/********************rmdir����********************/
		else if(strcmp(arg[0],"rmdir")==0)
		{
			for(i=6;(input[i]==' ')&&(i<=input_len);i++)
			{
				continue;
			}
			if(i==input_len)//rmdir�޲�
			{
				cout<<"rmdir������̫��"<<'\n'<<"�볢��ִ��rmdir --help����ȡ������Ϣ"<<endl;
				GetCurrentDirectory(100,path);
				if(is_login)
				{
					printf("[%s@LAPTOP-TB7M6EQ2 %s]#",getUsername(),path);
				}   
				else
				{
					printf("%s>",path);
				} 
			}
			else
			{	label3=0;
				for(int m=i;m<=input_len;m++)//��ȡmkdir����Ĳ���
					buf[label3++]=input[m];
				buf[label3]='\0';
				arg[1]=new char[label3+1];
				strcpy(arg[1],buf);//�������浽arg[1]��
				if(strcmp(arg[1],"--help")==0)
				{
					cout<<PRINTRMDIRHELP<<endl;
					GetCurrentDirectory(100,path);
					if(is_login)
					{
						printf("[%s@LAPTOP-TB7M6EQ2 %s]#",getUsername(),path);
					}   
					else
					{
						printf("%s>",path);
					} 
				}
				else
				{
					rmdir_cmd(arg[1]);
				}
			}
				delete(input);
				delete(arg[0]);
				delete(arg[1]);
				input_len=0;
		}
/********************cp����********************/
		else if(strcmp(arg[0],"cp")==0)
		{
			for(i=3;(input[i]==' ')&&(i<=input_len);i++)
			{
				continue;
			}
			if(i==input_len)//rmdir�޲�
			{
				cout<<"cp��ȱ�����ļ�����"<<'\n'<<"�볢��ִ��cp --help����ȡ������Ϣ"<<endl;
				GetCurrentDirectory(100,path);
				if(is_login)
				{
					printf("[%s@LAPTOP-TB7M6EQ2 %s]#",getUsername(),path);
				}   
				else
				{
					printf("%s>",path);
				} 
			}
			else
			{
				label3=0;
				for(int m=i;(input[m]!=' ')&&(m<=input_len);m++)
				{
					buf[label3++]=input[m];
					count=m;
				}
				buf[label3]='\0';
				arg[1]=new char[label3+1];
				strcpy(arg[1],buf);//��Դ�ļ����浽arg[1]��
				if(count==input_len)//cpֻ��һ������
				{
					if(strcmp(arg[1],"--help")==0)
					{
						cout<<PRINTCPHELP<<endl;
						GetCurrentDirectory(100,path);
						if(is_login)
						{
							printf("[%s@LAPTOP-TB7M6EQ2 %s]#",getUsername(),path);
						}   
						else
						{
							printf("%s>",path);
						} 
					}
					else
					{
						cout<<"cp��ȱ����Ŀ���ļ�"<<'\n'<<"�볢��ִ��cp --help����ȡ������Ϣ"<<endl;
						GetCurrentDirectory(100,path);
						if(is_login)
						{
							printf("[%s@LAPTOP-TB7M6EQ2 %s]#",getUsername(),path);
						}   
						else
						{
							printf("%s>",path);
						} 
					}
				}
				else			//cp����������
				{
					label=0;
					for(int n=count+2;n<=input_len;n++)//��ȡĿ���ļ���
						buf[label++]=input[n];
					buf[label]='\0';
					arg[2]=new char[label+1];
					strcpy(arg[2],buf);//��Ŀ���ļ����浽arg[2]��
					printf("%s",arg[2]);
					cp_cmd(arg[1],arg[2]);		
				}
			}
				delete(input);
				delete(arg[0]);
				input_len=0;
		}

/*********************cat����*******************/
		else if(strcmp(arg[0],"cat")==0)   // str1==str2 �򷵻�0 
		{
			for(i=4;(input[i]==' ')&&(i<=input_len);i++)
			{
				continue;
			}
			if(i==input_len)//cat�޲�
			{
				cout<<"cat��ȱ�����ļ�����"<<'\n'<<"�볢��ִ��cat --help����ȡ������Ϣ"<<endl;
				GetCurrentDirectory(100,path);
				if(is_login)
				{
					printf("[%s@LAPTOP-TB7M6EQ2 %s]#",getUsername(),path);
				}   
				else
				{
					printf("%s>",path);
				} 
			}
			else		//cat�в�
			{
				label3=0;
				for(int m=i;(input[m]!=' ')&&(m<=input_len);m++)//��ȡcat��һ������Ĳ���
				{
					buf[label3++]=input[m];
					count=m;
				} 
				
				buf[label3]='\0';  //�ַ������� 
				arg[1]=new char[label3+1];
				strcpy(arg[1],buf);//��cat��һ�����������浽arg[1]��
				//printf("%d",strcmp(arg[1],"--help"));
				//printf("%d",input_len); 
				if(count==input_len)    //catֻ��һ������
				{ 
					if(strcmp(arg[1],"--help")==0)
					{
						cout<<PRINTCATHELP<<endl;
						GetCurrentDirectory(100,path);
						if(is_login)
						{
							printf("[%s@LAPTOP-TB7M6EQ2 %s]#",getUsername(),path);
						}   
						else
						{
							printf("%s>",path);
						} 
					}
					else   
					{
						cat_cmd1(arg[1]);
					}
				}
				else//cat ��ֹһ������
				{
					label=0;
					for(int n=count+2;(input[n]!=' ')&&(n<=input_len);n++)//��ȡcat�ڶ�������Ĳ���
					{
						buf[label++]=input[n];
						count=n; 
					}
					buf[label]='\0';	
					arg[2]=new char[label+1];
					strcpy(arg[2],buf);//��cat�ڶ������������浽arg[2]��
					if(count==input_len)//catֻ����������
					{
						cout<<"��Ч������!"<<endl;
						GetCurrentDirectory(100,path);
						if(is_login)
						{
							printf("[%s@LAPTOP-TB7M6EQ2 %s]#",getUsername(),path);
						}   
						else
						{
							printf("%s>",path);
						} 	
					}    
					else//cat����������      
					{
					//	printf("%d",count); 7
					//	printf("%d",input_len); 11
					 	
						if(strcmp(arg[2],">>")==0)  //����ڶ��������� >> 
						{ 
							label2=0;
							for(int p=count+2;p<=input_len;p++)//��ȡcat����������Ĳ���
								buf[label2++]=input[p];
							buf[label2]='\0';
							arg[3]=new char[label2+1];
							strcpy(arg[3],buf);//��cat���������������浽arg[3]��
							cat_cmd2(arg[1],arg[3]);
						}
						else
						{
							cout<<"��Ч������!"<<endl;
							GetCurrentDirectory(100,path);
							if(is_login)
							{
								printf("[%s@LAPTOP-TB7M6EQ2 %s]#",getUsername(),path);
							}   
							else
							{
								printf("%s>",path);
							} 	
						}
					}
				}
			}
			delete(input);
			delete(arg[0]);
			input_len=0;
		}
/*********************more����*******************/
		else if(strcmp(arg[0],"more")==0)
		{
			for(i=5;(input[i]==' ')&&(i<=input_len);i++)
			{
				continue;
			}
			if(i==input_len)//more�޲�
			{
				cout<<"more��ȱ�����ļ�����"<<'\n'<<"�볢��ִ��more --help����ȡ������Ϣ"<<endl;
				GetCurrentDirectory(100,path);
				if(is_login)
				{
					printf("[%s@LAPTOP-TB7M6EQ2 %s]#",getUsername(),path);
				}   
				else
				{
					printf("%s>",path);
				} 
			}
			else			//more�в�
			{
				label3=0;
				for(int m=i;m<=input_len;m++)//��ȡmore����Ĳ���
					buf[label3++]=input[m];
				buf[label3]='\0';
				arg[1]=new char[label3+1];   
				strcpy(arg[1],buf);//�������浽arg[1]��
				if(strcmp(arg[1], "--help" )==0)
				{
					cout<<PRINTMOREHELP<<endl;
					GetCurrentDirectory(100,path);
					if(is_login)
					{
						printf("[%s@LAPTOP-TB7M6EQ2 %s]#",getUsername(),path);
					}   
					else
					{
						printf("%s>",path);
					} 
				}
				else
				{
					more_cmd(arg[1]);
				}
			}
			delete(input);
			delete(arg[0]);
			delete(arg[1]);
			input_len=0;
		}

/*********************mv����*******************/
		else if(strcmp(arg[0],"mv")==0)
		{
			for(i=3;(input[i]==' ')&&(i<=input_len);i++)
			{
				continue;
			}
			if(i==input_len)//mv�޲�
			{
				cout<<"mv��ȱ�����ļ�����"<<'\n'<<"�볢��ִ��mv --help����ȡ������Ϣ"<<endl;
				GetCurrentDirectory(100,path);
				if(is_login)
				{
					printf("[%s@LAPTOP-TB7M6EQ2 %s]#",getUsername(),path);
				}   
				else
				{
					printf("%s>",path);
				} 
			}
			else			//mv�в�
			{
				label3=0;
				for(int m=i;(input[m]!=' ')&&(m<=input_len);m++)//��ȡmv��һ������Ĳ���
				{
					buf[label3++]=input[m];
					count=m;
				}
				buf[label3]='\0';
				arg[1]=new char[label3+1];
				strcpy(arg[1],buf);//��mv��һ�����������浽arg[1]��
				if(count==input_len)//mvֻ��һ������
				{
					if(strcmp(arg[1], "--help" )==0)
					{
						cout<<PRINTMVHELP<<endl;
						GetCurrentDirectory(100,path);
						if(is_login)
						{
							printf("[%s@LAPTOP-TB7M6EQ2 %s]#",getUsername(),path);
						}   
						else
						{
							printf("%s>",path);
						} 
					}
					else
					{
						cout<<"mv��ȱ�����ļ�����"<<'\n'<<"�볢��ִ��mv --help����ȡ������Ϣ"<<endl;
						GetCurrentDirectory(100,path);
						if(is_login)
						{
							printf("[%s@LAPTOP-TB7M6EQ2 %s]#",getUsername(),path);
						}   
						else
						{
							printf("%s>",path);
						} 
					}
				}
				else//mv ��ֹһ������
				{
					label=0;
					for(int n=count+2;(input[n]!=' ')&&(n<=input_len);n++)//��ȡmv�ڶ�������Ĳ���
						{
						buf[label++]=input[n];
						count=n;
					}
					buf[label]='\0';
					arg[2]=new char[label+1];
					strcpy(arg[2],buf);//��mv�ڶ������������浽arg[2]��
					if(count==input_len)//mv����������
					{

						mv_cmd1(arg[1],arg[2]);	
					}
					else//mv����������
					{
						cout<<"mv:��Ч������"<<'\n'<<"�볢��ִ��mv --help����ȡ������Ϣ"<<endl;
						GetCurrentDirectory(100,path);
						if(is_login)
						{
							printf("[%s@LAPTOP-TB7M6EQ2 %s]#",getUsername(),path);
						}   
						else
						{
							printf("%s>",path);
						} 
					}
				}
			}
			delete(input);
			delete(arg[0]);
			input_len=0;
		}
/*********************sort����*******************/
		else if(strcmp(arg[0],"sort")==0)
		{
			for(i=5;(input[i]==' ')&&(i<=input_len);i++)
			{
				continue;
			}
			if(i==input_len)//sort�޲�
			{
				cout<<"sort:��Ч������"<<'\n'<<"�볢��ִ��sort --help����ȡ������Ϣ"<<endl;
				GetCurrentDirectory(100,path);
				if(is_login)
				{
					printf("[%s@LAPTOP-TB7M6EQ2 %s]#",getUsername(),path);
				}   
				else
				{
					printf("%s>",path);
				} 
			}
			else			//sort�в�
			{
				label3=0;
				for(int m=i;m<=input_len;m++)//��ȡsort����Ĳ���
					buf[label3++]=input[m];
				buf[label3]='\0';
				arg[1]=new char[label3+1];
				strcpy(arg[1],buf);//�������浽arg[1]��
				if(strcmp(arg[1], "--help" )==0)
				{
					cout<<PRINTSORTHELP<<endl;
					GetCurrentDirectory(100,path);
					if(is_login)
					{
						printf("[%s@LAPTOP-TB7M6EQ2 %s]#",getUsername(),path);
					}   
					else
					{
						printf("%s>",path);
					} 
				}
				else
				{
					cmd_sort(arg[1]);
				}
			}
			delete(input);
			delete(arg[0]);
			delete(arg[1]);
			input_len=0;
		}
		else if(strcmp(arg[0],"Login")==0)
		{
			Login();  //��¼���� 
			GetCurrentDirectory(100,path);
			if(is_login)
			{
				printf("[%s@LAPTOP-TB7M6EQ2 %s]#",getUsername(),path);
			}   
			else
			{
				printf("%s>",path);
			} 
			delete(arg[0]);
			delete(input);
			input_len=0;
		 }
		 else if(strcmp(arg[0],"Logout")==0)
		 {
		 	Logout();
		 	printf("%s>",path);
		 	delete(arg[0]);
			delete(input);
			input_len=0;
		 }
		 else if(strcmp(arg[0],"passwd")==0)
		 {
		 	for(i=7;(input[i]==' ')&&(i<=input_len);i++)
			{
				continue;
			}
			if(i==input_len)//cat�޲�
			{
				cout<<"cat��ȱ���˲���"<<'\n'<<"�볢��ִ��password --help����ȡ������Ϣ"<<endl;
				GetCurrentDirectory(100,path);
				if(is_login)
				{
					printf("[%s@LAPTOP-TB7M6EQ2 %s]#",getUsername(),path);
				}   
				else
				{
					printf("%s>",path);
				} 
			}
			else		//cat�в�
			{
				label3=0;
				for(int m=i;(input[m]!=' ')&&(m<=input_len);m++)//��ȡpasswd��һ������Ĳ���
				{
					buf[label3++]=input[m];
					count=m;
				} 
				
				buf[label3]='\0';  //�ַ������� 
				arg[1]=new char[label3+1];
				strcpy(arg[1],buf);//��passwd��һ�����������浽arg[1]��
				//printf("%d",strcmp(arg[1],"--help"));
				//printf("%d",input_len); 
				if(count==input_len)    //passwdֻ��һ������
				{ 
					if(strcmp(arg[1],"--help")==0)
					{
						cout<<PRINTPASSWDHELP<<endl;
						GetCurrentDirectory(100,path);
						if(is_login)
						{
							printf("[%s@LAPTOP-TB7M6EQ2 %s]#",getUsername(),path);
						}   
						else
						{
							printf("%s>",path);
						} 
					}
					else   
					{
						cat_cmd1(arg[1]);
					}
				}  
				else//passwd ��ֹһ������
				{
					label=0;
					for(int n=count+2;(input[n]!=' ')&&(n<=input_len);n++)//��ȡpasswd�ڶ�������Ĳ���
					{
						buf[label++]=input[n];
						count=n; 
					}
					buf[label]='\0';	
					arg[2]=new char[label+1];
					strcpy(arg[2],buf);//��passwd�ڶ������������浽arg[2]��
					if(count==input_len)//passwdֻ����������
					{
						
						GetCurrentDirectory(100,path);
						if(is_login)
						{
							printf("[%s@LAPTOP-TB7M6EQ2 %s]#",getUsername(),path);
						}   
						else
						{
							printf("%s>",path);
						} 	
					}
					else
					{
						cout<<"��Ч����"<<endl;
						GetCurrentDirectory(100,path);
						if(is_login)
						{
							printf("[%s@LAPTOP-TB7M6EQ2 %s]#",getUsername(),path);
						}   
						else
						{
							printf("%s>",path);
						} 
					}
				} 
			} 
		}
		else
		{   
			cout<<"��Ч������!"<<endl;
			GetCurrentDirectory(100,path);
			if(is_login)
			{
				printf("[%s@LAPTOP-TB7M6EQ2 %s]#",getUsername(),path);
			}   
			else
			{
				printf("%s>",path);
			}
			delete(input);   
			delete(arg[0]);
			input_len=0;
			continue;
		}
	}
	return 0;
}
