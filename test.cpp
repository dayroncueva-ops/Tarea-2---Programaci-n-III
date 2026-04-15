#include "core_numeric.h"
using namespace std;
using namespace core_numeric;


struct Coordenadas2D {
    double x, y;

    // Hacemos sobrecarga de operadores

    Coordenadas2D operator+(const Coordenadas2D& other) const {
        return {x + other.x, y + other.y};
    }

    Coordenadas2D operator-(const Coordenadas2D& other) const {
        return {x - other.x, y - other.y};
    }

    Coordenadas2D operator/(std::size_t n) const {
        return {x / n, y / n};
    }

    Coordenadas2D operator*(const Coordenadas2D& other) const {
        return {x * other.x, y * other.y};
    }

    bool operator==(const Coordenadas2D& other) const {
        return x == other.x && y == other.y;
    }
};

int main() {

    // CASOS QUE COMPILA

    // double COMPILA
    std::vector<double> vd{1.0,2.0,3.0}; // compila porque mean espera output DOUBLE [ ->
    std::cout << "Mean double: " << core_numeric::mean(vd) << "\n";
    std::cout << "Variance double: " << core_numeric::variance(vd) << "\n";

    // Usando objeto de clase propia
    vector<Coordenadas2D> vp{{1,2},{3,4},{5,6}};
    auto mp = core_numeric::mean(vp); //tiene operator+,-,/, y cumple el requisito de / porque siempre hacemos q devuelva el mismo objeto
    // aqui: Coordenadas2D operator/(std::size_t n)
    cout << "Mean Coordenada: (" << mp.x << "," << mp.y << ")\n";
    // comparación
    Coordenadas2D p1{1,2}, p2{1,2};
    if (p1 == p2) {
        std::cout << "Las coordenadas son  iguales\n";
    }

    vector <double> data {1, 2.7 , 0.3};
    auto v = core_numeric :: max ( data );
    cout<<"El mayor valor de data es:"<<v<<endl;
    auto r = core_numeric :: transform_reduce (data, []( double x) {
        return x*x;
    });
    cout<<r;
    cout<<"\n------------------------\n";

    auto s1 = core_numeric :: sum_variadic (1 ,2 ,33 ,4);
    auto s2 = core_numeric :: mean_variadic (0.1 ,2 ,3 ,4);
    auto s3 = core_numeric :: variance_variadic (1 ,2 ,3 ,4);
    auto s4 = core_numeric :: max_variadic (1 ,2.7 ,3 ,4);
    cout<<s1<<endl;
    cout<<s2<<endl;
    cout<<s3<<endl;
    cout<<s4<<endl;
    vector<int> vec{1,2,3,4};
    cout<<core_numeric::mean(vec);



    // NO COMPILA
    // int :NO COMPILA (en el caso de usar same_as en lugar de convertible_to en Divisible)
    /*std::vector<int> vi{1,2,3};
    cout << "Mean int: " << mean(vi) << "\n"; // se ingresa variables tipo INT, dbee retornar INT, pero en Divisable no esta garantizado q el output siempre sea int
    // ejemplo: 1 + 2 + 4 -> 7 / 3 != int [falla]
    cout << "Variance int: " << variance(vi) << "\n";


    // string: NO COMPILA
    vector<string> vk{"dayron","axel","antony","edson"}; // no se puede dividir un string (falla)
    cout<< "Mean string: " << mean(vk) << "\n";
    */


    //max no compila porque no satisface el require Numeric
    /*
        std :: vector <std :: string > data {"a", "b", "c"};
        auto v = core_numeric :: max ( data );
        // ERROR : std :: string no debe cumplir con el concept
    }
    */


    // transform_reduce incompatible
    /*
    vector<string> vs5{"a","bb"};
    transform_reduce(vs5, [](string s){
        return s.size();
    });
    */

    // Usamos objetos para prueba de funcionalidad
    // Tipo sin +
    struct SinSuma {
        int x;
    };
    /*
    vector<SinSuma> vs3{{1},{2}};
    auto s = sum(vs3); // no compila porque no existe operator+ y Addable espera saber sumarse con otro objeto del mismo tipo
    */

    // Tipo sin /
    struct SinDivision {
        int x;

        SinDivision operator+(const SinDivision& other) const {
            return {x + other.x};
        }
    };
    /*
    std::vector<SinDivision> vs4{{1},{2}};
    auto m2 = mean(vs4); // no existe operador / entonces a pesar de tener operator+, internamente se va tratar de dividir con objeto del mismo tipo pero falla porque no está definido
    */


    /*
    // Caso en Iterable
    int x = 10;
    auto m3 = mean(x); // no compila porque no tiene begin end, restriccion necesaria en Iterable
    */

    return 0;
}
