#include "turn_controll.hpp"
#include "deck.hpp"


TurnControll::TurnControll(Player* activePlayer, std::vector<Player>* allPlayer) : activePlayer(activePlayer), allPlayer(allPlayer)
{

}

void TurnControll::turn()
{
    Logger::getLogger()->log(LogType::INFO, "It\'s " + activePlayer->getName() + " turn...");

    // Phase 1
    phase_1();


    // Phase 2
//    phase_2();


    // Phase 3
//    phase_3();
}

void TurnControll::phase_1()
{
    Logger::getLogger()->log(LogType::DEBUG, "Phase 1...");

    // Draw a card as action
    Card_door* doorCard = Deck::getDeck()->pullDoorCard();
    if (!doorCard)
    {
        Logger::getLogger()->log(LogType::PLAY, "Door deck is empty, can not pull a card. This event is skipped.");
        return;
    }
    doorCard->pullEffect(activePlayer);

}
void TurnControll::phase_2()
{
    Logger::getLogger()->log(LogType::DEBUG, "Phase 2...");
}
void TurnControll::phase_3()
{
    Logger::getLogger()->log(LogType::DEBUG, "Phase 3...");
}
