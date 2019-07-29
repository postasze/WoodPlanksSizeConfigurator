#include <QApplication>
#include <QLabel>
#include <QSurfaceFormat>

#ifndef QT_NO_OPENGL
#include "constants.h"
#include "deskakarbon.h"
#include "deskaretro.h"
#include "deskamodern.h"
#include "eurodeskaretro.h"
#include "eurodeskamodern.h"
#include "bevelkarbon.h"
#include "bevelretro.h"
#include "bevelmodern.h"
#include "channelkarbon.h"
#include "channelretro.h"
#include "channelmodern.h"
#include "emptyprofilekarbon.h"
#include "emptyprofileretro.h"
#include "emptyprofilemodern.h"
#endif

Object3D currentObject3D;
WoodType currentWoodType;
bool euroPlank;

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QSurfaceFormat format;
    format.setDepthBufferSize(24);
    QSurfaceFormat::setDefaultFormat(format);

    app.setApplicationVersion("0.1");
#ifndef QT_NO_OPENGL

    DeskaKarbon *deskaKarbonWindow;
    DeskaRetro *deskaRetroWindow;
    DeskaModern *deskaModernWindow;
    EuroDeskaRetro *euroDeskaRetroWindow;
    EuroDeskaModern *euroDeskaModernWindow;
    BevelKarbon *bevelKarbonWindow;
    BevelRetro *bevelRetroWindow;
    BevelModern *bevelModernWindow;
    ChannelKarbon *channelKarbonWindow;
    ChannelRetro *channelRetroWindow;
    ChannelModern *channelModernWindow;
    EmptyProfileKarbon *emptyProfileKarbonWindow;
    EmptyProfileRetro *emptyProfileRetroWindow;
    EmptyProfileModern *emptyProfileModernWindow;

    currentObject3D = Channel;
    currentWoodType = Karbon;
    euroPlank = false;

    switch(currentObject3D)
    {
    case 0: // Plank - deska
        switch(currentWoodType)
        {
        case 0: // Karbon
            deskaKarbonWindow = new DeskaKarbon();
            deskaKarbonWindow->resize(deskaKarbonWindow->width(), deskaKarbonWindow->height());
            deskaKarbonWindow->show();
            break;
        case 1: // Retro
            if(euroPlank)
            {
                euroDeskaRetroWindow = new EuroDeskaRetro();
                euroDeskaRetroWindow->resize(euroDeskaRetroWindow->width(), euroDeskaRetroWindow->height());
                euroDeskaRetroWindow->show();
            }
            else
            {
                deskaRetroWindow = new DeskaRetro();
                deskaRetroWindow->resize(deskaRetroWindow->width(), deskaRetroWindow->height());
                deskaRetroWindow->show();
            }
            break;
        case 2: // Modern
            if(euroPlank)
            {
                euroDeskaModernWindow = new EuroDeskaModern();
                euroDeskaModernWindow->resize(euroDeskaModernWindow->width(), euroDeskaModernWindow->height());
                euroDeskaModernWindow->show();
            }
            else
            {
                deskaModernWindow = new DeskaModern();
                deskaModernWindow->resize(deskaModernWindow->width(), deskaModernWindow->height());
                deskaModernWindow->show();
            }
            break;
        }
        break;
    case 1: // Channel - ceownik
        switch(currentWoodType)
        {
        case 0: // Karbon
            channelKarbonWindow = new ChannelKarbon();
            channelKarbonWindow->resize(channelKarbonWindow->width(), channelKarbonWindow->height());
            channelKarbonWindow->show();
            break;
        case 1: // Retro
            channelRetroWindow = new ChannelRetro();
            channelRetroWindow->resize(channelRetroWindow->width(), channelRetroWindow->height());
            channelRetroWindow->show();
            break;
        case 2: // Modern
            channelModernWindow = new ChannelModern();
            channelModernWindow->resize(channelModernWindow->width(), channelModernWindow->height());
            channelModernWindow->show();
            break;
        }
        break;
    case 2: // FullProfile - profil pelny
        break;
    case 3: // EmptyProfile - profil przelotowy
        switch(currentWoodType)
        {
        case 0: // Karbon
            emptyProfileKarbonWindow = new EmptyProfileKarbon();
            emptyProfileKarbonWindow->resize(emptyProfileKarbonWindow->width(), emptyProfileKarbonWindow->height());
            emptyProfileKarbonWindow->show();
            break;
        case 1: // Retro
            emptyProfileRetroWindow = new EmptyProfileRetro();
            emptyProfileRetroWindow->resize(emptyProfileRetroWindow->width(), emptyProfileRetroWindow->height());
            emptyProfileRetroWindow->show();
            break;
        case 2: // Modern
            emptyProfileModernWindow = new EmptyProfileModern();
            emptyProfileModernWindow->resize(emptyProfileModernWindow->width(), emptyProfileModernWindow->height());
            emptyProfileModernWindow->show();
            break;
        }
        break;
    case 4: // Bevel - katownik
        switch(currentWoodType)
        {
        case 0: // Karbon
            bevelKarbonWindow = new BevelKarbon();
            bevelKarbonWindow->resize(bevelKarbonWindow->width(), bevelKarbonWindow->height());
            bevelKarbonWindow->show();
            break;
        case 1: // Retro
            bevelRetroWindow = new BevelRetro();
            bevelRetroWindow->resize(bevelRetroWindow->width(), bevelRetroWindow->height());
            bevelRetroWindow->show();
            break;
        case 2: // Modern
            bevelModernWindow = new BevelModern();
            bevelModernWindow->resize(bevelModernWindow->width(), bevelModernWindow->height());
            bevelModernWindow->show();
            break;
        }
        break;
    }

#else
    QLabel note("OpenGL Support required");
    note.show();
#endif
    return app.exec();
}
