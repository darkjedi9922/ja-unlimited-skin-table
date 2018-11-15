#ifndef MYGROUPBOX_H
#define MYGROUPBOX_H

#include <QGroupBox>

class JGroupBox : public QGroupBox
{
private:
    QString fontFamily;
    QColor color;
    QColor textColor;
    QString titleAlign;
    int borderWidth;
    int valign;
    int textHeight;
    int textMargin;
protected:
    virtual void paintEvent(QPaintEvent *);
public:
    JGroupBox(const QString &title, QWidget *parent = 0);
    void setFont(const QString &family);
    void setColor(const QColor &c);
    void setTextColor(const QColor &c);
    void setBorderWidth(int bw);
    void setTitleAlign(const QString &align);
    void setValign(int alignment);
    void setTextHeight(int height);
    void setTextMargin(int margin);
    QFontMetrics fontMetrics();
    virtual QSize sizeHint() const;
};

#endif // MYGROUPBOX_H
