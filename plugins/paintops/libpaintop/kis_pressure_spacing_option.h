/* This file is part of the KDE project
 * Copyright (c) 2011 Cyrille Berger <cberger@cberger.net>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public License
 * along with this library; see the file COPYING.LIB.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 */

#ifndef KIS_PRESSURE_SPACING_OPTION_H
#define KIS_PRESSURE_SPACING_OPTION_H

#include "kis_curve_option.h"
#include <brushengine/kis_paint_information.h>
#include <kritapaintop_export.h>

/**
 * The pressure spacing option defines a curve that is used to
 * calculate the effect of pressure on the spacing of the dab
 */
class PAINTOP_EXPORT KisPressureSpacingOption : public KisCurveOption
{
public:
    KisPressureSpacingOption();
    double apply(const KisPaintInformation & info) const;

    void setIsotropicSpacing(bool isotropic);
    bool isotropicSpacing() const;

    void readOptionSetting(const KisPropertiesConfigurationSP setting);
    void writeOptionSetting(KisPropertiesConfigurationSP setting) const;

private:
    bool m_isotropicSpacing;
};

#endif
