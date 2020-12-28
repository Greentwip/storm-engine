//============================================================================================
//	Spirenkov Maxim, 2005
//--------------------------------------------------------------------------------------------
//
//--------------------------------------------------------------------------------------------
//	WdmWindUI
//--------------------------------------------------------------------------------------------
//
//============================================================================================

#include "WdmWindUI.h"
#include "WdmPlayerShip.h"
#include "WorldMap.h"

//============================================================================================
//Конструирование, деструктурирование
//============================================================================================

WdmWindUI::WdmWindUI()
{
    strcpy(month[0], "january");
    strcpy(month[1], "february");
    strcpy(month[2], "march");
    strcpy(month[3], "april");
    strcpy(month[4], "may");
    strcpy(month[5], "june");
    strcpy(month[6], "july");
    strcpy(month[7], "august");
    strcpy(month[8], "september");
    strcpy(month[9], "october");
    strcpy(month[10], "november");
    strcpy(month[11], "december");
    txBack = wdmObjects->rs->TextureCreate("WorldMap\\Interfaces\\back.tga");
    txSky = wdmObjects->rs->TextureCreate("WorldMap\\Interfaces\\sky.tga");
    txSkyMask = wdmObjects->rs->TextureCreate("WorldMap\\Interfaces\\sky_mask.tga");
    txBar = wdmObjects->rs->TextureCreate("WorldMap\\Interfaces\\bar.tga");
    txBarMask = wdmObjects->rs->TextureCreate("WorldMap\\Interfaces\\bar_mask.tga");
    txWindPointer = wdmObjects->rs->TextureCreate("WorldMap\\Interfaces\\wind_pointer.tga");
    txMorale = wdmObjects->rs->TextureCreate("WorldMap\\Interfaces\\morale.tga");
    txMoraleMask = wdmObjects->rs->TextureCreate("WorldMap\\Interfaces\\morale_mask.tga");
    txMoraleBar = wdmObjects->rs->TextureCreate("WorldMap\\Interfaces\\morale_bar.tga");
    txCoord = wdmObjects->rs->TextureCreate("WorldMap\\Interfaces\\coord.tga");
    txNationFlag = wdmObjects->rs->TextureCreate("WorldMap\\Interfaces\\WorldMapEnsigns.tga");
    dateFont = -1;
    morale = 0.0f;
    food = 0;
    rum = 0;
    resizeRatio = 1.0f;
}

WdmWindUI::~WdmWindUI()
{
    if (txBack >= 0)
        wdmObjects->rs->TextureRelease(txBack);
    if (txSky >= 0)
        wdmObjects->rs->TextureRelease(txSky);
    if (txSkyMask >= 0)
        wdmObjects->rs->TextureRelease(txSkyMask);
    if (txBar >= 0)
        wdmObjects->rs->TextureRelease(txBar);
    if (txBarMask >= 0)
        wdmObjects->rs->TextureRelease(txBarMask);
    if (txWindPointer >= 0)
        wdmObjects->rs->TextureRelease(txWindPointer);
    if (txMorale >= 0)
        wdmObjects->rs->TextureRelease(txMorale);
    if (txMoraleMask >= 0)
        wdmObjects->rs->TextureRelease(txMoraleMask);
    if (txMoraleBar >= 0)
        wdmObjects->rs->TextureRelease(txMoraleBar);
    if (txCoord >= 0)
        wdmObjects->rs->TextureRelease(txCoord);
    if (txNationFlag >= 0)
        wdmObjects->rs->TextureRelease(txNationFlag);
}

//============================================================================================

//============================================================================================

//Считать имя фонта
void WdmWindUI::SetAttributes(ATTRIBUTES *apnt)
{
    if (!apnt)
        return;
    ATTRIBUTES *ap = apnt->FindAClass(apnt, "date");
    if (ap)
    {
        // Font
        char *s = ap->GetAttribute("font");
        if (s && s[0])
            dateFont = wdmObjects->wm->GetRS()->LoadFont(s);
        strcpy(wdmObjects->stCoordinate, ap->GetAttribute("coordinate"));
        ATTRIBUTES *a = ap->FindAClass(ap, "monthnames");
        if (a)
        {
            char buf[4];
            buf[0] = 'm';
            buf[3] = 0;
            for (long i = 1; i <= 12; i++)
            {
                if (i < 10)
                    buf[1] = '0';
                else
                    buf[1] = '1';
                buf[2] = char('0' + (i % 10));
                s = a->GetAttribute(buf);
                if (s && s[0])
                {
                    long sl = strlen(s) + 1;
                    if (sl > 128)
                        sl = 128;
                    memcpy(month[i - 1], s, sl);
                    month[i - 1][127] = 0;
                }
            }
        }
    }
}

//Отрисовка
void WdmWindUI::LRender(VDX8RENDER *rs)
{
    VDATA *data;
    if (wdmObjects->isNextDayUpdate)
    {
        data = api->Event("WorldMap_GetMoral");
        if (data)
        {
            morale = data->GetFloat() * 0.02f - 1.0f;
        }
        data = api->Event("WorldMap_GetFood");
        if (data)
        {
            food = long(data->GetFloat() + 0.5f);
        }
        data = api->Event("WorldMap_GetRum");
        if (data)
        {
            rum = long(data->GetFloat() + 0.5f);
        }
        if (morale < -1.0f)
            morale = -1.0f;
        if (morale > 1.0f)
            morale = 1.0f;
        if (food < 0)
            food = 0;
        if (food > 1000000000)
            food = 1000000000;
        if (rum < 0)
            rum = 0;
        if (rum > 1000000000)
            rum = 1000000000;
    }
    //Параметры ветра у игрока
    float x, y, ay;
    wdmObjects->playerShip->GetPosition(x, y, ay);
    CVECTOR windDir;
    resizeRatio = wdmObjects->resizeRatio;
    float widForce = wdmObjects->GetWind(x, y, windDir);
    float ang = (float)atan2(windDir.x, windDir.z);
    //Параметры экрана
    float w, h;
    wdmObjects->GetVPSize(w, h);
    float kDef = rs->GetHeightDeformator();
    //Центр штуки
    // float cx = (w - 128.0f - 16.0f) + 64.0f;
    float cx = w - (128.0f) * resizeRatio - 16.0f + 64.0f;
    // float cy = (-40.0f) + 128.0f;
    float cy = -40.0f + 128.0f * resizeRatio;
    //Буфер для рисования плашек
    Vertex buf[(3 * 2) * 2];
    //Небо
    rs->TextureSet(0, txSky);
    rs->TextureSet(1, txSkyMask);

    // FillRectCoord(buf, cx - 64.0f, cy - 64.0f, 128.0f, 128.0f);
    FillRectCoord(buf, cx - (64.0f * resizeRatio), cy - (64.0f * resizeRatio), 128.0f * resizeRatio,
                  128.0f * resizeRatio);

    FillRectUV(buf, (wdmObjects->wm->hour * (1.0f / 24.0f) - 0.125f), 0.0f, 0.25f, 1.0f);
    FillRectUV1(buf, 0.0f, 0.0f, 1.0f, 1.0f);
    FillRectColor(buf, 0x80ffffff);
    DrawRects(buf, 1, "WdmInterfaceDrawSky");
    //Направление ветра
    rs->TextureSet(0, txWindPointer);

    // FillRectCoord(buf, cx - 16.0f, cy - 64.0f, 32.0f, 128.0f, ang);
    FillRectCoord(buf, cx - (16.0f * resizeRatio), cy - (64.0f * resizeRatio), 32.0f * resizeRatio,
                  128.0f * resizeRatio, ang);

    FillRectUV(buf, 0.0f, 0.0f, 1.0f, 1.0f);
    FillRectColor(buf, 0xffffffff);
    DrawRects(buf, 1, "WdmDrawMapBlend");
    //Сила ветра
    rs->TextureSet(0, txBar);
    rs->TextureSet(1, txBarMask);

    // FillRectCoord(buf, cx - 64.0f, cy, 128.0f, 128.0f);
    FillRectCoord(buf, cx - (64.0f * resizeRatio), cy, 128.0f * resizeRatio, 128.0f * resizeRatio);

    FillRectUV(buf, 0.0f, 0.0f, 1.0f, 1.0f);
    FillRectUV1(buf, -0.5f, 0.0f, 1.0f, 1.0f);
    CMatrix rot(0.0f, 1.8f * (1.0f - widForce), 0.0f, 0.5f, 0.0f, 0.0f);
    for (long i = 0; i < 6; i++)
    {
        CVECTOR v(buf[i].tu1, 0.0f, buf[i].tv1);
        CVECTOR vrot = rot * v;
        buf[i].tu1 = vrot.x;
        buf[i].tv1 = vrot.z;
    }
    FillRectColor(buf, 0xffffffff);
    DrawRects(buf, 1, "WdmInterfaceDrawSky");
    //Рамка
    rs->TextureSet(0, txBack);

    // FillRectCoord(buf, cx - 64.0f, cy - 128.0f, 128.0f, 256.0f);
    FillRectCoord(buf, cx - 64.0f * resizeRatio, cy - 128.0f * resizeRatio, 128.0f * resizeRatio, 256.0f * resizeRatio);

    FillRectUV(buf, 0.0f, 0.0f, 1.0f, 1.0f);
    FillRectColor(buf, 0xffffffff);
    DrawRects(buf, 1, "WdmDrawMapBlend");
    //Пишем дату
    char tbuf[128];
    _snprintf(tbuf, sizeof(tbuf) - 1, "%i %s %i", wdmObjects->wm->day, month[wdmObjects->wm->mon - 1],
              wdmObjects->wm->year);
    tbuf[sizeof(tbuf) - 1] = 0;
    long font = dateFont >= 0 ? dateFont : FONT_DEFAULT;
    long fw = rs->StringWidth(tbuf, font);
    long fh = rs->CharHeight(font);

    // rs->Print(font, 0xffffffff, long(cx - fw*0.5f), long(cy + 98.0f - fh*0.5f), tbuf);
    rs->ExtPrint(font, 0xffffffff, 0x00000000, ALIGN_CENTER, 0, resizeRatio, 0, 0, long(cx),
                 long(cy + (98.0f - fh * 0.5f) * resizeRatio), tbuf);

    //Центр
    // cy += 128.0f + 32.0f;
    cy += 128.0f * resizeRatio + 32.0f;
    //Рисуем моральную бару
    rs->TextureSet(0, txMoraleBar);
    rs->TextureSet(1, txMoraleMask);

    // FillRectCoord(buf, cx - 64.0f, cy - 32.0f, 128.0f, 64.0f);
    FillRectCoord(buf, cx - 64.0f * resizeRatio, cy - 32.0f * resizeRatio, 128.0f * resizeRatio, 64.0f * resizeRatio);

    FillRectUV(buf, morale * 0.28f, 0.0f, 1.0f, 1.0f);
    FillRectUV1(buf, 0.0f, 0.0f, 1.0f, 1.0f);
    FillRectColor(buf, 0xffffffff);
    DrawRects(buf, 1, "WdmInterfaceDrawSky");
    //Рисуем моральную плашку
    rs->TextureSet(0, txMorale);

    // FillRectCoord(buf, cx - 64.0f, cy - 32.0f, 128.0f, 64.0f);
    FillRectCoord(buf, cx - 64.0f * resizeRatio, cy - 32.0f * resizeRatio, 128.0f * resizeRatio, 64.0f * resizeRatio);

    FillRectUV(buf, 0.0f, 0.0f, 1.0f, 1.0f);
    FillRectColor(buf, 0xffffffff);
    DrawRects(buf, 1, "WdmDrawMapBlend");
    //Пишем количество припасов
    _snprintf(tbuf, sizeof(tbuf) - 1, "%i", food);
    tbuf[sizeof(tbuf) - 1] = 0;
    fw = rs->StringWidth(tbuf, font, resizeRatio, w);

    // rs->Print(font, 0xffffffff, long(cx - 24.0f - fw*0.5f), long(cy + 30.0f), tbuf);
    rs->ExtPrint(font, 0xffffffff, 0x00000000, ALIGN_CENTER, 0, resizeRatio, 0, 0, long(cx - 24.0f * resizeRatio),
                 long(cy + 30.0f * resizeRatio), tbuf);

    //Пишем количество рома --> ugeen 29.10.10
    _snprintf(tbuf, sizeof(tbuf) - 1, "%i", rum);
    tbuf[sizeof(tbuf) - 1] = 0;
    fw = rs->StringWidth(tbuf, font, resizeRatio, w);

    // rs->Print(font, 0xffffffff, long(cx + 24.0f - fw*0.5f), long(cy + 30.0f), tbuf);
    rs->ExtPrint(font, 0xffffffff, 0x00000000, ALIGN_CENTER, 0, resizeRatio, 0, 0, long(cx + 24.0f * resizeRatio),
                 long(cy + 30.0f * resizeRatio), tbuf);

    //Рамка с координатами
    rs->TextureSet(0, txCoord);

    // FillRectCoord(buf, cx - 64.0f, cy + 64.0f, 128.0f, 64.0f);
    FillRectCoord(buf, cx - 64.0f * resizeRatio, cy + 64.0f * resizeRatio, 128.0f * resizeRatio, 64.0f * resizeRatio);

    FillRectUV(buf, 0.0f, 0.0f, 1.0f, 1.0f);
    FillRectColor(buf, 0xffffffff);
    DrawRects(buf, 1, "WdmDrawMapBlend");

    // выводим строку с координатами
    _snprintf(tbuf, sizeof(tbuf) - 1, "%s", wdmObjects->coordinate);
    tbuf[sizeof(tbuf) - 1] = 0;
    fw = rs->StringWidth(tbuf, font, resizeRatio, w);
    fh = rs->CharHeight(font);

    // rs->Print(font, 0xffffffff, long(cx - fw*0.5f), long(cy + 64.0f + 44.0f- fh*0.5f), tbuf);
    rs->ExtPrint(font, 0xffffffff, 0x00000000, ALIGN_CENTER, 0, resizeRatio, 0, 0, long(cx),
                 long(cy + (64.0f + 32.0f) * resizeRatio), tbuf);

    _snprintf(tbuf, sizeof(tbuf) - 1, "%s", wdmObjects->stCoordinate);
    tbuf[sizeof(tbuf) - 1] = 0;
    fw = rs->StringWidth(tbuf, font, resizeRatio, w);
    fh = rs->CharHeight(font);

    // rs->Print(font, 0xffffffff, long(cx - fw*0.5f), long(cy + 64.0f + 20.0f- fh*0.5f), tbuf);
    rs->ExtPrint(font, 0xffffffff, 0x00000000, ALIGN_CENTER, 0, resizeRatio, 0, 0, long(cx),
                 long(cy + (64.0f + 13.0f) * resizeRatio), tbuf);

    // национальный флаг
    float addtu = 0.125;
    rs->TextureSet(0, txNationFlag);

    // FillRectCoord(buf, cx - 24.0f, cy + 150.0f, 48.0f, 48.0f);
    FillRectCoord(buf, cx - 24.0f * resizeRatio, cy + 150.0f * resizeRatio, 48.0f * resizeRatio, 48.0f * resizeRatio);

    FillRectUV(buf, wdmObjects->nationFlagIndex * addtu, 0.0f, addtu, 1.0f);
    FillRectColor(buf, 0xffffffff);
    DrawRects(buf, 1, "WdmDrawMapBlend");
    // <-- ugeen
}