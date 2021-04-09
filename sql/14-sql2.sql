SELECT Helicopters.brand, sum(Flights.hours), sum(Flights.quantity), Flights.id, Flights.data
  FROM Helicopters INNER JOIN Flights ON Helicopters.number = Flights.helicopter_number;
