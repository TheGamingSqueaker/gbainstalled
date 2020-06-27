
#ifndef _MENU_H
#define _MENU_H

#include <ultra64.h>

#define INITIAL_TIME_DELAY 16
#define REPEAT_TIME_DELAY 2

struct MenuItem;

typedef void (*MenuItemRender)(struct MenuItem* menuItem, struct MenuItem* highlightedItem);
typedef struct MenuItem* (*MenuItemHandleInput)(struct MenuItem* menuItem, int buttonsDown, int buttonsState);
typedef void (*MenuItemSetActive)(struct MenuItem* menuItem, int isActive);

#define MENU_ITEM_FLAGS_HIDDEN  0x1

struct MenuItem {
    struct MenuItem* toLeft;
    struct MenuItem* toRight;
    struct MenuItem* toUp;
    struct MenuItem* toDown;
    void* data;
    MenuItemRender renderCallback;
    MenuItemHandleInput handleButtonDown;
    MenuItemHandleInput handleButtonUp;
    MenuItemSetActive setActive;
    u32 flags;
};

struct MenuState {
    struct MenuItem* currentMenuItem;
    struct MenuItem* allItems;
    int menuItemCount;
    int lastButtons;
    int holdTimer;
};

void initMenuState(struct MenuState* menu, struct MenuItem* items, int itemCount);

void menuStateHandleInput(struct MenuState* menu, OSContPad* pad);
void menuStateRender(struct MenuState* menu);
void menuItemInit(struct MenuItem* menuItem, void* data, MenuItemRender renderCallback, MenuItemHandleInput handleButtonDown, MenuItemSetActive setActive);

void menuItemConnectSideToSide(struct MenuItem* left, struct MenuItem* right);
void menuItemConnectUpAndDown(struct MenuItem* up, struct MenuItem* down);

#endif