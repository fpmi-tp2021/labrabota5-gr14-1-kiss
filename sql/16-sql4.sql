SELECT Helicopters.brand, sum(Flights.hours), sum(Flights.quantity), sum(Flights.cost), COUNT(Flights.id) as Kolvo
  FROM Helicopters INNER JOIN Flights ON Helicopters.number = Flights.helicopter_number WHERE Flights.special = 0 GROUP BY Helicopters.brand;
