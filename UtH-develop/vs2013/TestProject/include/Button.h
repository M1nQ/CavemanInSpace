#ifndef BUTTON_H
#define BUTTON_H

#include <UtH/Engine/GameObject.hpp>
#include <UtH/Renderer/Texture.hpp>
#include <functional>

class Button : public uth::GameObject
{
public:
	Button(const uth::RenderTarget& target, uth::Texture* texture);
	~Button();

	void update(float dt) override;
	
	void setCallBack(std::function<void()> callback);

private:
	const uth::RenderTarget& target;
	std::function<void()> callback;
};

#endif