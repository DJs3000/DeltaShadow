int32_t Program::UpdateBar(int32_t current, int32_t value, int32_t x, int32_t y)
{
    if (value >= 78)
    {
        value = 77;
    }
    if (current < value)
    {
        SetScaleCol(x + current, y);
        current++;
    }
    else if (current >= value + 1)
    {
        current--;
        ResScaleCol(x + current, y);
    }
    return current;
}