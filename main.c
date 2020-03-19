#include <stdio.h>
#include "curl/url_fopen.h"
#include "conio2/conio2.h"

// Pedro Antonio Estévez Pérez

// Ejercicio 17

/* En la página web de la asignatura encontrará la librería curl, que permite cargar páginas
 * web usando funciones similares a las de manejo de ficheros en C. Así, la librería provee
 * de funciones url_fopen(), url_fclose(), url_fgets() etc. La página web a cargar se le pasa
 * como un URL (una cadena de caracteres “http://...”). Para usar la librería es necesario
 * que todos los ficheros que descargue de la web de la asignatura estén en la carpeta de su
 * proyecto. Además, deberá incluir en su programa el fichero url_fopen.h, e indicar en su
 * proyecto que se usan las librerías url_fopen.lib, libcurl.lib, libcurldll.lib y
 * libws2_32.lib (en ese orden). Realice un programa que obtenga datos meteorológicos actuales
 * de Ciudad Real (http://www.tiempo.com/ciudad-real.htm) y los muestre en pantalla (solo
 * deben aparecen los datos meteorológicos, p.ej. el estado del cielo o la temperatura).
 * Para que la salida en pantalla sea más “bonita” utilice la librería ”conio2” que podrá
 * descargar de la página web de la asignatura. NOTA IMPORTANTE: La URL se debe pasar
 * al programa como un parámetro de línea de comandos.*/

/* Primero, las librerías. Si ponía todos los archivos en la raíz del programa, no me las
 * cogía, creo que porque había archivos con el mismo nombre. O no. No lo sé. Pero al poner
 * cada librería en una carpeta y especificar la ruta en el programa ya sí las reconocía.
 * Recordar también que las libreías se ponen en la misma carpeta que el main, no en la
 * carpeta debug como con los ficheros. Por otra parte, recordar que para linkar librerías se
 * hace en el archivo .pro.
 *
 * En cuanto al html, el que se ve en la consola de google no es el mismo que se descarga ni
 * está distribuido de la misma forma. De ahí que buscara condicion atmosférica y no
 * apareciera nada, al igual que no podía buscar el final de línea ya que mete muchos en el
 * párrafo que equivaldría a una línea. Después me di cuenta de que después del segundo hoy del
 * html, aparece una descripción completa de las condiciones de ese día, así que será esa
 * la que coja. El problema es que está después del segundo hoy, por tanto, no se puede usar
 * strstr, sino que habrá que hacer un bucle para que nos podamos saltar el primer hoy.*/

int main()
{
    char codigo[50000], url[100];
    int i=0, j=0;
    URL_FILE *file;

    printf("Introduce la url: "); /*http://www.tiempo.com/ciudad-real.htm*/
    gets(url);

    file = url_fopen(url,"r");
    if (file == NULL)
    {
        printf("Error. No se pudo abrir la direccion especificada.");
        return 0;
    }
    else
    {
        int encontrado = 0;
        int aux = 0;
        url_fgets(codigo,50000,file);

        while (i<50000 && encontrado == 0)
        {
            if (codigo[i] == 'H' && codigo[i+1] == 'o' && codigo[i+2] == 'y')
            {
                if (aux == 0) // La primera nos la saltamos
                    aux++;
                else
                {
                    printf("La prevision del tiempo es: ");
                    j = i + 5; // Avanzamos Hoy: .
                    while(codigo[j] != '"')
                    {
                         printf("%c", codigo[j]);
                         j++;
                    }
                    encontrado = 1; // Una vez impresa la previsión, terminamos el bucle
                }
            }
            i++;
        }

        if (encontrado == 0) // Si encontrado es 0 es que hemos introducido una url, pero no la del tiempo
            printf("No se ha encontrado la condicion atmosferica.");

    }
    printf("\n\n");
    url_fclose(file);
}
