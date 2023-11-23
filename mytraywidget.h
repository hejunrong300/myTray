#ifndef MYTRAYWIDGET_H
#define MYTRAYWIDGET_H

#include <QAction>
#include <QCloseEvent>
#include <QMenu>
#include <QSystemTrayIcon>
#include <QWidget>

namespace Ui
{
class myTrayWidget;
}

class myTrayWidget : public QWidget
{
	Q_OBJECT

public:
	explicit myTrayWidget(QWidget *parent = 0);
	~myTrayWidget();

private:
	Ui::myTrayWidget *ui;
	QSystemTrayIcon *m_sysTrayIcon; // 系统托盘
	void initSysTrayIcon();

	QMenu *m_menu;			   // 菜单
    QAction *m_mainAction;     // 主界面
	QAction *m_showAboutAction; // 关于
	QAction *m_exitAppAction;  // 退出
	void createActions();
	void createMenu();

private slots:
    void on_showMainAction();
	void on_showAboutAction();
	void on_exitAppAction();

	void on_pushButton_clicked();

protected:
	void closeEvent(QCloseEvent *event) override;
};

#endif // MYTRAYWIDGET_H
