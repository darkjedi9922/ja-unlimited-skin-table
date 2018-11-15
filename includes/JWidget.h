#ifndef JWIDGET_H
#define JWIDGET_H

// Дата создания виджета: 16.06.2016
// Дата завершения создания: 16.06.2016
// От Dark Jedi
// Стандарт программирования Dark Jedi v3
// Версия виджета: 1.0.2
// Исправлено ошибок после релиза версии 1.0.0: 2

#include <QWidget>
#include "JBorder.h"

class JWidget;

class JWidgetPrivate : public QWidget
{
public:
    explicit JWidgetPrivate(QWidget *parent = 0);
    virtual ~JWidgetPrivate();

protected:
    virtual void paintEvent(QPaintEvent *);

private:
    JWidget *parentJWidget_;
};



class JWidget : public QWidget
{
    Q_OBJECT
public:
    explicit JWidget(QWidget *parent = 0);
    virtual ~JWidget();

    QColor getGlobalBrushColor() const;
    QColor getGlobalBorderColor() const;
    JBorder getGlobalBorder() const;

    QRect calculateContentsRect() const;

    bool isAllowedRaisingBorder() const;

    void setGlobalBrushColor(const QColor &color);
    void setGlobalBorderColor(const QColor &color);
    void setGlobalBorder(const JBorder &border);
    void setGlobalBorderWidth(int left, int top, int right, int bottom);

    void allowRaisingBorder(bool);

protected:
    virtual void paintEvent(QPaintEvent *);
    virtual void resizeEvent(QResizeEvent *);
    virtual void childEvent(QChildEvent *);

    JWidgetPrivate *getBorderClass() const;

private:
    JWidgetPrivate *borderClass_;
    bool raisingBorder_;

    QColor globalBrushColor_;
    QColor globalBorderColor_;
    JBorder globalBorder_;

};

#endif // JWIDGET_H
