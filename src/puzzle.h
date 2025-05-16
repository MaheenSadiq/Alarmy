Puzzle.h:

#pragma once

#include"alarm.h"

const int noofpieces = 12;
const int WindowWidth = 800;
const int WindowHeight = 500;
class JigsawPuzzle
{
private:


    sf::Texture puzzletexture[noofpieces];
    sf::Sprite puzzlepieces[noofpieces];
    sf::Vector2f offset;
    bool isdragging;
    int selectedpieceindex;
    sf::Vector2f puzzlePositions[noofpieces];

public:


    JigsawPuzzle()
    {
        isdragging = false;
        selectedpieceindex = -1;
        const float PuzzleSize = 150.f;

        puzzlePositions[0] = sf::Vector2f(100, 100);
        puzzlePositions[1] = sf::Vector2f(450, 100);
        puzzlePositions[2] = sf::Vector2f(800, 100);
        puzzlePositions[3] = sf::Vector2f(100, 350);
        puzzlePositions[4] = sf::Vector2f(450, 350);
        puzzlePositions[5] = sf::Vector2f(800, 350);
        puzzlePositions[6] = sf::Vector2f(100, 600);
        puzzlePositions[7] = sf::Vector2f(450, 600);
        puzzlePositions[8] = sf::Vector2f(800, 600);
        puzzlePositions[9] = sf::Vector2f(200, 200);
        puzzlePositions[10] = sf::Vector2f(650, 200);
        puzzlePositions[11] = sf::Vector2f(350, 500);
        for (int i = 0; i < noofpieces; i++)
        {
            puzzletexture[i].loadFromFile("piece" + std::to_string(i) + ".png");
            puzzlepieces[i].setTexture(puzzletexture[i]);
            puzzlepieces[i].setScale(PuzzleSize / puzzletexture[i].getSize().x, PuzzleSize / puzzletexture[i].getSize().y);
            puzzlepieces[i].setPosition(puzzlePositions[i]);
        }
    }


       void onMouseButtonPressed(const sf::Event::MouseButtonEvent & event)
        {
            if (event.button == sf::Mouse::Left)
            {
                sf::Vector2f mousePos(event.x, event.y);

                for (int i = 0; i < noofpieces; i++)
                {
                    if (puzzlepieces[i].getGlobalBounds().contains(mousePos))
                    {
                        isdragging = true;
                        selectedpieceindex = i;
                        offset = mousePos - puzzlepieces[i].getPosition();
                    }
                }
            }
       }


       const sf::Sprite& getPuzzlePiece(int index) const
        {
            if (index >= 0 && index < noofpieces)
            {
                return puzzlepieces[index];
            }
            else
            {

                static sf::Sprite defaultSprite;
                return defaultSprite;
            }
       }

        void onMouseButtonReleased(sf::Event::MouseButtonEvent & event)
        {
            if (event.button == sf::Mouse::Left)
            {
                isdragging = false;
                selectedpieceindex = -1;
            }
        }

         void onMouseMoved(const sf::Event::MouseMoveEvent & event)
         {
            if (isdragging && selectedpieceindex >= 0 && selectedpieceindex < noofpieces)
            {
                sf::Vector2f mousePos(event.x, event.y);
                puzzlepieces[selectedpieceindex].setPosition(mousePos - offset);
            }
         }



        void draw(sf::RenderWindow & window)
        {
            for (int i = 0; i < noofpieces; i++)
                window.draw(puzzlepieces[i]);
        }

};
