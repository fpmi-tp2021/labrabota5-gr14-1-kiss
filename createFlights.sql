CREATE TABLE Flights (
    id int NOT NULL,
    hours int NOT NULL,
    cost int NOT NULL,
    date date NOT NULL,
    helicopter_number int NOT NULL,
    weight real(12,3) NOT NULL,
    quantity int NOT NULL,
    special bool NOT NULL,
    CONSTRAINT Flights_pk PRIMARY KEY (id)
);
