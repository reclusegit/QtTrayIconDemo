#ifndef TRAYICONDEMO_H
#define TRAYICONDEMO_H

#include <QMainWindow>
#include <QSystemTrayIcon>
#include <QCloseEvent>

namespace Ui {
class TrayIconDemo;
}

// 前向声明
class QAction;

class TrayIconDemo : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit TrayIconDemo(QWidget *parent = 0);
    ~TrayIconDemo();
    void createTrayIcon();
    void CreatTrayMenu();
    
public slots:
    void iconActivated(QSystemTrayIcon::ActivationReason reason);

protected:
    // 重载窗口关闭事件
    void closeEvent(QCloseEvent *event);

private:
    Ui::TrayIconDemo *ui;

public:
     QSystemTrayIcon *_pTrayIcon;
     QString _strIconPath;
     QMenu *_pMenu;

     QAction *_pminiSizeAction;
     QAction *_pmaxSizeAction;
     QAction *_prestoreWinAction;
     QAction *_pquitAction;
};

#endif // TRAYICONDEMO_H
