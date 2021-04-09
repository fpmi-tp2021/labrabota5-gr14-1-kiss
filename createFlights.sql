CREATE TABLE Flights (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    hours int NOT NULL,
    cost int NOT NULL,
    data date NOT NULL,
    helicopter_number int NOT NULL,
    weight real(12,3) NOT NULL,
    quantity int NOT NULL,
    special bool NOT NULL,
);
