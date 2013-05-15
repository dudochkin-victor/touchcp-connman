/*   -*- Mode: C++ -*-
 * meegotouchcp-connman - connectivity plugin for duicontrolpanel
 * Copyright © 2010, Intel Corporation.
 *
 * This program is licensed under the terms and conditions of the
 * Apache License, version 2.0.  The full text of the Apache License is at
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 */
#ifndef NETWORKLISTMODEL_H
#define NETWORKLISTMODEL_H

#include "networkitemmodel.h"
#include "manager.h"

#include <QAbstractTableModel>
#include <QtDBus>

class NetworkListModel : public QAbstractTableModel
{
  Q_OBJECT;

  Q_PROPERTY(bool offlineMode READ offlineMode WRITE setOfflineMode NOTIFY offlineModeChanged);
  Q_PROPERTY(QString defaultTechnology READ defaultTechnology NOTIFY defaultTechnologyChanged);
  Q_PROPERTY(QString state READ state NOTIFY stateChanged);

public:
  static NetworkListModel* instance();
  virtual ~NetworkListModel();
  int rowCount(const QModelIndex &parent = QModelIndex()) const;
  int columnCount(const QModelIndex &parent = QModelIndex()) const;
  QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
  QVariant data(const QModelIndex &index, int role) const;
  void enableTechnology(const QString &technology);
  void disableTechnology(const QString &technology);
  void connectService(const QString &name, const QString &security,
		      const QString &passphrase);
  const QStringList availableTechnologies() const;
  const QStringList enabledTechnologies() const;
  const QStringList connectedTechnologies() const;

public slots:
  void requestScan();
  bool offlineMode() const;
  void setOfflineMode(const bool &offlineMode);
  QString defaultTechnology() const;
  QString state() const;

signals:
  void technologiesChanged(const QStringList &availableTechnologies,
			   const QStringList &enabledTechnologies,
			   const QStringList &connectedTechnologies);
  void offlineModeChanged(bool offlineMode);
  void defaultTechnologyChanged(const QString &defaultTechnology);
  void stateChanged(const QString &state);

protected:
  void timerEvent(QTimerEvent *event); //hack


private:
  NetworkListModel();
  void connectToConnman();
  void disconnectFromConnman();
  int findNetworkItemModel(const QDBusObjectPath &path) const;
  void emitTechnologiesChanged();

  Manager *m_manager;
  QDBusPendingCallWatcher *m_getPropertiesWatcher;
  QDBusPendingCallWatcher *m_connectServiceWatcher;
  QVariantMap m_propertiesCache;
  QVector<NetworkItemModel*> m_networks;
  QStringList m_headerData;
  static const QString availTechs;
  static const QString enablTechs;
  static const QString connTechs;
  static const QString OfflineMode;
  static const QString DefaultTechnology;
  static const QString State;

private slots:
  void getPropertiesReply(QDBusPendingCallWatcher *call);
  void connectServiceReply(QDBusPendingCallWatcher *call);
  void propertyChanged(const QString &name,
		       const QDBusVariant &value);
  void networkItemModified(const QList<const char *> &members);

private:
  Q_DISABLE_COPY(NetworkListModel);
};

#endif //NETWORKLISTMODEL_H
