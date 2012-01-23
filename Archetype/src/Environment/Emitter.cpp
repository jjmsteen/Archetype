 
#include "stdafx.h"

#include "Emitter.h"

using namespace AT;

Emitter::Emitter()
	: name("Unnamed Emitter"), worldTransform(), emitting(false), emitterShape(0)
{
}

Emitter::Emitter(const std::string & name, const Maths::Matrix4x4 & worldTransform, bool isEmitting, Model::Mesh * emitterShape)
	: name(name), worldTransform(worldTransform), emitting(isEmitting)
{
}


Emitter::~Emitter(void)
{
	if (emitterShape)
		delete emitterShape;
}

#pragma region OAO / Copy Constructor

Emitter::Emitter(const Emitter & e)
{
	this->DeepCopy(e);
}

Emitter & Emitter::operator= (const Emitter & e)
{
	this->DeepCopy(e);

	return *this;
}

void Emitter::DeepCopy(const Emitter & e)
{
	this->name = e.name;
	this->worldTransform = e.worldTransform;
	this->emitting = e.emitting;

	if (e.emitterShape)
		this->emitterShape = new Model::Mesh(*e.emitterShape);
	else
		this->emitterShape = 0;


}

#pragma endregion

const Maths::Matrix4x4 & Emitter::GetWorldTransform() const { return worldTransform; }

bool Emitter::IsEmitting() const { return emitting; }