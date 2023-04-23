
#include <stdio.h>
#include <stdlib.h>


// Prototipos de las funciones
void roundRobin();
void trabajoMasCorto();
void beneficioColectivo();

int requeridas[2][8] ={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

char * actividades[11][5]={
"Libre", "0", "0", "0", "0",
"Require", "Gym", "100", "30", "# Para iniciar el día con energía",
"Trabaja", " ", "23", "40", "# Inicio quitandole los cordones a los zapatos",
"Requiere", " ", "Taller", "34", "20", "# Tengo que ir a traer el betún y el cepillo"
"Trabaja", " ", "324", "20", "# Enbetunar",
"Requiere", "Taller", "34", "20", "# Se me olvidó el cepillo del brillo",
"Trabaja", " ", "30", "20", "# Darles brillo",
"Trabaja", " ", "25", "09", "# Hay que tomar turnos para el brillo por que que cansado",
"Requiere", "Recreación", "23", "09", "# Me cansé, voy a pasear",
"Trabaja", " ", "242", "98", "# Limpio todo",
"Requiere", "Taller", "23", "908", "# Entrego todos los materiales"};

typedef struct Battery {
  float percentage;
} Battery;

//Estructura que lleva registro de las metricas
typedef struct Metrica {
  float tiempoEjecucion;
  int numeroDeIteraciones;
  
  //Tiempo promedio que toma cada tarea en ejecutar
  int tiempoPromedioTarea;
} Metrica;

void init_battery(Battery* battery) {
  battery->percentage = 100;
}

void charge_battery(Battery* battery) {
  battery->percentage += 10;
  if (battery->percentage > 100) {
    battery->percentage = 100;
  }
}

void discharge_battery(Battery* battery, float n) {
  battery->percentage -= n;
  if (battery->percentage < 0) {
    battery->percentage = 0;
  }
}

void pasoDelTiempo (int n){
    int i;
    int j;
    for (i = 0; i < 8; i++){
        if(requeridas[0][i] >0){
            requeridas[0][i] -= n;
            if (requeridas[0][i] <= 0) {
                requeridas[0][i] = 0;
                j = requeridas[1][i];
                requeridas[1][i] = 0;
                actividades[j][0] = "Libre";
            }
        }
    }
}

void ejecutarTareas() {
    Battery mi_bateria;
    init_battery(&mi_bateria);
    int i, j, r, ubicacion, temp, tiempo;
    float carga, x;
    char letra;
    for (i = 0; i < 1000; i++ ){
        pasoDelTiempo(1);
        letra =' ';
        char mystring[20] = " ";
        charge_battery(&mi_bateria);
        r = 0;
        tiempo = 0;
        temp = 0;
        for (j = 0; j < 11; j++ ){
            if (actividades[j][r] == "Libre"){
                ubicacion = j;
                r = 2;
                temp = 1;
            }else{
                if(actividades[j][r] != "0"){
                    carga = atof(actividades[j][3]);
                    tiempo = strtol(actividades[j][2], NULL, 10);
                    if(actividades[j][0] == "Trabaja"){
                        x = carga / tiempo;
                        if(tiempo >= 20){
                            pasoDelTiempo(20);
                            x *= 20;
                            discharge_battery(&mi_bateria,x);
                            x = carga - x;
                            sprintf(mystring,"%f",x);
                            actividades[j][3] = mystring;
                            x = tiempo - 20;
                            i += 20;
                            sprintf(mystring,"%f",x);
                            actividades[j][2] = mystring;
                            r = 0;
                            printf ("\n El proceso realizado es:%s", actividades[j][4]);
                        }else{
                            pasoDelTiempo(tiempo);
                            x *= tiempo;
                            discharge_battery(&mi_bateria,x);
                            x = carga - x;
                            sprintf(mystring,"%f",x);
                            actividades[j][3] = mystring;
                            x = tiempo - tiempo;
                            i += tiempo;
                            sprintf(mystring,"%f",x);
                            actividades[j][2] = mystring;
                            r = 0;
                            printf ("\n El proceso realizado es:%s", actividades[j][4]);
                        }
                    }else{
                        if(actividades[j][0] == "Requiere"){
                            tiempo = atof(actividades[j][2]);
                            carga = atof(actividades[j][3]);
                            letra = actividades[j][1][0];
                            switch (letra) {
                                case 'C':
                                    if(requeridas[0][0] == 0){
                                        requeridas[0][0] = tiempo;
                                        requeridas[1][0] = ubicacion;
                                        discharge_battery(&mi_bateria,carga);
                                        actividades[j][3] = "0";
                                        printf ("\n El proceso realizado es:%s", actividades[j][4]);
                                    }else{
                                        printf ("\n El recurso esta siendo utilizado");
                                    }
                                    break;
                                case 'R':
                                    if(requeridas[0][1] == 0){
                                        requeridas[0][1] = tiempo;
                                        requeridas[1][1] = ubicacion;
                                        discharge_battery(&mi_bateria,carga);
                                        actividades[j][3] = "0";
                                        printf ("\n El proceso realizado es:%s", actividades[j][4]);
                                    }else{
                                        printf ("\n El recurso esta siendo utilizado");
                                    }
                                    break;
                                case 'G':
                                    if(requeridas[0][2] == 0){
                                        requeridas[0][2] = tiempo;
                                        requeridas[1][2] = ubicacion;
                                        discharge_battery(&mi_bateria,carga);
                                        actividades[j][3] = "0";
                                        printf ("\n El proceso realizado es:%s", actividades[j][4]);
                                    }else{
                                        printf ("\n El recurso esta siendo utilizado");
                                    }
                                    break;
                                case 'B':
                                    if(requeridas[0][3] == 0){
                                        requeridas[0][3] = tiempo;
                                        requeridas[1][3] = ubicacion;
                                        discharge_battery(&mi_bateria,carga);
                                        actividades[j][3] = "0";
                                        printf ("\n El proceso realizado es:%s", actividades[j][4]);
                                    }else{
                                        printf ("\n El recurso esta siendo utilizado");
                                    }
                                    break;
                                case 'T':
                                    if(requeridas[0][4] == 0){
                                        requeridas[0][4] = tiempo;
                                        requeridas[1][4] = ubicacion;
                                        discharge_battery(&mi_bateria,carga);
                                        actividades[j][3] = "0";
                                        printf ("\n El proceso realizado es:%s", actividades[j][4]);
                                    }else{
                                        printf ("\n El recurso esta siendo utilizado");
                                    }
                                    break;
                                case 'F':
                                    if(requeridas[0][5] == 0){
                                        requeridas[0][5] = tiempo;
                                        requeridas[1][5] = ubicacion;
                                        discharge_battery(&mi_bateria,carga);
                                        actividades[j][3] = "0";
                                        printf ("\n El proceso realizado es:%s", actividades[j][4]);
                                    }else{
                                        printf ("\n El recurso esta siendo utilizado");
                                    }
                                    break;
                                case 'D':
                                    if(requeridas[0][6] == 0){
                                        requeridas[0][6] = tiempo;
                                        requeridas[1][6] = ubicacion;
                                        discharge_battery(&mi_bateria,carga);
                                        actividades[j][3] = "0";
                                        printf ("\n El proceso realizado es:%s", actividades[j][4]);
                                    }else{
                                        printf ("\n El recurso esta siendo utilizado");
                                    }
                                    break;
                                case 'H':
                                    if(requeridas[0][7] == 0){
                                        requeridas[0][7] = tiempo;
                                        requeridas[1][7] = ubicacion;
                                        discharge_battery(&mi_bateria,carga);
                                        actividades[j][3] = "0";
                                        printf ("\n El proceso realizado es:%s", actividades[j][4]);
                                    }else{
                                        printf ("\n El recurso esta siendo utilizado");
                                    }
                                    break;
                                default:
                                    printf ("\n El recurso especificado no existe");
                                    break;
                            }
                        }
                    }
                }
            }
        }
    }
}


// Definición de las funciones

//Ordenar la matriz en base al algoritmo round robin
void roundRobin() {
    printf("\nHa seleccionado round robin");
}

//Ordenar la matriz en base al algoritmo trabajo mas corto
void trabajoMasCorto() {
    printf("\nHa seleccionado trabajo mas corto");
}

//Ordenar la matriz en base al algoritmo beneficio colectivo
void beneficioColectivo() {
    printf("\nHa seleccionado beneficio colectivo");
}

int main(){
    int opcion;

    // Menú principal
    printf("---- Sistema de administracion de comuna. Seleccione el algoritmo que desea utilizar:\n");
    printf("1. Planificacion por turno circular 1\n");
    printf("2. Planificacion por trabajo mas corto 2\n");
    printf("3. Planificacion por beneficio colectivo 3\n");
    printf("---- Ingrese el número de la opción que desea: ");
    scanf("%d", &opcion);

    // Ejecutar la función correspondiente según la opción seleccionada
    switch(opcion) {
        case 1:
            roundRobin();
            break;
        case 2:
            trabajoMasCorto();
            break;
        case 3:
            beneficioColectivo();
            break;
        default:
            printf("Opción inválida\n");
            break;
    }

    ejecutarTareas();

    return 0;
}
