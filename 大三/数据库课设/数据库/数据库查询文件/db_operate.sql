use computerroo

-- DECLARE price INT(2);
-- SET price := (SELECT price FROM computerroom WHERE computerroom.cr_id = new.cr_id);

-- 实现自动扣费功能的触发器，个人上机表 
CREATE TRIGGER SUBB_MONEY_PERSON
AFTER UPDATE ON one
FOR EACH ROW
BEGIN
	IF(new.s_end IS NOT NULL)
	THEN
		UPDATE student SET s_money = s_money - TIMESTAMPDIFF(HOUR,new.s_start,new.s_end)*(SELECT price FROM computerroom WHERE computerroom.cr_id = new.cr_id) WHERE student.s_id = new.s_id;
	END IF;
END;

-- 删除实现个人自动扣费功能的触发器（个人结束时扣费）
drop trigger SUBB_MONEY_PERSON;

-- 实现自动扣费功能的触发器，班级预约表 
CREATE TRIGGER SUBB_MONEY_CLASS
AFTER UPDATE ON creservation
FOR EACH ROW
BEGIN
	IF(new.finish = 1)
	THEN
		UPDATE student SET s_money = s_money - new.crs_long*(SELECT price FROM computerroom WHERE computerroom.cr_id = new.cr_id) WHERE student.s_id IN(SELECT stu1.s_id FROM student stu1 WHERE stu1.c_id = new.c_id);
	END IF;
END;

-- 删除实现班级自动扣费功能的触发器（班级完成时扣费）
drop trigger SUBB_MONEY_CLASS;

-- 实现个人机房的可用数量更新的触发器
CREATE TRIGGER CHANGE_COMPUTERROOM_NUM_PERSON
AFTER INSERT ON one
FOR EACH ROW
BEGIN
	IF(new.s_start IS NOT NULL AND new.s_end IS NULL)
	THEN
		UPDATE computerroom SET use_num = use_num - 1 WHERE computerroom.cr_id = new.cr_id;
	END IF;
END;

-- 删除实现个人机房的可用数量更新的触发器
drop trigger CHANGE_COMPUTERROOM_NUM_PERSON;

-- 添加两种权限的可以登录机房管理系统的用户的账户和密码
INSERT INTO `user` (`user`.user_na,`user`.user_pw,`user`.power) VALUES ('user1','123456',0)
INSERT INTO `user` (`user`.user_na,`user`.user_pw,`user`.power) VALUES ('root','123456',1)

