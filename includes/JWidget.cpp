#include "JWidget.h"
#include <QPainter>
#include <QChildEvent>

JWidgetPrivate::JWidgetPrivate(QWidget *parent) : QWidget(parent)
{
    if (parent) parentJWidget_ = static_cast<JWidget*>(parent);
}
JWidgetPrivate::~JWidgetPrivate() {
}

void JWidgetPrivate::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    painter.setPen(Qt::NoPen);

    //рисование границы
    painter.setBrush(QBrush(parentJWidget_->getGlobalBorderColor()));
        //верхняя граница
        painter.drawRect(0, 0, width(), parentJWidget_->getGlobalBorder().top());
        //нижняя граница
        painter.drawRect(0, height() + 1, width(), - parentJWidget_->getGlobalBorder().bottom());
        //левая граница
        painter.drawRect(0, parentJWidget_->getGlobalBorder().top(),
                         parentJWidget_->getGlobalBorder().left(), height() - parentJWidget_->getGlobalBorder().sumHeight());
        //правая граница
        painter.drawRect(width() + 1, parentJWidget_->getGlobalBorder().top(),
                         - parentJWidget_->getGlobalBorder().right(), height() - parentJWidget_->getGlobalBorder().sumHeight());
}



JWidget::JWidget(QWidget *parent) : QWidget(parent)
{
    globalBrushColor_.setNamedColor("white");
    globalBorderColor_.setNamedColor("black");
    globalBorder_.setBorder(0, 0, 0, 0);
    raisingBorder_ = true;

    borderClass_ = new JWidgetPrivate(this);
    borderClass_->setAttribute(Qt::WA_TransparentForMouseEvents);
}
JWidget::~JWidget() {
    delete borderClass_;
}

JWidgetPrivate *JWidget::getBorderClass() const {
    return borderClass_;
}

QColor JWidget::getGlobalBrushColor() const {
    return globalBrushColor_;
}
QColor JWidget::getGlobalBorderColor() const {
    return globalBorderColor_;
}
JBorder JWidget::getGlobalBorder() const {
    return globalBorder_;
}

QRect JWidget::calculateContentsRect() const {
    return QRect(globalBorder_.left(), globalBorder_.top(), width() - globalBorder_.sumWidth(), height() - globalBorder_.sumHeight());
}

bool JWidget::isAllowedRaisingBorder() const {
    return raisingBorder_;
}

void JWidget::setGlobalBrushColor(const QColor &color) {
    globalBrushColor_ = color;
    if (!isHidden()) repaint();
}
void JWidget::setGlobalBorderColor(const QColor &color) {
    globalBorderColor_ = color;
    if (!isHidden()) {
        borderClass_->repaint();
        repaint();
    }
}
void JWidget::setGlobalBorder(const JBorder &border) {

    // Почти такая же функция продублирована в setGlobalBorder.
    // Создавать отдельный метод было бесполезно,
    // поскольку слишком много зависимостей от самих этих функций
    for (int i = 0; i < children().size(); ++i) {
        if (children().at(i)->isWidgetType()) {
            QWidget *child = static_cast<QWidget*>(children().at(i));
            QRect tempContentsRect = calculateContentsRect();
            child->move(child->x() + border.left() - tempContentsRect.left(), child->y() + border.top() - tempContentsRect.top());
        }
    }

    globalBorder_ = border;
    setContentsMargins(border.left(), border.top(), border.right(), border.bottom());
    if (!isHidden()) {
        borderClass_->repaint();
        repaint();
    }
}
void JWidget::setGlobalBorderWidth(int left, int top, int right, int bottom) {

    // Почти такая же функция продублирована в setGlobalBorder.
    // Создавать отдельный метод было бесполезно,
    // поскольку слишком много зависимостей от самих этих функций
    for (int i = 0; i < children().size(); ++i) {
        if (children().at(i)->isWidgetType() && children().at(i) != borderClass_) {
            QWidget *child = static_cast<QWidget*>(children().at(i));
            QRect tempContentsRect = calculateContentsRect();
            child->move(child->x() + left - tempContentsRect.left(), child->y() + top - tempContentsRect.top());
        }
    }

    globalBorder_.setBorder(left, top, right, bottom);
    setContentsMargins(left, top, right, bottom);
    if (!isHidden()) {
        borderClass_->repaint();
        repaint();
    }
}

void JWidget::allowRaisingBorder(bool value) {
    raisingBorder_ = value;
}

void JWidget::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    painter.setPen(Qt::NoPen);
    //фон
    painter.setBrush(QBrush(globalBrushColor_));
    painter.drawRect(calculateContentsRect());
}
void JWidget::resizeEvent(QResizeEvent *) {
    borderClass_->resize(size());
}
void JWidget::childEvent(QChildEvent *event) {
    if (event->type() == QChildEvent::ChildAdded && event->child()->isWidgetType()) {
        static_cast<QWidget*>(event->child())->move(calculateContentsRect().left(), calculateContentsRect().top());
    }

    // Во второй части условия - магия.
    // Не пытайся понять - сломаешь мозг.
    if (raisingBorder_ == true && event->child() == borderClass_) borderClass_->raise();
}



