SELECT Helicopters.brand, sum(Flights.hours)
  FROM Helicopters INNER JOIN Flights ON Helicopters.number = Flights.helicopter_number WHERE Helicopters.last_overhaul < Flights.date GROUP BY Helicopters.brand;
