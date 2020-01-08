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
uint8_t gameLoop = 1;
uint8_t amountOfLives = 3;
int counter = 0;
uint8_t enemyCounter = 3;
uint8_t bossVar = 0;

typedef struct position
{
    uint8_t x;
    uint8_t y;

} Position;

typedef struct bullet
{
    uint8_t direction;
    Position *pos;
} Bullet;

typedef struct node
{
    Bullet *val;
    struct node *next;
} Node;

typedef struct enemy
{
    uint8_t type;
    uint8_t hitpoints;
    uint8_t speed;
    uint8_t size;
    Position *val;
    uint8_t state;
    uint8_t shoot;
    uint8_t score;
} Enemy;

typedef struct player
{
    uint8_t lives;
    Position pos;
    uint8_t score;
} Player;

int randomY()
{
    return uBit.random(5);
}
Node *bulletList;
Enemy *enemyArray[15] = {NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL};

Node *makeNode(Bullet *bullet, Node *next)
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

Position playerPos = {0, 2};
Player player = {amountOfLives, playerPos, 0};

Node *appendToList(Node *head, Bullet *data)
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

Node *deleteList()
{
    Node *head;
    head = bulletList;
    while (head != NULL)
    {
        free(head->val->pos);
        free(head->val);
        free(head);
        head = head->next;
    }
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
    free(front->val->pos);
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
    free(cursor->val->pos);
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
        free(tmp->val->pos);
        free(tmp->val);
        free(tmp);
    }
    return head;
}

void endGame()
{
    for (int i = 0; i < 15; i++)
    {
        if (enemyArray[i] != NULL)
        {
            free(enemyArray[i]->val);
            free(enemyArray[i]);
            enemyArray[i] = NULL;
        }
    }
    while (bulletList != NULL)
    {
        bulletList = deleteList();
    }
    uBit.display.scroll("U LOST!");
    //uBit.display.scroll(player.score);
    gameLoop = 0;
}

void updateBulletlist()
{
    if (counter % 2 == 0)
    {
        Node *currNode;
        Bullet *currBullet;

        currNode = bulletList;
        while (currNode != NULL)
        {
            currBullet = currNode->val;
            if (currBullet->direction == 0)
            {
                if (currBullet->pos->x < 5)
                {
                    currBullet->pos->x++;
                }
                else if (currBullet->pos->x == 5)
                {
                    remove_any(bulletList, currNode); //freeing bullet from make bullet when position is out of bounds
                }
                currNode = currNode->next;
            }
            else if (currBullet->direction == 1)
            {
                if (currBullet->pos->x > 0)
                {
                    currBullet->pos->x--;
                }
                else if (currBullet->pos->x == 0)
                {
                    remove_any(bulletList, currNode); //freeing bullet from make bullet when position is out of bounds
                }
                currNode = currNode->next;
            }
        }
    }
}

void deleteEnemy(Enemy *enemy)
{
    for (int i = 0; i < 15; i++)
    {
        if (enemyArray[i] == enemy)
        {
            free(enemyArray[i]->val);
            free(enemyArray[i]);
            enemyArray[i] = NULL;
        }
    }
}

void updateEnemies()
{
    for (int i = 0; i < 15; i++)
    {
        Enemy *currEnemy = enemyArray[i];
        if (currEnemy != NULL)
        {
            if (currEnemy->speed != 0)
            {
                if (counter % currEnemy->speed == 0)
                {
                    if (currEnemy->val->x > 0)
                    {
                        currEnemy->val->x--;
                    }
                    else
                    {
                        if (player.lives == 0)
                        {
                            endGame(); //end game if player has no more life
                            break;
                        }
                        else
                        {
                            player.lives--;
                            deleteEnemy(enemyArray[i]); //decrement lives and delete enemy
                        }
                    }
                }
            }
        }
    }
}

void decPlayerY(MicroBitEvent e)
{
    if (player.pos.y < 4)
    {
        player.pos.y++;
    }
}
void incPlayerY(MicroBitEvent e)
{
    if (player.pos.y > 0)
    {
        player.pos.y--;
    }
}

void makeBullet(MicroBitEvent e)
{
    Bullet *bullet;
    Position *bulletPos;
    bullet = (Bullet *)malloc(sizeof(Bullet));
    bulletPos = (Position *)malloc(sizeof(Position));
    if (bullet == NULL)
    {
        printf("malloc failed");
        exit(1);
    }

    // Set size and return.
    bullet->pos = bulletPos;
    bullet->pos->x = player.pos.x;
    bullet->pos->y = player.pos.y;
    bullet->direction = 0; //going from left to right
    appendToList(bulletList, bullet);
}

void makeEnemyBullet(uint8_t xPos, uint8_t yPos)
{

    Bullet *bullet;
    Position *bulletPos;
    bullet = (Bullet *)malloc(sizeof(Bullet));
    bulletPos = (Position *)malloc(sizeof(Position));
    if (bullet == NULL)
    {
        printf("malloc failed");
        exit(1);
    }

    // Set size and return.
    bullet->pos = bulletPos;
    bullet->pos->x = xPos;
    bullet->pos->y = yPos;
    bullet->direction = 1; //going from right to left
    appendToList(bulletList, bullet);
}

void incrScore(Enemy *enemy)
{
    player.score = player.score + enemy->score;
}

void decrementGhostPoints(Enemy *enemy)
{
    if (enemy->hitpoints > 0)
    {
        enemy->hitpoints = enemy->hitpoints - 5;
    }
    else
    {
        if (enemy->type == 3)
        {
            enemyCounter = 2; //if we beat the boss we initiliaze counter again back to 10
            bossVar = 0;
        }
        else
        {
            if (enemyCounter > 0)
                enemyCounter--; //if we kill normal enemy we decrement counter
        }
        incrScore(enemy);
        deleteEnemy(enemy);
    }
}

void checkCollisionBulletGhost()
{
    Node *currNode;
    currNode = bulletList;
    while (currNode != NULL)
    {
        if (currNode->val->direction == 0)
        {
            for (int i = 0; i < 15; i++)
            {
                if (enemyArray[i] != NULL)
                {
                    switch (enemyArray[i]->size)
                    {
                    case 1:
                        if (enemyArray[i]->val->x == currNode->val->pos->x && enemyArray[i]->val->y == currNode->val->pos->y)
                        {
                            decrementGhostPoints(enemyArray[i]);
                            remove_any(bulletList, currNode);
                        }
                        break;
                    case 2:
                        if (enemyArray[i]->val->x == currNode->val->pos->x && (currNode->val->pos->y == enemyArray[i]->val->y || currNode->val->pos->y == (enemyArray[i]->val->y + 1)))
                        {
                            decrementGhostPoints(enemyArray[i]);
                            remove_any(bulletList, currNode);
                        }
                        break;
                    case 3:
                        if (enemyArray[i]->val->x == currNode->val->pos->x)
                        {
                            if ((currNode->val->pos->y >= enemyArray[i]->val->y) && (currNode->val->pos->y <= (enemyArray[i]->val->y + 3 - 1)))
                            {
                                decrementGhostPoints(enemyArray[i]);
                                remove_any(bulletList, currNode);
                            }
                        }
                        break;
                    case 4:
                        if (enemyArray[i]->val->x == currNode->val->pos->x)
                        {
                            if ((currNode->val->pos->y >= enemyArray[i]->val->y) && (currNode->val->pos->y <= (enemyArray[i]->val->y + 4 - 1)))
                            {
                                decrementGhostPoints(enemyArray[i]);
                                remove_any(bulletList, currNode);
                            }
                        }
                        break;
                    }
                }
            }
        }
        currNode = currNode->next;
    }
}
void checkCollisionBulletPlayer()
{
    Node *currNode;
    currNode = bulletList;
    while (currNode != NULL)
    {
        if (currNode->val->direction == 1)
        {
            if (currNode->val->pos->x == player.pos.x && currNode->val->pos->y == player.pos.y)
            {
                if (player.lives == 0)
                {
                    endGame();
                    break;
                }
                else
                {
                    player.lives--;
                    remove_any(bulletList, currNode);
                }
            }
        }
        currNode = currNode->next;
    }
}

void checkCollisionBetweenBullets()
{
    Node *currNodePlayer;
    currNodePlayer = bulletList;
    Node *currNodeEnemy;
    currNodeEnemy = bulletList;

    while (currNodePlayer != NULL)
    {
        if (currNodePlayer->val->direction == 0)
        {
            while (currNodeEnemy != NULL)
            {
                if (currNodeEnemy->val->direction == 1 && currNodePlayer->val->pos->x == currNodeEnemy->val->pos->x && currNodePlayer->val->pos->y == currNodeEnemy->val->pos->y)
                {
                    remove_any(bulletList, currNodeEnemy);
                    remove_any(bulletList, currNodePlayer);
                }
                currNodeEnemy = currNodeEnemy->next;
            }
        }
        currNodePlayer = currNodePlayer->next;
    }
}

Enemy *makeEasyEnemy()
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
    easyEnemy->val->y = randomY();
    easyEnemy->hitpoints = 5;
    easyEnemy->type = 0;
    easyEnemy->speed = 10;
    easyEnemy->size = 1;
    easyEnemy->state = 1;
    easyEnemy->shoot = 20;
    easyEnemy->score = 1;
    return easyEnemy;
}
Enemy *makeTier2Enemy()
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
    tier2Enemy->hitpoints = 5;
    tier2Enemy->type = 1;
    tier2Enemy->speed = 15;
    tier2Enemy->size = 2;
    tier2Enemy->state = 1;
    tier2Enemy->shoot = 15;
    tier2Enemy->score = 2;
    return tier2Enemy;
}
Enemy *makeTier3Enemy()
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
    tier3Enemy->hitpoints = 15;
    tier3Enemy->type = 2;
    tier3Enemy->speed = 20;
    tier3Enemy->size = 3;
    tier3Enemy->state = 1;
    tier3Enemy->shoot = 10;
    tier3Enemy->score = 3;
    return tier3Enemy;
}
Enemy *makeBoss()
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
    boss->val->y = 1; //randomY();
    boss->hitpoints = 25;
    boss->type = 3;
    boss->speed = 0;
    boss->size = 4;
    boss->state = 1;
    boss->shoot = 5;
    boss->score = 4;
    return boss;
}

int emptyArray()
{
    int count;
    for (int i = 0; i < 15; i++)
    {
        if (enemyArray[i] == NULL)
            count++;
    }
    if (count == 15)
    {
        return 1;
    }
    else
        return 0;
}
uint8_t countCurrentEnemies()
{
    uint8_t amount;
    for (int i = 0; i < 15; i++)
    {
        if (enemyArray[i] != NULL)
            amount++;
    }
    return amount;
}
void makeEnemy()
{
    if (counter % 25 == 0)
    {
        int nextFree = 0;
        for (int i = 0; i < 15; i++)
        {
            if (enemyArray[i] == NULL) //we search in the array the first free position and break out the for loop when found
            {
                nextFree = i;
                break;
            }
        }
        if (nextFree < 15 && enemyCounter != 0)
        {
            int type = uBit.random(3);
            switch (type)
            {
            case 0:
                enemyArray[nextFree] = makeEasyEnemy();
                break;
            case 1:
                enemyArray[nextFree] = makeTier2Enemy();
                break;
            case 2:
                enemyArray[nextFree] = makeTier3Enemy();
                break;
            }
        }
        else if (enemyCounter == 0 && nextFree < 15 && bossVar == 0 && countCurrentEnemies() == 0)
        {
            if (counter % 100 == 0)
            {
                enemyArray[nextFree] = makeBoss();
                bossVar = 1;
            }
        }
    }
}
void drawField()
{
    Node *currNode;
    currNode = bulletList;
    uBit.display.clear();
    uBit.display.image.setPixelValue(player.pos.x, player.pos.y, 5);
    while (currNode != NULL)
    {
        uBit.display.image.setPixelValue(currNode->val->pos->x, currNode->val->pos->y, 255);
        currNode = currNode->next;
    }
    for (int i = 0; i < 15; i++)
    {
        if (enemyArray[i] != NULL)
        {
            for (int a = 0; a < enemyArray[i]->size; a++)
            {
                uBit.display.image.setPixelValue(enemyArray[i]->val->x, enemyArray[i]->val->y + a, 255);
            }
        }
    }
}
void shootEnemy()
{
    for (int i = 0; i < 15; i++)
    {
        if (enemyArray[i] != NULL)
        {
            if (counter % enemyArray[i]->shoot == 0)
            {
                makeEnemyBullet(enemyArray[i]->val->x, enemyArray[i]->val->y);
            }
        }
    }
}
void spaceInvaders()
{

    uBit.messageBus.listen(MICROBIT_ID_BUTTON_A, MICROBIT_BUTTON_EVT_CLICK, incPlayerY);
    uBit.messageBus.listen(MICROBIT_ID_BUTTON_B, MICROBIT_BUTTON_EVT_CLICK, decPlayerY);
    uBit.messageBus.listen(MICROBIT_ID_BUTTON_AB, MICROBIT_BUTTON_EVT_CLICK, makeBullet);
    uBit.messageBus.listen(MICROBIT_ID_BUTTON_A, MICROBIT_BUTTON_EVT_LONG_CLICK, save);
    uBit.messageBus.listen(MICROBIT_ID_BUTTON_B, MICROBIT_BUTTON_EVT_LONG_CLICK, load);
    while (gameLoop)
    {
        drawField();
        if (counter <= 100)
        {
            counter++;
        }
        else
            counter = 0;
        makeEnemy();
        shootEnemy();
        updateBulletlist();
        checkCollisionBulletGhost();
        checkCollisionBulletPlayer();
        checkCollisionBetweenBullets();
        updateEnemies();
        uBit.sleep(250);
    }
    uBit.display.scroll(player.score);
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

uint8_t encodePlayer(Player player)
{
    uint8_t shifted_lives = player.lives << 3;
    uint8_t shifted_pos_y = player.pos.y;

    uint8_t savedPlayer;
    savedPlayer = shifted_lives | shifted_pos_y;
    return savedPlayer;
}
uint8_t encodePlayerScore(Player player)
{
    return player.score;
}

uint8_t encodeEnemyPosType(Enemy *enemy)
{
    uint8_t shifted_pos_x = enemy->val->x << 5;
    uint8_t shifted_pos_y = enemy->val->y << 2;
    uint8_t shifted_type = enemy->type;
    uint8_t shifted = shifted_pos_x | shifted_pos_y | shifted_type;
    return shifted;
}
uint8_t encodeEnemyHP(Enemy *enemy)
{
    return enemy->hitpoints;
}

void save(MicroBitEvent e)
{
    uint8_t currentEnemies = countCurrentEnemies();
    int save_data_size = (2 * sizeof(uint8_t) + (currentEnemies * 2 * sizeof(uint8_t)) + (1 * sizeof(uint8_t)));
    uint8_t *to_save = (uint8_t *)malloc(save_data_size);
    uint8_t *pointer = to_save;
    *pointer = currentEnemies;
    pointer = pointer + sizeof(uint8_t);
    for (int i = 0; i < 15; i++)
    {
        if (enemyArray[i] != NULL)
        {
            *pointer = encodeEnemyPosType(enemyArray[i]);
            pointer = pointer + sizeof(uint8_t);
            *pointer = encodeEnemyHP(enemyArray[i]);
            pointer = pointer + sizeof(uint8_t);
        }
    }
    *pointer = encodePlayer(player);
    pointer = pointer + sizeof(uint8_t);
    *pointer = encodePlayerScore(player);
    pointer = pointer + sizeof(uint8_t);
    int result = uBit.storage.put("save", to_save, save_data_size);
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
    free(to_save);
}
void decode_person(uint8_t *saved_person)
{
    uint8_t bitmask_pos_y = 0b00000111;
    uint8_t bitmask_lives = 0b00011000;
    player.lives = (*saved_person & bitmask_lives) >> 3;
    player.pos.y = (*saved_person & bitmask_pos_y);
}

void decodeEnemyPosType(uint8_t *saved, int i)
{
    uint8_t bitmask_pos_x = 0b11100000;
    uint8_t bitmask_pos_y = 0b00011100;
    uint8_t bitmask_type = 0b00000011;
    uint8_t enemyType = (*saved & bitmask_type);
    switch (enemyType)
    {
    case 0:
        enemyArray[i] = makeEasyEnemy();
        enemyCounter = 3;
        bossVar = 0;
        break;
    case 1:
        enemyArray[i] = makeTier2Enemy();
        enemyCounter = 3;
        bossVar = 0;
        break;
    case 2:
        enemyArray[i] = makeTier3Enemy();
        enemyCounter = 3;
        bossVar = 0;
        break;
    case 3:
        enemyArray[i] = makeBoss();
        enemyCounter = 0;
        bossVar = 1;
        break;
    }
    enemyArray[i]->val->x = (*saved & bitmask_pos_x) >> 5;
    enemyArray[i]->val->y = (*saved & bitmask_pos_y) >> 2;
}

void decodeEnemyHP(uint8_t *saved, int i)
{
    enemyArray[i]->hitpoints = *saved;
}

void load(MicroBitEvent e)
{
    uBit.display.clear();
    while (bulletList != NULL)
    {
        bulletList = deleteList(); //delete all the bullets
    }
    for (int a = 0; a < 15; a++)
    { //DELETE EVERY ENEMY
        if (enemyArray[a] != NULL)
        {
            free(enemyArray[a]->val);
            free(enemyArray[a]);
            enemyArray[a] = NULL;
        }
    }
    KeyValuePair *loaded = uBit.storage.get("save");
    if (loaded != NULL)
    {
        uint8_t *saved_data = loaded->value;
        uint8_t *pointer = saved_data;
        uint8_t currentEnemies = *pointer;
        pointer = pointer + sizeof(uint8_t);
        for (int i = 0; i < currentEnemies; i++)
        {
            decodeEnemyPosType(pointer, i);
            pointer = pointer + sizeof(uint8_t);
            decodeEnemyHP(pointer, i);
            pointer = pointer + sizeof(uint8_t);
        }
        if (currentEnemies == 0)
        {
            enemyCounter = 3;
            bossVar = 0;
        }
        decode_person(pointer);
        pointer = pointer + sizeof(uint8_t);
        player.score = *pointer;
        pointer = pointer + sizeof(uint8_t);
    }
    delete loaded;
}
