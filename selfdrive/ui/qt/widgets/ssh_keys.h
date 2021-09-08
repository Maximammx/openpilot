#pragma once

#include <QPushButton>

#include "selfdrive/hardware/hw.h"
#include "selfdrive/ui/qt/widgets/controls.h"

class latkpv : public AbstractControl {
  Q_OBJECT

public:
  latkpv();
private:
  QPushButton pbtndigit;
  QPushButton pbtnminus;
  QPushButton pbtnplus;
  QLabel plabel;
  Params params;
  int pdigit = 1;
  
  void prefresh();
};

class latkiv : public AbstractControl {
  Q_OBJECT

public:
  latkiv();
private:
  QPushButton ibtndigit;
  QPushButton ibtnminus;
  QPushButton ibtnplus;
  QLabel ilabel;
  Params params;
  int idigit = 1;
  
  void irefresh();
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
