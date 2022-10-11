TYPE=TRIGGERS
triggers='CREATE DEFINER=`root`@`localhost` TRIGGER CHANGE_COMPUTERROOM_NUM_PERSON\nAFTER INSERT ON one\nFOR EACH ROW\nBEGIN\n	IF(new.s_start IS NOT NULL AND new.s_end IS NULL)\n	THEN\n		UPDATE computerroom SET use_num = use_num - 1 WHERE computerroom.cr_id = new.cr_id;\n	END IF;\nEND' 'CREATE DEFINER=`root`@`localhost` TRIGGER SUBB_MONEY_PERSON\nAFTER UPDATE ON one\nFOR EACH ROW\nBEGIN\n	IF(new.s_end IS NOT NULL)\n	THEN\n		UPDATE student SET s_money = s_money - TIMESTAMPDIFF(HOUR,new.s_start,new.s_end)*(SELECT price FROM computerroom WHERE computerroom.cr_id = new.cr_id) WHERE student.s_id = new.s_id;\n	END IF;\nEND'
sql_modes=1436549152 1436549152
definers='root@localhost' 'root@localhost'
client_cs_names='utf8mb4' 'utf8mb4'
connection_cl_names='utf8mb4_general_ci' 'utf8mb4_general_ci'
db_cl_names='utf8_general_ci' 'utf8_general_ci'
created=165484383232 165484226654
