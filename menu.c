#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "libraries/malloc_utils.h"
#include "libraries/list.h"
#include "libraries/sort_list.h"
#include "libraries/items.h"
#include "libraries/print_items.h"

#include "list_extras.h"
#include "save_list.h"
#include "save_items.h"
#include "credentials.h"

#include "menu.h"

#define BUF_SIZE 50
#define ITEM_NAME_BUF_SIZE 200

#define HEADER "\
  _____                      _   _____  ____  \n\
 |  __ \\                    | | |  __ \\|  _ \\ \n\
 | |  | | ___  ___ ___ _ __ | |_| |  | | |_) |\n\
 | |  | |/ _ \\/ __/ _ \\ '_ \\| __| |  | |  _ < \n\
 | |__| |  __/ (_|  __/ | | | |_| |__| | |_) |\n\
 |_____/ \\___|\\___\\___|_| |_|\\__|_____/|____/\n"


int get_option() {
    printf("Select an option: ");
    char buffer[BUF_SIZE];
    int option;
    fgets(buffer, sizeof(buffer), stdin);
    if (1 == sscanf(buffer, "%d", &option)) {
        return option;
    } else {
        return -1;
    }
}

unsigned int get_uint() {
    char buffer[BUF_SIZE];
    unsigned int n;
    while (1) {
        fgets(buffer, sizeof(buffer), stdin);
        if (1 == sscanf(buffer, "%u", &n)) {
            return n;
        }
        printf("Invalid value. Try again: ");
    }
}

float get_float() {
    char buffer[BUF_SIZE];
    float n;
    while (1) {
        fgets(buffer, sizeof(buffer), stdin);
        if (1 == sscanf(buffer, "%f", &n)) {
            return n;
        }
        printf("Invalid value. Try again: ");
    }
}

int get_yes_no() {
    char buffer[BUF_SIZE];
    char y_n;
    fgets(buffer, sizeof(buffer), stdin);
    if (1 == sscanf(buffer, "%c", &y_n)) {
        if (y_n != 'y' && y_n != 'Y') {
            return 0;
        } else {
            return 1;
        }
    } else {
        fprintf(stderr, "Error reading from stdin\n");
        exit(-1);
    }
}

credentials *find_user_by_name(const char *username, list *creds) {
    node *curr = creds->head;
    while(curr) {
        credentials *cred = curr->data;
        if (!strcmp(cred->username, username)) {
            return cred;
        }
        curr = curr->next;
    }
    return NULL;
}

credentials *find_by_login(const char *username, const char *password, list *creds) {
    credentials *cred = find_user_by_name(username, creds);
    if (!cred || strcmp(cred->password, password)) return NULL;
    return cred;
}

credentials *login(list *creds) {
    char username[BUF_SIZE];
    char password[BUF_SIZE];
    credentials *user = NULL;
    do {
        printf("Username: ");
        fgets(username, sizeof(username), stdin);
        username[strcspn(username, "\n")] = '\0';
        printf("Password: ");
        fgets(password, sizeof(password), stdin);
        password[strcspn(password, "\n")] = '\0';
        user = find_by_login(username, password, creds);
        if (!user) {
            printf("Wrong username or password. Try again? (Y/n)\n");
            if (!get_yes_no()) {
                return NULL;
            }
        }
    } while (!user);
    return user;
}

void create_user(program_state *state) {
    char username[BUF_SIZE];
    char password[BUF_SIZE];
    credentials *prev_user = NULL;
    do {
        if (prev_user) {
            printf("Username already exists. Try again? (Y/n)\n");
            if (!get_yes_no()) {
                return;
            }
        }
        printf("Username: ");
        fgets(username, sizeof(username), stdin);
        username[strcspn(username, "\n")] = '\0';
        prev_user = find_user_by_name(username, state->saved_credentials);
    } while (prev_user);
    
    printf("Password: ");
    fgets(password, sizeof(password), stdin);
    password[strcspn(password, "\n")] = '\0';

    credentials *cred = create_credentials(state->u_state.user_id_gen++, username, password);
    add_last(state->saved_credentials, cred);
}

void print_items(list *items) {
    unsigned int idx = 0;
    node *curr = items->head;
    while(curr) {
        int idx_str_len = snprintf(NULL, 0, "%d", idx);
        printf(
            "-------------------------------------------\n"
            "| # %0*d                                  |\n"
            "-------------------------------------------\n",
            5 - idx_str_len,
            idx + 1
        );
        printf("\n");
        print_item((item *) curr->data);
        printf("\n");
        curr = curr->next;
        idx++;
    }
}

int ascending_by_name(void *a, void *b) {
    item *item_a = (item *)a;
    item *item_b = (item *)b;
    return strcmp(item_a->name, item_b->name);
}

int descending_by_name(void *a, void *b) {
    item *item_a = (item *)a;
    item *item_b = (item *)b;
    return strcmp(item_b->name, item_a->name);
}

int ascending_by_price(void *a, void *b) {
    item *item_a = (item *)a;
    item *item_b = (item *)b;
    return item_a->price - item_b->price;
}

int descending_by_price(void *a, void *b) {
    item *item_a = (item *)a;
    item *item_b = (item *)b;
    return item_b->price - item_a->price;
}

int ascending_by_type(void *a, void *b) {
    item *item_a = (item *)a;
    item *item_b = (item *)b;
    return item_a->type - item_b->type;
}

int descending_by_type(void *a, void *b) {
    item *item_a = (item *)a;
    item *item_b = (item *)b;
    return item_b->type - item_a->type;
}

void sort_menu(list *items) {
    while (1) {
        printf("1. Ascending by name\n");
        printf("2. Ascending by price\n");
        printf("3. Ascending by type\n");
        printf("4. Descending by name\n");
        printf("5. Descending by price\n");
        printf("6. Descending by type\n");
        printf("0. Back\n");
        printf("\n");
        int opt = get_option();
        switch(opt) {
            case 1:
                sort(items, &ascending_by_name);
                print_items(items);
                return;
            case 2:
                sort(items, &ascending_by_price);
                print_items(items);
                return;
            case 3:
                sort(items, &ascending_by_type);
                print_items(items);
                return;
            case 4:
                sort(items, &descending_by_name);
                print_items(items);
                return;
            case 5:
                sort(items, &descending_by_price);
                print_items(items);
                return;
            case 6:
                sort(items, &descending_by_type);
                print_items(items);
                return;
            case 0:
                return;
            default:
                printf("Invalid option. Try again\n");
                break;
        }
    }
}

void add_food_menu(list *items) {
    printf("ADDING FOOD\n");
    printf("Enter name: ");
    char name[ITEM_NAME_BUF_SIZE];
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = '\0';
    printf("Enter price: ");
    unsigned int price = get_uint();
    printf("Enter calories: ");
    unsigned int calories = get_uint();
    printf("Enter protein: ");
    float protein = get_float();
    printf("Enter carbs: ");
    float carbs = get_float();
    printf("Enter fat: ");
    float fat = get_float();

    food *f = create_food(strdup(name), price, calories, protein, carbs, fat);
    printf("Created food:\n");
    print_food(f);
    printf("Add? (Y/n)\n");

    if (!get_yes_no()) {
        printf("Operation cancelled\n");
        destroy_food(f);
        return;
    }

    add_last(items, f);
}

void add_kitchen_equipment_menu(list *items) {
    printf("ADDING KITCHEN EQUIPMENT\n");
    printf("Enter name: ");
    char name[ITEM_NAME_BUF_SIZE];
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = '\0';
    printf("Enter price: ");
    unsigned int price = get_uint();
    material mat;
    int run = 0;
    do {
        run = 0;
        printf("1. Wood\n");
        printf("2. Metal\n");
        printf("3. Plastic\n");
        int opt = get_option();
        switch(opt) {
            case 1:
                mat = WOOD;
                break;
            case 2:
                mat = METAL;
                break;
            case 3:
                mat = PLASTIC;
                break;
            default:
                printf("Invalid option. Try again\n");
                run = 1;
                break;
        }
    } while (run);

    kitchen_equipment *k = create_kitchen_equipment(strdup(name), price, mat);
    printf("Created kitchen equipment:\n");
    print_kitchen_equipment(k);
    printf("Add? (Y/n)\n");

    if (!get_yes_no()) {
        printf("Operation cancelled\n");
        destroy_kitchen_equipment(k);
        return;
    }

    add_last(items, k);
}

void add_appliance_menu(list *items) {
    printf("ADDING APPLIANCE\n");
    printf("Enter name: ");
    char name[ITEM_NAME_BUF_SIZE];
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = '\0';
    printf("Enter price: ");
    unsigned int price = get_uint();
    printf("Enter power consumption: ");
    unsigned int power_consumption_watts = get_uint();

    appliance *a = create_appliance(strdup(name), price, power_consumption_watts);
    printf("Created appliance:\n");
    print_appliance(a);
    printf("Add? (Y/n)\n");

    if (!get_yes_no()) {
        printf("Operation cancelled\n");
        destroy_appliance(a);
        return;
    }
    
    add_last(items, a);
}

void add_electronic_device_menu(list *items) {
    printf("ADDING ELECTRONIC DEVICE\n");
    printf("Enter name: ");
    char name[ITEM_NAME_BUF_SIZE];
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = '\0';
    printf("Enter price: ");
    unsigned int price = get_uint();

    electronic_device *e = create_electronic_device(strdup(name), price);
    printf("Created electronic device:\n");
    print_electronic_device(e);
    printf("Add? (Y/n)\n");

    if (!get_yes_no()) {
        printf("Operation cancelled\n");
        destroy_electronic_device(e);
        return;
    }
    
    add_last(items, e);
}

void add_item_menu(list *items) {
    while (1) {
        printf("1. Add food\n");
        printf("2. Add kitchen equipment\n");
        printf("3. Add appliance\n");
        printf("4. Add electronic device\n");
        printf("0. Back\n");
        printf("\n");
        int opt = get_option();
        switch(opt) {
            case 1:
                add_food_menu(items);
                break;
            case 2:
                add_kitchen_equipment_menu(items);
                break;
            case 3:
                add_appliance_menu(items);
                break;
            case 4:
                add_electronic_device_menu(items);
                break;
            case 0:
                return;
            default:
                printf("Invalid option. Try again\n");
                break;
        }
    }
}

void remove_item_menu(list *items) {
    printf("REMOVING ITEM\n");
    printf("Enter name to search: ");
    char name[ITEM_NAME_BUF_SIZE];
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = '\0';

    int idx = 0;
    node *curr = items->head;
    item *i = NULL;
    while (curr) {
        idx++;
        i = curr->data;
        if (strstr(i->name, name)) {
            break;
        }
        curr = curr->next;
    }
    if (curr) {
        printf("Item found: \n");
        print_item((item *) curr->data);
        printf("Delete? (Y/n)\n");
        if (!get_yes_no()) {
            printf("Operation cancelled\n");
        } else {
            void *it;
            remove_element(items, idx, &it);
            destroy_item((item *) it);
            printf("Item removed\n");
        }
    } else {
        printf("No item found\n");
    }
}

int main_menu(program_state *state) {
    list *items = state->items;
    printf("===========================================\n");
    printf("Welcome %s!\n", state->current_user->username);
    printf("===========================================\n");
    printf("\n");
    while (1) {
        printf("1. View items\n");
        printf("2. Sort items\n");
        printf("3. Add item\n");
        printf("4. Remove item\n");
        printf("9. Logout\n");
        printf("0. Exit\n");
        printf("\n");
        int opt = get_option();
        switch(opt) {
            case 1:
                print_items(items);
                break;
            case 2:
                sort_menu(items);
                break;
            case 3:
                add_item_menu(items);
                break;
            case 4:
                remove_item_menu(items);
                break;
            case 9:
                printf("Are you sure you want to logout? (Y/n)\n");
                if (get_yes_no()) {
                    state->u_state.current_user_id = -1;
                    state->current_user = NULL;
                    return 1;
                }
                break;
            case 0:
                printf("Are you sure you want to exit? (Y/n)\n");
                if (get_yes_no()) {
                    return 0;
                }
                break;
            default:
                printf("Invalid option. Try again\n");
                break;
        }
    }
}

void start_menu(program_state *state) {
    while(1) {
        printf("%s\n", HEADER);
        if (state->current_user) {
            int should_logout = main_menu(state);
            if (should_logout) continue;
            else return;
        }
        printf("1. Login\n");
        printf("2. Register\n");
        printf("0. Exit\n");
        printf("\n");
        int opt = get_option();
        switch (opt) {
            case 1: {
                credentials *user = login(state->saved_credentials);
                if (user) {
                    state->current_user = user;
                    state->u_state.current_user_id = user->user_id;
                    int should_logout = main_menu(state);
                    if (!should_logout) return;
                }
                break;
            }
            case 2:
                create_user(state);
                break;
            case 0:
                return;
            default:
                printf("Invalid option. Try again\n");
                break;
        }
    }
    
}