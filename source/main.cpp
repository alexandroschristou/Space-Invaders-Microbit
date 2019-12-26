/*
The MIT License (MIT)

Copyright (c) 2016 British Broadcasting Corporation.
This software is provided by Lancaster University by arrangement with the BBC.

Permission is hereby granted, free of charge, to any person obtaining a
copy of this software and associated documentation files (the "Software"),
to deal in the Software without restriction, including without limitation
the rights to use, copy, modify, merge, publish, distribute, sublicense,
and/or sell copies of the Software, and to permit persons to whom the
Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
DEALINGS IN THE SOFTWARE.
*/

#include "MicroBit.h"
#include <stdlib.h>
void load(MicroBitEvent e);
void save(MicroBitEvent e);

MicroBit uBit;

struct Position
{
    uint8_t x;
    uint8_t y;
};

struct Position player = {0, 2};
int gameLoop = 1;

struct Position playerBullets[5];
int bulletPtr = 0;




void decPlayerY(MicroBitEvent e)
{
    if (player.y < 4)
    {
        player.y++;
    }
}
void incPlayerY(MicroBitEvent e)
{
    if (player.y > 0)
    {
        player.y--;
    }
}





void spaceInvaders()
{
    player.x = 0;
    player.y = 2;

    uBit.messageBus.listen(MICROBIT_ID_BUTTON_A, MICROBIT_BUTTON_EVT_CLICK, incPlayerY);
    uBit.messageBus.listen(MICROBIT_ID_BUTTON_B, MICROBIT_BUTTON_EVT_CLICK, decPlayerY);
    //uBit.messageBus.listen(MICROBIT_ID_BUTTON_AB, MICROBIT_BUTTON_EVT_CLICK, makeBullet);
    uBit.messageBus.listen(MICROBIT_ID_BUTTON_A, MICROBIT_BUTTON_EVT_LONG_CLICK, save);
    uBit.messageBus.listen(MICROBIT_ID_BUTTON_B, MICROBIT_BUTTON_EVT_LONG_CLICK, load);

    //create_fiber(updateBullets);

    while (gameLoop)
    {
        uBit.display.clear();
        uBit.display.image.setPixelValue(player.x, player.y, 255);
        //updateBullets();
        uBit.sleep(250);
    }
}
int main()
{
    uBit.init();
    //uBit.display.scroll("INVADERS!");
    while (1)
    {
        spaceInvaders();
    }
    release_fiber();
}

void save(MicroBitEvent e)
{
    int save_data_size = 2 * sizeof(uint8_t);
    uint8_t *save_data = (uint8_t *)malloc(save_data_size);
    save_data[0] = player.x;
    save_data[1] = player.y;
    int result = uBit.storage.put("save", save_data, save_data_size);
    switch (result)
    {
    case MICROBIT_OK:
        break;
    case MICROBIT_INVALID_PARAMETER:
        uBit.display.scroll("MICROBIT_INVALID_PARAMETER");
        break;
    case MICROBIT_NO_RESOURCES:
        uBit.display.scroll("MICROBIT_NO_RESOURCES");
        break;
    }
    free(save_data);
}

void load(MicroBitEvent e)
{
    KeyValuePair *loaded = uBit.storage.get("save");
    if (loaded != NULL)
    {
        uint8_t *save_data = loaded->value;
        player.x = save_data[0];
        player.y = save_data[1];
    }
    delete loaded;
}
