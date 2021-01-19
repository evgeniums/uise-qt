/**
@copyright Evgeny Sidorov 2021

This software is dual-licensed. Choose the appropriate license for your project.

1. For open source projects this software is distrubuted under the GNU GENERAL PUBLIC LICENSE, Version 3.0.
(See accompanying file LICENSE-GPLv3.md or copy at https://www.gnu.org/licenses/gpl-3.0.txt)

2. For proprietary license contact evgeniums@dracosha.com.

*/

/****************************************************************************/

/** \file demo/flyweightlistview/main.cpp
*
*  Demo application of FlyweightListView.
*
*/

/****************************************************************************/

#include <QApplication>
#include <QMainWindow>
#include <QLabel>

#include <uise/desktop/flyweightlistview.hpp>
#include <uise/desktop/flyweightlistview.ipp>

#include <uise/desktop/flyweightlistitem.hpp>

using namespace UISE_DESKTOP_NAMESPACE;

//--------------------------------------------------------------------------

static size_t HelloWorldItemId=100000;

class HelloWorldItem : public QLabel
{
    public:

        HelloWorldItem(size_t seqNum, QWidget* parent=nullptr)
            : QLabel(parent),
              m_id(HelloWorldItemId--),
              m_seqNum(seqNum)
        {
            setText(QString("Hello world %1, %2").arg(seqNum).arg(m_id));
        }

        size_t seqNum() const noexcept
        {
            return m_seqNum;
        }

        size_t id() const noexcept
        {
            return m_id;
        }

        void setSeqNum(size_t value)
        {
            m_seqNum=value;
        }

    private:

        size_t m_id;
        size_t m_seqNum;
};

struct HelloWorldItemTraits : public FlyweightListItemTraits<HelloWorldItem*,QLabel,size_t,size_t>
{
    static size_t sortValue(const HelloWorldItem* item) noexcept
    {
        return item->seqNum();
    }

    static QLabel* widget(HelloWorldItem* item) noexcept
    {
        return item;
    }

    static size_t id(const HelloWorldItem* item)
    {
        return item->id();
    }
};

using HelloWorldItemWrapper=FlyweightListItem<HelloWorldItemTraits>;

int main(int argc, char *argv[])
{
    QApplication app(argc,argv);

    {
        QMainWindow w;

        auto v=new FlyweightListView<HelloWorldItemWrapper>();

        auto item2=HelloWorldItemWrapper(new HelloWorldItem(2));
        v->insertItem(std::move(item2));
        auto item1=HelloWorldItemWrapper(new HelloWorldItem(1));
        v->insertItem(std::move(item1));

        for (size_t i=50;i<70;i++)
        {
            auto item=HelloWorldItemWrapper(new HelloWorldItem(i));
            v->insertItem(std::move(item));
        }
        for (size_t i=3;i<30;i++)
        {
            auto item=HelloWorldItemWrapper(new HelloWorldItem(i));
            v->insertItem(std::move(item));
        }

        for (size_t i=70;i<100;i++)
        {
            auto item=HelloWorldItemWrapper(new HelloWorldItem(i));
            v->insertItem(std::move(item));
        }

        std::vector<HelloWorldItemWrapper> items;
        for (size_t i=30;i<50;i++)
        {
            auto item=HelloWorldItemWrapper(new HelloWorldItem(i));
            items.push_back(std::move(item));
        }
        v->insertContinuousItems(items);

        items[0].item()->setSeqNum(80);
        v->insertItem(items[0]);

        w.setCentralWidget(v);
        w.show();
        app.exec();
    }

    return 0;
}

//--------------------------------------------------------------------------
