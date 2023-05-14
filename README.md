# Employee Management System

A simple console-based employee management system written in C. The system reads and writes employee information to a CSV file called `EmployeeDB.csv`.

## Features
- Add an employee with their name, employee ID, job title, and salary
- Edit an employee's information by employee ID
- Search for an employee by their name
- Display all employees

## How to Run
1. Clone the repository using `git clone [https://github.com/username/Employee-Management-System-C.git](https://github.com/User2596/Employee-Management-System.git)`
2. Navigate to the project directory.
3. Compile the program using the following command: `gcc -o main main.c`
4. Run the program using `./main`

## Functions
### `loadData()`
This function reads the data from `EmployeeDB.csv` and stores it in the global variable `employees`.

### `saveData()`
This function saves the data in `employees` to `EmployeeDB.csv`.

### `displayEmployees()`
This function displays all employees currently in the system.

### `searchEmployee()`
This function allows the user to search for an employee by their name.

### `addEmployee()`
This function allows the user to add a new employee to the system.

### `editEmployee()`
This function allows the user to edit an existing employee's information by their employee ID.

## Limitations
- The system can only store a maximum of 100 employees.
- The employee information is stored in a single CSV file, which may not be scalable for larger systems.

## License
This project is licensed under the MIT License. See the `LICENSE.md` file for details.
