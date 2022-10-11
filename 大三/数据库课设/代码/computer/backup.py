import os

''' 定义变量 '''
databases = ['computer']  # 定义要备份的数据库名
sql_host = 'localhost'
sql_user = 'root'  # 数据库登陆用户
sql_pwd = 'yanping2001'  # 数据库登陆密码
database_name = 'computer'  # 数据库名字
sql_path = './restore/computer.sql'  # 存放sql文件的地址

def db_backup():
    ''' 开始还原数据到指定文件夹 '''
    if not os.path.exists(sql_path):
        print('文件不存在')
    else:
        sql_comm = "mysql –u%s –p%s -D%s < %s"%(sql_user,sql_pwd,database_name,os.path.abspath(sql_path))  # 定义备份数据库变量
        print(sql_comm)
        if os.system(sql_comm) == 0:  # 如果上一条执行结果等于0，表示成功
            print(database_name, '还原成功')  # 打印成功信息
        else:  # 备份失败
            print(database_name, '还原失败')  # 打印成功信息
