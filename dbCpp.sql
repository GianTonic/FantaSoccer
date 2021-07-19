-- phpMyAdmin SQL Dump
-- version 5.0.2
-- https://www.phpmyadmin.net/
--
-- Host: localhost
-- Creato il: Lug 08, 2021 alle 15:16
-- Versione del server: 10.4.11-MariaDB
-- Versione PHP: 7.4.5

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Database: `dbCpp`
--

-- --------------------------------------------------------

--
-- Struttura della tabella `day_point`
--

CREATE TABLE `day_point` (
  `squad` varchar(255) NOT NULL,
  `day` int(255) NOT NULL,
  `points` float DEFAULT 0
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

--
-- Dump dei dati per la tabella `day_point`
--

INSERT INTO `day_point` (`squad`, `day`, `points`) VALUES
('Palestina', 1, 14.5);

-- --------------------------------------------------------

--
-- Struttura della tabella `day_vote`
--

CREATE TABLE `day_vote` (
  `number` int(11) NOT NULL,
  `surname` varchar(255) NOT NULL,
  `vote` float DEFAULT 0
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

--
-- Dump dei dati per la tabella `day_vote`
--

INSERT INTO `day_vote` (`number`, `surname`, `vote`) VALUES
(1, 'Distefano', 7),
(1, 'Privitera', 7),
(1, 'Zagarella', 7.5);

-- --------------------------------------------------------

--
-- Struttura della tabella `login`
--

CREATE TABLE `login` (
  `name` varchar(32) NOT NULL,
  `pass` varchar(32) NOT NULL,
  `type` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

--
-- Dump dei dati per la tabella `login`
--

INSERT INTO `login` (`name`, `pass`, `type`) VALUES
('admin', '21232f297a57a5a743894a0e4a801fc3', 0),
('jenny', 'b59c67bf196a4758191e42f76670ceba', 1),
('zibibbo', 'b59c67bf196a4758191e42f76670ceba', 1);

-- --------------------------------------------------------

--
-- Struttura della tabella `player`
--

CREATE TABLE `player` (
  `id` int(10) NOT NULL,
  `squad` varchar(15) NOT NULL,
  `surname` varchar(15) NOT NULL,
  `role` varchar(5) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

--
-- Dump dei dati per la tabella `player`
--

INSERT INTO `player` (`id`, `squad`, `surname`, `role`) VALUES
(73, 'croazese', 'Gollini', 'P'),
(74, 'croazese', 'Da%20costa', 'P'),
(75, 'croazese', 'Carboni', 'D'),
(76, 'croazese', 'Golemic', 'D'),
(77, 'croazese', 'Luperto', 'D'),
(78, 'croazese', 'Magallan', 'D'),
(79, 'croazese', 'Biraghi', 'D'),
(80, 'croazese', 'Pezzella%20ger.', 'D'),
(81, 'croazese', 'Behrami', 'C'),
(82, 'croazese', 'Cataldi', 'C'),
(83, 'croazese', 'Ruiz', 'C'),
(84, 'croazese', 'Ekdal', 'C'),
(85, 'croazese', 'Verre', 'C'),
(86, 'croazese', 'Berardi', 'A'),
(87, 'croazese', 'Caputo', 'A'),
(88, 'croazese', 'Sanabria', 'A'),
(89, 'croazese', 'Bonazzoli', 'A'),
(90, 'croazese', 'Belotti', 'A');

-- --------------------------------------------------------

--
-- Struttura della tabella `squad`
--

CREATE TABLE `squad` (
  `id` int(10) NOT NULL,
  `name` varchar(15) NOT NULL,
  `owner` varchar(30) NOT NULL,
  `setup` int(11) NOT NULL DEFAULT -1
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

--
-- Dump dei dati per la tabella `squad`
--

INSERT INTO `squad` (`id`, `name`, `owner`, `setup`) VALUES
(26, 'Triestina', 'Jenny', 0),
(28, 'Palestina', 'Giovanni', 0),
(33, 'croazese', 'zibibbo', 1);

-- --------------------------------------------------------

--
-- Struttura della tabella `test`
--

CREATE TABLE `test` (
  `id` int(10) NOT NULL,
  `nome` varchar(20) NOT NULL,
  `cognome` varchar(20) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

--
-- Dump dei dati per la tabella `test`
--

INSERT INTO `test` (`id`, `nome`, `cognome`) VALUES
(1, 'Giovanni', 'Santoro'),
(2, 'Paolo', 'Zagarella');

--
-- Indici per le tabelle scaricate
--

--
-- Indici per le tabelle `day_point`
--
ALTER TABLE `day_point`
  ADD PRIMARY KEY (`squad`,`day`);

--
-- Indici per le tabelle `day_vote`
--
ALTER TABLE `day_vote`
  ADD PRIMARY KEY (`number`,`surname`);

--
-- Indici per le tabelle `login`
--
ALTER TABLE `login`
  ADD PRIMARY KEY (`name`);

--
-- Indici per le tabelle `player`
--
ALTER TABLE `player`
  ADD PRIMARY KEY (`id`);

--
-- Indici per le tabelle `squad`
--
ALTER TABLE `squad`
  ADD PRIMARY KEY (`id`),
  ADD UNIQUE KEY `name` (`name`);

--
-- Indici per le tabelle `test`
--
ALTER TABLE `test`
  ADD PRIMARY KEY (`id`);

--
-- AUTO_INCREMENT per le tabelle scaricate
--

--
-- AUTO_INCREMENT per la tabella `player`
--
ALTER TABLE `player`
  MODIFY `id` int(10) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=91;

--
-- AUTO_INCREMENT per la tabella `squad`
--
ALTER TABLE `squad`
  MODIFY `id` int(10) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=40;

--
-- AUTO_INCREMENT per la tabella `test`
--
ALTER TABLE `test`
  MODIFY `id` int(10) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=3;
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
