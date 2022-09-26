#pragma once

// Ό³Έν :
class GameBgmPlayer
{
public:
	static GameBgmPlayer* BgmPlay_;
	// constrcuter destructer
	GameBgmPlayer();
	~GameBgmPlayer();

	// delete Function
	GameBgmPlayer(const GameBgmPlayer& _Other) = delete;
	GameBgmPlayer(GameBgmPlayer&& _Other) noexcept = delete;
	GameBgmPlayer& operator=(const GameBgmPlayer& _Other) = delete;
	GameBgmPlayer& operator=(GameBgmPlayer&& _Other) noexcept = delete;

	GameEngineSoundPlayer BgmPlayer_;

public:
	void Stop()
	{
		BgmPlayer_.Stop();
	}

	void ChangeBgm(std::string _BgmName, unsigned int LoopCount = 30)
	{
		BgmPlayer_.Stop();
		BgmPlayer_ = GameEngineSound::SoundPlayControl(_BgmName, LoopCount);
	}

	void Destroy()
	{
		if (BgmPlay_ != nullptr)
		{
			delete BgmPlay_;
		}
	}

protected:

private:

};

