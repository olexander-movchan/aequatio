#include <cmath>
#include <algorithm>
#include "EquationSystem.hpp"


namespace Aequatio
{

    EquationSystem::EquationSystem(double a, double b, double c, double d, double e, double f, double g, double h)
            : a(a), b(b), c(c), d(d), e(e), f(f), g(g), h(h)
    {

    }


    double EquationSystem::f1(double x1, double x2)
    {
        return std::sqrt(- (x1 * (b*x2 + c) + d) / a);
    }


    double EquationSystem::f2(double x1, double x2)
    {
        static const double ln10inv = 1.0 / std::log(10.0);
        return std::sqrt(- (e*x1 + f*std::log(x1)*ln10inv + h) / g);
    }


    EquationSystem::Results EquationSystem::JacobiMethod(double x1, double x2, double eps)
    {
        int iterations = 0;
        static const int ITERATION_OPS = 25;

        auto t_start = std::chrono::steady_clock::now();

        while (true)
        {
            ++iterations;
            double x1p = x1;
            double x2p = x2;

            x1 = f1(x1p, x2p);
            x2 = f2(x1p, x2p);

            if (std::max(std::abs(x1 - x1p), std::abs(x2 - x2p)) <= eps)
            {
                break;
            }
        }

        auto t_finish = std::chrono::steady_clock::now();

        return {
            x1, x2,
            iterations,
            iterations * ITERATION_OPS,
            t_finish - t_start
        };
    }


    EquationSystem::Results EquationSystem::GaussSeidelMethod(double x1, double x2, double eps)
    {
        int iterations = 0;
        static const int ITERATION_OPS = 25;

        auto t_start = std::chrono::steady_clock::now();

        while (true)
        {
            ++iterations;
            double x1p = x1;
            double x2p = x2;

            x1 = f1(x1, x2);
            x2 = f2(x1, x2);

            if (std::max(std::abs(x1 - x1p), std::abs(x2 - x2p)) <= eps)
            {
                break;
            }
        }

        auto t_finish = std::chrono::steady_clock::now();

        return {
                x1, x2,
                iterations,
                iterations * ITERATION_OPS,
                t_finish - t_start
        };
    }
}