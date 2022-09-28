#pragma once
#include "KeyboardEvent.h"
#include <queue>

class KeyboardClass
{
private:
	static KeyboardClass* Inst;

public:
	static KeyboardClass& GetInst()
	{
		return *Inst;
	}

	static void Destory()
	{
		if (nullptr != Inst)
		{
			delete Inst;
			Inst = nullptr;
		}
	}

private:
	bool autoRepeatKeys = false;
	bool autoRepeatChars = false;
	bool KeyState[256];
	std::queue<KeyboardEvent> KeyBuffer;
	std::queue<unsigned char> CharBuffer;

public:
	bool KeyIsPressed(const unsigned char keyCode);
	bool KeyBufferIsEmpty();
	bool CharBufferIsEmpty();
	KeyboardEvent ReadKey();
	unsigned char ReadChar();
	void OnKeyPressed(const unsigned char Key);
	void OnKeyReleased(const unsigned char Key);
	void OnChar(const unsigned char key);
	void EnableAutoRepeatKeys();
	void DisableAutoRepeatKeys();
	void EnableAutoRepeatChars();
	void DisableAutoRepeatChars();
	bool IsKeysAutoRepeat();
	bool IsCharsAutoRepeat();
	void DeleteCharBuffer();
public:
	//construcuter destructer
	KeyboardClass();
	~KeyboardClass();

	//delete Function
	KeyboardClass(const KeyboardClass& _Other) = delete;
	KeyboardClass(KeyboardClass&& _Other) noexcept = delete;
	KeyboardClass& operator=(const KeyboardClass& _Other) = delete;
	KeyboardClass& operator=(KeyboardClass&& _Other) noexcept = delete;
};

