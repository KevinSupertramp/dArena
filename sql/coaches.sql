-- phpMyAdmin SQL Dump
-- version 3.5.1
-- http://www.phpmyadmin.net
--
-- Client: localhost
-- Généré le: Jeu 19 Juin 2014 à 11:21
-- Version du serveur: 5.5.24-log
-- Version de PHP: 5.4.3

SET SQL_MODE="NO_AUTO_VALUE_ON_ZERO";
SET time_zone = "+00:00";

--
-- Base de données: `darena_coach`
--
CREATE DATABASE `darena_coach` DEFAULT CHARACTER SET latin1 COLLATE latin1_swedish_ci;
USE `darena_coach`;

-- --------------------------------------------------------

--
-- Structure de la table `coaches`
--

CREATE TABLE IF NOT EXISTS `coaches` (
  `guid` int(10) unsigned NOT NULL,
  `name` varchar(15) COLLATE utf8_unicode_ci NOT NULL,
  `gender` tinyint(3) unsigned NOT NULL,
  `level` smallint(5) unsigned NOT NULL DEFAULT '1',
  `xp` smallint(5) unsigned NOT NULL,
  `skin_color` int(11) NOT NULL,
  `hair_color` int(11) NOT NULL,
  `position_x` int(11) NOT NULL,
  `position_y` int(11) NOT NULL,
  `position_z` int(11) NOT NULL,
  `direction` int(11) NOT NULL,
  `instance_id` int(11) NOT NULL,
  PRIMARY KEY (`guid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci;

--
-- Contenu de la table `coaches`
--

INSERT INTO `coaches` (`guid`, `name`, `gender`, `level`, `xp`, `skin_color`, `hair_color`, `position_x`, `position_y`, `position_z`, `direction`, `instance_id`) VALUES
(1, 'Mia', 1, 1, 0, 10, 0, 0, 0, 0, 0, 0);