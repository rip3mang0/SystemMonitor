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
    // Setter Methods
    void setValue(const QString &value);
    void setPercentage(double percent);
    void setIcon(const QIcon &icon);
    void setIconText(const QString &iconText);
    void setSubtitle(const QString &subtitle);
    void updateTheme(); // Update colors for current theme

signals:

private:
    void setupUI();
    void applyTheme();

private:
    QString m_title;
    QLabel *m_iconLabel;
    QLabel *m_titleLabel;
    QLabel *m_valueLabel;
    QLabel *m_subtitleLabel;
    QProgressBar *m_progressBar;
};

#endif // INFOCARD_H
