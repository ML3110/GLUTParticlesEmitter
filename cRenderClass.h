#pragma once

//class cParticle;

class cRenderClass
{
public:

	cRenderClass(const int, const int);
	~cRenderClass();

	void create(int argc, _TCHAR* argv[]);
	void loop();

	void clear();

	void render();
	void setColour(float, float, float, float);
	void setColour(cParticle);
	void setPointSize(int);
	void drawPixel(int, int);

private:
	int		 m_sw, m_sh;
	int		 m_point_size;
	float	*m_buffer;
	sRGBA	 m_colour;
};