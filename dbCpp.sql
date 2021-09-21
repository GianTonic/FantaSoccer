-- phpMyAdmin SQL Dump
-- version 5.0.1
-- https://www.phpmyadmin.net/
--
-- Host: localhost
-- Creato il: Set 21, 2021 alle 20:00
-- Versione del server: 10.4.11-MariaDB
-- Versione PHP: 7.4.3

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET AUTOCOMMIT = 0;
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

-- --------------------------------------------------------

--
-- Struttura della tabella `day_vote`
--

CREATE TABLE `day_vote` (
  `number` int(11) NOT NULL,
  `surname` varchar(255) NOT NULL,
  `vote` float DEFAULT 0
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

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
('admin', '4a7d1ed414474e4033ac29ccb8653d9b', 0),
('esame', 'b59c67bf196a4758191e42f76670ceba', 1),
('giovanni', 'b59c67bf196a4758191e42f76670ceba', 1),
('jenny', 'b59c67bf196a4758191e42f76670ceba', 1);

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
(116, 'croazese', 'Szczesny', 'P'),
(117, 'croazese', 'Bonucci', 'D'),
(118, 'croazese', 'Bastoni', 'D'),
(119, 'croazese', 'De%20vrij', 'D'),
(120, 'croazese', 'Dumfries', 'D'),
(121, 'croazese', 'Calabria', 'D'),
(122, 'croazese', 'Veretout', 'C'),
(123, 'croazese', 'Luis%20alberto', 'C'),
(124, 'croazese', 'Barella', 'C'),
(125, 'croazese', 'Calhanoglu', 'C'),
(126, 'croazese', 'Mkhitaryan', 'C'),
(127, 'croazese', 'Pessina', 'C'),
(128, 'croazese', 'Muriel', 'A'),
(129, 'croazese', 'Gosens', 'D'),
(130, 'croazese', 'Chiesa', 'C'),
(131, 'croazese', 'Dybala', 'A'),
(132, 'croazese', 'Morata', 'A'),
(133, 'croazese', 'Martinez%20l.', 'A'),
(134, 'croazese', 'Dzeko', 'A'),
(135, 'Trieste', 'Maignan', 'P'),
(136, 'Trieste', 'Meret', 'P'),
(137, 'Trieste', 'Koulibaly', 'D'),
(138, 'Trieste', 'Manolas', 'D'),
(139, 'Trieste', 'Di%20lorenzo', 'D'),
(140, 'Trieste', 'Mario%20rui', 'D'),
(141, 'Trieste', 'Danilo', 'D'),
(142, 'Trieste', 'Chiellini', 'D'),
(143, 'Trieste', 'Tonali', 'C'),
(144, 'Trieste', 'Saelemaekers', 'C'),
(145, 'Trieste', 'Castrovilli', 'C'),
(146, 'Trieste', 'Brozovic', 'C'),
(147, 'Trieste', 'Kulusevski', 'C'),
(148, 'Trieste', 'Thorsby', 'C'),
(149, 'Trieste', 'Boga', 'A'),
(150, 'Trieste', 'Berardi', 'A'),
(151, 'Trieste', 'Deulofeu', 'A'),
(152, 'Trieste', 'Abraham', 'A'),
(153, 'Trieste', 'Shomurodov', 'A'),
(154, 'Trieste', 'Osimhen', 'A');

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
(26, 'croazese', 'Jenny', 0),
(57, 'Trieste', 'giovanni', 0);

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
  ADD PRIMARY KEY (`id`),
  ADD UNIQUE KEY `squad` (`squad`,`surname`);

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
  MODIFY `id` int(10) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=155;

--
-- AUTO_INCREMENT per la tabella `squad`
--
ALTER TABLE `squad`
  MODIFY `id` int(10) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=58;

--
-- AUTO_INCREMENT per la tabella `test`
--
ALTER TABLE `test`
  MODIFY `id` int(10) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=3;
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
