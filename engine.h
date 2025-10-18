#ifndef ENGINE_H
#define ENGINE_H

#include <QObject>
#include <QPushButton>
#include <QVector>
#include <QMap>
#include <QTimer>
#include <QGridLayout>

struct Happens
{
    std::pair<int, int> from;
    std::pair<int, int> eat;
    std::pair<int, int> to;
    Happens(std::pair<int, int> _from, std::pair<int, int> _eat, std::pair<int, int> _to) : from(_from), eat(_eat), to(_to) {};
};

class Engine : public QObject
{
    Q_OBJECT

public:
    Engine(QObject* parent = nullptr) : grid(nullptr) {};

    void moveCounter(QPushButton* btn);
    void moveCouterForQueen(QPushButton* btn);
    void setMove(QPushButton* btn);
    void queenCheck(QPushButton* btn);
    void blockForEat(QPushButton* btn);
    void blockForEat();
    void setWhiteHand();
    void setBlackHand();
    void updateStatus();

    QPushButton* getButton(int x, int y);

    QVector<Happens> getMove() const { return move; }
    QPushButton* getLastButton() const { return lastButton; }
    QString getPlayer() const { return player; }
    bool getProgress() const { return progress; }

    void clearMove() { move.clear(); }
    void setMove(const QVector<Happens>& value) { move = value; }
    void setLastButton(QPushButton* value) { lastButton = value; }
    void setPlayer(const QString& value) { player = value; }
    void setProgress(bool value) { progress = value; }
    void setGridLayout(QGridLayout* layout) { grid = layout; }

private:
	QVector<Happens> move = {};
	QPushButton* lastButton = nullptr;
	QString player = "W";
	bool progress;
	QGridLayout* grid = nullptr;
};

#endif // ENGINE_H
