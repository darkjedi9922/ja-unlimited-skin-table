#include "JAbstractScrollBar.h"

JAbstractScrollBar::JAbstractScrollBar(QWidget *parent) : QScrollBar(parent)
{
    v_singleStep = 20;
    v_singleStepForWidget = false;

    //установка стандартных стилей
        //цвет фона
        v_globalBrushColor.setNamedColor("black");
        v_innerContentsBrushColor.setNamedColor("black");
        v_subArrowBrushColor.setNamedColor("black");
        v_plusArrowBrushColor.setNamedColor("black");
        v_sliderBrushColor.setNamedColor("skyblue");
        v_subArrowIconColor.setNamedColor("red");
        v_plusArrowIconColor.setNamedColor("lime");
        //изображение фона
        v_sliderBrushImage = QImage();
        //цвет границы
        v_globalBorderColor.setNamedColor("white");
        v_innerContentsBorderColor.setNamedColor("white");
        v_subArrowBorderColor.setNamedColor("red");
        v_plusArrowBorderColor.setNamedColor("lime");
        v_sliderBorderColor.setNamedColor("lightblue");
        //ширина границы
        v_globalBorderWidth.setBorder(0, 0, 0, 0);
        v_innerContentsBorderWidth.setBorder(0, 0, 0, 0);
        v_subArrowBorderWidth.setBorder(1, 1, 1, 1);
        v_plusArrowBorderWidth.setBorder(1, 1, 1, 1);
        v_sliderBorderWidth.setBorder(0, 0, 0, 0);
        //ширина отступов
        v_contentsMarginsWidth.setMargins(0, 0, 0, 0);
        v_innerContentsMarginsWidth.setMargins(0, 0, 0, 0);
        v_sliderMarginsWidth.setMargins(0, 0, 0, 0);
        //фиксированные размеры
        v_sliderFixedSize.scale(-1, -1, Qt::IgnoreAspectRatio);
        v_subArrowFixedSize.scale(-1, -1, Qt::IgnoreAspectRatio);
        v_plusArrowFixedSize.scale(-1, -1, Qt::IgnoreAspectRatio);
        v_subArrowIconFixedSize.scale(6, 6, Qt::IgnoreAspectRatio);
        v_plusArrowIconFixedSize.scale(6, 6, Qt::IgnoreAspectRatio);
}
JAbstractScrollBar::~JAbstractScrollBar() {
}

float JAbstractScrollBar::value() const {
    return QScrollBar::value()/k;
}
int JAbstractScrollBar::singleStep() const {
    return v_singleStep;
}
bool JAbstractScrollBar::singleStepForWidget() const {
    return v_singleStepForWidget;
}
void JAbstractScrollBar::setValue(int v) {
    QScrollBar::setValue(v*k);
    emit valueChanged(v*k);
}
void JAbstractScrollBar::setSingleStep(int v) {
    v_singleStep = v;
}
void JAbstractScrollBar::setSingleStepForWidget(bool v) {
    v_singleStepForWidget = v;
}

//СТИЛИ - ВОЗВРАЩЕНИЕ
    //цвет фона
    QColor JAbstractScrollBar::globalBrushColor() const {
        return v_globalBrushColor;
    }
    QColor JAbstractScrollBar::innerContentsBrushColor() const {
        return v_innerContentsBrushColor;
    }
    QColor JAbstractScrollBar::subArrowBrushColor() const {
        return v_subArrowBrushColor;
    }
    QColor JAbstractScrollBar::plusArrowBrushColor() const {
        return v_plusArrowBrushColor;
    }
    QColor JAbstractScrollBar::sliderBrushColor() const {
        return v_sliderBrushColor;
    }
    QColor JAbstractScrollBar::subArrowIconColor() const {
        return v_subArrowIconColor;
    }
    QColor JAbstractScrollBar::plusArrowIconColor() const {
        return v_plusArrowIconColor;
    }
    //изображение фона
    QImage JAbstractScrollBar::sliderBrushImage() const {
        return v_sliderBrushImage;
    }
    //цвет границы
    QColor JAbstractScrollBar::globalBorderColor() const {
        return v_globalBorderColor;
    }
    QColor JAbstractScrollBar::innerContentsBorderColor() const {
        return v_innerContentsBorderColor;
    }
    QColor JAbstractScrollBar::subArrowBorderColor() const {
        return v_subArrowBorderColor;
    }
    QColor JAbstractScrollBar::plusArrowBorderColor() const {
        return v_plusArrowBorderColor;
    }
    QColor JAbstractScrollBar::sliderBorderColor() const {
        return v_sliderBorderColor;
    }
    //ширина границы
    JBorder JAbstractScrollBar::globalBorderWidth() const {
        return v_globalBorderWidth;
    }
    JBorder JAbstractScrollBar::innerContentsBorderWidth() const {
        return v_innerContentsBorderWidth;
    }
    JBorder JAbstractScrollBar::subArrowBorderWidth() const {
        return v_subArrowBorderWidth;
    }
    JBorder JAbstractScrollBar::plusArrowBorderWidth() const {
        return v_plusArrowBorderWidth;
    }
    JBorder JAbstractScrollBar::sliderBorderWidth() const {
        return v_sliderBorderWidth;
    }
    //отступы
    JMargins JAbstractScrollBar::contentsMarginsWidth() const {
        return v_contentsMarginsWidth;
    }
    JMargins JAbstractScrollBar::innerContentsMarginsWidth() const {
        return v_innerContentsMarginsWidth;
    }
    JMargins JAbstractScrollBar::sliderMarginsWidth() const {
        return v_sliderMarginsWidth;
    }
    //фиксированные размеры
    QSize JAbstractScrollBar::sliderFixedSize() const {
        return v_sliderFixedSize;
    }
    QSize JAbstractScrollBar::subArrowFixedSize() const {
        return v_subArrowFixedSize;
    }
    QSize JAbstractScrollBar::plusArrowFixedSize() const {
        return v_plusArrowFixedSize;
    }
    QSize JAbstractScrollBar::subArrowIconFixedSize() const {
        return v_subArrowIconFixedSize;
    }
    QSize JAbstractScrollBar::plusArrowIconFixedSize() const {
        return v_plusArrowIconFixedSize;
    }

//СТИЛИ - УСТАНОВКА
    //цвет фона
    void JAbstractScrollBar::setGlobalBrushColor(const QColor &color) {
        v_globalBrushColor = color;
    }
    void JAbstractScrollBar::setInnerContentsBrushColor(const QColor &color) {
        v_innerContentsBrushColor = color;
    }
    void JAbstractScrollBar::setSubArrowBrushColor(const QColor &color) {
        v_subArrowBrushColor = color;
    }
    void JAbstractScrollBar::setPlusArrowBrushColor(const QColor &color) {
        v_plusArrowBrushColor = color;
    }
    void JAbstractScrollBar::setSliderBrushColor(const QColor &color) {
        v_sliderBrushColor = color;
    }
    void JAbstractScrollBar::setSubArrowIconColor(const QColor &color) {
        v_subArrowIconColor = color;
    }
    void JAbstractScrollBar::setPlusArrowIconColor(const QColor &color) {
        v_plusArrowIconColor = color;
    }
    //изображение фона
    void JAbstractScrollBar::setSliderBrushImage(const QImage &image) {
        v_sliderBrushImage = image;
    }
    //цвет границы
    void JAbstractScrollBar::setGlobalBorderColor(const QColor &color) {
        v_globalBorderColor = color;
    }
    void JAbstractScrollBar::setInnerContentsBorderColor(const QColor &color) {
        v_innerContentsBorderColor = color;
    }
    void JAbstractScrollBar::setSubArrowBorderColor(const QColor &color) {
        v_subArrowBorderColor = color;
    }
    void JAbstractScrollBar::setPlusArrowBorderColor(const QColor &color) {
        v_plusArrowBorderColor = color;
    }
    void JAbstractScrollBar::setSliderBorderColor(const QColor &color) {
        v_sliderBorderColor = color;
    }
    //ширина границы
    void JAbstractScrollBar::setGlobalBorderWidth(int left, int top, int right, int bottom) {
        v_globalBorderWidth.setBorder(left, top, right, bottom);
    }
    void JAbstractScrollBar::setInnerContentsBorderWidth(int left, int top, int right, int bottom) {
        v_innerContentsBorderWidth.setBorder(left, top, right, bottom);
    }
    void JAbstractScrollBar::setSubArrowBorderWidth(int left, int top, int right, int bottom) {
        v_subArrowBorderWidth.setBorder(left, top, right, bottom);
    }
    void JAbstractScrollBar::setPlusArrowBorderWidth(int left, int top, int right, int bottom) {
        v_plusArrowBorderWidth.setBorder(left, top, right, bottom);
    }
    void JAbstractScrollBar::setSliderBorderWidth(int left, int top, int right, int bottom) {
        v_sliderBorderWidth.setBorder(left, top, right, bottom);
    }
    //отступы
    void JAbstractScrollBar::setContentsMarginsWidth(int left, int top, int right, int bottom) {
        v_contentsMarginsWidth.setMargins(left, top, right, bottom);
    }
    void JAbstractScrollBar::setInnerContentsMarginsWidth(int left, int top, int right, int bottom) {
        v_innerContentsMarginsWidth.setMargins(left, top, right, bottom);
    }
    void JAbstractScrollBar::setSliderMarginsWidth(int left, int top, int right, int bottom) {
        v_sliderMarginsWidth.setMargins(left, top, right, bottom);
    }

    //фиксированные размеры
    void JAbstractScrollBar::setSliderFixedSize(int width, int height) {
        v_sliderFixedSize.scale(width, height, Qt::IgnoreAspectRatio);
    }
    void JAbstractScrollBar::setSliderFixedWidth(int width) {
        v_sliderFixedSize.setWidth(width);
    }
    void JAbstractScrollBar::setSliderFixedHeight(int height) {
        v_sliderFixedSize.setHeight(height);
    }
    void JAbstractScrollBar::setSubArrowFixedSize(int width, int height) {
        v_subArrowFixedSize.scale(width, height, Qt::IgnoreAspectRatio);
    }
    void JAbstractScrollBar::setSubArrowFixedWidth(int width) {
        v_subArrowFixedSize.setWidth(width);
    }
    void JAbstractScrollBar::setSubArrowFixedHeight(int height) {
        v_subArrowFixedSize.setHeight(height);
    }
    void JAbstractScrollBar::setPlusArrowFixedSize(int width, int height) {
        v_plusArrowFixedSize.scale(width, height, Qt::IgnoreAspectRatio);
    }
    void JAbstractScrollBar::setPlusArrowFixedWidth(int width) {
        v_plusArrowFixedSize.setWidth(width);
    }
    void JAbstractScrollBar::setPlusArrowFixedHeight(int height) {
        v_plusArrowFixedSize.setHeight(height);
    }
    void JAbstractScrollBar::setSubArrowIconFixedSize(int width, int height) {
        v_subArrowIconFixedSize.scale(width, height, Qt::IgnoreAspectRatio);
    }
    void JAbstractScrollBar::setSubArrowIconFixedWidth(int width) {
        v_subArrowIconFixedSize.setWidth(width);
    }
    void JAbstractScrollBar::setSubArrowIconFixedHeight(int height) {
        v_subArrowIconFixedSize.setHeight(height);
    }
    void JAbstractScrollBar::setPlusArrowIconFixedSize(int width, int height) {
        v_plusArrowIconFixedSize.scale(width, height, Qt::IgnoreAspectRatio);
    }
    void JAbstractScrollBar::setPlusArrowIconFixedWidth(int width) {
        v_plusArrowIconFixedSize.setWidth(width);
    }
    void JAbstractScrollBar::setPlusArrowIconFixedHeight(int height) {
        v_plusArrowIconFixedSize.setHeight(height);
    }


