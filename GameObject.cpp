#include "GameObject.h"

std::shared_ptr<Program::GameObject> Program::CreateObject(uint8_t name, int32_t x, int32_t y, bool direction, bool actual_object)
{
    //ищем пустой слот объекта
    for (uint32_t i = 0; i < game_objects.size(); i++)
    {
        if (game_objects[i]->Name == 0)
        {
            std::shared_ptr<GameObject> obj = std::make_shared<GameObject>();
            obj->Name = name;
            obj->X = x;
            obj->Y = y;
            obj->Direction = direction;
            game_objects[i] = obj;
            if (actual_object)
            {
                AddActualObject(obj);
            }
            return obj;
        }
    }
    return game_objects[127];
}

void Program::RemoveObject(const std::shared_ptr<GameObject> &obj)
{
    RemoveActualObject(obj);
    obj->Name = 0;
}

void Program::ClearAllObjects()
{
    for (size_t i = 0; i < game_objects.size(); i++)
    {
        std::shared_ptr<GameObject> obj = std::make_shared<GameObject>();
        obj->Name = 0;
        game_objects[i] = obj;
    }
    ClearActualObjectsList();
    particle_cntr = 0;
}

void Program::ClearActualObjectsList()
{
    for (size_t i = 0; i < actual_objects.size(); i++)
    {
        std::shared_ptr<GameObject> obj = std::make_shared<GameObject>();
        obj->Name = 0;
        actual_objects[i] = obj;
    }
}

void Program::AddActualObject(const std::shared_ptr<GameObject> &obj)
{
    for (size_t i = 0; i < actual_objects.size(); i++)
    {
        if (actual_objects[i]->Name == 0)
        {
            actual_objects[i] = obj;
            break;
        }
    }
}

void Program::RemoveActualObject(const std::shared_ptr<GameObject> &obj)
{
    for (size_t i = 0; i < actual_objects.size(); i++)
    {
        if (actual_objects[i] == obj)
        {
            for (size_t j = i; j < actual_objects.size() - 1; j++)
            {
                if (actual_objects[j]->Name == 0)
                {
                    break;
                }
                actual_objects[j] = actual_objects[j + 1];
            }
            break;
        }
    }
}

std::shared_ptr<Program::GameObject> Program::CreateChild(const std::shared_ptr<Program::GameObject> &obj, uint8_t name, int32_t xoffset, int32_t yoffset)
{
    if (obj->Direction)
    {
        xoffset = -xoffset;
    }
    return CreateObject(name, obj->X + xoffset, obj->Y + yoffset, obj->Direction, true);
}
