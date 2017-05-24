#ifndef AEQUATIO_EQUATIONSYSTEM_HPP
#define AEQUATIO_EQUATIONSYSTEM_HPP


#include <chrono>


namespace Aequatio
{
    class EquationSystem
    {
    public:
        /**
         * @brief Constructor with coefficients
         */
        EquationSystem(double a, double b, double c, double d,
                       double e, double f, double g, double h);

        /**
         * @brief Contraction mapping for first argument
         *
         * Calculates next approximation for x1.
         *
         * @param x1 x1^(k)
         * @param x2 x2^(k)
         * @return x1^(x+1)
         */
        double f1(double x1, double x2);

        /**
         * @brief Contraction mapping for second argument
         *
         * Calculates next approximation for x2.
         *
         * @param x1 x1 (k)
         * @param x2 x2 (k)
         * @return x1 (x+1)
         */
        double f2(double x1, double x2);

        struct Results
        {
            double x1, x2;

            int iterations;
            int operations;

            std::chrono::duration<float> duration;
        };

        /**
         * @brief Simple iterative (Jacobi) method
         * @param x1 Initial x1 value
         * @param x2 Initial x2 value
         * @param eps Tolerance
         * @return result object (solution & statistics)
         */
        Results JacobiMethod(double x1, double x2, double eps = 1e-6);

        /**
         * @brief Gauss-Seidel method
         * @param x1 Initial x1 value
         * @param x2 Initial x2 value
         * @param eps Tolerance
         * @return result object (solution & statistics)
         */
        Results GaussSeidelMethod(double x1, double x2, double eps = 1e-6);

    private:
        double a, b, c, d;
        double e, f, g, h;
    };
}


#endif //AEQUATIO_EQUATIONSYSTEM_HPP
