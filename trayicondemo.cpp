#include <QSystemTrayIcon>
#include "trayicondemo.h"
#include "ui_trayicondemo.h"

TrayIconDemo::TrayIconDemo(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TrayIconDemo),
    _strIconPath("D:/QtPorjects/TrayIconDemo/res/barcaTray.ico")
{
    ui->setupUi(this);

    createTrayIcon();

    setWindowIcon(QIcon(_strIconPath));
}

TrayIconDemo::~TrayIconDemo()
{
    delete ui;
}

void TrayIconDemo::createTrayIcon()
{
    // 创建托盘右键菜单
    CreatTrayMenu();

    if(!QSystemTrayIcon::isSystemTrayAvailable())
        return;

    // 创建托盘图标
    _pTrayIcon = new QSystemTrayIcon(this);
    _pTrayIcon->setIcon(QIcon(_strIconPath));
    _pTrayIcon->setContextMenu(_pMenu);
    _pTrayIcon->setToolTip(tr("支付盾"));
    _pTrayIcon->showMessage(tr("支付盾"), tr("支付盾即将插入"),
        QSystemTrayIcon::Information, 5000);
    _pTrayIcon->show();

    // 托盘事件响应
    connect(_pTrayIcon,SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
            this,SLOT(iconActivated(QSystemTrayIcon::ActivationReason)));
}

void TrayIconDemo::CreatTrayMenu()
{
    _pminiSizeAction = new QAction("最小化(&N)",this);
    _pmaxSizeAction = new QAction("最大化(&X)",this);
    _prestoreWinAction = new QAction("还 原(&R)",this);
    _pquitAction = new QAction("退出(&Q)",this);

    connect(_pminiSizeAction,SIGNAL(triggered()),this,SLOT(hide()));
    connect(_pmaxSizeAction,SIGNAL(triggered()),this,SLOT(showMaximized()));
    connect(_prestoreWinAction,SIGNAL(triggered()),this,SLOT(showNormal()));
    connect(_pquitAction,SIGNAL(triggered()),qApp,SLOT(quit()));

    _pMenu = new QMenu((QWidget*)QApplication::desktop());
    _pMenu->addAction(_pminiSizeAction);
    _pMenu->addAction(_pmaxSizeAction);
    _pMenu->addAction(_prestoreWinAction);
    _pMenu->addSeparator();     //加入一个分离符
    _pMenu->addAction(_pquitAction);
}

void TrayIconDemo::iconActivated(QSystemTrayIcon::ActivationReason reason)
{
    switch(reason)
    {
    case QSystemTrayIcon::Trigger:
    case QSystemTrayIcon::DoubleClick:
        this->showNormal();
        break;
    default:
        break;
    }
}

// 截获关闭事件，做些托盘提示
void TrayIconDemo::closeEvent(QCloseEvent *event)
{
    if (_pTrayIcon->isVisible())
    {
        _pTrayIcon->showMessage("支付盾","双击托盘图标可恢复窗口",QSystemTrayIcon::Information,3000);

        this->hide();     //最小化
        event->ignore();
    }
    else
    {
        event->accept();
    }
}










