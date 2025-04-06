#ifndef PIZZA_ANALYSIS_H
#define PIZZA_ANALYSIS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAX_LINE 1024
#define MAX_ORDERS 1000
#define MAX_FIELD_LENGTH 200
#define MAX_INGREDIENTS 100
#define MAX_CATEGORIES 20

typedef struct {
    char pizza_id[20];
    char order_id[20];
    char pizza_name_id[50];
    int quantity;
    char order_date[20];
    char order_time[20];
    float unit_price;
    float total_price;
    char pizza_size[5];
    char pizza_category[20];
    char pizza_ingredients[MAX_FIELD_LENGTH];
    char pizza_name[50];
} PizzaOrder;

// Declaraciones de funciones
void load_csv(const char *filename);
void pms();
void pls();
void dms();
void dls();
void dmsp();
void dlsp();
void apo();
void apd();
void hp();
void ims();

// Variable global (se recomienda evitar globales en proyectos grandes,
// pero para este ejemplo se mantiene para simplificar la migración)
extern PizzaOrder orders[MAX_ORDERS];
extern int order_count;

#endif // PIZZA_ANALYSIS_H