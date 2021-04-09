CREATE TABLE Pilots (
    identification_number int NOT NULL,
    surname varchar(30) NOT NULL,
    position varchar(30) NOT NULL,
    helicopter_number int NOT NULL,
    experience int NOT NULL,
    adress varchar(70) NOT NULL,
    birthdate date NOT NULL,
    CONSTRAINT Pilot_pk PRIMARY KEY (identification_number)
);
