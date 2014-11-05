#include "Button.h"
#include <UtH/Engine/Sprite.hpp>
#include <UtH/Platform/Input.hpp>

Button::Button(const uth::RenderTarget& target, uth::Texture* texture)
	: GameObject(), target(target)
{	
	this->AddComponent(new uth::Sprite(texture));
}
Button::~Button(){}

void Button::update(float dt)
{
	// TODO: Change to Touch Input?
	if (uthInput.Common.Event() == uth::InputEvent::TAP)
	{
		auto pos = target.PixelToCoords(uthInput.Common.Position());

		if (transform.GetBounds().contains(pos))
			callback();
	}

}

void Button::setCallBack(std::function<void()> callback)
{
	this->callback = callback;
}