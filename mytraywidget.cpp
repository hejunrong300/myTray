#include "mytraywidget.h"
#include "ui_mytraywidget.h"
#include <QMessageBox>

myTrayWidget::myTrayWidget(QWidget *parent) : QWidget(parent), ui(new Ui::myTrayWidget)
{
	ui->setupUi(this);
	initSysTrayIcon();
}

myTrayWidget::~myTrayWidget()
{
	delete ui;
}

// 创建系统托盘
void myTrayWidget::initSysTrayIcon()
{
	// 隐藏程序主窗口
	this->hide();

	// 新建QSystemTrayIcon对象
	m_sysTrayIcon = new QSystemTrayIcon(this);

	// 设置托盘图标
	QIcon icon = QIcon(":/images/test.ico"); // 资源文件添加的图标
	m_sysTrayIcon->setIcon(icon);

	// 当鼠标移动到托盘上的图标时，会显示此处设置的内容
	m_sysTrayIcon->setToolTip("托盘提示信息");

	// 给QSystemTrayIcon添加槽函数
	connect(m_sysTrayIcon, &QSystemTrayIcon::activated, [=](QSystemTrayIcon::ActivationReason reason) {
		switch (reason) {
		case QSystemTrayIcon::Trigger:
			// 单击托盘图标
			m_sysTrayIcon->showMessage(QObject::trUtf8("Message Title"),
									   QObject::trUtf8("欢迎使用此程序"),
									   QSystemTrayIcon::Information,
									   1000);
			this->show();
			break;
		case QSystemTrayIcon::DoubleClick:
			// 双击托盘图标
			// 双击后显示主程序窗口
			this->show();
			break;
		default:
			break;
		}
	});

	// 建立托盘操作的菜单
	createActions();
	createMenu();
	ui->textEdit->setText("贺军荣万岁！！！");
	ui->pushButton->setIcon(QIcon(":/images/test.ico"));
	// 在系统托盘显示此对象
	m_sysTrayIcon->show();
}

// 创建动作
void myTrayWidget::createActions()
{
    m_mainAction = new QAction("主界面", this);
    connect(m_mainAction, SIGNAL(triggered()), this, SLOT(on_showMainAction()));

	m_showAboutAction = new QAction("关于系统", this);
	connect(m_showAboutAction, SIGNAL(triggered()), this, SLOT(on_showAboutAction()));

	m_exitAppAction = new QAction("退出", this);
	connect(m_exitAppAction, SIGNAL(triggered()), this, SLOT(on_exitAppAction()));
}

// 创建托盘菜单
void myTrayWidget::createMenu()
{
	m_menu = new QMenu(this);
	// 新增菜单项---显示主界面
    m_menu->addAction(m_mainAction);
	// 增加分隔符
	// m_menu->addSeparator();
    // 显示关于
	m_menu->addAction(m_showAboutAction);
	// 增加分隔符
	// m_menu->addSeparator();
	// 新增菜单项---退出程序
	m_menu->addAction(m_exitAppAction);
	// 把QMenu赋给QSystemTrayIcon对象
	m_sysTrayIcon->setContextMenu(m_menu);
}

void myTrayWidget::on_showMainAction()
{
    this->show();
}

// 当在系统托盘点击菜单内的显示主界面操作
void myTrayWidget::on_showAboutAction()
{
	QApplication::setQuitOnLastWindowClosed(false);
	QMessageBox::information(nullptr, "提示", "中星伟业科技有限公司copyright©2023");
}

// 当在系统托盘点击菜单内的退出程序操作
void myTrayWidget::on_exitAppAction()
{
	qApp->exit();
}

// 关闭事件
void myTrayWidget::closeEvent(QCloseEvent *event)
{
	// 忽略窗口关闭事件
	QApplication::setQuitOnLastWindowClosed(true);
	this->hide();
	event->ignore();
}

void myTrayWidget::on_pushButton_clicked()
{
	QMessageBox::information(this, "提示信息", "串口测试正常！");
}
