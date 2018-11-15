#include "SkinsWindow.h"
#include <QDir>
#include <QApplication>
#include <QClipboard>

SkinsWindow::SkinsWindow(QWidget *parent) : QWidget(parent) {

    skinsModel_ = new QStandardItemModel;
    mainLayer_ = new QHBoxLayout;
    groupBox_ = new JGroupBox("Dark Jedi's JA Unlimited Skins 1.2");
    groupBoxLayer_ = new QHBoxLayout;
    modelViewTable_ = new JTableView(skinsModel_);
    sideBoxLayer_ = new QVBoxLayout;
    teamColorLabel_ = new TeamColorLabel;

    currentTeam_ = Default;

    skinsIconSize_.scale(80, 80, Qt::IgnoreAspectRatio);

    teamColorLabel_->setText("Цвет команды: По-умолчанию");

    loadExcludedModelNames();

    loadTableSkins(Default);

    setWindowStyles();
    setGroupBoxStyles();
    setModelViewTableStyles();
    setTeamColorLabelStyles();

    setLayers();

    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    QObject::connect(modelViewTable_, SIGNAL(itemSelected(int,int)), this, SLOT(saveSkinName(int,int)));
    QObject::connect(modelViewTable_, SIGNAL(itemSelected(int,int)), this, SLOT(copySkinName(int,int)));
    QObject::connect(teamColorLabel_, SIGNAL(clicked()), this, SLOT(changeSkinTeam()));
}
SkinsWindow::~SkinsWindow() {

    delete teamColorLabel_;
    teamColorLabel_ = NULL;

    for (int i = sideBoxLayer_->count(); i > 0; --i) delete sideBoxLayer_->itemAt(i)->widget();
    delete sideBoxLayer_;
    sideBoxLayer_ = NULL;

    delete modelViewTable_;
    modelViewTable_ = NULL;

    delete groupBoxLayer_;
    groupBoxLayer_ = NULL;

    delete groupBox_;
    groupBox_ = NULL;

    delete mainLayer_;
    mainLayer_ = NULL;

    skinsModel_->clear();
    delete skinsModel_;
    skinsModel_ = NULL;
}

void SkinsWindow::setWindowStyles() {

    QPalette windowPalette;
    windowPalette.setColor(backgroundRole(), "#020134");
    setPalette(windowPalette);
    setAutoFillBackground(true);
}
void SkinsWindow::setGroupBoxStyles() {
    groupBox_->setColor(QColor("#4b4daf"));
    groupBox_->setBorderWidth(15);
    groupBox_->setTextHeight(25);
}
void SkinsWindow::setModelViewTableStyles() {

    modelViewTable_->setColumnsWidth(skinsIconSize_.width());
    modelViewTable_->setRowsHeight(skinsIconSize_.height());
    modelViewTable_->setBackgroundColor(QColor("black"));
    modelViewTable_->setActiveItemBorderColor(QColor("yellow"));
    modelViewTable_->setActiveItemBrushColor(QColor(Qt::transparent));
    modelViewTable_->setItemBorderWidth(3);

    modelViewTable_->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    modelViewTable_->setGlobalBorderWidth(2, 2, 2, 2);
    modelViewTable_->setGlobalBorderColor(Qt::yellow);

    modelViewTable_->getVerticalScrollBar()->setInnerContentsBrushColor("#020134");
    modelViewTable_->getVerticalScrollBar()->setInnerContentsBorderColor("#4b4daf");
    modelViewTable_->getVerticalScrollBar()->setInnerContentsBorderWidth(2, 2, 2, 2);
    modelViewTable_->getVerticalScrollBar()->setSubArrowBorderColor(Qt::transparent);
    modelViewTable_->getVerticalScrollBar()->setPlusArrowBorderColor(Qt::transparent);
    modelViewTable_->getVerticalScrollBar()->setFixedWidth(25);
    modelViewTable_->getVerticalScrollBar()->setSubArrowIconFixedSize(24, 26);
    modelViewTable_->getVerticalScrollBar()->setPlusArrowIconFixedSize(24, 24);
    modelViewTable_->getVerticalScrollBar()->setSubArrowIconColor("#4b4daf");
    modelViewTable_->getVerticalScrollBar()->setPlusArrowIconColor("#4b4daf");
    modelViewTable_->getVerticalScrollBar()->setSliderFixedSize(16, 16);
    modelViewTable_->getVerticalScrollBar()->setSliderBrushImage(QImage(":resources/slider_icon.png"));
    modelViewTable_->getVerticalScrollBar()->setSliderBrushColor(Qt::transparent);
    modelViewTable_->getVerticalScrollBar()->setSliderBorderColor(Qt::transparent);
    modelViewTable_->getVerticalScrollBar()->setSliderMarginsWidth(0, 4, 0, 4);
    modelViewTable_->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    modelViewTable_->getVerticalScrollBar()->setContextMenuPolicy(Qt::NoContextMenu);
    modelViewTable_->getVerticalScrollBar()->setSingleStep(83);
    modelViewTable_->getVerticalScrollBar()->setSingleStepForWidget(true);

    modelViewTable_->setHorizontalScrollBar(new JHScrollBar(*modelViewTable_->getVerticalScrollBar()));
}
void SkinsWindow::setTeamColorLabelStyles() {
    teamColorLabel_->setTextColor(QColor(Qt::yellow));
    teamColorLabel_->setBold(true);
    teamColorLabel_->setFontFamily("Calibri");
    teamColorLabel_->setPixelSize(20);
}

void SkinsWindow::setLayers() {
    setLayout(mainLayer_);
    mainLayer_->addWidget(groupBox_);
    groupBox_->setLayout(groupBoxLayer_);

    groupBoxLayer_->addWidget(modelViewTable_, 3);
    groupBoxLayer_->addLayout(sideBoxLayer_, 1);

    groupBoxLayer_->setSpacing(15);

    sideBoxLayer_->addWidget(teamColorLabel_);
    sideBoxLayer_->addStretch();

    sideBoxLayer_->setSpacing(10);
}

void SkinsWindow::loadTableSkins(SkinsTeam team)
{
    skinsAmount_ = 0;
    indexRow_ = 0;
    indexColumn_ = -1;

    skinsModel_->clear();
    skinsModel_->setColumnCount(10);

    QDir skinsDir("..");
    QFileInfoList skinsDirList = skinsDir.entryInfoList(QDir::Files, QDir::Reversed);

    // Проход по файлам в папке
    foreach(QFileInfo dirFileInfo, skinsDirList)
    {
        // Выборка только pk3 файлов
        QStringList fileSplittedName = dirFileInfo.fileName().split(".");
        QString fileFormat = fileSplittedName.back();
        // А также после && идут исключения файлов, в которых не может быть скинов
        if ((fileFormat == "pk3" || fileFormat == "PK3") &&
                (dirFileInfo.fileName() != "assets0.pk3" ||
                 dirFileInfo.fileName() != "assets2.pk3" ||
                 dirFileInfo.fileName() != "assets3.pk3"))
        {
            QZipReader pk3(dirFileInfo.filePath());

            // Проход по файлам в pk3
            foreach (QZipReader::FileInfo pk3FileInfo, pk3.fileInfoList())
            {
                QStringList filePathList = pk3FileInfo.filePath.split("/");

                QString fileName = filePathList.back();
                QStringList fileSplittedName = fileName.split(".");

                // Проверяем файл на формат
                if (fileSplittedName.back() == "skin" || fileSplittedName.back() == "SKIN") {

                    QStringList fileNameNameList = static_cast<QString>(fileSplittedName.first()).split("_");

                    // Проверяем файл на наличие префикса model
                    if (fileNameNameList.first() == "model") {

                        fileNameNameList.pop_front();

                        if (team == Default && fileNameNameList.first() != "red" && fileNameNameList.first() != "blue") goto loadSkin;
                        else if (team == Red && fileNameNameList.first() == "red") goto loadSkin;
                        else if (team == Blue && fileNameNameList.first() == "blue") goto loadSkin;
                        else continue;

                        loadSkin:
                        QString fileNameTeam = fileNameNameList.join("_");
                        QString skinName = filePathList.at(2) + "/" + fileNameTeam;

                        if (!excludedModelNames_.contains(skinName + "\r\n") && fileNameTeam != "menu") {
                            // Загружаем скин
                            ++skinsAmount_;
                            setNecessaryRowsAmount();
                            ++indexColumn_;
                            updateSkinIndexCoordinates();

                                // Загружаем иконку скина
                                QString iconDirPath = filePathList.at(0) + "/" + filePathList.at(1) + "/" + filePathList.at(2);
                                if (loadSkinIcon(pk3, iconDirPath + "/icon_" + fileNameTeam + ".jpg")) goto scaleIcon;
                                else if (loadSkinIcon(pk3, iconDirPath + "/icon_" + fileNameTeam + ".JPG")) goto scaleIcon;
                                else if (loadSkinIcon(pk3, iconDirPath + "/Icon_" + fileNameTeam + ".jpg")) goto scaleIcon;
                                else if (loadSkinIcon(pk3, iconDirPath + "/Icon_" + fileNameTeam + ".JPG")) goto scaleIcon;

                                else if (QFile("fixes/" + filePathList.at(2) + "_" + fileNameTeam + ".jpg").exists())
                                    icon_.load("fixes/" + filePathList.at(2) + "_" + fileNameTeam + ".jpg");

                                else icon_.load(":resources/icon_hidden.jpg");

                            scaleIcon:
                            icon_ = icon_.scaled(skinsIconSize_);

                            skinsModel_->setData(skinsModel_->index(indexRow_, indexColumn_), skinName);
                            skinsModel_->setData(skinsModel_->index(indexRow_, indexColumn_), icon_, Qt::DecorationRole);
                        }
                    }
                }
            }
            pk3.close();
        }
    }
}
void SkinsWindow::setNecessaryRowsAmount() {
    int necessaryRowsAmount = (skinsAmount_ / 10) + 1;
    skinsModel_->setRowCount(necessaryRowsAmount);
}
void SkinsWindow::updateSkinIndexCoordinates() {
    if (indexColumn_ == 10) {
        ++indexRow_;
        indexColumn_ = 0;
    }
}

void SkinsWindow::saveSkinName(int row, int column) {
    QString skinName = skinsModel_->index(row, column).data().toString();
    emit returnCurrentSkinName(skinName);
}
void SkinsWindow::changeSkinTeam() {

    if (currentTeam_ == Default) {
        currentTeam_ = Blue;
        teamColorLabel_->setText("Цвет команды: Синий");
        loadTableSkins(Blue);
    }
    else if (currentTeam_ == Red) {
        currentTeam_ = Default;
        teamColorLabel_->setText("Цвет команды: По-умолчанию");
        loadTableSkins(Default);
    }
    else if (currentTeam_ == Blue) {
        currentTeam_ = Red;
        teamColorLabel_->setText("Цвет команды: Красный");
        loadTableSkins(Red);
    }

    modelViewTable_->decactivateAllItems();
    modelViewTable_->updateTableSize();
    modelViewTable_->getVerticalScrollBar()->setValue(0);
    modelViewTable_->getHorizontalScrollBar()->setValue(0);
    modelViewTable_->repaintAll();
}
void SkinsWindow::copySkinName(int row, int column) {

    QString skinName = skinsModel_->index(row, column).data().toString();

    if (!skinName.isNull()) {
        QString modelCmd = "/model " + skinName;

        // Копирование в буфер обмена
        QClipboard *clipBoard = QApplication::clipboard();
        clipBoard->setText(modelCmd);

        writeRecord(modelCmd);
    }
}
void SkinsWindow::writeRecord(const QString &modelCmd) {

    JLabel *modelCmdLabel = new JLabel(modelCmd);
    modelCmdLabel->setTextColor(QColor(Qt::yellow));
    modelCmdLabel->setBold(true);
    modelCmdLabel->setFontFamily("Calibri");
    modelCmdLabel->setPixelSize(15);

    JLabel *accessMessage = new JLabel("Скопировано в буфер обмена");
    accessMessage->setTextColor(QColor(Qt::green));
    accessMessage->setBold(true);
    accessMessage->setFontFamily("Calibri");
    accessMessage->setPixelSize(15);

    if (sideBoxLayer_->count() - 2 == 20) {
        delete sideBoxLayer_->itemAt(1)->widget();
        delete sideBoxLayer_->itemAt(1)->widget();
    }

    sideBoxLayer_->removeItem(sideBoxLayer_->itemAt(sideBoxLayer_->count() - 1)); // Убираем strecth (последнйи итем)
    sideBoxLayer_->addWidget(modelCmdLabel);
    sideBoxLayer_->addWidget(accessMessage);
    sideBoxLayer_->addStretch();
}
void SkinsWindow::loadExcludedModelNames() {
    QFile excludeModelsFile("exclude_models.txt");

    if (excludeModelsFile.open(QIODevice::ReadOnly)) {
        while (!excludeModelsFile.atEnd())
        {
             QByteArray line = excludeModelsFile.readLine();
             excludedModelNames_ << line.data();
        }
    }
}

bool SkinsWindow::loadSkinIcon(const QZipReader &zip, const QString &fileName) {

    QByteArray iconByteArray = zip.fileData(fileName);
    if (!iconByteArray.isNull()) icon_.loadFromData(iconByteArray);
    else return false;

    return true;
}

QSize SkinsWindow::sizeHint() {
    return QSize(200, 200);
}
