TYPE=TRIGGERS
triggers='CREATE DEFINER=`root`@`localhost` TRIGGER CLASS_STUDENT_ADD\nAFTER INSERT ON student\nFOR EACH ROW\nBEGIN\n		UPDATE class SET class.c_num = class.c_num + 1 WHERE new.c_id = class.c_id;\nEND' 'CREATE DEFINER=`root`@`localhost` TRIGGER CLASS_STUDENT_SUB\nAFTER DELETE ON student\nFOR EACH ROW\nBEGIN\n		UPDATE class SET class.c_num = class.c_num - 1 WHERE old.c_id = class.c_id;\nEND'
sql_modes=1436549152 1436549152
definers='root@localhost' 'root@localhost'
client_cs_names='utf8mb4' 'utf8mb4'
connection_cl_names='utf8mb4_general_ci' 'utf8mb4_general_ci'
db_cl_names='utf8_general_ci' 'utf8_general_ci'
created=165522083242 165522100569
