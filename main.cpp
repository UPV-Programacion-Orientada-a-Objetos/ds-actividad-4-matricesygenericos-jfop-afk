#include <iostream>

template <typename T>
class Campo2D {
private:
    T **_datos;
    int _filas;
    int _columnas;

    void liberarMemoria();

public:
    Campo2D(int f, int c);
    ~Campo2D();

    T getValor(int f, int c) const;
    void setValor(int f, int c, T valor);

    void redimensionar(int nuevaF, int nuevaC);

    double calcularGradientePromedio(int inicioF, int finF, int inicioC, int finC);
};

template <typename T>
void Campo2D<T>::liberarMemoria() {
    if (_datos != NULL) {
        for (int i = 0; i < _filas; ++i) {
            delete[] _datos[i];
        }
        delete[] _datos;
        _datos = NULL;
    }
}

template <typename T>
Campo2D<T>::Campo2D(int f, int c) : _filas(f), _columnas(c), _datos(NULL) {
    _datos = new T*[f];
    for (int i = 0; i < f; ++i) {
        _datos[i] = new T[c];
        for (int j = 0; j < c; ++j) {
            _datos[i][j] = T();
        }
    }
}

template <typename T>
Campo2D<T>::~Campo2D() {
    std::cout << "Liberando memoria..." << std::endl;
    this->liberarMemoria();
}

template <typename T>
T Campo2D<T>::getValor(int f, int c) const {
    if (f >= 0 && f < _filas && c >= 0 && c < _columnas) {
        return _datos[f][c];
    }
    std::cout << "ADVERTENCIA: Indice (" << f << ", " << c << ") fuera de rango. Devolviendo valor por defecto." << std::endl;
    return T();
}

template <typename T>
void Campo2D<T>::setValor(int f, int c, T valor) {
    if (f >= 0 && f < _filas && c >= 0 && c < _columnas) {
        _datos[f][c] = valor;
    } else {
        std::cout << "ADVERTENCIA: Indice (" << f << ", " << c << ") fuera de rango. No se pudo establecer el valor." << std::endl;
    }
}

template <typename T>
void Campo2D<T>::redimensionar(int nuevaF, int nuevaC) {
    if (nuevaF <= 0 || nuevaC <= 0) {
        std::cout << "ERROR: Las nuevas dimensiones deben ser positivas." << std::endl;
        return;
    }

    T** nueva_datos = new T*[nuevaF];
    for (int i = 0; i < nuevaF; ++i) {
        nueva_datos[i] = new T[nuevaC];
    }

    int minF = (_filas < nuevaF) ? _filas : nuevaF;
    int minC = (_columnas < nuevaC) ? _columnas : nuevaC;

    for (int i = 0; i < nuevaF; ++i) {
        for (int j = 0; j < nuevaC; ++j) {
            if (i < minF && j < minC) {
                nueva_datos[i][j] = _datos[i][j];
            } else {
                nueva_datos[i][j] = T();
            }
        }
    }

    this->liberarMemoria();

    _datos = nueva_datos;
    _filas = nuevaF;
    _columnas = nuevaC;

    std::cout << "Datos copiados. Memoria antigua liberada." << std::endl;
}

template <typename T>
double Campo2D<T>::calcularGradientePromedio(int inicioF, int finF, int inicioC, int finC) {

    if (inicioF < 0 || inicioC < 0 || finF >= _filas || finC >= _columnas || inicioF > finF || inicioC > finC) {
        std::cout << "ERROR: Rangos de submatriz invalidos o fuera de los limites del Grid (" << _filas << "x" << _columnas << ")." << std::endl;
        return 0.0;
    }

    double suma_diferencias = 0.0;
    int contador_gradientes = 0;

    for (int i = inicioF; i <= finF; ++i) {
        for (int j = inicioC; j <= finC; ++j) {

            if (j + 1 <= finC) {
                double diff = (double)_datos[i][j + 1] - (double)_datos[i][j];
                double diff_h;
                if (diff < 0) {
                    diff_h = -diff;
                } else {
                    diff_h = diff;
                }
                suma_diferencias += diff_h;
                contador_gradientes++;
            }

            if (i + 1 <= finF) {
                double diff = (double)_datos[i + 1][j] - (double)_datos[i][j];
                double diff_v;
                if (diff < 0) {
                    diff_v = -diff;
                } else {
                    diff_v = diff;
                }
                suma_diferencias += diff_v;
                contador_gradientes++;
            }
        }
    }

    if (contador_gradientes == 0) {
        return 0.0;
    }

    return suma_diferencias / contador_gradientes;
}

void imprimirCampoFloat(Campo2D<float>& campo) {
    std::cout << "\nGrid Actual (Paso 0):" << std::endl;
    for (int i = 0; i < 3; ++i) {
        std::cout << "|";
        for (int j = 0; j < 3; ++j) {
            std::cout.width(5);
            std::cout.precision(1);
            std::cout << std::fixed << campo.getValor(i, j) << " ";
        }
        std::cout << "|" << std::endl;
    }
}

int main() {

    std::cout << "--- Simulador Generico de Campo 2D ---" << std::endl;
    std::cout << ">> Inicializando Campo Gravitatorio <<" << std::endl;

    Campo2D<float> campoFloat(3, 3);
    std::cout << "Creando Grid de 3x3..." << std::endl;

    campoFloat.setValor(0, 0, 10.0f); campoFloat.setValor(0, 1, 8.0f); campoFloat.setValor(0, 2, 5.0f);
    campoFloat.setValor(1, 0, 12.0f); campoFloat.setValor(1, 1, 9.0f); campoFloat.setValor(1, 2, 6.0f);
    campoFloat.setValor(2, 0, 15.0f); campoFloat.setValor(2, 1, 11.0f); campoFloat.setValor(2, 2, 7.0f);
    std::cout << "Estableciendo valores iniciales..." << std::endl;

    imprimirCampoFloat(campoFloat);

    int iF = 0, fF = 2, iC = 0, fC = 2;
    double gradiente = campoFloat.calcularGradientePromedio(iF, fF, iC, fC);

    std::cout.precision(5);
    std::cout << "\nOpción: Calcular Gradiente Promedio" << std::endl;
    std::cout << "Ingrese Fila Inicial: 0, Fila Final: 2" << std::endl;
    std::cout << "Ingrese Columna Inicial: 0, Columna Final: 2" << std::endl;
    std::cout << "Calculando Gradiente Promedio en la region [" << iF << "," << fF << "]x[" << iC << "," << fC << "]..." << std::endl;
    std::cout << "Gradiente Promedio calculado: " << gradiente << " unidades/metro." << std::endl;

    std::cout << "\nOpción: Redimensionar" << std::endl;
    std::cout << "Redimensionando Grid a 4x4..." << std::endl;
    campoFloat.redimensionar(4, 4);

    std::cout << "\nOpción: Redimensionar (A una dimension menor)" << std::endl;
    std::cout << "Redimensionando Grid a 2x2..." << std::endl;
    campoFloat.redimensionar(2, 2);

    std::cout << "\n>> Demostracion de Genericidad (Tipo INT) <<" << std::endl;
    Campo2D<int> campoInt(2, 2);
    std::cout << "Creando Campo de Potencial (INT) de 2x2..." << std::endl;
    campoInt.setValor(0, 0, 100);
    campoInt.setValor(0, 1, 50);
    campoInt.setValor(1, 0, 120);
    campoInt.setValor(1, 1, 60);

    double gradienteInt = campoInt.calcularGradientePromedio(0, 1, 0, 1);
    std::cout << "Gradiente Promedio (INT) en 2x2: " << gradienteInt << std::endl;

    std::cout << "\n>> Demostracion de Genericidad (Tipo DOUBLE) <<" << std::endl;
    Campo2D<double> campoDouble(1, 4);
    std::cout << "Creando Campo de Densidad (DOUBLE) de 1x4..." << std::endl;
    campoDouble.setValor(0, 0, 1.2345);
    campoDouble.setValor(0, 1, 1.2300);
    campoDouble.setValor(0, 2, 1.2500);
    campoDouble.setValor(0, 3, 1.2450);

    double gradienteDouble = campoDouble.calcularGradientePromedio(0, 0, 0, 3);
    std::cout << "Gradiente Promedio (DOUBLE) en 1x4: " << gradienteDouble << std::endl;

    std::cout << "\nOpción: Salir" << std::endl;

    return 0;
}
