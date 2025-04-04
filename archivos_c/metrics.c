#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAX_LINE 1024
#define MAX_ORDERS 1000
#define MAX_FIELD_LENGTH 200
#define MAX_CATEGORIES 20 //Para funcion hp
#define MAX_INGREDIENTS 100 // Maxima cantidad de ingredientes unicos, Para funcion ims

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

PizzaOrder orders[MAX_ORDERS];
int order_count = 0;

void load_csv(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Error al abrir el archivo");
        exit(EXIT_FAILURE);
    }

    char line[MAX_LINE];
    fgets(line, MAX_LINE, file); // Saltar encabezado

    while (fgets(line, MAX_LINE, file) && order_count < MAX_ORDERS) {
        char *token;
        char *saveptr;

        token = strtok_r(line, ",", &saveptr);
        if (token == NULL) continue;
        strncpy(orders[order_count].pizza_id, token, sizeof(orders[order_count].pizza_id) - 1);

        token = strtok_r(NULL, ",", &saveptr);
        if (token == NULL) continue;
        strncpy(orders[order_count].order_id, token, sizeof(orders[order_count].order_id) - 1);

        token = strtok_r(NULL, ",", &saveptr);
        if (token == NULL) continue;
        strncpy(orders[order_count].pizza_name_id, token, sizeof(orders[order_count].pizza_name_id) - 1);

        token = strtok_r(NULL, ",", &saveptr);
        if (token == NULL) continue;
        orders[order_count].quantity = atoi(token);

        token = strtok_r(NULL, ",", &saveptr);
        if (token == NULL) continue;
        strncpy(orders[order_count].order_date, token, sizeof(orders[order_count].order_date) - 1);

        token = strtok_r(NULL, ",", &saveptr);
        if (token == NULL) continue;
        strncpy(orders[order_count].order_time, token, sizeof(orders[order_count].order_time) - 1);

        token = strtok_r(NULL, ",", &saveptr);
        if (token == NULL) continue;
        orders[order_count].unit_price = atof(token);

        token = strtok_r(NULL, ",", &saveptr);
        if (token == NULL) continue;
        orders[order_count].total_price = atof(token);

        token = strtok_r(NULL, ",", &saveptr);
        if (token == NULL) continue;
        strncpy(orders[order_count].pizza_size, token, sizeof(orders[order_count].pizza_size) - 1);

        token = strtok_r(NULL, ",", &saveptr);
        if (token == NULL) continue;
        strncpy(orders[order_count].pizza_category, token, sizeof(orders[order_count].pizza_category) - 1);

        token = strtok_r(NULL, "\"", &saveptr); // Ingredientes entre comillas
        if (token == NULL) continue;
        strncpy(orders[order_count].pizza_ingredients, token, sizeof(orders[order_count].pizza_ingredients) - 1);

        token = strtok_r(NULL, ",", &saveptr);
        if (token == NULL) continue;
        strncpy(orders[order_count].pizza_name, token, sizeof(orders[order_count].pizza_name) - 1);

        order_count++;
    }

    fclose(file);
}

// === FUNCIONES DE MÉTRICAS ===
void trim_newline(char *str) {
    size_t len = strlen(str);
    if (len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0';
    }
}

void pms() {
    char best_seller[50];
    int max_quantity = 0;
    for (int i = 0; i < order_count; i++) {
        if (orders[i].quantity > max_quantity) {
            max_quantity = orders[i].quantity;
            strcpy(best_seller, orders[i].pizza_name);
        }
    }
    printf("Pizza más vendida: %s con %d unidades\n", best_seller, max_quantity);
}

void pls() {
    char worst_seller[50];
    int min_quantity = INT_MAX;
    for (int i = 0; i < order_count; i++) {
        if (orders[i].quantity < min_quantity) {
            min_quantity = orders[i].quantity;
            strcpy(worst_seller, orders[i].pizza_name);
        }
    }
    printf("Pizza menos vendida: %s con %d unidades\n", worst_seller, min_quantity);
}

void dms() {
    typedef struct {
        char fecha[20];
        float total;
    } FechaVenta;

    FechaVenta fechas[MAX_ORDERS];
    int fechas_count = 0;

    for (int i = 0; i < order_count; i++) {
        int found = 0;
        for (int j = 0; j < fechas_count; j++) {
            if (strcmp(orders[i].order_date, fechas[j].fecha) == 0) {
                fechas[j].total += orders[i].total_price;
                found = 1;
                break;
            }
        }
        if (!found) {
            strcpy(fechas[fechas_count].fecha, orders[i].order_date);
            fechas[fechas_count].total = orders[i].total_price;
            fechas_count++;
        }
    }

    float max_total = 0;
    char mejor_fecha[20];

    for (int i = 0; i < fechas_count; i++) {
        if (fechas[i].total > max_total) {
            max_total = fechas[i].total;
            strcpy(mejor_fecha, fechas[i].fecha);
        }
    }

    printf("Fecha con más ventas en dinero: %s con un total de $%.2f\n", mejor_fecha, max_total);
}

void dls() {
    typedef struct {
        char fecha[20];
        float total;
    } FechaVenta;

    FechaVenta fechas[MAX_ORDERS];
    int fechas_count = 0;

    for (int i = 0; i < order_count; i++) {
        int found = 0;
        for (int j = 0; j < fechas_count; j++) {
            if (strcmp(orders[i].order_date, fechas[j].fecha) == 0) {
                fechas[j].total += orders[i].total_price;
                found = 1;
                break;
            }
        }
        if (!found) {
            strcpy(fechas[fechas_count].fecha, orders[i].order_date);
            fechas[fechas_count].total = orders[i].total_price;
            fechas_count++;
        }
    }

    float min_total = INT_MAX;
    char peor_fecha[20];

    for (int i = 0; i < fechas_count; i++) {
        if (fechas[i].total < min_total) {
            min_total = fechas[i].total;
            strcpy(peor_fecha, fechas[i].fecha);
        }
    }

    printf("Fecha con menos ventas en dinero: %s con un total de $%.2f\n", peor_fecha, min_total);
}


void dmsp() {
    char best_day[20];
    int max_quantity = 0;
    for (int i = 0; i < order_count; i++) {
        if (orders[i].quantity > max_quantity) {
            max_quantity = orders[i].quantity;
            strcpy(best_day, orders[i].order_date);
        }
    }
    printf("Fecha con más ventas en cantidad de pizzas: %s con %d pizzas\n", best_day, max_quantity);
}

void dlsp() {
    char worst_day[20];
    int min_quantity = INT_MAX;
    for (int i = 0; i < order_count; i++) {
        if (orders[i].quantity < min_quantity) {
            min_quantity = orders[i].quantity;
            strcpy(worst_day, orders[i].order_date);
        }
    }
    printf("Fecha con menos ventas en cantidad de pizzas: %s con %d pizzas\n", worst_day, min_quantity);
}

void apo() {
    if (order_count == 0) {
        printf("No hay órdenes para calcular el promedio.\n");
        return;
    }

    int total_pizzas = 0;
    for (int i = 0; i < order_count; i++) {
        total_pizzas += orders[i].quantity;
    }

    float promedio = (float)total_pizzas / order_count;
    printf("Promedio de pizzas por orden: %.2f\n", promedio);
}


void apd() {
    if (order_count == 0) {
        printf("No hay órdenes para calcular el promedio.\n");
        return;
    }

    // Usaremos un arreglo para registrar las fechas únicas
    char fechas_unicas[MAX_ORDERS][20];
    int fechas_count = 0;
    int total_pizzas = 0;

    for (int i = 0; i < order_count; i++) {
        int fecha_existe = 0;
        // Verificamos si la fecha ya está registrada
        for (int j = 0; j < fechas_count; j++) {
            if (strcmp(orders[i].order_date, fechas_unicas[j]) == 0) {
                fecha_existe = 1;
                break;
            }
        }
        // Si la fecha no está registrada, la añadimos
        if (!fecha_existe) {
            strcpy(fechas_unicas[fechas_count], orders[i].order_date);
            fechas_count++;
        }

        // Sumar la cantidad de pizzas de cada orden
        total_pizzas += orders[i].quantity;
    }

    // Calculamos el promedio de pizzas por día
    float promedio = (float)total_pizzas / fechas_count;
    printf("Promedio de pizzas por día: %.2f\n", promedio);
}
void hp() {
    int category_counts[MAX_CATEGORIES] = {0};
    char category_names[MAX_CATEGORIES][20];
    int category_count = 0;

    for (int i = 0; i < order_count; i++) {
        if (strlen(orders[i].pizza_category) == 0) continue;

        char cleaned_category[20];
        strncpy(cleaned_category, orders[i].pizza_category, sizeof(cleaned_category) - 1);
        cleaned_category[sizeof(cleaned_category) - 1] = '\0';
        trim_newline(cleaned_category);

        int found = 0;
        for (int j = 0; j < category_count; j++) {
            if (strcmp(cleaned_category, category_names[j]) == 0) {
                category_counts[j] += orders[i].quantity;
                found = 1;
                break;
            }
        }
        if (!found && category_count < MAX_CATEGORIES) {
            strncpy(category_names[category_count], cleaned_category, sizeof(category_names[category_count]) - 1);
            category_names[category_count][sizeof(category_names[category_count]) - 1] = '\0';
            category_counts[category_count] = orders[i].quantity;
            category_count++;
        }
    }
    for (int i = 0; i < category_count; i++) {
        printf("Categoría: %s, Cantidad: %d\n", category_names[i], category_counts[i]);
    }
}

void ims() {
    int ingredient_counts[MAX_INGREDIENTS] = {0};
    char ingredient_names[MAX_INGREDIENTS][50] = {0};
    int ingredient_count = 0;

    for (int i = 0; i < order_count; i++) {
        char ingredients[MAX_FIELD_LENGTH];
        strcpy(ingredients, orders[i].pizza_ingredients);
        char *ingredient = strtok(ingredients, ",");
        while (ingredient != NULL) {
            // Trim leading/trailing spaces
            while (*ingredient == ' ') ingredient++;
            char *end = ingredient + strlen(ingredient) - 1;
            while (end > ingredient && *end == ' ') end--;
            *(end + 1) = '\0';

            int found = 0;
            for (int j = 0; j < ingredient_count; j++) {
                if (strcmp(ingredient, ingredient_names[j]) == 0) {
                    ingredient_counts[j] += orders[i].quantity;
                    found = 1;
                    break;
                }
            }
            if (!found && ingredient_count < MAX_INGREDIENTS) {
                strcpy(ingredient_names[ingredient_count], ingredient);
                ingredient_counts[ingredient_count] = orders[i].quantity;
                ingredient_count++;
            }
            ingredient = strtok(NULL, ",");
        }
    }

    int max_count = 0;
    int max_index = -1;
    for (int i = 0; i < ingredient_count; i++) {
        if (ingredient_counts[i] > max_count) {
            max_count = ingredient_counts[i];
            max_index = i;
        }
    }

    if (max_index != -1) {
        printf("El ingrediente más vendido es: %s\nCon un total de %d ventas \n", ingredient_names[max_index], ingredient_counts[max_index]);
    } else {
        printf("No se encontraron ingredientes.\n");
    }
}


// === MAPEO DE FUNCIONES ===

typedef void (*MetricFunction)();

typedef struct {
    const char *name;
    MetricFunction function;
} FunctionMap;

FunctionMap functions[] = {
    {"pms", pms},
    {"pls", pls},
    {"dms", dms},
    {"dls", dls},
    {"dmsp", dmsp},
    {"dlsp", dlsp},
    {"apo", apo},
    {"apd", apd},
    {"hp", hp},
    {"ims", ims}
};

int num_functions = sizeof(functions) / sizeof(FunctionMap);

void call_function_by_name(const char *name) {
    for (int i = 0; i < num_functions; i++) {
        if (strcmp(name, functions[i].name) == 0) {
            functions[i].function();
            return;
        }
    }
    printf("Función desconocida: %s\n", name);
}

// === MAIN ===

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Uso: %s <archivo_csv> <métrica1> [métrica2] [...]\n", argv[0]);
        return 1;
    }

    load_csv(argv[1]);

    for (int i = 2; i < argc; i++) {
        call_function_by_name(argv[i]);
    }

    return 0;
}
