[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/0yFiWenz)
[![Open in Codespaces](https://classroom.github.com/assets/launch-codespace-2972f46106e565e64193e422d61a12cf1da4916b45550586e14ef0a7c637dd04.svg)](https://classroom.github.com/open-in-codespaces?assignment_repo_id=21131780)
# Actividad Práctica: Simulador Genérico de Campo Gravitatorio 2D

## Definición del Problema a Resolver

Una agencia de astrofísica necesita una herramienta de bajo nivel para modelar y analizar campos de fuerza en un plano bidimensional. La magnitud de la fuerza o el potencial en cada punto de la cuadrícula puede variar y debe ser representada con la precisión adecuada (enteros para cálculos simplificados, flotantes o dobles para precisión científica).

El objetivo es construir una Clase Genérica llamada `Campo2D<T>` que gestione una **Matriz Dinámica 2D** ($M \times N$) donde cada celda almacena el valor de la magnitud física (campo gravitatorio, potencial eléctrico, etc.) en esa coordenada.

El sistema debe ser capaz de:

* Crear y liberar la matriz 2D de cualquier tipo numérico (`T`).
* Redimensionar el campo en tiempo de ejecución.
* Calcular el Gradiente Promedio de la magnitud en una región específica (submatriz).

---

## Temas Relacionados y Necesarios

Para resolver este problema, los alumnos deberán integrar los siguientes conocimientos:

| Tema Principal                                | Concepto a Aplicar                                                                                                                                                                                             |
| :-------------------------------------------- | :-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| Matrices Dinámicas 2D                         | Gestión de punteros dobles (`T**`) para la asignación, acceso y liberación de memoria de la cuadrícula física.                                                                                                  |
| Genericidad (Templates) en C++                | Definición de una Clase Genérica (`Campo2D<T>`) que opera con tipos `int`, `float`, `double`, sin modificar el código fuente.                                                                                  |
| Programación Orientada a Objetos (POO)        | Encapsulamiento de la matriz y sus dimensiones dentro de una clase, incluyendo constructor y destructor.                                                                                                        |
| Cálculo Físico (Gradiente)                    | Abstracción del concepto matemático de Gradiente (tasa de cambio) mediante el cálculo de la diferencia promedio entre valores adyacentes.|

---

## Definición y Detalles del Proceso a Desarrollar

### Estructura de la Clase y Atributos

```C++
template <typename T>
class Campo2D {
private:
    T **_datos;
    int _filas;
    int _columnas;

public:
    Campo2D(int f, int c); // Constructor
    ~Campo2D(); // Destructor
    void redimensionar(int nuevaF, int nuevaC);
    void setValor(int f, int c, T valor);
    T calcularGradientePromedio(int inicioF, int finF, int inicioC, int finC);
    // ... otros métodos
};
```

---

### Proceso de Solución Detallado

1. **Asignación y Destrucción Genérica**:
    * El constructor debe asignar memoria para la matriz 2D (`_datos`) utilizando punteros dobles y el tipo genérico `T`.
    * El destructor debe liberar la memoria de manera segura (liberando columnas primero, luego filas).
2. **Redimensión de la Matriz**: El método `redimensionar(nuevaF, nuevaC)` es crítico:
    * Debe crear una nueva matriz temporal (`T**`) con las nuevas dimensiones.
    * Copiar los datos de la matriz antigua a la nueva, conservando solo los elementos dentro del rango mínimo.
    * Liberar la memoria de la matriz antigua antes de asignar la nueva.
3. **Cálculo del Gradiente Promedio**: El método `calcularGradientePromedio(...)` debe realizar lo siguiente:
    * Validar que la submatriz (definida por los parámetros inicio/fin) esté dentro de los límites del `_grid`.
    * Recorrer cada celda interna de la submatriz.
    * Para cada celda, calcular la diferencia absoluta promedio respecto a sus dos vecinos directos (ej., el valor promedio de `|valor[i+1][j] - valor[i][j]|` y `|valor[i][j+1] - valor[i][j]|`).
    * Sumar estas diferencias y devolver el promedio total de todos los puntos dentro de la submatriz.

---

## Requerimientos Funcionales y No Funcionales

### Requisitos Funcionales

* **Clase Genérica**: Implementar la clase `Campo2D<T>` probando la instanciación con `Campo2D<int>`, `Campo2D<double>`  y `Campo2D<float>` en el `main`.
* **Redimensión Dinámica**: El método `redimensionar` debe funcionar correctamente, copiando datos y liberando memoria.
* **Operación Central**: Implementar la función `calcularGradientePromedio` con validación de límites.
* **Acceso Seguro**: Implementar un método para asignar (`setValor`) y obtener (`getValor`) valores de una celda, validando los índices.

### Requisitos No Funcionales

* **Control de Memoria**: Prohibido el uso de la STL (`std::vector`, `std::array`). La gestión debe ser manual con `new` y `delete`.
* **Implementación POO y Templates**: La solución debe estar completamente encapsulada dentro de la clase genérica.
* **Robustez**: Manejar casos de índices fuera de rango y la validación de las dimensiones de la submatriz para el cálculo del gradiente.

---

## Ejemplo de Entradas y Salidas del Problema en Consola

### Simulación de Interacción


```bash
--- Simulador Genérico de Campo 2D ---

>> Inicializando Campo Gravitatorio (Tipo FLOAT) <<
Creando Grid (FLOAT) de 3x3...
Estableciendo valores iniciales...

Grid Actual (Paso 0):
| 10.0 | 8.0 | 5.0 |
| 12.0 | 9.0 | 6.0 |
| 15.0 | 11.0 | 7.0 |

Opción: Calcular Gradiente Promedio
Ingrese Fila Inicial: 0, Fila Final: 2
Ingrese Columna Inicial: 0, Columna Final: 2

Calculando Gradiente Promedio en la región [0,2]x[0,2]...
Gradiente Promedio calculado: 2.16667 unidades/metro.

Opción: Redimensionar
Redimensionando Grid a 4x4...
Datos copiados. Memoria antigua liberada.

Opción: Redimensionar (A una dimensión menor)
Redimensionando Grid a 2x2...
Datos copiados. Memoria antigua liberada.

Opción: Salir
Destructor invocado. Liberando memoria de la Matriz 2D...
Sistema cerrado.
```

---

## Temas Adicionales de Investigación Necesarios

Para llevar a cabo esta actividad con éxito, el alumno deberá investigar a fondo:

1. **Regla de los Tres (o Cinco) en C++**: Es vital entender por qué es necesario implementar el Constructor de Copia, el Operador de Asignación y el Destructor para la clase` Campo2D<T>` que contiene punteros, y cómo se aplican las plantillas a esta regla.
2. **Concepto de Gradiente (Matemáticas)**: Entender que el gradiente es una medida de la tasa de cambio de un campo escalar. La versión simplificada aquí usa promedios de diferencias absolutas.
3. **Sobrecarga del Operador de Acceso** `[]`: Cómo sobrecargar el operador de corchetes (`[]`) en la clase `Campo2D<T>` para permitir la sintaxis de acceso intuitiva `campo[i][j]`, aunque se esté trabajando con punteros dobles.
