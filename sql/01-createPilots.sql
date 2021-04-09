CREATE TABLE Pilots (
    identification_number INTEGER PRIMARY KEY AUTOINCREMENT,
    surname VARCHAR(30) NOT NULL,
    position VARCHAR(30) NOT NULL,
    helicopter_number INT NOT NULL,
    experience INT NOT NULL,
    adress VARCHAR(70) NOT NULL,
    birthDATE DATE NOT NULL
);
