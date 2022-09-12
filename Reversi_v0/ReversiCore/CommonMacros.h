#pragma once
#include <QDebug>

#if defined(DEBUG) || !defined(NDEBUG)
#	define LOG(MESSAGE) qDebug() << MESSAGE;
#else
#	define LOG(MESSAGE)
#endif

