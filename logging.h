#pragma once

#include <QLoggingCategory>

// Declare logging categories for different subsystems
Q_DECLARE_LOGGING_CATEGORY(alsaCategory)
Q_DECLARE_LOGGING_CATEGORY(chordCategory)
Q_DECLARE_LOGGING_CATEGORY(configCategory)
Q_DECLARE_LOGGING_CATEGORY(generalCategory)

// Convenience macros for common logging patterns
#define LOG_INFO(category, msg) qCInfo(category) << msg
#define LOG_WARNING(category, msg) qCWarning(category) << msg
#define LOG_ERROR(category, msg) qCCritical(category) << msg
#define LOG_DEBUG(category, msg) qCDebug(category) << msg