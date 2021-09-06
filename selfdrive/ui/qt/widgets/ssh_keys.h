#pragma once

#include <QPushButton>

#include "selfdrive/hardware/hw.h"
#include "selfdrive/ui/qt/widgets/controls.h"

class latkpv : public AbstractControl {
  Q_OBJECT

public:
  latpiv();

private:
  QPushButton btndigit;
  QPushButton btnminus;
  QPushButton btnplus;
  QLabel label;
  Params params;
  float digit = 0.01;
  
  void refresh();
};

// SSH enable toggle
class SshToggle : public ToggleControl {
  Q_OBJECT

public:
  SshToggle() : ToggleControl("Enable SSH", "", "", Hardware::get_ssh_enabled()) {
    QObject::connect(this, &SshToggle::toggleFlipped, [=](bool state) {
      Hardware::set_ssh_enabled(state);
    });
  }
};

// SSH key management widget
class SshControl : public ButtonControl {
  Q_OBJECT

public:
  SshControl();

private:
  Params params;

  QLabel username_label;

  void refresh();
  void getUserKeys(const QString &username);
};
