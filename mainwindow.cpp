#include <QTabBar>
#include "styles.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QVector>
#include <QVariant>
#include <QDebug>
#include <QString>
#include <cmath>
#include <QPropertyAnimation>
#include <QTimer>
#include <QTime>
#include <QMessageBox>
#include <QPixmap>
#include <QPalette>
#include <cstdio>
#include <QFontDatabase>
#include <QPropertyAnimation>
#include <QSequentialAnimationGroup>
#include <QDebug>
#include <QGraphicsOpacityEffect>
#include <QEvent>
#include <QWheelEvent>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    time = new QTimer(this);
    connect(time, SIGNAL(timeout()), this, SLOT(timerUpdate()));
    setStyleTimer();

    ui->label->setStyleSheet(Styles::getNameStyle());

    configTabWidget();

    setGameArea();

    setStyleMainWindow();

    ui->helpWindow->setStyleSheet(Styles::getHelpWindowStyle());

    Styles::setHtmlHelp(ui->helpWindow);

}

MainWindow::~MainWindow()
{
	delete ui;
}

// настройка виджета игрового поля
void MainWindow::configTabWidget()
{
    ui->helpWindow->setStyleSheet(Styles::getHelpWindowStyle());
    ui->helpWindow->setContextMenuPolicy(Qt::NoContextMenu); // Убираем меню
    ui->tabWidget->tabBar()->hide();
    ui->tabWidget->setCurrentIndex(0);
    ui->tabWidget->setStyleSheet(Styles::getTabWidgetStyle());
}

// смена игрока
void MainWindow::playerChenger()
{
    if (white == 12 or black == 12)  // проверяем окончание игры
    {
        gameReset();
        return;
    }
	engine->setPlayer(engine->getPlayer() == "W" ? "B" : "W");
	if (engine->getPlayer() == 'W') engine->setWhiteHand();
	else engine->setBlackHand();
	engine->blockForEat();
    playerChengerStyle();
}


//настройка изначального игрового поля
void MainWindow::setGameArea()
{

	QGridLayout* grid = qobject_cast<QGridLayout*>(ui->tab->layout());
	engine->setGridLayout(grid);
	for (int row = 0; row < 8; row++)
	{
		for (int column = (row + 1) % 2; column < 8; column += 2)
		{
			QPushButton* btn = qobject_cast<QPushButton*>(grid->itemAtPosition(row, column)->widget());
			connect(btn, &QPushButton::clicked, this, &MainWindow::onGameButtonClicked);
			btn->setProperty("row", row);//инфa о колонах и строках // не изменяется
			btn->setProperty("column", column);// не изменяется
			btn->setProperty("color", "N");
			btn->setProperty("queen", false);
			btn->setFlat(1);
			if (row < 3)
			{
                setStyleBlack(btn);
                btn->setProperty("color", "B");
			}
			else if (row > 4)
			{
                setStyleWhite(btn);
                btn->setProperty("color", "W");
			}
			else btn->setStyleSheet("");
		}
	}
	for (int row = 0; row < 8; row++)
	{
		for (int column = 0; column < 8; column++)
		{
			QPushButton* btn = qobject_cast<QPushButton*>(grid->itemAtPosition(row, column)->widget());
			btn->setDisabled(1);
			if ((row + column) % 2 == 0)
			{
				btn->setFlat(1);
			}
		}
	}
}

void MainWindow::gameReset()
{
    ui->giveUpButton->setDisabled(1);

    AnimationNameLabel();

    engine->updateStatus();
	setStyleTimer();

	white = 0;
	black = 0;

	if (time->isActive()) time->stop();
	setGameArea();
}

void MainWindow::setStyleMainWindow()
{
	ui->giveUpButton->setDisabled(1);
	ui->startButton->setDisabled(0);
	ui->helpButton->setStyleSheet(Styles::getHelpButtonStyle());
	ui->quitButton->setStyleSheet(Styles::getQuitButtonStyle());
	ui->startButton->setStyleSheet(Styles::getStartButtonStyle());
	ui->giveUpButton->setStyleSheet(Styles::getGiveUpButtonStyle());
	QPixmap background(":/resourses/bg3.jpg");
	QPalette palette;
	palette.setBrush(QPalette::Window, background);
	this->setPalette(palette);
	this->setAutoFillBackground(true);
}

// основа программы(реализация ходов)
void MainWindow::onGameButtonClicked()
{
    QPushButton* btn = qobject_cast<QPushButton*>(sender());
    int x = btn->property("row").toInt();
    int y = btn->property("column").toInt();
    if (btn->property("color") == engine->getPlayer())
    {
            if (btn->property("queen") == true) engine->moveCouterForQueen(btn);
            else engine->moveCounter(btn);
            progress = (engine->getMove().size() != 0 ? progress = true : progress = false);   // если ходы есть то добавляем возможность ходить
            engine->setLastButton(btn);
    }
    if (progress)
    {
            bool flag = false;
            Happens click({}, {}, {});
            for (Happens mv : engine->getMove()) // проверяем является ли шашка ходом для пред
            {
                    if (mv.to.first == x && mv.to.second == y && mv.from.first == engine->getLastButton()->property("row") && mv.from.second == engine->getLastButton()->property("column"))
                    {
                            flag = true;
                            click = mv;
                            break;
                    }
            }
            if (flag)
            {
                    std::pair<int, int> nul = { -1, -1 };
                    engine->setMove(btn); // передвижение мождельки
                    engine->queenCheck(btn);
                    if (click.eat != nul) // если игрок съел шашку противника
                    {
                            QPushButton* eatedButton = engine->getButton(click.eat.first, click.eat.second);
                            eatedButton->setProperty("color", "N");
                            eatedButton->setText("");
                            eatedButton->setStyleSheet("");
                            eatedButton->setProperty("queen", false);
                            if (engine->getPlayer() == "W")
            {
                                    black++;
                ui->leftLabel->setText(QString("     %1").arg(black, 1, 10, QChar('0')));
                            }
                            else {

                white++;
                ui->rightLabel->setText(QString("%1     ").arg(white, 1, 10, QChar('0')));
                            }
                            engine->clearMove();

                            if (btn->property("queen") == true) engine->moveCouterForQueen(btn);
                            else engine->moveCounter(btn);

                            bool eatNext = false;

                            for (Happens mv : engine->getMove()) // проверяем является ли шашка ходом для пред
                            {
                                    if (mv.eat != nul)
                                    {
                                            eatNext = true;
                                            break;
                                    }
                            }
            if (eatNext) {
                engine->blockForEat(btn); // если игрок может есть дальше
                engine->setLastButton(btn);
                progress = true;
                return;
            }
                            else playerChenger(); // если не может то ход переходит

                    }
                    else playerChenger();
                    progress = false;
            }
    }
}

void MainWindow::AnimationNameLabel()
{
    QPropertyAnimation* setWinDown = new QPropertyAnimation(ui->labelLose, "pos", this);
    setWinDown->setStartValue(ui->label->pos());
    setWinDown->setEndValue(ui->label->pos() + QPoint(0, -200));
    setWinDown->setEasingCurve(QEasingCurve::InOutQuad);

    QPropertyAnimation* animationUp = new QPropertyAnimation(ui->label, "pos", this);
    animationUp->setStartValue(ui->label->pos());
    animationUp->setEndValue(ui->label->pos() + QPoint(0, -400));
    animationUp->setDuration(500);
    animationUp->setEasingCurve(QEasingCurve::InOutQuad);

    QObject::connect(animationUp, &QSequentialAnimationGroup::finished, [=]() {
            AnimationWinnerLabel();
            });

    QPropertyAnimation* animationStay = new QPropertyAnimation(ui->label, "pos", this);
    animationStay->setDuration(3000);
    animationStay->setStartValue(ui->label->pos() + QPoint(0, -400));
    animationStay->setEndValue(ui->label->pos() + QPoint(0, -400));

    QPropertyAnimation* animationDown = new QPropertyAnimation(ui->label, "pos", this);
    animationDown->setStartValue(ui->label->pos() + QPoint(0, -400));
    animationDown->setEndValue(ui->label->pos());
    animationDown->setDuration(500);
    animationDown->setEasingCurve(QEasingCurve::InOutQuad);

    QSequentialAnimationGroup* group = new QSequentialAnimationGroup;
    group->addAnimation(setWinDown);
    group->addAnimation(animationUp);
    group->addAnimation(animationStay);
    group->addAnimation(animationDown);

    QObject::connect(group, &QSequentialAnimationGroup::finished, [=]() {
            ui->giveUpButton->setDisabled(1);
            ui->startButton->setDisabled(0);
            delete animationUp;
            delete animationDown;
            delete animationStay;
            delete group;
            });
    group->start();
}

void MainWindow::AnimationWinnerLabel()
{
    if (engine->getPlayer() == 'W')
    {
        ui->labelLose->setPixmap(QPixmap(":/resourses/mainwinbgblue.png"));
    }
    else
    {
        ui->labelLose->setPixmap(QPixmap(":/resourses/mainwinbgred.png"));
    }

    ui->labelLose->setAlignment(Qt::AlignCenter);

    QGraphicsOpacityEffect* opacity = new QGraphicsOpacityEffect(ui->labelLose);
    opacity->setOpacity(0.0);
    ui->labelLose->setGraphicsEffect(opacity);

    QPropertyAnimation* fadeIn = new QPropertyAnimation(opacity, "opacity", this);
    fadeIn->setDuration(500);
    fadeIn->setStartValue(0.0);
    fadeIn->setEndValue(1.0);

    QPropertyAnimation* fadeOut = new QPropertyAnimation(opacity, "opacity", this);
    fadeOut->setDuration(500);
    fadeOut->setStartValue(1.0);
    fadeOut->setEndValue(0.0);
    QObject::connect(fadeOut, &QSequentialAnimationGroup::finished, [=]() {
        delete fadeIn;
        delete fadeOut;
        });
    fadeIn->start();
    QTimer::singleShot(2000, this, [fadeOut]() {
        fadeOut->start();
        });
}

void MainWindow::setStyleBlack(QPushButton* btn)
{
    btn->setStyleSheet(Styles::getBlackStyle());
}

void MainWindow::setStyleWhite(QPushButton* btn)
{
    btn->setStyleSheet(Styles::getWhiteStyle());
}

void MainWindow::setStyleTimer()
{
    int fontID = QFontDatabase::addApplicationFont(":/resourses/HarreeghPoppedCyrillic.ttf");
    QString fontName = QFontDatabase::applicationFontFamilies(fontID).at(0);
    QFont font(fontName, 18);
    ui->timeLabel->setFont(font);
    ui->timeLabel->setStyleSheet("QLabel{"
            "color:white;"
            "background: url(:/resourses/timerbg.png) no-repeat center center;"
            "}");
    ui->leftLabel->setFont(font);
    ui->leftLabel->setStyleSheet("QLabel{"
            "color:white;"
            "background: url(:/resourses/leftbg.png) no-repeat center center;"
            "}");
    ui->rightLabel->setFont(font);
    ui->rightLabel->setStyleSheet("QLabel{"
            "color:white;"
            "background: url(:/resourses/rightbg.png) no-repeat center center;"
            "}");
}

void MainWindow::playerChengerStyle()
{
    int fontID = QFontDatabase::addApplicationFont(":/resourses/HarreeghPoppedCyrillic.ttf");
    QString fontName = QFontDatabase::applicationFontFamilies(fontID).at(0);
    QFont font(fontName, 18);
    if (engine->getPlayer() == "W")
    {
        ui->leftLabel->setFont(font);
        ui->leftLabel->setStyleSheet("QLabel{"
                "color:white;"
                "background: url(:/resourses/leftbg.png) no-repeat center center;"
                "}");
        ui->rightLabel->setFont(font);
        ui->rightLabel->setStyleSheet("QLabel{"
                "color:white;"
                "background: url(:/resourses/rightbggrey.png) no-repeat center center;"
                "}");
    }
    else
    {
        ui->leftLabel->setFont(font);
        ui->leftLabel->setStyleSheet("QLabel{"
                "color:white;"
                "background: url(:/resourses/leftbggrey.png) no-repeat center center;"
                "}");
        ui->rightLabel->setFont(font);
        ui->rightLabel->setStyleSheet("QLabel{"
                "color:white;"
                "background: url(:/resourses/rightbg.png) no-repeat center center;"
                "}");
    }

}

void MainWindow::timerUpdate()
{
    totalSec++;
    int min = totalSec / 60;
    int sec = totalSec % 60;
    ui->timeLabel->setText(
            QString("%1:%2")
            .arg(min, 2, 10, QChar('0'))
            .arg(sec, 2, 10, QChar('0'))
    );
}



void MainWindow::on_startButton_clicked()
{
    ui->tabWidget->setCurrentIndex(0);
    ui->startButton->setDisabled(1);
    ui->giveUpButton->setDisabled(0);
    if (!time->isActive())
    {
            time->start(1000);
            totalSec = 0;
            ui->timeLabel->setText("00:00");
            ui->leftLabel->setText("     0");
            ui->rightLabel->setText("0     ");
    }
    engine->setPlayer("W");
    playerChengerStyle();
    engine->setWhiteHand();
}

void MainWindow::on_giveUpButton_clicked()
{
    engine->setPlayer(engine->getPlayer() == "W" ? "B" : "W");
    gameReset();
}

void MainWindow::on_quitButton_clicked()
{
    int repos = QMessageBox::question(this, "Подтверждение", "Вы действительно хотите выйти ?", QMessageBox::Ok | QMessageBox::Cancel);
    if (repos == QMessageBox::Ok) QApplication::quit();
}

void MainWindow::on_helpButton_clicked()
{
    helpOpened = (helpOpened ? false : true);
    if (helpOpened)
    {
            ui->tabWidget->setCurrentIndex(1);
            ui->helpButton->setStyleSheet(Styles::getBackButtonStyle());
    }
    else
    {
            ui->tabWidget->setCurrentIndex(0);
            ui->helpButton->setStyleSheet(Styles::getHelpButtonStyle());
    }
}


