#define MAX_CONTACTS 100
#define MAX_LENGTH 100
#include "List.h"

typedef struct StringNode {
    char *value;
    struct StringNode **next;
    int level;
} StringNode;

typedef struct {
    int max_level;
    StringNode **heads;
} StringList;

typedef struct RendezVous {
    char date[11];  // Date au format "AAAA-MM-JJ"
    char description[100];
} RendezVous;

typedef struct AppointmentNode {
    RendezVous rendezVous;   // Détails du rendez-vous
    struct StringNode* next; // Prochain rendez-vous dans la liste
} AppointmentNode;

void calculateInsertionTimes(int maxLevel);
void insert_string_tri(StringList *mylist, StringNode *newNode);
StringNode* searchStringLevels(StringList* mylist, const char* targetName);
void insertStringNode(StringList *mylist, StringNode *newNode);
StringList *createStringList(int n);
void displayStringList(StringList *mylist);

StringNode* search_name_levels(StringList* mylist, const char* targetName);
void add_appointment(StringNode* contact, RendezVous rendezVous);

void displayAppointmentsForContact(StringNode* contact);
void saveAppointmentsToFile(StringList* contactList);
void loadAppointmentsFromFile(StringList* contactList);