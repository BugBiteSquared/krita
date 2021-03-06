/*
 *  Copyright (c) 2007 Boudewijn Rempt boud@valdyas.org
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

#include "kis_fill_painter_test.h"

#include "testutil.h"

#include <QTest>
#include "kis_fill_painter.h"

#include <floodfill/kis_scanline_fill.h>

#define THRESHOLD 10

void KisFillPainterTest::testCreation()
{
    KisFillPainter test;
}

void KisFillPainterTest::benchmarkFillPainter(const QPoint &startPoint, bool useCompositioning)
{
    const KoColorSpace * cs = KoColorSpaceRegistry::instance()->rgb8();
    KisPaintDeviceSP dev = new KisPaintDevice(cs);

    QImage srcImage(TestUtil::fetchDataFileLazy("heavy_labyrinth.png"));
    QVERIFY(!srcImage.isNull());

    QRect imageRect = srcImage.rect();

    dev->convertFromQImage(srcImage, 0, 0, 0);


    QBENCHMARK_ONCE {
        KisFillPainter gc(dev);
        gc.setFillThreshold(THRESHOLD);
        gc.setWidth(imageRect.width());
        gc.setHeight(imageRect.height());
        gc.setPaintColor(KoColor(Qt::red, dev->colorSpace()));
        gc.setUseCompositioning(useCompositioning);
        gc.fillColor(startPoint.x(), startPoint.y(), dev);
    }

    QImage resultImage =
        dev->convertToQImage(0,
                             imageRect.x(), imageRect.y(),
                             imageRect.width(), imageRect.height());

    QString testName = QString("heavy_labyrinth_%1_%2_%3")
        .arg(startPoint.x())
        .arg(startPoint.y())
        .arg(useCompositioning ? "composed" : "direct");


    QVERIFY(TestUtil::checkQImage(resultImage,
                                  "fill_painter",
                                  "general_",
                                  testName));
}

void KisFillPainterTest::benchmarkFillPainter()
{
    benchmarkFillPainter(QPoint(), false);
}

void KisFillPainterTest::benchmarkFillPainterOffset()
{
    benchmarkFillPainter(QPoint(5,5), false);
}

void KisFillPainterTest::benchmarkFillPainterOffsetCompositioning()
{
    benchmarkFillPainter(QPoint(5,5), true);
}

void KisFillPainterTest::benchmarkFillingScanlineColor()
{
    const KoColorSpace * cs = KoColorSpaceRegistry::instance()->rgb8();
    KisPaintDeviceSP dev = new KisPaintDevice(cs);

    QImage srcImage(TestUtil::fetchDataFileLazy("heavy_labyrinth.png"));
    QVERIFY(!srcImage.isNull());

    QRect imageRect = srcImage.rect();

    dev->convertFromQImage(srcImage, 0, 0, 0);


    QBENCHMARK_ONCE {
        KisScanlineFill gc(dev, QPoint(), imageRect);
        gc.setThreshold(THRESHOLD);
        gc.fillColor(KoColor(Qt::red, dev->colorSpace()));
    }

    QImage resultImage =
        dev->convertToQImage(0,
                             imageRect.x(), imageRect.y(),
                             imageRect.width(), imageRect.height());

    QVERIFY(TestUtil::checkQImage(resultImage,
                                  "fill_painter",
                                  "scanline_",
                                  "heavy_labyrinth_top_left"));
}

void KisFillPainterTest::benchmarkFillingScanlineSelection()
{
    const KoColorSpace * cs = KoColorSpaceRegistry::instance()->rgb8();
    KisPaintDeviceSP dev = new KisPaintDevice(cs);

    QImage srcImage(TestUtil::fetchDataFileLazy("heavy_labyrinth.png"));
    QVERIFY(!srcImage.isNull());

    QRect imageRect = srcImage.rect();

    dev->convertFromQImage(srcImage, 0, 0, 0);


    KisPixelSelectionSP pixelSelection = new KisPixelSelection();

    QBENCHMARK_ONCE {
        KisScanlineFill gc(dev, QPoint(), imageRect);
        gc.setThreshold(THRESHOLD);
        gc.fillSelection(pixelSelection);
    }

    QImage resultImage =
        pixelSelection->convertToQImage(0,
                                        imageRect.x(), imageRect.y(),
                                        imageRect.width(), imageRect.height());

    QVERIFY(TestUtil::checkQImage(resultImage,
                                  "fill_painter",
                                  "scanline_",
                                  "heavy_labyrinth_top_left_selection"));
}


QTEST_MAIN(KisFillPainterTest)
