#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAX_LINE 1024
#define MAX_ORDERS 1000
#define MAX_FIELD_LENGTH 200 // Ajustado para pizza_ingredients

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
        printf("Línea leída: %s", line); // Imprime la línea leída

        char *token;
        char *saveptr;

        token = strtok_r(line, ",", &saveptr);
        if (token == NULL) continue;
        strncpy(orders[order_count].pizza_id, token, sizeof(orders[order_count].pizza_id) - 1);
        orders[order_count].pizza_id[sizeof(orders[order_count].pizza_id) - 1] = '\0';

        token = strtok_r(NULL, ",", &saveptr);
        if (token == NULL) continue;
        strncpy(orders[order_count].order_id, token, sizeof(orders[order_count].order_id) - 1);
        orders[order_count].order_id[sizeof(orders[order_count].order_id) - 1] = '\0';

        token = strtok_r(NULL, ",", &saveptr);
        if (token == NULL) continue;
        strncpy(orders[order_count].pizza_name_id, token, sizeof(orders[order_count].pizza_name_id) - 1);
        orders[order_count].pizza_name_id[sizeof(orders[order_count].pizza_name_id) - 1] = '\0';

        token = strtok_r(NULL, ",", &saveptr);
        if (token == NULL) continue;
        orders[order_count].quantity = atoi(token);

        token = strtok_r(NULL, ",", &saveptr);
        if (token == NULL) continue;
        strncpy(orders[order_count].order_date, token, sizeof(orders[order_count].order_date) - 1);
        orders[order_count].order_date[sizeof(orders[order_count].order_date) - 1] = '\0';

        token = strtok_r(NULL, ",", &saveptr);
        if (token == NULL) continue;
        strncpy(orders[order_count].order_time, token, sizeof(orders[order_count].order_time) - 1);
        orders[order_count].order_time[sizeof(orders[order_count].order_time) - 1] = '\0';

        token = strtok_r(NULL, ",", &saveptr);
        if (token == NULL) continue;
        orders[order_count].unit_price = atof(token);

        token = strtok_r(NULL, ",", &saveptr);
        if (token == NULL) continue;
        orders[order_count].total_price = atof(token);

        token = strtok_r(NULL, ",", &saveptr);
        if (token == NULL) continue;
        strncpy(orders[order_count].pizza_size, token, sizeof(orders[order_count].pizza_size) - 1);
        orders[order_count].pizza_size[sizeof(orders[order_count].pizza_size) - 1] = '\0';

        token = strtok_r(NULL, ",", &saveptr);
        if (token == NULL) continue;
        strncpy(orders[order_count].pizza_category, token, sizeof(orders[order_count].pizza_category) - 1);
        orders[order_count].pizza_category[sizeof(orders[order_count].pizza_category) - 1] = '\0';

        // Manejar la cadena entre comillas dobles
        token = strtok_r(NULL, "\"", &saveptr);
        if (token == NULL) continue;
        strncpy(orders[order_count].pizza_ingredients, token, sizeof(orders[order_count].pizza_ingredients) - 1);
        orders[order_count].pizza_ingredients[sizeof(orders[order_count].pizza_ingredients) - 1] = '\0';

        token = strtok_r(NULL, ",", &saveptr);
        if (token == NULL) continue;
        strncpy(orders[order_count].pizza_name, token, sizeof(orders[order_count].pizza_name) - 1);
        orders[order_count].pizza_name[sizeof(orders[order_count].pizza_name) - 1] = '\0';

        order_count++;
    }

    fclose(file);
    printf("Se cerro el bucle \n");
}

void pms() { printf("Pizza más vendida\n"); }
void pls() { printf("Pizza menos vendida\n"); }
void dms() { printf("Fecha con más ventas en dinero\n"); }
void dls() { printf("Fecha con menos ventas en dinero\n"); }
void dmsp() { printf("Fecha con más ventas en cantidad de pizzas\n"); }
void dlsp() { printf("Fecha con menos ventas en cantidad de pizzas\n"); }
void apo() { printf("Promedio de pizzas por orden\n"); }
void apd() { printf("Promedio de pizzas por día\n"); }
void ims() { printf("Ingrediente más vendido\n"); }
void hp() { printf("Cantidad de pizzas por categoría vendidas\n"); }

typedef void (*MetricFunction)();

typedef struct {
    char *name;
    MetricFunction function;
} Metric;

Metric metrics[] = {
    {"pms", pms}, {"pls", pls}, {"dms", dms}, {"dls", dls},
    {"dmsp", dmsp}, {"dlsp", dlsp}, {"apo", apo}, {"apd", apd},
    {"ims", ims}, {"hp", hp}
};

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Uso: %s <archivo.csv> <métrica1> [métrica2] ...\n", argv[0]);
        return 1;
    }
    load_csv(argv[1]);
    for (int i = 2; i < argc; i++) {
        int found = 0;
        for (int j = 0; j < sizeof(metrics) / sizeof(metrics[0]); j++) {
            if (strcmp(argv[i], metrics[j].name) == 0) {
                metrics[j].function();
                found = 1;
                break;
            }
        }
        if (!found) printf("Función desconocida: %s\n", argv[i]);
    }
    return 0;
}





/* //PRUEBA PARA VER SI LA MIELDA SE MUESTRA EN LA TERMINAL O NO
int main(int argc, char *argv[]) {
    // Verifica si se proporcionó al menos un argumento
    if (argc < 2) {
      printf("Uso: %s <nombre>\n", argv[0]);
      return 1; // Indica un error
    }
  
    // Obtiene el nombre del argumento
    char *nombre = argv[1];
  
    // Imprime un saludo personalizado
    printf("Hola, %s!\n", nombre);
  
    // Verifica si se proporcionó un segundo argumento
    if (argc > 2) {
      printf("Argumento adicional: %s\n", argv[2]);
    }
  
    return 0; // Indica éxito
  } */