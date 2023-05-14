#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
#define filename "EmployeeDB.csv"
#define MAX_EMPLOYEES 100
#define MAX_NAME_LEN 50
#define MAX_ID_LEN 10
#define MAX_TITLE_LEN 50
#define MAX_SALARY_LEN 10

struct Employee
{
	char name[50];
	char id[15];
	char title[20];
	float salary;
};

// Global variables
struct Employee employees[MAX_EMPLOYEES];
int employeeCount = 0;

// Function to load employee data from the CSV file
void loadData() {
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("No data file found. Starting with an empty database.\n");
        return;
    }
    char line[MAX_NAME_LEN + MAX_ID_LEN + MAX_TITLE_LEN + MAX_SALARY_LEN
		+ 4];
    char *token;
    fgets(line, sizeof(line), fp); //to ignore header line
    while (fgets(line, sizeof(line), fp)) {
        struct Employee employee;
        token = strtok(line, ",");
        strcpy(employee.name, token);
        token = strtok(NULL, ",");
        strcpy(employee.id, token);
        token = strtok(NULL, ",");
        strcpy(employee.title, token);
        token = strtok(NULL, ",");
        employee.salary = atof(token);
        employees[employeeCount] = employee;
        employeeCount++;
    }
    fclose(fp);
}

// Function to save employee data to the CSV file
void saveData() {
    FILE *fp = fopen(filename, "w");
	fseek(fp,0,SEEK_SET);
    if (fp == NULL) {
        printf("Unable to open file for writing.\n");
        return;
    }
    fprintf(fp,"Name,Employee ID,Job Title,Salary\n");
    for (int i = 0; i < employeeCount; i++) {
        fprintf(fp, "%s,%s,%s,%.2f\n",employees[i].name, employees[i].id,
			employees[i].title,	employees[i].salary);
	}
    fclose(fp);
}

// Function to display all employees
void displayEmployees() {
    if (employeeCount == 0) {
        printf("No employees to display.\n");
        return;
    }
    printf("\n--- All Employees ---\n");
    for (int i = 0; i < employeeCount; i++) {
        printf("Name: %s\n", employees[i].name);
        printf("Employee ID: %s\n", employees[i].id);
        printf("Job Title: %s\n", employees[i].title);
        printf("Salary: %.2f\n\n", employees[i].salary);
    }
}

// Function to search for a employee by name
void searchEmployee() {
    if (employeeCount == 0) {
        printf("No employees to search.\n");
        return;
    }
    char searchName[MAX_NAME_LEN];
    printf("Search the Name of the employee: ");
    scanf("%s", searchName);
    int count = 0;
    for (int i = 0; i < employeeCount; i++) {
        if (strstr(employees[i].name, searchName) != NULL) {
            printf("\nResult %d:\n",(count+1));
        	printf("Name: %s\n", employees[i].name);
        	printf("Employee ID: %s\n", employees[i].id);
        	printf("Job Title: %s\n", employees[i].title);
        	printf("Salary: %.2f\n\n", employees[i].salary);
            count++;
            continue;
        }
    }
    if (count == 0) {
        printf("Employee not found.\n");
    }
}

// Function to add a new employee
void addEmployee() {
    if (employeeCount >= MAX_EMPLOYEES) {
        printf("Maximum number of students reached.\n");
        return;
    }
    struct Employee newEmployee;
    gets(newEmployee.name); //to avoid input error
    printf("Enter Name: ");
    gets(newEmployee.name);
    printf("Enter Employee ID: ");
    gets(newEmployee.id);
    printf("Enter Job Title: ");
    gets(newEmployee.title);
    printf("Enter Salary: ");
    scanf("%f", &newEmployee.salary);
    employees[employeeCount] = newEmployee;
    employeeCount++;
    saveData();
    printf("Employee added successfully.\n");
}

// Function to edit a employee by Employee ID
void editEmployee() {
    if (employeeCount == 0) {
        printf("No employees to edit.\n");
        return;
    }
    char employeeID[MAX_ID_LEN];
    gets(employeeID); //to avoid input error
    printf("Enter the Employee ID to edit: ");
    gets(employeeID);
    int found = 0;
    for (int i = 0; i < employeeCount; i++) {
        if (strcmp(employees[i].id, employeeID) == 0) {
            found = 1;
    		printf("Enter Name: ");
    		gets(employees[i].name);
    		printf("Enter Job Title: ");
    		gets(employees[i].title);
    		printf("Enter Salary: ");
    		scanf("%f", &employees[i].salary);
    		for (int j = i; j < employeeCount - 1; j++) {
                employees[j] = employees[j + 1];
            }
            saveData();
            printf("Employee details updated successfully.\n");
            break;
        }
    }
    if (!found) {
        printf("Employee not found.\n");
    }
}

// Function to delete a employee by Employee ID
void deleteEmployee() {
    if (employeeCount == 0) {
        printf("No employees to delete.\n");
        return;
    }
    char employeeID[MAX_ID_LEN];
    gets(employeeID); //to avoid input error
    printf("Enter the Employee ID of the employee to delete: ");
    gets(employeeID);
    int found = 0;
    for (int i = 0; i < employeeCount; i++) {
        if (strcmp(employees[i].id, employeeID) == 0) {
            found = 1;
            for (int j = i; j < employeeCount - 1; j++) {
                employees[j] = employees[j + 1];
            }
            employeeCount--;
            saveData();
            printf("Employee deleted successfully.\n");
            break;
        }
    }
 
    if (!found) {
        printf("Employee not found.\n");
    }
}

int main() {
    loadData();
    int choice;
    do {
    	printf("\n*** Employee Management System ***\n\n");
    	printf("1. Display All Employees\n");
    	printf("2. Search Employee\n");
    	printf("3. Add Employee\n");
    	printf("4. Edit Employee\n");
    	printf("5. Delete Employee\n");
    	printf("6. Exit\n");
    	printf("Enter your choice: ");;
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                displayEmployees();
                break;
            case 2:
                searchEmployee();
                break;
            case 3:
                addEmployee();
                break;
            case 4:
                editEmployee();
                break;
            case 5:
                deleteEmployee();
                break;
            case 6:
                printf("Exiting...\n");
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }
    } while (choice != 6);
    return 0;
}
