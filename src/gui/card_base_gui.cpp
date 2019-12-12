#include "gui/card_base_gui.hpp"

#include "gui/player_window.hpp"


QSize Card_base_gui::SIZE_OF_CARD = QSize(100, 175);


QWidget* parentByName(QWidget* widget, QString name)
{
    if (!widget)
        return nullptr;
    widget = widget->parentWidget();
    if (widget && widget->objectName() != name)
        return parentByName(widget, name);
    return widget;
}

QWidget* calcPos(QWidget* widget, QString name, QPoint& position)
{
    if (!widget)
        return nullptr;
    position += widget->pos();
    widget = widget->parentWidget();
    if (widget && widget->objectName() != name)
        return parentByName(widget, name);
    return widget;
}

void Card_base_gui::mousePressEvent(QMouseEvent* event)
{
    if( event->buttons() & Qt::LeftButton)
    {
        relativeDragStartPosition = pos();
        globalDragStartPosition = event->globalPos();

//        QPoint windowPos = pos();
//        PlayerWindow* window = dynamic_cast<PlayerWindow*>(calcPos(parentWidget(), "PlayerWindow", windowPos));
//        windowPos = QPoint(0,0);
//        if (window)
//        {
//            move(windowPos);
//            lastParent = parent();
//            setParent(window);
//        }
//        std::cerr << window << " " << lastParent << " " << windowPos.x() << " " << windowPos.y() << "\n";

        raise();

        this->setAttribute(Qt::WA_TransparentForMouseEvents, true);
    }
}

void Card_base_gui::mouseReleaseEvent(QMouseEvent* event)
{
    QWidget* window = dynamic_cast<QWidget*>(parent());
    if (window)
    {
        QFrame *area = dynamic_cast<QFrame*>(window->childAt(this->pos() + event->pos()));
        if (area)
        {
            Target target;
            if (area->objectName() == "ItemsArea")
                target = Target::SELF;
            else if (area->objectName() == "MonsterArea")
                target = Target::MONSTER;
            // else: No target
            if (target != Target::UNK)
            {
                emit dropped(card, target);
                return;
            }
        }
    }

    move(relativeDragStartPosition); // reset position (can be changed at refresh [if happens])

    this->setAttribute(Qt::WA_TransparentForMouseEvents, false);
}


void Card_base_gui::mouseDoubleClickEvent(QMouseEvent *event)
{
    Card_item* cardItem = dynamic_cast<Card_item*>(card);
    if (cardItem)
    {
        if (cardItem->activated)
            cardItem->activated = false;
        else
            emit dropped(card, Target::SELF);
    }
}
