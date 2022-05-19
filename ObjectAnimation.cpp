#include "ObjectAnimation.h"

void Program::LoadAnimations(const std::string &name)
{
    LoadAnimationsProject(name + "Classic.scproj");
    LoadAnimationsProject(name + "Next.scproj");
}

void Program::LoadAnimationsProject(const std::string &name)
{
    std::shared_ptr<ObjectAnimation> anim = std::make_shared<ObjectAnimation>();
    anim->Name = name;

    std::string animFileName = "./res/animations/" + name;
    BinaryStreamReader f(animFileName.c_str());

    f.ReadString(); //пропуск номера версии проекта

    //спрайты
    anim->Sprites.clear();
    int32_t spr_count = f.ReadInt32();
    for (int32_t i = 0; i < spr_count; i++)
    {
        std::shared_ptr<ObjectAnimation::Sprite> s = std::make_shared<ObjectAnimation::Sprite>();
        s->Name   = f.ReadString();
        s->Type   = f.ReadByte();
        s->Width  = f.ReadInt32();
        s->Height = f.ReadInt32();

        //монохромный спрайт с маской
        if (s->Type == 0)
        {
            s->ClassicLayer = AllocateDynamicArray<int32_t>(s->Height, s->Width);
            for (int32_t y = 0; y < s->Height; y++)
            {
                for (int32_t x = 0; x < s->Width; x++)
                {
                    s->ClassicLayer[x][y] = f.ReadInt32();
                }
            }
        }

        //255-цветный спрайт в палитре Next
        if (s->Type == 1)
        {
            s->NextLayer = AllocateDynamicArray<SdlDotNetCompat::Drawing::Color>(s->Height, s->Width);
            for (int32_t y = 0; y < s->Height; y++)
            {
                for (int32_t x = 0; x < s->Width; x++)
                {
                    s->NextLayer[x][y] = Color::FromArgb(f.ReadInt32());
                }
            }
        }
        anim->Sprites.push_back(s);
    }

    //анимации
    anim->Animations.clear();
    int32_t anim_count = f.ReadInt32();
    for (int32_t i = 0; i < anim_count; i++)
    {
        std::shared_ptr<ObjectAnimation::Animation> a = std::make_shared<ObjectAnimation::Animation>();
        a->Name = f.ReadString();

        //кадры
        int32_t frame_count = f.ReadInt32();
        a->Frames = std::vector<std::shared_ptr<ObjectAnimation::Frame>>();
        for (int32_t j = 0; j < frame_count; j++)
        {
            std::shared_ptr<ObjectAnimation::Frame> fr = std::make_shared<ObjectAnimation::Frame>();

            //композиции
            int32_t comp_count = f.ReadInt32();
            fr->Composition = std::vector<std::shared_ptr<ObjectAnimation::CompositionElement>>();
            for (int32_t k = 0; k < comp_count; k++)
            {
                std::shared_ptr<ObjectAnimation::CompositionElement> c = std::make_shared<ObjectAnimation::CompositionElement>();
                c->ElemSprite = FindSprite(f.ReadString(), anim);
                c->XOffset = f.ReadInt32();
                c->YOffset = f.ReadInt32();
                f.ReadBoolean(); //пропуск свойста View композиции
                fr->Composition.push_back(c);
            }
            fr->DX1   = f.ReadInt32();
            fr->DY1   = f.ReadInt32();
            fr->DX2   = f.ReadInt32();
            fr->DY2   = f.ReadInt32();
            fr->HX1   = f.ReadInt32();
            fr->HY1   = f.ReadInt32();
            fr->HX2   = f.ReadInt32();
            fr->HY2   = f.ReadInt32();
            fr->Time  = f.ReadInt32();
            fr->Event = f.ReadString();
            a->Frames.push_back(fr);
        }
        a->Loop = f.ReadBoolean();
        anim->Animations.push_back(a);
    }

    ObjectAnimations.push_back(anim);
}

std::shared_ptr<Program::ObjectAnimation::Sprite> Program::FindSprite(const std::string &name, const std::shared_ptr<ObjectAnimation> &anim)
{
    for (const auto &s : anim->Sprites)
    {
        if (s->Name == name)
        {
            return s;
        }
    }
    return nullptr;
}

void Program::InitAnimation(const std::shared_ptr<GameObject> &obj, const std::string &name, bool hard_enable)
{
    int32_t i = 0;
    for (const auto &a : obj->Animations[sprite_mode]->Animations)
    {
        if (a->Name == name && (obj->CurrentAnimation != i || hard_enable))
        {
            obj->CurrentAnimation = static_cast<uint8_t>(i);
            obj->Frame = 0;
            obj->AnimCounter = static_cast<uint8_t>(obj->Animations[sprite_mode]->Animations[i]->Frames[0]->Time);
            obj->AnimationPlayed = true;
            GetObjSize(obj);
            break;
        }
        i++;
    }
}

void Program::InitAnimation(const std::shared_ptr<GameObject> &obj, uint8_t id_anim, bool hard_enable)
{
    if (obj->CurrentAnimation != id_anim || hard_enable)
    {
        obj->CurrentAnimation = id_anim;
        obj->Frame = 0;
        obj->AnimCounter = static_cast<uint8_t>(obj->Animations[sprite_mode]->Animations[id_anim]->Frames[0]->Time);
        obj->AnimationPlayed = true;
        GetObjSize(obj);
    }
}

void Program::PlayAnimation(const std::shared_ptr<GameObject> &obj)
{
    if (!obj->AnimationPlayed || obj->NoVisible)
    {
        obj->NoInterruptAnim = false;
        return;
    }
    obj->AnimCounter--;
    if (obj->AnimCounter != 0)
    {
        return;
    }
    obj->Frame++;
    if (obj->Frame == obj->Animations[sprite_mode]->Animations[obj->CurrentAnimation]->Frames.size())
    {
        if (obj->Animations[sprite_mode]->Animations[obj->CurrentAnimation]->Loop)
        {
            obj->Frame = 0;
        }
        else
        {
            obj->Frame--;
            obj->AnimationPlayed = false;
            return;
        }
    }
    obj->AnimCounter = static_cast<uint8_t>(obj->Animations[sprite_mode]->Animations[obj->CurrentAnimation]->Frames[obj->Frame]->Time);
    std::string e = obj->Animations[sprite_mode]->Animations[obj->CurrentAnimation]->Frames[obj->Frame]->Event;
    GetObjSize(obj);

    //обработка событий
    DoEvent(obj, e);
}

void Program::GetObjSize(const std::shared_ptr<Program::GameObject> &obj)
{
    obj->Width = obj->Animations[sprite_mode]->Animations[obj->CurrentAnimation]->Frames[obj->Frame]->DX2;
    obj->Height = obj->Animations[sprite_mode]->Animations[obj->CurrentAnimation]->Frames[obj->Frame]->DY1;
}

std::vector<std::shared_ptr<Program::ObjectAnimation>> Program::FindObjectAnimation(const std::string &name)
{
    std::vector<std::shared_ptr<ObjectAnimation>> anim(2);
    for (const auto &a : ObjectAnimations)
    {
        if (a->Name == name + "Classic.scproj")
        {
            anim[0] = a;
        }
    }
    for (const auto &a : ObjectAnimations)
    {
        if (a->Name == name + "Next.scproj")
        {
            anim[1] = a;
        }
    }
    return anim;
}