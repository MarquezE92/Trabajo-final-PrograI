# Trabajo Práctico Final - Programación 1

## UTN – Facultad Regional Mar del Plata

### Tecnicatura Universitaria en Programación (TUP)

---

# Introducción y Fundamentación

El objetivo principal de este trabajo es integrar los conocimientos adquiridos en la materia **Programación 1**.

Los estudiantes deberán formar grupos de **mínimo tres (3)** y **máximo cuatro (4)** integrantes para desarrollar un sistema que administre al menos **dos estructuras de datos**, asegurando la persistencia de las mismas mediante **archivos binarios**.

El valor pedagógico de esta propuesta se fundamenta en el aprendizaje colaborativo a través del desarrollo de un proyecto de software. Este enfoque favorece el logro de los objetivos de aprendizaje propuestos, desarrollando competencias profesionales y preparando al futuro programador para el ámbito laboral y el trabajo en equipo.

## Aprendizaje Colaborativo

En un entorno de aprendizaje colaborativo, los estudiantes:

* Construyen conocimiento de manera activa en lugar de recibirlo pasivamente.
* Se involucran y comprometen directamente con el descubrimiento de nuevo conocimiento.
* Se exponen a puntos de vista alternativos e ideas contrapuestas, permitiéndoles sacar conclusiones propias y transformar conocimientos y experiencias previas para una comprensión más profunda.
* Transfieren conocimientos y habilidades a nuevas situaciones o circunstancias.
* Se responsabilizan y apropian tanto de su aprendizaje continuo de contenidos curriculares como del desarrollo de competencias propias.
* Colaboran para el aprendizaje del grupo y el grupo colabora en el aprendizaje individual de cada integrante.

---

# Objetivos

## Objetivos de Aprendizaje

* Integrar todos los contenidos aprendidos en la materia:

  * Pilas
  * Arreglos estáticos y dinámicos
  * Matrices
  * Strings
  * Modularización
  * Estructuras de datos
  * Archivos binarios
  * Punteros simples y dobles
  * Recursividad
* Trabajar de manera colaborativa.

## Objetivos Metodológicos

* Ser capaces de trabajar en un proyecto complejo aplicando técnicas de desarrollo de software.
* Integrar contenidos de otras asignaturas.
* Presentar avances del trabajo durante las clases.

---

# Modo de Evaluación

* Se establecerá una fecha límite de entrega según la planificación de cada comisión.
* La aprobación de este trabajo es obligatoria para aprobar la materia.
* La evaluación se realizará según los siguientes criterios:

| Apartado                                           | Puntaje        |
| -------------------------------------------------- | -------------- |
| Funciones ABMCL de las estructuras de datos        | 35 puntos      |
| Manejo de archivos binarios y persistencia         | 35 puntos      |
| Main, modularización, reutilización y presentación | 30 puntos      |
| **Total**                                          | **100 puntos** |

## Funciones ABMCL (35 puntos)

* Alta
* Baja
* Modificación
* Consulta
* Listados
* Validación de datos ingresados
* Búsqueda de información en archivos

## Manejo de Archivos Binarios (35 puntos)

* Persistencia de datos
* Gestión de la información almacenada

## Main y Organización General (30 puntos)

* Correcta modularización
* Correcto uso de parámetros
* Orden y prolijidad del código
* Reutilización de funciones
* Comentarios descriptivos en cada función
* Explicación presencial del sistema

---

# Pautas Generales

* El código debe compilar sin errores.
* El sistema deberá ser presentado y explicado presencialmente.

---

# Requisitos Mínimos del Trabajo

## Sistema

Cada equipo desarrollará un sistema completo que resuelva una problemática a elección.

El equipo podrá decidir:

* Qué aspectos resolver.
* Cómo resolverlos.
* Qué funcionalidades adicionales incorporar.

## Estructuras de Datos

Como mínimo deberán utilizarse:

* Dos (`2`) estructuras (`struct`) diferentes.
* Persistencia de todas las estructuras en archivos binarios.

## Recursos Obligatorios

El sistema deberá utilizar al menos:

* Una pila.
* Un arreglo dinámico de estructuras.
* Un arreglo estático de estructuras.
* Strings.
* Una matriz o un arreglo de palabras.

La elección de cada estructura deberá estar justificada según la funcionalidad implementada.

---

# Operaciones ABMCL Obligatorias

Las siguientes operaciones deberán implementarse para cada una de las estructuras principales del sistema.

## Alta

* Carga de datos.
* Validación para evitar registros duplicados.
* Guardado en archivo.

## Baja

* Búsqueda del registro.
* Eliminación del dato.
* Actualización del archivo.

## Modificación

* Búsqueda del registro.
* Modificación de datos.
* Guardado de cambios.

## Consulta

Búsqueda de un registro específico utilizando uno o más criterios definidos por el usuario.

Ejemplo:

* Buscar un empleado por DNI.
* Buscar un producto por código.
* Buscar un alumno por legajo.

## Listados

### Ordenamiento Alfabético

Listado completo ordenado mediante el método de **Selección**.

### Ordenamiento Numérico

Listado completo ordenado mediante el método de **Inserción**.

### Listados Filtrados (Opcional)

Ejemplos:

* Productos de una categoría determinada.
* Alumnos con notas entre 6 y 8.
* Clientes activos.

---

# Menús del Sistema

El sistema deberá incluir:

* Menú principal.
* Submenús necesarios.
* Acceso a todas las funcionalidades implementadas.
* Navegación clara e intuitiva.

---

# Funcionalidades Opcionales

Además de las operaciones ABMCL obligatorias, cada grupo podrá incorporar funcionalidades adicionales relacionadas con la temática elegida para enriquecer el sistema.
