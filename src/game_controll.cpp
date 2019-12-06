#include "game_controll.hpp"
#include "logger.h"
#include "deck.hpp"
#include "cards/card_monster.h"

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

    connect(state.player, &Player::playCard_sign, this, &GameControll::playCard, Qt::ConnectionType::DirectConnection);
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

void GameControll::wait() const
{
    if (gameThread)
        gameThread->wait();
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
        usleep(10); // microsec

        bool gameChanged = false;
        while(!cardsQueue.empty()) // TODO: mutex
        {
            const CardCommand& cardWrap = cardsQueue.front();
            cardsQueue.pop_front();
            // Process card
            if (legalStep(cardWrap.card, cardWrap.target))
            {
                Card_item* cardItem = dynamic_cast<Card_item*>(cardWrap.card);
                if(cardItem)
                {
                    if (Player* target = dynamic_cast<Player*>(cardWrap.target))
                    {
                        if (target == cardWrap.sender) // played himself
                        {
                            bool ok = target->putToTable(cardItem);
                            if (!ok)
                                std::cerr << "TODO: send card back to player" << std::endl;
                            gameChanged = true;
                        }
                        else // to someone
                            std::cerr << "TODO: write target other player" << std::endl;
                    }
                    else if (Monster* target = dynamic_cast<Monster*>(cardWrap.target))
                    {
                        std::cerr << "TODO: card played to monster" << std::endl;
                    }
                    else
                        std::cerr << "Cast target not found" << std::endl;
                }
                else
                    std::cerr << "TODO: write other card types" << std::endl;
            }

            // IF state changed
//            start = std::chrono::steady_clock::now();
        }
        if (gameChanged)
        {
            Logger::getLogger()->log(LogType::DEBUG, "Game status changed, restart wait timer...");
            start = std::chrono::steady_clock::now();
        }
    }
    Logger::getLogger()->log(LogType::DEBUG, "Wait is ended");
}

void GameControll::start()
{
    Logger::getLogger()->log(LogType::DEBUG, "Game (thread) is started...");

    // Init player
    state.player->init(state.deck);

    int turnCounter = 1;
    while(state.player->getLevel() < 10)
    {
        // Pre turn
        Logger::getLogger()->log(LogType::PLAY, "Turn " + std::to_string(turnCounter) + " pre drawing phase...");
        changeWatcher(2);

        // Draw monster
        Logger::getLogger()->log(LogType::PLAY, "Monster drawing...");
        Card_monster* monsterCard = state.deck->pullDoorCard();
        state.fight = new Fight(&(monsterCard->monster), state.player, state.deck);
        changeWatcher(2);

        // Remove fight

        Logger::getLogger()->log(LogType::DEBUG, "Delete and remove fight from state...");
        delete state.fight;
        state.fight = nullptr;

        turnCounter++;
    }
    Logger::getLogger()->log(LogType::PLAY, "Player " + state.player->getName() + " reached level " + std::to_string(state.player->getLevel()) + ", so the game is finished!");
}

void GameControll::playCard(Player* player, Card_base* card, Target* target)
{
//    std::cerr << QObject::sender() << " request " << target << "\n";
    CardCommand wrap;
    wrap.sender = player;
    wrap.card = card;
    wrap.target = target;
    addToCardsQueue(wrap);
}
