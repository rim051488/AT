#pragma once
#include <array>
#include "InputID.h"

using inputData = std::array<std::pair<bool, bool>, static_cast<size_t>(InputID::Max) + 1>;

class Input
{
public:
	Input();
	virtual ~Input();
	virtual void Update(void) = 0;
	const inputData& Get(void);
protected:
	inputData data_;
};

