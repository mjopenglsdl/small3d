/*
 *  Text.hpp
 *
 *  Created on: 2014/11/23
 *      Author: Dimitri Kourkoulis
 *              http://dimitros.be
 *     License: BSD 3-Clause License (see LICENSE file)
 */

// bii://dimitrikourk/small3d/samplegame/resources/fonts/CrusoeText/CrusoeText-Regular.ttf

#include <string>
#include "Renderer.hpp"
#include <memory>
#include <miguel/sdl2_ttf/SDL_ttf.h>

using namespace std;

#pragma once

extern bool ttfInitialised;

namespace small3d {

  string intToStr(int number);

  /**
   * @struct	Text
   *
   * @brief	Structure for rendering text
   *
   */

  struct Text {
  private:
    shared_ptr<Renderer> renderer;

    TTF_Font *font;
    int size;

  public:

    /**
     * @fn	Text( shared_ptr<Renderer> renderer,
     * 		const string &ttfFontPath="dimitrikourk/small3d/samplegame/resources/fonts/CrusoeText/CrusoeText-Regular.ttf",
     * 		const int &size = 48);
     *
     * @brief	Constructor.
     *
     * @param	renderer   	The renderer to be used.
     * @param	ttfFontPath	(optional) The path to the TrueType font to be used by the Renderer,
     * 						including its filename. It defaults to the font provided
     * 						by the engine but, even if the same one is used for an
     * 						game, most probably the path to where it is placed
     * 						will need to be specified here. Only one font can be used
     * 						by the engine at present but that will change in the near
     * 						future.
     * @param	size	   	(optional) the size of the font in the created images. It defaults
     * 						to 48.
     */

    Text(
	 shared_ptr<Renderer> renderer,
	 const string &ttfFontPath="dimitrikourk/small3d/samplegame/resources/fonts/CrusoeText/CrusoeText-Regular.ttf",
	 const int &size = 48);

    /**
     * @fn	~Text();
     *
     * @brief	Destructor.
     *
     */

    ~Text();

    /**
     * Render some text on the screen. A texture will be generated, containing the given
     * text and it will be rendered at a depth z of 0.5 in an orthographic coordinate space.
     * @param text The text to be rendered
     * @param colour The colour in which the text will be rendered
     * @param topX The top x coordinate of the text rectangle
     * @param topY The top y coordinate of the text rectangle
     * @param bottomX The bottom x coordinate of the text rectangle
     * @param bottomY The bottom y coordinate of the text rectangle
     */
    void renderText(const string &text, const SDL_Color &colour,
		    const float &topX, const float &topY, const float &bottomX, const float &bottomY);

    /**
     * @fn	void deleteTextTexture(const string &text);
     *
     * @brief	Deletes a texture, generated for text rendering, from the GPU and
     * 			from the renderer's map of textures
     *
     * @param	text	The text for which the texture has been generated.
     */

    void deleteTextTexture(const string &text);

  };
}
