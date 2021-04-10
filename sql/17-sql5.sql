select q as Model,s as Surname, w as Adress, e as Position, Summa, max(num_flights) as Flights_number
from (
  select count(Flights.id) as num_flights, Helicopters.brand as q, Pilots.surname as s,Pilots.adress as w, Pilots.position as e, sum(Flights.cost) as Summa
  from Helicopters INNER JOIN Flights ON Helicopters.number = Flights.helicopter_number INNER JOIN Pilots ON Pilots.helicopter_number = Helicopters.number
)
