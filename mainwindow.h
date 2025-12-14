#pragma once

#include <QMainWindow>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  MainWindow(QWidget* parent = nullptr);
  ~MainWindow();

private:
  void onSyncDateTime(void);
  void startTick(void);
  void stopTick(void);
  void onTick(void);
  void setStatusBarText(void);

  QString formattedDateTime(void) const;

  Ui::MainWindow* ui;

  uint64_t _tickCount{ 0 };
  QTimer _timerTick;
  QTimer _timerSync;
};
