CREATE TABLE Pilots (
    identification_number INTEGER PRIMERY KEY AUTOINCREMENT,
    surname varchar(30) NOT NULL,
    position varchar(30) NOT NULL,
    helicopter_number int NOT NULL,
    experience int NOT NULL,
    adress varchar(70) NOT NULL,
    birthdate date NOT NULL,
);
