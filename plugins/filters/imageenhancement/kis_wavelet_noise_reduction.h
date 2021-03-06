/*
 * This file is part of the KDE project
 *
 * Copyright (c) 2005 Cyrille Berger <cberger@cberger.net>
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 */

#ifndef KIS_WAVELET_NOISE_REDUCTION_H
#define KIS_WAVELET_NOISE_REDUCTION_H

#include <vector>

#include <filter/kis_filter.h>

#define BEST_WAVELET_THRESHOLD_VALUE 7.0

/**
@author Cyrille Berger
*/
class KisWaveletNoiseReduction : public KisFilter
{
public:
    KisWaveletNoiseReduction();

    ~KisWaveletNoiseReduction();

public:

    void processImpl(KisPaintDeviceSP device,
                     const QRect& applyRect,
                     const KisFilterConfigurationSP config,
                     KoUpdater* progressUpdater
                     ) const;
    virtual KisConfigWidget * createConfigurationWidget(QWidget* parent, const KisPaintDeviceSP dev) const;

    static inline KoID id() {
        return KoID("waveletnoisereducer", i18n("Wavelet Noise Reducer"));
    }

private:
    virtual KisFilterConfigurationSP  factoryConfiguration() const;

};

#endif
