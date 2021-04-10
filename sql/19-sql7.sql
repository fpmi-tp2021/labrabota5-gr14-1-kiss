SELECT Flights.special as Special, Flights.hours as Czasy, Flights.quantity as Kolvo, Flights.cost as Cena
  FROM Flights INNER JOIN Pilots ON Pilots.helicopter_number = Flights.helicopter_number WHERE Pilots.surname = 'Petro';
