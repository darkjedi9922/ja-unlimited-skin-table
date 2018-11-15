#include "JGroupBox.h"
#include <QPainter>

JGroupBox::JGroupBox(const QString &title, QWidget *parent) : QGroupBox()
{
    setTitle(title);
    fontFamily = "Impact";
    color = "black";
    textColor = color;
    borderWidth = 1;
    textHeight = 10;
    textMargin = 10;
    valign = Qt::AlignVCenter;
    if (parent) setParent(parent);
    setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
}
void JGroupBox::paintEvent(QPaintEvent *) {
    QPainter painter;
    QBrush brush(color, Qt::SolidPattern);
    QImage image(width(), height(), QImage::Format_ARGB32_Premultiplied);
    QFont font(fontFamily);
    font.setPointSize(textHeight-4); //-4 потому что текст почему-то срезается верхние 4 пиксела
    QFontMetrics fontMetrics(font);

    int rectY = 0;
    int textRectX = 2*borderWidth;
    int textY = textHeight;

    if (valign == Qt::AlignTop && textHeight > borderWidth) rectY = textHeight - borderWidth;
    else if (valign == Qt::AlignVCenter) {
        if (textHeight > borderWidth) rectY = (textHeight - borderWidth)/2;
        else textY = borderWidth/2 + textHeight/2;
    }

    painter.begin(&image);
    painter.setPen(QPen(Qt::NoPen));
    painter.setBrush(brush);
    painter.setCompositionMode(QPainter::CompositionMode_Clear);
    painter.drawRect(0, 0, width(), height());
    painter.setCompositionMode(QPainter::CompositionMode_SourceOver);
    painter.drawRect(0, rectY, width(), height()-rectY); //заполненный прямоугольник
    painter.setCompositionMode(QPainter::CompositionMode_Clear);
    painter.drawRect(borderWidth, borderWidth+rectY, width()-2*borderWidth, height()-2*borderWidth-rectY); //вырез прямоугольника
    if (alignment() == Qt::AlignLeft) painter.drawRect(textRectX, rectY,
                                                       fontMetrics.width(title())+2*textMargin, borderWidth); //вырез левого текста
    else if (alignment() == Qt::AlignHCenter) {
        textRectX = width()/2-fontMetrics.width(title())/2-textMargin;
        painter.drawRect(textRectX, rectY,
                         fontMetrics.width(title())+2*textMargin, borderWidth); //вырез центрального текста

    }
    else {
        textRectX = width()-2*borderWidth-fontMetrics.width(title())-2*textMargin;
        painter.drawRect(textRectX, rectY,
                         fontMetrics.width(title())+2*textMargin, borderWidth); //вырез правого текста
    }
    painter.end();

    painter.begin(this);
    painter.setPen(QPen(Qt::NoPen));
    painter.setCompositionMode(QPainter::CompositionMode_SourceOver);
    painter.drawImage(0, 0, image);
    painter.setFont(font);
    painter.setPen(QPen(textColor));
    painter.drawText(QPoint(textRectX+textMargin, textY), title());
    painter.end();
}
void JGroupBox::setFont(const QString &family) {
    fontFamily = family;
    setBorderWidth(borderWidth);
}
void JGroupBox::setColor(const QColor &c) {
    color = c;
    textColor = c;
}
void JGroupBox::setTextColor(const QColor &c) {
    textColor = c;
}
void JGroupBox::setBorderWidth(int bw) {
    borderWidth = bw;
    int topMargin = bw;
    QFont font(fontFamily);
    font.setPointSize(textHeight-4); //-4 потому что текст почему-то срезается верхние 4 пиксела
    QFontMetrics fontMetrics(font);
    if (textHeight > bw) topMargin = textHeight;
    setContentsMargins(bw, topMargin+fontMetrics.descent(), bw, bw);
}
void JGroupBox::setValign(int alignment) {
    valign = alignment;
}
void JGroupBox::setTextHeight(int height) {
    textHeight = height;
    setBorderWidth(borderWidth);
}
void JGroupBox::setTextMargin(int margin) {
    textMargin = margin;
}
QSize JGroupBox::sizeHint() const {
    QFont font(fontFamily);
    font.setPointSize(textHeight-4); //-4 потому что текст почему-то срезается верхние 4 пиксела
    QFontMetrics fontMetrics(font);
    return QSize(fontMetrics.width(title())+2*textMargin+4*borderWidth, textHeight+2*borderWidth/*+childrenRect().height()*/);
}
