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
void mainDraw(sf::RenderWindow *window, Graph<std::string, float> *graph);
void createVertex(sf::Vector2i & position, Graph<std::string, float> *graph, sf::RenderWindow *window, std::string & inputData);

int main(){

    //Global Variables
    Graph<std::string, float> graph;
    sf::VideoMode desktop;
    sf::RenderWindow window;

    configureSFML(&desktop, &window);
    mainDraw(&window, &graph);

    return 0;
}

void configureSFML(sf::VideoMode *desktop, sf::RenderWindow *window){

    *desktop = sf::VideoMode::getDesktopMode();
    window->create(sf::VideoMode(1024, 768, desktop->bitsPerPixel), "Graphs");

}

void mainDraw(sf::RenderWindow *window, Graph<std::string, float> *graph){
    //Configure the background
    sf::Texture texture;
    if (!texture.loadFromFile("world.jpg"))
    {
        std::cout << "Error: loading the background image!" << '\n';
    }
    sf::Sprite background(texture);

    window->clear(sf::Color::White);
    // Set background to image
    window->draw(background);

    //Configure the font
    sf::Font font;
    font.loadFromFile("Akashi.ttf");

    // Configure the description object
    std::string textDescription;
    sf::Text description;
    description.setFont(font);
    description.setCharacterSize(24);
    description.setColor(sf::Color::Black);
    description.setPosition(sf::Vector2f(20, 10));

    // Configure the dataInput object
    sf::Text dataInput;
    dataInput.setFont(font);
    dataInput.setCharacterSize(18);
    dataInput.setColor(sf::Color::Black);
    dataInput.setPosition(sf::Vector2f(20, 52));

    textDescription = "Graphs";

    //Variable for accepting the input text
    bool createAVertex = false;

    //Variable for getting the position of the Mouse when clicked
    sf::Vector2i position;

    //Variable for getting the desired data for the new Vertex
    std::string inputData = "";

    while (window->isOpen())
    {
        description.setString(textDescription);
        dataInput.setString(inputData);

        sf::Event event;
        while (window->pollEvent(event))
        {
            switch (event.type){
                case sf::Event::Closed:
                    std::cout << "Window closed" << '\n';
                    window->close();
                    break;
                case sf::Event::MouseButtonReleased:
                {
                    /*if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
                        && Mouse::getPosition(window).x >= rect1.getPosition().x
                        && Mouse::getPosition(window).x <= rect1.getPosition().x + rect1.getSize().x
                        && Mouse::getPosition(window).y >= rect1.getPosition().y
                        && Mouse::getPosition(window).y <= rect1.getPosition().y + rect1.getSize().y)*/

                      // get the local mouse position (relative to window)
                      position = sf::Mouse::getPosition(*window);

                      // Change the text displayed
                      textDescription = "Enter the data for the Vertex: ";

                      // Toggle the boolean so it accepts input
                      createAVertex = true;
                }

                break;
                case sf::Event::TextEntered:
                    if ( createAVertex )
                    {
                        // it's a printable char
                        if ( event.text.unicode < 0x80 ) {
                            char letter = (char) event.text.unicode;
                            inputData += letter;
                        }
                        //Submit the entered text
                        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return)){
                            createVertex(position, graph, window, inputData);
                            createAVertex = false;
                            inputData = "";
                            textDescription = "Graphs";
                        }
                    }
                    break;
            }
        }

        //Rectangle for clearing the title
        sf::RectangleShape rec(sf::Vector2f(1024,80));
        rec.setPosition(0,0);
        rec.setFillColor(sf::Color::White);
        window->draw(rec);

        window->draw(description);
        window->draw(dataInput);

        window->display();

    }

}

void createVertex(sf::Vector2i & position, Graph<std::string, float> *graph, sf::RenderWindow *window, std::string & inputData){

    int x = position.x - 10;
    int y = position.y - 10;


    //Draw the vertex in the place pressed
    sf::CircleShape circle(10.f);
    circle.setFillColor(sf::Color(33,53,156));
    circle.setPosition(x,y);
    window->draw(circle);

    //Configure the font
    sf::Font font;
    font.loadFromFile("Akashi.ttf");

    //Draw its name next to it
    sf::Text name;
    name.setFont(font);
    name.setCharacterSize(12);
    name.setColor(sf::Color(33,53,156));
    name.setPosition(sf::Vector2f(x-5, y-15));
    name.setString(inputData);
    window->draw(name);

    //Rectangle for clearing the title
    sf::RectangleShape rec(sf::Vector2f(1024,80));
    rec.setPosition(0,0);
    rec.setFillColor(sf::Color::White);
    window->draw(rec);

    Vertex<std::string, float> * newVertex = new Vertex<std::string, float>(inputData);
    newVertex->setX(x);
    newVertex->setY(y);

    graph->addVertex(newVertex);

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
