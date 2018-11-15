#ifndef JABSTRACTSCROLLBAR_H
#define JABSTRACTSCROLLBAR_H

// Дата создания: 19.06.2016
// Дата завершения создания: 19.06.2016
// От Dark Jedi
// Стандарт программирования Dark Jedi v2
// Версия: 1.0.0
// Исправлено ошибок после релиза версии 1.0.0: 0

#include <QScrollBar>
#include "JBorder.h"
#include "JMargins.h"

class JAbstractScrollBar : public QScrollBar
{
public:
    JAbstractScrollBar(QWidget *parent = 0);
    virtual ~JAbstractScrollBar();

    float value() const; //значение скроллинга
    int singleStep() const;
    bool singleStepForWidget() const;
    void setValue(int); //установить значение скроллинга
    void setSingleStep(int); //устанавливает количество пикселей, на которое нужно приблизительно прокрутить слайдер (не виджет), при нажатии на стрелки
    void setSingleStepForWidget(bool);

    //СТИЛИ - ВОЗВРАЩЕНИЕ
        //цвет фона
        QColor globalBrushColor() const;
        QColor innerContentsBrushColor() const;
        QColor subArrowBrushColor() const;
        QColor plusArrowBrushColor() const;
        QColor sliderBrushColor() const;
        QColor subArrowIconColor() const;
        QColor plusArrowIconColor() const;
        //изображение фона
        QImage sliderBrushImage() const;
        //цвет границы
        QColor globalBorderColor() const;
        QColor innerContentsBorderColor() const;
        QColor subArrowBorderColor() const;
        QColor plusArrowBorderColor() const;
        QColor sliderBorderColor() const;
        //ширина границы
        JBorder globalBorderWidth() const;
        JBorder innerContentsBorderWidth() const;
        JBorder subArrowBorderWidth() const;
        JBorder plusArrowBorderWidth() const;
        JBorder sliderBorderWidth() const;
        //отступы
        JMargins contentsMarginsWidth() const;
        JMargins innerContentsMarginsWidth() const;
        JMargins sliderMarginsWidth() const;
        //фиксированные размеры
        QSize sliderFixedSize() const;
        QSize subArrowFixedSize() const;
        QSize plusArrowFixedSize() const;
        QSize subArrowIconFixedSize() const;
        QSize plusArrowIconFixedSize() const;
    //СТИЛИ - УСТАНОВКА
        //цвет фона
        void setGlobalBrushColor(const QColor &color);
        void setInnerContentsBrushColor(const QColor &color);
        void setSubArrowBrushColor(const QColor &color);
        void setPlusArrowBrushColor(const QColor &color);
        void setSliderBrushColor(const QColor &color);
        void setSubArrowIconColor(const QColor &color);
        void setPlusArrowIconColor(const QColor &color);
        //изображение фона
        void setSliderBrushImage(const QImage &image);
        //цвет границы
        void setGlobalBorderColor(const QColor &color);
        void setInnerContentsBorderColor(const QColor &color);
        void setSubArrowBorderColor(const QColor &color);
        void setPlusArrowBorderColor(const QColor &color);
        void setSliderBorderColor(const QColor &color);
        //ширина границы
        void setGlobalBorderWidth(int left, int top, int right, int bottom);
        void setInnerContentsBorderWidth(int left, int top, int right, int bottom);
        void setSubArrowBorderWidth(int left, int top, int right, int bottom);
        void setPlusArrowBorderWidth(int left, int top, int right, int bottom);
        void setSliderBorderWidth(int left, int top, int right, int bottom);
        //отступы
        void setContentsMarginsWidth(int left, int top, int right, int bottom);
        void setInnerContentsMarginsWidth(int left, int top, int right, int bottom);
        void setSliderMarginsWidth(int left, int top, int right, int bottom);
        //фиксированные размеры
        void setSliderFixedSize(int width, int height);
        void setSliderFixedWidth(int width);
        void setSliderFixedHeight(int height);
        void setSubArrowFixedSize(int width, int height);
        void setSubArrowFixedWidth(int width);
        void setSubArrowFixedHeight(int height);
        void setPlusArrowFixedSize(int width, int height);
        void setPlusArrowFixedWidth(int width);
        void setPlusArrowFixedHeight(int height);
        void setSubArrowIconFixedSize(int width, int height);
        void setSubArrowIconFixedWidth(int width);
        void setSubArrowIconFixedHeight(int height);
        void setPlusArrowIconFixedSize(int width, int height);
        void setPlusArrowIconFixedWidth(int width);
        void setPlusArrowIconFixedHeight(int height);

protected:
    float k; //коэффициент пропорциональности
    int v_singleStep; //прокручивает слайдер на приблизительно v_pageStep пикселей (не виджет), при нажатии на стрелки
    bool v_singleStepForWidget; //true = прокрутка виджета на v_singleStep пикселей (не слайдер), при нажатии на стрелки

    //СТИЛИ - ДАННЫЕ
        //цвет фона
        QColor v_globalBrushColor;
        QColor v_innerContentsBrushColor;
        QColor v_subArrowBrushColor;
        QColor v_plusArrowBrushColor;
        QColor v_sliderBrushColor;
        QColor v_subArrowIconColor;
        QColor v_plusArrowIconColor;
        //изображение фона
        QImage v_sliderBrushImage;
        //цвет границы
        QColor v_globalBorderColor;
        QColor v_innerContentsBorderColor;
        QColor v_subArrowBorderColor;
        QColor v_plusArrowBorderColor;
        QColor v_sliderBorderColor;
        //ширина границы
        JBorder v_globalBorderWidth;
        JBorder v_innerContentsBorderWidth;
        JBorder v_subArrowBorderWidth;
        JBorder v_plusArrowBorderWidth;
        JBorder v_sliderBorderWidth;
        //отступы
        JMargins v_contentsMarginsWidth;
        JMargins v_innerContentsMarginsWidth;
        JMargins v_sliderMarginsWidth;
        //фиксированные размеры
        QSize v_sliderFixedSize;
        QSize v_subArrowFixedSize;
        QSize v_plusArrowFixedSize;
        QSize v_subArrowIconFixedSize;
        QSize v_plusArrowIconFixedSize;
};

#endif // JABSTRACTSCROLLBAR_H
