#include "JVScrollBar.h"
#include <QMouseEvent>
#include <QPainter>

//ОСНОВНЫЕ ФУНКЦИИ
    JVScrollBar::JVScrollBar(QWidget *parent) : JAbstractScrollBar(parent) {
        //минимальные размеры
        v_sliderMinimumHeight = 10;
    }
    int JVScrollBar::heightWidgetOfParent() const {
        return height()+maximum();
    }
//СОБЫТИЯ
    /*
     * При желании максимальной оптимизации, в реальном проекте,
     * где понадобится этот класс, можно унаследовать его и переписать paintEvent,
     * скопировав код уже с нужными настройками
    */
    void JVScrollBar::paintEvent(QPaintEvent *) {
        k = (heightWidgetOfParent() - height()) / (innerContentsRectContents().height() - sliderRect().height());
        QPainter painter(this);
        painter.setPen(Qt::NoPen);
        //глобальное
            //граница
            painter.setBrush(v_globalBorderColor);
            painter.drawRect(rect());
            //фон
            painter.setBrush(v_globalBrushColor);
            painter.drawRect(rectContents());
        //innerRect
            //граница
            painter.setBrush(v_innerContentsBorderColor);
            painter.drawRect(innerContentsRect());
            //фон
            painter.setBrush(v_innerContentsBrushColor);
            painter.drawRect(v_globalBorderWidth.left() + v_contentsMarginsWidth.left()
                             + v_innerContentsMarginsWidth.left() + v_innerContentsBorderWidth.left(),

                             v_globalBorderWidth.top() + v_contentsMarginsWidth.top() + v_innerContentsMarginsWidth.top()
                             + subArrowRect().height() + v_innerContentsBorderWidth.top(),

                             width() - v_globalBorderWidth.sumWidth() -  v_contentsMarginsWidth.sumWidth() - v_innerContentsMarginsWidth.sumWidth()
                             - v_innerContentsBorderWidth.sumWidth() - v_sliderMarginsWidth.sumWidth(),

                             height() - v_globalBorderWidth.sumHeight() - v_contentsMarginsWidth.sumHeight()
                             - v_innerContentsMarginsWidth.sumHeight() - subArrowRect().height() - plusArrowRect().height()
                             - v_innerContentsBorderWidth.sumHeight());
        //верхняя/левая стрелка
            //граница
            painter.setBrush(v_subArrowBorderColor);
            painter.drawRect(subArrowRect());
            //фон
            painter.setBrush(v_subArrowBrushColor);
            painter.drawRect(subArrowRectContents());
        //нижняя/правая стрелка
            //граница
            painter.setBrush(v_plusArrowBorderColor);
            painter.drawRect(plusArrowRect());
            //фон
            painter.setBrush(v_plusArrowBrushColor);
            painter.drawRect(plusArrowRectContents());
        //иконки стрелок
            //верхняя/левая стрелка
            painter.setRenderHint(QPainter::Antialiasing, true);
            painter.setBrush(v_subArrowIconColor);
            painter.drawPolygon(subArrowIconPolygon());
            //нижняя/правая стрелка
            painter.setBrush(v_plusArrowIconColor);
            painter.drawPolygon(plusArrowIconPolygon());
            painter.setRenderHint(QPainter::Antialiasing, false);
        //слайдер
            //граница
            painter.setBrush(v_sliderBorderColor);
            painter.drawRect(sliderRect());
            //фон
            painter.setBrush(v_sliderBrushColor);
            painter.drawRect(sliderContents());
            if (sliderRect() == sliderRect()) //без этого возвращается NaN, если height() > heightOfParentWidget()
                painter.drawImage(sliderContents(), v_sliderBrushImage);
    }
    void JVScrollBar::mousePressEvent(QMouseEvent *event) {
        //выбор кнопки мыши
        switch (event->buttons()) {
            //левая кнопка
            case Qt::LeftButton:
                mouseOld.setX(event->x());
                mouseOld.setY(event->y());
                sliderOldRect = sliderRect();
                oldValue = value();
                //нажатие на нижнюю стрелку
                if (isPointOnRect(plusArrowRect(), event->pos())) setValue(value() + singleStepForWidgetToUse() + 1/k); // + 1/k - костыль. Не убирать.
                //нажатие на верхнюю стрелку
                else if (isPointOnRect(subArrowRect(), event->pos())) setValue(value() - singleStepForWidgetToUse());
                //нажатие на область между plusArray и слайдером
                else if (isPointOnRect(plusPageStepRect(), event->pos())) setValue(value() + pageStep()); //все еще немножко непонятно
                //нажатие на область мнжду subArray и слайдером
                else if (isPointOnRect(subPageStepRect(), event->pos())) setValue(value() - pageStep()); //все еще немножко непонятно
            break;
        }
    }
    void JVScrollBar::mouseMoveEvent(QMouseEvent *event) {
    //выбор нажатой кнопки при движении мыши
    switch (event->buttons()) {
        //левая кнопка мыши
        case Qt::LeftButton:
            //нажатие на слайдер
            if (isPointOnRect(sliderOldRect, mouseOld)) {
                setValue(oldValue + event->y() - mouseOld.y());
                repaint(innerContentsRectContents());
            }
        break;
        default: return;
    }
}
//ПОЛИГОНЫ ИКОНОК - ВОЗВРАЩЕНИЕ
    QPolygonF JVScrollBar::subArrowIconPolygon() const {
                              //верхняя вершина
        return QPolygonF() << QPointF(subArrowRectContents().center().x(), subArrowRectContents().center().y() - v_subArrowIconFixedSize.height()/2.0)
                              //нижняя правая вершина
                           << QPointF(subArrowRectContents().center().x() + v_subArrowIconFixedSize.width()/2.0,
                                      subArrowRectContents().center().y() + v_subArrowIconFixedSize.height()/2.0)
                              //нижняя левая вершина
                           << QPointF(subArrowRectContents().center().x() - v_subArrowIconFixedSize.width()/2.0,
                                      subArrowRectContents().center().y() + v_subArrowIconFixedSize.height()/2.0);
    }
    QPolygonF JVScrollBar::plusArrowIconPolygon() const {
                              //нижняя вершина
        return QPolygonF() << QPointF(plusArrowRectContents().center().x(), plusArrowRect().center().y() + v_plusArrowIconFixedSize.height()/2.0)
                              //верхняя правая вершина
                           << QPointF(plusArrowRectContents().center().x() + v_plusArrowIconFixedSize.width()/2.0,
                                      plusArrowRectContents().center().y() - v_plusArrowIconFixedSize.height()/2.0)
                              //верхняя левая вершина
                           << QPointF(plusArrowRectContents().center().x() - v_plusArrowIconFixedSize.width()/2.0,
                                      plusArrowRectContents().center().y() - v_plusArrowIconFixedSize.height()/2.0);
    }
//ПРЯМОУГОЛЬНЫЕ ОБЛАСТИ
    QRect JVScrollBar::rectContents() const {
        return QRect(v_globalBorderWidth.left(), v_globalBorderWidth.top(),
                     width() - v_globalBorderWidth.left() - v_globalBorderWidth.right(), height() - v_globalBorderWidth.top() - v_globalBorderWidth.bottom());
    }
    QRect JVScrollBar::contentsRect() const {
        return QRect(v_globalBorderWidth.left() + v_contentsMarginsWidth.left(),
                     v_globalBorderWidth.top() + v_contentsMarginsWidth.top(),
                     width() - v_globalBorderWidth.left() - v_globalBorderWidth.right() - v_contentsMarginsWidth.left() - v_contentsMarginsWidth.right(),
                     height() - v_globalBorderWidth.top() - v_globalBorderWidth.bottom() - v_contentsMarginsWidth.top() - v_contentsMarginsWidth.bottom());
    }
    QRect JVScrollBar::subArrowRect() const {
                     //x
        return QRect(v_globalBorderWidth.left() + v_contentsMarginsWidth.left()
                     + (width() - v_globalBorderWidth.left() - v_globalBorderWidth.right() - v_contentsMarginsWidth.left() - v_contentsMarginsWidth.right())/2
                     - subArrowSize().width()/2,
                     //y
                     v_globalBorderWidth.top() + v_contentsMarginsWidth.top(),
                     //width, height
                     subArrowSize().width(), subArrowSize().height());
    }
    QRect JVScrollBar::plusArrowRect() const {
                     //x
        return QRect(v_globalBorderWidth.left() + v_contentsMarginsWidth.left()
                     + (width() - v_globalBorderWidth.left() - v_globalBorderWidth.right() - v_contentsMarginsWidth.left() - v_contentsMarginsWidth.right())/2
                     - plusArrowSize().width()/2,
                     //y
                     v_globalBorderWidth.top() + v_contentsMarginsWidth.top() +
                     height() - v_globalBorderWidth.top() - v_globalBorderWidth.bottom() - v_contentsMarginsWidth.top() - v_contentsMarginsWidth.bottom()
                     - plusArrowSize().height(),
                     //width, height
                     plusArrowSize().width(), plusArrowSize().height());
    }
    QRect JVScrollBar::subArrowRectContents() const {
                     //x
        return QRect(v_globalBorderWidth.left() + v_contentsMarginsWidth.left()
                     + (width() - v_globalBorderWidth.left() - v_globalBorderWidth.right() - v_contentsMarginsWidth.left() - v_contentsMarginsWidth.right())/2
                     - subArrowSize().width()/2 + v_subArrowBorderWidth.left(),
                     //y
                     v_globalBorderWidth.top() + v_contentsMarginsWidth.top() + v_subArrowBorderWidth.top(),
                     //width
                     subArrowSize().width() - v_subArrowBorderWidth.left() - v_subArrowBorderWidth.right(),
                     //height
                     subArrowSize().height() - v_subArrowBorderWidth.top() - v_subArrowBorderWidth.bottom());
    }
    QRect JVScrollBar::plusArrowRectContents() const {
                      //x
        return QRect(v_globalBorderWidth.left() + v_contentsMarginsWidth.left()
                     + (width() - v_globalBorderWidth.left() - v_globalBorderWidth.right() - v_contentsMarginsWidth.left() - v_contentsMarginsWidth.right())/2
                     - plusArrowSize().width()/2 + v_plusArrowBorderWidth.left(),
                     //y
                     v_globalBorderWidth.top() + v_contentsMarginsWidth.top() +
                     height() - v_globalBorderWidth.top() - v_globalBorderWidth.bottom() - v_contentsMarginsWidth.top() - v_contentsMarginsWidth.bottom()
                     - plusArrowSize().height() + v_plusArrowBorderWidth.top(),
                     //width
                     plusArrowSize().width() - v_plusArrowBorderWidth.left() - v_plusArrowBorderWidth.right(),
                     //height
                     plusArrowSize().height() - v_plusArrowBorderWidth.top() - v_plusArrowBorderWidth.bottom());
    }
    QRect JVScrollBar::innerContentsRect() const {
                     //x
        return QRect(v_globalBorderWidth.left() + v_contentsMarginsWidth.left()
                     + v_innerContentsMarginsWidth.left(),
                     //y
                     v_globalBorderWidth.top() + v_contentsMarginsWidth.top() + v_innerContentsMarginsWidth.top()
                     + subArrowRect().height(),
                     //width
                     width() - v_globalBorderWidth.left() - v_globalBorderWidth.right() - v_contentsMarginsWidth.left() - v_contentsMarginsWidth.right()
                     - v_innerContentsMarginsWidth.left() - v_innerContentsMarginsWidth.right(),
                     //height
                     height() - v_globalBorderWidth.top() - v_globalBorderWidth.bottom() - v_contentsMarginsWidth.top() - v_contentsMarginsWidth.bottom()
                     - v_innerContentsMarginsWidth.top() - v_innerContentsMarginsWidth.bottom() - subArrowRect().height() - plusArrowRect().height());
    }
    QRect JVScrollBar::innerContentsRectContents() const {
                     //x
        return QRect(v_globalBorderWidth.left() + v_contentsMarginsWidth.left()
                     + v_innerContentsMarginsWidth.left() + v_innerContentsBorderWidth.left()
                     + v_sliderMarginsWidth.left(),
                     //y
                     v_globalBorderWidth.top() + v_contentsMarginsWidth.top() + v_innerContentsMarginsWidth.top()
                     + subArrowRect().height() + v_innerContentsBorderWidth.top()
                     + v_sliderMarginsWidth.top(),
                     //width
                     width() - v_globalBorderWidth.sumWidth() -  v_contentsMarginsWidth.sumWidth() - v_innerContentsMarginsWidth.sumWidth()
                     - v_innerContentsBorderWidth.sumWidth() - v_sliderMarginsWidth.sumWidth(),
                     //height
                     height() - v_globalBorderWidth.sumHeight() - v_contentsMarginsWidth.sumHeight()
                     - v_innerContentsMarginsWidth.sumHeight() - subArrowRect().height() - plusArrowRect().height()
                     - v_innerContentsBorderWidth.sumHeight() - v_sliderMarginsWidth.sumHeight());
    }
    QRectF JVScrollBar::sliderRect() const {
    float sliderWidth, sliderHeight;
    //ширина
    if (!isFixedSliderWidth()) sliderWidth = innerContentsRectContents().width();
    else sliderWidth = v_sliderFixedSize.width();
    //высота
    if (!isFixedSliderHeight()) {
        //проверка и установка минимальной высоты
        sliderHeight = innerContentsRectContents().height() * height() / float(heightWidgetOfParent());
        if (sliderHeight < v_sliderMinimumHeight) sliderHeight = v_sliderMinimumHeight;
    }
    else sliderHeight = v_sliderFixedSize.height();
    //результат
    return QRectF(innerContentsRectContents().center().x() - sliderWidth/2.0, innerContentsRectContents().y() + value(), sliderWidth, sliderHeight);
}
    QRectF JVScrollBar::sliderContents() const {
    return QRectF(sliderRect().x() + v_sliderBorderWidth.left(),
                 sliderRect().y() + v_sliderBorderWidth.top(),
                 sliderRect().width() - v_sliderBorderWidth.left() - v_sliderBorderWidth.right(),
                 sliderRect().height() - v_sliderBorderWidth.top() - v_sliderBorderWidth.bottom());
}
    QRect JVScrollBar::subPageStepRect() const {
    return QRect(QPoint(contentsRect().x() + 1, subArrowRect().y() + 1), QPoint(contentsRect().right() - 1, sliderRect().top() - 1));
}
    QRect JVScrollBar::plusPageStepRect() const {
    return QRect(QPoint(contentsRect().x() + 1, sliderRect().bottom() + 1), QPoint(contentsRect().right() - 1, plusArrowRect().top() - 1));
}
//РАЗМЕРЫ ВОЗВРАЩЕНИЕ
    QSize JVScrollBar::subArrowSize() const {
    int width, height;
    //ширина
    if (!isFixedSubArrowWidth()) width = contentsRect().width();
    else width = v_subArrowFixedSize.width();
    //высота
    if (!isFixedSubArrowHeight()) height = contentsRect().width();
    else height = v_subArrowFixedSize.height();
    //result
    return QSize(width, height);
}
    QSize JVScrollBar::plusArrowSize() const {
    int width, height;
    //ширина
    if (!isFixedPlusArrowWidth()) width = contentsRect().width();
    else width = v_plusArrowFixedSize.width();
    //высота
    if (!isFixedPlusArrowHeight()) height = contentsRect().width();
    else height = v_plusArrowFixedSize.height();
    //result
    return QSize(width, height);
}
//ВСПОМОГАТЕЛЬНЫЕ ФУНКЦИИ
    float JVScrollBar::singleStepForWidgetToUse() const {
        if (v_singleStepForWidget) return v_singleStep/k;
        else return v_singleStep;
    }
    bool JVScrollBar::isFixedSliderWidth() const {
        if (v_sliderFixedSize.width() != -1) return true;
        else return false;
    }
    bool JVScrollBar::isFixedSliderHeight() const {
        if (v_sliderFixedSize.height() != -1) return true;
        else return false;
    }
    bool JVScrollBar::isFixedSubArrowWidth() const {
        if (v_subArrowFixedSize.width() != -1) return true;
        else return false;
    }
    bool JVScrollBar::isFixedSubArrowHeight() const {
        if (v_subArrowFixedSize.height() != -1) return true;
        else return false;
    }
    bool JVScrollBar::isFixedPlusArrowWidth() const {
        if (v_subArrowFixedSize.width() != -1) return true;
        else return false;
    }
    bool JVScrollBar::isFixedPlusArrowHeight() const {
        if (v_subArrowFixedSize.height() != -1) return true;
        else return false;
    }
    bool JVScrollBar::isPointOnRect(const QRectF &rect, const QPoint &point) const {
        if (point.x() >= rect.left() && point.x() <= rect.right() && point.y() >= rect.top() && point.y() <= rect.bottom()) return true;
        else return false;
    }
    bool JVScrollBar::isPointOnRect(const QRect &rect, const QPoint &point) const {
        if (point.x() >= rect.left() && point.x() <= rect.right() && point.y() >= rect.top() && point.y() <= rect.bottom()) return true;
        else return false;
    }
    //минимальные размеры
    int JVScrollBar::sliderMinumumHeight() const {
        return v_sliderMinimumHeight;
    }
    void JVScrollBar::setSliderMinimumHeight(int height) {
        v_sliderMinimumHeight = height;
    }
