#include <QtCore/QCoreApplication>
#include <QtWidgets/QApplication>
#include "View.h"
#include "ReversiCore/Game.h"
#include "ReversiCore/Presenter.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    std::srand(std::time(nullptr));

    View view;
    Game game(Array2D(Size(8, 8)));

    Presenter presenter(view, game);
    presenter.simulateAllAgainstAll(3);


    return a.exec();
}
