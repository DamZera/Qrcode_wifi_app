#ifndef BACKEND_H
#define BACKEND_H

#include <QObject>
#include <QString>

#include <iostream>

class BackEnd : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString ssid READ ssid WRITE setSsid)
    Q_PROPERTY(QString password READ password WRITE setPassword)
    Q_PROPERTY(QString sourceImage READ sourceImage NOTIFY sourceImageChanged)

public:
    explicit BackEnd(QObject *parent = nullptr);

    QString ssid();
    QString password();
    void setSsid(const QString &ssid);
    void setPassword(const QString &password);
    QString sourceImage();

    Q_INVOKABLE void clickOnGenerate();

signals:
     void sourceImageChanged();

private:
    QString m_ssid;
    QString m_password;
    QString m_sourceImage;

    void qWifi(int mfactor, const char* ssid, const char* security, const char* password);
    void write_bitmap(const std::string path, const int width, const int height, bool* &data);
};

#endif // BACKEND_H
