/*
 * Copyright (c) 2009,2010 Lukáš Tvrdý (lukast.dev@gmail.com)
 *
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

#ifndef KIS_GRID_SHAPE_OPTION_H
#define KIS_GRID_SHAPE_OPTION_H

#include <kis_paintop_option.h>

const QString GRIDSHAPE_SHAPE = "GridShape/shape";

class KisShapeOptionsWidget;

class KisGridShapeOption : public KisPaintOpOption
{
public:
    KisGridShapeOption();
    ~KisGridShapeOption();

    /// Ellipse, rectangle, line, pixel, anti-aliased pixel
    int shape() const;

    void writeOptionSetting(KisPropertiesConfigurationSP setting) const;
    void readOptionSetting(const KisPropertiesConfigurationSP setting);
private:
    KisShapeOptionsWidget * m_options;
};

#endif // KIS_GRID_SHAPE_OPTION_H

