select d as Cost,t as Surname, w as Data, e as Quantity, r as Weight, max(q) as Flights_total
from (
  select sum(Flights.cost) as q, Flights.date as w, Flights.quantity as e, Flights.weight as r, Pilots.surname as t, Flights.cost as d
  from Helicopters INNER JOIN Flights ON Helicopters.number = Flights.helicopter_number INNER JOIN Pilots ON Pilots.helicopter_number = Helicopters.number
)
