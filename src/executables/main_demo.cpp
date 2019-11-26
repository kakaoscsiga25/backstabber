#include <QApplication>
#include <QPushButton>
#include <QFrame>

#include "deck.hpp"
#include "gui/player_window.hpp"


int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    Player player("Player", 1);
    Deck deck;
    QObject::connect(&player, &Player::usedCard, &deck, &Deck::discard);

    player.init(&deck);


    PlayerWindow window(&player);
    window.stateChanged(); // init
    window.show();

/*
    for (int i=0;i<5;i++)
    {
        if (p.dead)
            p.init(&deck);

        // Try put to table all card
        for (size_t i = 0; i < p.cards_hand.size();)
            if (!p.putToTable(p.cards_hand.at(i)))
                i++;

        Card_monster* monsterCard = deck.pullDoorCard();
        monsterCard->fightWithMonster(&p, &deck);
    }
    */


    return app.exec();
}
