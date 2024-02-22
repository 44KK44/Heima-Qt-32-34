#include "mywidget.h"
#include "ui_mywidget.h"
#include <QKeyEvent>
#include <QDebug>
#include <QTimerEvent>
#include <QString>
#include <QMessageBox>
#include <QEvent>

MyWidget::MyWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MyWidget)
{
    ui->setupUi(this);

    timerID = this->startTimer(1000);//间隔1s
    this->timerID2 = this->startTimer(500);//间隔0.5s

    connect(ui->pushButton, &mybutton::clicked,
            [=]()
            {
                qDebug() << "按钮被按下";
            }
            );

    //安装过滤器
    ui->label_2->installEventFilter(this);

    //设置鼠标追踪
    ui->label_2->setMouseTracking(true);
}

MyWidget::~MyWidget()
{
    delete ui;
}

void MyWidget::keyPressEvent(QKeyEvent *ev)
{
    if (ev->key() == Qt::Key_A)
    {
        ui->label->setText("<center><h1>A</h1></center>");
    }
    else if (ev->key() == Qt::Key_Up)
    {
        ui->label->setText("<center><h1>Up</h1></center>");
    }
    else if (ev->key() == Qt::Key_Down)
    {
        ui->label->setText("<center><h1>Down</h1></center>");
    }
    else if (ev->key() == Qt::Key_Left)
    {
        ui->label->setText("<center><h1>Left</h1></center>");
    }
    else if (ev->key() == Qt::Key_Right)
    {
        ui->label->setText("<center><h1>Right</h1></center>");
    }
    else
    {
        ui->label->setText("<center><h1>other key</h1></center>");
    }
}

void MyWidget::timerEvent(QTimerEvent *ev)
{
    if(ev->timerId() == this->timerID){
        static int sec = 0;
        // sec++;
        ui->label->setText(QString{"<center><h1>time: %1</h1></center>"}.arg(sec++));

        if(10 == sec)
        {
            this->killTimer(timerID);//停止定时器
        }
    }
    else if(ev->timerId() == this->timerID2){
        static int sec = 0;
        // sec++;
        ui->label_2->setText(QString{"<center><h1>time: %1</h1></center>"}.arg(sec++));

        if(10 == sec)
        {
            this->killTimer(timerID2);//停止定时器
        }
    }
}

void MyWidget::mousepressevent(QMouseEvent *ev)
{
    qDebug() << "6666666666";
}

void MyWidget::clodeEvent(QCloseEvent *ev)
{
    int ret = QMessageBox::question(this, "question", "是否关闭窗口");
    if(ret == QMessageBox::Yes)
    {
        //关闭窗口
        ev->accept();//接受事件
    }
    else
    {
        //忽略事件
        ev->ignore();
    }
}

bool MyWidget::event(QEvent *ev)
{
    // switch (ev->type())
    // {
    //     case QEvent::Close:
    //         closeEvent((QCloseEvent *)ev);
    //     break;

    //     case QEvent::MouseMove:
    //         mousepressevent((QMouseEvent *)ev);
    //     break;
    // }
    if(ev->type() == QEvent::Timer)
    {
        //定时器事件
        timerEvent((QTimerEvent *)ev);
        return true;
    }
    else if(ev->type() == QEvent::KeyPress)
    {
        //键盘按下事件
        QKeyEvent *event = static_cast<QKeyEvent *>(ev);
        if(event->key() == Qt::Key_B)
        {
            qDebug() << "B pressed";
            return QWidget::event(ev);
        }
        else
        {
            keyPressEvent(event);
            return true;
        }
    }
    else
    {
        //键盘按下事件
        return QWidget::event(ev);
    }
}

bool MyWidget::eventFilter(QObject *watched, QEvent *event)
{
    if(watched == ui->label_2)
    {
        QMouseEvent *event = static_cast<QMouseEvent *>(event);
        //判断事件
        if(event->type() == QEvent::MouseMove)
        {
            ui->label_2->setText("鼠标移动:(%1, %2)").arg(event->x()).arg(event->y());
            return true;
        }
        //鼠标按下
        else if(event->type() == QEvent::MouseButtonPress)
        {
            ui->label_2->setText("鼠标按下");
            return true;
        }
        else
        {
            return QWidget::eventFilter(watched, event);
        }
        //鼠标释放
        // else if(event->type() == QEvent::MouseButtonRelease)

    }
    else
    {
        return QWidget::eventFilter(watched, event);
    }
    return QWidget::eventFilter(watched, event);
}
