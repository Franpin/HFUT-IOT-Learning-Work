import re
from flask import Flask
from flask_migrate import Migrate
import config as settings
from models import *
from interface import *
from flask import Flask,render_template,send_from_directory,request,flash
app = Flask(__name__)
app.secret_key = '123456'
app.config.from_object(settings)
db.init_app(app)
Migrate(app, db)


@app.route('/',methods=['GET','POST'])
def login():
    # PagePersonal.end_pes(12007)
    return render_template('login.html')

@app.route('/index',methods=['GET','POST'])
def index():
    
    if request.method=='POST':
        username=str(request.form.get('username'))
        passwd=str(request.form.get('password'))

        result=list(PageUser.get_pw(username))

        passwd1=str(result[0][0])
        print(passwd)
        print(passwd1)
        if passwd==passwd1:
            return render_template('index.html')
        else:
            return render_template('login.html')
    return render_template('index.html')

@app.route('/index1_result',methods=['GET','POST'])
def index1_resut():
    if request.method=='POST':
        stu_id=request.form.get('input_id')
        stu_pri=request.form.get('input_price')
        if stu_pri !=None:
            
            flash("学生id："+str(stu_id))
            
            flash('充值金额：'+str(stu_pri))
            PageAddMoney.add_money(stu_id,int(stu_pri))
            flash("充值完成！")
        elif stu_id !=None:
            pri=PageAddMoney.get_money(stu_id)
            flash("学生id："+str(stu_id))

            flash('余额：'+str(pri))
        else:
            result=list(PageAddMoney.get_money_all())
            flash('学生id    '+'学生姓名    '+'余额')
            for x in result:
                flash(str(x[0])+'    '+str(x[1])+'    '+str(x[2]))

    return render_template('index1.html')

@app.route('/index2_result',methods=['GET','POST'])
def index2_resut():
    if request.method=='POST':
        input_id=request.form.get('input_id')
        submit1=request.form.get('submit1')
        submit2=request.form.get('submit2')
        submit3=request.form.get('submit3')
        # submit4=request.form.get('submit4')
        if input_id == None:
            result=list(PageCReservation.get_crs_all())
            flash('班级id   '+' 开始时间 '+'    持续时间')
            for x in result:
                # print(x[1])
                # x[1]=x[1].strftime("%Y-%m-%d %H:%M:%S")
                flash(str(x[0])+'    '+x[1].strftime("%Y-%m-%d %H:%M:%S")+"    "+str(x[2]))

        if submit1 != None:
            flash('查看某个班级的预约情况')
            flash('班级id   '+' 开始时间    '+' 持续时间')
            
            if input_id != None:
                print(input_id)
                result=list(PageCReservation.get_crs(input_id))
                x=result[0]
                print(x)
                flash(str(x[0])+'    '+x[1].strftime("%Y-%m-%d %H:%M:%S")+"    "+str(x[2]))
            
        if submit2 != None:
            PageCReservation.delete_crs(input_id)
            flash('删除预约成功')
        if submit3 != None:
            PageCReservation.end_class(input_id)
            flash('班级预约号'+str(input_id)+'完成了预约')
     
    return render_template('index1.html')


@app.route('/index3_result',methods=['GET','POST'])
def index3_result():
    if request.method=='POST':
        input_id=request.form.get('input_id')
        submit1=request.form.get('submit1')
        submit2=request.form.get('submit2')
        submit3=request.form.get('submit3')
        if input_id == None:

            flash("全体学生的信息")
            result=list(PageStudent.get_stu_all())
            flash('学生id'+'   '+'学生姓名'+'   '+'班级id')
            for x in result:
                result_sid,result_sna,result_cid= x[0],x[1],x[2]
                
                flash(str(result_sid)+'   '+str(result_sna)+'   '+str(result_cid))

            
        if submit1 !=None:

            flash('查看某个学生的信息')

            result_sid=PageStudent.get_stu(input_id).s_id
            result_sna=PageStudent.get_stu(input_id).s_na
            result_cid=PageStudent.get_stu(input_id).c_id
            result_smon=PageStudent.get_stu(input_id).s_money
            flash('学生id'+'   '+'学生姓名'+'   '+'班级id'+'   '+'余额')
            flash(str(result_sid)+'   '+str(result_sna)+'   '+str(result_cid)+'   '+str(result_smon))
        if submit2 !=None:
            flash('删除学生'+str(input_id)+'的信息')
            PageStudent.delete_stu(input_id)
        if submit3 !=None:
            flash('增加学生信息')
            input_id1=request.form.get('input_id1')
            input_id2=request.form.get('input_id2')
            input_id3=request.form.get('input_id3')
            input_id4=request.form.get('input_id4')
            Student(input_id1,input_id2,input_id3,input_id4).save()
            flash('学生id'+'   '+'学生姓名'+'   '+'班级id'+'   '+'余额')
            flash(str(input_id1)+'    '+str(input_id2)+'    '+str(input_id3)+'    '+str(input_id4))
    return render_template('index1.html')

@app.route('/index4_result',methods=['GET','POST'])
def index4_result():
    if request.method=='POST':
        input_id=request.form.get('input_id')
        submit1=request.form.get('submit1')
        submit2=request.form.get('submit2')
        submit3=request.form.get('submit3')
        if input_id == None:

            flash("全体班级的信息")
            result=list(PageClass.get_class_all())
            flash('班级id'+'   '+'班级名称'+'   '+'班级人数')
            for x in result:
                result_sid,result_sna,result_cid= x[0],x[1],x[2]
                
                flash(str(result_sid)+'   '+str(result_sna)+'   '+str(result_cid))

        if submit1 !=None:

            flash('查看某个班级的信息')
            flash('班级id'+'   '+'班级名称'+'   '+'班级人数')
            result_cid=PageClass.get_class(input_id).c_id
            result_cna=PageClass.get_class(input_id).c_na
            result_cnum=PageClass.get_class(input_id).c_num
            flash(str(result_cid)+'   '+str(result_cna)+'   '+str(result_cnum))

        if submit2 !=None:
            flash('删除班级'+str(input_id)+'的信息')
            PageClass.delete_class(input_id)

        if submit3 !=None:
            
            flash('增加班级信息')
            input_id1=request.form.get('input_id1')
            Class(input_id1).save()

    return render_template('index1.html')



@app.route('/index5_result',methods=['GET','POST'])
def index5_resut():
    if request.method=='POST':
        input_id=request.form.get('input_id')
        submit1=request.form.get('submit1')
        submit2=request.form.get('submit2')
        submit3=request.form.get('submit3')
        if input_id == None:
            result=list(PagePersonal.get_pes_all())
            flash('学生id   '+' 开始时间 '+'    持续时间')
            for x in result:
                # print(x[1])
                # x[1]=x[1].strftime("%Y-%m-%d %H:%M:%S")
                flash(str(x[0])+'    '+str(x[1])+"    "+str(x[2]))

        if submit1 != None:
            flash('查看某个学生的预约情况')
            flash('个人预约id    '+'学生id   '+' 开始时间    ')
            
            if input_id != None:
                
                result=list(PagePersonal.get_pes(input_id))
                x=result[0]
                flash(str(x[0])+'    '+str(x[1])+"    "+str(x[2]))
            
        if submit2 != None:
            PagePersonal.delete_pes(input_id)
            flash('删除预约成功')
        if submit3 != None:
            # PagePersonal.end_pes(input_id)
            flash('学生id'+str(input_id)+'完成了预约')
    return render_template('index1.html')




@app.route('/index6_result',methods=['GET','POST'])
def index6_result():
    if request.method=='POST':
        input_id1=request.form.get('input_id1')
        input_id2=request.form.get('input_id2')
        input_id3=request.form.get('input_id3')
        submit0=request.form.get('submit0')
        submit1=request.form.get('submit1')
        submit2=request.form.get('submit2')
        submit3=request.form.get('submit3')

        if submit0 != None :
            result=list(PageCompuRoomUseClass.get_free_all())
            print(result)
            flash("获取现在班级的所有的空闲的机房")
            flash('机房id   '+' 机房名称 '+'    可用数量')
            for x in result:
                # print(x[1])
                # x[1]=x[1].strftime("%Y-%m-%d %H:%M:%S")
                flash(str(x[0])+'    '+str(x[1])+"    "+str(x[2]))

        if submit1 !=None:
            flash('增加班级预约')
            # input_id1=request.form.get('input_id1')
            # input_id2=request.form.get('input_id2')
            # input_id3=request.form.get('input_id3')
            input_id4=request.form.get('input_id4')
            input_id2=datetime.strptime(input_id2, '%Y.%m.%d')
            CReservation(input_id1,input_id2,input_id3,input_id4).save()
            flash(str(input_id1)+'    '+str(input_id2)+'    '+str(input_id3)+'    '+str(input_id4))


        if submit2 !=None:
            result=list(PageCompuRoomUsePerson.get_free_all())
            flash('获取现在个人的所有的空闲的机房')
            flash('机房id   '+' 机房名称 '+'    可用数量')
            for x in result:
                # print(x[1])
                # x[1]=x[1].strftime("%Y-%m-%d %H:%M:%S")
                flash(str(x[0])+'    '+str(x[1])+"    "+str(x[2]))

        if submit3 != None:
            flash('个人上机登记')
            input_id3=datetime.strptime(input_id3, '%Y.%m.%d')
            PageCompuRoomUsePerson.person_rsv(input_id1,input_id2,input_id3)
            flash('学生id   '+' 机房id '+'    开始时间')
            flash(str(input_id1)+'    '+str(input_id2)+'    '+str(input_id3))

    return render_template('index1.html')

@app.route('/index7_result',methods=['GET','POST'])
def index7_result():
    if request.method=='POST':
        input_id1=request.form.get('input_id1')
        input_id2=request.form.get('input_id2')
        input_id3=request.form.get('input_id3')
        input_id4=request.form.get('input_id4')
        input_id5=request.form.get('input_id5')
        submit0=request.form.get('submit0')
        submit1=request.form.get('submit1')
        if submit0 !=None:
            flash('机房地址   '+' 机房名称 '+'    电脑数量'+'   机房用途   '+'  机房价格')
            flash(str(input_id1)+'    '+str(input_id2)+'    '+str(input_id3)+str(input_id4)+'    '+str(input_id5))
            PgeComputerRoom.add_cr(input_id1,input_id2,input_id3,input_id4,input_id5)

        if submit1 !=None:
            if input_id1 != None:
                flash("删除机房，机房id："+str(input_id1))

    return render_template('index1.html')

@app.route('/index8_result',methods=['GET','POST'])
def index8_result():
    if request.method=='POST':

        submit0=request.form.get('submit0')
        submit1=request.form.get('submit1')
        if submit0 !=None:
            PaeBackupAndRestore.make_restore()
            flash("开始备份")

        if submit1 !=None:
            import os
            PaeBackupAndRestore.make_bakcup()
            flash("恢复成功")

    return render_template('index1.html')

if __name__ == '__main__':
    app.run()

# @app.route('/')
# def hello_world():  # put application's code here
#     return 'Hello World!'


if __name__ == '__main__':
    app.run()
