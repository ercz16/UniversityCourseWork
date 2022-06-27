#include <iostream>
#include <fstream>
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <string>

#include "TextureManager.h"
#include "Random.h"
#include "Tile.h"

using std::cout;
using std::endl;
using std::ifstream;
using std::string;

int main()
{
    sf::RenderWindow window(sf::VideoMode(1500, 1000), "Minesweeper");

    // Load Sprites
    unordered_map<string, sf::Sprite> sprites;
    sf::Sprite sprite;

    sprite.setTexture(TextureManager::GetTexture("tile_hidden"));
    sprites["tile_hidden"] = sprite;

    sprite.setTexture(TextureManager::GetTexture("tile_revealed"));
    sprites["tile_revealed"] = sprite;

    sprite.setTexture(TextureManager::GetTexture("debug"));
    sprite.setTextureRect(sf::IntRect(0, 0, 64, 64));
    sprites["debug"] = sprite;

    sprite.setTexture(TextureManager::GetTexture("number_1"));
    sprites["number_1"] = sprite;

    sprite.setTexture(TextureManager::GetTexture("number_2"));
    sprites["number_2"] = sprite;

    sprite.setTexture(TextureManager::GetTexture("number_3"));
    sprites["number_3"] = sprite;

    sprite.setTexture(TextureManager::GetTexture("number_4"));
    sprites["number_4"] = sprite;

    sprite.setTexture(TextureManager::GetTexture("number_5"));
    sprites["number_5"] = sprite;

    sprite.setTexture(TextureManager::GetTexture("number_6"));
    sprites["number_6"] = sprite;

    sprite.setTexture(TextureManager::GetTexture("number_7"));
    sprites["number_7"] = sprite;

    sprite.setTexture(TextureManager::GetTexture("number_8"));
    sprites["number_8"] = sprite;

    sprite.setTexture(TextureManager::GetTexture("mine"));
    sprites["mine"] = sprite;

    sprite.setTexture(TextureManager::GetTexture("test_1"));
    sprite.setTextureRect(sf::IntRect(0, 0, 64, 64));
    sprites["test_1"] = sprite;

    sprite.setTexture(TextureManager::GetTexture("test_2"));
    sprite.setTextureRect(sf::IntRect(0, 0, 64, 64));
    sprites["test_2"] = sprite;

    sprite.setTexture(TextureManager::GetTexture("test_3"));
    sprite.setTextureRect(sf::IntRect(0, 0, 64, 64));
    sprites["test_3"] = sprite;

    sprite.setTexture(TextureManager::GetTexture("face_win"));
    sprite.setTextureRect(sf::IntRect(0, 0, 64, 64));
    sprites["face_win"] = sprite;

    sprite.setTexture(TextureManager::GetTexture("face_happy"));
    sprite.setTextureRect(sf::IntRect(0, 0, 64, 64));
    sprites["face_happy"] = sprite;

    sprite.setTexture(TextureManager::GetTexture("face_lose"));
    sprite.setTextureRect(sf::IntRect(0, 0, 64, 64));
    sprites["face_lose"] = sprite;

    sprite.setTexture(TextureManager::GetTexture("digits"));
    sprites["digits"] = sprite;

    sprite.setTexture(TextureManager::GetTexture("flag"));
    sprites["flag"] = sprite;

    Board b("testboard1.brd");
    b.initAdjTiles();
    b.initNumMines();
    //b.printNumMines();

    // Config
    int w = 32; 
    int w2 = w * 2;

    while (window.isOpen())
    {

        // Check for win
        b.checkWin();

        sf::Vector2i pos = sf::Mouse::getPosition(window);
        int x = pos.x / w;
        int y = pos.y / w;

        int x2 = pos.x / w2;
        int y2 = pos.y / w2;

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    if (x < b.getCols() && y < b.getRows() && 
                        b.getState() == "pending") {
                        b.leftClick(y, x);
                    }
                    else if (b.getState() == "pending" && x2 == 0 && y >= b.getRows() && y <= b.getRows()+1) {
                        b.debug();
                    }
                    else if (x2 == 1 && y >= b.getRows() && y <= b.getRows()+1) {
                        b = Board("testboard1.brd");
                        b.initAdjTiles();
                        b.initNumMines();
                    }
                    else if (x2 == 2 && y >= b.getRows() && y <= b.getRows()+1) {
                        b = Board("testboard2.brd");
                        b.initAdjTiles();
                        b.initNumMines();
                    }
                    else if (x2 == 3 && y >= b.getRows() && y <= b.getRows()+1) {
                        b = Board("testboard3.brd");
                        b.initAdjTiles();
                        b.initNumMines();
                    }
                    else if (x2 == 4 && y >= b.getRows() && y <= b.getRows()+1) {
                        b.reset();
                    }
                } else if (event.mouseButton.button == sf::Mouse::Right && 
                           x < b.getCols() && y < b.getRows() && 
                           b.getState() == "pending") {
                    b.rightClick(y, x);
                }
            }
        }

        window.clear(sf::Color::White);
        sf::Sprite overLay(TextureManager::GetTexture("tile_hidden"));

        for(unsigned int i = 0; i < b.getRows(); ++i) {
            for(unsigned int j = 0; j < b.getCols(); ++j) {

                Tile tile = b.getTile(i, j);

                if (tile.isRevealed()) {
                    sprite = sprites["tile_revealed"];
                    int N = tile.getAdjMines();
                    if (tile.isMine()) {
                        overLay = sprites["mine"];
                        overLay.setPosition(j * w, i * w);
                    }
                    else if (N != 0) {
                        overLay = sprites["number_" + std::to_string(N)];
                        overLay.setPosition(j * w, i * w);
                    }
                    else {
                        overLay = sprites["tile_revealed"];
                        overLay.setPosition(j * w, i * w);
                    }
                }
                else {
                    if (tile.isFlagged()) {
                        overLay = sprites["flag"];
                        overLay.setPosition(j * w, i * w);
                    }
                    sprite = sprites["tile_hidden"];
                }

                sprite.setPosition(j * w, i * w);

                window.draw(sprite);
                window.draw(overLay);
            }
        }

        sf::Sprite item = sprites["debug"];
        item.setPosition(0, b.getRows() * w);
        window.draw(item);

        item = sprites["test_1"];
        item.setPosition(w2, b.getRows() * w);
        window.draw(item);

        item = sprites["test_2"];
        item.setPosition(2 * w2, b.getRows() * w);
        window.draw(item);

        item = sprites["test_3"];
        item.setPosition(3 * w2, b.getRows() * w);
        window.draw(item);

        if(b.getState() == "pending") item = sprites["face_happy"];
        else if(b.getState() == "win") item = sprites["face_win"];
        else if (b.getState() == "lose") item = sprites["face_lose"];
        item.setPosition(4 * w2, b.getRows() * w);
        window.draw(item);

        item = sprites["digits"];
        int N = b.getNumMines() - b.getNumFlags();
        bool negative = false;
        if (N < 0) {
            N *= -1;
            negative = true;
        }
        int digits[3];
        digits[0] = N / 100;
        N %= 100;
        digits[1] = N / 10;
        N %= 10;
        digits[2] = N;

        if(negative) {
            item.setTextureRect(sf::IntRect(10*21, 0, 21, 32));
            item.setPosition((5 * w2) + 43, b.getRows() * w);
            window.draw(item);
        }
        for(int i = 0; i < 3; ++i) {
            int pix = digits[i] * 21;
            item.setTextureRect(sf::IntRect(pix, 0, 21, 32));
            item.setPosition((6 * w2) + i * 21, b.getRows() * w);
            window.draw(item);
        }

        window.display();
    }

    TextureManager::Clear();
    return 0;
}
