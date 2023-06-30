-- MySQL dump 10.13  Distrib 8.0.33, for Win64 (x86_64)
--
-- Host: localhost    Database: chat
-- ------------------------------------------------------
-- Server version	8.0.33

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
-- Table structure for table `global_message`
--

DROP TABLE IF EXISTS `global_message`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `global_message` (
  `id` int NOT NULL AUTO_INCREMENT,
  `id_from` int DEFAULT NULL,
  `text` text,
  `date` timestamp NULL DEFAULT CURRENT_TIMESTAMP,
  `status` int DEFAULT '1',
  PRIMARY KEY (`id`),
  KEY `id_from` (`id_from`),
  CONSTRAINT `global_message_ibfk_1` FOREIGN KEY (`id_from`) REFERENCES `users` (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=18 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `global_message`
--

LOCK TABLES `global_message` WRITE;
/*!40000 ALTER TABLE `global_message` DISABLE KEYS */;
INSERT INTO `global_message` VALUES (1,8,'Hello','2023-06-23 21:49:52',1),(2,1,'Hello','2023-06-23 22:36:58',1),(3,11,'привет','2023-06-26 11:30:50',1),(4,12,'hh','2023-06-28 00:36:02',1),(5,12,'vv','2023-06-28 00:36:20',1),(6,12,'Hello','2023-06-28 00:38:05',1),(7,12,'Buy','2023-06-28 00:38:32',1),(8,12,'Buy','2023-06-28 00:42:37',1),(9,12,'buy','2023-06-28 08:58:00',1),(10,12,'Hello','2023-06-28 09:41:41',1),(11,1,'ghfj','2023-06-28 19:19:09',1),(12,1,'Hello','2023-06-28 19:45:21',1),(13,12,'Hello','2023-06-29 11:49:10',1),(14,8,'hello','2023-06-29 11:50:41',1),(15,8,'Hello','2023-06-29 12:42:56',1),(16,8,'Hello','2023-06-30 05:05:01',1),(17,8,'Hello','2023-06-30 05:26:53',1);
/*!40000 ALTER TABLE `global_message` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2023-06-30 20:24:51
