#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Constants for room types and status
#define MAX_ROOMS 100
#define MAX_NAME_LENGTH 50
#define MAX_PHONE_LENGTH 15
#define SINGLE_ROOM 1
#define DOUBLE_ROOM 2
#define SUITE_ROOM 3
#define AVAILABLE 0
#define BOOKED 1
#define CHECKED_IN 2

// Structure to represent a room
typedef struct {
    int roomNumber;
    int roomType; // 1: Single, 2: Double, 3: Suite
    int status;    // 0: Available, 1: Booked, 2: Checked-in
    char guestName[MAX_NAME_LENGTH];
    char guestPhone[MAX_PHONE_LENGTH];
} Room;

// Function to get room type name
char *getRoomTypeName(int roomType) {
    switch (roomType) {
        case SINGLE_ROOM:
            return "Single";
        case DOUBLE_ROOM:
            return "Double";
        case SUITE_ROOM:
            return "Suite";
        default:
            return "Unknown";
    }
}

// Function to get room status name
char *getRoomStatusName(int status) {
    switch (status) {
        case AVAILABLE:
            return "Available";
        case BOOKED:
            return "Booked";
        case CHECKED_IN:
            return "Checked-in";
        default:
            return "Unknown";
    }
}

// Function to initialize rooms
void initializeRooms(Room rooms[], int numRooms) {
    for (int i = 0; i < numRooms; i++) {
        rooms[i].roomNumber = i + 1;
        // Assign room types in a round-robin fashion
        if (i % 3 == 0) {
            rooms[i].roomType = SINGLE_ROOM;
        } else if (i % 3 == 1) {
            rooms[i].roomType = DOUBLE_ROOM;
        } else {
            rooms[i].roomType = SUITE_ROOM;
        }
        rooms[i].status = AVAILABLE;
        strcpy(rooms[i].guestName, "");
        strcpy(rooms[i].guestPhone, "");
    }
}

// Function to display a single room
void displayRoom(Room *room) {
    printf("Room Number: %d\n", room->roomNumber);
    printf("Room Type: %s\n", getRoomTypeName(room->roomType));
    printf("Status: %s\n", getRoomStatusName(room->status));
    if (room->status != AVAILABLE) {
        printf("Guest Name: %s\n", room->guestName);
        printf("Guest Phone: %s\n", room->guestPhone);
    }
    printf("--------------------\n");
}

// Function to display all rooms
void displayAllRooms(Room rooms[], int numRooms) {
    printf("\n--- All Rooms ---\n");
    for (int i = 0; i < numRooms; i++) {
        displayRoom(&rooms[i]);
    }
}

// Function to find a room by number
int findRoom(Room rooms[], int numRooms, int roomNumber) {
    for (int i = 0; i < numRooms; i++) {
        if (rooms[i].roomNumber == roomNumber) {
            return i;
        }
    }
    return -1;
}

// Function to book a room
void bookRoom(Room rooms[], int numRooms) {
    int roomNumber;
    char guestName[MAX_NAME_LENGTH];
    char guestPhone[MAX_PHONE_LENGTH];

    printf("Enter room number to book: ");
    if (scanf("%d", &roomNumber) != 1) {
        printf("Invalid input for room number.\n");
        while (getchar() != '\n');
        return;
    }

    int roomIndex = findRoom(rooms, numRooms, roomNumber);
    if (roomIndex == -1) {
        printf("Room not found.\n");
        return;
    }

    if (rooms[roomIndex].status != AVAILABLE) {
        printf("Room is not available. Status: %s\n", getRoomStatusName(rooms[roomIndex].status));
        return;
    }

    printf("Enter guest name: ");
    if (scanf(" %[^\n]s", guestName) != 1) {
        printf("Invalid input for guest name.\n");
        while (getchar() != '\n');
        return;
    }
    if (strlen(guestName) >= MAX_NAME_LENGTH) {
        printf("Guest name is too long.\n");
        return;
    }

    printf("Enter guest phone number: ");
    if (scanf(" %s", guestPhone) != 1) {
        printf("Invalid input for guest phone number.\n");
        while (getchar() != '\n');
        return;
    }
    if (strlen(guestPhone) >= MAX_PHONE_LENGTH) {
        printf("Guest phone number is too long.\n");
        return;
    }

    rooms[roomIndex].status = BOOKED;
    strcpy(rooms[roomIndex].guestName, guestName);
    strcpy(rooms[roomIndex].guestPhone, guestPhone);
    printf("Room booked successfully.\n");
}

// Function to check in a guest
void checkInGuest(Room rooms[], int numRooms) {
    int roomNumber;
    printf("Enter room number to check in: ");
    if (scanf("%d", &roomNumber) != 1) {
        printf("Invalid input for room number.\n");
        while (getchar() != '\n');
        return;
    }
    int roomIndex = findRoom(rooms, numRooms, roomNumber);
    if (roomIndex == -1) {
        printf("Room not found.\n");
        return;
    }
    if (rooms[roomIndex].status == AVAILABLE) {
        printf("Room is available, cannot check-in.\n");
        return;
    }
    if (rooms[roomIndex].status == CHECKED_IN) {
        printf("Guest already checked in.\n");
        return;
    }
    rooms[roomIndex].status = CHECKED_IN;
    printf("Guest checked in successfully.\n");
}

// Function to check out a guest
void checkOutGuest(Room rooms[], int numRooms) {
    int roomNumber;
    printf("Enter room number to check out: ");
    if (scanf("%d", &roomNumber) != 1) {
        printf("Invalid input for room number.\n");
        while (getchar() != '\n');
        return;
    }
    int roomIndex = findRoom(rooms, numRooms, roomNumber);
    if (roomIndex == -1) {
        printf("Room not found.\n");
        return;
    }
    if (rooms[roomIndex].status != CHECKED_IN) {
        printf("Room is not checked in.\n");
        return;
    }
    rooms[roomIndex].status = AVAILABLE;
    strcpy(rooms[roomIndex].guestName, "");
    strcpy(rooms[roomIndex].guestPhone, "");
    printf("Guest checked out successfully.\n");
}

// Function to display available rooms
void displayAvailableRooms(Room rooms[], int numRooms) {
    printf("\n--- Available Rooms ---\n");
    int found = 0;
    for (int i = 0; i < numRooms; i++) {
        if (rooms[i].status == AVAILABLE) {
            displayRoom(&rooms[i]);
            found = 1;
        }
    }
    if (!found) {
        printf("No available rooms.\n");
    }
}

// 🆕 Function to search guest by name or phone (partial match)
void searchGuest(Room rooms[], int numRooms) {
    char search[MAX_NAME_LENGTH];
    printf("Enter guest name or phone number to search: ");
    scanf(" %[^\n]", search);

    int found = 0;
    for (int i = 0; i < numRooms; i++) {
        if (rooms[i].status != AVAILABLE) {
            if (strstr(rooms[i].guestName, search) != NULL || strstr(rooms[i].guestPhone, search) != NULL) {
                printf("\nGuest found!\n");
                displayRoom(&rooms[i]);
                found = 1;
            }
        }
    }
    if (!found) {
        printf("Guest not found.\n");
    }
}

// Function to display the main menu
void displayMenu() {
    printf("\n--- Hotel Management System Menu ---\n");
    printf("1. Display All Rooms\n");
    printf("2. Display Available Rooms\n");
    printf("3. Book a Room\n");
    printf("4. Check in a Guest\n");
    printf("5. Check out a Guest\n");
    printf("6. Exit\n");
    printf("7. Search Guest by Name or Phone Number\n"); // 🆕 New menu option
    printf("Enter your choice: ");
}

int main() {
    Room rooms[MAX_ROOMS];
    int numRooms = MAX_ROOMS;
    int choice;

    initializeRooms(rooms, numRooms);

    do {
        displayMenu();
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter a number.\n");
            while (getchar() != '\n');
            choice = 0;
            continue;
        }
        switch (choice) {
            case 1:
                displayAllRooms(rooms, numRooms);
                break;
            case 2:
                displayAvailableRooms(rooms, numRooms);
                break;
            case 3:
                bookRoom(rooms, numRooms);
                break;
            case 4:
                checkInGuest(rooms, numRooms);
                break;
            case 5:
                checkOutGuest(rooms, numRooms);
                break;
            case 6:
                printf("Exiting the system.\n");
                break;
            case 7:
                searchGuest(rooms, numRooms);
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 6);

    return 0;
}
