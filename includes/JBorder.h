#ifndef JBORDER_H
#define JBORDER_H

// Дата создания виджета: ??.??.2016
// Дата завершения создания: ??.??.2016
// От Dark Jedi
// Стандарт программирования Dark Jedi v2
// Версия: 1.0.0
// Исправлено ошибок после релиза версии 1.0.0: 0

class JBorder
{
public:
    JBorder();
    JBorder(int left, int top, int right, int bottom);
    virtual ~JBorder() {}
    void setLeft(int left);
    void setTop(int top);
    void setRight(int right);
    void setBottom(int bottom);
    void setBorder(int left, int top, int right, int bottom);
    void setBorder(const JBorder &border);
    void invert();
    int left() const;
    int top() const;
    int right() const;
    int bottom() const;
    int sumWidth() const;
    int sumHeight() const;
    bool isNull() const;
private:
    int b_left;
    int b_top;
    int b_right;
    int b_bottom;
};

#endif // JBORDER_H
