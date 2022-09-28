#include "PreCompile.h"
#include "KeyboardClass.h"

KeyboardClass* KeyboardClass::Inst = new KeyboardClass();


KeyboardClass::KeyboardClass()
{
	for (int i = 0; i < 256; i++)
	{
		KeyState[i] = false;
	}
}

KeyboardClass::~KeyboardClass()
{
	while (!KeyBuffer.empty())
	{
		KeyBuffer.pop();
	}

	// 문자 버퍼 소멸
	while (!CharBuffer.empty())
	{
		CharBuffer.pop();
	}
}

bool KeyboardClass::KeyIsPressed(const unsigned char KeyCode)
{
	return KeyState[KeyCode];
}

bool KeyboardClass::KeyBufferIsEmpty()
{
	return KeyBuffer.empty();
}

bool KeyboardClass::CharBufferIsEmpty()
{
	return CharBuffer.empty();
}

KeyboardEvent KeyboardClass::ReadKey()
{
	if (KeyBuffer.empty())
	{
		return KeyboardEvent();
	}
	else
	{
		KeyboardEvent e = KeyBuffer.front();
		KeyBuffer.pop();
		return e;
	}
}

unsigned char KeyboardClass::ReadChar()
{
	if (CharBuffer.empty())
	{
		return 0;
	}
	else
	{
		unsigned char e = CharBuffer.front();
		CharBuffer.pop();


		return e;
	}
}

void KeyboardClass::OnKeyPressed(const unsigned char key)
{
	KeyState[key] = false;
	KeyBuffer.push(KeyboardEvent(KeyboardEvent::EventType::Press, key));
}

void KeyboardClass::OnKeyReleased(const unsigned char key)
{
	KeyState[key] = false;
	KeyBuffer.push(KeyboardEvent(KeyboardEvent::EventType::Release, key));
}

void KeyboardClass::OnChar(const unsigned char key)
{
	CharBuffer.push(key);
}

void KeyboardClass::EnableAutoRepeatKeys()
{
	autoRepeatKeys = true;
}

void KeyboardClass::DisableAutoRepeatKeys()
{
	autoRepeatKeys = false;
}


void KeyboardClass::EnableAutoRepeatChars()
{
	autoRepeatChars = true;
}

void KeyboardClass::DisableAutoRepeatChars()
{
	autoRepeatChars = false;
}

bool KeyboardClass::IsKeysAutoRepeat()
{
	return autoRepeatKeys;
}

bool KeyboardClass::IsCharsAutoRepeat()
{
	return autoRepeatChars;
}

void KeyboardClass::DeleteCharBuffer()
{
	if (true == CharBufferIsEmpty())
	{
		return;
	}
	while (!CharBuffer.empty())
	{
		CharBuffer.pop();
	}

}

