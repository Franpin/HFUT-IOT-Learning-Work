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

bool cd_cmd(char * route,char * path)
{
	//cd ���� 
//	�ж�·���Ƿ����; 
	if(!SetCurrentDirectory(route))
	{	
	
		
		return FALSE;

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
	
}

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
