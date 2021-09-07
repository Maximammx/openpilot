#include "selfdrive/ui/qt/widgets/ssh_keys.h"

#include "selfdrive/common/params.h"
#include "selfdrive/ui/qt/api.h"
#include "selfdrive/ui/qt/widgets/input.h"

latkiv::latkiv() : AbstractControl("Lat Kiv", "Description here", "../assets/offroad/icon_shell.png") {

  ilabel.setAlignment(Qt::AlignVCenter|Qt::AlignRight);
  ilabel.setStyleSheet("color: #e0e879");
  hlayout->addWidget(&ilabel);

  ibtndigit.setStyleSheet(R"(
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
  ibtnminus.setStyleSheet(R"(
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
  ibtnplus.setStyleSheet(R"(
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
  ibtndigit.setFixedSize(100, 100);
  ibtnminus.setFixedSize(100, 100);
  ibtnplus.setFixedSize(100, 100);
  hlayout->addWidget(&ibtndigit);
  hlayout->addWidget(&ibtnminus);
  hlayout->addWidget(&ibtnplus);
  ibtndigit.setText("0.01");
  ibtnminus.setText("-");
  ibtnplus.setText("+");

  QObject::connect(&ibtndigit, &QPushButton::clicked, [=]() {
    idigit = idigit * 10;
    if (idigit >= 11 ) {
      idigit = 0.01;
    }
    QString level = QString::number(idigit);
    ibtndigit.setText(level);
  });

  QObject::connect(&ibtnminus, &QPushButton::clicked, [=]() {
    auto str = QString::fromStdString(params.get("LatKiv"));
    int value = str.toInt();
    value = value - idigit;
    QString values = QString::number(value);
    params.put("LatKiv", values.toStdString());
    irefresh();
  });
  
  QObject::connect(&ibtnplus, &QPushButton::clicked, [=]() {
    auto str = QString::fromStdString(params.get("LatKiv"));
    int value = str.toInt();
    value = value + idigit;
    QString values = QString::number(value);
    params.put("LatKiv", values.toStdString());
    irefresh();
  });
  irefresh();
}

latkpv::latkpv() : AbstractControl("Lat Kpv", "Description here", "../assets/offroad/icon_shell.png") {

  plabel.setAlignment(Qt::AlignVCenter|Qt::AlignRight);
  plabel.setStyleSheet("color: #e0e879");
  hlayout->addWidget(&plabel);

  pbtndigit.setStyleSheet(R"(
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
  pbtnminus.setStyleSheet(R"(
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
  pbtnplus.setStyleSheet(R"(
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
  pbtndigit.setFixedSize(100, 100);
  pbtnminus.setFixedSize(100, 100);
  pbtnplus.setFixedSize(100, 100);
  hlayout->addWidget(&pbtndigit);
  hlayout->addWidget(&pbtnminus);
  hlayout->addWidget(&pbtnplus);
  pbtndigit.setText("0.01");
  pbtnminus.setText("-");
  pbtnplus.setText("+");

  QObject::connect(&pbtndigit, &QPushButton::clicked, [=]() {
    pdigit = pdigit * 10;
    if (pdigit >= 11 ) {
      pdigit = 0.01;
    }
    QString level = QString::number(pdigit);
    pbtndigit.setText(level);
  });

  QObject::connect(&pbtnminus, &QPushButton::clicked, [=]() {
    auto str = QString::fromStdString(params.get("LatKpv"));
    int value = str.toInt();
    value = value - pdigit;
    QString values = QString::number(value);
    params.put("LatKpv", values.toStdString());
    prefresh();
  });
  
  QObject::connect(&pbtnplus, &QPushButton::clicked, [=]() {
    auto str = QString::fromStdString(params.get("LatKpv"));
    int value = str.toInt();
    value = value + pdigit;
    QString values = QString::number(value);
    params.put("LatKpv", values.toStdString());
    prefresh();
  });
  prefresh();
}

void latkpv::prefresh() {
  auto strs = QString::fromStdString(params.get("LatKpv"));
  int valuei = strs.toInt();
  float valuef = valuei * 0.0001;
  QString valuefs = QString::number(valuef);
  plabel.setText(QString::fromStdString(valuefs.toStdString()));
}

void latkiv::irefresh() {
  auto strs = QString::fromStdString(params.get("LatKiv"));
  int valuei = strs.toInt();
  float valuef = valuei * 0.0001;
  QString valuefs = QString::number(valuef);
  ilabel.setText(QString::fromStdString(valuefs.toStdString()));
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
