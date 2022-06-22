#include "Input.h"

Input::Input()
{
    data_.fill(std::make_pair(false, false));
}

Input::~Input()
{
}

const inputData& Input::Get(void)
{
    return data_;
}
