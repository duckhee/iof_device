-- --------------------------------------------------------
-- 호스트:                          192.168.0.17
-- 서버 버전:                        10.1.23-MariaDB-9+deb9u1 - Raspbian 9.0
-- 서버 OS:                        debian-linux-gnueabihf
-- HeidiSQL 버전:                  9.4.0.5125
-- --------------------------------------------------------

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET NAMES utf8 */;
/*!50503 SET NAMES utf8mb4 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;


-- iof 데이터베이스 구조 내보내기
CREATE DATABASE IF NOT EXISTS `iof` /*!40100 DEFAULT CHARACTER SET utf8mb4 */;
USE `iof`;

-- 테이블 iof.iof_data 구조 내보내기
CREATE TABLE IF NOT EXISTS `iof_data` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `sd_serial` varchar(255) NOT NULL,
  `temp_value` float DEFAULT '0',
  `soil_value` float DEFAULT '0',
  `createdAt` datetime NOT NULL DEFAULT CURRENT_TIMESTAMP,
  `updatedAt` datetime NOT NULL DEFAULT CURRENT_TIMESTAMP,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=228 DEFAULT CHARSET=utf8mb4;

-- 내보낼 데이터가 선택되어 있지 않습니다.
-- 테이블 iof.iof_images 구조 내보내기
CREATE TABLE IF NOT EXISTS `iof_images` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `si_serial` varchar(255) CHARACTER SET utf8 COLLATE utf8_unicode_ci NOT NULL,
  `si_path` varchar(255) CHARACTER SET utf8 COLLATE utf8_unicode_ci NOT NULL,
  `si_filename` varchar(255) CHARACTER SET utf8 COLLATE utf8_unicode_ci NOT NULL,
  `si_filesize` varchar(255) CHARACTER SET utf8 COLLATE utf8_unicode_ci NOT NULL,
  `createdAt` datetime NOT NULL DEFAULT CURRENT_TIMESTAMP,
  `updatedAt` datetime NOT NULL DEFAULT CURRENT_TIMESTAMP,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=39 DEFAULT CHARSET=utf8mb4;

-- 내보낼 데이터가 선택되어 있지 않습니다.
-- 테이블 iof.iof_networks 구조 내보내기
CREATE TABLE IF NOT EXISTS `iof_networks` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `si_serial` varchar(255) DEFAULT NULL,
  `si_type` enum('active','inactive') DEFAULT 'inactive',
  `createdAt` datetime NOT NULL DEFAULT CURRENT_TIMESTAMP,
  `updatedAt` datetime NOT NULL DEFAULT CURRENT_TIMESTAMP,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=13 DEFAULT CHARSET=utf8mb4;

-- 내보낼 데이터가 선택되어 있지 않습니다.
-- 테이블 iof.iof_sensor 구조 내보내기
CREATE TABLE IF NOT EXISTS `iof_sensor` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `sensor_info` varchar(255) DEFAULT NULL,
  `createdAt` datetime NOT NULL DEFAULT CURRENT_TIMESTAMP,
  `updatedAt` datetime NOT NULL DEFAULT CURRENT_TIMESTAMP,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=50 DEFAULT CHARSET=utf8mb4;

-- 내보낼 데이터가 선택되어 있지 않습니다.
-- 테이블 iof.iof_settings 구조 내보내기
CREATE TABLE IF NOT EXISTS `iof_settings` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `st_serial` varchar(255) NOT NULL,
  `st_shootingtime` varchar(255) DEFAULT '30',
  `st_watertime` varchar(255) DEFAULT '1',
  `createdAt` datetime NOT NULL DEFAULT CURRENT_TIMESTAMP,
  `updatedAt` datetime NOT NULL DEFAULT CURRENT_TIMESTAMP,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=8 DEFAULT CHARSET=utf8mb4;

-- 내보낼 데이터가 선택되어 있지 않습니다.
/*!40101 SET SQL_MODE=IFNULL(@OLD_SQL_MODE, '') */;
/*!40014 SET FOREIGN_KEY_CHECKS=IF(@OLD_FOREIGN_KEY_CHECKS IS NULL, 1, @OLD_FOREIGN_KEY_CHECKS) */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
