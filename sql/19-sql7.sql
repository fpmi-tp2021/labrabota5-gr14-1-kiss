SELECT Flights.date, Flights.hours as Czasy, Flights.quantity as Kolvo, Flights.cost as Cena, Flights.special as Special
  FROM Flights INNER JOIN Pilots ON Pilots.helicopter_number = Flights.helicopter_number WHERE Pilots.surname = 'Vasili';
