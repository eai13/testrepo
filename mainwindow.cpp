#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QDateTime>
#include <QTimeZone>

MainWindow::MainWindow(QWidget* parent)
  : QMainWindow(parent)
  , ui(new Ui::MainWindow)
  , _tickCount{ 0 }
  , _timerTick{ this }
  , _timerSync{ this }
{
  ui->setupUi(this);

  connect(&_timerTick, &QTimer::timeout, this, &MainWindow::onTick);
  connect(&_timerSync, &QTimer::timeout, this, &MainWindow::onSyncDateTime);
  connect(ui->pbStart, &QPushButton::clicked, this, &MainWindow::startTick);
  connect(ui->pbStop, &QPushButton::clicked, this, &MainWindow::stopTick);

  _timerSync.start(500);

  onSyncDateTime();
  stopTick();
}

MainWindow::~MainWindow()
{
  delete ui;
}

void
MainWindow::onSyncDateTime()
{
  ui->lblTime->setText(formattedDateTime());
}

void
MainWindow::startTick()
{
  ui->pbStart->setEnabled(false);
  ui->pbStop->setEnabled(true);
  _timerTick.start(1000);
}

void
MainWindow::stopTick()
{
  ui->pbStart->setEnabled(true);
  ui->pbStop->setEnabled(false);
  _timerTick.stop();
}

void
MainWindow::onTick()
{
  ui->teLog->append(
    QStringLiteral("%1\tTick %2").arg(formattedDateTime()).arg(_tickCount++));
}

QString
MainWindow::formattedDateTime() const
{
  return QDateTime::currentDateTime().toString("yyyy/MM/ddThh:mm:ss");
}
