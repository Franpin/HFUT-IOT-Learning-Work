import os

''' 定义变量 '''
databases = ['computer']  # 定义要备份的数据库名
sql_host = 'localhost'
sql_user = 'root'  # 数据库登陆用户
sql_pwd = 'yanping2001'  # 数据库登陆密码
root_path = './restore'  # 存放sql文件的地址


def db_restore():
    ''' 创建存放备份文件的文件夹 '''
    mkdir_dir = root_path+"/"  # 在/home/work/目录下用当天时间的格式创建目录
    if not os.path.exists(mkdir_dir):  # 判断如果没有当天时间目录
            os.mkdir(mkdir_dir)  # 创建
    print('创建文件夹成功:', os.path.abspath(mkdir_dir))  # 打印创建成功
    ''' 开始备份到指定文件夹 '''
    os.chdir(mkdir_dir)  # 改变当前工作目录到指定的路径
    for database_name in databases:  # 循环遍历要备份的数据库的名字
        today_sql = database_name+'.sql'  # 定义数据库文件名变量
        # 编写cmd语句
        sql_comm="mysqldump -u%s -p%s %s > %s --default_character-set=utf8"%(sql_user,sql_pwd,database_name,today_sql)  # 定义备份数据库变量
        if os.system(sql_comm) == 0:  # 如果上一条执行结果等于0，表示成功
            print(database_name, 'is backup successfully!')  # 打印成功信息
            print('备份文件地址:',os.path.abspath('./')+today_sql)
        else:  # 备份失败
            print(database_name, 'is backup fai!')  # 打印成功信息
