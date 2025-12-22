#include "infocard.h"
#include <QGraphicsDropShadowEffect>
#include <QHBoxLayout>

InfoCard::InfoCard(const QString &title, QWidget *parent)
    : QWidget(parent)
    , m_title(title)
    , m_iconLabel(new QLabel(this))
    , m_titleLabel(new QLabel(this))
    , m_valueLabel(new QLabel(this))
    , m_subtitleLabel(new QLabel(this))
    , m_progressBar(new QProgressBar(this))
{
    setupUI();
}

void InfoCard::setupUI()
{
    //Main layout
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(12, 12, 12, 12);
    mainLayout->setSpacing(6);

    // Header layout (icon + title)
    QHBoxLayout *headerLayout = new QHBoxLayout();
    headerLayout->setSpacing(6);

    m_iconLabel->setFixedSize(24, 24);
    m_iconLabel->setScaledContents(false);
    m_iconLabel->setAlignment(Qt::AlignCenter);
    QFont iconFont;
    iconFont.setPointSize(16);
    m_iconLabel->setFont(iconFont);

    // Add glow effect for dark mode visibility
    QGraphicsDropShadowEffect *iconGlow = new QGraphicsDropShadowEffect();
    iconGlow->setBlurRadius(15);
    iconGlow->setColor(QColor(255,255,255,180));
    iconGlow->setOffset(0, 0);
    m_iconLabel->setGraphicsEffect(iconGlow);

    // Add background to icon label for better visibility
    m_iconLabel->setStyleSheet(
        "QLabel {"
        "   background-color: #808080;"
        "   border-radius: 4px;"
        "   padding: 2px;"
        "}"
        );

    headerLayout->addWidget(m_iconLabel);

    m_titleLabel->setText(m_title);
    m_titleLabel->setStyleSheet("font-size: 11pt; font-weight: bold;");
    headerLayout->addWidget(m_titleLabel);
    headerLayout->addStretch();

    mainLayout->addLayout(headerLayout);

    //Value Label
    m_valueLabel->setText("0%");
    m_valueLabel->setStyleSheet("font-size: 20pt; font-weight: bold;");
    m_valueLabel->setAlignment(Qt::AlignLeft);
    mainLayout->addWidget(m_valueLabel);

    // Subtitle label
    m_subtitleLabel->setStyleSheet("font-size: 9pt;");
    m_subtitleLabel->setAlignment(Qt::AlignLeft);
    mainLayout->addWidget(m_subtitleLabel);

    // Progress bar
    m_progressBar->setMinimum(0);
    m_progressBar->setMaximum(100);
    m_progressBar->setValue(0);
    m_progressBar->setTextVisible(false);
    m_progressBar->setFixedHeight(6);
    mainLayout->addWidget(m_progressBar);

    mainLayout->addStretch();

    setMinimumSize(220, 120);
    setMaximumHeight(130);

    // Add shadow effect
    QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect();
    shadow->setBlurRadius(10);
    shadow->setColor(QColor(0, 0, 0, 30));
    shadow->setOffset(0, 2);
    setGraphicsEffect(shadow);

    // Apply initial theme
    // applyTheme();
}
