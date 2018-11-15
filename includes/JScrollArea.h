#ifndef JSCROLLAREA_H
#define JSCROLLAREA_H

// Дата создания виджета: 16.06.2016
// Дата завершения создания: 18.06.2016
// От Dark Jedi
// Стандарт программирования Dark Jedi v3
// Версия виджета: 1.0.2
// Исправлено ошибок после релиза версии 1.0.0: 2

#include "JWidget.h"
#include "JVScrollBar.h"
#include "JHScrollBar.h"

class JScrollArea : public JWidget
{
    Q_OBJECT
public:
    enum VerticalScrollBarPosition {Left, Right};
    enum HorizontalScrollBarPosition {Top, Bottom};

    explicit JScrollArea(QWidget *parent = 0);
    virtual ~JScrollArea();

    virtual QSize sizeHint() const;

    JVScrollBar *getVerticalScrollBar() const;
    JHScrollBar *getHorizontalScrollBar() const;
    QWidget *getWidget() const;
    JWidget *getCornerWidget() const;

    QRect calculateInnerContentsRect() const;

    int getVerticalScrollBarPosition() const;
    int getHorizontalScrollBarPosition() const;

    int getVerticalScrollBarPolicy() const;
    int getHorizontalScrollBarPolicy() const;

    void setVerticalScrollBar(JVScrollBar *scrollBar);
    void setHorizontalScrollBar(JHScrollBar *scrollBar);
    void setWidget(QWidget *wgt);
    void setCornerWidget(JWidget *jwgt);

    void setVerticalScrollBarPosition(JScrollArea::VerticalScrollBarPosition);
    void setHorizontalScrollBarPosition(JScrollArea::HorizontalScrollBarPosition);

    void setVerticalScrollBarPolicy(Qt::ScrollBarPolicy);
    void setHorizontalScrollBarPolicy(Qt::ScrollBarPolicy);

public slots:
    void scrollWidgetVertical(int value);
    void scrollWidgetHorizontal(int value);

protected:
    virtual void resizeEvent(QResizeEvent *);
    virtual void showEvent(QShowEvent *);

    void updateSettings();

    int calculateVerticalScrollBarDynamicWidth() const;
    int calculateVerticalScrollBarDynamicHeight() const;
    int calculateHorizontalScrollBarDynamicHeight() const;
    int calculateHorizontalScrollBarDynamicWidth() const;

    void moveVerticalScrollBarOnOwnPosition();
    void moveHorizontalScrollBarOnOwnPosition();
    void moveCornerWidgetOnOwnPosition();

    void switchVerticalScrollBarDisplay();
    void switchHorizontalScrollBarDisplay();
    void switchCornerWidgetDisplay();

    void setNeededVerticalScrollBarMaximum();
    void setNeededHorizontalScrollBarMaximum();

private:
    JVScrollBar *verticalScrollBar_;
    JHScrollBar *horizontalScrollBar_;
    QWidget *widget_;
    JWidget *cornerWidget_;

    int verticalScrollBarPosition_;
    int horizontalScrollBarPosition_;

    int verticalScrollBarPolicy_;
    int horizontalScrollBarPolicy_;
};

#endif // JSCROLLAREA_H
