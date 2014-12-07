/*
 * Copyright 2014 Joseph Mills.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; version 3.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * Author: Joseph Mills  <josephjamesmills@gmail.com>
 */
#ifndef SPEECHRECOGNITION_H
#define SPEECHRECOGNITION_H

#include <QObject>
#include <QList>

class QIODevice;
class QNetworkAccessManager;
class QNetworkReply;
class SpeechRecognition : public QObject {
  Q_OBJECT
    Q_PROPERTY(QString results READ results NOTIFY resultsChanged)

public:
  SpeechRecognition( QObject* parent = 0);
  static const char* kUrl;
  static const char* kContentType;

  struct Hypothesis {
    QString utterance;
    qreal confidence;
  };
  typedef QList<Hypothesis> Hypotheses;

  // This enumeration follows the values described here:
  // http://www.w3.org/2005/Incubator/htmlspeech/2010/10/google-api-draft.html#speech-input-error
  enum Result {
    Result_Success = 0,
    Result_ErrorAborted,
    Result_ErrorAudio,
    Result_ErrorNetwork,
    Result_NoSpeech,
    Result_NoMatch,
    Result_BadGrammar
  };
  Q_INVOKABLE void start();
  void Cancel();
  QString results()const;
  void setResults(const QString &results);

signals:
  void Finished(Result result, const Hypotheses& hypotheses);
  void resultsChanged();

private slots:
  void replyFinished(QNetworkReply* reply);

private:
  void ParseResponse(QIODevice* reply, Result* result, Hypotheses* hypotheses);

private:
  QNetworkAccessManager* network_;
  QNetworkReply* reply_;
  QByteArray buffered_raw_data_;
  int num_samples_recorded_;
    QString m_results;
};

#endif // SPEECHRECOGNITION_H
