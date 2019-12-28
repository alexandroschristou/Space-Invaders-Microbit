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
int gameLoop = 1;

typedef struct position
{
    uint8_t x;
    uint8_t y;

} Position;

typedef struct node
{
    Position *val;
    struct node *next;
} Node;

typedef struct enemy
{
    uint8_t type;
    uint8_t hitpoints;
    uint8_t speed;
    uint8_t size;
    Position *val;
} Enemy;

uint8_t randomY()
{
    return rand() % 5;
}

Node *makeNode(Position *bullet,Node *next)
{
    Node *head = (Node *)malloc(sizeof(Node));
    if (head == NULL)
    {
        exit(1);
    }

    head->val = bullet;
    head->next = next;
    return head;
}

Node *bulletList;
Enemy *enemyArray[11] = {NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL};
Position player = {0, 2};

Node *append(Node *head, Position *data)
{
    if (head == NULL)
    {
        bulletList = makeNode(data, NULL);
        return NULL;
    }
    /* go to the last node */
    Node *cursor = head;
    while (cursor->next != NULL)
        cursor = cursor->next;

    /* create a new node */
    Node *new_node = makeNode(data, NULL);
    cursor->next = new_node;

    return head;
}

Node *remove_front(node *head)
{
    if (head == NULL)
        return NULL;
    Node *front = head;
    head = head->next;
    front->next = NULL;
    /* is this the last node in the list */
    if (front == head)
        head = NULL;
    free(front->val);
    free(front);
    return head;
}

Node *remove_back(Node *head)
{
    if (head == NULL)
        return NULL;

    Node *cursor = head;
    Node *back = NULL;
    while (cursor->next != NULL)
    {
        back = cursor;
        cursor = cursor->next;
    }
    if (back != NULL)
        back->next = NULL;

    /* if this is the last node in the list*/
    if (cursor == head)
        head = NULL;
    free(cursor->val);
    free(cursor);

    return head;
}

Node *remove_any(Node *head, Node *nd)
{
    /* if the node is the first node */
    if (nd == head)
    {
        bulletList = remove_front(head);
        return head;
    }

    /* if the node is the last node */
    if (nd->next == NULL)
    {
        bulletList = remove_back(head);
        return head;
    }

    /* if the node is in the middle */
    Node *cursor = head;
    while (cursor != NULL)
    {
        if (cursor->next = nd)
            break;
        cursor = cursor->next;
    }

    if (cursor != NULL)
    {
        Node *tmp = cursor->next;
        cursor->next = tmp->next;
        tmp->next = NULL;
        free(tmp->val);
        free(tmp);
    }
    return head;
}

void updateBulletlist()
{
    Node *currNode;
    Position *currBullet;

    currNode = bulletList;
    while (currNode != NULL)
    {
        currBullet = currNode->val;

        if (currBullet->x < 5)
        {
            currBullet->x++;
            uBit.display.image.setPixelValue(currBullet->x, currBullet->y, 255);
        }
        else if (currBullet->x == 5)
        {
            remove_any(bulletList, currNode); //freeing bullet from make bullet when position is out of bounds
        }
        currNode = currNode->next;
    }
}

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

void makeBullet(MicroBitEvent e)
{
    Position *bullet;
    bullet = (Position *)malloc(sizeof(Position));
    if (bullet == NULL)
    {
        printf("malloc failed");
        exit(1);
    }

    // Set size and return.
    bullet->x = player.x;
    bullet->y = player.y;
    append(bulletList, bullet);
}

Enemy* makeEasyEnemy()
{
    Enemy *easyEnemy;
    easyEnemy = (Enemy *)malloc(sizeof(Enemy));
    if (easyEnemy == NULL)
    {
        printf("malloc failed");
        exit(1);
    }
    Position *enemyPos;
    enemyPos = (Position *)malloc(sizeof(Position));
    easyEnemy->val = enemyPos;
    easyEnemy->val->x = 4;
    easyEnemy->val->y = 4;
    easyEnemy->val->y = randomY();
    easyEnemy->hitpoints = 10;
    easyEnemy->type = 1;
    easyEnemy->speed = 4;
    easyEnemy->size = 1;
    return easyEnemy;
}
Enemy* makeTier2Enemy()
{
    Enemy *tier2Enemy;
    tier2Enemy = (Enemy *)malloc(sizeof(Enemy));
    if (tier2Enemy == NULL)
    {
        printf("malloc failed");
        exit(1);
    }
    Position *enemyPos;
    enemyPos = (Position *)malloc(sizeof(Position));
    tier2Enemy->val = enemyPos;
    tier2Enemy->val->x = 4;
    tier2Enemy->val->y = randomY();
    tier2Enemy->hitpoints = 15;
    tier2Enemy->type = 2;
    tier2Enemy->speed = 3;
    tier2Enemy->size = 2;
    return tier2Enemy;
}
Enemy* makeTier3Enemy()
{
    Enemy *tier3Enemy;
    tier3Enemy = (Enemy *)malloc(sizeof(Enemy));
    if (tier3Enemy == NULL)
    {
        printf("malloc failed");
        exit(1);
    }
    Position *enemyPos;
    enemyPos = (Position *)malloc(sizeof(Position));
    tier3Enemy->val = enemyPos;
    tier3Enemy->val->x = 4;
    tier3Enemy->val->y = randomY();
    tier3Enemy->hitpoints = 20;
    tier3Enemy->type = 3;
    tier3Enemy->speed = 2;
    tier3Enemy->size = 3;
    return tier3Enemy;
}
Enemy* makeBoss()
{
    Enemy *boss;
    boss = (Enemy *)malloc(sizeof(Enemy));
    if (boss == NULL)
    {
        printf("malloc failed");
        exit(1);
    }
    Position *enemyPos;
    enemyPos = (Position *)malloc(sizeof(Position));
    boss->val = enemyPos;
    boss->val->x = 4;
    boss->val->y = randomY();
    boss->hitpoints = 40;
    boss->type = 4;
    boss->speed = 1;
    boss->size = 4;
    return boss;
}
void makeEnemies()
{
    //enemyArray = (Enemy *)malloc(sizeof(Enemy *) * 11);

    for (int i = 0; i < 11; i++)
    {   
        if(i < 4){
            enemyArray[i] = makeEasyEnemy();
        }
        else if(i > 3 && i < 7) {
            enemyArray[i] = makeTier2Enemy();
        }
        else if(i > 6 && i < 10){
            enemyArray[i] = makeTier3Enemy();
        }
        else if(i == 10){
            enemyArray[i] = makeBoss();
        }
        else printf("error making enemies");
    }
}


void spaceInvaders()
{

    uBit.messageBus.listen(MICROBIT_ID_BUTTON_A, MICROBIT_BUTTON_EVT_CLICK, incPlayerY);
    uBit.messageBus.listen(MICROBIT_ID_BUTTON_B, MICROBIT_BUTTON_EVT_CLICK, decPlayerY);
    uBit.messageBus.listen(MICROBIT_ID_BUTTON_AB, MICROBIT_BUTTON_EVT_CLICK, makeBullet);
    uBit.messageBus.listen(MICROBIT_ID_BUTTON_A, MICROBIT_BUTTON_EVT_LONG_CLICK, save);
    uBit.messageBus.listen(MICROBIT_ID_BUTTON_B, MICROBIT_BUTTON_EVT_LONG_CLICK, load);
    makeEnemies();
    while (gameLoop)
    {
        uBit.display.clear();
        uBit.display.image.setPixelValue(player.x, player.y, 5);
        uBit.display.image.setPixelValue(enemyArray[2]->val->x,enemyArray[2]->val->y, 255);
        updateBulletlist();
        uBit.sleep(250);
    }
}
int main()
{
    srand(time(NULL));
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
