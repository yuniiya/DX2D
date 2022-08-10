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
	UI,
	FADE,
	MOUSE,

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