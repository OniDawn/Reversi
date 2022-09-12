#include "Reversi.h"
#include "ReversiCore/Array2D.h"
#include "ReversiCore/Size.h"
#include "Renderer.h"
#include "ClickableLabel.h"
#include "ReversiCore/StrategyFactory.h"
#include <QMessageBox>
#include <QString>
#include <vector>

Reversi::Reversi(QWidget *parent) : 
    QMainWindow(parent),
    ui(new Ui::ReversiClass())
{
    
    ui->setupUi(this);
    
    QMainWindow::connect(ui->pushButtonEnd, &QPushButton::pressed, this, &Reversi::endGameRequest);
    QMainWindow::connect(ui->pushButtonStart, &QPushButton::pressed, this, &Reversi::startGame);
    QMainWindow::connect(ui->labelBoard, &ClickableLabel::clickedLeft, this, &Reversi::clickedLeft);
    QMainWindow::connect(ui->horizontalSlider, &QSlider::valueChanged, this, &Reversi::speedUpdateRequest);

    initializeComboBox();
    initializeDescriptionTable();
}

Reversi::~Reversi()
{
    delete ui;
}

void Reversi::drawBoard(Array2D board, int player)
{
    drawInitialBoard(board);
    Renderer renderer = Renderer(board, getSizeClickableLabel());
    m_clickableLabelImage = renderer.updateBoard(board, m_clickableLabelImage);
    ui->labelBoard->setPixmap(QPixmap::fromImage(m_clickableLabelImage));
    m_previewImage = renderer.updateLabelWhosNext(player);
    ui->nextTurnColorLabel->setPixmap(QPixmap::fromImage(m_previewImage));
}

void Reversi::drawScore(int scorePlayer1, int scorePlayer2) const
{
    ui->player1ScoreLabel->setText(QString::number(scorePlayer1));
    ui->player2ScoreLabel->setText(QString::number(scorePlayer2));
}

int Reversi::getWidth() const
{
    return this->size().width();
}

int Reversi::getHeight() const
{
    return this->size().height();
}

Size Reversi::getSizeClickableLabel() const
{
    return Size(ui->labelBoard->width(), ui->labelBoard->height());
}

void Reversi::drawInitialBoard(Array2D board)
{
    Renderer renderer = Renderer(board, getSizeClickableLabel());
    m_clickableLabelImage = renderer.calculateBoardImage();
    ui->labelBoard->setPixmap(QPixmap::fromImage(m_clickableLabelImage));
    m_previewImage = renderer.updateLabelWhosNext(1);
    ui->nextTurnColorLabel->setPixmap(QPixmap::fromImage(m_previewImage));
    ui->player1ColorScoreLabel->setPixmap(QPixmap::fromImage(renderer.calculateScoreLabel(1)));
    ui->player2ColorScoreLabel->setPixmap(QPixmap::fromImage(renderer.calculateScoreLabel(2)));
}

QString Reversi::getCurrentStrategyPlayer1()
{
    return ui->comboBoxStrategyPlayer1->currentText();
}

QString Reversi::getCurrentStrategyPlayer2()
{
    return ui->comboBoxStrategyPlayer2->currentText();
}

void Reversi::drawPossibleMoves(std::vector<Field> moves) const
{

}

void Reversi::closeEvent(QCloseEvent* event)
{
    emit gameCloseRequest();
}

QPoint Reversi::cursorPosition()
{
    QPoint pos = ui->labelBoard->mapFromGlobal(QCursor::pos());
    return pos;
}

void Reversi::showWinnerWindow(int player, int scorePlayer)
{
    QMessageBox msgBox;
    if (player == 1)
    {
        msgBox.setText("Player 1 (red) wins!");
    }
    else if (player == 2)
    {
        msgBox.setText("Player 2 (green) wins!");
    }
    else if (player == 0)
    {
        msgBox.setText("Tie!");
    }
    msgBox.exec();
}

int Reversi::getCurrentSpeed()
{
    return ui->horizontalSlider->value();
}


void Reversi::initializeComboBox()
{
    int i = 0;
    for (auto& name : StrategyFactory::instance().getNames())
    {
        ui->comboBoxStrategyPlayer1->addItem(name, i);
        ui->comboBoxStrategyPlayer2->addItem(name, i);
        i++;
    }
}

void Reversi::initializeDescriptionTable()
{
    int count = 0;
    for (auto& name : StrategyFactory::instance().getNames())
    {
        count++;
    }
    ui->tableWidget->setRowCount(count);
    ui->tableWidget->setColumnCount(2);

    int row = 0;
    int column = 0;
    for (auto& newName : StrategyFactory::instance().getNames())
    {
        QTableWidgetItem* newItem = new QTableWidgetItem(tr("%1").arg(newName));
        ui->tableWidget->setItem(row, column, newItem);
        newItem = new QTableWidgetItem(tr("%1").arg(StrategyFactory::instance().getDescription(newName)));
        ui->tableWidget->setItem(row, column+1, newItem);
        row++;
    }

    QTableWidgetItem* headerItem = new QTableWidgetItem(tr("%1").arg("Strategie"));
    ui->tableWidget->setHorizontalHeaderItem(0, headerItem);
    headerItem = new QTableWidgetItem(tr("%1").arg("Beschreibung"));
    ui->tableWidget->setHorizontalHeaderItem(1, headerItem);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
    
}

void Reversi::drawAllStrategiesUsed(QString player1Strategy, QString player2Strategy)
{

}

void Reversi::showAllAgainstAllTable(std::vector<QString> &winners)
{

}
