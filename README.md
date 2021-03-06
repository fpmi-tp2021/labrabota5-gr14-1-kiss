# AIRWAY

![](https://github.com/fpmi-tp2021/labrabota5-kiss-report/raw/report/data/query-menu.png)

# Description

The project is made for commander of the air squad. It stores the information about helicopters, crew and cruises. The functionality of the project:

- get the total hours for each helicopter after last renovation and the quantity of hours that are left until the new one

- get information about all cruises made by each each helicopter(with specific details about flight)

- get information about all helicopters that have made special cruises(with specific details about flights)

- get information about all helicopters that have made usual cruises(with specific details about the flights)

- get information about helicopters that have the biggest quantity of cruises(with specific abou the crew and the total summ the was earned during flights)

- get info about the have earned the biggest sum(with specific details about their flights)

- get information about the crew or the crew member(with specific details about all flights that were made by crew or person)

# Dependencies

To build and run the program you will need:

- [sqlite3](https://sqlite.org/)
- [chafa](https://github.com/hpjansson/chafa)
- [jpg2ff](http://git.suckless.org/farbfeld/files.html)

[pandoc](https://pandoc.org/) and a tex distriution are required for report generation.

# Installation

Clone the repository with submodules

```
$ git clone --recurse-submodules https://github.com/fpmi-tp2021/labrabota5-gr14-1-kiss.git
```

To install or uninstall the program, run

```
# make install
```

or

```
# make uninstall
```

respectively from the project directory.

# Usage

The program needs a database to operate on.
You can generate an example database from the sql scripts provided in the sql directory.

```
$ make flights.db
```

Specify path to the database file as a single command line argument to the program.

```
$ airway flights.db
```

# Authors

[Herman Yanush](https://github.com/jiffygist)

[Valiantsin Rakots](https://github.com/valikrakots)
