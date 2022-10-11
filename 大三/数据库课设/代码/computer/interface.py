# 前端界面的每个页面使用的功能接口

from models import *
import restore
import backup

# 充值页面
class PageAddMoney:
    # 充值功能
    # 返回值：充值后的总金额
    @staticmethod
    def add_money(sid, add):
        student = Student.get_by_id(sid)
        student.s_money = student.s_money + add
        db.session.commit()
        return student.s_money

    # 余额查看功能（某人）
    #
    @staticmethod
    def get_money(sid):
        student = Student.get_by_id(sid)
        money = student.s_money
        return money

    # 余额查看功能（全体）
    # 结果要强转为list
    @staticmethod
    def get_money_all():
        moneys = db.session.execute(db.select(Student.s_id, Student.s_na, Student.s_money))
        return moneys


# 班级预约统计页面
class PageCReservation:

    # 查看全部的班级预约情况
    # 结果要强转为list
    @staticmethod
    def get_crs_all():
        crs = db.session.execute(db.select(CReservation.c_id, CReservation.crs_time, CReservation.crs_long))
        return crs

    # 查看某个班级的预约情况
    # 结果要强转为list
    @staticmethod
    def get_crs(cid):
        crs = db.session.execute(db.select(CReservation.c_id, CReservation.crs_time,
                                           CReservation.crs_long).filter(CReservation.c_id == cid))
        return crs

    # 删除预约情况
    # 已测试
    @staticmethod
    def delete_crs(crs_id):
        CReservation.delete_by_id(crs_id)

    # 某班完成了预约
    # 已测试
    @staticmethod
    def end_class(crsid):
        CReservation.is_end(crsid)


# 学生管理页面
class PageStudent:
    # 查看全体学生的信息
    # 已测试
    # 返回值需要强转为list
    @staticmethod
    def get_stu_all():
        stu = db.session.execute(db.select(Student.s_id, Student.s_na, Class.c_na).filter(Student.c_id == Class.c_id))
        return stu

    # 查看某个学生的信息
    # 已测试
    # 返回值是ORM模型封装的对象
    @staticmethod
    def get_stu(sid):
        stu = Student.get_by_id(sid)
        return stu

    # 删除某个学生的信息
    # 已测试
    @staticmethod
    def delete_stu(sid):
        Student.delete_by_id(sid)


# 班级管理页面
class PageClass:
    # 查看全部班级情况
    # 已测试
    # 返回值：需强转成list
    @staticmethod
    def get_class_all():
        clas = db.session.execute(db.select(Class.c_id, Class.c_na, Class.c_num))
        return clas

    # 查看某个班级的情况
    # 已测试
    # 返回值：ORM封装的对象，可以直接调用属性的值
    @staticmethod
    def get_class(cid):
        clas = Class.get_by_name(cid)
        return clas

    # 删除某个班级（包括学生）
    # 已测试
    @staticmethod
    def delete_class(cid):
        clas = Class.query.filter_by(c_id=cid).first()
        # clas = db.session.execute(db.select(Class.c_id, Class.c_na, Class.c_num).filter(Class.c_na == cname).delete())
        db.session.delete(clas)
        db.session.commit()

    # 添加某个班级
    # 已测试
    @staticmethod
    def add_class(cname):
        Class(cname).save()

# 个人上机统计页面
class PagePersonal:
    # 查看所有的个人预约(id,学号，开始时间)
    # 结果要强转为list
    @staticmethod
    def get_pes_all():
        pes = db.session.execute(db.select(One.o_id, One.s_id, One.s_start))
        return pes

    # 查看某个人的预约
    # 结果要强转为list
    @staticmethod
    def get_pes(sid):
        pes = db.session.execute(db.select(One.o_id, One.s_id, One.s_start).filter(One.s_id == sid))
        return pes

    # 添加个人预约
    @staticmethod
    def add_personal( s_id, cr_id, s_start):
        One( s_id, cr_id, s_start).save()
        res = ComputerRoom.query.filter_by(cr_id=cr_id).first()
        res.use_num = res.use_num - 1
        db.session.commit()

    # 删除某个人的预约
    #
    @staticmethod
    def delete_pes(sid):
        res = One.query.filter_by(s_id=sid).first()
        res = ComputerRoom.query.filter_by(cr_id=res.cr_id).first()
        res.use_num = res.use_num + 1
        db.session.commit()
        One.delete_by_sid(sid)


    # 某人完成了预约
    # 已测试
    @staticmethod
    def end_pes(sid):
        One.is_end(sid)
        res = One.query.filter_by(s_id=sid).first()
        sid = res.s_id
        crid = res.cr_id
        start = res.s_start
        end = res.s_end
        sql = "select TIMESTAMPDIFF(hour,one.s_start,one.s_end) from one where one.s_id = {}".format(sid)
        res1 = list(db.session.execute(sql))
        print(res1[0][0])
        sql ='select computerroom.price from computerroom where computerroom.cr_id = {}'.format(crid)
        res2 = list(db.session.execute(sql))
        print(res2[0][0])
        sql = "update student set student.s_money = student.s_money - {}*{}" \
              " where student.s_id = {}".format(res1[0][0], res2[0][0], sid)
        db.session.execute(sql)
        db.session.commit()
        db.session.delete(res)
        db.session.commit()
        res = ComputerRoom.query.filter_by(cr_id=crid).first()
        res.use_num = res.use_num + 1
        db.session.commit()

# 当前班级使用机房空闲情况及预约页面
class PageCompuRoomUseClass:

    # 获取现在所有的空闲的机房（id，名称，可用数量）
    #
    #
    @staticmethod
    def get_free_all():
        today_date = datetime.now().strftime('%Y-%m-%d %H:%M:%S')
        sql = "select computerroom.cr_id, computerroom.cr_na, computerroom.use_num from computerroom where " \
              "computerroom.cr_id not in(select creservation.cr_id from creservation) " \
              "and computerroom.use = '集体' order by computerroom.use_num DESC".format(today_date)
        result = db.session.execute(sql)
        return result

    # 班级预约
    #
    @staticmethod
    def class_rsv(c_id, crs_time, long):
        rsv = CReservation(c_id, crs_time, long)
        rsv.save()

# 个人机房空闲情况及上机使用登记页面
class PageCompuRoomUsePerson:

    # 获取现在所有的空闲的机房（id，名称，可用数量）
    #已测试
    #
    @staticmethod
    def get_free_all():
        sql = "select computerroom.cr_id, computerroom.cr_na, computerroom.use_num from computerroom"\
              " where computerroom.use = '个人' and computerroom.use_num > 0 order by computerroom.use_num ASC "
        result = db.session.execute(sql)
        return result

    # 个人上机登记
    #
    @staticmethod
    def person_rsv(s_id, cr_id, start):
        one = One(s_id, cr_id, start)
        one.save()

# 机房管理页面
class PgeComputerRoom:
    # 添加一个机房
    #已测试
    # 参数类型：机房地址（string），机房名称（string），电脑数量（int），机房用途（string（“集体”或“个人”）），机房价格（float）
    @staticmethod
    def add_cr(cr_adr, cr_na, cr_num, use, price):
        cr = ComputerRoom(cr_adr, cr_na, cr_num, use, price)
        cr.save()

    # 删除某个机房，按名字删除
    # 已测试
    @staticmethod
    def delete_cr(cr_id):
        cr = ComputerRoom.query.filter_by(cr_id=cr_id).first()
        db.session.delete(cr)
        db.session.commit()

# 登录界面
class PageUser:
    # 获取存储的用户的密码
    # 已测试
    # 返回值：list()强转后的格式为[(密码，权限)]，密码的类型为字符串，权限的类型为整型
    @staticmethod
    def get_pw(uer_name):
        result = db.session.execute(db.select(User.user_pw, User.power).filter(User.user_na == uer_name))
        return result

# 备份和恢复页面
class PaeBackupAndRestore:
    # 数据库备份
    @staticmethod
    def make_bakcup():
        backup.db_backup()

    # 数据库恢复
    @staticmethod
    def make_restore():
        restore.db_restore()


# 扣费功能的实现以及个人使用机房的可用数量的更新采用触发器由数据库自动实现,只需将扣费金额存入即可
