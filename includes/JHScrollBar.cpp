#include "JHScrollBar.h"
#include <QMouseEvent>
#include <QPainter>

//ОСНОВНЫЕ ФУНКЦИИ
    JHScrollBar::JHScrollBar(QWidget *parent) : JAbstractScrollBar(parent) {
        //минимальные размеры
        v_sliderMinimumWidth = 10;
    }
    JHScrollBar::JHScrollBar(const JVScrollBar &obj) {
        //установка стандартных данных
            v_singleStep = obj.singleStep();
            v_singleStepForWidget = obj.singleStepForWidget();

            setFixedHeight(obj.width());
            setContextMenuPolicy(obj.contextMenuPolicy());
        //установка стандартных стилей
            //цвет фона
            v_globalBrushColor = obj.globalBrushColor();
            v_innerContentsBrushColor = obj.innerContentsBrushColor();
            v_subArrowBrushColor = obj.subArrowBrushColor();
            v_plusArrowBrushColor = obj.plusArrowBrushColor();
            v_sliderBrushColor = obj.sliderBrushColor();
            v_subArrowIconColor = obj.subArrowIconColor();
            v_plusArrowIconColor = obj.plusArrowIconColor();
            //изображение фона
            v_sliderBrushImage = obj.sliderBrushImage();
            //цвет границы
            v_globalBorderColor = obj.globalBorderColor();
            v_innerContentsBorderColor = obj.innerContentsBorderColor();
            v_subArrowBorderColor = obj.subArrowBorderColor();
            v_plusArrowBorderColor = obj.plusArrowBorderColor();
            v_sliderBorderColor = obj.sliderBorderColor();
            //ширина границы
            v_globalBorderWidth.setBorder(obj.globalBorderWidth().top(), obj.globalBorderWidth().left(),
                                          obj.globalBorderWidth().bottom(), obj.globalBorderWidth().right());
            v_innerContentsBorderWidth.setBorder(obj.innerContentsBorderWidth().top(), obj.innerContentsBorderWidth().left(),
                                                 obj.innerContentsBorderWidth().bottom(), obj.innerContentsBorderWidth().right());
            v_subArrowBorderWidth.setBorder(obj.subArrowBorderWidth().top(), obj.subArrowBorderWidth().left(),
                                            obj.subArrowBorderWidth().bottom(), obj.subArrowBorderWidth().right());
            v_plusArrowBorderWidth.setBorder(obj.plusArrowBorderWidth().top(), obj.plusArrowBorderWidth().left(),
                                             obj.plusArrowBorderWidth().bottom(), obj.plusArrowBorderWidth().right());
            v_sliderBorderWidth.setBorder(obj.sliderBorderWidth().top(), obj.sliderBorderWidth().left(),
                                          obj.sliderBorderWidth().bottom(), obj.sliderBorderWidth().right());
            //ширина отступов
            v_contentsMarginsWidth.setMargins(obj.contentsMarginsWidth().top(), obj.contentsMarginsWidth().left(),
                                              obj.contentsMarginsWidth().bottom(), obj.contentsMarginsWidth().right());
            v_innerContentsMarginsWidth.setMargins(obj.innerContentsMarginsWidth().top(), obj.innerContentsMarginsWidth().left(),
                                                   obj.innerContentsMarginsWidth().bottom(), obj.innerContentsMarginsWidth().right());
            v_sliderMarginsWidth.setMargins(obj.sliderMarginsWidth().top(), obj.sliderMarginsWidth().left(),
                                                   obj.sliderMarginsWidth().bottom(), obj.sliderMarginsWidth().right());
            //фиксированные размеры
            v_sliderFixedSize.scale(obj.sliderFixedSize().height(), obj.sliderFixedSize().width(), Qt::IgnoreAspectRatio);
            v_subArrowFixedSize.scale(obj.subArrowFixedSize().height(), obj.subArrowFixedSize().width(), Qt::IgnoreAspectRatio);
            v_plusArrowFixedSize.scale(obj.plusArrowFixedSize().height(), obj.plusArrowFixedSize().width(), Qt::IgnoreAspectRatio);
            v_subArrowIconFixedSize.scale(obj.subArrowIconFixedSize().height(), obj.subArrowIconFixedSize().width(), Qt::IgnoreAspectRatio);
            v_plusArrowIconFixedSize.scale(obj.plusArrowIconFixedSize().height(), obj.plusArrowIconFixedSize().width(), Qt::IgnoreAspectRatio);
            //минимальные размеры
            v_sliderMinimumWidth = obj.sliderMinumumHeight();
    }
//СОБЫТИЯ
    /*
     * При желании максимальной оптимизации, в реальном проекте,
     * где понадобится этот класс, можно унаследовать его и переписать paintEvent,
     * скопировав код уже с нужными настройками
    */
    void JHScrollBar::paintEvent(QPaintEvent *) {
        k = (widthWidgetOfParent() - width()) / (innerContentsRectContents().width() - sliderRect().width());
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
            painter.drawRect(v_globalBorderWidth.left() + v_contentsMarginsWidth.left() + subArrowRect().width()
                             + v_innerContentsMarginsWidth.left() + v_innerContentsBorderWidth.left(),

                             v_globalBorderWidth.top() + v_contentsMarginsWidth.top() + v_innerContentsMarginsWidth.top()
                             + v_innerContentsBorderWidth.top(),

                             width() - v_globalBorderWidth.sumWidth() - v_contentsMarginsWidth.sumWidth()
                             - v_innerContentsMarginsWidth.sumWidth() - v_innerContentsBorderWidth.sumWidth()
                             - subArrowRect().width() - plusArrowRect().width(),

                             height() - v_globalBorderWidth.sumHeight() - v_contentsMarginsWidth.sumHeight()
                             - v_innerContentsMarginsWidth.sumHeight() - v_innerContentsBorderWidth.sumHeight());
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
    void JHScrollBar::mousePressEvent(QMouseEvent *event) {
        //выбор кнопки мыши
        switch (event->buttons()) {
            //левая кнопка
            case Qt::LeftButton:
                mouseOld.setX(event->x());
                mouseOld.setY(event->y());
                sliderOldRect = sliderRect();
                oldValue = value();
                //нажатие на правую стрелку
                if (isPointOnRect(plusArrowRect(), event->pos())) setValue(value() + singleStepForWidgetToUse() + 1/k); // + 1/k - костыль. Не убирать.
                //нажатие на левую стрелку
                else if (isPointOnRect(subArrowRect(), event->pos())) setValue(value() - singleStepForWidgetToUse());
                //нажатие на область между plusArray и слайдером
                else if (isPointOnRect(plusPageStepRect(), event->pos())) setValue(value() + pageStep()); //все еще немножко непонятно
                //нажатие на область мнжду subArray и слайдером
                else if (isPointOnRect(subPageStepRect(), event->pos())) setValue(value() - pageStep()); //все еще немножко непонятно
            break;
        }
    }
    void JHScrollBar::mouseMoveEvent(QMouseEvent *event) {
    //выбор нажатой кнопки при движении мыши
    switch (event->buttons()) {
        //левая кнопка мыши
        case Qt::LeftButton:
            //нажатие на слайдер
            if (isPointOnRect(sliderOldRect, mouseOld)) {
                setValue(oldValue + event->x() - mouseOld.x());
                repaint(innerContentsRectContents());
            }
        break;
        default: return;
    }
}
//ПОЛИГОНЫ ИКОНОК
    QPolygonF JHScrollBar::subArrowIconPolygon() const {
                          //левая вершина
    return QPolygonF() << QPointF(subArrowRectContents().center().x() - v_subArrowIconFixedSize.width()/2.0,
                                  subArrowRectContents().center().y())
                          //правая нижняя вершина
                       << QPointF(subArrowRectContents().center().x() + v_subArrowIconFixedSize.width()/2.0,
                                  subArrowRectContents().center().y() + v_subArrowIconFixedSize.height()/2.0)
                          //правая верхняя вершина
                       << QPointF(subArrowRectContents().center().x() + v_subArrowIconFixedSize.width()/2.0,
                                  subArrowRectContents().center().y() - v_subArrowIconFixedSize.height()/2.0);
}
    QPolygonF JHScrollBar::plusArrowIconPolygon() const {
                          //правая вершина
    return QPolygonF() << QPointF(plusArrowRectContents().center().x() + v_plusArrowIconFixedSize.width()/2.0,
                                  plusArrowRectContents().center().y())
                          //левая нижняя вершина
                       << QPointF(plusArrowRectContents().center().x() - v_plusArrowIconFixedSize.width()/2.0,
                                  plusArrowRectContents().center().y() + v_plusArrowIconFixedSize.height()/2.0)
                          //левая верхняя вершина
                       << QPointF(plusArrowRectContents().center().x() - v_plusArrowIconFixedSize.width()/2.0,
                                  plusArrowRectContents().center().y() - v_plusArrowIconFixedSize.height()/2.0);
}
//ПРЯМОУГОЛЬНЫЕ ОБЛАСТИ
    QRect JHScrollBar::rectContents() const {
        return QRect(v_globalBorderWidth.left(), v_globalBorderWidth.top(),
                     width() - v_globalBorderWidth.left() - v_globalBorderWidth.right(), height() - v_globalBorderWidth.top() - v_globalBorderWidth.bottom());
    }
    QRect JHScrollBar::contentsRect() const {
        return QRect(v_globalBorderWidth.left() + v_contentsMarginsWidth.left(),
                     v_globalBorderWidth.top() + v_contentsMarginsWidth.top(),
                     width() - v_globalBorderWidth.left() - v_globalBorderWidth.right() - v_contentsMarginsWidth.left() - v_contentsMarginsWidth.right(),
                     height() - v_globalBorderWidth.top() - v_globalBorderWidth.bottom() - v_contentsMarginsWidth.top() - v_contentsMarginsWidth.bottom());
    }
    QRect JHScrollBar::subArrowRect() const {
                     //x
        return QRect(v_globalBorderWidth.left() + v_contentsMarginsWidth.left(),
                     //y
                     v_globalBorderWidth.top() + v_contentsMarginsWidth.top()
                     + (height() - v_globalBorderWidth.top() - v_globalBorderWidth.bottom() - v_contentsMarginsWidth.top() - v_contentsMarginsWidth.bottom())/2
                     - subArrowSize().height()/2,
                     //width, height
                     subArrowSize().width(), subArrowSize().height());
    }
    QRect JHScrollBar::plusArrowRect() const {
                     //x
        return QRect(v_globalBorderWidth.left() + v_contentsMarginsWidth.left()
                     + width() - v_globalBorderWidth.left() - v_globalBorderWidth.right() - v_contentsMarginsWidth.left() - v_contentsMarginsWidth.right()
                     - plusArrowSize().width(),
                     //y
                     v_globalBorderWidth.top() + v_contentsMarginsWidth.top()
                     + (height() - v_globalBorderWidth.top() - v_globalBorderWidth.bottom() - v_contentsMarginsWidth.top() - v_contentsMarginsWidth.bottom())/2
                     - plusArrowSize().height()/2,
                     //width, height
                     plusArrowSize().width(), plusArrowSize().height());
    }
    QRect JHScrollBar::subArrowRectContents() const {
                     //x
        return QRect(v_globalBorderWidth.left() + v_contentsMarginsWidth.left() + v_subArrowBorderWidth.left(),
                     //y
                     v_globalBorderWidth.top() + v_contentsMarginsWidth.top()
                     + (height() - v_globalBorderWidth.top() - v_globalBorderWidth.bottom() - v_contentsMarginsWidth.top() - v_contentsMarginsWidth.bottom())/2
                     - subArrowSize().height()/2
                     + v_subArrowBorderWidth.top(),
                     //width
                     subArrowSize().width() - v_subArrowBorderWidth.left() - v_subArrowBorderWidth.right(),
                     //height
                     subArrowSize().height() - v_subArrowBorderWidth.top() - v_subArrowBorderWidth.bottom());
    }
    QRect JHScrollBar::plusArrowRectContents() const {
                      //x
        return QRect(v_globalBorderWidth.left() + v_contentsMarginsWidth.left()
                     + width() - v_globalBorderWidth.left() - v_globalBorderWidth.right() - v_contentsMarginsWidth.left() - v_contentsMarginsWidth.right()
                     - plusArrowSize().width()
                     + v_plusArrowBorderWidth.left(),
                     //y
                     v_globalBorderWidth.top() + v_contentsMarginsWidth.top()
                     + (height() - v_globalBorderWidth.top() - v_globalBorderWidth.bottom() - v_contentsMarginsWidth.top() - v_contentsMarginsWidth.bottom())/2
                     - plusArrowSize().height()/2
                     + v_plusArrowBorderWidth.top(),
                     //width
                     plusArrowSize().width() - v_plusArrowBorderWidth.left() - v_plusArrowBorderWidth.right(),
                     //height
                     plusArrowSize().height() - v_plusArrowBorderWidth.top() - v_plusArrowBorderWidth.bottom());
    }
    QRect JHScrollBar::innerContentsRect() const {
                     //x
        return QRect(v_globalBorderWidth.left() + v_contentsMarginsWidth.left() + v_innerContentsMarginsWidth.left()
                     + subArrowRect().width(),
                     //y
                     v_globalBorderWidth.top() + v_contentsMarginsWidth.top() + v_innerContentsMarginsWidth.top(),
                     //width
                     width() - v_globalBorderWidth.left() - v_globalBorderWidth.right() - v_contentsMarginsWidth.left() - v_contentsMarginsWidth.right()
                     - v_innerContentsMarginsWidth.left() - v_innerContentsMarginsWidth.right() - subArrowRect().width() - plusArrowRect().width(),
                     //height
                     height() - v_globalBorderWidth.top() - v_globalBorderWidth.bottom() - v_contentsMarginsWidth.top() - v_contentsMarginsWidth.bottom()
                     - v_innerContentsMarginsWidth.top() - v_innerContentsMarginsWidth.bottom());
    }
    QRect JHScrollBar::innerContentsRectContents() const {
                     //x
        return QRect(v_globalBorderWidth.left() + v_contentsMarginsWidth.left() + subArrowRect().width()
                     + v_innerContentsMarginsWidth.left() + v_innerContentsBorderWidth.left()
                     + v_sliderMarginsWidth.left(),
                     //y
                     v_globalBorderWidth.top() + v_contentsMarginsWidth.top() + v_innerContentsMarginsWidth.top()
                     + v_innerContentsBorderWidth.top()
                     + v_sliderMarginsWidth.top(),
                     //width
                     width() - v_globalBorderWidth.sumWidth() - v_contentsMarginsWidth.sumWidth()
                     - v_innerContentsMarginsWidth.sumWidth() - v_innerContentsBorderWidth.sumWidth()
                     - subArrowRect().width() - plusArrowRect().width()
                     - v_sliderMarginsWidth.sumWidth(),
                     //height
                     height() - v_globalBorderWidth.sumHeight() - v_contentsMarginsWidth.sumHeight()
                     - v_innerContentsMarginsWidth.sumHeight() - v_innerContentsBorderWidth.sumHeight()
                     - v_sliderMarginsWidth.sumHeight());
    }
    QRectF JHScrollBar::sliderRect() const {
    float sliderWidth, sliderHeight;
    //ширина
    if (!isFixedSliderWidth()) {
        //проверка и установка минимальной ширины
        sliderWidth = innerContentsRectContents().width() * width() / float(widthWidgetOfParent());
        if (sliderWidth < v_sliderMinimumWidth) sliderWidth = v_sliderMinimumWidth;
    }
    else sliderWidth = v_sliderFixedSize.width();
    //высота
    if (!isFixedSliderHeight()) sliderHeight = innerContentsRectContents().height();
    else sliderHeight = v_sliderFixedSize.height();
    //результат
    return QRectF(innerContentsRectContents().x() + value(), innerContentsRectContents().center().y() - sliderHeight/2.0, sliderWidth, sliderHeight);
}
    QRectF JHScrollBar::sliderContents() const {
    return QRectF(sliderRect().x() + v_sliderBorderWidth.left(),
                 sliderRect().y() + v_sliderBorderWidth.top(),
                 sliderRect().width() - v_sliderBorderWidth.left() - v_sliderBorderWidth.right(),
                 sliderRect().height() - v_sliderBorderWidth.top() - v_sliderBorderWidth.bottom());
}
    QRect JHScrollBar::subPageStepRect() const {
    return QRect(QPoint(subArrowRect().x() + 1, contentsRect().y() + 1), QPoint(sliderRect().left() - 1, contentsRect().bottom() - 1));
}
    QRect JHScrollBar::plusPageStepRect() const {
    return QRect(QPoint(sliderRect().right() + 1, contentsRect().y() + 1), QPoint(plusArrowRect().left() - 1, contentsRect().bottom() - 1));
}
//РАЗМЕРЫ - ВОЗВРАЩЕНИЕ
    QSize JHScrollBar::subArrowSize() const {
    int width, height;
    //ширина
    if (!isFixedSubArrowWidth()) width = contentsRect().height();
    else width = v_subArrowFixedSize.width();
    //высота
    if (!isFixedSubArrowHeight()) height = contentsRect().height();
    else height = v_subArrowFixedSize.height();
    //result
    return QSize(width, height);
}
    QSize JHScrollBar::plusArrowSize() const {
    int width, height;
    //ширина
    if (!isFixedPlusArrowWidth()) width = contentsRect().height();
    else width = v_plusArrowFixedSize.width();
    //высота
    if (!isFixedPlusArrowHeight()) height = contentsRect().height();
    else height = v_plusArrowFixedSize.height();
    //result
    return QSize(width, height);
}
    int JHScrollBar::widthWidgetOfParent() const {
    return width()+maximum();
}
//ВСПОМОГАТЕЛЬНЫЕ ФУНКЦИИ
    float JHScrollBar::singleStepForWidgetToUse() const {
        if (v_singleStepForWidget) return v_singleStep/k;
        else return v_singleStep;
    }
    bool JHScrollBar::isFixedSliderWidth() const {
        if (v_sliderFixedSize.width() != -1) return true;
        else return false;
    }
    bool JHScrollBar::isFixedSliderHeight() const {
        if (v_sliderFixedSize.height() != -1) return true;
        else return false;
    }
    bool JHScrollBar::isFixedSubArrowWidth() const {
        if (v_subArrowFixedSize.width() != -1) return true;
        else return false;
    }
    bool JHScrollBar::isFixedSubArrowHeight() const {
        if (v_subArrowFixedSize.height() != -1) return true;
        else return false;
    }
    bool JHScrollBar::isFixedPlusArrowWidth() const {
        if (v_subArrowFixedSize.width() != -1) return true;
        else return false;
    }
    bool JHScrollBar::isFixedPlusArrowHeight() const {
        if (v_subArrowFixedSize.height() != -1) return true;
        else return false;
    }
    bool JHScrollBar::isPointOnRect(const QRectF &rect, const QPoint &point) const {
    if (point.x() >= rect.left() && point.x() <= rect.right() && point.y() >= rect.top() && point.y() <= rect.bottom()) return true;
    else return false;
}
    bool JHScrollBar::isPointOnRect(const QRect &rect, const QPoint &point) const {
    if (point.x() >= rect.left() && point.x() <= rect.right() && point.y() >= rect.top() && point.y() <= rect.bottom()) return true;
    else return false;
}
    //минимальные размеры
    int JHScrollBar::sliderMinumumWidth() const {
            return v_sliderMinimumWidth;
        }
    void JHScrollBar::setSliderMinimumWidth(int width) {
        v_sliderMinimumWidth = width;
    }
