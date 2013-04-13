#include "Object.h"

void Object::HandleInput(bool* bKeys, Object* objects)
{
     foreach object in objects
       object->HandleInput(bKeys, NULL)
}

void Object::Render(Object* objects)
{
     foreach object in objects
       object->Render(NULL)
}

void Object::Update(Object* objects)
{
     foreach object in objects
       object->Update(NULL)
}