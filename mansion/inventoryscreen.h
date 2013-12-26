#ifndef INVENTORYSCREEN_H
#define INVENTORYSCREEN_H

#include <QDialog>
#include <QString>
#include <QPushButton>
#include <QLabel>
#include <QTextEdit>
#include <QLineEdit>
#include <QGridLayout>
#include "player.h"

class inventoryScreen : public QDialog
{
    Q_OBJECT

public:
    explicit inventoryScreen(QDialog *parent = 0);
    void showPlayer(Player showPlayer);

private:
    QPushButton *okButton;
    QLabel *nameLabel, *itemLabel, *statLabel, *moneyLabel, *karmaLabel, *gameoverLabel;
    QLineEdit *moneyAmount, *karmaAmount, *gameoverAmount;
    QTextEdit *itemlist, *statlist;
    QGridLayout *layout;
    
signals:
    
public slots:
    
};

#endif // INVENTORYSCREEN_H
