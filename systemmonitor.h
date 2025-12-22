#ifndef SYSTEMMONITOR_H
#define SYSTEMMONITOR_H

#include <QObject>
#include <QTimer>
#include <QVector>
#include "utils/systeminfo.h"

class SystemMonitor : public QObject
{
    Q_OBJECT
public:
    explicit SystemMonitor(QObject *parent = nullptr);
    ~SystemMonitor();

    void startMonitoring(int intervalMs = 1000);
    void stopMonitoring();

    // Data retrieval methods
    double getCpuUsage() const { return m_cpuUsage; }
    MemoryInfo getMemoryInfo() const { return m_memoryInfo; }
    QVector<DiskInfo> getDiskInfo() const { return m_diskInfo; }
    NetworkStats getNetworkStats() const { return m_networkStats; }
    QVector<ProcessInfo> getTopProcesses(int count = 10) const;

signals:
    void dataUpdated();
    void cpuUsageChanged(double usage);
    void memoryUsageChanged(qint64 used, qint64 total);
    void networkActivityChanged(double downloadKBps, double uploadKBps);

private slots:
    void updateData();

private:
    QTimer *m_updateTimer;

    // Cached Data
    double m_cpuUsage;
    MemoryInfo m_memoryInfo;
    QVector<DiskInfo> m_diskInfo;
    NetworkStats m_networkStats;
    QVector<ProcessInfo> m_processes;

    // For network speed calculation
    qint64 m_lastRxBytes;
    qint64 m_lastTxBytes;
    qint64 m_lastUpdateTime;
};

#endif // SYSTEMMONITOR_H
