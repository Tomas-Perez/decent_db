#include <stdlib.h>

#include "libraries/malloc_utils.h"
#include "items.h"

food *create_food(char *name, unsigned int price, unsigned int calories, float protein, float carbs, float fat) {
    food *f = malloc_or_die(sizeof(food));
    f->type = FOOD;
    f->name = name;
    f->price = price;
    f->calories = calories;
    f->protein = protein;
    f->carbs = carbs;
    f->fat = fat;
    return f;
}

void destroy_food(food *f) {
    free(f->name);
    free(f);
}

kitchen_equipment *create_kitchen_equipment(char *name, unsigned int price, material mat) {
    kitchen_equipment *k = malloc_or_die(sizeof(kitchen_equipment));
    k->type = KITCHEN_EQUIPMENT;
    k->name = name;
    k->price = price;
    k->mat = mat;
    return k;
}

void destroy_kitchen_equipment(kitchen_equipment *k) {
    free(k->name);
    free(k);
}

appliance *create_appliance(char *name, unsigned int price, unsigned int power_consumption_watts) {
    appliance *a = malloc_or_die(sizeof(appliance));
    a->type = APPLIANCE;
    a->name = name;
    a->price = price;
    a->power_consumption_watts = power_consumption_watts;
    return a;
}

void destroy_appliance(appliance *a) {
    free(a->name);
    free(a);
}

electronic_device *create_electronic_device(char *name, unsigned int price) {
    electronic_device *e = malloc_or_die(sizeof(electronic_device));
    e->type = ELECTRONIC_DEVICE;
    e->name = name;
    e->price = price;
    return e;
}

void destroy_electronic_device(electronic_device *e) {
    free(e->name);
    free(e);
}

void destroy_item(item *i) {
    switch(i->type) {
        case FOOD:
            destroy_food((food*) i);
            break;
        case KITCHEN_EQUIPMENT:
            destroy_kitchen_equipment((kitchen_equipment *) i);
            break;
        case APPLIANCE:
            destroy_appliance((appliance *) i);
            break;
        case ELECTRONIC_DEVICE:
            destroy_electronic_device((electronic_device *) i);
            break;
    }
}