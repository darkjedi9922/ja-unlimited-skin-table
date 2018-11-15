#include "JScrollArea.h"
#include <QResizeEvent>

JScrollArea::JScrollArea(QWidget *parent) : JWidget(parent)
{
    verticalScrollBar_ = new JVScrollBar(this);
    verticalScrollBar_->setOrientation(Qt::Vertical);

    horizontalScrollBar_ = new JHScrollBar(this);
    horizontalScrollBar_->setOrientation(Qt::Horizontal);

    widget_ = 0;

    verticalScrollBarPosition_ = Right;
    horizontalScrollBarPosition_ = Bottom;

    verticalScrollBarPolicy_ = Qt::ScrollBarAsNeeded;
    horizontalScrollBarPolicy_ = Qt::ScrollBarAsNeeded;

    cornerWidget_ = new JWidget(this);
    cornerWidget_->setGlobalBrushColor("black");

    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    QObject::connect(verticalScrollBar_, SIGNAL(valueChanged(int)), this, SLOT(scrollWidgetVertical(int)));
    QObject::connect(horizontalScrollBar_, SIGNAL(valueChanged(int)), this, SLOT(scrollWidgetHorizontal(int)));
}
JScrollArea::~JScrollArea() {
    if (verticalScrollBar_) delete verticalScrollBar_;
    if (horizontalScrollBar_) delete horizontalScrollBar_;
    if (widget_) delete widget_;
    if (cornerWidget_) delete cornerWidget_;
}

QSize JScrollArea::sizeHint() const {
    return QSize(200, 100);
}

JVScrollBar *JScrollArea::getVerticalScrollBar() const {
    return verticalScrollBar_;
}
JHScrollBar *JScrollArea::getHorizontalScrollBar() const {
    return horizontalScrollBar_;
}
QWidget *JScrollArea::getWidget() const {
    return widget_;
}
JWidget *JScrollArea::getCornerWidget() const {
    return cornerWidget_;
}

int JScrollArea::getVerticalScrollBarPosition() const {
    return verticalScrollBarPosition_;
}
int JScrollArea::getHorizontalScrollBarPosition() const {
    return horizontalScrollBarPosition_;
}

int JScrollArea::getVerticalScrollBarPolicy() const {
    return verticalScrollBarPolicy_;
}
int JScrollArea::getHorizontalScrollBarPolicy() const {
    return horizontalScrollBarPolicy_;
}

void JScrollArea::setVerticalScrollBar(JVScrollBar *scrollBar) {
    delete verticalScrollBar_;
    verticalScrollBar_ = scrollBar;
    verticalScrollBar_->setOrientation(Qt::Vertical);
    verticalScrollBar_->setParent(this);

    switchVerticalScrollBarDisplay();
    moveVerticalScrollBarOnOwnPosition();
    verticalScrollBar_->setFixedHeight(calculateVerticalScrollBarDynamicHeight());
    verticalScrollBar_->setMinimum(0);

    QObject::connect(verticalScrollBar_, SIGNAL(valueChanged(int)), this, SLOT(scrollWidgetVertical(int)));
}
void JScrollArea::setHorizontalScrollBar(JHScrollBar *scrollBar) {
    delete horizontalScrollBar_;
    horizontalScrollBar_ = scrollBar;
    horizontalScrollBar_->setOrientation(Qt::Horizontal);
    horizontalScrollBar_->setParent(this);

    switchHorizontalScrollBarDisplay();
    moveHorizontalScrollBarOnOwnPosition();
    horizontalScrollBar_->setFixedWidth(calculateHorizontalScrollBarDynamicWidth());
    horizontalScrollBar_->setMinimum(0);

    QObject::connect(horizontalScrollBar_, SIGNAL(valueChanged(int)), this, SLOT(scrollWidgetHorizontal(int)));
}
void JScrollArea::setWidget(QWidget *wgt) {
    widget_ = wgt;
    wgt->setParent(this);

    verticalScrollBar_->raise();
    horizontalScrollBar_->raise();
    cornerWidget_->raise();
}
void JScrollArea::setCornerWidget(JWidget *jwgt) {

    delete cornerWidget_;
    cornerWidget_ = jwgt;
    jwgt->setParent(this);

    if (!isHidden()) {
        switchCornerWidgetDisplay();
        cornerWidget_->setFixedSize(verticalScrollBar_->width(), horizontalScrollBar_->height());
        moveCornerWidgetOnOwnPosition();
    }
}

void JScrollArea::setVerticalScrollBarPosition(JScrollArea::VerticalScrollBarPosition position) {
    verticalScrollBarPosition_ = position;
    if (!isHidden()) {
        moveVerticalScrollBarOnOwnPosition();
        moveHorizontalScrollBarOnOwnPosition();
    }
}
void JScrollArea::setHorizontalScrollBarPosition(JScrollArea::HorizontalScrollBarPosition position) {
    horizontalScrollBarPosition_ = position;
    if (!isHidden()) {
        moveHorizontalScrollBarOnOwnPosition();
        moveVerticalScrollBarOnOwnPosition();
    }
}

void JScrollArea::setVerticalScrollBarPolicy(Qt::ScrollBarPolicy policy) {
    verticalScrollBarPolicy_ = policy;

    if (!isHidden()) {
        switchVerticalScrollBarDisplay();
        switchHorizontalScrollBarDisplay();
        horizontalScrollBar_->setFixedWidth(calculateHorizontalScrollBarDynamicWidth());
        moveVerticalScrollBarOnOwnPosition();

        verticalScrollBar_->setMinimum(0);
        horizontalScrollBar_->setMinimum(0);

        setNeededVerticalScrollBarMaximum();
        setNeededHorizontalScrollBarMaximum();
    }
}
void JScrollArea::setHorizontalScrollBarPolicy(Qt::ScrollBarPolicy policy) {
    horizontalScrollBarPolicy_ = policy;

    if (!isHidden()) {
        switchHorizontalScrollBarDisplay();
        switchVerticalScrollBarDisplay();
        verticalScrollBar_->setFixedHeight(calculateVerticalScrollBarDynamicHeight());
        moveHorizontalScrollBarOnOwnPosition();

        verticalScrollBar_->setMinimum(0);
        horizontalScrollBar_->setMinimum(0);

        setNeededVerticalScrollBarMaximum();
        setNeededHorizontalScrollBarMaximum();
    }
}

void JScrollArea::scrollWidgetVertical(int value) {

    if (widget_) {
        if (value > 0 && value < verticalScrollBar_->maximum()) {
            widget_->move(widget_->x(), calculateInnerContentsRect().top() - value);
        }
        else if (value <= 0) {
            widget_->move(widget_->x(), calculateInnerContentsRect().top());
        }
        else {
            widget_->move(widget_->x(), calculateInnerContentsRect().bottom() + 1 - widget_->height());
        }
    }
}
void JScrollArea::scrollWidgetHorizontal(int value) {

    if (widget_) {
        if (value > 0 && value < horizontalScrollBar_->maximum()) {
            widget_->move(calculateInnerContentsRect().left() - value, widget_->y());
        }
        else if (value <= 0) {
            widget_->move(calculateInnerContentsRect().left(), widget_->y());
        }
        else {
            widget_->move(calculateInnerContentsRect().right() + 1 - widget_->width(), widget_->y());
        }
    }
}

void JScrollArea::resizeEvent(QResizeEvent *event) {
    JWidget::resizeEvent(event);

    updateSettings();
}
void JScrollArea::showEvent(QShowEvent *) {
    updateSettings();
}

void JScrollArea::updateSettings() {

    switchVerticalScrollBarDisplay();
    switchHorizontalScrollBarDisplay();
    switchCornerWidgetDisplay();

    if (!verticalScrollBar_->isHidden()) {

        verticalScrollBar_->setFixedHeight(calculateVerticalScrollBarDynamicHeight());
        moveVerticalScrollBarOnOwnPosition();

        verticalScrollBar_->setMinimum(0);
        setNeededVerticalScrollBarMaximum();
    }

    if (!horizontalScrollBar_->isHidden()) {

        horizontalScrollBar_->setFixedWidth(calculateHorizontalScrollBarDynamicWidth());
        moveHorizontalScrollBarOnOwnPosition();

        horizontalScrollBar_->setMinimum(0);
        setNeededHorizontalScrollBarMaximum();
    }

    if (!cornerWidget_->isHidden()) {
        cornerWidget_->setFixedSize(verticalScrollBar_->width(), horizontalScrollBar_->height());
        moveCornerWidgetOnOwnPosition();
    }
}

QRect JScrollArea::calculateInnerContentsRect() const {

    QRect tempContentsRect = calculateContentsRect();
    int tempVerticalScrollBarDynamicWidth = calculateVerticalScrollBarDynamicWidth();
    int tempHorizontalScrollBarDynamicHeight = calculateHorizontalScrollBarDynamicHeight();

    int x = tempContentsRect.x() + (verticalScrollBarPosition_ == Right ? 0 : tempVerticalScrollBarDynamicWidth);

    int y = tempContentsRect.y() + (horizontalScrollBarPosition_ == Bottom ? 0 : tempHorizontalScrollBarDynamicHeight);

    int width = tempContentsRect.width() - tempVerticalScrollBarDynamicWidth;

    int height = tempContentsRect.height() - tempHorizontalScrollBarDynamicHeight;

    return QRect(x, y, width, height);
}

int JScrollArea::calculateVerticalScrollBarDynamicWidth() const {
    return (verticalScrollBar_->isHidden() ? 0 : verticalScrollBar_->width());
}
int JScrollArea::calculateVerticalScrollBarDynamicHeight() const {
    return calculateContentsRect().height() - calculateHorizontalScrollBarDynamicHeight();
}
int JScrollArea::calculateHorizontalScrollBarDynamicHeight() const {
    return (horizontalScrollBar_->isHidden() ? 0 : horizontalScrollBar_->height());
}
int JScrollArea::calculateHorizontalScrollBarDynamicWidth() const {
    return calculateContentsRect().width() - calculateVerticalScrollBarDynamicWidth();
}

void JScrollArea::moveVerticalScrollBarOnOwnPosition() {

    int x = (verticalScrollBarPosition_ == Right ? calculateContentsRect().right() - verticalScrollBar_->width() + 1 : calculateContentsRect().x());

    int y = (horizontalScrollBarPosition_ == Bottom ? calculateContentsRect().y() : calculateContentsRect().y() + calculateHorizontalScrollBarDynamicHeight());

    verticalScrollBar_->move(x, y);
}
void JScrollArea::moveHorizontalScrollBarOnOwnPosition() {

    int x = (verticalScrollBarPosition_ == Right ? calculateContentsRect().left() : calculateContentsRect().left() + calculateVerticalScrollBarDynamicWidth());

    int y = (horizontalScrollBarPosition_ == Bottom ? calculateContentsRect().bottom() - horizontalScrollBar_->height() + 1 : calculateContentsRect().y());

    horizontalScrollBar_->move(x, y);
}
void JScrollArea::moveCornerWidgetOnOwnPosition() {

    cornerWidget_->move(verticalScrollBar_->pos().x(), horizontalScrollBar_->pos().y());
}

void JScrollArea::switchVerticalScrollBarDisplay() {
    int widgetHeight = (widget_ ? widget_->height() : 0);

    if ( verticalScrollBarPolicy_ == Qt::ScrollBarAlwaysOn ||
        (verticalScrollBarPolicy_ == Qt::ScrollBarAsNeeded && calculateInnerContentsRect().height() < widgetHeight) )
    {
        verticalScrollBar_->show();
    }
    else {
        verticalScrollBar_->hide();
        verticalScrollBar_->setValue(0);
        if (widget_ ) widget_->move(widget_->x(), calculateInnerContentsRect().top());
    }

    if (!isHidden()) horizontalScrollBar_->setFixedWidth(calculateHorizontalScrollBarDynamicWidth());
}
void JScrollArea::switchHorizontalScrollBarDisplay() {
    int widgetWidth = (widget_ ? widget_->width() : 0);

    if ( horizontalScrollBarPolicy_ == Qt::ScrollBarAlwaysOn ||
        (horizontalScrollBarPolicy_ == Qt::ScrollBarAsNeeded && calculateInnerContentsRect().width() < widgetWidth) )
    {
        horizontalScrollBar_->show();
    }
    else {
        horizontalScrollBar_->hide();
        horizontalScrollBar_->setValue(0);
        if (widget_) widget_->move(calculateInnerContentsRect().left(), widget_->y());
    }

    if (!isHidden()) verticalScrollBar_->setFixedHeight(calculateVerticalScrollBarDynamicHeight());
}
void JScrollArea::switchCornerWidgetDisplay() {

    if (verticalScrollBar_->isHidden() || horizontalScrollBar_->isHidden()) cornerWidget_->hide();
    else cornerWidget_->show();
}

void JScrollArea::setNeededVerticalScrollBarMaximum() {
    int widgetHeight = (widget_ ? widget_->height() : 0);

    if (calculateInnerContentsRect().height() < widgetHeight) verticalScrollBar_->setMaximum(widgetHeight - calculateInnerContentsRect().height());
    else verticalScrollBar_->setMaximum(0);
}
void JScrollArea::setNeededHorizontalScrollBarMaximum() {
    int widgetWidth = (widget_ ? widget_->width() : 0);

    if (calculateInnerContentsRect().width() < widgetWidth) horizontalScrollBar_->setMaximum(widgetWidth - calculateInnerContentsRect().width());
    else horizontalScrollBar_->setMaximum(0);
}



