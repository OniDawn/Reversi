#include "Reversi.h"
#include "ReversiCore/StrategyFactory.h"
#include <QtWidgets/QApplication>
#include "ReversiCore/Presenter.h"


int main(int argc, char *argv[])
{
    std::srand(std::time(nullptr));

    QApplication app(argc, argv);
    Reversi view;
    Game game(Array2D(Size(8, 8)), StrategyFactory(), MoveCalculator());

    Presenter presenter(view, game);
    presenter.initializeGame();


    view.show();
    return app.exec();
}
