#ifndef JVSCROLLBAR_H
#define JVSCROLLBAR_H

// Дата создания виджета: ??.??.2016
// Дата завершения создания: ??.??.2016
// От Dark Jedi
// Стандарт программирования Dark Jedi v2
// Версия: 2.0.0
// Исправлено ошибок после релиза версии 1.0.0: 0

#include "JAbstractScrollBar.h"

class JVScrollBar : public JAbstractScrollBar
{
    Q_OBJECT
//PUBLIC
public:
    //ОСНОВНЫЕ ФУНКЦИИ
        JVScrollBar(QWidget *parent = 0);
        virtual ~JVScrollBar() {}
        int heightWidgetOfParent() const; //высота виджета, который скроллится
        //минимальные размеры
        int sliderMinumumHeight() const;
        void setSliderMinimumHeight(int height);
//PROTECTED
protected:
    //СОБЫТИЯ
        virtual void paintEvent(QPaintEvent *);
        virtual void mousePressEvent(QMouseEvent *);
        virtual void mouseMoveEvent(QMouseEvent *);
    //ПОЛИГОНЫ ИКОНОК - ВОЗВРАЩЕНИЕ
        QPolygonF subArrowIconPolygon() const;
        QPolygonF plusArrowIconPolygon() const;
    //ПРЯМОУГОЛЬНЫЕ ОБЛАСТИ
        QRect rectContents() const; //rect rect()'a внутри границы
        QRect contentsRect() const; //rect содержимого самого scrollbar'a
        QRect subArrowRect() const; //rect кнопки стрелки вверх/влево (вместе с границей)
        QRect plusArrowRect() const; //rect кнопки стрелки вниз/вправо (вместе с границей)
        QRect subArrowRectContents() const; //rect subArrowRect внутри границы
        QRect plusArrowRectContents() const; //rect plusArrowRect внутри границы
        QRect innerContentsRect() const; //rect пространства слайдера
        QRect innerContentsRectContents() const; //rect пространства слайдера внутри граница innerContentsRect
        QRectF sliderRect() const; //rect слайдера (вместе с границей)
        QRectF sliderContents() const;
        QRect subPageStepRect() const; //rect пустого пространства между subArray и слайдером
        QRect plusPageStepRect() const; //rect пустого пространства между plusArray и слайдером
    //РАЗМЕРЫ - ВОЗВРАЩЕНИЕ
        QSize subArrowSize() const;
        QSize plusArrowSize() const;
    //ВСПОМОГАТЕЛЬНЫЕ ФУНКЦИИ
        float singleStepForWidgetToUse() const;
        bool isFixedSliderWidth() const;
        bool isFixedSliderHeight() const;
        bool isFixedSubArrowWidth() const;
        bool isFixedSubArrowHeight() const;
        bool isFixedPlusArrowWidth() const;
        bool isFixedPlusArrowHeight() const;
        bool isPointOnRect(const QRectF &rect, const QPoint &point) const; //лежит ли заданая точка на заданой области
        bool isPointOnRect(const QRect &rect, const QPoint &point) const; //лежит ли заданая точка на заданой области
//PRIVATE
private:
    //ПРИВАТНЫЕ ДАННЫЕ
        QRectF sliderOldRect; //rect слайдера до движения
        QPoint mouseOld; //предыдущая координата нажатия мышки
        int oldValue; //предыдущее значение
        //минимальные размеры
        int v_sliderMinimumHeight;
};

#endif // JVSCROLLBAR_H
