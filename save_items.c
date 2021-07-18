#include <string.h>

#include "save_items.h"
#include "libraries/malloc_utils.h"

#define FWRITE_OR_RETURN(ptr, size, amt, file) if (fwrite(ptr, size, amt, file) != amt) return 0;
#define FREAD_OR_RETURN(ptr, size, amt, file) if (fread(ptr, size, amt, file) != amt) return 0;

static int fwrite_food(food *f, FILE *file) {
    FWRITE_OR_RETURN(&f->type, sizeof(f->type), 1, file);
    size_t string_length = strlen(f->name);
    FWRITE_OR_RETURN(&string_length, sizeof(string_length), 1, file);
    FWRITE_OR_RETURN(f->name, sizeof(char), string_length, file);
    FWRITE_OR_RETURN(&f->price, sizeof(f->price), 1, file);
    FWRITE_OR_RETURN(&f->calories, sizeof(f->calories), 1, file);
    FWRITE_OR_RETURN(&f->protein, sizeof(f->protein), 1, file);
    FWRITE_OR_RETURN(&f->carbs, sizeof(f->carbs), 1, file);
    FWRITE_OR_RETURN(&f->fat, sizeof(f->fat), 1, file);
    return 1;
}

static int fwrite_kitchen_equipment(kitchen_equipment *k, FILE *file) {
    FWRITE_OR_RETURN(&k->type, sizeof(k->type), 1, file);
    size_t string_length = strlen(k->name);
    FWRITE_OR_RETURN(&string_length, sizeof(string_length), 1, file);
    FWRITE_OR_RETURN(k->name, sizeof(char), string_length, file);
    FWRITE_OR_RETURN(&k->price, sizeof(k->price), 1, file);
    FWRITE_OR_RETURN(&k->mat, sizeof(k->mat), 1, file);
    return 1;
}

static int fwrite_appliance(appliance *a, FILE *file) {
    FWRITE_OR_RETURN(&a->type, sizeof(a->type), 1, file);
    size_t string_length = strlen(a->name);
    FWRITE_OR_RETURN(&string_length, sizeof(size_t), 1, file);
    FWRITE_OR_RETURN(a->name, sizeof(char), string_length, file);
    FWRITE_OR_RETURN(&a->price, sizeof(a->price), 1, file);
    FWRITE_OR_RETURN(&a->power_consumption_watts, sizeof(a->power_consumption_watts), 1, file);
    return 1;
}

static int fwrite_electronic_device(electronic_device *e, FILE *file) {
    FWRITE_OR_RETURN(&e->type, sizeof(e->type), 1, file);
    size_t string_length = strlen(e->name);
    FWRITE_OR_RETURN(&string_length, sizeof(size_t), 1, file);
    FWRITE_OR_RETURN(e->name, sizeof(char), string_length, file);
    FWRITE_OR_RETURN(&e->price, sizeof(e->price), 1, file);
    return 1;
}

int fwrite_item(item *i, FILE *file) {
    switch(i->type) {
        case FOOD:
            return fwrite_food((food *) i, file);
        case KITCHEN_EQUIPMENT:
            return fwrite_kitchen_equipment((kitchen_equipment *) i, file);
        case APPLIANCE:
            return fwrite_appliance((appliance *) i, file);
        case ELECTRONIC_DEVICE:
            return fwrite_electronic_device((electronic_device *) i, file);
    }
    return 0;
}

static int fread_food_helper(
    char *name, size_t name_len, 
    unsigned int *price, unsigned int *calories, 
    float *protein, float *carbs, float *fat, 
    FILE *file
) {
    FREAD_OR_RETURN(name, sizeof(char), name_len, file);
    name[name_len] = '\0';
    FREAD_OR_RETURN(price, sizeof(*price), 1, file);
    FREAD_OR_RETURN(calories, sizeof(*calories), 1, file);
    FREAD_OR_RETURN(protein, sizeof(*protein), 1, file);
    FREAD_OR_RETURN(carbs, sizeof(*carbs), 1, file);
    FREAD_OR_RETURN(fat, sizeof(*fat), 1, file);
    return 1;
}

static int fread_food(food **f, FILE *file) {
    size_t name_len;
    FREAD_OR_RETURN(&name_len, sizeof(name_len), 1, file);
    char *name = malloc_or_die(name_len + 1);
    unsigned int price, calories;
    float protein, carbs, fat;
    int success = fread_food_helper(name, name_len, &price, &calories, &protein, &carbs, &fat, file);
    if (!success) {
        free(name);
        return 0;
    }
    *f = create_food(name, price, calories, protein, carbs, fat);
    return 1;
}

static int fread_kitchen_equipment_helper(
    char *name, size_t name_len, 
    unsigned int *price, material *mat, 
    FILE *file
) {
    FREAD_OR_RETURN(name, sizeof(char), name_len, file);
    name[name_len] = '\0';
    FREAD_OR_RETURN(price, sizeof(*price), 1, file);
    FREAD_OR_RETURN(mat, sizeof(*mat), 1, file);
    return 1;
}

static int fread_kitchen_equipment(kitchen_equipment **k, FILE *file) {
    size_t name_len;
    FREAD_OR_RETURN(&name_len, sizeof(name_len), 1, file);
    char *name = malloc_or_die(name_len + 1);
    unsigned int price;
    material mat;
    int success = fread_kitchen_equipment_helper(name, name_len, &price, &mat, file);
    if (!success) {
        free(name);
        return 0;
    }
    *k = create_kitchen_equipment(name, price, mat);
    return 1;
}

static int fread_appliance_helper(
    char *name, size_t name_len, 
    unsigned int *price, unsigned int *power_consumption_watts, 
    FILE *file
) {
    FREAD_OR_RETURN(name, sizeof(char), name_len, file);
    name[name_len] = '\0';
    FREAD_OR_RETURN(price, sizeof(*price), 1, file);
    FREAD_OR_RETURN(power_consumption_watts, sizeof(*power_consumption_watts), 1, file);
    return 1;
}

static int fread_appliance(appliance **a, FILE *file) {
    size_t name_len;
    FREAD_OR_RETURN(&name_len, sizeof(name_len), 1, file);
    char *name = malloc_or_die(name_len + 1);
    unsigned int price, power_consumption_watts;
    int success = fread_appliance_helper(name, name_len, &price, &power_consumption_watts, file);
    if (!success) {
        free(name);
        return 0;
    }
    *a = create_appliance(name, price, power_consumption_watts);
    return 1;
}

static int fread_electronic_device_helper(
    char *name, size_t name_len, 
    unsigned int *price, 
    FILE *file
) {
    FREAD_OR_RETURN(name, sizeof(char), name_len, file);
    name[name_len] = '\0';
    FREAD_OR_RETURN(price, sizeof(*price), 1, file);
    return 1;
}

static int fread_electronic_device(electronic_device **a, FILE *file) {
    size_t name_len;
    FREAD_OR_RETURN(&name_len, sizeof(name_len), 1, file);
    char *name = malloc_or_die(name_len + 1);
    unsigned int price;
    int success = fread_electronic_device_helper(name, name_len, &price, file);
    if (!success) {
        free(name);
        return 0;
    }
    *a = create_electronic_device(name, price);
    return 1;
}

int fread_item(item **i, FILE *file) {
    item_type type;
    fread(&type, sizeof(type), 1, file);
    switch(type) {
        case FOOD:
            return fread_food((food **) i, file);
        case KITCHEN_EQUIPMENT:
            return fread_kitchen_equipment((kitchen_equipment **) i, file);
        case APPLIANCE:
            return fread_appliance((appliance **) i, file);
        case ELECTRONIC_DEVICE:
            return fread_electronic_device((electronic_device **) i, file);
    }
    return 0;
}