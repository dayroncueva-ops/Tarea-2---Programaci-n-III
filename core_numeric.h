#include <complex>
#include <concepts>
#include <iostream>
#include <vector>
#include <string>
#include <iterator>

namespace core_numeric {

// Agregamos los Concept del problema

// Tarea 1

    // Iterable
    template<typename C>
    concept Iterable = requires(C c) {
        std::begin(c);
        std::end(c);
    };

    // Addable
    template<typename T>
    concept Addable = requires(T a, T b) {
        { a + b } -> std::same_as<T>;
    };

    // Divisible
    template<typename T>
    concept Divisible = requires(T a, std::size_t n) {
        { a / n } -> std::convertible_to<T>; //cambiamos el same_as por convertible_to para que compile cuando el resultado de una divisón de int sea double
    };

    // Concept propio
    template<typename T>
    concept Resta = requires(T a, T b) {
        { a - b } -> std::same_as<T>;
    };


    // suma
    template<Iterable C>
    requires Addable<typename C::value_type> // restringimos a que el contenedor C cumpla con las condiciones de Addable
    auto sum(const C& container) {
        using T = typename C::value_type; // si por ejemplo nuestro C es vector de interos, T debe ser un entero
        T result{}; // inicializamos por defecto dependiendo del tipo
        for (const auto& x : container) {
            result = result + x;
        }
        return result; // si es container es string, el output es una string concatenado
    }



// Tarea 2: MEAN

    template<Iterable C>
    requires Addable<typename C::value_type> && Divisible<typename C::value_type>
    // como ahora requiere de las condiciones de Divisible, un contenedor con variable de tipo string NO COMPILARIA
    auto mean(const C& container) {
        using T=typename C::value_type;
        auto total = sum(container); // aplicamos la funcion anterior
        //Usamos de constexpr como lo pide la pregunta 7
        if constexpr (std::is_integral_v<T>) {
            // evitar división entera
            return static_cast<double>(total) / container.size();
        } else {
            // flotantes
            return total / container.size();
        }
    }


    // Tarea 3: VARIANCE

    template<Iterable C>
    requires Addable<typename C::value_type> && Resta<typename C::value_type>
    auto variance(const C& container) {
        using T = typename C::value_type;

        auto m = mean(container);
        T result{};

        for (const auto& x : container) {
            T diff = x - m;
            result+= diff * diff;
        }

        return result / container.size();
    }

    //Tarea 4
    //Creamos un concept para verificar numeros
    template<typename T>
    concept Numeric=std::is_arithmetic_v<T>;

    template<Iterable C>
    requires Numeric<typename C::value_type>
    auto max(const C& container) {
        using T = typename C::value_type;
        auto it = std::begin(container);
        T mayor = *it;
        ++it;
        for (; it != std::end(container); ++it)
            if (*it > mayor)
                mayor = *it;

        return mayor;
    }


    //Tarea 5
    template <Iterable C, typename F>
    requires requires(typename C::value_type x, F f) {
        f(x);
        f(x) + f(x);
    }
    auto transform_reduce(const C& container, F func) {
        auto it = std::begin(container);
        using R = decltype(func(*it)); //
        R result{};
        for (const auto& iter : container)
            result += func(iter);
        return result;
    }

    //Tarea 6
    //sum_variadic
    template<typename... T>
    requires (std::is_arithmetic_v<T> && ...)
    auto sum_variadic(T... args) {
        return (args + ...);
    }
    //mean_variadic
    template<typename... T>
    requires (std::is_arithmetic_v<T> && ...)
    auto mean_variadic(T... args) {
        return (args + ...) / sizeof...(args);
    }
    //variance_variadic
    template<typename ... T>
    requires (std::is_arithmetic_v<T> && ...)
    auto variance_variadic(T ... args) {
        auto mean=(args + ...)/sizeof...(args);
        return(((args-mean)*(args-mean))+...)/sizeof ...(args);
    }
    template<typename... Ts>
    requires (std::is_arithmetic_v<Ts> && ...)
    auto max_variadic(Ts... args) {
        using T = std::common_type_t<Ts...>;
        T max_val = std::numeric_limits<T>::lowest();
        ((max_val = args > max_val ? args : max_val), ...);
        return max_val;
    }

}
