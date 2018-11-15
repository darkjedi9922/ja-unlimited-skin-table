#include "JMargins.h"

JMargins::JMargins() : m_left(0), m_top(0), m_right(0), m_bottom(0) {}
JMargins::JMargins(int left, int top, int right, int bottom)
{
    m_left = left;
    m_top = top;
    m_right = right;
    m_bottom = bottom;
}
void JMargins::setLeft(int left) {
    m_left = left;
}
void JMargins::setTop(int top) {
    m_top = top;
}
void JMargins::setRight(int right) {
    m_right = right;
}
void JMargins::setBottom(int bottom) {
    m_bottom = bottom;
}
void JMargins::setMargins(int left, int top, int right, int bottom) {
    m_left = left;
    m_top = top;
    m_right = right;
    m_bottom = bottom;
}
void JMargins::setMargins(const JMargins &margins) {
    m_left = margins.left();
    m_top = margins.top();
    m_right = margins.right();
    m_bottom = margins.bottom();
}
void JMargins::invert() {
    int temp_left = m_left;
    int temp_right = m_right;
    m_left = m_top;
    m_top = temp_left;
    m_right = m_bottom;
    m_bottom = temp_right;
}
int JMargins::left() const {
    return m_left;
}
int JMargins::top() const {
    return m_top;
}
int JMargins::right() const {
    return m_right;
}
int JMargins::bottom() const {
    return m_bottom;
}
int JMargins::sumWidth() const {
    return m_left + m_right;
}
int JMargins::sumHeight() const {
    return m_top + m_bottom;
}
bool JMargins::isNull() const {
    if (!m_left && !m_top && !m_right && !m_bottom) return true;
    else return false;
}
