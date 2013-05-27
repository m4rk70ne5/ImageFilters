#ifndef OBJECT_H
#define OBJECT_H

#include "base.h"

using namespace std;

class Object;  // forward declaration

typedef void (*pfuncVoid)(Object*);

struct tKey
{
	bool depressedFlag;
	bool holdFlag;
	pfuncVoid keyFunction;
};

class Object
{
	protected:
		Object* objList;
		map<int, tKey*> keyMap;
		vector<int> keys;
	public:
		Object();
		virtual ~Object();
		virtual void HandleInput();
		virtual void Render();
		virtual void Update();
		void AddObject(Object*);
		void RegisterKey(int, pfuncVoid, bool);
};

#endif