#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define NAME_LEN 16
#define PHONE_NUM_LEN 16

typedef struct Contact {
    char first_name[NAME_LEN];
    char second_name[NAME_LEN];
    char phone_number[PHONE_NUM_LEN];
} Contact;

void print_contact(Contact* contact) {
    printf("%-16s %-16s: %-16s\n", contact->first_name, contact->second_name, contact->phone_number);
}

Contact* create_contact(char* first_name, char* second_name, char* phone_number) {
    Contact* c = (Contact*)malloc(sizeof(Contact));
    strcpy(c->first_name, first_name);
    strcpy(c->second_name, second_name);
    strcpy(c->phone_number, phone_number);
    return c;
}

void delete_contact(Contact** book, int* size, int index) {
    free(book[index]);
    for (int i = index; i < (*size) - 1; i++) {
        book[i] = book[i + 1];
    }
    (*size)--;
}

int menu() {
    printf("\nMenu: 1) Add Friend; 2) Delete Friend; 3) Show phone book; 4) Find Phone Number; 5) Randomly Call Friend; 6) Delete All Friends; 7) Sort by First Name; 8) Sort by Last Name; 9) Exit\n");
    int r;
    scanf("%d", &r);
    getchar(); // read the newline character
    return r;
}

void safe_read(char* buffer, unsigned int buffer_size) {
    fgets(buffer, buffer_size, stdin);
    if (buffer[strlen(buffer) - 1] == '\n') {
        buffer[strlen(buffer) - 1] = '\0';
    }
}

void read_name(char* first_name, char* second_name) {
    printf("First name: ");
    safe_read(first_name, NAME_LEN);
    printf("Second name: ");
    safe_read(second_name, NAME_LEN);
}

void read_phone_number(char* phone_number) {
    printf("Phone number: ");
    safe_read(phone_number, PHONE_NUM_LEN);
}

int compare_contacts(const void* a, const void* b) {
    Contact* contactA = *(Contact**)a;
    Contact* contactB = *(Contact**)b;
    return strcmp(contactA->first_name, contactB->first_name);
}

int compare_contacts_last_name(const void* a, const void* b) {
    Contact* contactA = *(Contact**)a;
    Contact* contactB = *(Contact**)b;
    return strcmp(contactA->second_name, contactB->second_name);
}

Contact* find_contact_by_name(Contact** book, int size, const char* first_name, const char* second_name) {
    for (int i = 0; i < size; i++) {
        if (strcmp(book[i]->first_name, first_name) == 0 && strcmp(book[i]->second_name, second_name) == 0) {
            return book[i];
        }
    }
    return NULL;
}

Contact* randomly_select_friend(Contact** book, int size) {
    if (size == 0) {
        return NULL;
    }
    int randomIndex = rand() % size;
    return book[randomIndex];
}

void save_to_file(Contact** book, int size) {
    FILE* file = fopen("phonebook.dat", "wb");
    if (file == NULL) {
        printf("Failed to open the file for writing.\n");
        return;
    }
    fwrite(&size, sizeof(int), 1, file);
    for (int i = 0; i < size; i++) {
        fwrite(book[i], sizeof(Contact), 1, file);
    }
    fclose(file);
}

void load_from_file(Contact*** book, int* size) {
    FILE* file = fopen("phonebook.dat", "rb");
    if (file == NULL) {
        printf("No saved phone book data found.\n");
        return;
    }
    fread(size, sizeof(int), 1, file);
    *book = (Contact**)malloc(*size * sizeof(Contact*));
    for (int i = 0; i < *size; i++) {
        (*book)[i] = (Contact*)malloc(sizeof(Contact));
        fread((*book)[i], sizeof(Contact), 1, file);
    }
    fclose(file);
}

int main() {
    int option;
    char first_name[NAME_LEN];
    char second_name[NAME_LEN];
    char phone_number[PHONE_NUM_LEN];
    Contact** book = NULL;
    int size = 0;
    int capacity = 0;

    load_from_file(&book, &size);

    for (;;) {
        option = menu();
        switch (option) {
            case 1:
                read_name(first_name, second_name);
                read_phone_number(phone_number);
                Contact* contact = create_contact(first_name, second_name, phone_number);
                print_contact(contact);
                if (size == capacity) {
                    int extend = 10;
                    capacity += extend;
                    book = (Contact**)realloc(book, capacity * sizeof(Contact*));
                }
                book[size] = contact;
                size += 1;
                break;

            case 2:
                read_name(first_name, second_name);
                int i;
                for (i = 0; i < size; i++) {
                    if (strcmp(book[i]->first_name, first_name) == 0 && strcmp(book[i]->second_name, second_name) == 0) {
                        delete_contact(book, &size, i);
                        break;
                    }
                }
                if (i == size) {
                    printf("Contact not found.\n");
                }
                break;

            case 3:
                printf("Contacts:\n");
                for (int i = 0; i < size; i++) {
                    if (book[i] != NULL) {
                        print_contact(book[i]);
                    }
                }
                break;

            case 4:
                read_name(first_name, second_name);
                Contact* foundContact = find_contact_by_name(book, size, first_name, second_name);
                if (foundContact != NULL) {
                    printf("Phone number: %s\n", foundContact->phone_number);
                } else {
                    printf("Contact not found.\n");
                }
                break;

            case 5:
                Contact* selectedFriend = randomly_select_friend(book, size);
                if (selectedFriend != NULL) {
                    printf("Calling a friend: ");
                    print_contact(selectedFriend);
                } else {
                    printf("No friends to call.\n");
                }
                break;

            case 6:
                for (int i = 0; i < size; i++) {
                    if (book[i] != NULL) {
                        free(book[i]);
                    }
                }
                free(book);
                size = 0;
                capacity = 0;
                book = NULL;
                break;

            case 7:
                qsort(book, size, sizeof(Contact*), compare_contacts);
                break;

            case 8:
                qsort(book, size, sizeof(Contact*), compare_contacts_last_name);
                break;

            case 9:
                save_to_file(book, size);
                for (int i = 0; i < size; i++) {
                    if (book[i] != NULL) {
                        free(book[i]);
                    }
                }
                free(book);
                return 0;

            default:
                printf("Invalid input.\n");
                break;
        }
    }

    return 0;
}
