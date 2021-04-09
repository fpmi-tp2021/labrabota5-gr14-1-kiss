SELECT Helicopters.brand, sum(Flights.hours), sum(Flights.quantity), sum(Flights.cost)
  FROM Helicopters INNER JOIN Flights ON Helicopters.number = Flights.helicopter_number WHERE Flights.special = 0;
