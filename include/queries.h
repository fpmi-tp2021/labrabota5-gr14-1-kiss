#pragma once

#define QUERY_IMAGE "SELECT image FROM Helicopters WHERE number=1"
#define Q_IMAGE 'i'
#define QUERY_ALL_FLIGHTS "SELECT * FROM Flights"
#define Q_ALL_FLIGHTS 'F'
#define QUERY_ALL_HELICOPTERS "SELECT * FROM Helicopters"
#define Q_ALL_HELICOPTERS 'H'
#define QUERY_ALL_PILOTS "SELECT * FROM Pilots"
#define Q_ALL_PILOTS 'P'
#define QUERY_1 "SELECT Helicopters.brand, sum(Flights.hours)  FROM Helicopters INNER JOIN Flights ON Helicopters.number = Flights.helicopter_number WHERE Helicopters.last_overhaul < Flights.date GROUP BY Helicopters.brand;"
#define Q_1 '1'
#define QUERY_2 "SELECT Helicopters.brand, sum(Flights.hours), sum(Flights.quantity), Flights.id, Flights.date  FROM Helicopters INNER JOIN Flights ON Helicopters.number = Flights.helicopter_number GROUP BY Helicopters.brand;"
#define Q_2 '2'
#define QUERY_3 "SELECT Helicopters.brand, sum(Flights.hours), sum(Flights.quantity), sum(Flights.cost), COUNT(Flights.id) as Kolvo  FROM Helicopters INNER JOIN Flights ON Helicopters.number = Flights.helicopter_number WHERE Flights.special = 1 GROUP BY Helicopters.brand;"
#define Q_3 '3'
#define QUERY_4 "SELECT Helicopters.brand, sum(Flights.hours), sum(Flights.quantity), sum(Flights.cost), COUNT(Flights.id) as Kolvo  FROM Helicopters INNER JOIN Flights ON Helicopters.number = Flights.helicopter_number WHERE Flights.special = 0 GROUP BY Helicopters.brand;"
#define Q_4 '4'
#define QUERY_5 "select * from pilots inner join (select helicopters.number as hn, helicopters.brand from Helicopters inner join (select max(num_flights), sum(cost) as total, brand as b from (select count(Flights.id) as num_flights, Flights.cost as cost, Helicopters.brand as brand from Flights inner join Helicopters on Flights.helicopter_number = Helicopters.number group by brand)) on helicopters.brand = b) on pilots.helicopter_number = hn group by pilots.surname;"
#define Q_5 '5'
#define QUERY_6 "select Flights.date, Flights.weight, Flights.cost, h from flights inner join (select h,max(total) from (select sum(fc) as total, hn as h from (select Pilots.surname as s, sum(Flights.cost) as fc, Flights.helicopter_number as hn FROM Pilots INNER JOIN Flights ON Pilots.helicopter_number = Flights.helicopter_number GROUP BY Pilots.surname) GROUP BY hn)) ON flights.helicopter_number = h;"
#define Q_6 '6'
#define QUERY_7 "SELECT Flights.date, Flights.hours as Czasy, Flights.quantity as Kolvo, Flights.cost as Cena, Flights.special as Special  FROM Flights INNER JOIN Pilots ON Pilots.helicopter_number = Flights.helicopter_number WHERE Pilots.surname = 'Vasili';"
#define Q_7 '7'
