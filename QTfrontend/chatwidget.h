/*
 * Hedgewars, a free turn based strategy game
 * Copyright (c) 2007 Igor Ulyanov <iulyanov@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 2 of the License
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA
 */

#ifndef _CHAT_WIDGET_INCLUDED
#define _CHAT_WIDGET_INCLUDED

#include <QWidget>
#include <QListWidget>
#include <QString>
#include <QGridLayout>

#include "SDLs.h"

class QTextBrowser;
class QLineEdit;
class QListWidget;
class QSettings;
class SDLInteraction;

class HWChatWidget : public QWidget
{
  Q_OBJECT

 public:
  HWChatWidget(QWidget* parent, QSettings * gameSettings, SDLInteraction * sdli, bool notify);
  void loadLists(const QString & nick);
  void saveLists(const QString & nick);
  void setShowReady(bool s);

private:
  void loadList(QStringList & list, const QString & file);
  void saveList(QStringList & list, const QString & file);
  void updateIcon(QListWidgetItem *item);
  void updateIcons();

 public slots:
  void onChatString(const QString& str);
  void onServerMessage(const QString& str);
  void nickAdded(const QString& nick, bool notifyNick);
  void nickRemoved(const QString& nick);
  void clear();
  void setReadyStatus(const QString & nick, bool isReady);
  void adminAccess(bool);

 signals:
  void chatLine(const QString& str);
  void kick(const QString & str);
  void ban(const QString & str);
  void info(const QString & str);
  void follow(const QString &);

 private:
  QGridLayout mainLayout;
  QTextBrowser* chatText;
  QStringList chatStrings;
  QStringList ignoreList, friendsList;
  QListWidget* chatNicks;
  QLineEdit* chatEditLine;
  QAction * acInfo;
  QAction * acKick;
  QAction * acBan;
  QAction * acFollow;
  QAction * acIgnore;
  QAction * acFriend;
  QSettings * gameSettings;
  SDLInteraction * sdli;
  Mix_Chunk *sound[4];
  bool notify;
  bool showReady;

 private slots:
  void returnPressed();
  void onBan();
  void onKick();
  void onInfo();
  void onFollow();
  void onIgnore();
  void onFriend();
  void chatNickDoubleClicked(QListWidgetItem * item);
  void chatNickSelected(int index);
};

#endif // _CHAT_WIDGET_INCLUDED
