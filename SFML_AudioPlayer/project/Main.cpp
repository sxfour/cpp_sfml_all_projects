#include "Main.h"
#include "Audio.h"
#include "Visualizer.h"

int main()
{
    srand(time(NULL));

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    sf::RenderWindow window(sf::VideoMode(1280, 720), "Audio Player with Visual", sf::Style::Default, settings);
    
    window.setFramerateLimit(60);

    Audio audio = Audio();
    std::thread frequencyAnalyzation(&Audio::getSampleOverFrequency, &audio);

    Visualizer visualizer = Visualizer();

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            switch (event.type) {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::KeyPressed:
                if (event.key.code == sf::Keyboard::Escape) {
                    window.close();
                    break;
                }
                else if (event.key.code == sf::Keyboard::P) {
                    audio.pauseSong();
                }
                else if (event.key.code == sf::Keyboard::O) {
                    audio.playSong();
                }
            }
            
        }

        window.clear(sf::Color::Black);

        if (audio.getfrequencyVisualizationVector().size() > 120) {
            visualizer.update(audio.getfrequencyVisualizationVector(), audio.getSongPlayingOffset());

            std::vector<sf::RectangleShape> freqRangeRects = visualizer.getFreqRangeRects();
            for (int i = 0; i < freqRangeRects.size(); i++) {
                window.draw(freqRangeRects[i]);
            }

            if (!audio.songPlayed())  {
                audio.playSong();
            }
        }
        window.display();
    }
    
    return 0;
}