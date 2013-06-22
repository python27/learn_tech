/********************************************************************************
** Form generated from reading UI file 'richedit.ui'
**
** Created: Sat Jun 22 12:25:34 2013
**      by: Qt User Interface Compiler version 4.8.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RICHEDIT_H
#define UI_RICHEDIT_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QStatusBar>
#include <QtGui/QTextEdit>
#include <QtGui/QToolBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Richedit
{
public:
    QAction *action_New;
    QAction *action_Save;
    QAction *action_Print;
    QAction *action_Open;
    QAction *action_Cut;
    QAction *action_Copy;
    QAction *action_Paste;
    QAction *action_Undo;
    QAction *action_Redo;
    QAction *actionContent;
    QAction *actionAbout;
    QAction *action_Exit;
    QAction *actionBold;
    QAction *actionItalic;
    QAction *actionUnderline;
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout;
    QTextEdit *textEdit;
    QMenuBar *menuBar;
    QMenu *menu_File;
    QMenu *menu_Edit;
    QMenu *menu_Help;
    QMenu *menuF_ormat;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *Richedit)
    {
        if (Richedit->objectName().isEmpty())
            Richedit->setObjectName(QString::fromUtf8("Richedit"));
        Richedit->resize(624, 375);
        action_New = new QAction(Richedit);
        action_New->setObjectName(QString::fromUtf8("action_New"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/images/new.png"), QSize(), QIcon::Normal, QIcon::On);
        action_New->setIcon(icon);
        action_Save = new QAction(Richedit);
        action_Save->setObjectName(QString::fromUtf8("action_Save"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/images/save.png"), QSize(), QIcon::Normal, QIcon::On);
        action_Save->setIcon(icon1);
        action_Print = new QAction(Richedit);
        action_Print->setObjectName(QString::fromUtf8("action_Print"));
        action_Open = new QAction(Richedit);
        action_Open->setObjectName(QString::fromUtf8("action_Open"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/images/open.png"), QSize(), QIcon::Normal, QIcon::On);
        action_Open->setIcon(icon2);
        action_Cut = new QAction(Richedit);
        action_Cut->setObjectName(QString::fromUtf8("action_Cut"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/images/cut.png"), QSize(), QIcon::Normal, QIcon::On);
        action_Cut->setIcon(icon3);
        action_Copy = new QAction(Richedit);
        action_Copy->setObjectName(QString::fromUtf8("action_Copy"));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/images/copy.png"), QSize(), QIcon::Normal, QIcon::On);
        action_Copy->setIcon(icon4);
        action_Paste = new QAction(Richedit);
        action_Paste->setObjectName(QString::fromUtf8("action_Paste"));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/images/paste.png"), QSize(), QIcon::Normal, QIcon::On);
        action_Paste->setIcon(icon5);
        action_Undo = new QAction(Richedit);
        action_Undo->setObjectName(QString::fromUtf8("action_Undo"));
        action_Redo = new QAction(Richedit);
        action_Redo->setObjectName(QString::fromUtf8("action_Redo"));
        actionContent = new QAction(Richedit);
        actionContent->setObjectName(QString::fromUtf8("actionContent"));
        actionAbout = new QAction(Richedit);
        actionAbout->setObjectName(QString::fromUtf8("actionAbout"));
        action_Exit = new QAction(Richedit);
        action_Exit->setObjectName(QString::fromUtf8("action_Exit"));
        actionBold = new QAction(Richedit);
        actionBold->setObjectName(QString::fromUtf8("actionBold"));
        actionBold->setCheckable(true);
        actionItalic = new QAction(Richedit);
        actionItalic->setObjectName(QString::fromUtf8("actionItalic"));
        actionItalic->setCheckable(true);
        actionUnderline = new QAction(Richedit);
        actionUnderline->setObjectName(QString::fromUtf8("actionUnderline"));
        actionUnderline->setCheckable(true);
        centralWidget = new QWidget(Richedit);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        horizontalLayout = new QHBoxLayout(centralWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        textEdit = new QTextEdit(centralWidget);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));

        horizontalLayout->addWidget(textEdit);

        Richedit->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(Richedit);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 624, 25));
        menu_File = new QMenu(menuBar);
        menu_File->setObjectName(QString::fromUtf8("menu_File"));
        menu_Edit = new QMenu(menuBar);
        menu_Edit->setObjectName(QString::fromUtf8("menu_Edit"));
        menu_Help = new QMenu(menuBar);
        menu_Help->setObjectName(QString::fromUtf8("menu_Help"));
        menuF_ormat = new QMenu(menuBar);
        menuF_ormat->setObjectName(QString::fromUtf8("menuF_ormat"));
        Richedit->setMenuBar(menuBar);
        mainToolBar = new QToolBar(Richedit);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        Richedit->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(Richedit);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        Richedit->setStatusBar(statusBar);

        menuBar->addAction(menu_File->menuAction());
        menuBar->addAction(menu_Edit->menuAction());
        menuBar->addAction(menuF_ormat->menuAction());
        menuBar->addAction(menu_Help->menuAction());
        menu_File->addAction(action_New);
        menu_File->addAction(action_Open);
        menu_File->addAction(action_Save);
        menu_File->addSeparator();
        menu_File->addAction(action_Print);
        menu_File->addSeparator();
        menu_File->addAction(action_Exit);
        menu_Edit->addAction(action_Cut);
        menu_Edit->addAction(action_Copy);
        menu_Edit->addAction(action_Paste);
        menu_Edit->addSeparator();
        menu_Edit->addAction(action_Undo);
        menu_Edit->addAction(action_Redo);
        menu_Help->addAction(actionContent);
        menu_Help->addAction(actionAbout);
        mainToolBar->addAction(action_New);
        mainToolBar->addAction(action_Open);
        mainToolBar->addAction(action_Save);
        mainToolBar->addSeparator();
        mainToolBar->addAction(action_Cut);
        mainToolBar->addAction(action_Copy);
        mainToolBar->addAction(action_Paste);
        mainToolBar->addSeparator();
        mainToolBar->addAction(actionBold);
        mainToolBar->addAction(actionItalic);
        mainToolBar->addAction(actionUnderline);
        mainToolBar->addSeparator();

        retranslateUi(Richedit);
        QObject::connect(action_Cut, SIGNAL(activated()), textEdit, SLOT(cut()));
        QObject::connect(action_Copy, SIGNAL(activated()), textEdit, SLOT(copy()));
        QObject::connect(action_Paste, SIGNAL(activated()), textEdit, SLOT(paste()));
        QObject::connect(action_Exit, SIGNAL(activated()), Richedit, SLOT(close()));

        QMetaObject::connectSlotsByName(Richedit);
    } // setupUi

    void retranslateUi(QMainWindow *Richedit)
    {
        Richedit->setWindowTitle(QApplication::translate("Richedit", "Richedit", 0, QApplication::UnicodeUTF8));
        action_New->setText(QApplication::translate("Richedit", "&New", 0, QApplication::UnicodeUTF8));
        action_New->setShortcut(QApplication::translate("Richedit", "Ctrl+N", 0, QApplication::UnicodeUTF8));
        action_Save->setText(QApplication::translate("Richedit", "&Save", 0, QApplication::UnicodeUTF8));
        action_Save->setShortcut(QApplication::translate("Richedit", "Ctrl+S", 0, QApplication::UnicodeUTF8));
        action_Print->setText(QApplication::translate("Richedit", "&Print", 0, QApplication::UnicodeUTF8));
        action_Print->setShortcut(QApplication::translate("Richedit", "Ctrl+P", 0, QApplication::UnicodeUTF8));
        action_Open->setText(QApplication::translate("Richedit", "&Open", 0, QApplication::UnicodeUTF8));
        action_Open->setShortcut(QApplication::translate("Richedit", "Ctrl+O", 0, QApplication::UnicodeUTF8));
        action_Cut->setText(QApplication::translate("Richedit", "&Cut", 0, QApplication::UnicodeUTF8));
        action_Cut->setShortcut(QApplication::translate("Richedit", "Ctrl+X", 0, QApplication::UnicodeUTF8));
        action_Copy->setText(QApplication::translate("Richedit", "&Copy", 0, QApplication::UnicodeUTF8));
        action_Copy->setShortcut(QApplication::translate("Richedit", "Ctrl+C", 0, QApplication::UnicodeUTF8));
        action_Paste->setText(QApplication::translate("Richedit", "&Paste", 0, QApplication::UnicodeUTF8));
        action_Paste->setShortcut(QApplication::translate("Richedit", "Ctrl+V", 0, QApplication::UnicodeUTF8));
        action_Undo->setText(QApplication::translate("Richedit", "&Undo", 0, QApplication::UnicodeUTF8));
        action_Undo->setShortcut(QApplication::translate("Richedit", "Ctrl+Z", 0, QApplication::UnicodeUTF8));
        action_Redo->setText(QApplication::translate("Richedit", "&Redo", 0, QApplication::UnicodeUTF8));
        actionContent->setText(QApplication::translate("Richedit", "Content", 0, QApplication::UnicodeUTF8));
        actionAbout->setText(QApplication::translate("Richedit", "About", 0, QApplication::UnicodeUTF8));
        action_Exit->setText(QApplication::translate("Richedit", "&Exit", 0, QApplication::UnicodeUTF8));
        action_Exit->setShortcut(QApplication::translate("Richedit", "Ctrl+Q", 0, QApplication::UnicodeUTF8));
        actionBold->setText(QApplication::translate("Richedit", "bold", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionBold->setToolTip(QApplication::translate("Richedit", "boldbold", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionBold->setShortcut(QApplication::translate("Richedit", "Ctrl+B", 0, QApplication::UnicodeUTF8));
        actionItalic->setText(QApplication::translate("Richedit", "italic", 0, QApplication::UnicodeUTF8));
        actionItalic->setShortcut(QApplication::translate("Richedit", "Ctrl+I", 0, QApplication::UnicodeUTF8));
        actionUnderline->setText(QApplication::translate("Richedit", "underline", 0, QApplication::UnicodeUTF8));
        actionUnderline->setShortcut(QApplication::translate("Richedit", "Ctrl+U", 0, QApplication::UnicodeUTF8));
        menu_File->setTitle(QApplication::translate("Richedit", "&File", 0, QApplication::UnicodeUTF8));
        menu_Edit->setTitle(QApplication::translate("Richedit", "&Edit", 0, QApplication::UnicodeUTF8));
        menu_Help->setTitle(QApplication::translate("Richedit", "&Help", 0, QApplication::UnicodeUTF8));
        menuF_ormat->setTitle(QApplication::translate("Richedit", "F&ormat", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Richedit: public Ui_Richedit {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RICHEDIT_H
