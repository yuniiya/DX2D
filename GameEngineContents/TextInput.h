#pragma once

// Ό³Έν :
class TextInput
{
public:
	// constrcuter destructer
	TextInput();
	~TextInput();

	// delete Function
	TextInput(const TextInput& _Other) = delete;
	TextInput(TextInput&& _Other) noexcept = delete;
	TextInput& operator=(const TextInput& _Other) = delete;
	TextInput& operator=(TextInput&& _Other) noexcept = delete;

protected:

private:

};

