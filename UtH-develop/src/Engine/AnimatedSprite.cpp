#include <UtH/Engine/AnimatedSprite.hpp>
#include <UtH/Platform/Debug.hpp>
#include <UtH/Engine/GameObject.hpp>
#include <UtH/Platform/HiResTimer.hpp>
#include <cassert>

using namespace uth;


//uth::AnimatedSprite::AnimatedSprite()
//    : Sprite()
//{
//
//}

AnimatedSprite::AnimatedSprite(Texture* texture, const unsigned int frames,
	const pmath::Vec2& frameSize,
	const float fps, const unsigned int firstFrame,
	const bool reversed, const bool loop)
	: Sprite(texture, "AnimatedSprite"),
		m_frames(frames),
		m_firstFrame(firstFrame),
		m_curFrame(firstFrame),
		m_fps(fps),
		m_delay(0.0f),
		m_reversed(reversed),
		m_loop(loop),
		m_loopEnd(false)
{
	const pmath::Vec2 texSize = texture->GetSize();

	m_frameCountX = static_cast<unsigned int>(texSize.x / frameSize.x);
	m_frameCountY = static_cast<unsigned int>(texSize.y / frameSize.y);

#ifndef NDEBUG
	if(int(texSize.x) % int(frameSize.x) != 0 || int(texSize.y) % int(frameSize.y) != 0)
	{
		WriteError("Bad frame size! texture(%f, %f) frame(%f, %f)",
			texSize.x, texSize.y, frameSize.x, frameSize.y);
		assert(false);
	}

	if (frames > m_frameCountX * m_frameCountY)
	{
		WriteError("Too many frames! (maximum frame capacity: %d)", m_frameCountX * m_frameCountY);
		assert(false);
	}
#endif
	
	// Doesn't work for some reason.
	//AnimatedSprite(texture, frames, m_frameCountX, m_frameCountY, fps, firstFrame, reversed, loop);

	// frame size in pixels
	m_sizePx.x = static_cast<const float>(texSize.x / m_frameCountX);
	m_sizePx.y = static_cast<const float>(texSize.y / m_frameCountY);
	// frame size in texcoord float
	m_sizeTc.x = 1.0f / m_frameCountX;
	m_sizeTc.y = 1.0f / m_frameCountY;
}

AnimatedSprite::AnimatedSprite(Texture* texture, const unsigned int frames,
	const unsigned int frameCountX, const unsigned int frameCountY,
	const float fps, const unsigned int firstFrame,
	const bool reversed, const bool loop)
	: Sprite(texture, "AnimatedSprite"),
		m_frames(frames),
		m_firstFrame(firstFrame),
		m_curFrame(firstFrame),
		m_fps(fps),
		m_delay(0.0f),
		m_reversed(reversed),
		m_loop(loop),
		m_loopEnd(false),
		m_frameCountX(frameCountX),
        m_frameCountY(frameCountY)
{
	const unsigned int texSizeX = static_cast<const unsigned int>(texture->GetSize().x);
	const unsigned int texSizeY = static_cast<const unsigned int>(texture->GetSize().y);

#ifndef NDEBUG
	if(texSizeX % frameCountX != 0 || texSizeY % frameCountY != 0)
	{
		WriteError("Bad texture size! (%d, %d)", texSizeX, texSizeY);
		assert(false);
	}
	if(frames > frameCountX * frameCountY)
	{
		WriteError("Too many frames! (maximum frame capacity: %d)", frameCountX * frameCountY);
		assert(false);
	}
#endif
	// frame size in pixels
	m_sizePx.x = static_cast<const float>(texSizeX / frameCountX);
	m_sizePx.y = static_cast<const float>(texSizeY / frameCountY);
	// frame size in texcoord float
	m_sizeTc.x = 1.0f / frameCountX;
	m_sizeTc.y = 1.0f / frameCountY;
}

AnimatedSprite::~AnimatedSprite()
{
}

void AnimatedSprite::ChangeAnimation(int loopStartFrame, int loopFrames,
	int startFrame, float fps, bool loop, bool reversed)
{

#ifndef NDEBUG
	if(loopFrames == 0)
	{
		WriteError("0 frame animation? (frame count = 0)");
		assert(false);
	}
#endif
	if(startFrame < loopStartFrame)
		m_curFrame = loopStartFrame;
	else
		m_curFrame = startFrame;

	m_frames = loopFrames;
	m_firstFrame = loopStartFrame;
	m_fps = fps;
	m_loop = loop;
	m_loopEnd = false;
	m_frameCount = 0;
	m_reversed = reversed;
	generateBuffer(true);
}

void AnimatedSprite::ChangeSpeed(float fps)
{
	m_fps = fps;
}

void AnimatedSprite::Init()
{
	ChangeAnimation(m_firstFrame,m_frames,m_firstFrame, m_fps, m_loop, m_reversed);

	const pmath::Vec2 size = pmath::Vec2(m_sizePx.x, m_sizePx.y);
	parent->transform.setSize(size);
}

void AnimatedSprite::Update(float dt)
{
    if (m_frames < 2 || m_fps == 0)
        return;

	m_delay += dt;

	if (!m_loop)
	{
		if(m_frames == m_frameCount + 1)
			m_loopEnd = true;
	}

	if(m_delay > 1.0f / m_fps && !m_loopEnd)
	{
		m_delay = 0.0f;
		m_frameCount++;
		if(!m_reversed)
		{
			m_curFrame++;
			if (m_curFrame - m_firstFrame >= m_frames)
			{
				m_curFrame -= m_frames;
			}
		}
		else
		{
			m_curFrame--;
			if(m_curFrame < m_firstFrame)
			{
				m_curFrame = m_firstFrame + m_frames - 1;
			}
		}
		generateBuffer();
	}
}

void AnimatedSprite::generateBuffer(bool init)
{
	const int X = m_curFrame % m_frameCountX;
	const int Y = m_curFrame/m_frameCountX;

	const float w = m_sizePx.x;
	const float h = m_sizePx.y;

	const pmath::Rect texCoord(
		X * m_sizeTc.x,
		1.0f - Y * m_sizeTc.y,
		m_sizeTc.x,
		-m_sizeTc.y);

    if (init)
    {
        m_vertexBuffer.clear();

        m_vertexBuffer.addVertex(Vertex(
            pmath::Vec3(-0.5f * w, -0.5f * h, 0),
            pmath::Vec2(texCoord.getLeft(), texCoord.getTop()),
            m_color));
        m_vertexBuffer.addVertex(Vertex(
            pmath::Vec3(0.5f * w, -0.5f * h, 0),
            pmath::Vec2(texCoord.getRight(), texCoord.getTop()),
            m_color));
        m_vertexBuffer.addVertex(Vertex(
            pmath::Vec3(-0.5f * w, 0.5f * h, 0),
            pmath::Vec2(texCoord.getLeft(), texCoord.getBottom()),
            m_color));
        m_vertexBuffer.addVertex(Vertex(
            pmath::Vec3(0.5f * w, 0.5f * h, 0),
            pmath::Vec2(texCoord.getRight(), texCoord.getBottom()),
            m_color));


        m_vertexBuffer.addIndex(0);
        m_vertexBuffer.addIndex(1);
        m_vertexBuffer.addIndex(2);
        m_vertexBuffer.addIndex(1);
        m_vertexBuffer.addIndex(3);
        m_vertexBuffer.addIndex(2);

        m_vertexBuffer.setData();
    }
    else // We are updating the buffer
    {
        std::vector<Vertex> vertices;
        vertices.push_back(Vertex(
            pmath::Vec3(-0.5f * w, -0.5f * h, 0),
            pmath::Vec2(texCoord.getLeft(), texCoord.getTop()),
            m_color));
        vertices.push_back(Vertex(
            pmath::Vec3(0.5f * w, -0.5f * h, 0),
            pmath::Vec2(texCoord.getRight(), texCoord.getTop()),
            m_color));
        vertices.push_back(Vertex(
            pmath::Vec3(-0.5f * w, 0.5f * h, 0),
            pmath::Vec2(texCoord.getLeft(), texCoord.getBottom()),
            m_color));
        vertices.push_back(Vertex(
            pmath::Vec3(0.5f * w, 0.5f * h, 0),
            pmath::Vec2(texCoord.getRight(), texCoord.getBottom()),
            m_color));

        m_vertexBuffer.changeBufferData(0, vertices);
    }
}

namespace rj = rapidjson;

rj::Value AnimatedSprite::save(rj::MemoryPoolAllocator<>& alloc) const
{
    rj::Value val = Sprite::save(alloc);

    val.AddMember(rj::StringRef("frames"), m_frames, alloc);
    val.AddMember(rj::StringRef("firstFrame"), m_firstFrame, alloc);
    val.AddMember(rj::StringRef("curFrame"), m_curFrame, alloc);

    rj::Value& sizeVal = val.AddMember(rj::StringRef("sizes"), rj::kArrayType, alloc)["sizes"];

    sizeVal.PushBack(m_sizePx.x, alloc)
           .PushBack(m_sizePx.y, alloc)
           .PushBack(m_sizeTc.x, alloc)
           .PushBack(m_sizeTc.y, alloc);

    val.AddMember(rj::StringRef("fps"), m_fps, alloc);
    val.AddMember(rj::StringRef("delay"), m_delay, alloc);
    val.AddMember(rj::StringRef("reversed"), m_reversed, alloc);
    val.AddMember(rj::StringRef("loop"), m_loop, alloc);
    
    val.AddMember(rj::StringRef("frameCountX"), m_frameCountX, alloc);
    val.AddMember(rj::StringRef("frameCountY"), m_frameCountY, alloc);

    return val;
}

bool uth::AnimatedSprite::load(const rj::Value& doc)
{
    if (!Sprite::load(doc))
        return false;

    m_firstFrame = doc["firstFrame"].GetInt();
    m_curFrame = doc["curFrame"].GetInt();

    const rj::Value& sizeVal = doc["sizes"];

    m_sizePx.x = sizeVal[0u].GetDouble();
    m_sizePx.y = sizeVal[1].GetDouble();
    m_sizeTc.x = sizeVal[2].GetDouble();
    m_sizeTc.y = sizeVal[3].GetDouble();

    m_fps = doc["fps"].GetDouble();
    m_delay = doc["delay"].GetDouble();
    m_reversed = doc["reversed"].GetBool();
    m_loop = doc["loop"].GetBool();

    ChangeAnimation(0, m_frames, m_curFrame, m_fps, m_loop, m_reversed);
    const pmath::Vec2 size = pmath::Vec2(m_sizePx.x, m_sizePx.y);
    parent->transform.setSize(size);

    return true;
}