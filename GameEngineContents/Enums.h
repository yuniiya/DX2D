#pragma once

enum class GAMEOBJGROUP
{
	BACKGROUND,
	STAGE,
	ITEM,
	PLAYER,
	LEVELUP,
	MONSTER,
	OBJ,
	NPC,
	EFFECT,
	SKILL,
	MONSTERSKILL,
	UI,
	SLOTUI,
	QUICKSLOT,
	INVENTORY,
	FONT,
	MOUSE,
	FADE,

	MAINMOUSE,

	MAX,
};

enum class ZOrder
{
	MOUSE = 1,
	MOUSESLOT = 3,
	FONT = 5,
	UI = 10,
	DAMAGE = 15,
	SKILLFRONT = 20,
	MONSTERSKILL = 30,
	ITEM = 40,
	PORTAL = 50,
	PLAYER = 60,
	NPC = 65, 
	SKILLBACK = 70,
	EFFECT = 80,
	MONSTER = 90,
	STAGE = 100,
	BACKGROUND = 110,

	MAX,
};

enum class PLAYERSTATE
{
	IDLE,
	MOVE,
	JUMP,
	FALL,
	PRONE,
	PRONESTAB,
	LADDER,
	ROPE,
	ATTACK,
	DAMAGED,
	DIE,

	MAX,
};


enum class ACTORDIR
{
	LEFT,
	RIGHT,
	NONE,

	MAX,
};

enum class PLAYERSKILL
{
	SKILL_IN,
	SKILL_JI,
	SKILL_PA,
	SKILL_SIN,
	SKILL_SINA,
	SKILL_SINB,
	SKILL_SINC,
	SKILL_SIND,

	MAX,
};

enum class ItemType
{
	ITEM_CACTUS,
	ITEM_WHITERABBIT,
	ITEM_BROWNRABBIT,
	ITEM_SCOR,
	ITEM_SAND,
	ITEM_SPARKER,
	ITEM_FREEZER,
	ITEM_MESO,
	ITEM_HP300,
	ITEM_HP4000,
	ITEM_HP5000,
	ITEM_MP300,
	ITEM_MP4000,
	ITEM_MP5000,
	ITEM_QUEST,

	MAX,
};

enum class InventorySlotType
{
	SLOT_POTION,
	SLOT_ETC,
	SLOT_NONE,

	MAX,
};

enum class NPCType
{
	NPC_Cactus,
	NPC_Entrance,
	NPC_Castle,

	MAX,
};