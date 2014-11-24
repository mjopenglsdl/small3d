/*
*  Text.cpp
*
*  Created on: 2014/11/23
*      Author: Dimitri Kourkoulis
*              http://dimitros.be
*     License: MIT
*/

#include "Text.h"
#include "Exception.h"
#include <stdlib.h>

using namespace std;

bool ttfInitialised = false;

namespace small3d {

	string intToStr( int number )
	{
		char buffer[100];
#if defined(_WIN32) && !defined(__MINGW32__)
		_itoa_s(number, buffer, 10);
#else
		_itoa(number, buffer, 10);
#endif
		return string(buffer);
	}

	Text::Text(shared_ptr<Renderer> renderer,
		const string &ttfFontPath, const int &size)
	{
		this->renderer = renderer;

		if (!ttfInitialised) {


			if(TTF_Init()==-1)
			{
				LOGERROR(TTF_GetError());
				throw Exception("Unable to initialise font system");
			}
			else
			{
				ttfInitialised = true;
			}
		}

		string fontPath = SDL_GetBasePath() + ttfFontPath;
		LOGINFO("Loading font from " + fontPath);

		font = TTF_OpenFont(fontPath.c_str(), size);

		this->size = size;

		if (!font)
		{
			LOGERROR(TTF_GetError());
			throw Exception("Failed to load font");
		}
		else
		{
			LOGINFO("TTF font loaded successfully");
		}
	}

	Text::~Text()
	{
		TTF_CloseFont(font);
		//TTF_Quit();
	}

	void Text::renderText(const string &text, const SDL_Color &colour, 
		const float &topX, const float &topY, const float &bottomX, const float &bottomY)
	{
		GLuint textHandle = renderer->getTextureHandle(intToStr(size) + "text_" + text);

		if (textHandle == 0)
		{

			SDL_Surface *textSurface = TTF_RenderText_Blended(font,
				text.c_str(), colour);
			int numPixels = textSurface->h * textSurface->w;

			Uint32 *pix = static_cast<Uint32*>(textSurface->pixels);

			float *texturef = new float[numPixels * 4];

			for (int pidx = 0; pidx < numPixels; ++pidx)
			{
				Uint32 r = pix[pidx] & textSurface->format->Rmask;
				Uint32 g = pix[pidx] & textSurface->format->Gmask;
				Uint32 b = pix[pidx] & textSurface->format->Bmask;
				Uint32 a = pix[pidx] & textSurface->format->Amask;

				r = r >> textSurface->format->Rshift;
				g = g >> textSurface->format->Gshift;
				b = b >> textSurface->format->Bshift;
				a = a >> textSurface->format->Ashift;

				float ttuple[4] = {(float)r, 
					(float)g,
					(float)b,
					(float)a
				};

				ttuple[0]= floorf(100.0f * (ttuple[0] / 255.0f) + 0.5f) / 100.0f;
				ttuple[1]= floorf(100.0f * (ttuple[1] / 255.0f) + 0.5f) / 100.0f;
				ttuple[2]= floorf(100.0f * (ttuple[2] / 255.0f) + 0.5f) / 100.0f;
				ttuple[3]= floorf(100.0f * (ttuple[3] / 255.0f) + 0.5f) / 100.0f;

				memcpy(&texturef[pidx * 4], &ttuple, sizeof(ttuple));

			}

			textHandle = renderer->generateTexture(intToStr(size) + "text_" + text, texturef, textSurface->w, textSurface->h);

			delete[] texturef;
			texturef = NULL;
			SDL_FreeSurface(textSurface);
		}

		float boxVerts[16] =
		{
			topX, bottomY, -0.5f, 1.0f,
			bottomX, bottomY, -0.5f, 1.0f,
			bottomX, topY, -0.5f, 1.0f,
			topX, topY, -0.5f, 1.0f
		};

		renderer->renderImage(boxVerts, intToStr(size) + "text_" + text);		
	}

	void Text::deleteTextTexture( const string &text )
	{
		renderer->deleteTexture(intToStr(size) + "text_" + text);
	}

}
