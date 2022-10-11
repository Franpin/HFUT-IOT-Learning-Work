TYPE=TRIGGERS
triggers='CREATE DEFINER=`root`@`localhost` TRIGGER SUBB_MONEY_CLASS\nAFTER UPDATE ON creservation\nFOR EACH ROW\nBEGIN\n	IF(new.finish = 1)\n	THEN\n		UPDATE student SET s_money = s_money - new.crs_long*(SELECT price FROM computerroom WHERE computerroom.cr_id = new.cr_id) WHERE student.s_id IN(SELECT stu1.s_id FROM student stu1 WHERE stu1.c_id = new.c_id);\n	END IF;\nEND'
sql_modes=1436549152
definers='root@localhost'
client_cs_names='utf8mb4'
connection_cl_names='utf8mb4_general_ci'
db_cl_names='utf8_general_ci'
created=165484361813
