#include "TeamColorLabel.h"

TeamColorLabel::TeamColorLabel() {}
TeamColorLabel::~TeamColorLabel() {}

void TeamColorLabel::enterEvent(QEvent *) {
    setTextColor(QColor(Qt::white));
}
void TeamColorLabel::leaveEvent(QEvent *) {
    setTextColor(QColor(Qt::yellow));
}
void TeamColorLabel::mousePressEvent(QMouseEvent *) {
    emit clicked();
}
