#include <stdio.h>
#include <string.h>

#define MAX 100

// Structure for vehicle details
typedef struct {
    char vehicleNo[20];
    char ownerName[50];
    char vehicleType[20];
} Vehicle;

Vehicle parking[MAX];
int count = 0;

// Function declarations
void loadFromFile();
void saveToFile();
void addVehicle();
void searchVehicle();
void displayVehicles();

int main() {
    int choice;
    loadFromFile();

    while (1) {
        printf("\n====== VEHICLE PARKING MANAGEMENT SYSTEM ======\n");
        printf("1. Add Vehicle Entry\n");
        printf("2. Search Vehicle Details\n");
        printf("3. Display All Vehicles\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addVehicle(); break;
            case 2: searchVehicle(); break;
            case 3: displayVehicles(); break;
            case 4: 
                saveToFile();
                printf("Data saved. Exiting...\n");
                return 0;
            default:
                printf("Invalid choice! Try again.\n");
        }
    }
}

// Load existing vehicle records from file
void loadFromFile() {
    FILE *fp = fopen("parking.txt", "r");
    if (fp == NULL) return;

    while (fscanf(fp, "%s %s %s", 
                  parking[count].vehicleNo, 
                  parking[count].ownerName, 
                  parking[count].vehicleType) != EOF) 
    {
        count++;
    }
    fclose(fp);
}

// Save all vehicle records back to file
void saveToFile() {
    FILE *fp = fopen("parking.txt", "w");
    for (int i = 0; i < count; i++) {
        fprintf(fp, "%s %s %s\n", 
                parking[i].vehicleNo,
                parking[i].ownerName,
                parking[i].vehicleType);
    }
    fclose(fp);
}

// Add new vehicle entry
void addVehicle() {
    if (count >= MAX) {
        printf("Parking full! Cannot add more vehicles.\n");
        return;
    }

    printf("\nEnter vehicle number: ");
    scanf("%s", parking[count].vehicleNo);

    printf("Enter owner name: ");
    scanf("%s", parking[count].ownerName);

    printf("Enter vehicle type (Car/Bike/etc): ");
    scanf("%s", parking[count].vehicleType);

    count++;
    printf("Vehicle added successfully!\n");
}

// Search vehicle by vehicle number
void searchVehicle() {
    char searchNo[20];
    int found = 0;

    printf("\nEnter vehicle number to search: ");
    scanf("%s", searchNo);

    for (int i = 0; i < count; i++) {
        if (strcmp(parking[i].vehicleNo, searchNo) == 0) {
            printf("\nVehicle Found:\n");
            printf("Vehicle No  : %s\n", parking[i].vehicleNo);
            printf("Owner Name  : %s\n", parking[i].ownerName);
            printf("Vehicle Type: %s\n", parking[i].vehicleType);
            found = 1;
            break;
        }
    }
    if (!found)
        printf("Vehicle not found!\n");
}

// Display all parked vehicles
void displayVehicles() {
    if (count == 0) {
        printf("No vehicles parked.\n");
        return;
    }

    printf("\n----- All Parked Vehicles -----\n");
    for (int i = 0; i < count; i++) {
        printf("\nVehicle %d\n", i + 1);
        printf("Vehicle No  : %s\n", parking[i].vehicleNo);
        printf("Owner Name  : %s\n", parking[i].ownerName);
        printf("Vehicle Type: %s\n", parking[i].vehicleType);
    }
}
