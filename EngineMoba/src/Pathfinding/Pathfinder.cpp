#include "Pathfinder.h"
#define DEBUGPATHFINDING false




Pathfinder::Pathfinder()
{
}



void Pathfinder::InitGraph()
{
	nodes.reserve(76);
	nodes.push_back(LMVector3(131.91, 0.10, 59.95));
	nodes.push_back(LMVector3(59.42, 0.10, 131.84));
	nodes.push_back(LMVector3(52.48, 0.10, 302.87));
	nodes.push_back(LMVector3(97.64, 0.10, 348.38));
	nodes.push_back(LMVector3(267.38, 0.10, 341.42));
	nodes.push_back(LMVector3(341.05, 0.10, 268.48));
	nodes.push_back(LMVector3(348.10, 0.10, 97.12));
	nodes.push_back(LMVector3(303.05, 0.10, 50.86));
	nodes.push_back(LMVector3(103.82, 0.10, 50.01));
	nodes.push_back(LMVector3(50.24, 0.10, 103.74));
	nodes.push_back(LMVector3(137.70, 0.10, 138.24));
	nodes.push_back(LMVector3(145.09, 0.10, 74.55));
	nodes.push_back(LMVector3(189.20, 0.10, 38.71));
	nodes.push_back(LMVector3(206.81, 0.10, 81.83));
	nodes.push_back(LMVector3(208.72, 0.10, 39.01));
	nodes.push_back(LMVector3(224.84, 0.10, 79.82));
	nodes.push_back(LMVector3(282.94, 0.10, 78.31));
	nodes.push_back(LMVector3(265.37, 0.10, 36.48));
	nodes.push_back(LMVector3(321.78, 0.10, 47.84));
	nodes.push_back(LMVector3(355.66, 0.10, 76.84));
	nodes.push_back(LMVector3(307.09, 0.10, 98.81));
	nodes.push_back(LMVector3(321.57, 0.10, 117.71));
	nodes.push_back(LMVector3(363.59, 0.10, 135.03));
	nodes.push_back(LMVector3(362.10, 0.10, 193.52));
	nodes.push_back(LMVector3(320.16, 0.10, 172.71));
	nodes.push_back(LMVector3(297.64, 0.10, 122.48));
	nodes.push_back(LMVector3(302.39, 0.10, 166.16));
	nodes.push_back(LMVector3(260.37, 0.10, 156.50));
	nodes.push_back(LMVector3(364.16, 0.10, 213.29));
	nodes.push_back(LMVector3(315.11, 0.10, 194.56));
	nodes.push_back(LMVector3(327.70, 0.10, 252.44));
	nodes.push_back(LMVector3(299.90, 0.10, 191.82));
	nodes.push_back(LMVector3(241.24, 0.10, 176.57));
	nodes.push_back(LMVector3(250.45, 0.10, 236.29));
	nodes.push_back(LMVector3(303.38, 0.10, 248.46));
	nodes.push_back(LMVector3(277.28, 0.10, 105.30));
	nodes.push_back(LMVector3(233.50, 0.10, 96.61));
	nodes.push_back(LMVector3(245.47, 0.10, 138.19));
	nodes.push_back(LMVector3(207.20, 0.10, 101.60));
	nodes.push_back(LMVector3(153.11, 0.10, 97.13));
	nodes.push_back(LMVector3(163.03, 0.10, 148.77));
	nodes.push_back(LMVector3(223.71, 0.10, 157.45));
	nodes.push_back(LMVector3(149.70, 0.10, 163.52));
	nodes.push_back(LMVector3(97.55, 0.10, 151.89));
	nodes.push_back(LMVector3(99.41, 0.10, 208.52));
	nodes.push_back(LMVector3(157.78, 0.10, 223.91));
	nodes.push_back(LMVector3(72.40, 0.10, 147.61));
	nodes.push_back(LMVector3(36.22, 0.10, 187.26));
	nodes.push_back(LMVector3(84.95, 0.10, 204.92));
	nodes.push_back(LMVector3(38.61, 0.10, 207.10));
	nodes.push_back(LMVector3(79.65, 0.10, 226.70));
	nodes.push_back(LMVector3(78.60, 0.10, 282.51));
	nodes.push_back(LMVector3(36.90, 0.10, 264.23));
	nodes.push_back(LMVector3(98.41, 0.10, 233.75));
	nodes.push_back(LMVector3(138.55, 0.10, 243.32));
	nodes.push_back(LMVector3(103.18, 0.10, 277.33));
	nodes.push_back(LMVector3(44.46, 0.10, 323.27));
	nodes.push_back(LMVector3(93.40, 0.10, 301.18));
	nodes.push_back(LMVector3(79.55, 0.10, 354.41));
	nodes.push_back(LMVector3(117.74, 0.10, 322.98));
	nodes.push_back(LMVector3(135.26, 0.10, 363.70));
	nodes.push_back(LMVector3(191.81, 0.10, 361.75));
	nodes.push_back(LMVector3(173.82, 0.10, 321.72));
	nodes.push_back(LMVector3(166.65, 0.10, 302.80));
	nodes.push_back(LMVector3(154.06, 0.10, 261.84));
	nodes.push_back(LMVector3(122.07, 0.10, 295.58));
	nodes.push_back(LMVector3(175.81, 0.10, 241.78));
	nodes.push_back(LMVector3(192.83, 0.10, 297.68));
	nodes.push_back(LMVector3(247.44, 0.10, 302.55));
	nodes.push_back(LMVector3(238.67, 0.10, 252.13));
	nodes.push_back(LMVector3(254.60, 0.10, 326.39));
	nodes.push_back(LMVector3(211.10, 0.10, 361.19));
	nodes.push_back(LMVector3(194.15, 0.10, 318.47));
	nodes.push_back(LMVector3(295.41, 0.10, 351.04));
	nodes.push_back(LMVector3(350.42, 0.10, 297.28));
	nodes.push_back(LMVector3(261.30, 0.10, 260.46));

	m_graph.resize(76);
	m_graph.at(0).push_back(&nodes.at(0));
	m_graph.at(0).push_back(&nodes.at(8));
	m_graph.at(0).push_back(&nodes.at(10));
	m_graph.at(0).push_back(&nodes.at(11));
	m_graph.at(0).push_back(&nodes.at(12));
	m_graph.at(0).push_back(&nodes.at(39));
	m_graph.at(0).push_back(&nodes.at(40));
	m_graph.at(0).push_back(&nodes.at(42));
	m_graph.at(0).push_back(&nodes.at(45));
	m_graph.at(0).push_back(&nodes.at(61));
	m_graph.at(0).push_back(&nodes.at(62));
	m_graph.at(0).push_back(&nodes.at(66));
	m_graph.at(0).push_back(&nodes.at(72));
	m_graph.at(1).push_back(&nodes.at(1));
	m_graph.at(1).push_back(&nodes.at(9));
	m_graph.at(1).push_back(&nodes.at(10));
	m_graph.at(1).push_back(&nodes.at(23));
	m_graph.at(1).push_back(&nodes.at(24));
	m_graph.at(1).push_back(&nodes.at(29));
	m_graph.at(1).push_back(&nodes.at(31));
	m_graph.at(1).push_back(&nodes.at(32));
	m_graph.at(1).push_back(&nodes.at(40));
	m_graph.at(1).push_back(&nodes.at(41));
	m_graph.at(1).push_back(&nodes.at(42));
	m_graph.at(1).push_back(&nodes.at(43));
	m_graph.at(1).push_back(&nodes.at(46));
	m_graph.at(1).push_back(&nodes.at(47));
	m_graph.at(2).push_back(&nodes.at(2));
	m_graph.at(2).push_back(&nodes.at(51));
	m_graph.at(2).push_back(&nodes.at(52));
	m_graph.at(2).push_back(&nodes.at(55));
	m_graph.at(2).push_back(&nodes.at(56));
	m_graph.at(2).push_back(&nodes.at(57));
	m_graph.at(2).push_back(&nodes.at(64));
	m_graph.at(2).push_back(&nodes.at(65));
	m_graph.at(2).push_back(&nodes.at(66));
	m_graph.at(3).push_back(&nodes.at(3));
	m_graph.at(3).push_back(&nodes.at(43));
	m_graph.at(3).push_back(&nodes.at(44));
	m_graph.at(3).push_back(&nodes.at(45));
	m_graph.at(3).push_back(&nodes.at(48));
	m_graph.at(3).push_back(&nodes.at(53));
	m_graph.at(3).push_back(&nodes.at(54));
	m_graph.at(3).push_back(&nodes.at(55));
	m_graph.at(3).push_back(&nodes.at(57));
	m_graph.at(3).push_back(&nodes.at(58));
	m_graph.at(3).push_back(&nodes.at(59));
	m_graph.at(3).push_back(&nodes.at(60));
	m_graph.at(3).push_back(&nodes.at(65));
	m_graph.at(4).push_back(&nodes.at(4));
	m_graph.at(4).push_back(&nodes.at(13));
	m_graph.at(4).push_back(&nodes.at(14));
	m_graph.at(4).push_back(&nodes.at(15));
	m_graph.at(4).push_back(&nodes.at(32));
	m_graph.at(4).push_back(&nodes.at(33));
	m_graph.at(4).push_back(&nodes.at(41));
	m_graph.at(4).push_back(&nodes.at(68));
	m_graph.at(4).push_back(&nodes.at(69));
	m_graph.at(4).push_back(&nodes.at(70));
	m_graph.at(4).push_back(&nodes.at(71));
	m_graph.at(4).push_back(&nodes.at(73));
	m_graph.at(4).push_back(&nodes.at(75));
	m_graph.at(5).push_back(&nodes.at(5));
	m_graph.at(5).push_back(&nodes.at(28));
	m_graph.at(5).push_back(&nodes.at(30));
	m_graph.at(5).push_back(&nodes.at(33));
	m_graph.at(5).push_back(&nodes.at(34));
	m_graph.at(5).push_back(&nodes.at(44));
	m_graph.at(5).push_back(&nodes.at(45));
	m_graph.at(5).push_back(&nodes.at(48));
	m_graph.at(5).push_back(&nodes.at(49));
	m_graph.at(5).push_back(&nodes.at(50));
	m_graph.at(5).push_back(&nodes.at(66));
	m_graph.at(5).push_back(&nodes.at(69));
	m_graph.at(5).push_back(&nodes.at(74));
	m_graph.at(5).push_back(&nodes.at(75));
	m_graph.at(6).push_back(&nodes.at(6));
	m_graph.at(6).push_back(&nodes.at(19));
	m_graph.at(6).push_back(&nodes.at(20));
	m_graph.at(6).push_back(&nodes.at(21));
	m_graph.at(6).push_back(&nodes.at(22));
	m_graph.at(6).push_back(&nodes.at(25));
	m_graph.at(6).push_back(&nodes.at(35));
	m_graph.at(6).push_back(&nodes.at(37));
	m_graph.at(6).push_back(&nodes.at(41));
	m_graph.at(7).push_back(&nodes.at(7));
	m_graph.at(7).push_back(&nodes.at(16));
	m_graph.at(7).push_back(&nodes.at(17));
	m_graph.at(7).push_back(&nodes.at(18));
	m_graph.at(7).push_back(&nodes.at(20));
	m_graph.at(7).push_back(&nodes.at(25));
	m_graph.at(7).push_back(&nodes.at(26));
	m_graph.at(7).push_back(&nodes.at(27));
	m_graph.at(7).push_back(&nodes.at(29));
	m_graph.at(7).push_back(&nodes.at(32));
	m_graph.at(7).push_back(&nodes.at(34));
	m_graph.at(7).push_back(&nodes.at(35));
	m_graph.at(8).push_back(&nodes.at(8));
	m_graph.at(8).push_back(&nodes.at(0));
	m_graph.at(8).push_back(&nodes.at(9));
	m_graph.at(8).push_back(&nodes.at(10));
	m_graph.at(8).push_back(&nodes.at(11));
	m_graph.at(8).push_back(&nodes.at(39));
	m_graph.at(8).push_back(&nodes.at(40));
	m_graph.at(8).push_back(&nodes.at(42));
	m_graph.at(9).push_back(&nodes.at(9));
	m_graph.at(9).push_back(&nodes.at(1));
	m_graph.at(9).push_back(&nodes.at(8));
	m_graph.at(9).push_back(&nodes.at(10));
	m_graph.at(9).push_back(&nodes.at(40));
	m_graph.at(9).push_back(&nodes.at(42));
	m_graph.at(9).push_back(&nodes.at(43));
	m_graph.at(9).push_back(&nodes.at(46));
	m_graph.at(10).push_back(&nodes.at(10));
	m_graph.at(10).push_back(&nodes.at(0));
	m_graph.at(10).push_back(&nodes.at(1));
	m_graph.at(10).push_back(&nodes.at(8));
	m_graph.at(10).push_back(&nodes.at(9));
	m_graph.at(10).push_back(&nodes.at(11));
	m_graph.at(10).push_back(&nodes.at(32));
	m_graph.at(10).push_back(&nodes.at(33));
	m_graph.at(10).push_back(&nodes.at(39));
	m_graph.at(10).push_back(&nodes.at(40));
	m_graph.at(10).push_back(&nodes.at(42));
	m_graph.at(10).push_back(&nodes.at(43));
	m_graph.at(10).push_back(&nodes.at(46));
	m_graph.at(10).push_back(&nodes.at(69));
	m_graph.at(10).push_back(&nodes.at(75));
	m_graph.at(11).push_back(&nodes.at(11));
	m_graph.at(11).push_back(&nodes.at(0));
	m_graph.at(11).push_back(&nodes.at(8));
	m_graph.at(11).push_back(&nodes.at(10));
	m_graph.at(11).push_back(&nodes.at(12));
	m_graph.at(11).push_back(&nodes.at(13));
	m_graph.at(11).push_back(&nodes.at(20));
	m_graph.at(11).push_back(&nodes.at(35));
	m_graph.at(11).push_back(&nodes.at(36));
	m_graph.at(11).push_back(&nodes.at(38));
	m_graph.at(11).push_back(&nodes.at(39));
	m_graph.at(11).push_back(&nodes.at(40));
	m_graph.at(11).push_back(&nodes.at(42));
	m_graph.at(11).push_back(&nodes.at(45));
	m_graph.at(11).push_back(&nodes.at(61));
	m_graph.at(11).push_back(&nodes.at(62));
	m_graph.at(11).push_back(&nodes.at(63));
	m_graph.at(11).push_back(&nodes.at(66));
	m_graph.at(12).push_back(&nodes.at(12));
	m_graph.at(12).push_back(&nodes.at(0));
	m_graph.at(12).push_back(&nodes.at(11));
	m_graph.at(12).push_back(&nodes.at(13));
	m_graph.at(12).push_back(&nodes.at(14));
	m_graph.at(12).push_back(&nodes.at(15));
	m_graph.at(12).push_back(&nodes.at(17));
	m_graph.at(12).push_back(&nodes.at(32));
	m_graph.at(12).push_back(&nodes.at(36));
	m_graph.at(12).push_back(&nodes.at(37));
	m_graph.at(13).push_back(&nodes.at(13));
	m_graph.at(13).push_back(&nodes.at(4));
	m_graph.at(13).push_back(&nodes.at(11));
	m_graph.at(13).push_back(&nodes.at(12));
	m_graph.at(13).push_back(&nodes.at(14));
	m_graph.at(13).push_back(&nodes.at(15));
	m_graph.at(13).push_back(&nodes.at(16));
	m_graph.at(13).push_back(&nodes.at(20));
	m_graph.at(13).push_back(&nodes.at(21));
	m_graph.at(13).push_back(&nodes.at(27));
	m_graph.at(13).push_back(&nodes.at(32));
	m_graph.at(13).push_back(&nodes.at(33));
	m_graph.at(13).push_back(&nodes.at(35));
	m_graph.at(13).push_back(&nodes.at(36));
	m_graph.at(13).push_back(&nodes.at(37));
	m_graph.at(13).push_back(&nodes.at(38));
	m_graph.at(13).push_back(&nodes.at(39));
	m_graph.at(13).push_back(&nodes.at(41));
	m_graph.at(14).push_back(&nodes.at(14));
	m_graph.at(14).push_back(&nodes.at(4));
	m_graph.at(14).push_back(&nodes.at(12));
	m_graph.at(14).push_back(&nodes.at(13));
	m_graph.at(14).push_back(&nodes.at(15));
	m_graph.at(14).push_back(&nodes.at(17));
	m_graph.at(14).push_back(&nodes.at(32));
	m_graph.at(14).push_back(&nodes.at(33));
	m_graph.at(14).push_back(&nodes.at(36));
	m_graph.at(14).push_back(&nodes.at(37));
	m_graph.at(14).push_back(&nodes.at(38));
	m_graph.at(14).push_back(&nodes.at(41));
	m_graph.at(14).push_back(&nodes.at(68));
	m_graph.at(14).push_back(&nodes.at(69));
	m_graph.at(14).push_back(&nodes.at(70));
	m_graph.at(15).push_back(&nodes.at(15));
	m_graph.at(15).push_back(&nodes.at(4));
	m_graph.at(15).push_back(&nodes.at(12));
	m_graph.at(15).push_back(&nodes.at(13));
	m_graph.at(15).push_back(&nodes.at(14));
	m_graph.at(15).push_back(&nodes.at(16));
	m_graph.at(15).push_back(&nodes.at(20));
	m_graph.at(15).push_back(&nodes.at(21));
	m_graph.at(15).push_back(&nodes.at(32));
	m_graph.at(15).push_back(&nodes.at(33));
	m_graph.at(15).push_back(&nodes.at(35));
	m_graph.at(15).push_back(&nodes.at(36));
	m_graph.at(15).push_back(&nodes.at(37));
	m_graph.at(15).push_back(&nodes.at(38));
	m_graph.at(15).push_back(&nodes.at(39));
	m_graph.at(15).push_back(&nodes.at(41));
	m_graph.at(15).push_back(&nodes.at(68));
	m_graph.at(15).push_back(&nodes.at(69));
	m_graph.at(15).push_back(&nodes.at(70));
	m_graph.at(16).push_back(&nodes.at(16));
	m_graph.at(16).push_back(&nodes.at(7));
	m_graph.at(16).push_back(&nodes.at(13));
	m_graph.at(16).push_back(&nodes.at(15));
	m_graph.at(16).push_back(&nodes.at(17));
	m_graph.at(16).push_back(&nodes.at(18));
	m_graph.at(16).push_back(&nodes.at(20));
	m_graph.at(16).push_back(&nodes.at(21));
	m_graph.at(16).push_back(&nodes.at(24));
	m_graph.at(16).push_back(&nodes.at(25));
	m_graph.at(16).push_back(&nodes.at(27));
	m_graph.at(16).push_back(&nodes.at(35));
	m_graph.at(16).push_back(&nodes.at(36));
	m_graph.at(16).push_back(&nodes.at(38));
	m_graph.at(16).push_back(&nodes.at(39));
	m_graph.at(17).push_back(&nodes.at(17));
	m_graph.at(17).push_back(&nodes.at(7));
	m_graph.at(17).push_back(&nodes.at(12));
	m_graph.at(17).push_back(&nodes.at(14));
	m_graph.at(17).push_back(&nodes.at(16));
	m_graph.at(17).push_back(&nodes.at(20));
	m_graph.at(17).push_back(&nodes.at(21));
	m_graph.at(17).push_back(&nodes.at(24));
	m_graph.at(18).push_back(&nodes.at(18));
	m_graph.at(18).push_back(&nodes.at(7));
	m_graph.at(18).push_back(&nodes.at(16));
	m_graph.at(18).push_back(&nodes.at(19));
	m_graph.at(18).push_back(&nodes.at(20));
	m_graph.at(18).push_back(&nodes.at(25));
	m_graph.at(18).push_back(&nodes.at(27));
	m_graph.at(18).push_back(&nodes.at(32));
	m_graph.at(18).push_back(&nodes.at(35));
	m_graph.at(18).push_back(&nodes.at(64));
	m_graph.at(18).push_back(&nodes.at(65));
	m_graph.at(18).push_back(&nodes.at(66));
	m_graph.at(19).push_back(&nodes.at(19));
	m_graph.at(19).push_back(&nodes.at(6));
	m_graph.at(19).push_back(&nodes.at(18));
	m_graph.at(19).push_back(&nodes.at(20));
	m_graph.at(19).push_back(&nodes.at(21));
	m_graph.at(19).push_back(&nodes.at(25));
	m_graph.at(19).push_back(&nodes.at(37));
	m_graph.at(19).push_back(&nodes.at(41));
	m_graph.at(19).push_back(&nodes.at(45));
	m_graph.at(19).push_back(&nodes.at(54));
	m_graph.at(19).push_back(&nodes.at(55));
	m_graph.at(19).push_back(&nodes.at(56));
	m_graph.at(20).push_back(&nodes.at(20));
	m_graph.at(20).push_back(&nodes.at(6));
	m_graph.at(20).push_back(&nodes.at(7));
	m_graph.at(20).push_back(&nodes.at(11));
	m_graph.at(20).push_back(&nodes.at(13));
	m_graph.at(20).push_back(&nodes.at(15));
	m_graph.at(20).push_back(&nodes.at(16));
	m_graph.at(20).push_back(&nodes.at(17));
	m_graph.at(20).push_back(&nodes.at(18));
	m_graph.at(20).push_back(&nodes.at(19));
	m_graph.at(20).push_back(&nodes.at(21));
	m_graph.at(20).push_back(&nodes.at(22));
	m_graph.at(20).push_back(&nodes.at(24));
	m_graph.at(20).push_back(&nodes.at(25));
	m_graph.at(20).push_back(&nodes.at(26));
	m_graph.at(20).push_back(&nodes.at(27));
	m_graph.at(20).push_back(&nodes.at(29));
	m_graph.at(20).push_back(&nodes.at(31));
	m_graph.at(20).push_back(&nodes.at(32));
	m_graph.at(20).push_back(&nodes.at(34));
	m_graph.at(20).push_back(&nodes.at(35));
	m_graph.at(20).push_back(&nodes.at(36));
	m_graph.at(20).push_back(&nodes.at(37));
	m_graph.at(20).push_back(&nodes.at(39));
	m_graph.at(20).push_back(&nodes.at(41));
	m_graph.at(20).push_back(&nodes.at(45));
	m_graph.at(20).push_back(&nodes.at(54));
	m_graph.at(20).push_back(&nodes.at(55));
	m_graph.at(20).push_back(&nodes.at(57));
	m_graph.at(20).push_back(&nodes.at(64));
	m_graph.at(20).push_back(&nodes.at(65));
	m_graph.at(20).push_back(&nodes.at(66));
	m_graph.at(21).push_back(&nodes.at(21));
	m_graph.at(21).push_back(&nodes.at(6));
	m_graph.at(21).push_back(&nodes.at(13));
	m_graph.at(21).push_back(&nodes.at(15));
	m_graph.at(21).push_back(&nodes.at(16));
	m_graph.at(21).push_back(&nodes.at(17));
	m_graph.at(21).push_back(&nodes.at(19));
	m_graph.at(21).push_back(&nodes.at(20));
	m_graph.at(21).push_back(&nodes.at(22));
	m_graph.at(21).push_back(&nodes.at(24));
	m_graph.at(21).push_back(&nodes.at(25));
	m_graph.at(21).push_back(&nodes.at(26));
	m_graph.at(21).push_back(&nodes.at(29));
	m_graph.at(21).push_back(&nodes.at(31));
	m_graph.at(21).push_back(&nodes.at(34));
	m_graph.at(21).push_back(&nodes.at(35));
	m_graph.at(21).push_back(&nodes.at(37));
	m_graph.at(22).push_back(&nodes.at(22));
	m_graph.at(22).push_back(&nodes.at(6));
	m_graph.at(22).push_back(&nodes.at(20));
	m_graph.at(22).push_back(&nodes.at(21));
	m_graph.at(22).push_back(&nodes.at(23));
	m_graph.at(22).push_back(&nodes.at(28));
	m_graph.at(23).push_back(&nodes.at(23));
	m_graph.at(23).push_back(&nodes.at(1));
	m_graph.at(23).push_back(&nodes.at(22));
	m_graph.at(23).push_back(&nodes.at(24));
	m_graph.at(23).push_back(&nodes.at(26));
	m_graph.at(23).push_back(&nodes.at(27));
	m_graph.at(23).push_back(&nodes.at(28));
	m_graph.at(23).push_back(&nodes.at(29));
	m_graph.at(23).push_back(&nodes.at(31));
	m_graph.at(23).push_back(&nodes.at(32));
	m_graph.at(23).push_back(&nodes.at(40));
	m_graph.at(23).push_back(&nodes.at(41));
	m_graph.at(23).push_back(&nodes.at(42));
	m_graph.at(23).push_back(&nodes.at(43));
	m_graph.at(23).push_back(&nodes.at(46));
	m_graph.at(24).push_back(&nodes.at(24));
	m_graph.at(24).push_back(&nodes.at(1));
	m_graph.at(24).push_back(&nodes.at(16));
	m_graph.at(24).push_back(&nodes.at(17));
	m_graph.at(24).push_back(&nodes.at(20));
	m_graph.at(24).push_back(&nodes.at(21));
	m_graph.at(24).push_back(&nodes.at(23));
	m_graph.at(24).push_back(&nodes.at(25));
	m_graph.at(24).push_back(&nodes.at(26));
	m_graph.at(24).push_back(&nodes.at(27));
	m_graph.at(24).push_back(&nodes.at(28));
	m_graph.at(24).push_back(&nodes.at(29));
	m_graph.at(24).push_back(&nodes.at(31));
	m_graph.at(24).push_back(&nodes.at(32));
	m_graph.at(24).push_back(&nodes.at(34));
	m_graph.at(24).push_back(&nodes.at(40));
	m_graph.at(24).push_back(&nodes.at(41));
	m_graph.at(24).push_back(&nodes.at(42));
	m_graph.at(24).push_back(&nodes.at(43));
	m_graph.at(24).push_back(&nodes.at(46));
	m_graph.at(25).push_back(&nodes.at(25));
	m_graph.at(25).push_back(&nodes.at(6));
	m_graph.at(25).push_back(&nodes.at(7));
	m_graph.at(25).push_back(&nodes.at(16));
	m_graph.at(25).push_back(&nodes.at(18));
	m_graph.at(25).push_back(&nodes.at(19));
	m_graph.at(25).push_back(&nodes.at(20));
	m_graph.at(25).push_back(&nodes.at(21));
	m_graph.at(25).push_back(&nodes.at(24));
	m_graph.at(25).push_back(&nodes.at(26));
	m_graph.at(25).push_back(&nodes.at(27));
	m_graph.at(25).push_back(&nodes.at(29));
	m_graph.at(25).push_back(&nodes.at(30));
	m_graph.at(25).push_back(&nodes.at(32));
	m_graph.at(25).push_back(&nodes.at(35));
	m_graph.at(25).push_back(&nodes.at(37));
	m_graph.at(25).push_back(&nodes.at(41));
	m_graph.at(25).push_back(&nodes.at(45));
	m_graph.at(25).push_back(&nodes.at(54));
	m_graph.at(25).push_back(&nodes.at(55));
	m_graph.at(25).push_back(&nodes.at(56));
	m_graph.at(25).push_back(&nodes.at(57));
	m_graph.at(25).push_back(&nodes.at(64));
	m_graph.at(25).push_back(&nodes.at(66));
	m_graph.at(26).push_back(&nodes.at(26));
	m_graph.at(26).push_back(&nodes.at(7));
	m_graph.at(26).push_back(&nodes.at(20));
	m_graph.at(26).push_back(&nodes.at(21));
	m_graph.at(26).push_back(&nodes.at(23));
	m_graph.at(26).push_back(&nodes.at(24));
	m_graph.at(26).push_back(&nodes.at(25));
	m_graph.at(26).push_back(&nodes.at(27));
	m_graph.at(26).push_back(&nodes.at(28));
	m_graph.at(26).push_back(&nodes.at(29));
	m_graph.at(26).push_back(&nodes.at(30));
	m_graph.at(26).push_back(&nodes.at(31));
	m_graph.at(26).push_back(&nodes.at(32));
	m_graph.at(26).push_back(&nodes.at(34));
	m_graph.at(26).push_back(&nodes.at(41));
	m_graph.at(26).push_back(&nodes.at(42));
	m_graph.at(26).push_back(&nodes.at(43));
	m_graph.at(26).push_back(&nodes.at(46));
	m_graph.at(27).push_back(&nodes.at(27));
	m_graph.at(27).push_back(&nodes.at(7));
	m_graph.at(27).push_back(&nodes.at(13));
	m_graph.at(27).push_back(&nodes.at(16));
	m_graph.at(27).push_back(&nodes.at(18));
	m_graph.at(27).push_back(&nodes.at(20));
	m_graph.at(27).push_back(&nodes.at(23));
	m_graph.at(27).push_back(&nodes.at(24));
	m_graph.at(27).push_back(&nodes.at(25));
	m_graph.at(27).push_back(&nodes.at(26));
	m_graph.at(27).push_back(&nodes.at(28));
	m_graph.at(27).push_back(&nodes.at(29));
	m_graph.at(27).push_back(&nodes.at(31));
	m_graph.at(27).push_back(&nodes.at(32));
	m_graph.at(27).push_back(&nodes.at(35));
	m_graph.at(27).push_back(&nodes.at(37));
	m_graph.at(27).push_back(&nodes.at(38));
	m_graph.at(27).push_back(&nodes.at(41));
	m_graph.at(27).push_back(&nodes.at(42));
	m_graph.at(27).push_back(&nodes.at(45));
	m_graph.at(27).push_back(&nodes.at(54));
	m_graph.at(27).push_back(&nodes.at(55));
	m_graph.at(27).push_back(&nodes.at(56));
	m_graph.at(27).push_back(&nodes.at(57));
	m_graph.at(27).push_back(&nodes.at(64));
	m_graph.at(27).push_back(&nodes.at(65));
	m_graph.at(27).push_back(&nodes.at(66));
	m_graph.at(28).push_back(&nodes.at(28));
	m_graph.at(28).push_back(&nodes.at(5));
	m_graph.at(28).push_back(&nodes.at(22));
	m_graph.at(28).push_back(&nodes.at(23));
	m_graph.at(28).push_back(&nodes.at(24));
	m_graph.at(28).push_back(&nodes.at(26));
	m_graph.at(28).push_back(&nodes.at(27));
	m_graph.at(28).push_back(&nodes.at(29));
	m_graph.at(28).push_back(&nodes.at(30));
	m_graph.at(28).push_back(&nodes.at(41));
	m_graph.at(29).push_back(&nodes.at(29));
	m_graph.at(29).push_back(&nodes.at(1));
	m_graph.at(29).push_back(&nodes.at(7));
	m_graph.at(29).push_back(&nodes.at(20));
	m_graph.at(29).push_back(&nodes.at(21));
	m_graph.at(29).push_back(&nodes.at(23));
	m_graph.at(29).push_back(&nodes.at(24));
	m_graph.at(29).push_back(&nodes.at(25));
	m_graph.at(29).push_back(&nodes.at(26));
	m_graph.at(29).push_back(&nodes.at(27));
	m_graph.at(29).push_back(&nodes.at(28));
	m_graph.at(29).push_back(&nodes.at(30));
	m_graph.at(29).push_back(&nodes.at(31));
	m_graph.at(29).push_back(&nodes.at(32));
	m_graph.at(29).push_back(&nodes.at(34));
	m_graph.at(29).push_back(&nodes.at(40));
	m_graph.at(29).push_back(&nodes.at(41));
	m_graph.at(30).push_back(&nodes.at(30));
	m_graph.at(30).push_back(&nodes.at(5));
	m_graph.at(30).push_back(&nodes.at(25));
	m_graph.at(30).push_back(&nodes.at(26));
	m_graph.at(30).push_back(&nodes.at(28));
	m_graph.at(30).push_back(&nodes.at(29));
	m_graph.at(30).push_back(&nodes.at(31));
	m_graph.at(30).push_back(&nodes.at(33));
	m_graph.at(30).push_back(&nodes.at(34));
	m_graph.at(30).push_back(&nodes.at(45));
	m_graph.at(30).push_back(&nodes.at(49));
	m_graph.at(30).push_back(&nodes.at(50));
	m_graph.at(30).push_back(&nodes.at(53));
	m_graph.at(30).push_back(&nodes.at(66));
	m_graph.at(30).push_back(&nodes.at(69));
	m_graph.at(30).push_back(&nodes.at(74));
	m_graph.at(30).push_back(&nodes.at(75));
	m_graph.at(31).push_back(&nodes.at(31));
	m_graph.at(31).push_back(&nodes.at(1));
	m_graph.at(31).push_back(&nodes.at(20));
	m_graph.at(31).push_back(&nodes.at(21));
	m_graph.at(31).push_back(&nodes.at(23));
	m_graph.at(31).push_back(&nodes.at(24));
	m_graph.at(31).push_back(&nodes.at(26));
	m_graph.at(31).push_back(&nodes.at(27));
	m_graph.at(31).push_back(&nodes.at(29));
	m_graph.at(31).push_back(&nodes.at(30));
	m_graph.at(31).push_back(&nodes.at(32));
	m_graph.at(31).push_back(&nodes.at(34));
	m_graph.at(31).push_back(&nodes.at(38));
	m_graph.at(31).push_back(&nodes.at(40));
	m_graph.at(31).push_back(&nodes.at(41));
	m_graph.at(31).push_back(&nodes.at(74));
	m_graph.at(32).push_back(&nodes.at(32));
	m_graph.at(32).push_back(&nodes.at(1));
	m_graph.at(32).push_back(&nodes.at(4));
	m_graph.at(32).push_back(&nodes.at(7));
	m_graph.at(32).push_back(&nodes.at(10));
	m_graph.at(32).push_back(&nodes.at(12));
	m_graph.at(32).push_back(&nodes.at(13));
	m_graph.at(32).push_back(&nodes.at(14));
	m_graph.at(32).push_back(&nodes.at(15));
	m_graph.at(32).push_back(&nodes.at(18));
	m_graph.at(32).push_back(&nodes.at(20));
	m_graph.at(32).push_back(&nodes.at(23));
	m_graph.at(32).push_back(&nodes.at(24));
	m_graph.at(32).push_back(&nodes.at(25));
	m_graph.at(32).push_back(&nodes.at(26));
	m_graph.at(32).push_back(&nodes.at(27));
	m_graph.at(32).push_back(&nodes.at(29));
	m_graph.at(32).push_back(&nodes.at(31));
	m_graph.at(32).push_back(&nodes.at(33));
	m_graph.at(32).push_back(&nodes.at(35));
	m_graph.at(32).push_back(&nodes.at(36));
	m_graph.at(32).push_back(&nodes.at(37));
	m_graph.at(32).push_back(&nodes.at(38));
	m_graph.at(32).push_back(&nodes.at(40));
	m_graph.at(32).push_back(&nodes.at(41));
	m_graph.at(32).push_back(&nodes.at(42));
	m_graph.at(32).push_back(&nodes.at(43));
	m_graph.at(32).push_back(&nodes.at(45));
	m_graph.at(32).push_back(&nodes.at(46));
	m_graph.at(32).push_back(&nodes.at(54));
	m_graph.at(32).push_back(&nodes.at(55));
	m_graph.at(32).push_back(&nodes.at(56));
	m_graph.at(32).push_back(&nodes.at(57));
	m_graph.at(32).push_back(&nodes.at(64));
	m_graph.at(32).push_back(&nodes.at(65));
	m_graph.at(32).push_back(&nodes.at(66));
	m_graph.at(32).push_back(&nodes.at(68));
	m_graph.at(32).push_back(&nodes.at(69));
	m_graph.at(32).push_back(&nodes.at(70));
	m_graph.at(33).push_back(&nodes.at(33));
	m_graph.at(33).push_back(&nodes.at(4));
	m_graph.at(33).push_back(&nodes.at(5));
	m_graph.at(33).push_back(&nodes.at(10));
	m_graph.at(33).push_back(&nodes.at(13));
	m_graph.at(33).push_back(&nodes.at(14));
	m_graph.at(33).push_back(&nodes.at(15));
	m_graph.at(33).push_back(&nodes.at(30));
	m_graph.at(33).push_back(&nodes.at(32));
	m_graph.at(33).push_back(&nodes.at(34));
	m_graph.at(33).push_back(&nodes.at(38));
	m_graph.at(33).push_back(&nodes.at(40));
	m_graph.at(33).push_back(&nodes.at(41));
	m_graph.at(33).push_back(&nodes.at(42));
	m_graph.at(33).push_back(&nodes.at(45));
	m_graph.at(33).push_back(&nodes.at(49));
	m_graph.at(33).push_back(&nodes.at(50));
	m_graph.at(33).push_back(&nodes.at(53));
	m_graph.at(33).push_back(&nodes.at(54));
	m_graph.at(33).push_back(&nodes.at(66));
	m_graph.at(33).push_back(&nodes.at(68));
	m_graph.at(33).push_back(&nodes.at(69));
	m_graph.at(33).push_back(&nodes.at(70));
	m_graph.at(33).push_back(&nodes.at(73));
	m_graph.at(33).push_back(&nodes.at(74));
	m_graph.at(33).push_back(&nodes.at(75));
	m_graph.at(34).push_back(&nodes.at(34));
	m_graph.at(34).push_back(&nodes.at(5));
	m_graph.at(34).push_back(&nodes.at(7));
	m_graph.at(34).push_back(&nodes.at(20));
	m_graph.at(34).push_back(&nodes.at(21));
	m_graph.at(34).push_back(&nodes.at(24));
	m_graph.at(34).push_back(&nodes.at(26));
	m_graph.at(34).push_back(&nodes.at(29));
	m_graph.at(34).push_back(&nodes.at(30));
	m_graph.at(34).push_back(&nodes.at(31));
	m_graph.at(34).push_back(&nodes.at(33));
	m_graph.at(34).push_back(&nodes.at(45));
	m_graph.at(34).push_back(&nodes.at(49));
	m_graph.at(34).push_back(&nodes.at(50));
	m_graph.at(34).push_back(&nodes.at(53));
	m_graph.at(34).push_back(&nodes.at(66));
	m_graph.at(34).push_back(&nodes.at(69));
	m_graph.at(34).push_back(&nodes.at(74));
	m_graph.at(34).push_back(&nodes.at(75));
	m_graph.at(35).push_back(&nodes.at(35));
	m_graph.at(35).push_back(&nodes.at(6));
	m_graph.at(35).push_back(&nodes.at(7));
	m_graph.at(35).push_back(&nodes.at(11));
	m_graph.at(35).push_back(&nodes.at(13));
	m_graph.at(35).push_back(&nodes.at(15));
	m_graph.at(35).push_back(&nodes.at(16));
	m_graph.at(35).push_back(&nodes.at(18));
	m_graph.at(35).push_back(&nodes.at(20));
	m_graph.at(35).push_back(&nodes.at(21));
	m_graph.at(35).push_back(&nodes.at(25));
	m_graph.at(35).push_back(&nodes.at(27));
	m_graph.at(35).push_back(&nodes.at(32));
	m_graph.at(35).push_back(&nodes.at(36));
	m_graph.at(35).push_back(&nodes.at(37));
	m_graph.at(35).push_back(&nodes.at(41));
	m_graph.at(35).push_back(&nodes.at(45));
	m_graph.at(35).push_back(&nodes.at(54));
	m_graph.at(35).push_back(&nodes.at(55));
	m_graph.at(35).push_back(&nodes.at(57));
	m_graph.at(35).push_back(&nodes.at(64));
	m_graph.at(35).push_back(&nodes.at(65));
	m_graph.at(35).push_back(&nodes.at(66));
	m_graph.at(36).push_back(&nodes.at(36));
	m_graph.at(36).push_back(&nodes.at(11));
	m_graph.at(36).push_back(&nodes.at(12));
	m_graph.at(36).push_back(&nodes.at(13));
	m_graph.at(36).push_back(&nodes.at(14));
	m_graph.at(36).push_back(&nodes.at(15));
	m_graph.at(36).push_back(&nodes.at(16));
	m_graph.at(36).push_back(&nodes.at(20));
	m_graph.at(36).push_back(&nodes.at(32));
	m_graph.at(36).push_back(&nodes.at(35));
	m_graph.at(36).push_back(&nodes.at(37));
	m_graph.at(36).push_back(&nodes.at(38));
	m_graph.at(36).push_back(&nodes.at(39));
	m_graph.at(36).push_back(&nodes.at(41));
	m_graph.at(36).push_back(&nodes.at(68));
	m_graph.at(36).push_back(&nodes.at(69));
	m_graph.at(36).push_back(&nodes.at(70));
	m_graph.at(37).push_back(&nodes.at(37));
	m_graph.at(37).push_back(&nodes.at(6));
	m_graph.at(37).push_back(&nodes.at(12));
	m_graph.at(37).push_back(&nodes.at(13));
	m_graph.at(37).push_back(&nodes.at(14));
	m_graph.at(37).push_back(&nodes.at(15));
	m_graph.at(37).push_back(&nodes.at(19));
	m_graph.at(37).push_back(&nodes.at(20));
	m_graph.at(37).push_back(&nodes.at(21));
	m_graph.at(37).push_back(&nodes.at(25));
	m_graph.at(37).push_back(&nodes.at(27));
	m_graph.at(37).push_back(&nodes.at(32));
	m_graph.at(37).push_back(&nodes.at(35));
	m_graph.at(37).push_back(&nodes.at(36));
	m_graph.at(37).push_back(&nodes.at(38));
	m_graph.at(37).push_back(&nodes.at(41));
	m_graph.at(37).push_back(&nodes.at(45));
	m_graph.at(37).push_back(&nodes.at(54));
	m_graph.at(37).push_back(&nodes.at(55));
	m_graph.at(37).push_back(&nodes.at(57));
	m_graph.at(37).push_back(&nodes.at(64));
	m_graph.at(37).push_back(&nodes.at(65));
	m_graph.at(37).push_back(&nodes.at(66));
	m_graph.at(38).push_back(&nodes.at(38));
	m_graph.at(38).push_back(&nodes.at(11));
	m_graph.at(38).push_back(&nodes.at(13));
	m_graph.at(38).push_back(&nodes.at(14));
	m_graph.at(38).push_back(&nodes.at(15));
	m_graph.at(38).push_back(&nodes.at(16));
	m_graph.at(38).push_back(&nodes.at(27));
	m_graph.at(38).push_back(&nodes.at(31));
	m_graph.at(38).push_back(&nodes.at(32));
	m_graph.at(38).push_back(&nodes.at(33));
	m_graph.at(38).push_back(&nodes.at(36));
	m_graph.at(38).push_back(&nodes.at(37));
	m_graph.at(38).push_back(&nodes.at(39));
	m_graph.at(38).push_back(&nodes.at(41));
	m_graph.at(39).push_back(&nodes.at(39));
	m_graph.at(39).push_back(&nodes.at(0));
	m_graph.at(39).push_back(&nodes.at(8));
	m_graph.at(39).push_back(&nodes.at(10));
	m_graph.at(39).push_back(&nodes.at(11));
	m_graph.at(39).push_back(&nodes.at(13));
	m_graph.at(39).push_back(&nodes.at(15));
	m_graph.at(39).push_back(&nodes.at(16));
	m_graph.at(39).push_back(&nodes.at(20));
	m_graph.at(39).push_back(&nodes.at(36));
	m_graph.at(39).push_back(&nodes.at(38));
	m_graph.at(39).push_back(&nodes.at(40));
	m_graph.at(39).push_back(&nodes.at(42));
	m_graph.at(39).push_back(&nodes.at(45));
	m_graph.at(39).push_back(&nodes.at(61));
	m_graph.at(39).push_back(&nodes.at(62));
	m_graph.at(39).push_back(&nodes.at(63));
	m_graph.at(39).push_back(&nodes.at(66));
	m_graph.at(40).push_back(&nodes.at(40));
	m_graph.at(40).push_back(&nodes.at(0));
	m_graph.at(40).push_back(&nodes.at(1));
	m_graph.at(40).push_back(&nodes.at(8));
	m_graph.at(40).push_back(&nodes.at(9));
	m_graph.at(40).push_back(&nodes.at(10));
	m_graph.at(40).push_back(&nodes.at(11));
	m_graph.at(40).push_back(&nodes.at(23));
	m_graph.at(40).push_back(&nodes.at(24));
	m_graph.at(40).push_back(&nodes.at(29));
	m_graph.at(40).push_back(&nodes.at(31));
	m_graph.at(40).push_back(&nodes.at(32));
	m_graph.at(40).push_back(&nodes.at(33));
	m_graph.at(40).push_back(&nodes.at(39));
	m_graph.at(40).push_back(&nodes.at(41));
	m_graph.at(40).push_back(&nodes.at(42));
	m_graph.at(40).push_back(&nodes.at(43));
	m_graph.at(40).push_back(&nodes.at(45));
	m_graph.at(40).push_back(&nodes.at(46));
	m_graph.at(40).push_back(&nodes.at(61));
	m_graph.at(40).push_back(&nodes.at(62));
	m_graph.at(40).push_back(&nodes.at(63));
	m_graph.at(40).push_back(&nodes.at(64));
	m_graph.at(40).push_back(&nodes.at(66));
	m_graph.at(40).push_back(&nodes.at(69));
	m_graph.at(40).push_back(&nodes.at(75));
	m_graph.at(41).push_back(&nodes.at(41));
	m_graph.at(41).push_back(&nodes.at(1));
	m_graph.at(41).push_back(&nodes.at(4));
	m_graph.at(41).push_back(&nodes.at(6));
	m_graph.at(41).push_back(&nodes.at(13));
	m_graph.at(41).push_back(&nodes.at(14));
	m_graph.at(41).push_back(&nodes.at(15));
	m_graph.at(41).push_back(&nodes.at(19));
	m_graph.at(41).push_back(&nodes.at(20));
	m_graph.at(41).push_back(&nodes.at(23));
	m_graph.at(41).push_back(&nodes.at(24));
	m_graph.at(41).push_back(&nodes.at(25));
	m_graph.at(41).push_back(&nodes.at(26));
	m_graph.at(41).push_back(&nodes.at(27));
	m_graph.at(41).push_back(&nodes.at(28));
	m_graph.at(41).push_back(&nodes.at(29));
	m_graph.at(41).push_back(&nodes.at(31));
	m_graph.at(41).push_back(&nodes.at(32));
	m_graph.at(41).push_back(&nodes.at(33));
	m_graph.at(41).push_back(&nodes.at(35));
	m_graph.at(41).push_back(&nodes.at(36));
	m_graph.at(41).push_back(&nodes.at(37));
	m_graph.at(41).push_back(&nodes.at(38));
	m_graph.at(41).push_back(&nodes.at(40));
	m_graph.at(41).push_back(&nodes.at(42));
	m_graph.at(41).push_back(&nodes.at(43));
	m_graph.at(41).push_back(&nodes.at(45));
	m_graph.at(41).push_back(&nodes.at(46));
	m_graph.at(41).push_back(&nodes.at(54));
	m_graph.at(41).push_back(&nodes.at(57));
	m_graph.at(41).push_back(&nodes.at(58));
	m_graph.at(41).push_back(&nodes.at(64));
	m_graph.at(41).push_back(&nodes.at(65));
	m_graph.at(41).push_back(&nodes.at(66));
	m_graph.at(41).push_back(&nodes.at(68));
	m_graph.at(41).push_back(&nodes.at(69));
	m_graph.at(41).push_back(&nodes.at(70));
	m_graph.at(41).push_back(&nodes.at(75));
	m_graph.at(42).push_back(&nodes.at(42));
	m_graph.at(42).push_back(&nodes.at(0));
	m_graph.at(42).push_back(&nodes.at(1));
	m_graph.at(42).push_back(&nodes.at(8));
	m_graph.at(42).push_back(&nodes.at(9));
	m_graph.at(42).push_back(&nodes.at(10));
	m_graph.at(42).push_back(&nodes.at(11));
	m_graph.at(42).push_back(&nodes.at(23));
	m_graph.at(42).push_back(&nodes.at(24));
	m_graph.at(42).push_back(&nodes.at(26));
	m_graph.at(42).push_back(&nodes.at(27));
	m_graph.at(42).push_back(&nodes.at(32));
	m_graph.at(42).push_back(&nodes.at(33));
	m_graph.at(42).push_back(&nodes.at(39));
	m_graph.at(42).push_back(&nodes.at(40));
	m_graph.at(42).push_back(&nodes.at(41));
	m_graph.at(42).push_back(&nodes.at(43));
	m_graph.at(42).push_back(&nodes.at(45));
	m_graph.at(42).push_back(&nodes.at(46));
	m_graph.at(42).push_back(&nodes.at(61));
	m_graph.at(42).push_back(&nodes.at(62));
	m_graph.at(42).push_back(&nodes.at(63));
	m_graph.at(42).push_back(&nodes.at(66));
	m_graph.at(42).push_back(&nodes.at(67));
	m_graph.at(42).push_back(&nodes.at(69));
	m_graph.at(42).push_back(&nodes.at(72));
	m_graph.at(42).push_back(&nodes.at(75));
	m_graph.at(43).push_back(&nodes.at(43));
	m_graph.at(43).push_back(&nodes.at(1));
	m_graph.at(43).push_back(&nodes.at(3));
	m_graph.at(43).push_back(&nodes.at(9));
	m_graph.at(43).push_back(&nodes.at(10));
	m_graph.at(43).push_back(&nodes.at(23));
	m_graph.at(43).push_back(&nodes.at(24));
	m_graph.at(43).push_back(&nodes.at(26));
	m_graph.at(43).push_back(&nodes.at(32));
	m_graph.at(43).push_back(&nodes.at(40));
	m_graph.at(43).push_back(&nodes.at(41));
	m_graph.at(43).push_back(&nodes.at(42));
	m_graph.at(43).push_back(&nodes.at(44));
	m_graph.at(43).push_back(&nodes.at(46));
	m_graph.at(43).push_back(&nodes.at(48));
	m_graph.at(43).push_back(&nodes.at(50));
	m_graph.at(43).push_back(&nodes.at(51));
	m_graph.at(43).push_back(&nodes.at(53));
	m_graph.at(43).push_back(&nodes.at(57));
	m_graph.at(44).push_back(&nodes.at(44));
	m_graph.at(44).push_back(&nodes.at(3));
	m_graph.at(44).push_back(&nodes.at(5));
	m_graph.at(44).push_back(&nodes.at(43));
	m_graph.at(44).push_back(&nodes.at(45));
	m_graph.at(44).push_back(&nodes.at(46));
	m_graph.at(44).push_back(&nodes.at(48));
	m_graph.at(44).push_back(&nodes.at(49));
	m_graph.at(44).push_back(&nodes.at(50));
	m_graph.at(44).push_back(&nodes.at(51));
	m_graph.at(44).push_back(&nodes.at(53));
	m_graph.at(44).push_back(&nodes.at(54));
	m_graph.at(44).push_back(&nodes.at(57));
	m_graph.at(44).push_back(&nodes.at(66));
	m_graph.at(44).push_back(&nodes.at(69));
	m_graph.at(44).push_back(&nodes.at(75));
	m_graph.at(45).push_back(&nodes.at(45));
	m_graph.at(45).push_back(&nodes.at(0));
	m_graph.at(45).push_back(&nodes.at(3));
	m_graph.at(45).push_back(&nodes.at(5));
	m_graph.at(45).push_back(&nodes.at(11));
	m_graph.at(45).push_back(&nodes.at(19));
	m_graph.at(45).push_back(&nodes.at(20));
	m_graph.at(45).push_back(&nodes.at(25));
	m_graph.at(45).push_back(&nodes.at(27));
	m_graph.at(45).push_back(&nodes.at(30));
	m_graph.at(45).push_back(&nodes.at(32));
	m_graph.at(45).push_back(&nodes.at(33));
	m_graph.at(45).push_back(&nodes.at(34));
	m_graph.at(45).push_back(&nodes.at(35));
	m_graph.at(45).push_back(&nodes.at(37));
	m_graph.at(45).push_back(&nodes.at(39));
	m_graph.at(45).push_back(&nodes.at(40));
	m_graph.at(45).push_back(&nodes.at(41));
	m_graph.at(45).push_back(&nodes.at(42));
	m_graph.at(45).push_back(&nodes.at(44));
	m_graph.at(45).push_back(&nodes.at(48));
	m_graph.at(45).push_back(&nodes.at(49));
	m_graph.at(45).push_back(&nodes.at(50));
	m_graph.at(45).push_back(&nodes.at(53));
	m_graph.at(45).push_back(&nodes.at(54));
	m_graph.at(45).push_back(&nodes.at(55));
	m_graph.at(45).push_back(&nodes.at(57));
	m_graph.at(45).push_back(&nodes.at(58));
	m_graph.at(45).push_back(&nodes.at(61));
	m_graph.at(45).push_back(&nodes.at(62));
	m_graph.at(45).push_back(&nodes.at(63));
	m_graph.at(45).push_back(&nodes.at(64));
	m_graph.at(45).push_back(&nodes.at(65));
	m_graph.at(45).push_back(&nodes.at(66));
	m_graph.at(45).push_back(&nodes.at(67));
	m_graph.at(45).push_back(&nodes.at(69));
	m_graph.at(45).push_back(&nodes.at(71));
	m_graph.at(45).push_back(&nodes.at(72));
	m_graph.at(45).push_back(&nodes.at(75));
	m_graph.at(46).push_back(&nodes.at(46));
	m_graph.at(46).push_back(&nodes.at(1));
	m_graph.at(46).push_back(&nodes.at(9));
	m_graph.at(46).push_back(&nodes.at(10));
	m_graph.at(46).push_back(&nodes.at(23));
	m_graph.at(46).push_back(&nodes.at(24));
	m_graph.at(46).push_back(&nodes.at(26));
	m_graph.at(46).push_back(&nodes.at(32));
	m_graph.at(46).push_back(&nodes.at(40));
	m_graph.at(46).push_back(&nodes.at(41));
	m_graph.at(46).push_back(&nodes.at(42));
	m_graph.at(46).push_back(&nodes.at(43));
	m_graph.at(46).push_back(&nodes.at(44));
	m_graph.at(46).push_back(&nodes.at(47));
	m_graph.at(46).push_back(&nodes.at(48));
	m_graph.at(46).push_back(&nodes.at(53));
	m_graph.at(46).push_back(&nodes.at(55));
	m_graph.at(47).push_back(&nodes.at(47));
	m_graph.at(47).push_back(&nodes.at(1));
	m_graph.at(47).push_back(&nodes.at(46));
	m_graph.at(47).push_back(&nodes.at(48));
	m_graph.at(47).push_back(&nodes.at(49));
	m_graph.at(47).push_back(&nodes.at(50));
	m_graph.at(47).push_back(&nodes.at(52));
	m_graph.at(47).push_back(&nodes.at(53));
	m_graph.at(47).push_back(&nodes.at(54));
	m_graph.at(47).push_back(&nodes.at(66));
	m_graph.at(48).push_back(&nodes.at(48));
	m_graph.at(48).push_back(&nodes.at(3));
	m_graph.at(48).push_back(&nodes.at(5));
	m_graph.at(48).push_back(&nodes.at(43));
	m_graph.at(48).push_back(&nodes.at(44));
	m_graph.at(48).push_back(&nodes.at(45));
	m_graph.at(48).push_back(&nodes.at(46));
	m_graph.at(48).push_back(&nodes.at(47));
	m_graph.at(48).push_back(&nodes.at(49));
	m_graph.at(48).push_back(&nodes.at(50));
	m_graph.at(48).push_back(&nodes.at(51));
	m_graph.at(48).push_back(&nodes.at(53));
	m_graph.at(48).push_back(&nodes.at(54));
	m_graph.at(48).push_back(&nodes.at(55));
	m_graph.at(48).push_back(&nodes.at(57));
	m_graph.at(48).push_back(&nodes.at(66));
	m_graph.at(48).push_back(&nodes.at(69));
	m_graph.at(48).push_back(&nodes.at(75));
	m_graph.at(49).push_back(&nodes.at(49));
	m_graph.at(49).push_back(&nodes.at(5));
	m_graph.at(49).push_back(&nodes.at(30));
	m_graph.at(49).push_back(&nodes.at(33));
	m_graph.at(49).push_back(&nodes.at(34));
	m_graph.at(49).push_back(&nodes.at(44));
	m_graph.at(49).push_back(&nodes.at(45));
	m_graph.at(49).push_back(&nodes.at(47));
	m_graph.at(49).push_back(&nodes.at(48));
	m_graph.at(49).push_back(&nodes.at(50));
	m_graph.at(49).push_back(&nodes.at(52));
	m_graph.at(49).push_back(&nodes.at(53));
	m_graph.at(49).push_back(&nodes.at(54));
	m_graph.at(49).push_back(&nodes.at(66));
	m_graph.at(49).push_back(&nodes.at(69));
	m_graph.at(50).push_back(&nodes.at(50));
	m_graph.at(50).push_back(&nodes.at(5));
	m_graph.at(50).push_back(&nodes.at(30));
	m_graph.at(50).push_back(&nodes.at(33));
	m_graph.at(50).push_back(&nodes.at(34));
	m_graph.at(50).push_back(&nodes.at(43));
	m_graph.at(50).push_back(&nodes.at(44));
	m_graph.at(50).push_back(&nodes.at(45));
	m_graph.at(50).push_back(&nodes.at(47));
	m_graph.at(50).push_back(&nodes.at(48));
	m_graph.at(50).push_back(&nodes.at(49));
	m_graph.at(50).push_back(&nodes.at(51));
	m_graph.at(50).push_back(&nodes.at(53));
	m_graph.at(50).push_back(&nodes.at(54));
	m_graph.at(50).push_back(&nodes.at(55));
	m_graph.at(50).push_back(&nodes.at(57));
	m_graph.at(50).push_back(&nodes.at(59));
	m_graph.at(50).push_back(&nodes.at(60));
	m_graph.at(50).push_back(&nodes.at(66));
	m_graph.at(50).push_back(&nodes.at(69));
	m_graph.at(51).push_back(&nodes.at(51));
	m_graph.at(51).push_back(&nodes.at(2));
	m_graph.at(51).push_back(&nodes.at(43));
	m_graph.at(51).push_back(&nodes.at(44));
	m_graph.at(51).push_back(&nodes.at(48));
	m_graph.at(51).push_back(&nodes.at(50));
	m_graph.at(51).push_back(&nodes.at(52));
	m_graph.at(51).push_back(&nodes.at(53));
	m_graph.at(51).push_back(&nodes.at(55));
	m_graph.at(51).push_back(&nodes.at(56));
	m_graph.at(51).push_back(&nodes.at(57));
	m_graph.at(51).push_back(&nodes.at(59));
	m_graph.at(51).push_back(&nodes.at(60));
	m_graph.at(51).push_back(&nodes.at(62));
	m_graph.at(51).push_back(&nodes.at(64));
	m_graph.at(51).push_back(&nodes.at(65));
	m_graph.at(51).push_back(&nodes.at(72));
	m_graph.at(52).push_back(&nodes.at(52));
	m_graph.at(52).push_back(&nodes.at(2));
	m_graph.at(52).push_back(&nodes.at(47));
	m_graph.at(52).push_back(&nodes.at(49));
	m_graph.at(52).push_back(&nodes.at(51));
	m_graph.at(52).push_back(&nodes.at(57));
	m_graph.at(53).push_back(&nodes.at(53));
	m_graph.at(53).push_back(&nodes.at(3));
	m_graph.at(53).push_back(&nodes.at(30));
	m_graph.at(53).push_back(&nodes.at(33));
	m_graph.at(53).push_back(&nodes.at(34));
	m_graph.at(53).push_back(&nodes.at(43));
	m_graph.at(53).push_back(&nodes.at(44));
	m_graph.at(53).push_back(&nodes.at(45));
	m_graph.at(53).push_back(&nodes.at(46));
	m_graph.at(53).push_back(&nodes.at(47));
	m_graph.at(53).push_back(&nodes.at(48));
	m_graph.at(53).push_back(&nodes.at(49));
	m_graph.at(53).push_back(&nodes.at(50));
	m_graph.at(53).push_back(&nodes.at(51));
	m_graph.at(53).push_back(&nodes.at(54));
	m_graph.at(53).push_back(&nodes.at(55));
	m_graph.at(53).push_back(&nodes.at(57));
	m_graph.at(53).push_back(&nodes.at(66));
	m_graph.at(54).push_back(&nodes.at(54));
	m_graph.at(54).push_back(&nodes.at(3));
	m_graph.at(54).push_back(&nodes.at(19));
	m_graph.at(54).push_back(&nodes.at(20));
	m_graph.at(54).push_back(&nodes.at(25));
	m_graph.at(54).push_back(&nodes.at(27));
	m_graph.at(54).push_back(&nodes.at(32));
	m_graph.at(54).push_back(&nodes.at(33));
	m_graph.at(54).push_back(&nodes.at(35));
	m_graph.at(54).push_back(&nodes.at(37));
	m_graph.at(54).push_back(&nodes.at(41));
	m_graph.at(54).push_back(&nodes.at(44));
	m_graph.at(54).push_back(&nodes.at(45));
	m_graph.at(54).push_back(&nodes.at(47));
	m_graph.at(54).push_back(&nodes.at(48));
	m_graph.at(54).push_back(&nodes.at(49));
	m_graph.at(54).push_back(&nodes.at(50));
	m_graph.at(54).push_back(&nodes.at(53));
	m_graph.at(54).push_back(&nodes.at(55));
	m_graph.at(54).push_back(&nodes.at(57));
	m_graph.at(54).push_back(&nodes.at(58));
	m_graph.at(54).push_back(&nodes.at(64));
	m_graph.at(54).push_back(&nodes.at(65));
	m_graph.at(54).push_back(&nodes.at(66));
	m_graph.at(54).push_back(&nodes.at(67));
	m_graph.at(55).push_back(&nodes.at(55));
	m_graph.at(55).push_back(&nodes.at(2));
	m_graph.at(55).push_back(&nodes.at(3));
	m_graph.at(55).push_back(&nodes.at(19));
	m_graph.at(55).push_back(&nodes.at(20));
	m_graph.at(55).push_back(&nodes.at(25));
	m_graph.at(55).push_back(&nodes.at(27));
	m_graph.at(55).push_back(&nodes.at(32));
	m_graph.at(55).push_back(&nodes.at(35));
	m_graph.at(55).push_back(&nodes.at(37));
	m_graph.at(55).push_back(&nodes.at(45));
	m_graph.at(55).push_back(&nodes.at(46));
	m_graph.at(55).push_back(&nodes.at(48));
	m_graph.at(55).push_back(&nodes.at(50));
	m_graph.at(55).push_back(&nodes.at(51));
	m_graph.at(55).push_back(&nodes.at(53));
	m_graph.at(55).push_back(&nodes.at(54));
	m_graph.at(55).push_back(&nodes.at(56));
	m_graph.at(55).push_back(&nodes.at(57));
	m_graph.at(55).push_back(&nodes.at(58));
	m_graph.at(55).push_back(&nodes.at(59));
	m_graph.at(55).push_back(&nodes.at(64));
	m_graph.at(55).push_back(&nodes.at(65));
	m_graph.at(55).push_back(&nodes.at(66));
	m_graph.at(56).push_back(&nodes.at(56));
	m_graph.at(56).push_back(&nodes.at(2));
	m_graph.at(56).push_back(&nodes.at(19));
	m_graph.at(56).push_back(&nodes.at(25));
	m_graph.at(56).push_back(&nodes.at(27));
	m_graph.at(56).push_back(&nodes.at(32));
	m_graph.at(56).push_back(&nodes.at(51));
	m_graph.at(56).push_back(&nodes.at(55));
	m_graph.at(56).push_back(&nodes.at(57));
	m_graph.at(56).push_back(&nodes.at(58));
	m_graph.at(56).push_back(&nodes.at(64));
	m_graph.at(56).push_back(&nodes.at(66));
	m_graph.at(57).push_back(&nodes.at(57));
	m_graph.at(57).push_back(&nodes.at(2));
	m_graph.at(57).push_back(&nodes.at(3));
	m_graph.at(57).push_back(&nodes.at(20));
	m_graph.at(57).push_back(&nodes.at(25));
	m_graph.at(57).push_back(&nodes.at(27));
	m_graph.at(57).push_back(&nodes.at(32));
	m_graph.at(57).push_back(&nodes.at(35));
	m_graph.at(57).push_back(&nodes.at(37));
	m_graph.at(57).push_back(&nodes.at(41));
	m_graph.at(57).push_back(&nodes.at(43));
	m_graph.at(57).push_back(&nodes.at(44));
	m_graph.at(57).push_back(&nodes.at(45));
	m_graph.at(57).push_back(&nodes.at(48));
	m_graph.at(57).push_back(&nodes.at(50));
	m_graph.at(57).push_back(&nodes.at(51));
	m_graph.at(57).push_back(&nodes.at(52));
	m_graph.at(57).push_back(&nodes.at(53));
	m_graph.at(57).push_back(&nodes.at(54));
	m_graph.at(57).push_back(&nodes.at(55));
	m_graph.at(57).push_back(&nodes.at(56));
	m_graph.at(57).push_back(&nodes.at(58));
	m_graph.at(57).push_back(&nodes.at(59));
	m_graph.at(57).push_back(&nodes.at(60));
	m_graph.at(57).push_back(&nodes.at(62));
	m_graph.at(57).push_back(&nodes.at(63));
	m_graph.at(57).push_back(&nodes.at(64));
	m_graph.at(57).push_back(&nodes.at(65));
	m_graph.at(57).push_back(&nodes.at(66));
	m_graph.at(57).push_back(&nodes.at(70));
	m_graph.at(57).push_back(&nodes.at(72));
	m_graph.at(58).push_back(&nodes.at(58));
	m_graph.at(58).push_back(&nodes.at(3));
	m_graph.at(58).push_back(&nodes.at(41));
	m_graph.at(58).push_back(&nodes.at(45));
	m_graph.at(58).push_back(&nodes.at(54));
	m_graph.at(58).push_back(&nodes.at(55));
	m_graph.at(58).push_back(&nodes.at(56));
	m_graph.at(58).push_back(&nodes.at(57));
	m_graph.at(58).push_back(&nodes.at(59));
	m_graph.at(58).push_back(&nodes.at(65));
	m_graph.at(59).push_back(&nodes.at(59));
	m_graph.at(59).push_back(&nodes.at(3));
	m_graph.at(59).push_back(&nodes.at(50));
	m_graph.at(59).push_back(&nodes.at(51));
	m_graph.at(59).push_back(&nodes.at(55));
	m_graph.at(59).push_back(&nodes.at(57));
	m_graph.at(59).push_back(&nodes.at(58));
	m_graph.at(59).push_back(&nodes.at(60));
	m_graph.at(59).push_back(&nodes.at(62));
	m_graph.at(59).push_back(&nodes.at(63));
	m_graph.at(59).push_back(&nodes.at(65));
	m_graph.at(59).push_back(&nodes.at(67));
	m_graph.at(59).push_back(&nodes.at(68));
	m_graph.at(59).push_back(&nodes.at(72));
	m_graph.at(60).push_back(&nodes.at(60));
	m_graph.at(60).push_back(&nodes.at(3));
	m_graph.at(60).push_back(&nodes.at(50));
	m_graph.at(60).push_back(&nodes.at(51));
	m_graph.at(60).push_back(&nodes.at(57));
	m_graph.at(60).push_back(&nodes.at(59));
	m_graph.at(60).push_back(&nodes.at(61));
	m_graph.at(60).push_back(&nodes.at(71));
	m_graph.at(61).push_back(&nodes.at(61));
	m_graph.at(61).push_back(&nodes.at(0));
	m_graph.at(61).push_back(&nodes.at(11));
	m_graph.at(61).push_back(&nodes.at(39));
	m_graph.at(61).push_back(&nodes.at(40));
	m_graph.at(61).push_back(&nodes.at(42));
	m_graph.at(61).push_back(&nodes.at(45));
	m_graph.at(61).push_back(&nodes.at(60));
	m_graph.at(61).push_back(&nodes.at(62));
	m_graph.at(61).push_back(&nodes.at(63));
	m_graph.at(61).push_back(&nodes.at(64));
	m_graph.at(61).push_back(&nodes.at(66));
	m_graph.at(61).push_back(&nodes.at(67));
	m_graph.at(61).push_back(&nodes.at(71));
	m_graph.at(61).push_back(&nodes.at(72));
	m_graph.at(62).push_back(&nodes.at(62));
	m_graph.at(62).push_back(&nodes.at(0));
	m_graph.at(62).push_back(&nodes.at(11));
	m_graph.at(62).push_back(&nodes.at(39));
	m_graph.at(62).push_back(&nodes.at(40));
	m_graph.at(62).push_back(&nodes.at(42));
	m_graph.at(62).push_back(&nodes.at(45));
	m_graph.at(62).push_back(&nodes.at(51));
	m_graph.at(62).push_back(&nodes.at(57));
	m_graph.at(62).push_back(&nodes.at(59));
	m_graph.at(62).push_back(&nodes.at(61));
	m_graph.at(62).push_back(&nodes.at(63));
	m_graph.at(62).push_back(&nodes.at(64));
	m_graph.at(62).push_back(&nodes.at(65));
	m_graph.at(62).push_back(&nodes.at(66));
	m_graph.at(62).push_back(&nodes.at(67));
	m_graph.at(62).push_back(&nodes.at(68));
	m_graph.at(62).push_back(&nodes.at(71));
	m_graph.at(62).push_back(&nodes.at(72));
	m_graph.at(63).push_back(&nodes.at(63));
	m_graph.at(63).push_back(&nodes.at(11));
	m_graph.at(63).push_back(&nodes.at(39));
	m_graph.at(63).push_back(&nodes.at(40));
	m_graph.at(63).push_back(&nodes.at(42));
	m_graph.at(63).push_back(&nodes.at(45));
	m_graph.at(63).push_back(&nodes.at(57));
	m_graph.at(63).push_back(&nodes.at(59));
	m_graph.at(63).push_back(&nodes.at(61));
	m_graph.at(63).push_back(&nodes.at(62));
	m_graph.at(63).push_back(&nodes.at(64));
	m_graph.at(63).push_back(&nodes.at(65));
	m_graph.at(63).push_back(&nodes.at(66));
	m_graph.at(63).push_back(&nodes.at(67));
	m_graph.at(63).push_back(&nodes.at(68));
	m_graph.at(63).push_back(&nodes.at(70));
	m_graph.at(63).push_back(&nodes.at(71));
	m_graph.at(63).push_back(&nodes.at(72));
	m_graph.at(64).push_back(&nodes.at(64));
	m_graph.at(64).push_back(&nodes.at(2));
	m_graph.at(64).push_back(&nodes.at(18));
	m_graph.at(64).push_back(&nodes.at(20));
	m_graph.at(64).push_back(&nodes.at(25));
	m_graph.at(64).push_back(&nodes.at(27));
	m_graph.at(64).push_back(&nodes.at(32));
	m_graph.at(64).push_back(&nodes.at(35));
	m_graph.at(64).push_back(&nodes.at(37));
	m_graph.at(64).push_back(&nodes.at(40));
	m_graph.at(64).push_back(&nodes.at(41));
	m_graph.at(64).push_back(&nodes.at(45));
	m_graph.at(64).push_back(&nodes.at(51));
	m_graph.at(64).push_back(&nodes.at(54));
	m_graph.at(64).push_back(&nodes.at(55));
	m_graph.at(64).push_back(&nodes.at(56));
	m_graph.at(64).push_back(&nodes.at(57));
	m_graph.at(64).push_back(&nodes.at(61));
	m_graph.at(64).push_back(&nodes.at(62));
	m_graph.at(64).push_back(&nodes.at(63));
	m_graph.at(64).push_back(&nodes.at(65));
	m_graph.at(64).push_back(&nodes.at(66));
	m_graph.at(64).push_back(&nodes.at(67));
	m_graph.at(64).push_back(&nodes.at(71));
	m_graph.at(64).push_back(&nodes.at(72));
	m_graph.at(65).push_back(&nodes.at(65));
	m_graph.at(65).push_back(&nodes.at(2));
	m_graph.at(65).push_back(&nodes.at(3));
	m_graph.at(65).push_back(&nodes.at(18));
	m_graph.at(65).push_back(&nodes.at(20));
	m_graph.at(65).push_back(&nodes.at(27));
	m_graph.at(65).push_back(&nodes.at(32));
	m_graph.at(65).push_back(&nodes.at(35));
	m_graph.at(65).push_back(&nodes.at(37));
	m_graph.at(65).push_back(&nodes.at(41));
	m_graph.at(65).push_back(&nodes.at(45));
	m_graph.at(65).push_back(&nodes.at(51));
	m_graph.at(65).push_back(&nodes.at(54));
	m_graph.at(65).push_back(&nodes.at(55));
	m_graph.at(65).push_back(&nodes.at(57));
	m_graph.at(65).push_back(&nodes.at(58));
	m_graph.at(65).push_back(&nodes.at(59));
	m_graph.at(65).push_back(&nodes.at(62));
	m_graph.at(65).push_back(&nodes.at(63));
	m_graph.at(65).push_back(&nodes.at(64));
	m_graph.at(65).push_back(&nodes.at(66));
	m_graph.at(65).push_back(&nodes.at(70));
	m_graph.at(65).push_back(&nodes.at(72));
	m_graph.at(66).push_back(&nodes.at(66));
	m_graph.at(66).push_back(&nodes.at(0));
	m_graph.at(66).push_back(&nodes.at(2));
	m_graph.at(66).push_back(&nodes.at(5));
	m_graph.at(66).push_back(&nodes.at(11));
	m_graph.at(66).push_back(&nodes.at(18));
	m_graph.at(66).push_back(&nodes.at(20));
	m_graph.at(66).push_back(&nodes.at(25));
	m_graph.at(66).push_back(&nodes.at(27));
	m_graph.at(66).push_back(&nodes.at(30));
	m_graph.at(66).push_back(&nodes.at(32));
	m_graph.at(66).push_back(&nodes.at(33));
	m_graph.at(66).push_back(&nodes.at(34));
	m_graph.at(66).push_back(&nodes.at(35));
	m_graph.at(66).push_back(&nodes.at(37));
	m_graph.at(66).push_back(&nodes.at(39));
	m_graph.at(66).push_back(&nodes.at(40));
	m_graph.at(66).push_back(&nodes.at(41));
	m_graph.at(66).push_back(&nodes.at(42));
	m_graph.at(66).push_back(&nodes.at(44));
	m_graph.at(66).push_back(&nodes.at(45));
	m_graph.at(66).push_back(&nodes.at(47));
	m_graph.at(66).push_back(&nodes.at(48));
	m_graph.at(66).push_back(&nodes.at(49));
	m_graph.at(66).push_back(&nodes.at(50));
	m_graph.at(66).push_back(&nodes.at(53));
	m_graph.at(66).push_back(&nodes.at(54));
	m_graph.at(66).push_back(&nodes.at(55));
	m_graph.at(66).push_back(&nodes.at(56));
	m_graph.at(66).push_back(&nodes.at(57));
	m_graph.at(66).push_back(&nodes.at(61));
	m_graph.at(66).push_back(&nodes.at(62));
	m_graph.at(66).push_back(&nodes.at(63));
	m_graph.at(66).push_back(&nodes.at(64));
	m_graph.at(66).push_back(&nodes.at(65));
	m_graph.at(66).push_back(&nodes.at(67));
	m_graph.at(66).push_back(&nodes.at(69));
	m_graph.at(66).push_back(&nodes.at(72));
	m_graph.at(67).push_back(&nodes.at(67));
	m_graph.at(67).push_back(&nodes.at(42));
	m_graph.at(67).push_back(&nodes.at(45));
	m_graph.at(67).push_back(&nodes.at(54));
	m_graph.at(67).push_back(&nodes.at(59));
	m_graph.at(67).push_back(&nodes.at(61));
	m_graph.at(67).push_back(&nodes.at(62));
	m_graph.at(67).push_back(&nodes.at(63));
	m_graph.at(67).push_back(&nodes.at(64));
	m_graph.at(67).push_back(&nodes.at(66));
	m_graph.at(67).push_back(&nodes.at(68));
	m_graph.at(67).push_back(&nodes.at(70));
	m_graph.at(67).push_back(&nodes.at(72));
	m_graph.at(68).push_back(&nodes.at(68));
	m_graph.at(68).push_back(&nodes.at(4));
	m_graph.at(68).push_back(&nodes.at(14));
	m_graph.at(68).push_back(&nodes.at(15));
	m_graph.at(68).push_back(&nodes.at(32));
	m_graph.at(68).push_back(&nodes.at(33));
	m_graph.at(68).push_back(&nodes.at(36));
	m_graph.at(68).push_back(&nodes.at(41));
	m_graph.at(68).push_back(&nodes.at(59));
	m_graph.at(68).push_back(&nodes.at(62));
	m_graph.at(68).push_back(&nodes.at(63));
	m_graph.at(68).push_back(&nodes.at(67));
	m_graph.at(68).push_back(&nodes.at(69));
	m_graph.at(68).push_back(&nodes.at(70));
	m_graph.at(68).push_back(&nodes.at(72));
	m_graph.at(68).push_back(&nodes.at(73));
	m_graph.at(68).push_back(&nodes.at(75));
	m_graph.at(69).push_back(&nodes.at(69));
	m_graph.at(69).push_back(&nodes.at(4));
	m_graph.at(69).push_back(&nodes.at(5));
	m_graph.at(69).push_back(&nodes.at(10));
	m_graph.at(69).push_back(&nodes.at(14));
	m_graph.at(69).push_back(&nodes.at(15));
	m_graph.at(69).push_back(&nodes.at(30));
	m_graph.at(69).push_back(&nodes.at(32));
	m_graph.at(69).push_back(&nodes.at(33));
	m_graph.at(69).push_back(&nodes.at(34));
	m_graph.at(69).push_back(&nodes.at(36));
	m_graph.at(69).push_back(&nodes.at(40));
	m_graph.at(69).push_back(&nodes.at(41));
	m_graph.at(69).push_back(&nodes.at(42));
	m_graph.at(69).push_back(&nodes.at(44));
	m_graph.at(69).push_back(&nodes.at(45));
	m_graph.at(69).push_back(&nodes.at(48));
	m_graph.at(69).push_back(&nodes.at(49));
	m_graph.at(69).push_back(&nodes.at(50));
	m_graph.at(69).push_back(&nodes.at(66));
	m_graph.at(69).push_back(&nodes.at(68));
	m_graph.at(69).push_back(&nodes.at(70));
	m_graph.at(69).push_back(&nodes.at(73));
	m_graph.at(69).push_back(&nodes.at(74));
	m_graph.at(69).push_back(&nodes.at(75));
	m_graph.at(70).push_back(&nodes.at(70));
	m_graph.at(70).push_back(&nodes.at(4));
	m_graph.at(70).push_back(&nodes.at(14));
	m_graph.at(70).push_back(&nodes.at(15));
	m_graph.at(70).push_back(&nodes.at(32));
	m_graph.at(70).push_back(&nodes.at(33));
	m_graph.at(70).push_back(&nodes.at(36));
	m_graph.at(70).push_back(&nodes.at(41));
	m_graph.at(70).push_back(&nodes.at(57));
	m_graph.at(70).push_back(&nodes.at(63));
	m_graph.at(70).push_back(&nodes.at(65));
	m_graph.at(70).push_back(&nodes.at(67));
	m_graph.at(70).push_back(&nodes.at(68));
	m_graph.at(70).push_back(&nodes.at(69));
	m_graph.at(70).push_back(&nodes.at(71));
	m_graph.at(70).push_back(&nodes.at(72));
	m_graph.at(70).push_back(&nodes.at(73));
	m_graph.at(70).push_back(&nodes.at(75));
	m_graph.at(71).push_back(&nodes.at(71));
	m_graph.at(71).push_back(&nodes.at(4));
	m_graph.at(71).push_back(&nodes.at(45));
	m_graph.at(71).push_back(&nodes.at(60));
	m_graph.at(71).push_back(&nodes.at(61));
	m_graph.at(71).push_back(&nodes.at(62));
	m_graph.at(71).push_back(&nodes.at(63));
	m_graph.at(71).push_back(&nodes.at(64));
	m_graph.at(71).push_back(&nodes.at(70));
	m_graph.at(71).push_back(&nodes.at(72));
	m_graph.at(72).push_back(&nodes.at(72));
	m_graph.at(72).push_back(&nodes.at(0));
	m_graph.at(72).push_back(&nodes.at(42));
	m_graph.at(72).push_back(&nodes.at(45));
	m_graph.at(72).push_back(&nodes.at(51));
	m_graph.at(72).push_back(&nodes.at(57));
	m_graph.at(72).push_back(&nodes.at(59));
	m_graph.at(72).push_back(&nodes.at(61));
	m_graph.at(72).push_back(&nodes.at(62));
	m_graph.at(72).push_back(&nodes.at(63));
	m_graph.at(72).push_back(&nodes.at(64));
	m_graph.at(72).push_back(&nodes.at(65));
	m_graph.at(72).push_back(&nodes.at(66));
	m_graph.at(72).push_back(&nodes.at(67));
	m_graph.at(72).push_back(&nodes.at(68));
	m_graph.at(72).push_back(&nodes.at(70));
	m_graph.at(72).push_back(&nodes.at(71));
	m_graph.at(73).push_back(&nodes.at(73));
	m_graph.at(73).push_back(&nodes.at(4));
	m_graph.at(73).push_back(&nodes.at(33));
	m_graph.at(73).push_back(&nodes.at(68));
	m_graph.at(73).push_back(&nodes.at(69));
	m_graph.at(73).push_back(&nodes.at(70));
	m_graph.at(73).push_back(&nodes.at(74));
	m_graph.at(73).push_back(&nodes.at(75));
	m_graph.at(74).push_back(&nodes.at(74));
	m_graph.at(74).push_back(&nodes.at(5));
	m_graph.at(74).push_back(&nodes.at(30));
	m_graph.at(74).push_back(&nodes.at(31));
	m_graph.at(74).push_back(&nodes.at(33));
	m_graph.at(74).push_back(&nodes.at(34));
	m_graph.at(74).push_back(&nodes.at(69));
	m_graph.at(74).push_back(&nodes.at(73));
	m_graph.at(74).push_back(&nodes.at(75));
	m_graph.at(75).push_back(&nodes.at(75));
	m_graph.at(75).push_back(&nodes.at(4));
	m_graph.at(75).push_back(&nodes.at(5));
	m_graph.at(75).push_back(&nodes.at(10));
	m_graph.at(75).push_back(&nodes.at(30));
	m_graph.at(75).push_back(&nodes.at(33));
	m_graph.at(75).push_back(&nodes.at(34));
	m_graph.at(75).push_back(&nodes.at(40));
	m_graph.at(75).push_back(&nodes.at(41));
	m_graph.at(75).push_back(&nodes.at(42));
	m_graph.at(75).push_back(&nodes.at(44));
	m_graph.at(75).push_back(&nodes.at(45));
	m_graph.at(75).push_back(&nodes.at(48));
	m_graph.at(75).push_back(&nodes.at(68));
	m_graph.at(75).push_back(&nodes.at(69));
	m_graph.at(75).push_back(&nodes.at(70));
	m_graph.at(75).push_back(&nodes.at(73));
	m_graph.at(75).push_back(&nodes.at(74));


	m_neighbours.resize(m_graph.size());

	for (unsigned int i = 0; i < m_graph.size(); i++)
	{
		for (unsigned int j = 1; j < m_graph.at(i).size(); j++)
		{
			m_neighbours.at(i).push_back(m_graph.at(i).at(j));
		}

	}

	for (int i = 0; i < m_neighbours.size(); i++)
	{
		/////////////////////////////////////////////////////////////m_nodeMap.GetEdges()->insert(make_pair(&nodes.at(i), m_neighbours.at(i)));
	}

}


Pathfinder::~Pathfinder()
{

}





void Pathfinder::GeneratePath(vector<LMVector3 *> * pathOut, LMVector3 * position, LMVector3 * target)
{

	//LMVector3 * position, LMVector3 * target

	m_openList.resize(0);
	m_closedList.resize(0);


	//calc start node
	LMVector3 * bestStartNode = NULL;
	float best = 9999999.0f;
	float dist = 0.0f;


	for (unsigned int i = 0; i < m_graph.size(); i++)
	{
		if (m_graph.at(i).size() == 0) continue;

		dist = position->DisplacementMag(*m_graph.at(i).at(0));
		if (dist < best)
		{
			best = dist;
			bestStartNode = m_graph.at(i).at(0);
		}
	}
	
	m_bestNodes.resize(0);
	m_bestNodeDistances.resize(0);


	m_bestNodes.resize(3,nullptr);


	m_bestNodeDistances.resize(3,99999.9f);

	bool isBestEndFound = false;


	//is this overwriting index 0 if the tested distance is lower, only to write inferior (4th 5th best?) distances to index 1 and index 2
	for (unsigned int i = 0; i < m_graph.size(); i++)
	{
		if (m_graph.at(i).size() == 0) continue;
		
		for (unsigned int j = 0; j < m_bestNodeDistances.size(); j++)
		{
			dist = target->DisplacementMag(*m_graph.at(i).at(0));

			if (dist < m_bestNodeDistances.at(j))
			{
				m_bestNodeDistances.at(j) = dist;
				m_bestNodes.at(j) = m_graph.at(i).at(0);
				
				isBestEndFound = true;

				j = m_bestNodeDistances.size();
				break; //same effect as an example
			}
		}
	}


	if (bestStartNode != NULL && isBestEndFound)
	{
		Search(pathOut, bestStartNode, position, target);
		//OutputDebugString("Start and end node found: Call to Search.\n");
	}
}



void Pathfinder::Search(vector<LMVector3 *> * pathOut, LMVector3 * startNode, LMVector3 * position, LMVector3 * target)
{
	SearchMarch19(pathOut,startNode,position,target);
	//Search1(pathOut, startNode, position, target);
	//Search2(pathOut,startNode,position,target);//newest attempt
}




void Pathfinder::SearchMarch19(vector<LMVector3 *> * pathOut, LMVector3 * startNode, LMVector3 * position, LMVector3 * target)
{
	OutputDebugString("Pathfinder::Search Begin Search \n");


	vector<LMVector3*> * vec = NULL;
	vector<LMVector3*> * vecInClosed = NULL;
	bool found = false;



	float f = 0.0f;
	float g = 0.0f;
	float h = 0.0f;

	float SumOfG = position->DisplacementMag(*startNode);

	//1. Add Starting node to the open list
	m_openList.push_back(VectorForNode(startNode));
	//m_closedList.push_back(VectorForNode(startNode));

	vector<LMVector3*> * currentNode = VectorForNode(startNode);
	bool isComplete = false;
	while (!isComplete)
	{
		//3. Find lowest cost node on open list
		int indexofLowestCostNode = -1;
		float lowestCost = 9999.9f;

		for (unsigned int i = 0; i < m_openList.size(); ++i)
		{
			//maybe to not focus on this if i change pathfind methods anyway
			//thinking of making a tool that will give us a grid and we can do manhattan A Star on that.


			//we have yet to fully search all possibilities from closed list anyway. just first 'best one' at each depth.

			//prior to late jan that works
			//g = SumOfG;
			//if (m_closedList.size() > 0) g += position->DisplacementMag(*currentNode->at(0));
			//h = m_openList.at(i)->at(0)->DisplacementMag(*targetNode) - 2;
			//f = g + h;

			//late jan version which is adding stuff over and over to closed list
			g = SumOfG;
			if (m_closedList.size() > 0) g += currentNode->at(0)->DisplacementMag(*m_openList.at(i)->at(0));
			h = m_openList.at(i)->at(0)->DisplacementMag(*m_bestNodes.at(0)) - 0.1f;
			f = g + h;



			//most recent
			//g = SumOfG;
			//if (m_closedList.size() > 0) g += position->DisplacementMag(*currentNode->at(0));
			//h = m_openList.at(i)->at(0)->DisplacementMag(*targetNode) - 2;
			//f = g + h;

			//an attempt
			//g = SumOfG;
			//if (m_closedList.size() > 0) g+= m_closedList.back()->at(0)->DisplacementMag(*m_openList.at(i)->at(0));
			//h = m_openList.at(i)->at(0)->DisplacementMag(*targetNode) -2.0f;
			//f = g + h;

			if (f < lowestCost)
			{
				lowestCost = f;
				indexofLowestCostNode = i;
			}
		}

		if (indexofLowestCostNode != -1)//valid node found
		{
			/*
			sprintf_s(
				node_buffer,
				"Node on Closed: (%f %f %f)\n",
				m_openList.at(indexofLowestCostNode)->at(0)->x,
				m_openList.at(indexofLowestCostNode)->at(0)->y,
				m_openList.at(indexofLowestCostNode)->at(0)->z);

			if (DEBUGPATHFINDING) OutputDebugString(node_buffer);
			*/

			currentNode = m_openList.at(indexofLowestCostNode);

			if (currentNode->at(0) == m_bestNodes.at(0))
			{
				isComplete = true;
				//target added to closed list = target found

				m_closedList.push_back(VectorForNode(m_bestNodes.at(0)));
				StoreClosedListInPath(pathOut, position, target);
				if (DEBUGPATHFINDING) OutputDebugString("targ found \n");
				if (DEBUGPATHFINDING) OutputDebugString("Pathfinder::Search End Search \n");
				return;
			}


			if (m_closedList.size() > 0) SumOfG += m_closedList.back()->at(0)->DisplacementMag(*m_openList.at(indexofLowestCostNode)->at(0));
			m_closedList.push_back(m_openList.at(indexofLowestCostNode));
			m_openList.erase(m_openList.begin() + indexofLowestCostNode);


		}
		else
		{
			isComplete = true;
			//no path
			pathOut->resize(0);
			if (DEBUGPATHFINDING) OutputDebugString("Call to Search: NO PATH\n");
			if (DEBUGPATHFINDING) OutputDebugString("Pathfinder::Search End Search \n");
			return;
		}

		//Add edges to open list

		vec = NULL;
		vecInClosed = NULL;

		//i 0 is node i 1+ is tree
		for (unsigned int i = 1; i < currentNode->size(); ++i)
		{
			vec = VectorForNode(currentNode->at(i));
			//if (DEBUGPATHFINDING) if (vec == NULL) OutputDebugString("Vec for path is null");
			found = false;

			for (unsigned int j = 0; j < m_closedList.size(); ++j)
			{
				vecInClosed = m_closedList.at(j);

				if (*vec == *vecInClosed)
				{
					found = true;
					//if (DEBUGPATHFINDING) OutputDebugString("found on closed list dont add to open");

					//in some situations there are nodes on the open list that have been added to the closed list
				}
			}

			if (!found) m_openList.push_back(vec);
		}
	}

	if (DEBUGPATHFINDING) OutputDebugString("Call to Search: Exited LOOP and found end of search function\n");
	if (DEBUGPATHFINDING) OutputDebugString("Pathfinder::Search End Search \n");
	pathOut->resize(0);



	return;
}


void Pathfinder::Search1(vector<LMVector3 *> * pathOut, LMVector3 * startNode, LMVector3 * position, LMVector3 * target)
{/*
	
	float f = 0.0f;
	float g = 0.0f;
	float h = 0.0f;

	float SumOfG = position->DisplacementMag(*startNode);

	///////////////////////////////////////////////////////////////////////////////////////////////////////////
		//1. Add starting node to openList ////////////////////////////////////////////////////////////////////////
	m_open1.emplace(*startNode, 0);

	LMVector3 * currentNode = startNode;

	LMVector3 * testingNode = nullptr;
	LMVector3 * lowestCostNode = nullptr;


	came_from[*startNode] = *startNode;
	cost_so_far[*startNode] = 0;

	//f = g + h;




	///////////////////////////////////////////////////////////////////////////////////////////////////////////
		//2 Execute a series of steps until the target is found or break out if seach is exhuasted ////////////////


	while (!m_open1.empty())
	{
		///////////////////////////////////////////////////////////////////////////////////////////////////////////
		//2a Find lowest cost node on open list ///////////////////////////////////////////////////////////////////

		LMVector3 & selected = m_open1.top().second;//must have a came_from before we select
		m_open1.pop();


		m_closed1.push( make_pair(cost_so_far[selected], selected) );
		
		///////////////////////////////////////////////////////////////////////////////////////////////////////////
		// 2d. Now we have our lowest cost node, set its G as OUR sum + latest distance

		cost_so_far[selected] = cost_so_far[came_from[selected]] + selected.DisplacementMag(came_from[selected]);
		 
		///////////////////////////////////////////////////////////////////////////////////////////////////////////
		// 2E. STOP WHEN target added to the closed list.


		for (unsigned int j = 0; j < m_bestNodes.size(); j++)
		{
			if ( selected.x == m_bestNodes.at(j)->x && selected.y == m_bestNodes.at(j)->y) return;


			//if (selected == m_bestNodes.at(j)) return;
		}

	///////////////////////////////////////////////////////////////////////////////////////////////////////////
	// 2F. ADD CHILDREN TO OPENLIST
	//must have a came_from before we select (later, at top of while)

		vector<LMVector3*> * treeChildren = nullptr;
		for (unsigned int i = 0; i < m_graph.size(); i++)
		{

			if (selected.x == m_graph.at(i).at(0)->x && selected.y == m_graph.at(i).at(0)->y)
			{
				treeChildren = &m_graph.at(i);

				for (unsigned int j = 0; j < m_open1.size(); j++)
				{
					//are the children already on the open list; then:
					
					//selected g + (cost selected to CHILD COST).
					g = selected.DisplacementMag(*m_graph.at(i).at(j));

					m_open1.push( make_pair(g, *m_graph.at(i).at(j)) );
					came_from[*m_graph.at(i).at(j)] = selected;

				}

				break;
			}

		}


		///////////////////////////////////////////////////////////////////////////////////////////////////////////
		// 2G. If the edge is in the closed list, dont add it to the open list;
		//we could iterated the closed list and search for the neighbours here;
		//or since we have a boolean in the object

		// includes

		//////////////////////////////////////////////////////////////////////////////////////////////////////////
		//
		// 2H.  If it is on the open list already, check to see if this path to that square is better,
		//
		//

		for (LMVector3 * next : m_nodeMap.neighbours(&selected)) {
		
			g = cost_so_far[selected] + selected.DisplacementMag(*next); //m_nodeMap.cost(selected, next);
			
			if (cost_so_far.find(*next) == cost_so_far.end() || g < cost_so_far[*next])
			{
				cost_so_far[*next] = g;
			
			
				////

				LMVector3 * bestEndNode = nullptr;
				float fitness = 999999.9f;

				for (unsigned int j = 0; j < m_bestNodes.size(); j++)
				{
					g = cost_so_far[selected] + selected.DisplacementMag(*m_bestNodes.at(j));



					h = next->DisplacementMag(*m_bestNodes.at(j)) - 2.0f;
					f = g + h;

					if (f < fitness)
					{
						fitness = f;
						bestEndNode = m_bestNodes.at(j);
					}
					
					//g = 0.0f;
					//h = target->DisplacementMag(*m_bestNodes.at(i));
					//f = g + h;


				}


				//


				f = g + next->DisplacementMag(*bestEndNode);
			
				m_open1.push(make_pair(f, selected));
			
				came_from[*next] = selected;
			}
		}
	}

	*/
}

void Pathfinder::Search2(vector<LMVector3 *> * pathOut, LMVector3 * startNode, LMVector3 * position, LMVector3 * target)
{
	/*
	OutputDebugString("Pathfinder::Search Begin Search \n");


	vector<LMVector3*> * vec = NULL;
	vector<LMVector3*> * vecInClosed = NULL;
	bool found = false;



	float f = 0.0f;
	float g = 0.0f;
	float h = 0.0f;

	float SumOfG = position->DisplacementMag(*startNode);

	//1. Add Starting node to the open list
	 m_openList.push_back(VectorForNode(startNode));
	//m_closedList.push_back(VectorForNode(startNode));

	vector<LMVector3*> * currentNode = VectorForNode(startNode);
	bool isComplete = false;
	while (!isComplete)
	{
		//3. Find lowest cost node on open list
		int indexofLowestCostNode = -1;
		float lowestCost = 9999.9f;

		for (unsigned int i = 0; i < m_openList.size(); ++i)
		{
			//maybe to not focus on this if i change pathfind methods anyway
			//thinking of making a tool that will give us a grid and we can do manhattan A Star on that.
			
			
			//we have yet to fully search all possibilities from closed list anyway. just first 'best one' at each depth.

			//prior to late jan that works
			//g = SumOfG;
			//if (m_closedList.size() > 0) g += position->DisplacementMag(*currentNode->at(0));
			//h = m_openList.at(i)->at(0)->DisplacementMag(*targetNode) - 2;
			//f = g + h;

			//late jan version which is adding stuff over and over to closed list


			LMVector3 * bestEndNode = nullptr;
			float fitness = 99999.9f;

			for (unsigned int j = 0; j < m_bestNodes.size(); j++)
			{
			
				g = SumOfG;
				if (m_closedList.size() > 0) g += currentNode->at(0)->DisplacementMag(*m_openList.at(i)->at(0));
				h = m_openList.at(i)->at(0)->DisplacementMag(*m_bestNodes.at(j)) - 2.0f;
				f = g + h;

				if (f < fitness)
				{
					fitness = f;
					bestEndNode = m_bestNodes.at(j);
				}
				
				///g = 0.0f;
				///h = target->DisplacementMag(*m_bestNodes.at(i));
				///f = g + h;
			}


			//most recent
			//g = SumOfG;
			//if (m_closedList.size() > 0) g += position->DisplacementMag(*currentNode->at(0));
			//h = m_openList.at(i)->at(0)->DisplacementMag(*targetNode) - 2;
			//f = g + h;

			//an attempt
			//g = SumOfG;
			//if (m_closedList.size() > 0) g+= m_closedList.back()->at(0)->DisplacementMag(*m_openList.at(i)->at(0));
			//h = m_openList.at(i)->at(0)->DisplacementMag(*targetNode) -2.0f;
			//f = g + h;
			
			if (f < lowestCost)
			{
				lowestCost = f;
				indexofLowestCostNode = i;
			}
		}

		if (indexofLowestCostNode != -1)//valid node found
		{
			
		//	sprintf_s(
		//		node_buffer,
		//		"Node on Closed: (%f %f %f)\n",
		//		m_openList.at(indexofLowestCostNode)->at(0)->x,
		//		m_openList.at(indexofLowestCostNode)->at(0)->y,
		//		m_openList.at(indexofLowestCostNode)->at(0)->z);
			
		//	if (DEBUGPATHFINDING) OutputDebugString(node_buffer);
			

			currentNode = m_openList.at(indexofLowestCostNode);
			


			for (unsigned int j = 0; j < m_bestNodes.size(); j++)
			{


				if (currentNode->at(0) == m_bestNodes.at(j))
				{
					isComplete = true;
					//target added to closed list = target found

					m_closedList.push_back(VectorForNode(m_bestNodes.at(j)));
					StoreClosedListInPath(pathOut, position, target);
					if (DEBUGPATHFINDING) OutputDebugString("targ found \n");
					if (DEBUGPATHFINDING) OutputDebugString("Pathfinder::Search End Search \n");
					return;
				}

			}
			
			
			if (m_closedList.size() > 0) SumOfG += m_closedList.back()->at(0)->DisplacementMag(*m_openList.at(indexofLowestCostNode)->at(0));
			m_closedList.push_back(m_openList.at(indexofLowestCostNode));
			m_openList.erase(m_openList.begin() + indexofLowestCostNode);
			
			
		}
		else
		{
			isComplete = true;
			//no path
			pathOut->resize(0);
			if (DEBUGPATHFINDING) OutputDebugString("Call to Search: NO PATH\n");
			if (DEBUGPATHFINDING) OutputDebugString("Pathfinder::Search End Search \n");
			return;
		}
		
		//Add edges to open list
		
		vec = NULL;
		vecInClosed = NULL;
		
		//i 0 is node i 1+ is tree
		for (unsigned int i = 1; i < currentNode->size(); ++i)
		{
			vec = VectorForNode(currentNode->at(i));
			//if (DEBUGPATHFINDING) if (vec == NULL) OutputDebugString("Vec for path is null");
			found = false;
			
			for (unsigned int j = 0; j < m_closedList.size(); ++j)
			{
				vecInClosed = m_closedList.at(j);

				if (*vec == *vecInClosed)
				{
					found = true;
					//if (DEBUGPATHFINDING) OutputDebugString("found on closed list dont add to open");

					//in some situations there are nodes on the open list that have been added to the closed list
				}
			}

			if (!found) m_openList.push_back(vec);
		}
	}

	if (DEBUGPATHFINDING) OutputDebugString("Call to Search: Exited LOOP and found end of search function\n");
	if (DEBUGPATHFINDING) OutputDebugString("Pathfinder::Search End Search \n");
	pathOut->resize(0);



	*/

	return;
}


void Pathfinder::SearchMaze19(vector<LMVector3*>* pathOut, LMVector3 * startNode, LMVector3 * position, LMVector3 * target)
{

	int timeoutInitial = 15000;
	int timeout = timeoutInitial;
}


vector<LMVector3*> * Pathfinder::VectorForNode(LMVector3 * node)
{
	for (unsigned int i = 0; i < m_graph.size(); ++i)
	{
		if (node == m_graph.at(i).at(0))
		{
			return &m_graph.at(i);
		}
	}
	return NULL;
}


void Pathfinder::StoreClosedListInPath(vector<LMVector3 *> * pathOut, LMVector3 * position, LMVector3 * target)
{
	/*
	if (m_closedList.size() == 0)
	{
		pathOut->resize(0);
		return;
	}*/

	//if (DEBUGPATHFINDING) sprintf_s(node_buffer, "Closed list size: %i\n", m_closedList.size());
	//if (DEBUGPATHFINDING) OutputDebugString(node_buffer);

	m_tempGraph.resize(0);
	for (unsigned int i = 0; i < m_closedList.size(); i++)
	{
		
		m_tempGraph.push_back(m_closedList.at(i));
	}

	if (m_optimiseFunction != nullptr) m_optimiseFunction(pathOut, position, target);
	else
	{
		pathOut->resize(m_closedList.size());

		for (unsigned int i = 0; i <= m_closedList.size(); ++i)
		{
			pathOut->at(i) = m_closedList.at(i)->at(0); //bad access of graph node vector3's directly from player classes etc
		}
	}
}


/*
template<typename typename T, typename priority_t>
void Pathfinder::Search2(MyGraph graph, typename MyGraph::Location start)
{
	
	typedef typename MyGraph::Location Location;

	queue<Location> openList;
	openList.push(start);

	unordered_set<Location> closedList;
	closedList.insert(start);

	OutputDebugString("pre nav\n");


	while (!closedList.empty())
	{
		auto current = openList.front();
		openList.pop();

		OutputDebugString("nav\n");

		for (auto next : graph.neighbours(current))
		{
			if (!closedList.count(next))
			{
				openList.push(next);
				closedList.insert(next);
			}
		}
	}
	OutputDebugString("end nav\n");



	//float g = 
	//float h = 
	//float f = g + h;



}*/


deque<vector<LMVector3*>*> * Pathfinder::GetClosedList()
{ return &m_closedList; }




void Pathfinder::SetOptimiseFunction(std::function<void(vector<LMVector3*>*pathOut, LMVector3*position, LMVector3*target)> f)
{ m_optimiseFunction = f; }
