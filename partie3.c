
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "List.h"
#include "cell.h"
#include "partie3.h"
#include "timer.h"
#define MAX_PURPOSE_LENGTH 100

void insert_string_tri(StringList *mylist, StringNode *newNode) {
    for (int i = 0; i <= newNode->level; ++i) {
        StringNode *current = mylist->heads[i];
        StringNode *previous = NULL;

        while ((current != NULL) && (strcmp(newNode->value, current->value) > 0)) {
            previous = current;
            current = current->next;
        }

        newNode->next = current;
        if (previous != NULL) {
            previous->next = newNode;
        } else {
            mylist->heads[i] = newNode;
        }
    }
}


StringNode* searchStringLevels(StringList* mylist, const char* targetName) {
    int max_level = mylist->max_level;

    for (int i = max_level; i >= 0; --i) {
        StringNode* current = mylist->heads[i];

        while (current != NULL && strcmp(current->value, targetName) < 0) {
            current = current->next[i];
        }

        if (current != NULL && strcmp(current->value, targetName) == 0) {
            return current;
        }
    }
    return NULL;
}

void insertStringNode(StringList *mylist, StringNode *newNode) {
    for (int i = 0; i <= newNode->level; ++i) {
        StringNode *t1_node = mylist->heads[i];
        StringNode *t2_node = NULL;

        while ((t1_node != NULL) && (strcmp(newNode->value, t1_node->value) > 0)) {
            t2_node = t1_node;
            t1_node = t1_node->next[i];
        }

        newNode->next[i] = t1_node;
        if (t2_node != NULL) {
            t2_node->next[i] = newNode;
        } else {
            mylist->heads[i] = newNode;
        }
    }
}
StringList *createStringList(int n) {
    StringList *mylist = (StringList *)malloc(sizeof(StringList));
    mylist->max_level = n;
    mylist->heads = (StringNode **)calloc(n + 1, sizeof(StringNode *));

    for (int level = 0; level <= n; level++) {
        mylist->heads[level] = NULL;
    }

    return mylist;
}


StringNode* search_name_levels(StringList* mylist, const char* targetName) {
    if (mylist->max_level == 1) {
        StringNode* current = mylist->heads[0];

        if (strcmp(current->value, targetName) == 0) {
            printf("Contact '%s' found\n", targetName);
            return current;
        }
    } else {
        int max_level = mylist->max_level;

        for (int i = max_level - 1; i >= 0; --i) {
            StringNode* current = mylist->heads[i];

            while (current != NULL && strcmp(current->value, targetName) < 0) {
                current = current->next[i];
            }

            if (current != NULL && strcmp(current->value, targetName) == 0) {

                return current;
            }
        }
    }

    printf("Contact '%s' not found\n", targetName);
    return NULL;
}

void displayStringList(StringList *mylist) {
    for (int i = mylist->max_level; i >= 0; i--) {
        StringNode *current = &(mylist->heads[i]);
        printf("Level %d: ", i);
        while (current != NULL) {
            if (current->value != NULL) {
                printf("%s -> ", current->value);
            }
            current = current->next;
        }
        printf("NULL\n");
    }
}

void add_appointment(StringNode* contact, RendezVous rendezVous) {
    // Création d'un nouvel AppointmentNode pour le rendez-vous
    AppointmentNode* newAppointment = (AppointmentNode*)malloc(sizeof(AppointmentNode));
    if (newAppointment == NULL) {
        printf("Eroor of memory allocation\n");
        return;
    }

    // Attribution des détails du rendez-vous
    newAppointment->rendezVous = rendezVous;
    newAppointment->next = NULL; // Initialisation du prochain rendez-vous à NULL

    // Ajout du rendez-vous à la liste des rendez-vous du contact
    AppointmentNode* current = (AppointmentNode*)contact->next;
    if (current == NULL) {
        // Si la liste des rendez-vous est vide, on ajoute le nouveau rendez-vous directement
        contact->next = (StringNode*)newAppointment;
    } else {
        // Sinon, on parcourt la liste jusqu'à la fin pour ajouter le rendez-vous
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newAppointment;
    }

    printf("Appointment added : \nDate : %s\nDescription : %s\n", rendezVous.date, rendezVous.description);
}




void displayAppointmentsForContact(StringNode* contact) {
    if (contact->next == NULL) {
        printf("No appointments for this contact.\n");
        return;
    }

    AppointmentNode* appointments = (AppointmentNode*)contact->next;
    printf("Appointments for contact '%s':\n", contact->value);

    while (appointments != NULL) {
        printf("Date: %s\n", appointments->rendezVous.date);
        printf("Description: %s\n\n", appointments->rendezVous.description);
        appointments = appointments->next;
    }
}

void deleteAppointment(StringNode* contact) {
    if (contact->next == NULL) {
        printf("No appointments for this contact.\n");
        return;
    }

    printf("Enter the date of the appointment to delete: ");
    char dateToDelete[11];
    scanf("%10s", dateToDelete);

    AppointmentNode* appointments = (AppointmentNode*)contact->next;
    AppointmentNode* prev = NULL;

    while (appointments != NULL) {
        if (strcmp(appointments->rendezVous.date, dateToDelete) == 0) {
            if (prev == NULL) {
                contact->next = appointments->next;
            } else {
                prev->next = appointments->next;
            }

            free(appointments);
            printf("Appointment deleted successfully.\n");
            return;
        }

        prev = appointments;
        appointments = appointments->next;
    }

    printf("Appointment not found.\n");
}

void saveAppointmentsToFile(StringList* contactList) {
    FILE* file = fopen("appointments.txt", "w");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    for (int i = contactList->max_level; i >= 0; --i) {
        StringNode* current = contactList->heads[i];

        while (current != NULL) {
            AppointmentNode* appointments = (AppointmentNode*)current->next;

            while (appointments != NULL) {
                fprintf(file, "%s %s %s\n", current->value, appointments->rendezVous.date, appointments->rendezVous.description);
                appointments = (AppointmentNode*)appointments->next;
            }

            current = current->next[i];
        }
    }

    fclose(file);
}


void loadAppointmentsFromFile(StringList* contactList) {
    FILE* file = fopen("appointments.txt", "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    char contactName[MAX_NAME_LENGTH];
    char date[11];
    char description[MAX_PURPOSE_LENGTH];

    while (fscanf(file, "%s %s %s", contactName, date, description) != EOF) {
        // Find the contact
        StringNode* contact = search_name_levels(contactList, contactName);

        if (contact != NULL) {
            // Create an appointment node and populate it
            AppointmentNode* newAppointment = (AppointmentNode*)malloc(sizeof(AppointmentNode));
            if (newAppointment == NULL) {
                printf("Memory allocation error\n");
                return;
            }

            strcpy(newAppointment->rendezVous.date, date);
            strcpy(newAppointment->rendezVous.description, description);
            newAppointment->next = NULL;

            // Insert the appointment node into the contact's appointment list
            if (contact->next == NULL) {
                contact->next = (struct StringNode*)newAppointment;
            } else {
                StringNode* current = contact->next;
                while (current->next != NULL) {
                    current = current->next;
                }
                current->next = (struct StringNode*)newAppointment;
            }
        }
    }

    fclose(file);
}

void calculateInsertionTimes(int maxLevel) {
    startTimer(); // Start the timer before insertion

    // Simulate insertion for different levels
    for (int i = 0; i <= maxLevel; ++i) {
        StringList *contactList = createStringList(i); // Create a contact list with different maxLevel values
        for (int j = 0; j < 10; ++j) {
            // Simulate adding 1000 contacts
            char contactName[MAX_NAME_LENGTH];
            sprintf(contactName, "Contact_%d", j);
            StringNode *newNode = (StringNode *)malloc(sizeof(StringNode));
            newNode->value = strdup(contactName);
            newNode->level = rand() % (i + 1);
            newNode->next = NULL;

            insert_string_tri(contactList, newNode);
        }
        displayTime(); // Display the time taken for insertion for each level
    }
    stopTimer(); // Stop the timer after insertion
}
