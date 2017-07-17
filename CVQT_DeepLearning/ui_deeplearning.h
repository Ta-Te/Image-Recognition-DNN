/********************************************************************************
** Form generated from reading UI file 'deeplearning.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DEEPLEARNING_H
#define UI_DEEPLEARNING_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DeepLearning
{
public:
    QAction *actionOpen;
    QAction *actionExit;
    QAction *actionRecognize;
    QWidget *centralWidget;
    QLabel *label;
    QTextEdit *textEdit;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuRecognition;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *DeepLearning)
    {
        if (DeepLearning->objectName().isEmpty())
            DeepLearning->setObjectName(QStringLiteral("DeepLearning"));
        DeepLearning->resize(1111, 589);
        actionOpen = new QAction(DeepLearning);
        actionOpen->setObjectName(QStringLiteral("actionOpen"));
        actionExit = new QAction(DeepLearning);
        actionExit->setObjectName(QStringLiteral("actionExit"));
        actionRecognize = new QAction(DeepLearning);
        actionRecognize->setObjectName(QStringLiteral("actionRecognize"));
        centralWidget = new QWidget(DeepLearning);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(20, 20, 640, 480));
        label->setStyleSheet(QLatin1String("background-color: rgb(215, 215, 215);\n"
"border-color: rgb(8, 8, 8);"));
        textEdit = new QTextEdit(centralWidget);
        textEdit->setObjectName(QStringLiteral("textEdit"));
        textEdit->setGeometry(QRect(680, 20, 411, 481));
        DeepLearning->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(DeepLearning);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1111, 29));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        menuRecognition = new QMenu(menuBar);
        menuRecognition->setObjectName(QStringLiteral("menuRecognition"));
        DeepLearning->setMenuBar(menuBar);
        mainToolBar = new QToolBar(DeepLearning);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        DeepLearning->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(DeepLearning);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        DeepLearning->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuRecognition->menuAction());
        menuFile->addAction(actionOpen);
        menuFile->addSeparator();
        menuFile->addAction(actionExit);
        menuFile->addSeparator();
        menuRecognition->addAction(actionRecognize);

        retranslateUi(DeepLearning);

        QMetaObject::connectSlotsByName(DeepLearning);
    } // setupUi

    void retranslateUi(QMainWindow *DeepLearning)
    {
        DeepLearning->setWindowTitle(QApplication::translate("DeepLearning", "Image Recognition Using Deep Learning", 0));
        actionOpen->setText(QApplication::translate("DeepLearning", "Open", 0));
        actionExit->setText(QApplication::translate("DeepLearning", "Exit", 0));
        actionRecognize->setText(QApplication::translate("DeepLearning", "Recognize", 0));
        label->setText(QString());
        menuFile->setTitle(QApplication::translate("DeepLearning", "File", 0));
        menuRecognition->setTitle(QApplication::translate("DeepLearning", "Recognition", 0));
    } // retranslateUi

};

namespace Ui {
    class DeepLearning: public Ui_DeepLearning {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DEEPLEARNING_H
