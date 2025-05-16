#include "Puzzle.h"
#include "alarm.h"


int main()
{
    Display d;
    d.dis();


   sf::RenderWindow window(sf::VideoMode(WindowWidth, WindowHeight), "Jigsaw Puzzle");
    JigsawPuzzle puzzle;

   
        while (window.isOpen())
        {
            sf::Event event;
            while (window.pollEvent(event))
            {
                switch (event.type)
                {
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::MouseButtonPressed:
                    for (int i = 0; i < noofpieces; i++)
                    {
                        puzzle.getPuzzlePiece(i);
                        puzzle.onMouseButtonPressed(event.mouseButton);
                    }
                    break;
                case sf::Event::MouseButtonReleased:
                    puzzle.onMouseButtonReleased(event.mouseButton);
                    break;
                case sf::Event::MouseMoved:
                    for (int i = 0; i < noofpieces; i++)
                    {
                        puzzle.onMouseMoved(event.mouseMove);
                    }
                    break;
                default:
                    break;
                }

                window.clear();
                puzzle.draw(window);
                window.display();
            }
        }



    return 0;
}
