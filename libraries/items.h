#ifndef ITEMS_H
#define ITEMS_H

typedef enum item_type {
    FOOD,
    KITCHEN_EQUIPMENT,
    APPLIANCE,
    ELECTRONIC_DEVICE
} item_type;

typedef enum material {
    WOOD,
    METAL,
    PLASTIC
} material;

typedef struct item {
    item_type type;
    char *name;
    unsigned int price;
} item;

typedef struct food {
    item_type type;
    char *name;
    unsigned int price;
    unsigned int calories;
    float protein;
    float carbs;
    float fat;
} food;

typedef struct kitchen_equipment {
    item_type type;
    char *name;
    unsigned int price;
    material mat;
} kitchen_equipment;

typedef struct appliance {
    item_type type;
    char *name;
    unsigned int price;
    unsigned int power_consumption_watts;
} appliance;

typedef struct electronic_device {
    item_type type;
    char *name;
    unsigned int price;
} electronic_device;

food *create_food(char *name, unsigned int price, unsigned int calories, float protein, float carbs, float fat);
kitchen_equipment *create_kitchen_equipment(char *name, unsigned int price, material mat);
appliance *create_appliance(char *name, unsigned int price, unsigned int power_consumption_watts);
electronic_device *create_electronic_device(char *name, unsigned int price);

void destroy_food(food *f);
void destroy_kitchen_equipment(kitchen_equipment *k);
void destroy_appliance(appliance *a);
void destroy_electronic_device(electronic_device *e);
void destroy_item(item *i);

#endif