#pragma once

#include "libPrefix.h"

#include <string>

#include "Renderable.h"
#include "Matrix4x4.h"
#include "Mesh.h"

namespace AT
{

class Emitter : public Renderable
{
protected:

	std::string name;

	Maths::Matrix4x4 worldTransform;

	bool emitting;

	Model::Mesh * emitterShape;

public:

#pragma region Constructors / Destructor

	DLLEXPORT Emitter();

	DLLEXPORT Emitter(const std::string & name, const Maths::Matrix4x4 & worldTransform, 
		bool isEmitting, Model::Mesh * emitterShape = 0);

	DLLEXPORT virtual ~Emitter(void);

#pragma endregion

#pragma region OAO / Copy Constructor

	DLLEXPORT Emitter(const Emitter & e);

	DLLEXPORT Emitter & operator= (const Emitter & e);

private:
	DLLEXPORT void DeepCopy(const Emitter & e);
public:

#pragma endregion

#pragma region Getters and Setters

	DLLEXPORT const Maths::Matrix4x4 & GetWorldTransform() const;

	DLLEXPORT bool IsEmitting() const;

#pragma endregion

#pragma region Abstract Methods

	DLLEXPORT virtual void Enable() = 0;

	DLLEXPORT virtual void Disable() = 0;

#pragma endregion

};


}