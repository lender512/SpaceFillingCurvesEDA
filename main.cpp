#include <stdint.h>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
/*
g++ -c main.cpp
g++ main.o -o sfml-app -lsfml-graphics -lsfml-window -lsfml-audio -lsfml-system
./sfml-app

g++ -std=c++17 -g -c main.cpp &&  g++ -g main.o -o sfml-app -lsfml-graphics -lsfml-window -lsfml-audio -lsfml-system && ./sfml-app
*/


int MAX_BITS = 32;

int scaling = 50;
uint32_t width = 850, height = 850;
sf::RenderWindow window(sf::VideoMode(width - 2*scaling, height - 2*scaling), "Space-Filling Curve");

uint32_t gray_code(uint32_t n) {
	return n ^ (n >> 1);
}

uint32_t intercalado(uint32_t coord) {
    for (uint32_t step = 16; step >= 1; step = step / 2) {
        uint32_t aux = coord << step;
        coord |= aux;
        uint32_t sub_mask = (1 << step) - 1;
        uint32_t mask = 0;
		
        for (int a = 0; a < MAX_BITS; a = a + step) {
            mask |= sub_mask;
            mask = mask << (step*2);
        }
        mask |= sub_mask;
		
        coord &= mask;
    }
    return coord;
}

struct Pixel {
	uint32_t x;
	uint32_t y;
    uint32_t z_order;
};

std::vector<Pixel> vec;

enum Type {GRAY, DOUBLE_GRAY, Z_ORDER};

void draw_curve(Type type) {
    vec.clear();
    for (uint32_t i = 0; i < width/scaling - 1; i++) {
        for (uint32_t j = 0; j < height/scaling -1; j++) {
            switch (type)
            {
            case GRAY:
                vec.push_back({ i, j, gray_code(intercalado(i) | (intercalado(j) << 1)) });
                break;
            
            case DOUBLE_GRAY:
                vec.push_back({ i, j, gray_code(intercalado(gray_code(i)) | (intercalado(gray_code(j)) << 1)) });
                break;
            
            case Z_ORDER:
                vec.push_back({ i, j, intercalado(i) | (intercalado(j) << 1) });
                break;
            
            }
        }
    }

    std::sort(vec.begin(), vec.end(), [] (Pixel& a, Pixel& b) {return a.z_order < b.z_order;});


    for (int i = 0; i < vec.size()-1; i++) {
        sf::Color color(0, 255, 255);
        sf::Vertex line1[] = {
            sf::Vertex(sf::Vector2f(vec[i].x* scaling, vec[i].y * scaling), color),
            sf::Vertex(sf::Vector2f(vec[i + 1].x * scaling, vec[i + 1].y * scaling), color)
        };
        window.draw(line1, 2, sf::Lines);
        // sf::sleep(sf::milliseconds(100));
        // window.display();
    }
}

Type current_type = GRAY;

int main() {
    draw_curve(current_type);
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type){
                case sf::Event::Closed:
                {
                    window.close();
                    return 0;
                }
                case sf::Event::KeyPressed:
                {
                    switch (event.key.code)
                    {
                        case sf::Keyboard::Add:
                        {
                            if (!(scaling-1000)) break;
                            scaling++;
                            window.clear();
                            draw_curve(current_type);
                            break;
                        }
                        case sf::Keyboard::Subtract:
                        {
                            if (scaling < 5) break;
                            scaling--;
                            window.clear();
                            draw_curve(current_type);
                            break;
                        }
                    }
                    break;
                }
                case sf::Event::KeyReleased:
                {
                    switch (event.key.code)
                    {
                        case sf::Keyboard::Num1:
                        {
                            if (current_type == GRAY) break;
                            current_type = GRAY;
                            window.clear();
                            draw_curve(current_type);
                            break;
                        }
                        case sf::Keyboard::Num2:
                        {
                            if (current_type == DOUBLE_GRAY) break;
                            current_type = DOUBLE_GRAY;
                            window.clear();
                            draw_curve(current_type);
                            break;
                        }
                        case sf::Keyboard::Num3:
                        {
                            if (current_type == Z_ORDER) break;
                            current_type = Z_ORDER;
                            window.clear();
                            draw_curve(current_type);
                            break;
                        }
                        break;                        
                    }
                }
                
            }
        }
        window.display();

    }

}