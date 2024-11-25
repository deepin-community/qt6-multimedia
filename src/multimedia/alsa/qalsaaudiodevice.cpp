// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR LGPL-3.0-only OR GPL-2.0-only OR GPL-3.0-only

//
//  W A R N I N G
//  -------------
//
// This file is not part of the Qt API.  It exists for the convenience
// of other Qt classes.  This header file may change from version to
// version without notice, or even be removed.
//
// INTERNAL USE ONLY: Do NOT use for any other purpose.
//

#include "qalsaaudiodevice_p.h"

#include <alsa/version.h>

QT_BEGIN_NAMESPACE

QAlsaAudioDeviceInfo::QAlsaAudioDeviceInfo(const QByteArray &dev, const QString &desc, QAudioDevice::Mode mode)
    : QAudioDevicePrivate(dev, mode)
{
    description = desc;

    checkSurround();

    minimumChannelCount = 1;
    maximumChannelCount = 2;
    if (surround71)
        maximumChannelCount = 8;
    else if (surround40)
        maximumChannelCount = 4;
    else if (surround51)
        maximumChannelCount = 6;

    minimumSampleRate = 8000;
    maximumSampleRate = 48000;

    supportedSampleFormats = {
        QAudioFormat::UInt8,
        QAudioFormat::Int16,
        QAudioFormat::Int32,
        QAudioFormat::Float,
    };

    preferredFormat.setChannelCount(mode == QAudioDevice::Input ? 1 : 2);
    preferredFormat.setSampleFormat(QAudioFormat::Float);
    preferredFormat.setSampleRate(48000);
}

QAlsaAudioDeviceInfo::~QAlsaAudioDeviceInfo() = default;

void QAlsaAudioDeviceInfo::checkSurround()
{
    if (mode != QAudioDevice::Output)
        return;

    surround40 = false;
    surround51 = false;
    surround71 = false;

    if (id.startsWith(QLatin1String("surround40")))
        surround40 = true;
    if (id.startsWith(QLatin1String("surround51")))
        surround51 = true;
    if (id.startsWith(QLatin1String("surround71")))
        surround71 = true;
}

QT_END_NAMESPACE
