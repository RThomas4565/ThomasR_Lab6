#include <iostream>
#include <SFML/Graphics.hpp>
using namespace sf;
using namespace std;

int main() {
    string background = "images1/backgrounds/winter.png";
    string foreground = "images1/characters/Rey_green_screen.png";

    // Load background and foreground textures
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

    // Create render texture to combine images
    RenderTexture renderTexture;
    renderTexture.create(1024, 768);

    // Create sprites for background and foreground
    Sprite backgroundSprite(backgroundTex);

    Sprite foregroundSprite(foregroundTex);

    // Get the size of the foreground image
        Vector2u fgSize = foregroundTex.getSize();

    // Create images from the foreground and background textures
    Image foregroundImage = foregroundTex.copyToImage();
    Image backgroundImage = backgroundTex.copyToImage();

    // Remove green pixels from the foreground based on the background
    Color greenMin(0, 100, 0); 
    Color greenMax(100, 255, 100); 

    for (unsigned int y = 0; y < fgSize.y; y++) {
        for (unsigned int x = 0; x < fgSize.x; x++) {
            Color foregroundPixel = foregroundImage.getPixel(x, y);
            Color backgroundPixel = backgroundImage.getPixel(x, y);

            // Check if the foreground pixel is green
            if (foregroundPixel.r < 50 && foregroundPixel.g > 200 && foregroundPixel.b < 50) {
                // Replace the foreground pixel with the corresponding background pixel
            if (foregroundPixel.r >= greenMin.r && foregroundPixel.r <= greenMax.r &&
                foregroundPixel.g >= greenMin.g && foregroundPixel.g <= greenMax.g &&
                foregroundPixel.b >= greenMin.b && foregroundPixel.b <= greenMax.b) {

                foregroundImage.setPixel(x, y, backgroundPixel);
            }
        }
    }

    // Load the modified foreground image into a texture
    Texture modifiedForegroundTex;
    modifiedForegroundTex.loadFromImage(foregroundImage);
    Sprite modifiedForegroundSprite(modifiedForegroundTex);

    // Draw background and modified foreground onto the render texture
    renderTexture.draw(backgroundSprite);
    renderTexture.draw(modifiedForegroundSprite);

    // Display the combined image
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