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
#include<unistd.h>   //��POSIX����ϵͳAPI�ķ��ʹ��ܵ�ͷ�ļ�������
#include<lm.h>  // 
using namespace std;
//�Ƿ��¼�ı�־ 

//���浱ǰ��·�� 
//char path[100];
//��¼�û����û��� 
//char username[100];
//��¼�û������� 
//char passwd[100];
//������ض���ʱ���ڱ���������� 
//char output[1000];
 

//flag�ж��ڽ���������Ƿ�Ҫ������� 
//int flag=0;

bool cd_cmd(char * route,char * path)
{
	//cd ���� 
//	�ж�·���Ƿ����; 
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
		//�������õ�ǰ��·�� 
		SetCurrentDirectory(route);
		GetCurrentDirectory(100,path);
		return TRUE;

	}
	
}
//����Ƿ��¼ 
int check_Login(char *array,char* fileNamePath,char *username,char * passwd)
{
	
	char data[100];
	//�����û���������ĵ�¼�ļ� 
//	const char* fileNamePath = "D:\\account.txt";
	//���ļ� 
	ifstream infile;
	infile.open(fileNamePath);
	if (infile.fail()) {
//		cout << "�ļ�" << fileNamePath << "��ʧ�ܻ��߲����ڣ�" << endl;
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
//	cout<<"�û�������"<<endl;
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
		cout<<"��Ŀ¼�Ѵ��ڣ�����ʧ��!"<<endl;
		GetCurrentDirectory(100,path);

	}
	else
	{
		CreateDirectory(array,NULL);
		GetCurrentDirectory(100,path);

	}
}
/*rmdir����*/
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
		cout<<"��Ŀ¼�����ڣ�ɾ��ʧ��!"<<endl;
		GetCurrentDirectory(100,path);
 
	}
	else
	{
		RemoveDirectory(array);
		GetCurrentDirectory(100,path);

	}
}

/*cat����*/
void cat_cmd(char *array,char *path)//������ʾ�ļ�
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

/*more����*/
 cmd_more(char *array,char output[],char * path,int flag)
{
	char ch[1000];
	GetCurrentDirectory(100,path);
	//��·������ƴ�� 
	strcat(path,"\\");
	strcat(path,array);
	ifstream infile(path);
	if(!infile)
	{

		cout<<"�޷����ļ�"<<path<<endl;
		GetCurrentDirectory(100,path);
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
		int j=0;
		//��ÿ�����ǰ�����������������Ϊ�� 
		for(int y=0;y<1000;y++){
			output[y]=0;
		}
		if(count1<24)
		{
			for(l=0;l<count1-1;l++)
			{
				//һ�������һ�߰�������ݱ��浽���� 
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
			//��ȡ��ǰ��·����Path������ 
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

					break;
				}
			}
		}
	}
	infile.close();
}
//sort���� 
int cmd_sort(char *array,char output[],char *path,int flag)
{
	int lnum=0,min;
	char line[100][100],tmp[100];//������ÿ���ַ���
	string s[100];
	GetCurrentDirectory(100,path);
	strcat(path,"\\");
	strcat(path,array);
	ifstream infile(path);
	//�ж��ļ��Ƿ���� 
	if(!infile)
	{

//		cout<<"�޷����ļ�"<<array<<endl;
		return -1;
		GetCurrentDirectory(100,path);
 
	}
	else
	{
		while(!infile.eof())
		{
			infile.getline(line[lnum],100,'\n');
			lnum++;//��¼������
		}
		infile.close();
		//����ascii���С����Ƚ�ÿ���ַ��� 
		for(int x=0;x<lnum-1;x++)   
		{
			min=x;
			for(int y=x+1;y<lnum;y++)
				if(strcmp(line[y],line[min])<0)
					min=y;
				//min�ı䣬�ͽ������ַ����н��� 
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
//			cout<<"�ļ���ʧ��"<<endl;
			return -1;
		}
		else
		{
//			line[0][0]=NULL;
			int j=0;
			
			for(int y=0;y<1000;y++){
				output[y]=0;
			}
			//�ѽ��д���ļ����� 
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

//ls���� 
int ls_cmd(char *array,char output[],int flag)
{
	char path1[100]={0};
//	char path2[100]={0}; 
	HANDLE	handle;
	int filenum=0;
	FILETIME lpCreationTime,lpLastAccessTime,lpLastWriteTime;
	SYSTEMTIME stime;
	//����windows�ӿ� 
	WIN32_FIND_DATA* path2 = new WIN32_FIND_DATA();
	 
	if(!GetCurrentDirectory(50,path1))
	{
//		cout<<"·��������!"<<endl;
	
		return -1;
	}

	strcat(path1,"\\*.*");        //DOSͨ���
	if((handle = FindFirstFile(path1, path2)) != INVALID_HANDLE_VALUE)
	{
		int j=0;
		for(int y=0;y<1000;y++){
			output[y]=0;
		}
		do{
			//���ò���ϵͳ��� 
			HANDLE hDir = CreateFile(path2->cFileName,GENERIC_READ,FILE_SHARE_READ | FILE_SHARE_DELETE,NULL,OPEN_EXISTING,FILE_FLAG_BACKUP_SEMANTICS,  NULL);  
			if(GetFileTime(hDir,  &lpCreationTime,  &lpLastAccessTime,  &lpLastWriteTime)){  
				FILETIME  ftime;  
				FileTimeToLocalFileTime(&lpLastWriteTime,  &ftime);  //  ת���ɱ���ʱ��  
				FileTimeToSystemTime(&ftime,  &stime);  //  ת����ϵͳʱ���ʽ  
			}
			//cout<<setfill('0');
			if(strcmp(array,"ls")==0)
			{

				for(int p=0;path2->cFileName[p]!=0;p++){
					output[j]=path2->cFileName[p];
					j++;
				}
				//���ø�ʽ����־�����������ʽ 
				cout.setf(ios::left);
				//ÿ�������ļ�����һ����� 
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
	//���õ�ǰ·�� 
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

//�޸��������� 

//�ǳ� 
void logout(int& is_login){
	//�ѵ�¼�ı�־��Ϊ0 
	is_login=0;
}

//print���� 
int cmd_print(char *p2,char *p3,char output[],int flag){
	if(p3==NULL){
		if(flag==0){
			//û�и�ʽ���ַ�����ֱ�Ӵ�ӡP2 
			cout<<p2<<endl;
		}
		
		//���������������Ϊ0 
		for(int i=0;i<1000;i++){
			output[i]=0;
		}
		
		for(int i=0;p2[i]!=0;i++){
			output[i]=p2[i]; 
		}
	}
	else{
		//��ʽ����� 
		string str1=p2;
		char str2[100]={0};
		int j=0;
		for(int i=0;i<str1.length();i++){
			//ȥ����ʽ������� " �ַ� 
			if(str1[i]!='\"'){
				str2[j]=str1[i];
				j++;
			}	
		}
		
		for(int i=0;i<1000;i++){
			output[i]=0;
		} 
		
		p2=str2;
		//���͸�ʽ����� 
		if(strstr(p2,"%d")){
			if(flag==0){
				printf(p2,atoi(p3));
				cout<<endl;	
			}

			sprintf(output,p2,atof(p3));
			 
		}
		//�����͸�ʽ����� 
		else if(strstr(p2,"%f")){
			if(flag==0){
				printf(p2,atof(p3));
				cout<<endl;					
			}
			
			sprintf(output,p2,atof(p3));
		}
		//�ַ����͸�ʽ����� 
		else if(strstr(p2,"%s")){
			if(flag==0){
				printf(p2,p3);
				cout<<endl;
			}
			//��ͬʱ�Ǹ�ʽ��������ַ�����������ض��� 
			sprintf(output,p2,atof(p3));
				
		}
		else{
//			cout<<"ָ���ʽ�������������룡"<<endl; 
			return -1;
		}		
	}
	return 1;
}

//�ض��� 
int cmd_right(char *data,char *filename,int sign,char *path){
	GetCurrentDirectory(100,path);
	char* path1=path;
	strcat(path1,"\\");
	strcat(path1,filename);
	 
	string d=data;
	if(sign==0){ //��ʾ�ض�����> 
		//�ļ����Ϊ����ģʽ 
		fstream fst(path1,ios::out); 
		if(!fst)
		{
//			cout<<"�ļ���ʧ��"<<endl;
			
			return -1;
		}
		fst<<data;
		fst.close();
	}else{ //��ʾ�ض�����>> 
		//�ļ����Ϊĩβ����ģʽ 
		fstream fst(path1,ios::app);
		if(!fst)
		{
//			cout<<"�ļ���ʧ��"<<endl;
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
	SetCurrentDirectory("D:\\");//��Ĭ��·����ΪD�̸�Ŀ¼
	GetCurrentDirectory(100,path);//��һ����������װ�ص�ǰĿ¼����windows,ͷ�ļ��� 
	printf("%s>",path);
	char str1[100]={0};
	while(1){
		flag=0;
		//��ȡ��ǰ������ַ��� 
		gets(str1);	
		string str=str1;
//		if(str=="\n"){
//			cout<<endl; 
//		}
//		��Ϊ�ܵ�����ʱ 
		if(strstr(str1,"|")){
//			cout<<"hello"<<endl;
			//�ÿո�ֿ�������ַ��� 
			const char *d = " ";
		    string p1;
		    char* p2;
		    char* p3;
		    char* p4;
		    //���ѷָ����ַ�����P1��P2��P3��P4��ʾ 
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
			// ��P2Ϊ"|"ʱ ,�ж��Ƿ�Ϊls���� 
				if(p_1=="ls"){
					flag=1;
					ls_cmd(str1,output,flag);
				}
				else{
					cout<<"�������!"<<endl;
				} 
			}
			//��P3Ϊ"|"ʱ,�ж��Ƿ�Ϊ"sort,print,more"���� 
			if(p_3=="|"){
				//�ռ�ǰ���������� 
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
					cout<<"ָ�֧�֣�"<<endl; 
					continue;
				} 
				
				//ת��Ϊ������������� 
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
					cout<<"ָ�֧�֣�"<<endl; 
					continue;
				} 
			}else{
				cout<<"ָ�����"<<endl;
				continue;
			}
		}
		//ls���� 
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
					cout<<"ָ�����"<<endl;
				}
			}
			//��һ������ض��� 
			else if(p_2==">"){
//				cout<<"123"<<endl;
				flag=1;
				ls_cmd(str1,output,flag);
				cmd_right(output,p3,0,path);
			}
			//�ڶ�������ض��� 
			else if(p_2==">>"){
				flag=1;
				ls_cmd(str1,output,flag);
				cmd_right(output,p3,1,path);	
			}
			//��һ�������ض��򣬴��ļ����� 
			else if(p_2=="<"){
				GetCurrentDirectory(100,path);
				ls_cmd(str1,output,flag);
				
			}
			//�ڶ��������ض��򣬴Ӽ������� 
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
				cout<<"ָ�����"<<endl; 
			}
//			ls_cmd(str1);
		}
		//cd���� 
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
					cout<<"ָ�����"<<endl;
				}
			}
			//cdָ��ֻ�������ض��� 
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
				cout<<"ָ��������������룡"<<endl;
			} 

		} 
		//��¼���� 
		else if(str=="login"){
			char buff[100] = { 0 };
		    printf("Please enter username:");
			cin>>buff;
			//����û�����׼ȷ 
			int result=check_Login(buff,fileNamePath,username,passwd);
			if(result==-1)
			{
				cout << "�ļ�" << fileNamePath << "��ʧ�ܻ��߲����ڣ�" << endl;
				continue;
//				return -1;
			}
			else if(result==0){
				
				cout<<"�û�������"<<endl;
				continue;
			}
			
		//	wchar_t* G_LOGIN_NAME = char2wchar_t(buff);
		    printf("Please enter password:");
			char buff1[100] = { 0 };
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
			
			if(!(strcmp(passwd,buff1)==0)){
				cout<<"������������µ�¼��"<<endl;
				continue ;
				
			}
			cout<<"��¼�ɹ�"<<endl;
		//	wchar_t * G_LOGIN_PWD = char2wchar_t(buff1);
			is_login=1; 
			continue;
		}
		//�޸��������� 
		else if(str=="passwd"){
				if(is_login){
					cout<<"�����������ڵ�����:";
					char buff1[100] = { 0 };
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
						//�� * ���ڸǵ�ǰ������ 
						putchar('*');
						buff1[i++] = c;
					}
					//��������û��ļ�������һ��ʱ 
					if(strstr(buff1,passwd)){
						cout<<"��������������룺"; 
						char buff2[100] = { 0 };
						char ch;
						int j = 0;
						while (TRUE)
						{
							ch = getch(); //�ӿ���̨��ȡһ���ַ����ǲ���ʾ 
							if (ch == '\n' || ch == '\r')  //windows��getch����س��᷵��\r\n
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
						//���°�������д���ļ����� 
						infile<<username<<endl<<buff2;
						infile.close();
						continue ;
						
					}else{
						cout<<"�������"<<endl;
						continue;
					}	
				}
				cout<<"��û�е�¼�����ȵ�¼"<<endl;
				continue ;
		}
		//�ǳ����� 
		else if(str=="logout"){
			logout(is_login);
		}
		//sort ���� 
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
					cout<<"ָ�����"<<endl;
				}
			}
			//sort������������ض�����������ض��� 
			else if(p_3==">"){
				flag=1;
				//�ȵ������Ȼ���ڽ����ض��� 
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
				cout<<"ָ�����"<<endl;
			}
		}
		//moreָ�� 
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
					cout<<"ָ�����"<<endl;
				}
			}
			//moreָ����������ض�����������ض��� 
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
				cout<<"ָ�����"<<endl;
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
				cout<<"ָ�����"<<endl;
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
				cout<<"ָ�����"<<endl;
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
				cout<<"ָ�����"<<endl;
			}	
		} 
		//print���� 
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
				cout<<"ָ��淶�����������룡"<<endl; 
			}	
		} 
		//print�����и�ʽ������ض��� 
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
						cout<<"ָ��������������룡"<<endl; 
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
						
						//���͸�ʽ����� 
						if(strstr(p2,"%d")){
							sprintf(buff,p2,atoi(p3));
							cout<<endl;	 
						}
						//�����͸�ʽ����� 
						else if(strstr(p2,"%f")){
							sprintf(buff,p2,atof(p3));
							cout<<endl;	
						}
						//�ַ����͸�ʽ����� 
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
						cout<<"ָ��������������룡"<<endl;		
					}		
				}
			}
			else{
				cout<<"���֧��,����������"<<endl;
			}	
		}
	 	//�����������ֻ��һ������ʱ������� 
		else if(str==""){
			
		}
		else{
			
			cout<<"���������������������"<<endl;
			
		}
		GetCurrentDirectory(100,path);//��һ����������װ�ص�ǰĿ¼����windows,ͷ�ļ���
		//�ж��Ƿ��¼���Ӷ��ı���ʾ��·�� 
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


