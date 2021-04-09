CREATE TABLE Helicopters (
    number int NOT NULL,
    brand varchar(30) NOT NULL,
    date date NOT NULL,
    capacity real(12,3) NOT NULL,
    last_overhaul date NOT NULL,
    till_overhaul int NOT NULL,
    pilot_identification_number int NOT NULL,
    CONSTRAINT Helicopter_pk PRIMARY KEY (number)
);
