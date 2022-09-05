#pragma once

enum class GAMEOBJGROUP
{
	BACKGROUND,
	STAGE,
	ITEM,
	PLAYER,
	PLAYERCENTER,
	MONSTER,
	OBJ,
	NPC,
	EFFECT,
	SKILL,
	MONSTERSKILL,
	UI,
	SLOTUI,
	FONT,
	FADE,
	MOUSE,
	MAINMOUSE,

	MAX,
};

enum class ZOrder
{
	MOUSE = 1,
	FONT = 5,
	UI = 10,
	SKILLFRONT = 20,
	MONSTERSKILL = 30,
	ITEM = 40,
	PLAYER = 50,
	NPC = 55, 
	SKILLBACK = 60,
	EFFECT = 70,
	MONSTER = 80,
	PORTAL = 90,
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


	MAX,
};

enum class NPCType
{
	NPC_Ariant,
	NPC_Entrance,
	NPC_Castle,

	MAX,
};