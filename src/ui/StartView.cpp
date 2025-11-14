#include "StartView.hpp"
#include "ui_StartView.h"
#include <QFile>
#include <QTextStream>
#include <QDir>
#include <QPainter>

StartView::StartView(QWidget* parent)
    : QWidget(parent)
    , _ui(new Ui::StartView)
{
    _ui->setupUi(this);

    // 设置标题样式
    _ui->titleLabel->setStyleSheet(
        "font-size: 48px; "
        "font-weight: bold; "
        "color: #4CAF50; "
        "padding: 20px;"
    );

    // 设置按钮样式
    QString buttonStyle = 
        "QPushButton {"
        "    font-size: 24px; "
        "    font-weight: bold; "
        "    background-color: #4CAF50; "
        "    color: white; "
        "    border: none; "
        "    border-radius: 10px; "
        "    padding: 15px; "
        "}"
        "QPushButton:hover {"
        "    background-color: #45a049; "
        "}"
        "QPushButton:pressed {"
        "    background-color: #3d8b40; "
        "}";

    _ui->playButton->setStyleSheet(buttonStyle);
    _ui->encyclopediaButton->setStyleSheet(buttonStyle);
    _ui->recordsButton->setStyleSheet(buttonStyle);

    // 创建底层 QLabel 作为背景，保留按钮等控件的样式不变
    // 先尝试从 qrc 资源加载
    _bgPixmap = QPixmap(":/pictures/startview_bg.png");
    bool usedFallback = false;
    if (_bgPixmap.isNull()) {
        // 如果 qrc 加载失败，尝试从可执行相对路径加载 docs/pictures/startview_bg.png
        QString fallbackPath = QCoreApplication::applicationDirPath() + QDir::separator() + QLatin1String("..") + QDir::separator() + QLatin1String("docs") + QDir::separator() + QLatin1String("pictures") + QDir::separator() + QLatin1String("startview_bg.png");
        if (QFile::exists(fallbackPath)) {
            QPixmap p;
            if (p.load(fallbackPath)) {
                _bgPixmap = p;
                usedFallback = true;
            }
        }
    }

    // 诊断日志：把资源加载结果写入当前目录和系统临时目录，便于在外部检查
    QString cwdLogPath = QDir::currentPath() + QDir::separator() + "startview_debug.txt";
    QString tmpLogPath = QDir::tempPath() + QDir::separator() + "startview_debug.txt";
    auto writeLog = [&](const QString& path) {
        QFile f(path);
        if (f.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text)) {
            QTextStream out(&f);
            out << "ResourceExists(:/pictures/startview_bg.png): " << (QFile::exists(":/pictures/startview_bg.png") ? "true" : "false") << "\n";
            out << "LoadedPixmapIsNull: " << (_bgPixmap.isNull() ? "true" : "false") << "\n";
            out << "UsedFallbackPath: " << (usedFallback ? "true" : "false") << "\n";
            if (!_bgPixmap.isNull()) {
                out << "PixmapSize: " << _bgPixmap.size().width() << "x" << _bgPixmap.size().height() << "\n";
            }
            out << "---\n";
            f.close();
        }
    };
    writeLog(cwdLogPath);
    writeLog(tmpLogPath);

    if (!_bgPixmap.isNull()) {
        // 不使用自动填充背景，让 paintEvent 负责绘制背景（更稳定）
        setAutoFillBackground(false);
    } else {
        // 如果资源加载失败，保留一个浅灰背景作为回退，并写一条额外日志
        setStyleSheet("background-color: #f0f0f0;");
        writeLog(cwdLogPath);
        writeLog(tmpLogPath);
    }

    // 连接信号
    connect(_ui->playButton, &QPushButton::clicked, this, &StartView::playClicked);
    connect(_ui->encyclopediaButton, &QPushButton::clicked, this, &StartView::encyclopediaClicked);
    connect(_ui->recordsButton, &QPushButton::clicked, this, &StartView::recordsClicked);

    // 设置布局居中对齐
    _ui->buttonsLayout->setAlignment(Qt::AlignHCenter);
}

StartView::~StartView()
{
    delete _ui;
}

void StartView::resizeEvent(QResizeEvent* event)
{
    QWidget::resizeEvent(event);
    if (_bgLabel && !_bgPixmap.isNull()) {
        _bgLabel->setGeometry(rect());
        QPixmap scaled = _bgPixmap.scaled(_bgLabel->size(), Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);
        // 将 scaled 居中并设置到 label
        _bgLabel->setPixmap(scaled);
    }
}

void StartView::paintEvent(QPaintEvent* event)
{
    // 先由我们在最底层绘制背景，再让基类与子控件绘制（子控件会覆盖背景）
    if (!_bgPixmap.isNull()) {
        QPainter p(this);
        QSize targetSize = size();
        QPixmap scaled = _bgPixmap.scaled(targetSize, Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);
        // 计算居中偏移（当图片被放大裁剪时进行居中）
        int x = (targetSize.width() - scaled.width()) / 2;
        int y = (targetSize.height() - scaled.height()) / 2;
        p.drawPixmap(x, y, scaled);
    }

    // 调用基类以确保子控件正常绘制和事件处理
    QWidget::paintEvent(event);
}

