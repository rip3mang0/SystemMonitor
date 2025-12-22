#ifndef INFOCARD_H
#define INFOCARD_H

#include <QWidget>
#include <QLabel>
#include <QProgressBar>
#include <QBoxLayout>
#include <QIcon>

class InfoCard : public QWidget
{
    Q_OBJECT
public:
    explicit InfoCard(const QString &title, QWidget *parent = nullptr);

private:
    void setupUI();

private:
    QString m_title;
    QLabel *m_iconLabel;
    QLabel *m_titleLabel;
    QLabel *m_valueLabel;
    QLabel *m_subtitleLabel;
    QProgressBar *m_progressBar;
};

#endif // INFOCARD_H
