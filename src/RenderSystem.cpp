#include <iostream>

#include "RenderSystem.h"

RenderSystem::RenderSystem(SDL_Renderer* renderer): renderer(renderer) {}

void RenderSystem::draw_text(const std::string& text, int x, int y, TTF_Font* font, SDL_Color color, int wrapLength) {
    /**
     * Render text to the screen at a given position with a given color and font
     *
     * @param color: The color of the text
     * @param x: The x position of the text
     * @param y: The y position of the text
     * @param font: The font to use for the text
     * @param text: The text to render
     * @param wrapLength: The length to wrap the text at
     */

    // Set up the surface for the text
    SDL_Surface* textSurface = TTF_RenderUTF8_Blended_Wrapped(font, text.c_str(), color, wrapLength);
    if (textSurface == nullptr) {
        std::cout << "Unable to render text surface! SDL_ttf Error: " << TTF_GetError() << std::endl;
        return;
    }

    // Set up the texture for the text
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    if (textTexture == nullptr) {
        std::cout << "Unable to create texture from rendered text! SDL Error: " << SDL_GetError() << std::endl;
        return;
    }

    // Get the width and height of the text then free the surface
    int textWidth = textSurface->w;
    int textHeight = textSurface->h;
    SDL_FreeSurface(textSurface);

    // Set the position of the text then create a rectangle to render the text to
    SDL_Rect renderQuad = {x, y, textWidth, textHeight};

    // Copy the texture to the renderer then destroy the texture
    SDL_RenderCopy(renderer, textTexture, nullptr, &renderQuad);
    SDL_DestroyTexture(textTexture);
}