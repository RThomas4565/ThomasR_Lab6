#include <iostream>
#include <SFML/Graphics.hpp>
using namespace sf;
using namespace std;

int main() {
    string background = "images1/backgrounds/winter.png";
    string foreground = "images1/characters/Rey_green_screen.png";

    Texture backgroundTex;
    if (!backgroundTex.loadFromFile(background)) {
        cout << "Couldn't Load Background Image" << endl;
        return 1;
    }

    Texture foregroundTex;
    if (!foregroundTex.loadFromFile(foreground)) {
        cout << "Couldn't Load Foreground Image" << endl;
        return 1;
    }

    RenderTexture renderTexture;
    renderTexture.create(1024, 768);

    Sprite backgroundSprite(backgroundTex);

    Sprite foregroundSprite(foregroundTex);

    Vector2u fgSize = foregroundTex.getSize();
    Image foregroundImage = foregroundTex.copyToImage();
    Image backgroundImage = backgroundTex.copyToImage();

    Color greenMin(0, 100, 0);
    Color greenMax(100, 255, 100);

    for (unsigned int y = 0; y < fgSize.y; y++) {
        for (unsigned int x = 0; x < fgSize.x; x++) {
            Color foregroundPixel = foregroundImage.getPixel(x, y);
            Color backgroundPixel = backgroundImage.getPixel(x, y);

            if (foregroundPixel.r >= greenMin.r && foregroundPixel.r <= greenMax.r &&
                foregroundPixel.g >= greenMin.g && foregroundPixel.g <= greenMax.g &&
                foregroundPixel.b >= greenMin.b && foregroundPixel.b <= greenMax.b) {

                foregroundImage.setPixel(x, y, backgroundPixel);
            }
        }
    }

    Texture modifiedForegroundTex;
    modifiedForegroundTex.loadFromImage(foregroundImage);
    Sprite modifiedForegroundSprite(modifiedForegroundTex);

    renderTexture.draw(backgroundSprite);
    renderTexture.draw(modifiedForegroundSprite);

    renderTexture.display();

    RenderWindow window(VideoMode(1024, 768), "Combined Image");

    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }
        }

        window.clear();
        Sprite combinedSprite(renderTexture.getTexture());
        window.draw(combinedSprite);
        window.display();
    }

    return 0;
}
//