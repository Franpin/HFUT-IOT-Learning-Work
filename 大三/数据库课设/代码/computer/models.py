# 数据库模型的定义
from datetime import datetime
from flask_sqlalchemy import SQLAlchemy


db = SQLAlchemy()


# 机房表
class ComputerRoom(db.Model):
    __tablename__ = 'computerroom'
    cr_id = db.Column(db.Integer, autoincrement=True, primary_key=True)
    cr_adr = db.Column(db.String(20), unique=True, nullable=False)
    cr_na = db.Column(db.String(20), unique=True, nullable=False)
    cr_num = db.Column(db.Integer, nullable=False)
    use_num = db.Column(db.Integer, nullable=False)
    # 两种用途：个人和集体，每个机房只能选择一种用途
    use = db.Column(db.String(4))
    price = db.Column(db.Numeric(4, 1))

    def __init__(self, cr_adr, cr_na, cr_num, use, price):
        self.cr_num = cr_num
        self.use_num = cr_num
        self.cr_na = cr_na
        self.cr_adr = cr_adr
        self.use = use
        self.price = price

    # 添加
    def save(self):
        db.session.add(self)
        db.session.commit()

    # 按id删除
    @staticmethod
    def delete_by_id(crid):
        cr = ComputerRoom.query.filter_by(cr_id=crid)
        db.session.delete(cr)
        db.session.commit()

    # 按名字获取
    @staticmethod
    def get_by_name(crname):
        cr = ComputerRoom.query.filter_by(cr_na=crname).first()
        return cr


# 班级表
class Class(db.Model):
    __tablename__ = 'class'
    c_id = db.Column(db.Integer, autoincrement=True, primary_key=True)
    c_na = db.Column(db.String(20), unique=True, nullable=False)
    c_num = db.Column(db.Integer, nullable=False)

    def __init__(self, c_na, c_num = 0):
        self.c_na = c_na
        self.c_num = c_num

    # 添加
    def save(self):
        db.session.add(self)
        db.session.commit()

    # 按id删除
    @staticmethod
    def delete_by_id(cid):
        c = Class.query.filter_by(c_id=cid)
        db.session.delete(c)
        db.session.commit()

    # 按名字获取
    @staticmethod
    def get_by_name(cid):
        c = Class.query.filter_by(c_id=cid).first()
        return c


# 学生表
class Student(db.Model):
    __tablename__ = 'student'
    s_id = db.Column(db.Integer, primary_key=True)
    s_na = db.Column(db.String(10))
    c_id = db.Column(db.Integer, db.ForeignKey('class.c_id'), nullable=False)
    s_money = db.Column(db.Numeric(4, 1))
    s_class = db.relationship('Class', backref='students')

    def __init__(self, s_id, s_na, c_id, s_money):
        self.s_id = s_id
        self.s_na = s_na
        self.c_id = c_id
        self.s_money = s_money

    # 添加
    def save(self):
        db.session.add(self)
        db.session.commit()

    # 按学号删除
    @staticmethod
    def delete_by_id(sid):
        stu = Student.query.filter_by(s_id=sid).first()
        db.session.delete(stu)
        db.session.commit()

    # 按学生学号获取
    @staticmethod
    def get_by_id(sid):
        stu = Student.query.filter_by(s_id=sid).first()
        return stu


# 班级上机预约表
class CReservation(db.Model):
    __tablename__ = 'creservation'
    crs_id = db.Column(db.Integer, autoincrement=True, primary_key=True)
    c_id = db.Column(db.Integer, db.ForeignKey('class.c_id'), primary_key=True)
    cr_id = db.Column(db.Integer, db.ForeignKey('computerroom.cr_id'), nullable=False)
    crs_time = db.Column(db.DateTime)
    crs_long = db.Column(db.SmallInteger)
    coment  = db.Column(db.String(20))
    finish = db.Column(db.SmallInteger, default=0)
    crs_class = db.relationship('Class', backref='crs')
    crsroom = db.relationship('ComputerRoom', backref='cclass')

    def __init__(self, c_id, crs_time, long,cr_id):
        self.crs_time = crs_time
        self.crs_long = long
        self.c_id = c_id
        self.cr_id = cr_id
    # 添加
    def save(self):
        db.session.add(self)
        db.session.commit()

    # 班级预约结束
    @staticmethod
    def is_end(crsid):
        crs = CReservation.query.filter_by(crs_id=crsid).first()
        crs.finish = 1
        db.session.commit()

    # 按id删除
    @staticmethod
    def delete_by_id(crsid):
        crs = CReservation.query.filter_by(crs_id=crsid).first()
        db.session.delete(crs)
        db.session.commit()

    # 按id获取
    @staticmethod
    def get_by_id(crsid):
        stu = CReservation.query.filter_by(crs_id=crsid).first()
        return stu


# 个人上机表
class One(db.Model):
    __tablename__ = 'one'
    o_id = db.Column(db.Integer, autoincrement=True, primary_key=True)
    s_id = db.Column(db.Integer, db.ForeignKey('student.s_id'), unique=True)
    cr_id = db.Column(db.Integer, db.ForeignKey('computerroom.cr_id'))
    s_start = db.Column(db.DateTime)
    s_end = db.Column(db.DateTime, nullable=True)
    student = db.relationship('Student', backref=db.backref('one', uselist=False))
    sroom = db.relationship('ComputerRoom', backref='students')

    def __init__(self, s_id, cr_id, s_start):
        self.s_id = s_id
        self.cr_id = cr_id
        self.s_start = s_start

    # 添加
    def save(self):
        db.session.add(self)
        db.session.commit()

    # 个人上机结束
    @staticmethod
    def is_end(sid):
        one = One.query.filter_by(s_id=sid).first()
        print(one)
        one.s_end = datetime.now()
        db.session.commit()

    # 按学号删除
    @staticmethod
    def delete_by_sid(sid):
        one = One.query.filter_by(s_id=sid).first()
        db.session.delete(one)
        db.session.commit()

# 用户表(0:可查询用户，1：管理员用户)
class User(db.Model):
    __tablename__ = 'user'
    user_id = db.Column(db.Integer, autoincrement=True, primary_key=True)
    user_na = db.Column(db.String(10), unique=True, nullable=False)
    user_pw = db.Column(db.String(30), nullable=False)
    power = db.Column(db.SmallInteger)

    def __init__(self, user_id, user_na, user_pw, power):
        self.user_id = user_id
        self.user_na = user_na
        self.user_pw = user_pw
        self.power = power

    def save(self):
        db.session.add(self)
        db.session.commit()
