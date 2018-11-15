#ifndef SKINSWINDOW_H
#define SKINSWINDOW_H

#include <QWidget>
#include <QStandardItemModel>
#include <QHBoxLayout>
#include "includes/JGroupBox.h"
#include "includes/JTableView.h"
#include "includes/JHScrollBar.h"
#include "TeamColorLabel.h"
#include "qzipreader_p.h"

class SkinsWindow : public QWidget
{
    Q_OBJECT
public:
    enum SkinsTeam{Default, Blue, Red};
    explicit SkinsWindow(QWidget *parent = 0);
    virtual ~SkinsWindow();

signals:
    void returnCurrentSkinName(QString);

public slots:
    void saveSkinName(int row, int column);
    void changeSkinTeam();
    void copySkinName(int row, int column);

private:
    QStandardItemModel *skinsModel_;
    QHBoxLayout *mainLayer_;
    JGroupBox *groupBox_;
    QHBoxLayout *groupBoxLayer_;
    JTableView *modelViewTable_;
    QVBoxLayout *sideBoxLayer_;
    TeamColorLabel *teamColorLabel_;

    QList<QString> excludedModelNames_;

    QPixmap icon_;
    SkinsTeam currentTeam_;

    QSize skinsIconSize_;
    int skinsAmount_;
    int indexRow_;
    int indexColumn_;

    void setWindowStyles();
    void setGroupBoxStyles();
    void setModelViewTableStyles();
    void setTeamColorLabelStyles();

    void setLayers();

    void loadTableSkins(SkinsTeam);
    void setNecessaryRowsAmount();
    void updateSkinIndexCoordinates();
    void writeRecord(const QString &modelCmd);
    void loadExcludedModelNames();

    bool loadSkinIcon(const QZipReader &zip, const QString &fileName);

    virtual QSize sizeHint();
};

#endif // SKINSWINDOW_H
