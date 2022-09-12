#include <iostream>
#include "View.h"
#include "ReversiCore/Presenter.h"
#include "ReversiCore/Game.h"

int main()
{
    View v(8,8);
    Presenter p(v, Game(Array2D(Size(8,8)), StrategyFactory(), 2, 3, MoveCalculator()));
    p.play();
}
