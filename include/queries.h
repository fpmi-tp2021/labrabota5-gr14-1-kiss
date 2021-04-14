#pragma once

#define QUERY_IMAGE "SELECT image FROM Helicopters WHERE number=1"
#define Q_IMAGE 'i'
#define QUERY_ALL_FLIGHTS "SELECT * FROM Flights"
#define Q_ALL_FLIGHTS 'F'
#define QUERY_ALL_HELICOPTERS "SELECT * FROM Helicopters"
#define Q_ALL_HELICOPTERS 'H'
#define QUERY_ALL_PILOTS "SELECT * FROM Pilots"
#define Q_ALL_PILOTS 'P'
#define QUERY_1 "SELECT Helicopters.brand, sum(Flights.hours) FROM Helicopters INNER JOIN Flights ON Helicopters.number = Flights.helicopter_number WHERE Helicopters.last_overhaul < Flights.date;"
#define Q_1 'o'
#define QUERY_2 "SELECT Helicopters.brand, sum(Flights.hours), sum(Flights.quantity), Flights.id, Flights.date FROM Helicopters INNER JOIN Flights ON Helicopters.number = Flights.helicopter_number;"
#define Q_2 'f'
