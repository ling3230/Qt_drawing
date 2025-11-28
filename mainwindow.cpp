#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QColorDialog>
#include <QFileDialog>
#include <QMessageBox>
#include <QPushButton>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_canvasWidget(nullptr)  // 初始化画布指针
{

    ui->setupUi(this);

    // 加载背景图片
    m_background.load("C:/aaa_learn/QT_draw/Draw/resources/green.png");

    // 设置中央部件背景透明
    ui->centralwidget->setStyleSheet("background: transparent;");

    // 设置窗口大小
    this->resize(1000, 700);

    // 设置布局紧凑
    ui->verticalLayout->setSpacing(2);
    ui->verticalLayout->setContentsMargins(3, 3, 3, 3);

    // 查找并初始化画布控件
    m_canvasWidget = findChild<CanvasWidget*>("canvasWidget");
    if (!m_canvasWidget) {
        // 如果UI设计器中没找到，动态创建
        m_canvasWidget = new CanvasWidget(this);
        // 需要在这里手动将画布添加到布局中
    }

    // 连接画布信号
    connect(m_canvasWidget, &CanvasWidget::shapeCountChanged,
            this, &MainWindow::onShapeCountChanged);

    // 连接按钮信号槽
    connect(ui->lineButton, &QPushButton::clicked, this, &MainWindow::onLineButtonClicked);
    connect(ui->rectButton, &QPushButton::clicked, this, &MainWindow::onRectButtonClicked);
    connect(ui->circleButton, &QPushButton::clicked, this, &MainWindow::onCircleButtonClicked);
    connect(ui->freePenButton, &QPushButton::clicked, this, &MainWindow::onFreePenButtonClicked);
    connect(ui->colorButton, &QPushButton::clicked, this, &MainWindow::onColorButtonClicked);
    connect(ui->undoButton, &QPushButton::clicked, this, &MainWindow::onUndoButtonClicked);
    connect(ui->saveButton, &QPushButton::clicked, this, &MainWindow::onSaveButtonClicked);

    connect(ui->penWidthSpinBox, QOverload<int>::of(&QSpinBox::valueChanged),
            this, &MainWindow::onPenWidthChanged);

    // 初始化颜色按钮
    ui->colorButton->setStyleSheet("background-color: black;");

    // 设置按钮紧凑样式
    this->setStyleSheet(
        "QPushButton { "
        "   min-height: 25px; "
        "   max-height: 25px; "
        "   margin: 0px; "
        "   padding: 2px; "
        "   font-size: 11px; "
        "} "
        "QSpinBox { "
        "   min-height: 25px; "
        "   max-height: 25px; "
        "} "
        );
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::onLineButtonClicked() {
    if (m_canvasWidget) {
        m_canvasWidget->setCurrentShapeType(0);
    }
}

void MainWindow::onRectButtonClicked() {
    if (m_canvasWidget) {
        m_canvasWidget->setCurrentShapeType(1);
    }
}

void MainWindow::onCircleButtonClicked() {
    if (m_canvasWidget) {
        m_canvasWidget->setCurrentShapeType(2);
    }
}

void MainWindow::onFreePenButtonClicked() {
    if (m_canvasWidget) {
        m_canvasWidget->setCurrentShapeType(3);
    }
}

void MainWindow::onColorButtonClicked() {
    QColor color = QColorDialog::getColor(Qt::black, this, "选择画笔颜色");
    if (color.isValid() && m_canvasWidget) {
        m_canvasWidget->setCurrentColor(color);
        // 更新颜色按钮背景
        ui->colorButton->setStyleSheet(QString("background-color: %1").arg(color.name()));
    }
}

void MainWindow::onUndoButtonClicked() {
    if (m_canvasWidget) {
        m_canvasWidget->undo();
    }
}

void MainWindow::onSaveButtonClicked() {
    if (!m_canvasWidget) return;

    QString fileName = QFileDialog::getSaveFileName(this, "保存图像", "", "PNG Images (*.png)");
    if (!fileName.isEmpty()) {
        if (m_canvasWidget->saveImage(fileName)) {
            QMessageBox::information(this, "成功", "图像保存成功！");
        } else {
            QMessageBox::warning(this, "错误", "保存失败！");
        }
    }
}

void MainWindow::onShapeCountChanged(int count) {
    // 可以在这里更新状态栏显示形状数量
    // 例如：statusBar()->showMessage(QString("已绘制 %1 个形状").arg(count));
    Q_UNUSED(count);
}

void MainWindow::onPenWidthChanged(int width) {
    if (m_canvasWidget) {
        m_canvasWidget->setPenWidth(width);
    }
}

void MainWindow::paintEvent(QPaintEvent* event)
{
    // 先绘制背景图片
    if (!m_background.isNull()) {
        QPainter painter(this);
        painter.drawPixmap(0, 0, width(), height(), m_background);
    }

    // 调用父类的绘制事件
    QMainWindow::paintEvent(event);
}
