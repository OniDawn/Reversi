#pragma once
#include <QtWidgets/QMainWindow>
#include "ui_Reversi.h"
#include "ReversiCore/ViewInterface.h"
#include "Renderer.h"
#include <QPoint>
#include <QImage>
#include <vector>

QT_BEGIN_NAMESPACE
namespace Ui { class ReversiClass; };
QT_END_NAMESPACE

/// @brief View of the GUI
class Reversi : public virtual QMainWindow, public virtual ViewInterface
{
    Q_OBJECT

public:
    
    Reversi(QWidget *parent = nullptr);

    ~Reversi();

    /// @brief draws the game board
    void drawBoard(Array2D board, int player) override;

    /// @brief draws the score
    /// @param scorePlayer1 score of the first player
    /// @param scorePlayer2 score of the second player
    void drawScore(int scorePlayer1, int scorePlayer2) const override;

    /// @return strategy of the first player
    QString getCurrentStrategyPlayer1() override;

    /// @return strategy of the second player
    QString getCurrentStrategyPlayer2() override;

    /// @return width of the view
    int getWidth() const override;

    /// @return height of the view
    int getHeight() const override;

    /// @brief shows all possible moves for one player (not implemented in Reversi)
    /// @param moves all possible moves
    void drawPossibleMoves(std::vector<Field> moves) const override;

    /// @return size of the clickable label 
    Size getSizeClickableLabel() const override;

    /// @return cursor position
    QPoint cursorPosition() override;
    
    /// @brief opens window where the winner is displayed 
    /// @param player 1 if the first player is the winner and 2 if the second player is the winner
    /// @param scorePlayer integer that represents the score of the player
    void showWinnerWindow(int player, int scorePlayer) override;

    /// @return returns current speed
    int getCurrentSpeed() override;

    /// @brief draws initial board with four tokens in the middle of the board
    /// @param board array that contains the information about the fields on the board
    void drawInitialBoard(Array2D board);

    /// @brief is called when the game is closed
    void closeEvent(QCloseEvent *event);

    /// @brief initializes the ComboBox
    void initializeComboBox();

    /// @brief initializes the table where one could find the descriptions of the different strategies
    void initializeDescriptionTable();
    
    

    /// @brief shows the strategies of the players
    void drawAllStrategiesUsed(QString player1Strategy, QString player2Strategy) override;

    void showAllAgainstAllTable(std::vector<QString> &winners) override;

private:
    Ui::ReversiClass *ui;
    QImage m_clickableLabelImage;
    QImage m_previewImage;

};
