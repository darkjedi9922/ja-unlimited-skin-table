#ifndef LABEL_H
#define LABEL_H

#include "includes/JLabel.h"

class TeamColorLabel : public JLabel
{
    Q_OBJECT
public:
    TeamColorLabel();
    virtual ~TeamColorLabel();

signals:
    void clicked();

protected:
    virtual void enterEvent(QEvent *);
    virtual void leaveEvent(QEvent *);
    virtual void mousePressEvent(QMouseEvent *);
};

#endif // LABEL_H
