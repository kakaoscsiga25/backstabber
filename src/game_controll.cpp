#include "game_controll.hpp"
#include "logger.h"
#include "deck.hpp"

#include <QThread>
#include <unistd.h>
#include <assert.h>


GameControll::GameControll(int numberOfPlayers)
{
    // Init deck
    state.deck = new Deck();

    // Init players
//    for (int i = 0; i < numberOfPlayers; i++)
//    {
//        state.players.push_back(new Player(std::to_string(i+1))); // init players
//        QObject::connect(state.players.back(), &Player::playCard, this, &GameControll::playCardRequest, Qt::DirectConnection);
//    }
//    Logger::getLogger()->log(LogType::INFO, std::to_string(state.players.size()) + " player are initialized");
    Player* p = new Player("En", 1);
    state.player = p;

    connect(state.player, &Player::usedCard, state.deck, &Deck::discard);

    // Start internal thread (game logic thread)
    gameThread = new QThread();
    this->moveToThread(gameThread);
    connect(gameThread, &QThread::started, this, &GameControll::start);
    gameThread->start();
}
GameControll::~GameControll()
{
    delete state.player;
    delete state.deck;
    gameThread->quit();
    gameThread->deleteLater();
}


void GameControll::turn(Player* activePlayer)
{

}

bool GameControll::legalStep(Card_base* card, Target* target) const
{
    return true;
}

void GameControll::addToCardsQueue(const CardCommand& cardWrap)
{
    // TODO mutexing
    cardsQueue.push_back(cardWrap);
    Logger::getLogger()->log(LogType::DEBUG, "New carded added to card queue, size: " + std::to_string(cardsQueue.size()));
}

void GameControll::changeWatcher(int waitTime)
{
    auto start = std::chrono::steady_clock::now();
    while (std::chrono::duration_cast<std::chrono::seconds>(std::chrono::steady_clock::now() - start).count() < waitTime)
    {
        while(!cardsQueue.empty()) // mutex later?
        {
            const CardCommand& cardWrap = cardsQueue.front();
            cardsQueue.pop_front();
            // Process card
            bool cardIsUsed = false;
            if (legalStep(cardWrap.card, cardWrap.target))
            {
                Card_item* cardItem = dynamic_cast<Card_item*>(cardWrap.card);
                if(cardItem)
                {
                    if (Player* target = dynamic_cast<Player*>(cardWrap.target))
                    {
                        target->putToTable(cardItem);
                    }
                    else if (Monster* target = dynamic_cast<Monster*>(cardWrap.target))
                    {

                    }
                    else
                        std::cerr << "Cant cast target" << std::endl;
                }
                else
                    std::cerr << "Cant cast to carditem" << std::endl;
            }

            // IF state changed
//            start = std::chrono::steady_clock::now();
        }
        usleep(10); // microsec
    }
}

void GameControll::start()
{
    // Init player
    state.player->init(state.deck);

    int turnCounter = 1;
    while(state.player->getLevel() < 10)
    {
        // Pre turn
        Logger::getLogger()->log(LogType::PLAY, "Turn " + std::to_string(turnCounter) + " pre drawing phase...");
        changeWatcher(5);

        turnCounter++;
    }
    Logger::getLogger()->log(LogType::PLAY, "Player " + state.player->getName() + " reached level " + std::to_string(state.player->getLevel()) + ", so the game is finished!");
}

void GameControll::playCardRequest(Card_base* card, Target* target)
{
//    std::cerr << QObject::sender() << " request " << target << "\n";
    CardCommand wrap;
    wrap.card = card;
    wrap.target = target;
    addToCardsQueue(wrap);
}
