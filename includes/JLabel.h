#ifndef JLABEL_H
#define JLABEL_H

#include <QLabel>

class JLabel : public QLabel
{
public:
    JLabel();
    JLabel(const QString &text);
    virtual ~JLabel();

    void setTextColor(const QColor &color);
    void setFontFamily(const QString &family);
    void setPixelSize(int);
    void setBold(bool);

    QColor textColor() const;
    QString fontFamily() const;
    int pixelSize() const;
    bool bold() const;

private:
    QFont textFont_;
    QPalette textPalette_;
};

#endif // JLABEL_H
