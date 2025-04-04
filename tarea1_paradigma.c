#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAX_LINE 1024
#define MAX_ORDERS 1000
#define MAX_FIELD_LENGTH 200 // Ajustado para pizza_ingredients
#define MAX_INGREDIENTS 100 // Maxima cantidad de ingredientes unicos, Para funcion ims
#define MAX_CATEGORIES 20 //Para funcion hp

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

// Función para encontrar la pizza más vendida
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

// Función para encontrar la pizza menos vendida
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

// Función para encontrar la fecha con más ventas en términos de dinero
void dms() {
    char best_day[20];
    float max_sales = 0;
    for (int i = 0; i < order_count; i++) {
        if (orders[i].total_price > max_sales) {
            max_sales = orders[i].total_price;
            strcpy(best_day, orders[i].order_date);
        }
    }
    printf("Fecha con más ventas en dinero: %s con $%.2f\n", best_day, max_sales);
}




// Función para encontrar la fecha con menos ventas en términos de dinero
void dls() {
    char worst_day[20];
    float min_sales = INT_MAX;
    for (int i = 0; i < order_count; i++) {
        if (orders[i].total_price < min_sales) {
            min_sales = orders[i].total_price;
            strcpy(worst_day, orders[i].order_date);
        }
    }
    printf("Fecha con menos ventas en dinero: %s con $%.2f\n", worst_day, min_sales);
}

// Función para encontrar la fecha con más ventas en términos de cantidad de pizzas
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

// Función para encontrar la fecha con menos ventas en términos de cantidad de pizzas
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

// Función para calcular el promedio de pizzas por orden
void apo() { //REQUIERE QUE EL ULTIMO ORDER_ID SEA EL NUMERO TOTAL DE ORDENES
    int order_id_numerico = 0;
    if (order_count == 0) {
        printf("No hay órdenes para calcular el promedio.\n");
        return;
    }
    float total_pizzas = 0;
    for (int i = 0; i < order_count; i++) {
        total_pizzas += orders[i].quantity;
    }
    order_id_numerico = atoi(orders[order_count - 1].order_id);
    printf("Promedio de pizzas por orden: %.2f\n", (total_pizzas / order_id_numerico));
}

void apd() { //Esta funcion mira si entre dos fechas adyacentes hay diferencia, la registra como un uno y recorre todo el csv, en necesario que el csv este en orden cronologico
    int diferencias = 0;

    if (order_count <= 1) {
        // No hay suficientes fechas para comparar
        printf("No hay suficientes ordenes"); // O puedes retornar un valor de error si lo prefieres.
    }

    for (int i = 1; i < order_count; i++) {
        if (strcmp(orders[i].order_date, orders[i - 1].order_date) != 0) {
            diferencias++;
        }
    }

    float total_pizzas = 0;
    for (int i = 0; i < order_count; i++) {
        total_pizzas += orders[i].quantity;
    }
    printf("Hay una cantidad total de %d dias distintos, y hay un total de %f pizzas \n", diferencias, total_pizzas);
    printf("Entonces el promedio de pizzas por dia es: %.2f ", total_pizzas/diferencias); //No se como %.2f es el especificador de formato correcto, si no es un d y no un f xd, pero funciona
}

void hp() {
    int category_counts[MAX_CATEGORIES] = {0};
    char category_names[MAX_CATEGORIES][20] = {0};
    int category_count = 0;

    for (int i = 0; i < order_count; i++) {
        int found = 0;
        for (int j = 0; j < category_count; j++) {
            if (strcmp(orders[i].pizza_category, category_names[j]) == 0) {
                category_counts[j] += orders[i].quantity;
                found = 1;
                break;
            }
        }
        if (!found && category_count < MAX_CATEGORIES) {
            strcpy(category_names[category_count], orders[i].pizza_category);
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

int main (int argc, char *argv[]){ //Finalmente hacemos la funcion main 

    if (argc < 2){
        printf("No se ingreso ningun argumento, fuera FUERA FUERA SAL DE MI CABEZAAAAA");
        return 1;
    }

    // cargar csv ESTOY EN ESTo

    char *archivoCSV = argv[1];

    load_csv(archivoCSV); // Llama al CSV con el nombre del archivo

        //Obtiene el nombre del argumento 1 y 2
    char *nombreFuncion1 = argv[2];
    char *nombreFuncion2 = argv[3];


    if (argc > 2) {
        char *nombreFuncion1 = argv[2];
        if (strcmp(nombreFuncion1, "pms") == 0) {
            pms();
        } else if (strcmp(nombreFuncion1, "pls") == 0) {
            pls();
        } else if (strcmp(nombreFuncion1, "dms") == 0) {
            dms();
        } else if (strcmp(nombreFuncion1, "dls") == 0) {
            dls();
        } else if (strcmp(nombreFuncion1, "dmsp") == 0) {
            dmsp();
        } else if (strcmp(nombreFuncion1, "dlsp") == 0) {
            dlsp();
        } else if (strcmp(nombreFuncion1, "apo") == 0) {
            apo();
        } else if (strcmp(nombreFuncion1, "apd") == 0) {
            apd();
        } else if (strcmp(nombreFuncion1, "ims") == 0) {
            ims();  
        } else if (strcmp(nombreFuncion1, "hp") == 0) {
            hp();
        } else {
            printf("Función desconocida: %s\n", nombreFuncion1);
        }
    }
    
    if (argc > 3) {
        char *nombreFuncion2 = argv[3];
        if (strcmp(nombreFuncion2, "pms") == 0) {
            pms();
        } else if (strcmp(nombreFuncion2, "pls") == 0) {
            pls();
        } else if (strcmp(nombreFuncion2, "dms") == 0) {
            dms();
        } else if (strcmp(nombreFuncion2, "dls") == 0) {
            dls();
        } else if (strcmp(nombreFuncion2, "dmsp") == 0) {
            dmsp();
        } else if (strcmp(nombreFuncion2, "dlsp") == 0) {
            dlsp();
        } else if (strcmp(nombreFuncion2, "apo") == 0) {
            apo();
        } else if (strcmp(nombreFuncion2, "apd") == 0) {
            apd();
        } else if (strcmp(nombreFuncion2, "ims") == 0) {
            ims();  
        } else if (strcmp(nombreFuncion2, "hp") == 0) {
            hp();
        } else {
            printf("Función desconocida: %s\n", nombreFuncion2);
        }
    }

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