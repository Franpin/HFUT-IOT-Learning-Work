-- MySQL dump 10.13  Distrib 8.0.29, for Win64 (x86_64)
--
-- Host: localhost    Database: computer
-- ------------------------------------------------------
-- Server version	8.0.29

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!50503 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `alembic_version`
--

DROP TABLE IF EXISTS `alembic_version`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `alembic_version` (
  `version_num` varchar(32) NOT NULL,
  PRIMARY KEY (`version_num`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `alembic_version`
--

LOCK TABLES `alembic_version` WRITE;
/*!40000 ALTER TABLE `alembic_version` DISABLE KEYS */;
INSERT INTO `alembic_version` VALUES ('042b9df60055');
/*!40000 ALTER TABLE `alembic_version` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `class`
--

DROP TABLE IF EXISTS `class`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `class` (
  `c_id` int NOT NULL AUTO_INCREMENT,
  `c_na` varchar(20) NOT NULL,
  `c_num` int NOT NULL,
  PRIMARY KEY (`c_id`),
  UNIQUE KEY `c_na` (`c_na`)
) ENGINE=InnoDB AUTO_INCREMENT=29 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `class`
--

LOCK TABLES `class` WRITE;
/*!40000 ALTER TABLE `class` DISABLE KEYS */;
INSERT INTO `class` VALUES (1,'????????????',1),(2,'?????????19-2???',0),(3,'?????????18-2???',2),(4,'?????????18-1???',1),(5,'????????????????????????17-1???',1),(6,'????????????????????????17-2???',1),(7,'????????????????????????17-3???',1),(8,'????????????????????????17-4???',1),(9,'????????????????????????17-5???',1),(10,'????????????????????????19-1???',0),(11,'????????????????????????19-2???',0),(12,'????????????????????????19-3???',0),(22,'?????????3???',0),(23,'?????????21-1???',0),(26,'?????????19-2???',0),(27,'?????????19-3???',0),(28,'?????????20-3???',0);
/*!40000 ALTER TABLE `class` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `computerroom`
--

DROP TABLE IF EXISTS `computerroom`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `computerroom` (
  `cr_id` int NOT NULL AUTO_INCREMENT,
  `cr_adr` varchar(20) NOT NULL,
  `cr_na` varchar(20) NOT NULL,
  `cr_num` int NOT NULL,
  `use_num` int NOT NULL,
  `use` varchar(4) DEFAULT NULL,
  `price` decimal(4,1) DEFAULT NULL,
  PRIMARY KEY (`cr_id`),
  UNIQUE KEY `cr_adr` (`cr_adr`),
  UNIQUE KEY `cr_na` (`cr_na`)
) ENGINE=InnoDB AUTO_INCREMENT=12 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `computerroom`
--

LOCK TABLES `computerroom` WRITE;
/*!40000 ALTER TABLE `computerroom` DISABLE KEYS */;
INSERT INTO `computerroom` VALUES (1,'3120','????????????1?????????',50,50,'??????',10.0),(2,'3121','????????????2?????????',51,51,'??????',11.0),(3,'3122','????????????3?????????',52,52,'??????',12.0),(4,'3123','????????????4?????????',53,53,'??????',13.0),(5,'3124','????????????5?????????',54,54,'??????',14.0),(6,'3125','????????????6?????????',55,55,'??????',15.0),(7,'3126','????????????7?????????',56,56,'??????',16.0),(8,'3127','????????????8?????????',57,58,'??????',17.0),(9,'3128','????????????9?????????',58,58,'??????',18.0),(10,'????????????','????????????',60,60,'??????',60.0),(11,'10001','???9??????',50,50,'??????',600.0);
/*!40000 ALTER TABLE `computerroom` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `creservation`
--

DROP TABLE IF EXISTS `creservation`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `creservation` (
  `crs_id` int NOT NULL AUTO_INCREMENT,
  `c_id` int NOT NULL,
  `cr_id` int NOT NULL,
  `crs_time` datetime DEFAULT NULL,
  `crs_long` smallint DEFAULT NULL,
  `coment` varchar(20) DEFAULT NULL,
  `finish` smallint DEFAULT NULL,
  PRIMARY KEY (`crs_id`,`c_id`),
  KEY `c_id` (`c_id`),
  KEY `cr_id` (`cr_id`),
  CONSTRAINT `creservation_ibfk_1` FOREIGN KEY (`c_id`) REFERENCES `class` (`c_id`),
  CONSTRAINT `creservation_ibfk_2` FOREIGN KEY (`cr_id`) REFERENCES `computerroom` (`cr_id`)
) ENGINE=InnoDB AUTO_INCREMENT=14 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `creservation`
--

LOCK TABLES `creservation` WRITE;
/*!40000 ALTER TABLE `creservation` DISABLE KEYS */;
INSERT INTO `creservation` VALUES (2,2,2,'2022-05-11 00:00:00',40,NULL,1),(3,3,3,'2022-05-12 00:00:00',60,NULL,0),(11,10,8,'2022-10-23 00:00:00',99,NULL,1),(12,6,6,'2022-10-23 00:00:00',80,NULL,0);
/*!40000 ALTER TABLE `creservation` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `one`
--

DROP TABLE IF EXISTS `one`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `one` (
  `o_id` int NOT NULL AUTO_INCREMENT,
  `s_id` int DEFAULT NULL,
  `cr_id` int DEFAULT NULL,
  `s_start` datetime DEFAULT NULL,
  `s_end` datetime DEFAULT NULL,
  PRIMARY KEY (`o_id`),
  UNIQUE KEY `s_id` (`s_id`),
  KEY `cr_id` (`cr_id`),
  CONSTRAINT `one_ibfk_1` FOREIGN KEY (`cr_id`) REFERENCES `computerroom` (`cr_id`),
  CONSTRAINT `one_ibfk_2` FOREIGN KEY (`s_id`) REFERENCES `student` (`s_id`)
) ENGINE=InnoDB AUTO_INCREMENT=17 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `one`
--

LOCK TABLES `one` WRITE;
/*!40000 ALTER TABLE `one` DISABLE KEYS */;
INSERT INTO `one` VALUES (13,12008,7,'2022-06-15 00:00:00',NULL),(14,2019217819,8,'2022-06-15 00:00:00',NULL),(16,12006,7,'2022-06-16 00:00:00',NULL);
/*!40000 ALTER TABLE `one` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `student`
--

DROP TABLE IF EXISTS `student`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `student` (
  `s_id` int NOT NULL AUTO_INCREMENT,
  `s_na` varchar(10) DEFAULT NULL,
  `c_id` int NOT NULL,
  `s_money` decimal(4,1) DEFAULT NULL,
  PRIMARY KEY (`s_id`),
  KEY `c_id` (`c_id`),
  CONSTRAINT `student_ibfk_1` FOREIGN KEY (`c_id`) REFERENCES `class` (`c_id`)
) ENGINE=InnoDB AUTO_INCREMENT=2019217821 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `student`
--

LOCK TABLES `student` WRITE;
/*!40000 ALTER TABLE `student` DISABLE KEYS */;
INSERT INTO `student` VALUES (12000,'???0',1,400.0),(12002,'???2',3,600.0),(12003,'???3',4,348.0),(12004,'???4',5,500.0),(12005,'???5',6,600.0),(12006,'???6',7,700.0),(12007,'???7',8,290.0),(12008,'???8',9,900.0),(12010,'?????????',3,145.0),(12345,'?????????',3,555.0),(2019217819,'??????',3,339.0),(2019217820,'??????',23,300.0);
/*!40000 ALTER TABLE `student` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `user`
--

DROP TABLE IF EXISTS `user`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `user` (
  `user_id` int NOT NULL AUTO_INCREMENT,
  `user_na` varchar(10) NOT NULL,
  `user_pw` varchar(30) NOT NULL,
  `power` smallint DEFAULT NULL,
  PRIMARY KEY (`user_id`),
  UNIQUE KEY `user_na` (`user_na`)
) ENGINE=InnoDB AUTO_INCREMENT=4 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `user`
--

LOCK TABLES `user` WRITE;
/*!40000 ALTER TABLE `user` DISABLE KEYS */;
INSERT INTO `user` VALUES (3,'Franpin','123456',20);
/*!40000 ALTER TABLE `user` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2022-06-26 11:20:18
