#include "engine.h"
#include "styles.h"
#include <QVariant>

//просчёт возвожных ходов для обычной шашки
void Engine::moveCounter(QPushButton* btn)
{
	int x = btn->property("row").toInt();
	int y = btn->property("column").toInt();
    if (x < 6 && y > 1 && getButton(x + 1, y - 1)->property("color") == (player == 'W' ? "B" : "W") && getButton(x + 2, y - 2)->property("color") == "N")
	{
		Happens buf({ x,y }, { x + 1, y - 1 }, { x + 2, y - 2 });
		move.append(buf);
	}
	if (x < 6 && y < 6 && getButton(x + 1, y + 1)->property("color") == (player == 'W' ? "B" : "W") && getButton(x + 2, y + 2)->property("color") == "N")
	{
		Happens buf({ x,y }, { x + 1, y + 1 }, { x + 2, y + 2 });
		move.append(buf);
	}
	if (x > 1 && y > 1 && getButton(x - 1, y - 1)->property("color") == (player == 'W' ? "B" : "W") && getButton(x - 2, y - 2)->property("color") == "N")
	{
		Happens buf({ x,y }, { x - 1, y - 1 }, { x - 2, y - 2 });
		move.append(buf);
	}
	if (x > 1 && y < 6 && getButton(x - 1, y + 1)->property("color") == (player == 'W' ? "B" : "W") && getButton(x - 2, y + 2)->property("color") == "N")
	{
		Happens buf({ x,y }, { x - 1, y + 1 }, { x - 2, y + 2 });
		move.append(buf);
	}
    if (player == 'B')
	{
		if (x < 7 && y > 0 && getButton(x + 1, y - 1)->property("color") == "N")
		{
			Happens buf({ x,y }, { -1, -1 }, { x + 1, y - 1 });
			move.append(buf);
		}
		if (x < 7 && y < 7 && getButton(x + 1, y + 1)->property("color") == "N")
		{
			Happens buf({ x,y }, { -1, -1 }, { x + 1, y + 1 });
			move.append(buf);
		}
	}
	else
	{
		if (x > 0 && y > 0 && getButton(x - 1, y - 1)->property("color") == "N")
		{
			Happens buf({ x,y }, { -1, -1 }, { x - 1, y - 1 });
			move.append(buf);
		}
		if (x > 0 && y < 7 && getButton(x - 1, y + 1)->property("color") == "N")
		{
			Happens buf({ x,y }, { -1, -1 }, { x - 1, y + 1 });
			move.append(buf);
		}
	}
}

void Engine::moveCouterForQueen(QPushButton* btn)
{
	int x = btn->property("row").toInt();
	int y = btn->property("column").toInt();

	QVector<QVector<int>> directions = { {-1, -1}, {-1, 1}, {1, -1}, {1, 1} };

	for (const auto& dir : directions) // перебираем все диагональные направления
	{
		int dx = dir[0];
		int dy = dir[1];
		int nx = x + dx;
		int ny = y + dy;
		while (nx >= 0 && nx < 8 && ny >= 0 && ny < 8)  // двигаемся до границы поля
		{
			QPushButton* button = getButton(nx, ny);

			if (button->property("color") == "N")
			{
				Happens buf({ x,y }, { -1, -1 }, { nx, ny });
				move.append(buf);
				nx += dx;
				ny += dy;
			}
			else
			{
				if (button->property("color") == (player == 'W' ? "W" : "B"))
				{
					break;
				}
				if (button->property("color") == (player == 'W' ? "B" : "W"))
				{
					int eatX = nx + dx;
					int eatY = ny + dy;

					while (eatX >= 0 && eatX < 8 && eatY >= 0 && eatY < 8)
					{
						QPushButton* EatButton = getButton(eatX, eatY);
						if (EatButton->property("color") == "N")
						{
							Happens buf({ x,y }, { nx, ny }, { eatX, eatY });
							move.append(buf);
							eatX += dx;
							eatY += dy;
						}
						else break;
					}
					break;
				}
			}
		}
	}
}

void Engine::queenCheck(QPushButton* btn)
{
	int row = btn->property("row").toInt();
	QString color = btn->property("color").toString();

    if (color == "B" && row == 7)
	{
		btn->setProperty("queen", true);
        btn->setStyleSheet(Styles::getBlackQueenStyle());
	}
    if (color == "W" && row == 0)
	{
		btn->setProperty("queen", true);
        btn->setStyleSheet(Styles::getWhiteQueenStyle());
	}
}

// переставлям старую шашку
void Engine::setMove(QPushButton* btn)
{
    btn->setStyleSheet(lastButton->styleSheet());
	btn->setProperty("color", lastButton->property("color"));
	btn->setProperty("queen", lastButton->property("queen"));

	lastButton->setText("");
	lastButton->setStyleSheet("");
	lastButton->setProperty("color", "N");
	lastButton->setProperty("queen", false);
}


//ход белых
void Engine::setWhiteHand()
{
	clearMove();
	for (int row = 0; row < 8; row++)
	{
		for (int column = (row + 1) % 2; column < 8; column += 2)
		{
			QPushButton* btn = getButton(row, column);
			if (btn->property("color") != "W" && btn->property("color") != "N")
			{
				btn->setDisabled(1);
			}
			else
			{
				if (btn->property("color") != "N")
				{
					if (btn->property("queen") == true) moveCouterForQueen(btn);
					else moveCounter(btn);
				}
				btn->setDisabled(0);
			}
		}
	}
	updateStatus();
}

//ход чёрных
void Engine::setBlackHand()
{
	clearMove();
	for (int row = 0; row < 8; row++)
	{
		for (int column = (row + 1) % 2; column < 8; column += 2)
		{
			QPushButton* btn = getButton(row, column);
			if (btn->property("color") != "B" && btn->property("color") != "N")
			{
				btn->setDisabled(1);
			}
			else
			{
				if (btn->property("color") != "N")
				{
					if (btn->property("queen") == true) moveCouterForQueen(btn);
					else moveCounter(btn);
				}
				btn->setDisabled(0);
			}
		}
	}
	updateStatus();
}


void Engine::blockForEat()
{
	bool flag = false;
	std::pair nul = { -1, -1 };
	for (Happens mv : move) {
		if (mv.eat != nul)
		{
			flag = true;
			break;
		}
	}
	if (!flag) return;
	for (int row = 0; row < 8; row++)
	{
		for (int column = (row + 1) % 2; column < 8; column += 2)
		{
			getButton(row, column)->setDisabled(1);
		}
	}
	for (Happens mv : move) {
		if (mv.eat != nul)
		{
			getButton(mv.from.first, mv.from.second)->setDisabled(0);
			getButton(mv.to.first, mv.to.second)->setDisabled(0);
			getButton(mv.eat.first, mv.eat.second)->setDown(1);
		}
	}
}

void Engine::updateStatus()
{
	for (int row = 0; row < 8; row++)
	{
		for (int column = (row + 1) % 2; column < 8; column += 2)
		{
			getButton(row, column)->setDown(0);
		}
	}
}


// блокировка посторонних ходов при съедении
void Engine::blockForEat(QPushButton* btn)
{
	std::pair nul = { -1, -1 };
	for (int row = 0; row < 8; row++)
	{
		for (int column = (row + 1) % 2; column < 8; column += 2)
		{
			QPushButton* button = getButton(row, column);
			button->setDisabled(1);
		}
	}
	btn->setDisabled(0);
	for (Happens mv : move) {
		if (mv.eat != nul)
		{
			QPushButton* button = getButton(mv.to.first, mv.to.second);
			getButton(mv.eat.first, mv.eat.second)->setDown(1);
			button->setDisabled(0);
		}
	}
}

//получить указатель на кнопку по координатам
QPushButton* Engine::getButton(int x, int y)
{
	return qobject_cast<QPushButton*>(grid->itemAtPosition(x, y)->widget());
}
