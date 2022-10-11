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
#include<unistd.h>   //对POSIX操作系统API的访问功能的头文件的名称
#include<lm.h>  // 
using namespace std;
#pragma comment(lib,"netapi32.lib")
#pragma comment(lib, "Wtsapi32.lib")
#pragma comment(lib, "Userenv.lib")
char buf[100],path[100],path1[100],path2[100];//全局变量，buf用于缓存数据，3个path用于保存路径
bool is_login=0;   //是否登录 
#define G_LEN_CMD_LINE  1024    //命令行最大长度
// 计算wchar_t 数组的size, 以wchar_t为单位
#define SIZE_OF_WCHAR_ARRAY(x) (sizeof(x) / sizeof(wchar_t))
/***************************************************以下为各命令的帮助文档***********************************************/
#define PRINTLSHELP		"用法：ls  [选项]\n\
列出文件信息(默认为当前目录)\n\
ls无参         显示一个目录中的文件和子目录\n\
ls -l          每行仅显示一个目录或名称\n\
ls --help      显示此帮助信息并离开"
#define PRINTPASSWDHELP "用法：passwd [选项]\n\
若用户不存在     显示用户不存在\n\
passwd 用户名    设置[用户名]的密码\n\
passwd -s 用户名 显示账号密码信息\n\
passwd -d 用户名 删除用户密码\n\
passwd --help    显示此帮助信息并且离开" 
#define PRINTMKDIRHELP	"用法：mkdir  目录\n\
若目录不存在则创建目录\n\
mkdir --help   显示此帮助信息并离开"
#define PRINTRMDIRHELP		"用法：rmdir  目录\n\
若目录没有数据则删除目录\n\
rmdir --help   显示此帮助信息并离开"
#define PRINTCPHELP		"用法：cp  来源文件 目的文件\n\
将来源文件复制到目的文件\n\
cp --help   显示此帮助信息并离开"
#define PRINTCATHELP	"用法：cat  文件\n\
  或：cat  文件1 >> 文件2\n\
显示文件内容或连接两个文件，并将结果输出到显示屏上\n\
cat 文件            将文件的内容输出到显示屏上\n\
cat 文件1 >> 文件2  将文件1连接到文件2的结尾，并输出到显示屏上\n\
cat --help          显示此帮助信息并离开"
#define PRINTMOREHELP		"用法：more  文件\n\
使文件能逐行(回车键)或逐页(空格键)显示并显示当前文件所占总文件的百分比\n\
more --help		显示此帮助信息并离开"
#define PRINTMVHELP		"用法：mv 文件1 文件2\n\
  或：mv 文件 目录(格式为：要移动到的目录的绝对路径+要移动的文件)\n\
重命名或移动文件\n\
mv  文件1  文件2         将文件1名字改为文件2的名字\n\
mv  文件   目录          将指定文件移动到指定目录下\n\
mv --help                显示此帮助信息并离开"
#define PRINTSORTHELP		"用法：sort 文件\n\
将文本文件内容加以排序\n\
sort --help       显示此帮助信息并离开"
/*******************************************以下为各命令的具体实现函数***************************************************/
char* getUsername()  //获取当前用户名称 
{
    DWORD size=UNLEN+1;
    char buf[size];
    GetUserName(buf, &size);
    return buf;
}
/*cd命令*/
void cd_cmd(char * route)
{
	if(!SetCurrentDirectory(route))
	{	
		cout<<"路径不存在!"<<endl;
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
* 功能    切换用户权限，用户输入账号密码
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
//    // 循环，直到可以成功调用 NetUserEnum  
//    do
//    {
//        // 调用NetUserEnum函数  
//        nStatus = NetUserEnum(pszServerName,
//            dwLevel,// 这里设置为0，使用 LPUSER_INFO_0 返回结果  
//            FILTER_NORMAL_ACCOUNT, // 只列举“正常”类型的用户  
//            (LPBYTE*)&pBuf,// LPUSER_INFO_0 保存返回结果  
//            // MAX_PREFERRED_LENGTH，内存由API分配，需要在之后调用NetApiBufferFree释放  
//            dwPrefMaxLen,
//            &dwEntriesRead,// 读了的 Entries  
//            &dwTotalEntries,// 一共的 Entries  
//            &dwResumeHandle);
//        // 判断是否成功  
//        if ((nStatus == NERR_Success) || (nStatus == ERROR_MORE_DATA))
//        {
//            if ((pTmpBuf = pBuf) != NULL)
//            {
//                // 循环读取用户信息  
//                for (i = 0; (i < dwEntriesRead); i++)
//                {
//                    assert(pTmpBuf != NULL);
//                    if (pTmpBuf == NULL)
//                    {
//                        fprintf(stderr, "An access violation has occurred\n");
//                        break;
//                    }
//                    // 输出  
//                    wprintf(L"\t-- %s\n", pTmpBuf->usri0_name);
//                    // 下一个  
//                    pTmpBuf++;
//                    dwTotalCount++;
//                }
//            }
//        }
//        else
//            fprintf(stderr, "A system error has occurred: %d\n", nStatus);
//        // 释放内存  
//        if (pBuf != NULL)
//        {
//            NetApiBufferFree(pBuf);
//            pBuf = NULL;
//        }
//    } while (nStatus == ERROR_MORE_DATA); // end do  
//
//    // 释放内存  
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
		cout << "文件" << fileNamePath << "打开失败或者不存在！" << endl;
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
		c = getch(); //从控制台读取一个字符但是不显示 
		if (c == '\n' || c == '\r')  //windows下getch输入回车会返回\r\n
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
/*logout命令*/
void Logout()
{
	is_login=0;  
 } 
 /*修改密码*/ 
 void passwd() 
 {
 	
  } 
/*ls命令*/
void ls_cmd(char *array)
{
	HANDLE	handle;
	int filenum=0;
	FILETIME lpCreationTime,lpLastAccessTime,lpLastWriteTime;
	SYSTEMTIME stime;
	WIN32_FIND_DATA* path2 = new WIN32_FIND_DATA();
	if(!GetCurrentDirectory(50,path1))
	{
		cout<<"路径不存在!"<<endl;
		return;
	}

	strcat(path1,"\\*.*");        //DOS通配符
	if((handle = FindFirstFile(path1, path2)) != INVALID_HANDLE_VALUE)
	{
		do{
			HANDLE hDir = CreateFile(path2->cFileName,GENERIC_READ,FILE_SHARE_READ | FILE_SHARE_DELETE,NULL,OPEN_EXISTING,FILE_FLAG_BACKUP_SEMANTICS,  NULL);  
			if(GetFileTime(hDir,  &lpCreationTime,  &lpLastAccessTime,  &lpLastWriteTime)){  
				FILETIME  ftime;  
				FileTimeToLocalFileTime(&lpLastWriteTime,  &ftime);  //  转换成本地时间  
				FileTimeToSystemTime(&ftime,  &stime);  //  转换成系统时间格式  
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
/*mkdir命令*/
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
		cout<<"该目录已存在，创建失败!"<<endl;
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
/*rmdir命令*/
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
		cout<<"该目录不存在，删除失败!"<<endl;
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
/*cp命令*/
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
		cout<<"复制失败，没有那个文件或目录!"<<endl;
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
		CopyFile(array1,array2,FALSE);//FALSE作用：如果目的文件存在，则覆盖掉
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
/*cat命令*/
void cat_cmd1(char *array)//用于显示文件
{
	char ch[1000];
	GetCurrentDirectory(100,path);
	strcat(path,"\\");
	strcat(path,array);
	ifstream infile(path);
	if(!infile)
	{
		cout<<"无法打开文件"<<path<<endl;
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
 
void cat_cmd2(char *array1,char *array2)//用于连接并显示文件
{ 
	char ch[1000];
	char ch2[1000];
	GetCurrentDirectory(100,path);//保存cat操作之前的路径
	GetCurrentDirectory(100,path1);
	strcat(path1,"\\");
	GetCurrentDirectory(100,path2);
	strcat(path1,array1);
	ifstream infile1(path1);
	if(!infile1)
	{
		cout<<"无法打开文件"<<path1<<endl;
		GetCurrentDirectory(100,path1);
		printf("%s>",path1);
	}
	else
	{
		strcat(path2,array2);
		ofstream outfile2(path2,ios::app);
		if(!outfile2)
		{
			cout<<"无法打开文件"<<path2<<endl;
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
/*more命令*/
void more_cmd(char *array)
{
	char ch[1000];
	GetCurrentDirectory(100,path);
	strcat(path,"\\");
	strcat(path,array);
	ifstream infile(path);
	if(!infile)
	{
		cout<<"无法打开文件"<<path<<endl;
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
		int count1=0,count2=0,l;//count1用于显示文件总行数，count2用于显示当前读到的文件行数
		while(!infile.eof())
		{
			infile.getline(ch,1000,'\n');
			count1++;
		}
		infile.clear();//不用clear，之前的文件状态属性不会变化
		infile.seekg(0,ios::beg);//把流指针重新定位到文件头
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
				else if(getchar()==32)//输入两次空格，一次回车
				{
					if(cin.get()=='\n')//不加此判断条件，会把回车符解释成逐行显示文件的命令
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
/*mv命令*/	
void mv_cmd1(char *array1,char *array2)
{
	GetCurrentDirectory(100,path);
	GetCurrentDirectory(100,path1);
	strcat(path1,"\\");
	strcat(path1,array1);
	ifstream infile1(path1);
	if(!infile1)
	{
		cout<<"文件"<<array1<<"不存在，无法执行操作"<<endl;
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
				cout<<"文件"<<array2<<"已存在，无法执行操作"<<endl;
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
				cout<<"目录"<<array2<<"不存在，无法执行操作"<<endl;
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
/*sort命令*/
void cmd_sort(char *array)
{
	int lnum=0,min;
	char line[100][100],tmp[100];//行数、每行字符数
	string s[100];
	GetCurrentDirectory(100,path);
	strcat(path,"\\");
	strcat(path,array);
	ifstream infile(path);
	if(!infile)
	{
		cout<<"无法打开文件"<<array<<endl;
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
			lnum++;//记录总行数
		}
		infile.close();
		for(int x=0;x<lnum-1;x++)   //按照ascii码从小到大比较每行字符串 
		{
			min=x;
			for(int y=x+1;y<lnum;y++)
				if(strcmp(line[y],line[min])<0)
					min=y;
				if(min!=x) //min改变，就将两行字符进行交换 
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
			cout<<"文件打开失败"<<endl;
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
/******************************************************以下为主函数******************************************************/	
int main()
{
	char * input,*arg[4],c;
	int input_len=0,i,j,k,m,n,count,label,label2,label3;
	cout<<"*******************************************************************************"<<endl<<endl;
	cout<<"    此程序兼容了Linux的ls,cat,cp,mv,mkdir,rmdir,cd,sort,more命令，欢迎使用!    "<<endl<<endl;
	cout<<"*******************************************************************************"<<endl;
	SetCurrentDirectory("C:\\");//把默认路径设为c盘根目录
	GetCurrentDirectory(100,path);//在一个缓冲区中装载当前目录，在windows,头文件中 
	printf("%s>",path); 
	while(1)  
	{
		for(i=0;i<2;i++)
		arg[i]=NULL;
		while((c=getchar())==' ' || c=='\t' || c==EOF||c=='\n')//读入命令
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
		strcpy(input,buf);//将命令从缓存复制到input中
/**********************************************把命令解析成：命令+[参数]的形式*******************************************/
		for(i=0,j=0,k=0;i<input_len;i++)//此处将命令存入arg[0],其参数将在以下的if条件中处理
		{
			if((input[i]==' ' || input[i]=='\0')&&(k==0))
			{
				if(j==0)          //去掉连在一起的多个空格
					continue;
				else
				{
					buf[j++]='\0';
					arg[k]=new char[j];
					strcpy(arg[k++],buf);
					j=0;          //准备取下一个参数
				}
			}
			else
				buf[j++]=input[i];
		}
	   
/********************cd命令********************/
		if(strcmp(arg[0],"cd")==0)
		{
			for(i=3;(input[i]==' ')&&(i<=input_len);i++)
			{
				continue;
			}
			if(i==input_len)//仅输入cd返回根目录(linux特有)
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
				for(int m=i;m<=input_len;m++)//获取cd命令的参数
					buf[label3++]=input[m];
				buf[label3]='\0';
				arg[1]=new char[label3+1];
				strcpy(arg[1],buf);//将参数存到arg[1]中
				cd_cmd(arg[1]);
			}
			delete(input);
			delete(arg[0]);
			delete(arg[1]);
			input_len=0;
		}
/*********************ls命令*******************/
		else if(strcmp(arg[0],"ls")==0)
		{
			for(i=3;(input[i]==' ')&&(i<=input_len);i++)
			{
				continue;
			}
			if(i==input_len)//ls无参
				ls_cmd(arg[0]);
			else			//ls有参
			{
				label3=0;
				for(int m=i;m<=input_len;m++)//获取ls命令的参数
					buf[label3++]=input[m];
				buf[label3]='\0';
				arg[1]=new char[label3+1];
				strcpy(arg[1],buf);//将参数存到arg[1]中
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
					cout<<"无效的命令!"<<endl;
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
/********************mkdir命令********************/
		else if(strcmp(arg[0],"mkdir")==0)
		{
			for(i=6;(input[i]==' ')&&(i<=input_len);i++)
			{
				continue;
			}
			if(i==input_len)//mkdir无参
			{
				cout<<"mkdir：参数太少"<<'\n'<<"请尝试执行mkdir --help来获取更多信息"<<endl;
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
				for(int m=i;m<=input_len;m++)//获取mkdir命令的参数
					buf[label3++]=input[m];
				buf[label3]='\0';
				arg[1]=new char[label3+1];
				strcpy(arg[1],buf);//将参数存到arg[1]中
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
/********************rmdir命令********************/
		else if(strcmp(arg[0],"rmdir")==0)
		{
			for(i=6;(input[i]==' ')&&(i<=input_len);i++)
			{
				continue;
			}
			if(i==input_len)//rmdir无参
			{
				cout<<"rmdir：参数太少"<<'\n'<<"请尝试执行rmdir --help来获取更多信息"<<endl;
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
				for(int m=i;m<=input_len;m++)//获取mkdir命令的参数
					buf[label3++]=input[m];
				buf[label3]='\0';
				arg[1]=new char[label3+1];
				strcpy(arg[1],buf);//将参数存到arg[1]中
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
/********************cp命令********************/
		else if(strcmp(arg[0],"cp")==0)
		{
			for(i=3;(input[i]==' ')&&(i<=input_len);i++)
			{
				continue;
			}
			if(i==input_len)//rmdir无参
			{
				cout<<"cp：缺少了文件参数"<<'\n'<<"请尝试执行cp --help来获取更多信息"<<endl;
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
				strcpy(arg[1],buf);//将源文件名存到arg[1]中
				if(count==input_len)//cp只有一个参数
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
						cout<<"cp：缺少了目的文件"<<'\n'<<"请尝试执行cp --help来获取更多信息"<<endl;
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
				else			//cp有两个参数
				{
					label=0;
					for(int n=count+2;n<=input_len;n++)//获取目的文件名
						buf[label++]=input[n];
					buf[label]='\0';
					arg[2]=new char[label+1];
					strcpy(arg[2],buf);//将目的文件名存到arg[2]中
					printf("%s",arg[2]);
					cp_cmd(arg[1],arg[2]);		
				}
			}
				delete(input);
				delete(arg[0]);
				input_len=0;
		}

/*********************cat命令*******************/
		else if(strcmp(arg[0],"cat")==0)   // str1==str2 则返回0 
		{
			for(i=4;(input[i]==' ')&&(i<=input_len);i++)
			{
				continue;
			}
			if(i==input_len)//cat无参
			{
				cout<<"cat：缺少了文件参数"<<'\n'<<"请尝试执行cat --help来获取更多信息"<<endl;
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
			else		//cat有参
			{
				label3=0;
				for(int m=i;(input[m]!=' ')&&(m<=input_len);m++)//获取cat第一个命令的参数
				{
					buf[label3++]=input[m];
					count=m;
				} 
				
				buf[label3]='\0';  //字符串结束 
				arg[1]=new char[label3+1];
				strcpy(arg[1],buf);//将cat第一个参数参数存到arg[1]中
				//printf("%d",strcmp(arg[1],"--help"));
				//printf("%d",input_len); 
				if(count==input_len)    //cat只有一个参数
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
				else//cat 不止一个参数
				{
					label=0;
					for(int n=count+2;(input[n]!=' ')&&(n<=input_len);n++)//获取cat第二个命令的参数
					{
						buf[label++]=input[n];
						count=n; 
					}
					buf[label]='\0';	
					arg[2]=new char[label+1];
					strcpy(arg[2],buf);//将cat第二个参数参数存到arg[2]中
					if(count==input_len)//cat只有两个参数
					{
						cout<<"无效的命令!"<<endl;
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
					else//cat有三个参数      
					{
					//	printf("%d",count); 7
					//	printf("%d",input_len); 11
					 	
						if(strcmp(arg[2],">>")==0)  //如果第二个参数是 >> 
						{ 
							label2=0;
							for(int p=count+2;p<=input_len;p++)//获取cat第三个命令的参数
								buf[label2++]=input[p];
							buf[label2]='\0';
							arg[3]=new char[label2+1];
							strcpy(arg[3],buf);//将cat第三个参数参数存到arg[3]中
							cat_cmd2(arg[1],arg[3]);
						}
						else
						{
							cout<<"无效的命令!"<<endl;
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
/*********************more命令*******************/
		else if(strcmp(arg[0],"more")==0)
		{
			for(i=5;(input[i]==' ')&&(i<=input_len);i++)
			{
				continue;
			}
			if(i==input_len)//more无参
			{
				cout<<"more：缺少了文件参数"<<'\n'<<"请尝试执行more --help来获取更多信息"<<endl;
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
			else			//more有参
			{
				label3=0;
				for(int m=i;m<=input_len;m++)//获取more命令的参数
					buf[label3++]=input[m];
				buf[label3]='\0';
				arg[1]=new char[label3+1];   
				strcpy(arg[1],buf);//将参数存到arg[1]中
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

/*********************mv命令*******************/
		else if(strcmp(arg[0],"mv")==0)
		{
			for(i=3;(input[i]==' ')&&(i<=input_len);i++)
			{
				continue;
			}
			if(i==input_len)//mv无参
			{
				cout<<"mv：缺少了文件参数"<<'\n'<<"请尝试执行mv --help来获取更多信息"<<endl;
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
			else			//mv有参
			{
				label3=0;
				for(int m=i;(input[m]!=' ')&&(m<=input_len);m++)//获取mv第一个命令的参数
				{
					buf[label3++]=input[m];
					count=m;
				}
				buf[label3]='\0';
				arg[1]=new char[label3+1];
				strcpy(arg[1],buf);//将mv第一个参数参数存到arg[1]中
				if(count==input_len)//mv只有一个参数
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
						cout<<"mv：缺少了文件参数"<<'\n'<<"请尝试执行mv --help来获取更多信息"<<endl;
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
				else//mv 不止一个参数
				{
					label=0;
					for(int n=count+2;(input[n]!=' ')&&(n<=input_len);n++)//获取mv第二个命令的参数
						{
						buf[label++]=input[n];
						count=n;
					}
					buf[label]='\0';
					arg[2]=new char[label+1];
					strcpy(arg[2],buf);//将mv第二个参数参数存到arg[2]中
					if(count==input_len)//mv有两个参数
					{

						mv_cmd1(arg[1],arg[2]);	
					}
					else//mv有三个参数
					{
						cout<<"mv:无效的命令"<<'\n'<<"请尝试执行mv --help来获取更多信息"<<endl;
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
/*********************sort命令*******************/
		else if(strcmp(arg[0],"sort")==0)
		{
			for(i=5;(input[i]==' ')&&(i<=input_len);i++)
			{
				continue;
			}
			if(i==input_len)//sort无参
			{
				cout<<"sort:无效的命令"<<'\n'<<"请尝试执行sort --help来获取更多信息"<<endl;
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
			else			//sort有参
			{
				label3=0;
				for(int m=i;m<=input_len;m++)//获取sort命令的参数
					buf[label3++]=input[m];
				buf[label3]='\0';
				arg[1]=new char[label3+1];
				strcpy(arg[1],buf);//将参数存到arg[1]中
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
			Login();  //登录函数 
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
			if(i==input_len)//cat无参
			{
				cout<<"cat：缺少了参数"<<'\n'<<"请尝试执行password --help来获取更多信息"<<endl;
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
			else		//cat有参
			{
				label3=0;
				for(int m=i;(input[m]!=' ')&&(m<=input_len);m++)//获取passwd第一个命令的参数
				{
					buf[label3++]=input[m];
					count=m;
				} 
				
				buf[label3]='\0';  //字符串结束 
				arg[1]=new char[label3+1];
				strcpy(arg[1],buf);//将passwd第一个参数参数存到arg[1]中
				//printf("%d",strcmp(arg[1],"--help"));
				//printf("%d",input_len); 
				if(count==input_len)    //passwd只有一个参数
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
				else//passwd 不止一个参数
				{
					label=0;
					for(int n=count+2;(input[n]!=' ')&&(n<=input_len);n++)//获取passwd第二个命令的参数
					{
						buf[label++]=input[n];
						count=n; 
					}
					buf[label]='\0';	
					arg[2]=new char[label+1];
					strcpy(arg[2],buf);//将passwd第二个参数参数存到arg[2]中
					if(count==input_len)//passwd只有两个参数
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
						cout<<"无效命令"<<endl;
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
			cout<<"无效的命令!"<<endl;
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
