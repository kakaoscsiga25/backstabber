#ifndef GAME_CONTROLL_HPP
#define GAME_CONTROLL_HPP

#include "player.hpp"
#include "game_state.hpp"

#include <vector>
#include <QObject>


struct CardCommand
{
    Player* sender;
    Card_base* card;
    Target* target;
};


class GameControll : public QObject
{
    Q_OBJECT

    friend class PlayerWindow;

public:
    GameControll(int numberOfPlayers = 2);
    virtual ~GameControll();

    void turn(Player* activePlayer);

    bool legalStep(Card_base* card, Target* target) const;

    void wait() const;

    const GameState* getState() const { return &state; }

protected:
    void addToCardsQueue(const CardCommand& cardWrap);
    void changeWatcher(int waitTime);

    GameState state;
    QThread* gameThread;
    std::deque<CardCommand> cardsQueue;

signals:
    void somethingChanged();
    void fightStarted(Fight*);
    void fightEnded();

public slots:
    void start();
    void playCard(Player* player, Card_base* card, Target* target);
};


#endif // GAME_CONTROLL_HPP
