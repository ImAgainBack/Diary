#include "List.h"
#include "timer.h"
#include <stdio.h>
#include <stdlib.h>
#include "partie3.h"
#include <ctype.h>
#include <string.h>



int main() {
  StringList *contactList = createStringList(5);
  int choice;
  char searchName[MAX_NAME_LENGTH];
  StringNode *foundContact;
  RendezVous rendezVous;
  do {
            printf("\nMenu:\n");
            printf("1. Search for a contact\n");
            printf("2. Display the appointments of a contact\n");
            printf("3. Create a contact\n");
            printf("4. Create an appointment for a contact\n");
            printf("5. Delete an appointment\n");
            printf("6. Save the file of all appointments\n");
            printf("7. Loading an appointment file\n");
            printf("8. Provide the calculation times for inserting a new contact\n");
            printf("0. Quitter\n");

            printf("Choix : ");
            scanf("%d", &choice);

            switch (choice) {
                case 1:
                  printf("Name of contact to look for : ");
                  scanf("%99s", searchName);

                  foundContact = searchStringLevels(contactList, searchName);
                  if (foundContact != NULL) {
                      printf("Contact '%s' found \n", searchName);
                  } else {
                      printf("Contact not found.\n");
                  }
                    break;

                case 2:
                  printf("Name of contact: ");
                  scanf("%s", searchName);

                  StringNode* ctct = search_name_levels(contactList, searchName);
                  if (ctct != NULL) {
                      displayAppointmentsForContact(ctct);
                  } else {
                      printf("Contact not found.\n");
                  }
                    break;

                case 3:
                  printf("Name of new contact : ");
                  char searchName[MAX_NAME_LENGTH];
                  scanf("%99s", searchName);

                  StringNode *newNode = (StringNode *)malloc(sizeof(StringNode));
                  newNode->value = strdup(searchName);
                  newNode->level = 0;
                  newNode->next = NULL;

                  insert_string_tri(contactList, newNode);
                  printf("Contact added with success.\n");
                  break;

              case 4:
                printf("Name of contact : ");
                scanf("%99s", searchName);
                StringNode* contact = search_name_levels(contactList, searchName);

                if (contact != NULL) {
                    RendezVous rendezVous;
                    printf("Date of appointment (format AAAA-MM-JJ) : ");
                    scanf("%10s", rendezVous.date);

                    printf("Description of appointment : ");
                    scanf("%99s", rendezVous.description);

                    add_appointment(contact, rendezVous);
                } else {
                    printf("Contact not found.\n");
                }
                break;


                case 5:
                  printf("Name of contact: ");
                  scanf("%s", searchName);

                  StringNode* contactToDelete = search_name_levels(contactList, searchName);
                  if (contactToDelete != NULL) {
                      deleteAppointment(contactToDelete);
                  } else {
                      printf("Contact not found.\n");
                  }
                  break;

                case 6:
                  saveAppointmentsToFile(contactList);
                  printf("Appointments saved to file.\n");
                  break;

                case 7:
                  loadAppointmentsFromFile(contactList);
                  printf("Appointments loaded from file.\n");
                  break;

                case 8: 
                  printf("Enter the maximum level: ");
                  int maxlevl;
                  if (scanf("%d", &maxlevl) != 1) {
                      printf("Invalid input. Please enter a valid integer for the maximum level.\n");
                      break;
                  }

                  printf("Estimated insertion time for max level %d: ", maxlevl);
                  startTimer();
                  calculateInsertionTimes(maxlevl);
                  stopTimer();
                  displayTime();
                  break;

                case 0:
                    printf("End of program.\n");
                    break;

                default:
                    printf("Invalid choice.\n");
            }
        } while (choice != 0);
    return 0;
}