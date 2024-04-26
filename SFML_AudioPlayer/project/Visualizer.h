#pragma once

class Visualizer {
public:
	Visualizer() {
		for (int ranges = 0; ranges < 64; ranges++) {
			sf::RectangleShape freqRangeRect = sf::RectangleShape();
			freqRangeRect.setSize(sf::Vector2f(2, 0));
			freqRangeRect.setPosition(0.f + (20 * ranges), 650.f);

			freqRangeRect.setFillColor(sf::Color::White);

			freqRangeRects.push_back(freqRangeRect);
		}

	}

	std::vector<sf::RectangleShape>& getFreqRangeRects() {
		return freqRangeRects;
	}

	void update(std::vector<std::vector<double>>& frequencyVisualizationVector, double songPlayingOffset) {
		frequencyFrame = (int)(songPlayingOffset * 30);

		for (int rect_i = 0; rect_i < freqRangeRects.size(); rect_i++) {
			float rectHeight = freqRangeRects[rect_i].getSize().y;
			float newRectHeight;

			if (frequencyFrame < frequencyVisualizationVector.size()) {
				newRectHeight = frequencyVisualizationVector[frequencyFrame][rect_i] * -1;
			}
			else {
				newRectHeight = rectHeight;
			}

			freqRangeRects[rect_i].setSize(sf::Vector2f(16, newRectHeight));
		}
	}


private:
	int frequencyFrame = 0;

	std::vector<sf::RectangleShape> freqRangeRects;

	sf::RectangleShape backgroundRect;
};