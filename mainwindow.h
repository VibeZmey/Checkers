#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "engine.h"
#include <QMainWindow>
#include <QPushButton>
#include <QString>
#include <QVector>
#include <QMap>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui {
	class MainWindow;
}
QT_END_NAMESPACE


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

private slots:
    void on_startButton_clicked();
    void on_giveUpButton_clicked();
    void on_quitButton_clicked();
    void on_helpButton_clicked();
    void timerUpdate();

private:
    void configTabWidget();
    void setGameArea();
    void setStyleMainWindow();
    void onGameButtonClicked();
    void playerChenger();
    void gameReset();
    void queenSet(int x, QPushButton* btn);
    void setStyleBlack(QPushButton* btn);
    void setStyleWhite(QPushButton* btn);
    void setStyleTimer();
    void updateStyles();
    void playerChengerStyle();
    void AnimationNameLabel();
    void AnimationWinnerLabel();
    QPushButton* getButton(int x, int y);

    Engine* engine = new Engine();
    Ui::MainWindow* ui;
    QTimer* time;
    int totalSec = 0;
    bool helpOpened = false;
    bool progress;// возможность хода
    int white = 0;// кол во съеденых шашек
    int black = 0;
};
#endif // MAINWINDOW_H
