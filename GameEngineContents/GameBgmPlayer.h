#pragma once

// Ό³Έν :
class GameBgmPlayer
{
public:
	// constrcuter destructer
	GameBgmPlayer();
	~GameBgmPlayer();

	// delete Function
	GameBgmPlayer(const GameBgmPlayer& _Other) = delete;
	GameBgmPlayer(GameBgmPlayer&& _Other) noexcept = delete;
	GameBgmPlayer& operator=(const GameBgmPlayer& _Other) = delete;
	GameBgmPlayer& operator=(GameBgmPlayer&& _Other) noexcept = delete;

protected:

private:

};

