#ifndef STYLES_H
#define STYLES_H
#include <QString>
#include <QTextBrowser>

class Styles
{
public:
    static QString getWhiteStyle();
    static QString getWhiteStyleEat();
    static QString getBlackStyle();
    static QString getBlackStyleEat();
    static QString getWhiteQueenStyle();
    static QString getWhiteQueenStyleEat();
    static QString getBlackQueenStyle();
    static QString getBlackQueenStyleEat();
    static QString getTabWidgetStyle();
    static QString getHelpWindowStyle();
    static QString getMainWindowStyle();
    static QString getNameStyle();
    static QString getStartButtonStyle();
    static QString getGiveUpButtonStyle();
    static QString getQuitButtonStyle();
    static QString getHelpButtonStyle();
    static QString getBackButtonStyle();
    static void setHtmlHelp(QTextBrowser* textBrowser);
};

#endif // STYLES_H
