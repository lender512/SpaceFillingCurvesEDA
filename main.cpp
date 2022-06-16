#include <stdint.h>
#include <vector>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
/*
★ ° . *　　　°　.　°☆ 　. * ● ¸ ★ ° . *　　　°　.　°☆ 　. * ● ¸ ★ ° . *　　　°　.　°☆ 　. * ● ¸ 
. 　　　★ 　° :. ★　 * • ○ ° ★　 . 　　　★ 　° :. ★　 * • ○ ° ★　 . 　　　★ 　° :. ★　 * • ○ ° ★　 
.　 * 　.　 　　　　　. 　 .　 * 　.　 　　　　　. 　 .　 * 　.　 　　　　　. 　 
° 　. ● . ★ ° . *　　　°　.　°☆ ° 　. ● . ★ ° . *　　　°　.　°☆ ° 　. ● . ★ ° . *　　　°　.　°☆ 
　. * ● ¸ . 　　　★ 　° :●. 　 * 　. * ● ¸ . 　　　★ 　° :●. 　 * 　. * ● ¸ . 　　　★ 　° :●. 　 * 
• ○ ° ★　 .　 * 　.　 　　　　　.• ○ ° ★　 .　 * 　.　 　　　　　.• ○ ° ★　 .　 * 　.　 　　　　　.

                                  ,-.       _,---._ __  / \
                                 /  )    .-'       `./ /   \
                                (  (   ,'            `/    /|
                                 \  `-"             \'\   / |
                                  `.              ,  \ \ /  |
                                   /`.          ,'-`----Y   |
                                  (            ;        |   '
                                  |  ,-.    ,-'  Eren   |  /
                                  |  | (   |  La Gaviota| /
                                  )  |  \  `.___________|/
                                  `--'   `--'
° 　. ● . ★ ° . *　　　°　.　 　 ° 　. ● . ★ ° . *　　　°　.　 　 ° 　. ● . ★ ° . *　　　°　.　
°☆ 　. * ● ¸ . 　　　★ 　°☆ 　. * ● ¸ . 　　　★ 　°☆ 　. * ● ¸ . 　　　★ 　
° :. 　 * • ○ ° ★　 .　 * 　.　 ° :. 　 * • ○ ° ★　 .　 * 　.　 ° :. 　 * • ○ ° ★　 .　 * 　.　 
　★　　　　. 　 ° 　.  . 　    ★　 　　　★　　　　. 　 ° 　.  . 　    ★　 　　　★　　　　. 　 ° 　
° °☆ 　¸. ● . 　　★　★ ° °☆ 　¸. ● . 　　★　★ ° °☆ 　¸. ● . 　　★　★ 
° . *　　　°　.　°☆ 　. * ● ¸ . ° . *　　　°　.　°☆ 　. * ● ¸ . ° . *　　　°　.　°☆ 　. * ● ¸ . 
★ ° . *　　　°　.　°☆ 　. * ● ¸ ★ ° . *　　　°　.　°☆ 　. * ● ¸ ★ ° . *　　　°　.　°☆ 　. * ● ¸ 
. 　　　★ 　° :. 　 * • ○ ° ★　 . 　　　★ 　° :. 　 * • ○ ° ★　 . 　　　★ 　° :. 　 * • ○ ° ★　 
.　 * 　.　 　★     ° :.☆.　 * 　.　 　★     ° :.☆.　 * 　.　 　★     ° :.☆
                        
Instrucciones:
    Usar 1, 2 y 3 para seleccinar el tipo de curva
    Usar + o - para modificar el factor de escalado (zoom)

Como correrlo:
    g++ -c main.cpp
    g++ main.o -o sfml-app -lsfml-graphics -lsfml-window -lsfml-audio -lsfml-system
    ./sfml-app

    O resumido:
    g++ -std=c++17 -g -c main.cpp &&  g++ -g main.o -o sfml-app -lsfml-graphics -lsfml-window -lsfml-audio -lsfml-system && ./sfml-app
*/

/*✿ஜீ۞ஜீ✿•.¸¸.•*`*•.•ஜீ☼۞☼ஜீ•.•*`*•.¸¸.•✿ஜீ۞ஜீ✿
Variables globales importantes
✿ஜீ۞ஜீ✿•.¸¸.•*`*•.•ஜீ☼۞☼ஜீ•.•*`*•.¸¸.•✿ஜீ۞ஜீ✿*/
int MAX_BITS = 32;
int scaling = 50;
uint32_t width = 850, height = 850;
sf::RenderWindow window(sf::VideoMode(width, height), "Space-Filling Curve");

/*✿ஜீ۞ஜீ✿•.¸¸.•*`*•.•ஜீ☼۞☼ஜீ•.•*`*•.¸¸.•✿ஜீ۞ஜீ✿
Funcion para calcular el ray code
✿ஜீ۞ஜீ✿•.¸¸.•*`*•.•ஜீ☼۞☼ஜீ•.•*`*•.¸¸.•✿ஜீ۞ஜீ✿*/
uint32_t gray_code(uint32_t n) {
    /* ｡☆✼★━━━━━━Se desplaza 1 bit hacia la derecha y se hace XOR━━━━━━★✼☆｡ */
	return n ^ (n >> 1);
}


/*✿ஜீ۞ஜீ✿•.¸¸.•*`*•.•ஜீ☼۞☼ஜீ•.•*`*•.¸¸.•✿ஜீ۞ஜீ✿
    La función intercalado usada para añadir
    un cero entre cada bit, para posteriormente
    sumar dos intercalados (con un defase) y tener
    el Z-order
✿ஜீ۞ஜீ✿•.¸¸.•*`*•.•ஜீ☼۞☼ஜீ•.•*`*•.¸¸.•✿ஜீ۞ஜீ✿*/
uint32_t intercalado(uint32_t coord) {
    /* ｡☆✼★━━━━━━El tamaño de partición se reduce a la mitad por iteración━━━━━━★✼☆｡ */
    for (uint32_t step = 16; step >= 1; step = step / 2) {

        /* ｡☆✼★━━━━━━Cada particion se parte a la mitad con (STEP/2) bits X entre ambos━━━━━━★✼☆｡ */
        uint32_t aux = coord << step; 
        coord |= aux;
        uint32_t sub_mask = (1 << step) - 1;
        uint32_t mask = 0;
		
        /* ｡☆✼★━━━━━━Se vuelven 0s los bits X que estan en el medio de las nuevas particiones━━━━━━★✼☆｡ */
        for (int a = 0; a < MAX_BITS; a = a + step) {
            mask |= sub_mask;
            mask = mask << (step*2);
        }
        mask |= sub_mask;
		
        coord &= mask;
    }
    return coord;
}
std::vector<sf::Vector2i> hilbert_vec;
//hilbert curve algorithm
void hilbert(float n, float x, float y, float xi, float xj, float yi, float yj) {
    if (n <= 0) {
        hilbert_vec.push_back({x + (xi + yi)/2, y + (xj + yj)/2});
    } else {
        hilbert(n - 1, x            , y,                yi/2, yj/2, xi/2, xj/2);
        hilbert(n - 1, x+xi/2       , y+xj/2,           xi/2, xj/2, yi/2, yj/2);
        hilbert(n - 1, x+xi/2+yi/2  , y+xj/2+yj/2,      xi/2, xj/2, yi/2, yj/2);
        hilbert(n - 1, x+xi/2+yi    , y+xj/2+yj,        -yi/2, -yj/2, -xi/2, -xj/2);
    }
}




/*✿ஜீ۞ஜீ✿•.¸¸.•*`*•.•ஜீ☼۞☼ஜீ•.•*`*•.¸¸.•✿ஜீ۞ஜீ✿
Estruct que representa un pixel, su coordenada
"x" y "y", junto a su transformada que será 
asignada dependiendo de la curva
✿ஜீ۞ஜீ✿•.¸¸.•*`*•.•ஜீ☼۞☼ஜீ•.•*`*•.¸¸.•✿ஜீ۞ஜீ✿*/
struct Pixel {
	uint32_t x;
	uint32_t y;
    uint32_t transform;
};

std::vector<Pixel> vec;

enum Type {GRAY, DOUBLE_GRAY, Z_ORDER};

/*✿ஜீ۞ஜீ✿•.¸¸.•*`*•.•ஜீ☼۞☼ஜீ•.•*`*•.¸¸.•✿ஜீ۞ஜீ✿
Funcion que se llamará para pinter las lineas
pertinentes a la curva que se haya seleccionado
✿ஜீ۞ஜீ✿•.¸¸.•*`*•.•ஜீ☼۞☼ஜீ•.•*`*•.¸¸.•✿ஜீ۞ஜீ✿*/
void draw_curve(Type type) {
    vec.clear();
    for (uint32_t i = 0; i < width/scaling - 1; i++) {
        for (uint32_t j = 0; j < height/scaling -1; j++) {
            /*✿ஜீ۞ஜீ✿•.¸¸.•*`*•.•ஜீ☼۞☼ஜீ•.•*`*•.¸¸.•✿ஜீ۞ஜீ✿
            Switch para determinar el tipo de curva que se
            se va a dibujar
            ✿ஜீ۞ஜீ✿•.¸¸.•*`*•.•ஜீ☼۞☼ஜீ•.•*`*•.¸¸.•✿ஜீ۞ஜீ✿*/
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

    /*✿ஜீ۞ஜீ✿•.¸¸.•*`*•.•ஜீ☼۞☼ஜீ•.•*`*•.¸¸.•✿ஜீ۞ஜீ✿
    Se ordenan los futuros puntos segun el valor
    que les asignó la curva.
    ✿ஜீ۞ஜீ✿•.¸¸.•*`*•.•ஜீ☼۞☼ஜீ•.•*`*•.¸¸.•✿ஜீ۞ஜீ✿*/
    std::sort(vec.begin(), vec.end(), [] (Pixel& a, Pixel& b) {return a.transform < b.transform;});

    /*✿ஜீ۞ஜீ✿•.¸¸.•*`*•.•ஜீ☼۞☼ஜீ•.•*`*•.¸¸.•✿ஜீ۞ஜீ✿
    Se pintanlas lineas
    ✿ஜீ۞ஜீ✿•.¸¸.•*`*•.•ஜீ☼۞☼ஜீ•.•*`*•.¸¸.•✿ஜீ۞ஜீ✿*/
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
/*✿ஜீ۞ஜீ✿•.¸¸.•*`*•.•ஜீ☼۞☼ஜீ•.•*`*•.¸¸.•✿ஜீ۞ஜீ✿
Se define el tipo de curva por defecto 
✿ஜீ۞ஜீ✿•.¸¸.•*`*•.•ஜீ☼۞☼ஜீ•.•*`*•.¸¸.•✿ஜீ۞ஜீ✿*/
Type current_type = GRAY;

int main() {
    hilbert_vec = std::vector<sf::Vector2i>();
    int n = 6;
    hilbert(n, 0, 0, width, 0, 0, height);
    std::cout << hilbert_vec.size() << std::endl;
    // draw_curve(current_type);
    for (int i = 0; i < hilbert_vec.size()-1; i++) {
        sf::Vertex line1[] = {
            sf::Vertex(sf::Vector2f(hilbert_vec[i].x, hilbert_vec[i].y), sf::Color(0, 255, 0)),
            sf::Vertex(sf::Vector2f(hilbert_vec[i + 1].x, hilbert_vec[i + 1].y), sf::Color(0, 255, 0))
        };
        window.draw(line1, 2, sf::Lines);
    }
    window.display();

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close window: exit
            if (event.type == sf::Event::Closed)
                window.close();
        }


    }

}