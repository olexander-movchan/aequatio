#include <iostream>
#include "MainWindow.hpp"
#include "EquationSystem.hpp"


namespace Aequatio
{

    MainWindow::MainWindow(BaseObjectType *cobject, const Glib::RefPtr<Gtk::Builder> &builder) : Gtk::Window(cobject)
    {
        Gtk::MenuItem *menu_quit, *menu_about;
        builder->get_widget("Menu.Quit", menu_quit);
        builder->get_widget("Menu.About", menu_about);

        menu_quit->signal_activate().connect(sigc::mem_fun(*this, &MainWindow::close));

        Gtk::Button *button_compute;
        builder->get_widget("Button.Compute", button_compute);
        button_compute->signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::compute));

        builder->get_widget("Dialog.WrongFormat", dialogs.wrong_format);
        builder->get_widget("Dialog.NoSolution", dialogs.no_solution);
        builder->get_widget("Dialog.About", dialogs.about);

        menu_about->signal_activate().connect(sigc::mem_fun(*(dialogs.about), &Gtk::Dialog::show));

        builder->get_widget("Entry.A", parameters.a);
        builder->get_widget("Entry.B", parameters.b);
        builder->get_widget("Entry.C", parameters.c);
        builder->get_widget("Entry.D", parameters.d);
        builder->get_widget("Entry.E", parameters.e);
        builder->get_widget("Entry.F", parameters.f);
        builder->get_widget("Entry.G", parameters.g);
        builder->get_widget("Entry.H", parameters.h);

        builder->get_widget("Entry.X1", parameters.x1);
        builder->get_widget("Entry.X2", parameters.x2);
        builder->get_widget("Entry.Epsilon", parameters.eps);

        builder->get_widget("Jacobi.Solution", jacobi.solution);
        builder->get_widget("Jacobi.Iterations", jacobi.iterations);
        builder->get_widget("Jacobi.Operations", jacobi.operations);
        builder->get_widget("Jacobi.Time", jacobi.time);

        builder->get_widget("Seidel.Solution", seidel.solution);
        builder->get_widget("Seidel.Iterations", seidel.iterations);
        builder->get_widget("Seidel.Operations", seidel.operations);
        builder->get_widget("Seidel.Time", seidel.time);
    }

    int MainWindow::Start(int argc, char **argv)
    {
        auto gtkapp = Gtk::Application::create(argc, argv);
        auto builder = Gtk::Builder::create();

        try
        {
            builder->add_from_file("../AequatioUI.glade");
        }
        catch (Glib::FileError)
        {
            std::clog << "Unable to open open file: ../AequatioUI.glade" << std::endl;
            return 1;
        }

        MainWindow *main_window;
        builder->get_widget_derived("Window.Main", main_window);

        return gtkapp->run(*main_window);
    }


    void MainWindow::compute()
    {
        double a, b, c, d;
        double e, f, g, h;
        double x1, x2, eps;

        try
        {
            a = std::stod(parameters.a->get_text());
            b = std::stod(parameters.b->get_text());
            c = std::stod(parameters.c->get_text());
            d = std::stod(parameters.d->get_text());
            e = std::stod(parameters.e->get_text());
            f = std::stod(parameters.f->get_text());
            g = std::stod(parameters.g->get_text());
            h = std::stod(parameters.h->get_text());

            x1 = std::stod(parameters.x1->get_text());
            x2 = std::stod(parameters.x2->get_text());
            eps = std::stod(parameters.eps->get_text());
        }
        catch (std::invalid_argument)
        {
            dialogs.wrong_format->show();
            return;
        }

        eps = std::pow(0.1, eps);

        auto system = EquationSystem(a, b, c, d, e, f, g, h);

        auto j = system.JacobiMethod(x1, x2, eps);
        auto s = system.GaussSeidelMethod(x1, x2, eps);

        jacobi.solution->set_text(std::string("(") + std::to_string(j.x1) + ", " + std::to_string(j.x2) + ")");
        jacobi.iterations->set_text(std::to_string(j.iterations));
        jacobi.operations->set_text(std::to_string(j.operations));
        jacobi.time->set_text(std::to_string(int(j.duration.count() * 1000)));

        seidel.solution->set_text(std::string("(") + std::to_string(s.x1) + ", " + std::to_string(s.x2) + ")");
        seidel.iterations->set_text(std::to_string(s.iterations));
        seidel.operations->set_text(std::to_string(s.operations));
        jacobi.time->set_text(std::to_string(int(s.duration.count() * 1000)));
    }
}