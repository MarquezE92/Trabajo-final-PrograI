#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char *porte[] =
{
    "CHICO",
    "MEDIANO",
    "GRANDE"
};

const char *genero[] =
{
    "MACHO",
    "HEMBRA"
};

typedef enum
{
    CHICO,
    MEDIANO,
    GRANDE
} Porte;

typedef enum
{
    DISPONIBLE,
    ADOPTADO
} Estado;

typedef enum
{
    CALMADO,
    JUGUETON,
    ANSIOSO,
    AGRESIVO,
    SOCIABLE
} Temperamento;

typedef enum
{
    MACHO,
    HEMBRA
} Genero;

typedef struct
{
    int idPerrito;
    char solicitante[35];
    char email[35];
    char tel[12];
} Solicitud;

typedef struct
{
    int idPerrito;
    char nombre[35];
    int edad;
    char raza[35];
    Porte porte;
    Estado estado;
    Temperamento temperamento;
    Genero genero;
    char fechaIngreso[10];
} Perrito;

typedef struct
{
    char fecha[10];
    char comentario[125]
} Observacion;

typedef struct
{
    int idPerrito;
    int idAdoptante;
    Observacion observaciones[6]; //??
} Adopcion;

typedef struct
{
    int idAdoptante;
    char nombre[35];
    char email[35];
    char tel[12];
    char direccion[35]
} Adoptante;


///prototipados
int mostrarMenuPrincipal();
void mostrarMenuAdmin();

Solicitud cargarSolicitudSimple();
Perrito cargarPerrito();
///void mostrarPerrito(Perrito perri);

///yo
void mostrarUnPerrito(Perrito perri);
void mostrarListadoPerritosRecursivo(Perrito lista[], int valido, int i);
void filtrarPerritos(Perrito lista[], int validos);
void mostrarMenuAdoptante(Perrito lista[], int validos, char archivoSolicitudes[]);
int main()
{
    system("color 0B");

    Perrito perri = cargarPerrito();
    ///mostrarPerrito(perri);

    /*int opcion = mostrarMenuPrincipal();


    switch(opcion){
        case 0:
            printf("\n Nos vemos!!!");
            break;
        case 1:
            mostrarMenuAdmin();
            break;
        case 2:
            mostrarMenuAdoptante();
            break;
        case 3:
            printf("\nNo nos mienta\n");
            printf("\n");
            mostrarMenuPrincipal();
            break;
    }*/
    Perrito refugio[];/// arreglo para las funciones faltan los validos que daria la funcion de carga

    return 0;
}

///funciones
int mostrarMenuPrincipal()
{
    int opcion;

    do
    {
        printf("+-----------------------------------------+");
        printf("\n| \t 1.- Soy Admin                    |");
        printf("\n| \t 2.- Quiero adoptar               |");
        printf("\n| \t 3.- Soy un perrito               |");
        printf("\n| \t 0.- Me arrepenti y me quiero ir  |");
        printf("\n+-----------------------------------------+");
        printf("\n Elige la opcion correcta: ");
        scanf("%i", &opcion);

        if(opcion > 3 && opcion < 0)
        {
            printf("\n %i No es una opcion valida", opcion);
        }
    }
    while(opcion > 3 && opcion < 0);
    system("cls");
    return opcion;

}

void mostrarMenuAdmin()
{
    printf("\n Muestro el menu del admin");
}

void mostrarMenuAdoptante(Perrito lista[], int validos, char archivoSolicitudes[])
{
    int opcion;
    int idBuscar;
    int encontrado;

    do
    {
        printf("\n-----------------------------------------n");
        printf("\n|            MENU ADOPTANTE             |\n");
        printf("\n-----------------------------------------n");
        printf("\n| 1.- Ver listado de perritos (Todos)   |\n");
        printf("\n| 2.- Aplicar filtro                    |\n");
        printf("\n| 3.- Solicitar adopcion                |\n");
        printf("\n| 4.- Ver informacion de contacto       |\n");
        printf("\n| 0.- Volver al Menu Principal          |\n");
        printf("\n-----------------------------------------\n");
        printf("\n Elija una opcion:\n");
        scanf("%i", &opcion);

        switch(opcion)
        {
        case 1:
            printf("\n--- LISTADO COMPLETO DE PERRITOS ---");
            mostrarListadoPerritosRecursivo(lista, validos, 0);

            printf("\n�Desea ver el detalle de algun perrito? Ingrese el ID (0 para volver):\n");
            scanf("%i", &idBuscar);
            if(idBuscar != 0)
            {
                encontrado = 0;
                for(int i = 0; i < validos; i++)
                {
                    if(lista[i].idPerrito == idBuscar)
                    {
                        mostrarUnPerrito(lista[i]);
                        encontrado = 1;
                        break;
                    }
                }
                if(!encontrado) printf("\nNo se encontro el ID ingresado.\n");
            }
            break;

        case 2:
            filtrarPerritos(lista, validos);
            break;

        case 3:
            printf("\nIngrese el ID del perrito que desea adoptar: ");
            scanf("%i", &idBuscar);
            encontrado = 0;
            for(int i = 0; i < validos; i++)
            {
                if(lista[i].idPerrito == idBuscar)
                {
                    encontrado = 1;
                    if(lista[i].estado == DISPONIBLE)
                    {
                        cargarSolicitud(archivoSolicitudes);
                        lista[i].estado = ADOPTADO;
                    }
                    else
                    {
                        printf("\nLo sentimos, este perrito ya fue adoptado.\n");
                    }
                    break;
                }
            }
            if(!encontrado) printf("\nNo existe ningun perrito con ese ID.\n");
            break;

        case 4:
            printf("\n-----------------------------------------\n");
            printf("\n|     INFORMACION DE CONTACTO           |\n");
            printf("\n-----------------------------------------\n");
            printf("\n| Direccion:                            |\n");
            printf("\n| Telefono:                             |\n");
            printf("\n| Email:                                |\n");
            printf("\n-----------------------------------------\n");
            break;
        }
    }
    while(opcion != 0);
}
}

void cargarSolicitud(char nombreArchivo[])
{
    Solicitud aux;
    FILE *pf= fopen(nombreArchivo,  "ab");
    if(pf == NULL)
    {
        printf("\nNo se pudo abrir el archivo para cargar la solicitud");
    }
    else
    {
        aux = cargarSolicitudSimple();
        fwrite(&aux, sizeof(Solicitud),1, pf);
        fclose(pf);
    }
}

Solicitud cargarSolicitudSimple()
{
    Solicitud aux;

    printf("Cargue el ID del perrito: ");
    scanf("%d", &aux.idPerrito);
    fflush(stdin);
    printf("Cargue nombre del solicitante: ");
    gets(aux.solicitante);

    printf("Ingrese su email: ");
    gets(aux.email);

    printf("Ingrese su Telefono: ");
    gets(aux.tel);

    return aux;
}

Perrito cargarPerrito()
{
    Perrito aux;
    int op;
    printf("Cargue el ID del perrito: ");
    scanf("%d", &aux.idPerrito);
    printf("Cargue la edad del perrito: ");
    scanf("%d", &aux.edad);
    getchar();
    printf("Cargue el nombre del perrito: ");
    gets(aux.nombre);
    printf("Cargue la raza del perrito: ");
    gets(aux.raza);
    printf("Cargue fecha actual perrito: ");
    gets(aux.fechaIngreso);
    do
    {
        printf("Seleccione el porte (0-Chico, 1-Mediano, 2-Grande): ");
        scanf("%d", &op);
        if(op <0 || op>2)
        {
            printf("\nNo es una opcion valida,vuelva a intentarlo");
        }
    }
    while(op <0 || op>2);
    aux.porte = op;

    do
    {
        printf("Seleccione el genero (0-Macho, 1-Hembra): ");
        scanf("%d", &op);
        if(op <0 || op>1)
        {
            printf("\nNo es una opcion valida,vuelva a intentarlo");
        }
    }
    while(op <0 || op>1);
    aux.genero = op;

    do
    {
        printf("Seleccione el temperamento (0-Calmado, 1-Jugueton, 2-Ansioso, 3-Agresivo, 4-Sociable): ");
        scanf("%d", &op);
        if(op <0 || op>4)
        {
            printf("\nNo es una opcion valida,vuelva a intentarlo");
        }
    }
    while(op <0 || op>4);
    aux.temperamento = op;

    aux.estado = DISPONIBLE;

    return aux;
}


/// yo

void mostrarUnPerrito(Perrito perri)
{
    printf("\n---------------------------------\n");
    printf("\n  Ficha del perrito id %i", perri.idPerrito);
    printf("\n---------------------------------\n");
    printf("\n Nombre:%s\n", perri.nombre);
    printf("\n Edad:%i anos\n", perri.edad);
    printf("\n Raza:%s\n", perri.raza);
    printf("\n Genero:%s\n", generoTexto[perri.genero]);
    printf("\n Porte:%s\n", porteTexto[perri.porte]);
    printf("\n Temperamento:%s\n",temperamentoTexto[perri.temperamento]);
    printf("\n Estado:%s\n", estadoTexto[perri.estado]);
    printf("\n Ingreso:%s\n", perri.fechaIngreso);
    printf("\n---------------------------------\n");
}
void mostrarListadoPerritosRecursivo(Perrito lista[], int valido, int i)
{

    if (i < valido)
    {
        printf("\n[%i] ID: %i -%s %s, %s\n",
               i + 1,
               lista[i].idPerrito,
               lista[i].nombre,
               generoTexto[lista[i].genero],
               porteTexto[lista[i].porte]);

        mostrarListadoPerritosRecursivo(lista, valido, i + 1);
    }



    void filtrarPerritos(Perrito lista[], int validos)
    {
        int opcion;
        int criterio;
        int i = 0;
        printf("\n--- APLICAR FILTRO ---\n");
        printf("\n1. Por Edad\n2. Por Temperamento\n3. Por Genero\n4. Por Porte\nElija criterio: \n");
        scanf("%i", &opcion);

        switch(opcion)
        {
        case 1:
            printf("\nIngrese la edad exacta a buscar: \n");
            scanf("%i", &criterio);
            while( i<validos)
            {
                if(lista[i].edad == criterio)
                {
                    mostrarUnPerrito(lista[i]);
                    i++;
                }
            }
            break;
        case 2:
            printf("\nSeleccione (0-Calmado, 1-Jugueton, 2-Ansioso, 3-Agresivo, 4-Sociable):\n ");
            scanf("%i", &criterio);
            while( i<validos)
            {
                if(lista[i].temperamento == criterio)
                {
                    mostrarUnPerrito(lista[i]);
                    i++;
                }
            }
            break;
        case 3:
            printf("\nSeleccione (0-Macho, 1-Hembra): \n");
            scanf("%i", &criterio);
            while( i<validos)
            {
                if(lista[i].genero == criterio)
                {
                    mostrarUnPerrito(lista[i]);
                    i++;
                }
            }
            break;
        case 4:
            printf("\nSeleccione (0-Chico, 1-Mediano, 2-Grande):\n ");
            scanf("%i", &criterio);
            while( i<validos)
            {
                if(lista[i].porte == criterio)
                {
                    mostrarUnPerrito(lista[i]);
                    i++;
                }
            }
            break;
        }
        if(i == 0) printf("\nNo se encontraron perritos con el criterio seleccionado.\n");
    }
