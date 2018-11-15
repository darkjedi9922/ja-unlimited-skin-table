#ifndef JMARGINS_H
#define JMARGINS_H

// Дата создания виджета: ??.??.2016
// Дата завершения создания: ??.??.2016
// От Dark Jedi
// Стандарт программирования Dark Jedi v2
// Версия: 1.0.0
// Исправлено ошибок после релиза версии 1.0.0: 0

class JMargins
{
public:
    JMargins();
    JMargins(int left, int top, int right, int bottom);
    virtual ~JMargins() {}
    void setLeft(int left);
    void setTop(int top);
    void setRight(int right);
    void setBottom(int bottom);
    void setMargins(int left, int top, int right, int bottom);
    void setMargins(const JMargins &margins);
    void invert();
    int left() const;
    int top() const;
    int right() const;
    int bottom() const;
    int sumWidth() const;
    int sumHeight() const;
    bool isNull() const;
private:
    int m_left;
    int m_top;
    int m_right;
    int m_bottom;
};

#endif // JMARGINS_H
