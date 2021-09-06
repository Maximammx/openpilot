#include "selfdrive/ui/qt/widgets/ssh_keys.h"

#include "selfdrive/common/params.h"
#include "selfdrive/ui/qt/api.h"
#include "selfdrive/ui/qt/widgets/input.h"

latkpv::latkpv() : AbstractControl("Lat Kpv", "Description here", "../assets/offroad/icon_shell.png") {

  label.setAlignment(Qt::AlignVCenter|Qt::AlignRight);
  label.setStyleSheet("color: #e0e879");
  hlayout->addWidget(&label);

  btndigit.setStyleSheet(R"(
    QPushButton {
      padding: 0;
      border-radius: 50px;
      font-size: 35px;
      font-weight: 500;
      color: #E4E4E4;
      background-color: #393939;
    }
    QPushButton:pressed {
      background-color: #ababab;
    }
  )");
  btnminus.setStyleSheet(R"(
    QPushButton {
      padding: 0;
      border-radius: 50px;
      font-size: 35px;
      font-weight: 500;
      color: #E4E4E4;
      background-color: #393939;
    }
    QPushButton:pressed {
      background-color: #ababab;
    }
  )");
  btnplus.setStyleSheet(R"(
    QPushButton {
      padding: 0;
      border-radius: 50px;
      font-size: 35px;
      font-weight: 500;
      color: #E4E4E4;
      background-color: #393939;
    }
    QPushButton:pressed {
      background-color: #ababab;
    }
  )");
  btndigit.setFixedSize(100, 100);
  btnminus.setFixedSize(100, 100);
  btnplus.setFixedSize(100, 100);
  hlayout->addWidget(&btndigit);
  hlayout->addWidget(&btnminus);
  hlayout->addWidget(&btnplus);
  btndigit.setText("0.01");
  btnminus.setText("-");
  btnplus.setText("+");

  QObject::connect(&btndigit, &QPushButton::clicked, [=]() {
    digit = digit * 10;
    if (digit >= 11 ) {
      digit = 0.01;
    }
    QString level = QString::number(digit);
    btndigit.setText(level);
  });

  QObject::connect(&btnminus, &QPushButton::clicked, [=]() {
    auto str = QString::fromStdString(params.get("LatKpv"));
    int value = str.toInt();
    value = value - digit;
    if (value <= 0.1) {
      value = 0.1;
    }
    QString values = QString::number(value);
    params.put("LatKpv", values.toStdString());
    refresh();
  });
  
  QObject::connect(&btnplus, &QPushButton::clicked, [=]() {
    auto str = QString::fromStdString(params.get("LatKpv"));
    int value = str.toInt();
    value = value + digit;
    QString values = QString::number(value);
    params.put("LatKpv", values.toStdString());
    refresh();
  });
  refresh();
}

void latkpv::refresh() {
  auto strs = QString::fromStdString(params.get("LatKpv"));
  int valuei = strs.toInt();
  float valuef = valuei * 0.0001;
  QString valuefs = QString::number(valuef);
  label.setText(QString::fromStdString(valuefs.toStdString()));
}

SshControl::SshControl() : ButtonControl("SSH Keys", "", "Warning: This grants SSH access to all public keys in your GitHub settings. Never enter a GitHub username other than your own. A comma employee will NEVER ask you to add their GitHub username.") {
  username_label.setAlignment(Qt::AlignRight | Qt::AlignVCenter);
  username_label.setStyleSheet("color: #aaaaaa");
  hlayout->insertWidget(1, &username_label);

  QObject::connect(this, &ButtonControl::clicked, [=]() {
    if (text() == "ADD") {
      QString username = InputDialog::getText("Enter your GitHub username", this);
      if (username.length() > 0) {
        setText("LOADING");
        setEnabled(false);
        getUserKeys(username);
      }
    } else {
      params.remove("GithubUsername");
      params.remove("GithubSshKeys");
      refresh();
    }
  });

  refresh();
}

void SshControl::refresh() {
  QString param = QString::fromStdString(params.get("GithubSshKeys"));
  if (param.length()) {
    username_label.setText(QString::fromStdString(params.get("GithubUsername")));
    setText("REMOVE");
  } else {
    username_label.setText("");
    setText("ADD");
  }
  setEnabled(true);
}

void SshControl::getUserKeys(const QString &username) {
  HttpRequest *request = new HttpRequest(this, false);
  QObject::connect(request, &HttpRequest::receivedResponse, [=](const QString &resp) {
    if (!resp.isEmpty()) {
      params.put("GithubUsername", username.toStdString());
      params.put("GithubSshKeys", resp.toStdString());
    } else {
      ConfirmationDialog::alert("Username '" + username + "' has no keys on GitHub", this);
    }
    refresh();
    request->deleteLater();
  });
  QObject::connect(request, &HttpRequest::failedResponse, [=] {
    ConfirmationDialog::alert("Username '" + username + "' doesn't exist on GitHub", this);
    refresh();
    request->deleteLater();
  });
  QObject::connect(request, &HttpRequest::timeoutResponse, [=] {
    ConfirmationDialog::alert("Request timed out", this);
    refresh();
    request->deleteLater();
  });

  request->sendRequest("https://github.com/" + username + ".keys");
}
