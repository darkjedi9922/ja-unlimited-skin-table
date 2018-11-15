#include "JBorder.h"

JBorder::JBorder() : b_left(0), b_top(0), b_right(0), b_bottom(0) {}
JBorder::JBorder(int left, int top, int right, int bottom)
{
    b_left = left;
    b_top = top;
    b_right = right;
    b_bottom = bottom;
}
void JBorder::setLeft(int left) {
    b_left = left;
}
void JBorder::setTop(int top) {
    b_top = top;
}
void JBorder::setRight(int right) {
    b_right = right;
}
void JBorder::setBottom(int bottom) {
    b_bottom = bottom;
}
void JBorder::setBorder(int left, int top, int right, int bottom) {
    b_left = left;
    b_top = top;
    b_right = right;
    b_bottom = bottom;
}
void JBorder::setBorder(const JBorder &border) {
    b_left = border.left();
    b_top = border.top();
    b_right = border.right();
    b_bottom = border.bottom();
}
void JBorder::invert() {
    int temp_left = b_left;
    int temp_right = b_right;
    b_left = b_top;
    b_top = temp_left;
    b_right = b_bottom;
    b_bottom = temp_right;
}
int JBorder::left() const {
    return b_left;
}
int JBorder::top() const {
    return b_top;
}
int JBorder::right() const {
    return b_right;
}
int JBorder::bottom() const {
    return b_bottom;
}
int JBorder::sumWidth() const {
    return b_left + b_right;
}
int JBorder::sumHeight() const {
    return b_top + b_bottom;
}
bool JBorder::isNull() const {
    if (!b_left && !b_top && !b_right && !b_bottom) return true;
    else return false;
}