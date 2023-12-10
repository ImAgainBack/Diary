#include "List.h"
#include "timer.h"
#include <stdio.h>
#include <stdlib.h>
#include "partie3.h"
#include <ctype.h>
#include <string.h>



int main() {
  int test;
  printf("Would you like to test parts 1 and 2 (1/2) or part 3 (3) of the project ? ");
  scanf("%d", &test);
  while(test==1 || test == 2){
      int choice;
      t_sk_list *mylist = NULL;

      do {
            printf("\nMenu:\n");
            printf("1. Create simple list\n");
            printf("2. Display list\n");
            printf("3. Display aligned list\n");
            printf("4. Create list with 2^n - 1 cells\n");
            printf("5. Search level 0\n");
            printf("6. Search all levels\n");
            printf("7. Exit\n");
            printf("Enter your choice: ");
            scanf("%d", &choice);

            switch (choice) {
                case 1:
                    if (mylist != NULL) {
                        destroy_list(mylist);
                    }
                    int maxLevel;
                    int lvl;
                    int x, y;
                    printf("Enter maximum level: ");
                    scanf("%d", &maxLevel);
                    mylist = create_list(maxLevel);
                    printf("Add at least 2 different values : ");
                    printf("\nPlease put a value, then a level : ");
                    scanf("%d %d", &x ,&lvl);
                    t_sk_cell * cell1 = create_cell(x, lvl);
                    insert_tri(mylist, cell1);
                    printf("x added successfully");
                    printf("\nPlease put a value, then a level : ");
                    scanf("%d %d", &y ,&lvl);
                    t_sk_cell * cell2 = create_cell(y, lvl);
                    insert_tri(mylist, cell2);
                    printf("y added successfully");
                    break;
                case 2:
                    if (mylist != NULL) {
                        display_list(mylist);
                    } else {
                        printf("List is empty. Please create a list first.\n");
                    }
                    break;
                case 3:
                  if (mylist != NULL) {
                      display_aligned_list(mylist);
                  } else {
                      printf("List is empty. Please create a list first.\n");
                  }
                    break;
                case 4:
                  if (mylist != NULL) {
                    destroy_list(mylist);
                  }
                  int n;
                  printf("Enter n for 2^n - 1 : ");
                  scanf("%d", &n);
                  mylist = Createlist2(n);
                
                  break;
                case 5:
                if (mylist != NULL) {
                    int value;
                    printf("Enter value to search in level 0: ");
                    scanf("%d", &value);
                    search_level0(mylist, value);
                } else {
                    printf("List is empty. Please create a list first.\n");
                }
                  break;
                case 6:
                    if (mylist != NULL) {
                        int value;
                        printf("Enter value to search in all levels: ");
                        scanf("%d", &value);
                        search_all_levels(mylist, value);
                    } else {
                        printf("List is empty. Please create a list first.\n");
                    }
                    break;
                case 7:
                    if (mylist != NULL) {
                        destroy_list(mylist);
                    }
                    printf("Exiting...\n");
                    break;
                default:
                    printf("Invalid choice. Please enter a valid option.\n");
            }
        } while (choice != 7);
      printf("\nDo you want to test part 3 ? (3) ");
      scanf("%d", &test);
      
    }
  while(test == 3){
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
    
                printf("Choice : ");
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
    printf("\nDo you want to test part 1 and 2 ? (1/2) ");
    scanf("%d", &test);
    }
  return 0;
}
