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
//是否登录的标志 

//保存当前的路径 
//char path[100];
//登录用户的用户名 
//char username[100];
//登录用户的密码 
//char passwd[100];
//在输出重定向时用于保存输出内容 
//char output[1000];
 

//flag判断在进行输出是是否要进行输出 
//int flag=0;

bool cd_cmd(char * route,char * path)
{
	//cd 命令 
//	判断路径是否存在; 
	if(!SetCurrentDirectory(route))
	{	
	
		
		return FALSE;
//		if(is_login)
//		{
//			printf("[%s@LAPTOP-TB7M6EQ2 %s]#",username,path);
//		}   
//		else
//		{
//			printf("%s>",path);
//		} 
	//	GetLastError();
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
void mkdir_cmd(char *array,char * path)	
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

	}
	else
	{
		CreateDirectory(array,NULL);
		GetCurrentDirectory(100,path);

	}
}
/*rmdir命令*/
void rmdir_cmd(char *array,char* path)
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
 
	}
	else
	{
		RemoveDirectory(array);
		GetCurrentDirectory(100,path);

	}
}

/*cat命令*/
void cat_cmd(char *array,char *path)//用于显示文件
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
//		if(is_login)
//		{
//			printf("[%s@LAPTOP-TB7M6EQ2 %s]#",getUsername(),path);
//		}   
//		else
//		{
//			printf("%s>",path);
//		} 
	}
	else
	{
		infile.getline(ch,1000,EOF);
		cout<<ch<<endl;
		GetCurrentDirectory(100,path);
//		if(is_login)
//		{
//			printf("[%s@LAPTOP-TB7M6EQ2 %s]#",getUsername(),path);
//		}   
//		else
//		{
//			printf("%s>",path);
//		} 
	}
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
//	if(is_login)
//	{
//		printf("[%s@LAPTOP-TB7M6EQ2 %s]#",username,path);
//	}   
//	else
//	{
//		printf("%s>",path);
//	} 
	
}

//修改密码命令 

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
int main(){
	int flag;
	char username[100];
	char passwd[100];
	char path[100];
	char output[1000]={0};
	int is_login=0;
	const char* filenamePath = "account.txt";
	char* fileNamePath = (char *)filenamePath;
	SetCurrentDirectory("D:\\");//把默认路径设为D盘根目录
	GetCurrentDirectory(100,path);//在一个缓冲区中装载当前目录，在windows,头文件中 
	printf("%s>",path);
	char str1[100]={0};
	while(1){
		flag=0;
		//获取当前输入的字符串 
		gets(str1);	
		string str=str1;
//		if(str=="\n"){
//			cout<<endl; 
//		}
//		当为管道命令时 
		if(strstr(str1,"|")){
//			cout<<"hello"<<endl;
			//用空格分开输入的字符串 
			const char *d = " ";
		    string p1;
		    char* p2;
		    char* p3;
		    char* p4;
		    //并把分隔的字符串用P1、P2、P3、P4表示 
		    p1 = strtok(str1,d);
		    p2 = strtok(NULL,d);
		    p3 = strtok(NULL,d);
		    p4 = strtok(NULL,d);
		    string p_1=p1;
		    string p_2; 
			string p_4;
		    string p_3;
		    if(p3!=NULL){
		    	p_3=p3;
			}
			if(p2!=NULL){
		    	p_2=p2;
			}
			if(p4!=NULL){
				p_4=p4;
			}
			if(p_2=="|"){
			// 当P2为"|"时 ,判断是否为ls命令 
				if(p_1=="ls"){
					flag=1;
					ls_cmd(str1,output,flag);
				}
				else{
					cout<<"命令错误!"<<endl;
				} 
			}
			//当P3为"|"时,判断是否为"sort,print,more"命令 
			if(p_3=="|"){
				//收集前项命令的输出 
				if(p_1=="sort"){
					flag=1;
					cmd_sort(p2,output,path,flag);
				}

				else if(p_1=="print"){
					flag=1;
					cmd_print(p2,NULL,output,flag);
				}
				else if(p_1=="more"){
					flag=1;
					cmd_more(p2,output,path,flag);
				}else{
					cout<<"指令不支持！"<<endl; 
					continue;
				} 
				
				//转换为后项命令的输入 
				if(p_4=="sort"){
					flag=0;
					cmd_sort(output,output,path,flag);
				}
				else if(p_4=="print"){
					flag=0;
					cmd_print(output,NULL,output,flag);
				}
				else if(p_4=="cd"){
					flag=0;
					cd_cmd(output,path);
				}
				else if(p_4=="more"){
					flag=0;
					cmd_more(output,output,path,flag);
					
				}else{
					cout<<"指令不支持！"<<endl; 
					continue;
				} 
			}else{
				cout<<"指令错误！"<<endl;
				continue;
			}
		}
		//ls命令 
		else if(strstr(str1,"ls")){
			const char *d = " ";
		    string p1;
		    char* p2;
		    char* p3;
		    char* p4;
		    p1 = strtok(str1,d);
		    p2 = strtok(NULL,d);
		    p3 = strtok(NULL,d);
		    string p_3;
		    string p_2;
		    if(p2!=NULL){
		    	p_2=p2;
			}
		    if(p2==NULL){
		    	if(p1=="ls"){
					ls_cmd(str1,output,flag);
					
				}else{
					cout<<"指令错误"<<endl;
				}
			}
			//第一种输出重定向 
			else if(p_2==">"){
//				cout<<"123"<<endl;
				flag=1;
				ls_cmd(str1,output,flag);
				cmd_right(output,p3,0,path);
			}
			//第二种输出重定向 
			else if(p_2==">>"){
				flag=1;
				ls_cmd(str1,output,flag);
				cmd_right(output,p3,1,path);	
			}
			//第一种输入重定向，从文件输入 
			else if(p_2=="<"){
				GetCurrentDirectory(100,path);
				ls_cmd(str1,output,flag);
				
			}
			//第二种输入重定向，从键盘输入 
			else if(p_2=="<<"){
				
				string ch[100];
				int i=0;
				string p_3=p3;
				cout<<"<";
				cin>>ch[i];
				while(ch[i]!=p3){
					cout<<"<";
					i++;
					cin>>ch[i];
				}
				for(int j=0;j<i;j++){
					cout<<ch[j]<<endl;
				}
				continue;
			}
			else{
				cout<<"指令错误"<<endl; 
			}
//			ls_cmd(str1);
		}
		//cd命令 
		else if(strstr(str1,"cd")){
			const char *d = " ";
		    string p1;
		    char* p2;
		    char* p3;
		    char* p4;
		    p1 = strtok(str1,d);
		    p2 = strtok(NULL,d);
		    p3 = strtok(NULL,d);
		    string p_3;
		    string p_2;
		    if(p2!=NULL){
		    	p_2=p2;
			}
		    if(p2!=NULL){
		    	if(p1=="cd"){
					cd_cmd(p2,path);
					
				}else{
					cout<<"指令错误"<<endl;
				}
			}
			//cd指令只有输入重定向 
			else if(p_2=="<"){
				GetCurrentDirectory(100,path);
				cd_cmd(p2,path);

			}
			else if(p_2=="<<"){
				
				string ch[100];
				int i=0;
				string p_3=p3;
				cout<<"<";
				cin>>ch[i];
				while(ch[i]!=p3){
					cout<<"<";
					i++;
					cin>>ch[i];
				}
				for(int j=0;j<i;j++){
					cout<<ch[j]<<endl;
				}
				continue;
			}
			else{
				cout<<"指令错误，请重新输入！"<<endl;
			} 

		} 
		//登录命令 
		else if(str=="login"){
			char buff[100] = { 0 };
		    printf("Please enter username:");
			cin>>buff;
			//如果用户名不准确 
			int result=check_Login(buff,fileNamePath,username,passwd);
			if(result==-1)
			{
				cout << "文件" << fileNamePath << "打开失败或者不存在！" << endl;
				continue;
//				return -1;
			}
			else if(result==0){
				
				cout<<"用户名错误！"<<endl;
				continue;
			}
			
		//	wchar_t* G_LOGIN_NAME = char2wchar_t(buff);
		    printf("Please enter password:");
			char buff1[100] = { 0 };
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
			
			if(!(strcmp(passwd,buff1)==0)){
				cout<<"密码错误，请重新登录！"<<endl;
				continue ;
				
			}
			cout<<"登录成功"<<endl;
		//	wchar_t * G_LOGIN_PWD = char2wchar_t(buff1);
			is_login=1; 
			continue;
		}
		//修改密码命令 
		else if(str=="passwd"){
				if(is_login){
					cout<<"请输入你现在的密码:";
					char buff1[100] = { 0 };
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
						//用 * 来掩盖当前的密码 
						putchar('*');
						buff1[i++] = c;
					}
					//当密码和用户文件的密码一致时 
					if(strstr(buff1,passwd)){
						cout<<"请输入你的新密码："; 
						char buff2[100] = { 0 };
						char ch;
						int j = 0;
						while (TRUE)
						{
							ch = getch(); //从控制台读取一个字符但是不显示 
							if (ch == '\n' || ch == '\r')  //windows下getch输入回车会返回\r\n
							{
								printf("\n");
								break;
							}
							putchar('*');
							buff2[j++] = ch;
						}
						
						char data[100];
			//			const char* fileNamePath = "D:\\account.txt";
						fstream infile(fileNamePath,ios::out);
			
				//		string usn=username;
				//		string pwd=passwd;
				//		string str=usn+"\n"+passwd;
						//重新把新密码写到文件里面 
						infile<<username<<endl<<buff2;
						infile.close();
						continue ;
						
					}else{
						cout<<"密码错误！"<<endl;
						continue;
					}	
				}
				cout<<"还没有登录，请先登录"<<endl;
				continue ;
		}
		//登出命令 
		else if(str=="logout"){
			logout(is_login);
		}
		//sort 命令 
		else if(strstr(str1,"sort")){
//			char s[] = "Golden Global   View,disk * desk";

		    const char *d = " ";
		    string p1;
		    char* p2;
		    char* p3;
		    char* p4;
		    p1 = strtok(str1,d);
		    p2 = strtok(NULL,d);
		    p3 = strtok(NULL,d);
		    p4 = strtok(NULL,d);
		    string p_3;
		    string p_2=p2;
		    if(p3!=NULL){
		    	p_3=p3;
			}
		    if(p3==NULL){
		    	if(p1=="sort"){
					cmd_sort(p2,output,path,flag);
					
				}else{
					cout<<"指令错误"<<endl;
				}
			}
			//sort命令既有输入重定向，又有输出重定向 
			else if(p_3==">"){
				flag=1;
				//先调用命令，然后在进行重定向 
				cmd_sort(p2,output,path,flag);
				cmd_right(output,p4,0,path);
			}
			else if(p_3==">>"){
				flag=1;
				cmd_sort(p2,output,path,flag);
				cmd_right(output,p4,1,path);	
			}
			else if(p_2=="<"){
				GetCurrentDirectory(100,path);
				cmd_sort(p3,output,path,flag);
				
			}
			else if(p_2=="<<"){
				
				string ch[100];
				int i=0;
				string p_3=p3;
				cout<<"<";
				cin>>ch[i];
				while(ch[i]!=p3){
					cout<<"<";
					i++;
					cin>>ch[i];
				}
				for(int j=0;j<i;j++){
					cout<<ch[j]<<endl;
				}
				continue;
			}
			else{
				cout<<"指令错误"<<endl;
			}
		}
		//more指令 
		else if(strstr(str1,"more")){
		    const char *d = " ";
		    string p1;
		    char* p2;
		    char* p3;
		    char* p4;
		    p1 = strtok(str1,d);
		    p2 = strtok(NULL,d);
		    p3 = strtok(NULL,d);
		    p4 = strtok(NULL,d);
		    string p_3;
		    string p_2=p2;
		    if(p3!=NULL){
		    	p_3=p3;
			}
		    if(p3==NULL){
		    	if(p1=="more"){
					cmd_more(p2,output,path,flag);
					
				}else{
					cout<<"指令错误"<<endl;
				}
			}
			//more指令既有输入重定向，又有输出重定向 
			else if(p_3==">"){
				flag=1;
				cmd_more(p2,output,path,flag);
				cmd_right(output,p4,0,path);
			}
			else if(p_3==">>"){
				flag=1;
				cmd_more(p2,output,path,flag);
				cmd_right(output,p4,1,path);	
			}
			else if(p_2=="<"){
				
				GetCurrentDirectory(100,path);
				cmd_more(p3,output,path,flag);
				
			}
			else if(p_2=="<<"){
				string ch[100];
				int i=0;
				string p_3=p3;
				cout<<"<";
				cin>>ch[i];
				while(ch[i]!=p3){
					cout<<"<";
					i++;
					cin>>ch[i];
				}
				for(int j=0;j<i;j++){
					cout<<ch[j]<<endl;
				}
				continue ;
			}
			else{
				cout<<"指令错误"<<endl;
			}
		}
		else if(strstr(str1,"mkdir")){
			const char *d = " ";
		    string p1;
		    char* p2;
		    char* p3;
//		    char* p4;
		    p1 = strtok(str1,d);
		    p2 = strtok(NULL,d);
		    p3 = strtok(NULL,d);
//		    p4 = strtok(NULL,d);
		    string p_3;
		    string p_2=p2;
		    if(p3!=NULL){
		    	p_3=p3;
			}
			if(p1=="mkdir"){
				mkdir_cmd(p2,path);
			}else{
				cout<<"指令错误！"<<endl;
			}	
		}
		else if(strstr(str1,"rmdir")){
			const char *d = " ";
		    string p1;
		    char* p2;
		    char* p3;
//		    char* p4;
		    p1 = strtok(str1,d);
		    p2 = strtok(NULL,d);
		    p3 = strtok(NULL,d);
//		    p4 = strtok(NULL,d);
		    string p_3;
		    string p_2=p2;
		    if(p3!=NULL){
		    	p_3=p3;
			}
			if(p1=="rmdir"){
				rmdir_cmd(p2,path);
			}else{
				cout<<"指令错误！"<<endl;
			}	
		}

		else if(strstr(str1,"cat")){
			const char *d = " ";
		    string p1;
		    char* p2;
		    char* p3;
//		    char* p4;
		    p1 = strtok(str1,d);
		    p2 = strtok(NULL,d);
		    p3 = strtok(NULL,d);
//		    p4 = strtok(NULL,d);
		    string p_3;
		    string p_2=p2;
		    if(p3!=NULL){
		    	p_3=p3;
			}
			if(p1=="cat"){
				cat_cmd(p2,path);
			}else{
				cout<<"指令错误！"<<endl;
			}	
		} 
		//print命令 
		else if(strstr(str1,"print") && !strstr(str1,">>") && !strstr(str1,">")){
			const char *d = " ";
		    string p1;
		    char* p2;
		    char* p3;
		    p1 = strtok(str1,d);
		    p2 = strtok(NULL,d);
		    p3 = strtok(NULL,d);
		    
			if(p1=="print"){
				cmd_print(p2,p3,output,flag);	
			}else{
				cout<<"指令不规范，请重新输入！"<<endl; 
			}	
		} 
		//print命令有格式化输出重定向 
		else if(strstr(str1,">>")||strstr(str1,">")){
			if(strstr(str1,"print")){
//				cout<<"str1="<<str1<<endl;
				const char *d = " ";
			    string p1;
			    char* p2;
			    char* p3;
			    char* p4;
			    char* p5;
			    p1 = strtok(str1,d);
			    p2 = strtok(NULL,d);
			    p3 = strtok(NULL,d);
			    p4 = strtok(NULL,d);
			    p5 = strtok(NULL,d);
			    if(p5==NULL){
					string p_3=p3;
			    	if(p_3==">>"||p_3==">"){
			    		flag=1;
			    		if(p_3==">>"){
			    			
			    			cmd_right(p2,p4,1,path);	
						}else{
							cmd_right(p2,p4,0,path);	
						}	
					}else{
						cout<<"指令错误，请重新输入！"<<endl; 
					}	
				}
				else{
					string p_4=p4;
					if(p_4==">>"||p_4==">"){
						flag=1;
						string str1=p2;
						char str2[100]={0};
						int j=0;
						for(int i=0;i<str1.length();i++){
							if(str1[i]!='\"'){
								str2[j]=str1[i];
								j++;
							}
							
						}
						char buff[100];
						p2=str2;
						
						//整型格式化输出 
						if(strstr(p2,"%d")){
							sprintf(buff,p2,atoi(p3));
							cout<<endl;	 
						}
						//浮点型格式化输出 
						else if(strstr(p2,"%f")){
							sprintf(buff,p2,atof(p3));
							cout<<endl;	
						}
						//字符串型格式化输出 
						else if(strstr(p2,"%s")){
							sprintf(buff,p2,p3);
							cout<<endl;	
						}
						
						if(p_4==">>"){
							cmd_right(buff,p5,1,path);
						}
						else{
							cmd_right(buff,p5,0,path);
						}
					}
					else{
						cout<<"指令错误，请重新输入！"<<endl;		
					}		
				}
			}
			else{
				cout<<"命令不支持,请重新输入"<<endl;
			}	
		}
	 	//当输入的命令只有一个换行时，不输出 
		else if(str==""){
			
		}
		else{
			
			cout<<"命令输入错误，请重新输入"<<endl;
			
		}
		GetCurrentDirectory(100,path);//在一个缓冲区中装载当前目录，在windows,头文件中
		//判断是否登录，从而改变显示的路径 
		if(is_login)
		{
			
			printf("[%s@LAPTOP-TB7M6EQ2 %s]#",username,path);
			
		}   
		else
		{
			printf("%s>",path);
		}
	}
}


