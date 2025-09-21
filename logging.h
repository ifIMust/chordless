#pragma once

#include <QLoggingCategory>
#include <QString>
#include <string>
#include <sstream>

// Declare logging categories for different subsystems
Q_DECLARE_LOGGING_CATEGORY(alsaCategory)
Q_DECLARE_LOGGING_CATEGORY(chordCategory)
Q_DECLARE_LOGGING_CATEGORY(configCategory)
Q_DECLARE_LOGGING_CATEGORY(generalCategory)

// Helper to convert various types to QString
template<typename... Args>
inline QString logFormat(Args... args) {
    std::ostringstream oss;
    ((oss << args), ...);
    return QString::fromStdString(oss.str());
}

// Better logging macros that handle std::string and other types
#define LOG_INFO(category, ...) qCInfo(category) << logFormat(__VA_ARGS__)
#define LOG_WARNING(category, ...) qCWarning(category) << logFormat(__VA_ARGS__)
#define LOG_ERROR(category, ...) qCCritical(category) << logFormat(__VA_ARGS__)
#define LOG_DEBUG(category, ...) qCDebug(category) << logFormat(__VA_ARGS__)