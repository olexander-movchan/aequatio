#ifndef AEQUATIO_EQUATIONSYSTEM_HPP
#define AEQUATIO_EQUATIONSYSTEM_HPP


#include <chrono>


namespace Aequatio
{
    class EquationSystem
    {
    public:
        EquationSystem(double a, double b, double c, double d,
                       double e, double f, double g, double h);

        double f1(double x1, double x2);
        double f2(double x1, double x2);

        struct Results
        {
            double x1, x2;

            int iterations;
            int operations;

            std::chrono::duration<float> duration;
        };

        Results JacobiMethod(double x1, double x2, double eps = 1e-6);
        Results GaussSeidelMethod(double x1, double x2, double eps = 1e-6);

    private:
        double a, b, c, d;
        double e, f, g, h;
    };
}


#endif //AEQUATIO_EQUATIONSYSTEM_HPP
