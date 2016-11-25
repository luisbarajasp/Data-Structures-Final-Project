/*
    Final Project: Graphs in SFML
    Luis Barajas
    Mauricio Rico
    Data Structures
    30/11/16
    A01370934@itesm.mx
    A01370874@itesm.mx
*/


#include <SFML/Graphics.hpp>
#include <iostream>
#include "Graph.hpp"

void configureSFML(sf::VideoMode *desktop, sf::RenderWindow *window);
void mainDraw(sf::RenderWindow *window);

int main(){

    //Global Variables
    Graph<std::string, float> graph;
    sf::VideoMode desktop;
    sf::RenderWindow window;

    configureSFML(&desktop, &window);
    mainDraw(&window);

    return 0;
}

void configureSFML(sf::VideoMode *desktop, sf::RenderWindow *window){

    *desktop = sf::VideoMode::getDesktopMode();
    window->create(sf::VideoMode(1024, 768, desktop->bitsPerPixel), "Graphs");

}

void mainDraw(sf::RenderWindow *window){

    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);
    sf::Vector2f v(100,200);
    sf::RectangleShape recShape(v);
    recShape.setFillColor(sf::Color::Green);

    while (window->isOpen())
    {
        sf::Event event;
        while (window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window->close();
        }

        // Set background to white
        window->clear(sf::Color::White);
        window->draw(shape);
	    window->draw(recShape);
        window->display();

    }

}

/* Graph<std::string, float> graph;
Vertex<std::string, float> * vertex;
std::string cities[] = {"Mexico", "Guadalajara", "Puebla", "Queretaro", "Cuernavaca", "Veracruz", "Villahermosa", "Acapulco"};
int num_cities = sizeof cities / sizeof cities[0];
LinkedList<Vertex<std::string, float> *> * path = nullptr;

for (int i=0; i<num_cities; i++)
{
    vertex = new Vertex<std::string, float>(cities[i]);
    graph.addVertex(vertex);
}

graph.setStart("Mexico");
graph.addEdge("Mexico", "Puebla", 2.8);
graph.addEdge("Puebla", "Veracruz", 8.2);
graph.addEdge("Veracruz", "Villahermosa", 5.2);
graph.addEdge("Guadalajara", "Queretaro", 0.7);
graph.addEdge("Mexico", "Cuernavaca", 6.8);
graph.addEdge("Cuernavaca", "Acapulco", 6.8);
graph.addEdge("Mexico", "Guadalajara", 3.2);
graph.addEdge("Queretaro", "Mexico", 2.1);
graph.addEdge("Queretaro", "Acapulco", 5.1);

graph.printBreadthFirst();
graph.printDepthFirst();

path = graph.findPath("Mexico", "Villahermosa");
std::cout << "Resulting path (Mexico to villahermosa):" << std::endl << "\t";
graph.printPath(path);
delete path; */
