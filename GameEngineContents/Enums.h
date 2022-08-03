#pragma once

enum class GAMEOBJGROUP
{
	BACKGROUND,
	STAGE,
	PLAYER,
	MONSTER,
	OBJ,
	EFFECT,
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