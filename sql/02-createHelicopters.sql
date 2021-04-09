CREATE TABLE Helicopters (
    number INTEGER PRIMARY KEY AUTOINCREMENT,
    brand VARCHAR(30) NOT NULL,
    date DATE NOT NULL,
    capacity REAL(12,3) NOT NULL,
    last_overhaul DATE NOT NULL,
    till_overhaul INT NOT NULL,
    pilot_identification_number INT NOT NULL
);
