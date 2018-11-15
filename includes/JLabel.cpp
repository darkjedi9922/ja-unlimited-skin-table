#include "JLabel.h"

JLabel::JLabel() : QLabel() {}
JLabel::JLabel(const QString &text) : QLabel() {
    setText(text);
}
JLabel::~JLabel() {}

void JLabel::setTextColor(const QColor &color) {
    textPalette_.setColor(foregroundRole() , color);
    setPalette(textPalette_);
}
void JLabel::setFontFamily(const QString &family) {
    textFont_.setFamily(family);
    setFont(textFont_);
}
void JLabel::setPixelSize(int value) {
    textFont_.setPixelSize(value);
    setFont(textFont_);
}
void JLabel::setBold(bool value) {
    textFont_.setBold(value);
    setFont(textFont_);
}

QColor JLabel::textColor() const {
    return palette().color(foregroundRole());
}
QString JLabel::fontFamily() const {
    return font().family();
}
int JLabel::pixelSize() const {
    return font().pixelSize();
}
bool JLabel::bold() const {
    return font().bold();
}

