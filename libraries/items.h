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

// Creates a "food" object.
// Note: The object proceeds to own the given "name" parameter.
food *create_food(char *name, unsigned int price, unsigned int calories, float protein, float carbs, float fat);

// Creates a "kitchen_equipment" object, owning the given "name" parameter.
// Note: The object proceeds to own the given "name" parameter.
kitchen_equipment *create_kitchen_equipment(char *name, unsigned int price, material mat);

// Creates a "appliance" object, owning the given "name" parameter.
// Note: The object proceeds to own the given "name" parameter.
appliance *create_appliance(char *name, unsigned int price, unsigned int power_consumption_watts);

// Creates a "electronic_device" object, owning the given "name" parameter.
// Note: The object proceeds to own the given "name" parameter.
electronic_device *create_electronic_device(char *name, unsigned int price);

// Destroy given food.
void destroy_food(food *f);

// Destroy given kitchen_equipment.
void destroy_kitchen_equipment(kitchen_equipment *k);

// Destroy given appliance.
void destroy_appliance(appliance *a);

// Destroy given electronic_device.
void destroy_electronic_device(electronic_device *e);

// Destroy given item.
void destroy_item(item *i);

#endif