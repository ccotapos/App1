#include <stdio.h>
#include <string.h>
#include "includes/pizza_analysis.h"

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Uso: %s <archivo_csv> <metrica1> [metrica2 ...]\n", argv[0]);
        printf("Metricas disponibles: pms, pls, dms, dls, dmsp, dlsp, apo, apd, hp, ims\n");
        return 1;
    }

    char *archivoCSV = argv[1];


    load_csv(archivoCSV);

    for (int i = 2; i < argc; i++) {
        char *metrica = argv[i];
        printf("\n--- Metrica: %s ---\n", metrica);
        if (strcmp(metrica, "pms") == 0) {
            pms();
        } else if (strcmp(metrica, "pls") == 0) {
            pls();
        } else if (strcmp(metrica, "dms") == 0) {
            dms();
        } else if (strcmp(metrica, "dls") == 0) {
            dls();
        } else if (strcmp(metrica, "dmsp") == 0) {
            dmsp();
        } else if (strcmp(metrica, "dlsp") == 0) {
            dlsp();
        } else if (strcmp(metrica, "apo") == 0) {
            apo();
        } else if (strcmp(metrica, "apd") == 0) {
            apd();
        } else if (strcmp(metrica, "ims") == 0) {
            ims();
        } else if (strcmp(metrica, "hp") == 0) {
            hp();
        } else {
            printf("Metrica desconocida: %s\n", metrica);
        }
    }
    return 0; // Es buena práctica tener un return 0 al final de main si no hubo errores
}