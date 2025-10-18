#include "styles.h"
#include <QFont>
#include <QFontDatabase>

QString Styles::getWhiteStyle()
{
	return  "QPushButton{"
		"background: url(:/resourses/figureBlue.png) no-repeat center center;"
		"}"
		"QPushButton:pressed{"
		"background: transparent;"
		"image: url(:/resourses/figureBlueLight.png) no-repeat center center;"
		"}";
}

QString Styles::getBlackStyle()
{
	return  "QPushButton{"
		"background: url(:/resourses/figureRed.png) no-repeat center center;"
		"}"
		"QPushButton:pressed{"
		"background: transparent;"
		"image: url(:/resourses/figureRedLight.png) no-repeat center center;"
		"}";
}


QString Styles::getWhiteQueenStyle()
{
	return  "QPushButton{"
		"background: url(:/resourses/figureBlueQueen.png) no-repeat center center;"
		"}"
		"QPushButton:pressed{"
		"background: transparent;"
		"image: url(:/resourses/figureBlueQueenLight.png) no-repeat center center;"
		"}";
}

QString Styles::getBlackQueenStyle()
{
	return  "QPushButton{"
		"background: url(:/resourses/figureRedQueen.png) no-repeat center center;"
		"}"
		"QPushButton:pressed{"
		"background: transparent;"
		"image: url(:/resourses/figureRedQueenLight.png) no-repeat center center;"
		"}";
}

QString Styles::getTabWidgetStyle()
{
	return  "QTabWidget::pane {"
		"border: 1px solid #ccc;"
		"border-radius: 15px;"
		"background-image: url(:/resourses/graydesk.png);"
		"background-position: center;"
		"background-repeat: no-repeat;"
		"border: 3px solid black;"
		"}"
		"QTabBar::tab {"
		"border-top-left-radius: 15px;"
		"border: 3px solid black;"
        "background: #d0d0d0;"
		"color: #000000;"
		"padding: 15px;"
		"}"
		"QTabBar::tab:selected {"
        "background: #f0f0f0;"
		"color: #0000ff;"
		"border: 3px solid black;"
        "}";
}

QString Styles::getHelpWindowStyle()
{

    return "QTextBrowser {"
        "background: transparent;"
        "border-radius: 50px;"
        "padding: 5px;"
        "margin: 0;"
        "}"
        "QTextBrowser::viewport {"
        "border-radius: 50px;"
        "background: transparent;"
        "}";

}

QString Styles::getMainWindowStyle()
{
	return "QMainWindow{"
		"background-image: url(:/resourses/bg.jpg) no-repeat center center;"
		"}";
}

QString Styles::getNameStyle()
{
	return  "QLabel{"
		"background-image: url(:/resourses/namebgmain.png) no-repeat center center;"
		"}";
}

QString Styles::getStartButtonStyle()
{
	return  "QPushButton{"
		"background: url(:/resourses/startbgmain.png) no-repeat center center;"
		"}"
		"QPushButton:pressed{"
		"background: transparent;"
		"image: url(:/resourses/startbgpressed.png) no-repeat center center;"
		"}";
}

QString Styles::getGiveUpButtonStyle()
{
	return  "QPushButton{"
		"background: url(:/resourses/giveupbgmain.png) no-repeat center center;"
		"}"
		"QPushButton:pressed{"
		"background: transparent;"
		"image: url(:/resourses/giveupbgpressed.png) no-repeat center center;"
		"}";
}

QString Styles::getQuitButtonStyle()
{
	return  "QPushButton{"
		"background: url(:/resourses/quitbgmain.png) no-repeat center center;"
		"}"
		"QPushButton:pressed{"
		"background: transparent;"
		"image: url(:/resourses/quitbgpressed.png) no-repeat center center;"
		"}";
}

QString Styles::getHelpButtonStyle()
{
	return  "QPushButton{"
		"background: url(:/resourses/helpbgmain.png) no-repeat center center;"
		"}"
		"QPushButton:pressed{"
		"background: transparent;"
		"image: url(:/resourses/helpbgpressed.png) no-repeat center center;"
		"}";
}

QString Styles::getBackButtonStyle()
{
	return  "QPushButton{"
		"background: url(:/resourses/backbgmain.png) no-repeat center center;"
		"}"
		"QPushButton:pressed{"
		"background: transparent;"
		"image: url(:/resourses/backbgpressed.png) no-repeat center center;"
		"}";
}

void Styles::setHtmlHelp(QTextBrowser* textBrowser)
{

	int fontID = QFontDatabase::addApplicationFont(":/resourses/HarreeghPoppedCyrillic.ttf");
	QString fontName = QFontDatabase::applicationFontFamilies(fontID).at(0);
	QFont font(fontName, 18);

	textBrowser->setFont(font);

	QString rulesHtml = R"(
    <html>
    <head>
    <style>
        * {
            font-size: inherit;
            line-height: 1.7;
        }

        body {
            background-color: #444444;
            color: white;
            padding: 1.5em;
            margin: 0;
            border-radius: 50px;
            overflow: hidden;
            font-size: 1em;
        }
        h1 {
            color: #4CAF50;
            text-align: center;
            font-size: 2.2em;
            margin-bottom: 1em;
            text-shadow: 0.1em 0.1em 0.2em #000;
            font-weight: bold;
        }

        h2 {
            color: #4CAF50;
            font-size: 1.7em;
            margin-top: 1.5em;
            margin-bottom: 0.8em;
            border-bottom: 0.1em solid #4CAF50;
            padding-bottom: 0.5em;
            font-weight: bold;
        }

        .piece {
            font-weight: bold;
            font-size: 1.2em;
        }

        .blue {
            color: #4285F4;
        }

        .red {
            color: #EA4335;
        }

        ul {
            padding-left: 1.5em;
        }

        li {
            margin-bottom: 0.8em;
        }

        .note {
            font-style: italic;
            color: #BBBBBB;
            margin-top: 1.5em;
            font-size: 0.9em;
        }

        .board-example {
            background-color: #444;
            border: 0.15em solid #555;
            padding: 1em;
            margin: 1.5em 0;
            border-radius: 0.5em;
        }

        p {
            margin-bottom: 1em;
        }
    </style>
    </head>
    <body>
    <div class="rules-container">
        <h1>Правила игры в шашки</h1>

        <h2>Цель игры</h2>
        <p>Цель игры - захватить все шашки противника.</p>

        <h2>Игровые элементы</h2>
        <ul>
            <li>Игровое поле 8×8 клеток (чередующиеся тёмные и светлые клетки)</li>
            <li><span class="piece blue">Синие шашки</span> - принадлежат первому игроку</li>
            <li><span class="piece red">Красные шашки</span> - принадлежат второму игроку</li>
        </ul>

        <div class="board-example">
            <p>Начальная расстановка шашек:</p>
            <ul>
                <li><span class="piece blue">Синие шашки</span> занимают первые три ряда с одной стороны</li>
                <li><span class="piece red">Красные шашки</span> занимают первые три ряда с противоположной стороны</li>
            </ul>
        </div>

        <h2>Основные правила</h2>
        <ul>
            <li>Шашки ходят только по диагонали на одну клетку вперёд</li>
            <li>Если перед шашкой находится шашка противника, а за ней свободная клетка, шашка обязана "побить" (перепрыгнуть) шашку противника</li>
            <li>Побитая шашка снимается с доски</li>
            <li>Если после взятия возможно продолжение взятия других шашек противника, ход продолжается</li>
            <li>Шашка, достигшая последнего ряда, становится "дамкой" и получает возможность ходить на любое количество клеток по диагонали</li>
        </ul>

        <h2>Особые правила</h2>
        <ul>
            <li>При возможности взятия шашки противника игрок обязан это сделать</li>
            <li>Если есть несколько вариантов взятия, игрок может выбрать любой из них</li>
            <li>Дамка может бить шашки противника на любом расстоянии по диагонали</li>
        </ul>

        <h2>Конец игры</h2>
        <p>Игра заканчивается, когда:</p>
        <ul>
            <li>У одного из игроков не осталось шашек</li>
            <li>Игрок сдался</li>
        </ul>

        <p class="note">Примечание: В этой версии шашек используются традиционные правила, но с изменёнными цветами фигур - синие вместо белых и красные вместо чёрных.</p>
    </div>
    </body>
    </html>
    )";
	textBrowser->setHtml(rulesHtml);
	textBrowser->setOpenExternalLinks(true);
	textBrowser->setReadOnly(true);
}
