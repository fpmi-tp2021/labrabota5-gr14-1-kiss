CREATE TABLE Flights (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    hours INT NOT NULL,
    cost INT NOT NULL,
    date DATE NOT NULL,
    helicopter_number INT NOT NULL,
    weight REAL(12,3) NOT NULL,
    quantity INT NOT NULL,
    special bool NOT NULL
);
