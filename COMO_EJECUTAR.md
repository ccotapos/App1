
Primero y más importante, descarguen make para windows. Les dejo aquí link de vídeo tutorial
deben seguir TODOS los pasos del vídeo para que corra (yo seguí todos y me funcionó en windows aunque uso linux)

https://youtu.be/PIW8QG8q4v4?si=v1uJ2aAsobhfG9I2

despues de que hagan paso a paso lo del vídeo seguimos con lo importanteee


Ahora sí; 

1. Descarguen mi branch actualizada como carpeta (o solo abran mi branch en vscode desde su pc, tmbn sirve)
2. Despues abran la carpeta App1 de mi branch en vscode
3. Sí o sí el documento csv que tengan y quieran probar metanlo dentro de la carpeta App1, pueden cambiar si quieren
el csv datosdeprueva.csv que yo puse, si no el makefile no encontrará la ruta del archivo csv


4. Cuando hayan hecho todo esto, deberían abrir una terminal (Debe decir que esta abierta desde /App1 para así funcionar)
5. En la terminal ponen make, tal cual, sin parentesis ni mayusculas o etc
6. Luego debería aparecerles en el terminal el mensaje de:

 Compilación exitosa. Ejecutable creado en build/app1

7. Cuando sea así, ponen el siguiente comando en la terminal: 

.\build\app1.exe datosdeprueba.csv pms ims hp

Deben poner ese mismo mensaje, pueden cambiar el nombre de su archivo csv si es que tienen otro con otro nombre que hayan puesto en la carpeta App1 para probar.

Luego los parametros no tienen que ser los mismos a los que puse ahí, pueden probar solo pms, pms ims y etc, como quieran

Y debería salirles la ejecución, eso :D

8. Les recomiendo por último si es que quieren volver  probar, poner en la terminal el texto make clean
y luego volver a poner make para cuando lo quieran, así limpia el archivo del ejecutable y queda más limpia la terminal para repetidas ejecuciones.

Eso, confirmenme si les funciona porfa.