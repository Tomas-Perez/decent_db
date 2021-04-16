#include <stdio.h>
#include <string.h>

#include "print_items.h"

#define MAX(x, y) (x > y ? x : y)

void print_food(food *f) {
    printf("---FOOD---\n");
    printf("%s\n", f->name);
    printf("%u$ / 100g\n", f->price);
    printf("Nutritional Information:\n");
    
    const char *calories_str = "Calories";
    const char *protein_str = "Protein";
    const char *carbs_str = "Carbohydrates";
    const char *fat_str = "Fat";

    int size_calories_str = strlen(calories_str);
    int size_protein_str = strlen(protein_str);
    int size_carbs_str = strlen(carbs_str);
    int size_fat_str = strlen(fat_str);

    int size_calories_val_str = snprintf(NULL, 0, "%u kcal", f->calories);
    int size_protein_val_str = snprintf(NULL, 0, "%.2f g", f->protein);
    int size_carbs_val_str = snprintf(NULL, 0, "%.2f g", f->carbs);
    int size_fat_val_str = snprintf(NULL, 0, "%.2f g", f->fat);

    int calories_max_size = MAX(size_calories_str, size_calories_val_str);
    int protein_max_size = MAX(size_protein_str, size_protein_val_str);
    int carbs_max_size = MAX(size_carbs_str, size_carbs_val_str);
    int fat_max_size = MAX(size_fat_str, size_fat_val_str);

    int size_header_str = snprintf(NULL, 0, "| %*s%s | %*s%s | %*s%s | %*s%s |", 
        calories_max_size - size_calories_str, "", calories_str, 
        protein_max_size - size_protein_str, "", protein_str, 
        carbs_max_size - size_carbs_str, "", carbs_str, 
        fat_max_size - size_fat_str, "", fat_str 
    );

    char header[size_header_str+1];
    for (int i = 0; i < size_header_str; i++) {
        header[i] = '-';
    }
    header[size_header_str] = '\0';
    
    printf("%s\n", header);
    printf("| %*s%s | %*s%s | %*s%s | %*s%s |\n", 
        calories_max_size - size_calories_str, "", calories_str, 
        protein_max_size - size_protein_str, "", protein_str, 
        carbs_max_size - size_carbs_str, "", carbs_str, 
        fat_max_size - size_fat_str, "", fat_str 
    );
    printf("| %*s%u kcal | %*s%.2f g | %*s%.2f g | %*s%.2f g |\n",
        calories_max_size - size_calories_val_str, "", f->calories, 
        protein_max_size - size_protein_val_str, "", f->protein, 
        carbs_max_size - size_carbs_val_str, "", f->carbs, 
        fat_max_size - size_fat_val_str, "", f->fat 
    );
    printf("%s\n", header);
}

void print_kitchen_equipment(kitchen_equipment *k) {
    printf("---KITCHEN EQUIPMENT---\n");
    printf("%s\n", k->name);
    printf("Unit price: $ %u\n", k->price);
    printf("Material: ");
    switch(k->mat) {
        case WOOD:
            printf("Wood");
            break;
        case METAL:
            printf("Metal");
            break;
        case PLASTIC:
            printf("Plastic");
            break;
    }
    printf("\n");
}

void print_appliance(appliance *a) {
    printf("---APPLIANCE---\n");
    printf("%s\n", a->name);
    printf("MSRP: $ %u\n", a->price);
    printf("Power consumption: %u W\n", a->power_consumption_watts);
}

void print_electronic_device(electronic_device *e) {
    printf("---ELECTRONIC DEVICE---\n");
    printf("%s\n", e->name);
    printf("MSRP: $ %u\n", e->price);
}

void print_item(item *i) {
    switch(i->type) {
        case FOOD:
            print_food((food *) i);
            break;
        case KITCHEN_EQUIPMENT:
            print_kitchen_equipment((kitchen_equipment *) i);
            break;
        case APPLIANCE:
            print_appliance((appliance *) i);
            break;
        case ELECTRONIC_DEVICE:
            print_electronic_device((electronic_device *) i);
            break;
    }
}