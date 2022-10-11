#include<iostream>
#include<stdio.h> 
#include<conio.h>
#include<windows.h>
#include<stdlib.h>
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

bool cd_cmd(char * route,char * path)
{
	//cd 命令 
//	判断路径是否存在; 
	if(!SetCurrentDirectory(route))
	{	
	
		
		return FALSE;

	}
	else 
	{
		//更改设置当前的路径 
		SetCurrentDirectory(route);
		GetCurrentDirectory(100,path);
		return TRUE;
	}
	
}
//检查是否登录 
int check_Login(char *array,char* fileNamePath,char *username,char * passwd)
{
	
	char data[100];
	//设置用户名和密码的登录文件 
//	const char* fileNamePath = "D:\\account.txt";
	//打开文件 
	ifstream infile;
	infile.open(fileNamePath);
	if (infile.fail()) {
//		cout << "文件" << fileNamePath << "打开失败或者不存在！" << endl;
		return -1;
	} else {
		while (!infile.eof()) {
		
			infile.getline(username,100);
			infile.getline(passwd,100);
			if(strstr(username,array))
			{
				return 1;
			}
		}
	}
//	cout<<"用户名错误："<<endl;
	return 0;
	infile.close();
}

/*more命令*/
 cmd_more(char *array,char output[],char * path,int flag)
{
	char ch[1000];
	GetCurrentDirectory(100,path);
	//对路径进行拼接 
	strcat(path,"\\");
	strcat(path,array);
	ifstream infile(path);
	if(!infile)
	{

		cout<<"无法打开文件"<<path<<endl;
		GetCurrentDirectory(100,path);
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
		int j=0;
		//在每次输出前，把输出内容数组置为零 
		for(int y=0;y<1000;y++){
			output[y]=0;
		}
		if(count1<24)
		{
			for(l=0;l<count1-1;l++)
			{
				//一边输出，一边把输出内容保存到数组 
				infile.getline(ch,1000,'\n');
				if(flag==0){
					cout<<ch<<endl;
				}
				for(int x=0;x<1000;x++){
					output[x]=0;
				}
				for(int p=0;ch[p]!=0;p++){
					output[j]=ch[p];
					j++;
				}
				output[j]='\n';
				j++;

			}
			//获取当前的路径到Path数组里 
			GetCurrentDirectory(100,path);
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

					break;
				}
			}
		}
	}
	infile.close();
}
//sort命令 
int cmd_sort(char *array,char output[],char *path,int flag)
{
	int lnum=0,min;
	char line[100][100],tmp[100];//行数、每行字符数
	string s[100];
	GetCurrentDirectory(100,path);
	strcat(path,"\\");
	strcat(path,array);
	ifstream infile(path);
	//判断文件是否存在 
	if(!infile)
	{

//		cout<<"无法打开文件"<<array<<endl;
		return -1;
		GetCurrentDirectory(100,path);
 
	}
	else
	{
		while(!infile.eof())
		{
			infile.getline(line[lnum],100,'\n');
			lnum++;//记录总行数
		}
		infile.close();
		//按照ascii码从小到大比较每行字符串 
		for(int x=0;x<lnum-1;x++)   
		{
			min=x;
			for(int y=x+1;y<lnum;y++)
				if(strcmp(line[y],line[min])<0)
					min=y;
				//min改变，就将两行字符进行交换 
				{
				if(min!=x) 
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
//			cout<<"文件打开失败"<<endl;
			return -1;
		}
		else
		{
//			line[0][0]=NULL;
			int j=0;
			
			for(int y=0;y<1000;y++){
				output[y]=0;
			}
			//把结果写到文件里面 
			for(int c=1;c<lnum;c++){
				outfile<<line[c]<<endl;

				if(flag==0){
					cout<<line[c]<<endl;
				}
				
				for(int h=0;line[c][h]!=0;h++){
					output[j]=line[c][h];
					j++;
				}
				output[j]='\n';
				j++;
			}
			
			outfile.close();
		}
		GetCurrentDirectory(100,path);
	}
}

//ls命令 
int ls_cmd(char *array,char output[],int flag)
{
	char path1[100]={0};
//	char path2[100]={0}; 
	HANDLE	handle;
	int filenum=0;
	FILETIME lpCreationTime,lpLastAccessTime,lpLastWriteTime;
	SYSTEMTIME stime;
	//调用windows接口 
	WIN32_FIND_DATA* path2 = new WIN32_FIND_DATA();
	 
	if(!GetCurrentDirectory(50,path1))
	{
//		cout<<"路径不存在!"<<endl;
	
		return -1;
	}

	strcat(path1,"\\*.*");        //DOS通配符
	if((handle = FindFirstFile(path1, path2)) != INVALID_HANDLE_VALUE)
	{
		int j=0;
		for(int y=0;y<1000;y++){
			output[y]=0;
		}
		do{
			//调用操作系统句柄 
			HANDLE hDir = CreateFile(path2->cFileName,GENERIC_READ,FILE_SHARE_READ | FILE_SHARE_DELETE,NULL,OPEN_EXISTING,FILE_FLAG_BACKUP_SEMANTICS,  NULL);  
			if(GetFileTime(hDir,  &lpCreationTime,  &lpLastAccessTime,  &lpLastWriteTime)){  
				FILETIME  ftime;  
				FileTimeToLocalFileTime(&lpLastWriteTime,  &ftime);  //  转换成本地时间  
				FileTimeToSystemTime(&ftime,  &stime);  //  转换成系统时间格式  
			}
			//cout<<setfill('0');
			if(strcmp(array,"ls")==0)
			{

				for(int p=0;path2->cFileName[p]!=0;p++){
					output[j]=path2->cFileName[p];
					j++;
				}
				//设置格式化标志来控制输出格式 
				cout.setf(ios::left);
				//每隔三个文件进行一次输出 
				if(filenum%3!=0){
					if(flag==0){
						cout<<setw(20)<<path2->cFileName<<"	";
					}
					
					output[j]='\t';
					j++;
				}
					
				else{
					if(flag==0){
						cout<<setw(20)<<path2->cFileName<<endl;
					}
					
					output[j]='\n';
					j++;
				}
					
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
	//设置当前路径 
	GetCurrentDirectory(100,path1);
	
}

//登出 
void logout(int& is_login){
	//把登录的标志置为0 
	is_login=0;
}

//print命令 
int cmd_print(char *p2,char *p3,char output[],int flag){
	if(p3==NULL){
		if(flag==0){
			//没有格式化字符串，直接打印P2 
			cout<<p2<<endl;
		}
		
		//把输出内容数组置为0 
		for(int i=0;i<1000;i++){
			output[i]=0;
		}
		
		for(int i=0;p2[i]!=0;i++){
			output[i]=p2[i]; 
		}
	}
	else{
		//格式化输出 
		string str1=p2;
		char str2[100]={0};
		int j=0;
		for(int i=0;i<str1.length();i++){
			//去掉格式化输出的 " 字符 
			if(str1[i]!='\"'){
				str2[j]=str1[i];
				j++;
			}	
		}
		
		for(int i=0;i<1000;i++){
			output[i]=0;
		} 
		
		p2=str2;
		//整型格式化输出 
		if(strstr(p2,"%d")){
			if(flag==0){
				printf(p2,atoi(p3));
				cout<<endl;	
			}

			sprintf(output,p2,atof(p3));
			 
		}
		//浮点型格式化输出 
		else if(strstr(p2,"%f")){
			if(flag==0){
				printf(p2,atof(p3));
				cout<<endl;					
			}
			
			sprintf(output,p2,atof(p3));
		}
		//字符串型格式化输出 
		else if(strstr(p2,"%s")){
			if(flag==0){
				printf(p2,p3);
				cout<<endl;
			}
			//并同时那格式化输出到字符输出中用于重定向 
			sprintf(output,p2,atof(p3));
				
		}
		else{
//			cout<<"指令格式错误，请重新输入！"<<endl; 
			return -1;
		}		
	}
	return 1;
}

//重定向 
int cmd_right(char *data,char *filename,int sign,char *path){
	GetCurrentDirectory(100,path);
	char* path1=path;
	strcat(path1,"\\");
	strcat(path1,filename);
	 
	string d=data;
	if(sign==0){ //表示重定向是> 
		//文件输出为覆盖模式 
		fstream fst(path1,ios::out); 
		if(!fst)
		{
//			cout<<"文件打开失败"<<endl;
			
			return -1;
		}
		fst<<data;
		fst.close();
	}else{ //表示重定向是>> 
		//文件输出为末尾增加模式 
		fstream fst(path1,ios::app);
		if(!fst)
		{
//			cout<<"文件打开失败"<<endl;
			return -1;
		}
		fst<<data;
		fst.close();
	}	
}
