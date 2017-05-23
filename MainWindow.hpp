#ifndef AEQUATIO_MAINWINDOW_HPP
#define AEQUATIO_MAINWINDOW_HPP


#include <gtkmm.h>


namespace Aequatio
{
    class MainWindow : public Gtk::Window
    {
    public:
        MainWindow(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder> &builder);

        /**
         * @brief GUI entry point
         * @param argc number of program arguments
         * @param argv program arguments
         * @return exist status code
         */
        static int Start(int argc, char **argv);

    private:
        struct
        {
            Gtk::Entry *a, *b, *c, *d;
            Gtk::Entry *e, *f, *g, *h;

            Gtk::Entry *x1, *x2, *eps;
        } parameters;

        struct
        {
            Gtk::Dialog *wrong_format;
            Gtk::Dialog *no_solution;
            Gtk::Dialog *about;
        } dialogs;

        struct
        {
            Gtk::Label *solution;
            Gtk::Label *iterations;
            Gtk::Label *operations;
            Gtk::Label *time;
        } jacobi, seidel;

        void compute();
    };
}


#endif //AEQUATIO_MAINWINDOW_HPP
