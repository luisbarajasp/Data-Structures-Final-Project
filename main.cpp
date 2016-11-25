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
void createVertex(sf::Vector2i & position, Graph<std::string, float> *graph, sf::RenderWindow *window, std::string & textUserInteraction);
void getClickedVertex(sf::RenderWindow *window, Graph<std::string, float> *graph, sf::Vector2i & position);

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

    //Rectangle for the background in the title
    sf::RectangleShape rec(sf::Vector2f(1024,80));
    rec.setPosition(0,0);
    rec.setFillColor(sf::Color::White);

    // Configure the countriesNumber object
    std::string textCountriesNumber;
    sf::Text countriesNumber;
    countriesNumber.setFont(font);
    countriesNumber.setCharacterSize(24);
    countriesNumber.setColor(sf::Color::Black);
    countriesNumber.setPosition(sf::Vector2f(20, 10));

    // Configure the userInteraction object
    std::string textUserInteraction = "";
    sf::Text userInteraction;
    userInteraction.setFont(font);
    userInteraction.setCharacterSize(18);
    userInteraction.setColor(sf::Color::Black);
    userInteraction.setPosition(sf::Vector2f(20, 52));

    //Configure button for path
    //Background for the button
    sf::RectangleShape pathBackground(sf::Vector2f(130,35));
    pathBackground.setPosition(825,25);
    pathBackground.setFillColor(sf::Color::Black);
    //text for the button
    sf::Text pathBtnTitle;
    pathBtnTitle.setFont(font);
    pathBtnTitle.setCharacterSize(16);
    pathBtnTitle.setColor(sf::Color::White);
    pathBtnTitle.setPosition(850,32);
    pathBtnTitle.setString("New Path");

    textCountriesNumber = "There are " + std::to_string(graph->getVerticesLength()) + " countries.";
    textUserInteraction = "Click wherever you want a new country or click the button path";

    //Variables for accepting & assigning the input text
    bool createAVertex = false;
    bool createAnEdge = false;

    //Variable for getting the position of the Mouse when clicked
    sf::Vector2i position;

    while (window->isOpen())
    {
        countriesNumber.setString(textCountriesNumber);
        userInteraction.setString(textUserInteraction);

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
                    //Check if the click is in the title bar
                    if (sf::Mouse::getPosition(*window).y <= 80){
                        //Check if button path was clicked
                        if(sf::Mouse::getPosition(*window).x >= pathBackground.getPosition().x
                            && sf::Mouse::getPosition(*window).x <= pathBackground.getPosition().x + pathBackground.getSize().x
                            && sf::Mouse::getPosition(*window).y >= pathBackground.getPosition().y
                            && sf::Mouse::getPosition(*window).y <= pathBackground.getPosition().y + pathBackground.getSize().y){
                                std::cout << "Path clicked!" << '\n';
                            }
                    }else{

                        // get the local mouse position (relative to window)
                        position = sf::Mouse::getPosition(*window);

                        // Change the text displayed
                        textCountriesNumber = "Enter the data for the Vertex: ";
                        textUserInteraction = "";
                        // Toggle the boolean so it accepts input
                        createAVertex = true;

                    }

                }

                break;
                case sf::Event::TextEntered:
                    if ( createAVertex ){
                        //Delete the last character
                        if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace)){
                            if(textUserInteraction.length() > 0){
                                textUserInteraction.pop_back();
                            }
                        }else
                        // it's a printable char
                        if ( event.text.unicode < 0x80 ) {
                            char letter = (char) event.text.unicode;
                            textUserInteraction += letter;
                        }
                        //Submit the entered text
                        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return)){
                            createVertex(position, graph, window, textUserInteraction);
                            createAVertex = false;
                            createAnEdge = true;
                            //textCountriesNumber = "There are " + std::to_string(graph->getVerticesLength()) + " countries.";
                            //textUserInteraction = "Click wherever you want a new country or click the button path";
                            textCountriesNumber = "Select the countries to make a connection"
                            textUserInteraction = "Press escape when you are finished"
                        }
                    }else if (createAnEdge){
                        
                    }
                    break;
            }
        }
        //Draw title section
        window->draw(rec);

        window->draw(countriesNumber);
        window->draw(userInteraction);

        window->draw(pathBackground);
        window->draw(pathBtnTitle);

        window->display();

    }

}
//Method fofr creating and drawing a new vertex
void createVertex(sf::Vector2i & position, Graph<std::string, float> *graph, sf::RenderWindow *window, std::string & textUserInteraction){

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
    name.setString(textUserInteraction);
    window->draw(name);

    //Rectangle for clearing the title
    sf::RectangleShape rec(sf::Vector2f(1024,80));
    rec.setPosition(0,0);
    rec.setFillColor(sf::Color::White);
    window->draw(rec);

    Vertex<std::string, float> * newVertex = new Vertex<std::string, float>(textUserInteraction);
    newVertex->setX(x);
    newVertex->setY(y);

    graph->addVertex(newVertex);

}
// Method for getting the clicked Vertex
void getClickedVertex(sf::RenderWindow *window, Graph<std::string, float> *graph, sf::Vector2i & position){

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
