#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Define the structure for a node in the linked list
struct Node {
    char student_name[50];
    struct Node* next;
};

// Define a structure to represent a student
struct Student {
    int number;
    char name[50];
    int age;
    struct Student* next;
};

// Define a structure for a student record
struct Record {
    char name[50];
    // Add other fields as needed
};

// Function to add an element to the beginning of the list
void addOddToList(int *list, int *size, int value) {
    // Shift elements to the right to make space for the new element
    for (int i = (*size) - 1; i >= 0; i--) {
        list[i + 1] = list[i];
    }
    // Add the new element at the beginning
    list[0] = value;
    (*size)++;
}

// Function to add an element to the end of the list
void addEvenToList(int *list, int *size, int value) {
    // Add the new element at the end
    list[*size] = value;
    (*size)++;
}

// Function to search records by student name
int searchStudentByName(struct Student list[], int numRecords, const char *name) {
    for (int i = 0; i < numRecords; i++) {
        if (strcmp(list[i].name, name) == 0) {
            // If the names match, return the index of the matching record
            return i;
        }
    }
    // If no match is found, return -1
    return -1;
}

// Function to delete the next node after the node with a given student name
void deleteNextNode(struct Node* head, const char* target_name) {
    struct Node* current = head;

    // Traverse the linked list
    while (current != NULL && current->next != NULL) {
        // Check if the next node's student name matches the target
        if (strcmp(current->student_name, target_name) == 0) {
            struct Node* temp = current->next;

            // Make sure we are not deleting the last node
            if (temp->next != NULL) {
                current->next = temp->next;
                free(temp); // Free the memory of the next node
                printf("Node deleted successfully.\n");
            } else {
                printf("The target node is the last node, cannot delete.\n");
            }
            return; // Node deleted, exit the function
        }
        current = current->next;
    }

    // If the target name is not found, print a message
    printf("Target student name not found in the list.\n");
}

// Function to display all the student information and count them
void displayStudents(struct Student* head) {
    int count = 0;
    while (head != NULL) {
        printf("%d- %s %d %d\n", head->number, head->name, head->age, count + 1);
        head = head->next;
        count++;
    }
    printf("Total students: %d\n", count);
}

// Function to free the memory allocated for the linked list
void freeStudents(struct Student* head) {
    while (head != NULL) {
        struct Student* temp = head;
        head = head->next;
        free(temp);
    }
}

// Compare function for qsort
int compare(const void *a, const void *b) {
    return (*(int*)b - *(int*)a);
}

// Function to print the record with the longest name
void printRecordWithLongestName(struct Record records[], int numRecords) {
    if (numRecords <= 0) {
        printf("No records to check.\n");
        return;
    }

    int longestIndex = 0;
    int maxLength = strlen(records[0].name);

    for (int i = 1; i < numRecords; i++) {
        int currentLength = strlen(records[i].name);
        if (currentLength > maxLength) {
            maxLength = currentLength;
            longestIndex = i;
        }
    }

    printf("The longest name in the list: %s\n", records[longestIndex].name);
    printf("Length: %d\n", maxLength);
}

int main() {
    int list[100];  // Assuming a maximum of 100 elements in the list
    int size = 0;
    int num;

    struct Student* studentList = NULL;

    struct Record records[] = {
        {"Mohanad"},
        {"ahmed"},
        {"mohammed"},
        {"Abdurrahmangazi"},
        // Add more records as needed
    };
    int numRecords = sizeof(records) / sizeof(records[0]);

    struct Node* head = NULL;
    struct Node* second = NULL;
    struct Node* third = NULL;

    head = (struct Node*)malloc(sizeof(struct Node));
    second = (struct Node*)malloc(sizeof(struct Node));
    third = (struct Node*)malloc(sizeof(struct Node));

    strcpy(head->student_name, "Mohanad");
    head->next = second;

    strcpy(second->student_name, "ahmed");
    second->next = third;

    strcpy(third->student_name, "mohammed");
    third->next = NULL;

    printf("Welcome to the Menu-Driven Program\n");
    printf("1. Add number to list (odd/even)\n");
    printf("2. Search for a student by name\n");
    printf("3. Delete a node by student name\n");
    printf("4. Display student information\n");
    printf("5. Print the record with the longest name\n");
    printf("6. Exit\n");

    int choice;
    while (1) {
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter a number: ");
                scanf("%d", &num);



                if (num%2==0) {
                    addEvenToList(list, &size, num);
                } else {
                    addOddToList(list, &size, num);
                }
                break;
            case 2:
                printf("Enter the student name to search: ");
                char nameToSearch[50];
                scanf("%s", nameToSearch);
                int studentIndex = searchStudentByName(studentList, 2, nameToSearch);
                if (studentIndex != -1) {
                    printf("Student found at index %d\n", studentIndex);
                } else {
                    printf("Student not found\n");
                }
                break;
            case 3:
                printf("Enter the student name to delete the next node: ");
                char nameToDelete[50];
                scanf("%s", nameToDelete);
                deleteNextNode(head, nameToDelete);
                break;
            case 4:
                displayStudents(studentList);
                break;
            case 5:
                printRecordWithLongestName(records, numRecords);
                break;
            case 6:
                printf("Exiting the program.\n");
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    // Free the memory allocated for the linked list
    freeStudents(studentList);

    return 0;
}
