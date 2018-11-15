#include "JTableView.h"
#include <QAbstractItemModel>
#include <QPainter>
#include <QMouseEvent>
#include <QScrollBar>

JTableViewPrivate::JTableViewPrivate(JTableView *parentWidget) : QWidget()
{
    parent = parentWidget;
}
JTableViewPrivate::~JTableViewPrivate() {
    if (parent) delete parent;
}
void JTableViewPrivate::paintEvent(QPaintEvent *) {
    QPainter painter(this);

    //рисовка элементов, которые существуют
    if (parent->model->hasChildren()) {
        //рисовка обычных элементов
        for (int r = 0; r < parent->rowCount(); ++r) {
            for (int c = 0; c < parent->columnCount(); ++c) {
                if (parent->itemIsEmpty(r, c)) continue;
                QModelIndex index = parent->model->index(r, c);
                QPixmap itemIcon = index.data(Qt::DecorationRole).value<QPixmap>();
                QRect iconRect = parent->itemRect(r, c, false);

                //рисование рамки item'a, если она есть
                if (parent->itemBorderWidth != 0) {
                    painter.setPen(parent->itemBorderColor);
                    painter.setBrush(QBrush(parent->itemBorderColor));
                    painter.drawRect(parent->itemRect(r, c));
                    painter.setPen(Qt::NoPen);
                }
                //рисование иконки
                painter.drawPixmap(iconRect, itemIcon);
            }
        }

        //рисование активной иконки
        if (parent->isItemActivated()) {
            QModelIndex index = parent->model->index(parent->activeItem.y(), parent->activeItem.x());
            QPixmap itemIcon = index.data(Qt::DecorationRole).value<QPixmap>();
            QRect iconRect = parent->itemRect(parent->activeItem.y(), parent->activeItem.x(), false);

            painter.setBrush(QBrush(parent->activeItemBorderColor));
            painter.drawRect(parent->itemRect(parent->activeItem.y(), parent->activeItem.x()));
            painter.drawPixmap(iconRect, itemIcon);
            painter.setBrush(QBrush(parent->activeItemBrushColor));
            painter.drawRect(iconRect);
        }
    }
}

JTableView::JTableView(QAbstractItemModel *m) : JScrollArea() {
    model = m;
    rowsHeight = 50;
    columnsWidth = 50;
    itemBorderWidth = 1;
    itemBorderColor = QColor("black");
    activeItem = QPoint(-1, -1);
    activeItemBorderColor = QColor("aqua");
    activeItemBrushColor = QColor(0, 229, 255, 100);
    backgroundColor = QColor("white");

    //struct Pointings
    AutoSelectingJumps.leftToRightOut = true;
    AutoSelectingJumps.rightToLeftOut = true;
    AutoSelectingJumps.topToBottomOut = false;
    AutoSelectingJumps.bottomToTopOut = false;
    AutoSelectingJumps.leftToRightInner = true;
    AutoSelectingJumps.rightToLeftInner = true;
    AutoSelectingJumps.topToBottomInner = false;
    AutoSelectingJumps.bottomToTopInner = false;

    tableWidget = new JTableViewPrivate(this);
    setWidget(tableWidget);
    tableWidget->resize(tableSize());
    setFocusPolicy(Qt::StrongFocus);
}
JTableView::~JTableView() {
    if (model) delete model;
    if (tableWidget) delete tableWidget;
}
void JTableView::paintEvent(QPaintEvent *pe) {
    JScrollArea::paintEvent(pe);

    QPainter painter(this);
    painter.setPen(backgroundColor);
    painter.setBrush(QBrush(backgroundColor));
    painter.drawRect(rect());
    //QScrollArea::paintEvent(pe);
}
void JTableView::resizeEvent(QResizeEvent *event) {
    JScrollArea::resizeEvent(event);
    tableWidget->resize(tableSize());
}

void JTableView::setRowsHeight(int height) {
    rowsHeight = height;
    tableWidget->resize(tableSize());
}
void JTableView::setColumnsWidth(int width) {
    columnsWidth = width;
    tableWidget->resize(tableSize());
}
void JTableView::setItemBorderWidth(int width) {
    itemBorderWidth = width;
    tableWidget->resize(tableSize());
}
void JTableView::setItemBorderColor(QColor color) {
    itemBorderColor = color;
}
void JTableView::setActiveItemBorderColor(QColor color) {
    activeItemBorderColor = color;
}
void JTableView::setActiveItemBrushColor(QColor color) {
    activeItemBrushColor = color;
}
void JTableView::mousePressEvent(QMouseEvent *mouseEvent) {

        // Прибавляем value() и отнимаем верхнюю/левую границу,
        // чтобы позиция клика мыши правильно соответствовала
        // позиции нужного итема.
        //
        // Иначе, например, нажимая на второй ряд, может быть активирован первый.
        float mouseX = mouseEvent->x() + getHorizontalScrollBar()->QScrollBar::value() - getGlobalBorder().left();
        float mouseY = mouseEvent->y() + getVerticalScrollBar()->QScrollBar::value() - getGlobalBorder().top();

        // Если клик был в области итемов таблицы:
        if (mouseX > (itemBorderWidth/2.0) && mouseX < tableSize().width() - itemBorderWidth &&
            mouseY > (itemBorderWidth/2.0) && mouseY < tableSize().height() - itemBorderWidth
                /*(rowCount()*(rowsHeight+itemBorderWidth)+itemBorderWidth)*/)
        {
            if (isItemActivated()) deactivateItem(activeItem.y(), activeItem.x());
            float activeItemX = (mouseX - itemBorderWidth/2.0) / (columnsWidth + itemBorderWidth);
            float activeItemY = (mouseY - itemBorderWidth/2.0) / (rowsHeight + itemBorderWidth);
            activateItem(activeItemY, activeItemX);
            emit itemSelected(activeItemY, activeItemX);

            // Автоматический скроллинг таблицы, чтобы нажатый неполностью видный итем
            // был прокручен по своему размеру, чтобы быть видным в полный размер.
            autoscroll(Bottom);
            autoscroll(Top);
            autoscroll(Left);
            autoscroll(Right);
        }
        // Если клик был за областью итемов таблицы отключем активированный итем.
        else if (isItemActivated()) deactivateItem(activeItem.y(), activeItem.x());
}
QRect JTableView::itemRect(int r, int c, bool border) {
    int rectX;
    int rectY;
    int rectWidth;
    int rectHeight;
    if (border) {
        rectX = c*(columnsWidth+itemBorderWidth);
        rectY = r*(rowsHeight+itemBorderWidth);
        rectWidth = columnsWidth+2*itemBorderWidth;
        rectHeight = rowsHeight+2*itemBorderWidth;
    }
    else {
        rectX = c*(columnsWidth+itemBorderWidth)+itemBorderWidth;
        rectY = r*(rowsHeight+itemBorderWidth)+itemBorderWidth;
        rectWidth = columnsWidth;
        rectHeight = rowsHeight;
    }
    return QRect(rectX, rectY, rectWidth, rectHeight);
}
bool JTableView::itemIsEmpty(int r, int c) {
    if (model->index(r, c).data(Qt::DisplayRole).isNull() &&
        model->index(r, c).data(Qt::DecorationRole).isNull() &&
        model->index(r, c).data(Qt::EditRole).isNull() &&
        model->index(r, c).data(Qt::ToolTipRole).isNull() &&
        model->index(r, c).data(Qt::StatusTipRole).isNull() &&
        model->index(r, c).data(Qt::WhatsThisRole).isNull()) return true;
    else return false;
}
QSize JTableView::tableSize() {
    return QSize(columnCount()*(columnsWidth + itemBorderWidth) + itemBorderWidth, rowCount()*(rowsHeight + itemBorderWidth) + itemBorderWidth);
}
void JTableView::keyPressEvent(QKeyEvent *keyEvent) {
    //выбор клавиши
    switch (keyEvent->key()) {
    case Qt::Key_Space:
        if (isItemActivated()) return;
        else activateItem(0, 0);
        emit itemSelected(0, 0);
        autoscroll(Top);
        autoscroll(Left);
    break;
    case Qt::Key_Right:
        if (isItemActivated()) {
            moveSelecting(Right);
            autoscroll(Right);
            autoscroll(Left);
            autoscroll(Top);
            autoscroll(Bottom);
        }
    break;
    case Qt::Key_Left:
        if (isItemActivated()) {
            moveSelecting(Left);
            autoscroll(Left);
            autoscroll(Right);
            autoscroll(Top);
            autoscroll(Bottom);
        }
    break;
    case Qt::Key_Down:
        if (isItemActivated()) {
            moveSelecting(Bottom);
            autoscroll(Bottom);
            autoscroll(Top);
            autoscroll(Left);
            autoscroll(Right);
        }
    break;
    case Qt::Key_Up:
        if (isItemActivated()) {
            moveSelecting(Top);
            autoscroll(Top);
            autoscroll(Bottom);
            autoscroll(Left);
            autoscroll(Right);
        }
    break;
    default:
        QWidget::keyPressEvent(keyEvent);
    }
}
bool JTableView::isItemActivated(int row, int column) {
    if (row == -1 && column == -1) {
        if (activeItem.x() != -1 && activeItem.y() != -1) return true;
        else return false;
    }
    else if (activeItem.y() == row && activeItem.x() == column) return true;
    else return false;
}
void JTableView::activateItem(int row, int column) {
    activeItem = QPoint(column, row);
    tableWidget->repaint(itemRect(row, column));
}
void JTableView::deactivateItem(int row, int column) {
    activeItem = QPoint(-1, -1);
    tableWidget->repaint(itemRect(row, column));
}
void JTableView::moveSelecting(Side side) {
    int tempY = activeItem.y();
    int tempX = activeItem.x();
    int newY = activeItem.y();
    int newX = activeItem.x();
    switch (side) {
    case Right:
        //перепрыг с конца в начало
        if (isItemActivated(rowCount()-1, columnCount()-1) //в самом конце
            && AutoSelectingJumps.rightToLeftOut //разрешен прыжок снаружи
            ) { newY = 0; newX = 0; }
        //прыжок в начало следующей строки
        else if (isItemActivated(tempY, columnCount()-1) //в конце строки
                 && !isItemActivated(rowCount()-1, columnCount()-1) //не в самом конце
                 && AutoSelectingJumps.rightToLeftInner //разрешен прыжок внутри
                 ) { newY = tempY + 1; newX = 0; }
        //прыжок обычный
        else if (!isItemActivated(rowCount()-1, columnCount()-1) //не в самом конце
                 && !isItemActivated(tempY, columnCount()-1) //не в коцне строки
                 ) { newY = tempY; newX = tempX + 1; }
    break;
    case Left:
        //перепрыг с начала в конец
        if (isItemActivated(0, 0) //в самом начале
            && AutoSelectingJumps.leftToRightOut //разрешен прыжок снаружи
            ) { newY = rowCount() - 1; newX = columnCount() - 1; }
        //прыжок в конец предыдущей строки
        else if (isItemActivated(tempY, 0) //в начале строки
                 && !isItemActivated(0, 0) //не в самом начале
                 && AutoSelectingJumps.leftToRightInner //разрешен прыжок внутри
                 ) { newY = tempY - 1; newX = columnCount() - 1; }
        //обычный прыжок
        else if (!isItemActivated(tempY, 0) //не в начале строки
                 && !isItemActivated(0, 0) //не в самом начале
                 ) { newY = tempY; newX = tempX - 1; }
    break;
    case Bottom:
        //перепрыг с конца в начало
        if (isItemActivated(rowCount() - 1, columnCount() - 1) //в самом конце
            && AutoSelectingJumps.bottomToTopOut //разрешено перепрыгивать снаружи
            ) { newY = 0; newX = 0; }
        //перепрыг на начало следующей колонки
        else if (isItemActivated(rowCount() - 1, tempX) //в конце колонки
                 && !isItemActivated(rowCount() - 1, columnCount() - 1) //не в самом конце
                 && AutoSelectingJumps.bottomToTopInner //разрешено перепрыгивать внутри
                 ) { newY = 0; newX = tempX + 1; }
        //обычный перепрыг
        else if (!isItemActivated(rowCount() - 1, columnCount() - 1) //не в самом конце
                 && !isItemActivated(rowCount() - 1, tempX) //не в конце строки
                 ) { newY = tempY + 1; newX = tempX; }
    break;
    case Top:
        //перепрыг с начала в конец
        if (isItemActivated(0, 0) //в самом начале
            && AutoSelectingJumps.topToBottomOut //разрешено перепрыгивать снаружи
            ) { newY = rowCount() - 1; newX = columnCount() - 1; }
        //прыжок в конец предыдущей колонки
        else if (isItemActivated(0, tempX) //в начале колонки
                 && !isItemActivated(0, 0) //не в самом начале
                 && AutoSelectingJumps.topToBottomInner //разрешен прыжок внутри
                 ) { newY = rowCount() - 1; newX = tempX - 1; }
        //обычный прыжок
        else if (!isItemActivated(0, 0) //не в самом начале
                 && !isItemActivated(0, tempX) //не в начале колонки
                 ) { newY = tempY - 1; newX = tempX; }
    }
    if (!(tempX == newX && tempY == newY)) {
        deactivateItem(tempY, tempX);
        activateItem(newY, newX);
        emit itemSelected(newY, newX);
    }
}
QRect JTableView::itemsRect(int item1X, int item1Y, int item2X, int item2Y) {
    int width = (item2X - item1X + 1)*(columnsWidth + itemBorderWidth) + itemBorderWidth;
    int height = (item2Y - item1Y + 1)*(rowsHeight + itemBorderWidth) + itemBorderWidth;
    return QRect(itemRect(item1Y, item1X).x(), itemRect(item1Y, item1X).y(), width, height);
}
void JTableView::autoscroll(Side side)
{
    QRect activeItemRect = QRect(itemRect(activeItem.y(), activeItem.x()).x(), itemRect(activeItem.y(), activeItem.x()).y(),
                                 itemRect(activeItem.y(), activeItem.x()).width(), itemRect(activeItem.y(), activeItem.x()).height());
    QPoint activeItemPointEnd = QPoint(activeItemRect.x() + activeItemRect.width(), activeItemRect.y() + activeItemRect.height());
    int verticalScrollValue = getVerticalScrollBar()->QScrollBar::value();
    int horizontalScrollValue = getHorizontalScrollBar()->QScrollBar::value();
    int prevItemsHeight = itemsRect(activeItem.x(), 0, activeItem.x() ,activeItem.y()-1).height() - itemBorderWidth;
    int prevItemsWidth = itemsRect(0, activeItem.y(), activeItem.x()-1, activeItem.y()).width() - itemBorderWidth;
    QPoint scrollAreaPointEnd = QPoint(getHorizontalScrollBar()->width() + horizontalScrollValue,
                                       getVerticalScrollBar()->height() + verticalScrollValue);

    switch (side) {
    case Bottom:
        if (activeItemPointEnd.y() > scrollAreaPointEnd.y())
            getVerticalScrollBar()->QScrollBar::setValue(verticalScrollValue + activeItemPointEnd.y() - scrollAreaPointEnd.y());
    break;
    case Top:
        if (activeItemRect.y() < verticalScrollValue) getVerticalScrollBar()->QScrollBar::setValue(prevItemsHeight);
    break;
    case Left:
        if (activeItemRect.x() < horizontalScrollValue) getHorizontalScrollBar()->QScrollBar::setValue(prevItemsWidth);
    break;
    case Right:
        if (activeItemPointEnd.x() > scrollAreaPointEnd.x())
                getHorizontalScrollBar()->QScrollBar::setValue(horizontalScrollValue + activeItemPointEnd.x() - scrollAreaPointEnd.x());
    }
}
void JTableView::setAutoSelectingJump(Pointing jump, bool setting) {
    switch (jump) {
    case LeftToRightOut:
        setting ? AutoSelectingJumps.leftToRightOut = true : AutoSelectingJumps.leftToRightOut = false;
    break;
    case RightToLeftOut:
        setting ? AutoSelectingJumps.rightToLeftOut = true : AutoSelectingJumps.rightToLeftOut = false;
    break;
    case TopToBottomOut:
        setting ? AutoSelectingJumps.topToBottomOut = true : AutoSelectingJumps.topToBottomOut = false;
    break;
    case BottomToTopOut:
        setting ? AutoSelectingJumps.bottomToTopOut = true : AutoSelectingJumps.bottomToTopOut = false;
    break;
    case LeftToRightInner:
        setting ? AutoSelectingJumps.leftToRightInner = true : AutoSelectingJumps.leftToRightInner = false;
    break;
    case RightToLeftInner:
        setting ? AutoSelectingJumps.rightToLeftInner = true : AutoSelectingJumps.rightToLeftInner = false;
    break;
    case TopToBottomInner:
        setting ? AutoSelectingJumps.topToBottomInner = true : AutoSelectingJumps.topToBottomInner = false;
    break;
    case BottomToTopInner:
        setting ? AutoSelectingJumps.bottomToTopInner = true : AutoSelectingJumps.bottomToTopInner = false;
    break;
    }
}
void JTableView::setBackgroundColor(QColor color) {
    backgroundColor = color;
}

int JTableView::columnCount() const {
    return model->columnCount();
}
int JTableView::rowCount() const {
    return model->rowCount();
}

void JTableView::decactivateAllItems() {
    deactivateItem(activeItem.y(), activeItem.x());
}
void JTableView::updateTableSize() {
    tableWidget->resize(tableSize());
    JScrollArea::updateSettings();
}
void JTableView::repaintAll() {
    repaint();
    getVerticalScrollBar()->repaint();
    getHorizontalScrollBar()->repaint();
}
