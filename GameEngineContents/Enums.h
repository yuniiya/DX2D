#pragma once

enum class GAMEOBJGROUP
{
	BACKGROUND,
	STAGE,
	PLAYER,
	MONSTER,
	OBJ,
	EFFECT,
	SKILL,
	MONSTERSKILL,
	UI,
	FADE,
	MOUSE,

	MAX,
};

enum class ZOrder
{
	MOUSE = 1,
	UI = 10,
	SKILLFRONT = 20,
	MONSTERSKILL = 30,
	PLAYER = 40,
	SKILLBACK = 50,
	EFFECT = 60,
	ITEM = 70,
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