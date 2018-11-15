#ifndef JTABLEVIEW_H
#define JTABLEVIEW_H

// Дата создания: ??.??.201?
// Дата завершения создания: ??.??.201?
// От Dark Jedi
// Стандарт программирования Dark Jedi v1
// Версия: 2.0.2
// Исправлено ошибок после релиза версии 1.0.0: 0

#include <QWidget>
#include <QScrollArea>
#include "JScrollArea.h"

class QAbstractItemModel;
class JTableView;

class JTableViewPrivate : public QWidget
{
    Q_OBJECT
public:
    JTableViewPrivate(JTableView *parentWidget); //конструктор
    virtual ~JTableViewPrivate(); //деструктор
protected:
    virtual void paintEvent(QPaintEvent *); //событие рисования
private:
    JTableView *parent; //родитель
};

class JTableView : public JScrollArea
{
    Q_OBJECT
public:
    JTableView(QAbstractItemModel* model); //конструктор
    virtual ~JTableView(); //деструктор
    QAbstractItemModel *model; //модель
    //int rowCount; //количество рядов
    //int columnCount; //количество колонок
    int rowsHeight; //высота всех рядов (стандарт)
    int columnsWidth; //ширина всех колонок (стандарт)
    int itemBorderWidth; //ширина границ итемов
    QColor itemBorderColor; //цвет границ итемов
    QPoint activeItem; //координата активного итема по модели
    QColor activeItemBorderColor; //цвет границы активного итема
    QColor activeItemBrushColor; //цвет заливки активного итема
    QColor backgroundColor; //цвет фона всей таблицы
    enum Side {Top, Right, Bottom, Left};
    enum Pointing {LeftToRightOut,
                   RightToLeftOut,
                   TopToBottomOut,
                   BottomToTopOut,
                   LeftToRightInner,
                   RightToLeftInner,
                   TopToBottomInner,
                   BottomToTopInner};
    QRect itemRect(int row, int column, bool border = 1); //область итема(если установлен border = 1, считается с границами)
    QSize tableSize(); //размер всей таблицы
    void setRowsHeight(int height); //устанавливает высоту всех рядов
    void setColumnsWidth(int width); //устанавливает ширину всех колонок
    void setItemBorderWidth(int width); //устанавливает ширину границ вокруг итемов
    void setItemBorderColor(QColor color); //устанавливает цвет границ вокруг итемов
    void setActiveItemBorderColor(QColor color); //устанавливает цвет границ вокруг активных итемов
    void setActiveItemBrushColor(QColor color); //устанавливает цвет заливки всех активных итемов
    bool itemIsEmpty(int row, int column); //пустой ли итем
    bool isItemActivated(int r = -1, int c = -1); //активен ли итем(-1 означает любой итем)
    QRect itemsRect(int item1X, int item1Y, int item2X, int item2Y); //rect итемов под индексами: от (x1; y1) до (x2; y2)
    void setBackgroundColor(QColor color);

    int columnCount() const;
    int rowCount() const;

    void decactivateAllItems();
    void updateTableSize();
    void repaintAll(); //перерисовывает саму таблицу и дочерние скроллбары

signals:
    void itemSelected(int row, int column); //выбран итем
    void test(QString);

protected:
    virtual void paintEvent(QPaintEvent *);
    virtual void resizeEvent(QResizeEvent *);
    virtual void mousePressEvent(QMouseEvent *); //событие нажатия мышкой
    virtual void keyPressEvent(QKeyEvent *); //событие нажатия клавишей
private:
    JTableViewPrivate *tableWidget; //виджет самой таблицы
    struct Pointings {//внешнее перепрыгивание
                      bool leftToRightOut;
                      bool rightToLeftOut;
                      bool topToBottomOut;
                      bool bottomToTopOut;
                      //внутреннее перепрыгивание
                      bool leftToRightInner;
                      bool rightToLeftInner;
                      bool topToBottomInner;
                      bool bottomToTopInner;
    };
    Pointings AutoSelectingJumps; //объект Pointings
    void activateItem(int row, int column); //активирует итем
    void deactivateItem(int row, int column); //деактивирует итем
    void moveSelecting(Side side); //двигать выделение
    void autoscroll(Side side);
//члены класса, которые требуют что-то выше
public:
    void setAutoSelectingJump(Pointing jump, bool setting); //автоперепрыгивание выделения на другие строки/колонки, inner - внтуреннее переп.
};

#endif // JTABLEVIEW_H
