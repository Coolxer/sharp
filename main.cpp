#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <fstream>



using namespace std;

/////const infos///////////////

const int width = sf::VideoMode::getDesktopMode().width;
const int height = sf::VideoMode::getDesktopMode().height;

const int fps = 60;

float diameter, holeDiameter, alfa, beta, a, b, h;
float teethAmount;
float x, radian;
float angleRotateTooth;

sf::RenderWindow *window; //window here


/////////////////////////////////////    MANAGEMENT FUNCTIONS()   /////////////////////////

void input();
void draw();

////////////////////////////////////     OTHER FUNCTIONS()      ///////////////////////////


void get()
{
    cout<<"Diameter: ";
    cin>>diameter;
    cout<<endl;
    cout<<"Number of teeth: ";
    cin>>teethAmount;
    cout<<endl;
    cout<<"Hole diameter: ";
    cin>>holeDiameter;
    cout<<endl;
    cout<<"Alfa: ";
    cin>>alfa;
    cout<<endl;
    cout<<"Beta: ";
    cin>>beta;
    cout<<endl;
    cout<<"a: ";
    cin>>a;
    cout<<endl;
    cout<<"b: ";
    cin>>b;
    cout<<endl;
    cout<<"h: ";
    cin>>h;
}
void convert()
{
    diameter *= 3.7795;
    holeDiameter *= 3.7795;
    a *= 3.7795;
    b *= 3.7795;
    radian = 3.1415/180;
    x = h/(cos(beta * radian));
    h *= 3.7795;
    x *= 3.7795;
}

////////////////////////////////////     INT MAIN() FUNCTION     /////////////////////////

int main()
{
    sf::Clock clock;

    //get();

    diameter = 600;
    teethAmount = 38;
    holeDiameter = 50;
    alfa = 20;
    beta = 20;
    h = diameter/17.6923;
    a = h;
    radian = 3.1415/180;
    x = h/(cos(beta * radian));
    //b = x*0.955;
    b = x;
    //convert();

    //declerate hole
    sf::CircleShape hole(holeDiameter);
    hole.setFillColor(sf::Color::Black);
    hole.setOutlineThickness(1);
    hole.setOutlineColor(sf::Color::White);
    hole.setPosition(width/2 - holeDiameter,height/2 - holeDiameter);

    angleRotateTooth = 360/teethAmount; //angle rotate tooth

    //transforms...
    sf::Transform transformAlfa;
    transformAlfa.rotate(-alfa,width/2,height/2-diameter/2);

    sf::Transform transformBeta;
    transformBeta.rotate(beta,width/2,height/2-diameter/2);
    sf::Transform transformGamma;

    sf::Transform transformTooth;

    //declarate tooth
    sf::VertexArray tooth(sf::LinesStrip,21);

    tooth[1].position = transformAlfa.transformPoint(width/2-a,height/2-diameter/2);
    transformGamma.rotate(beta,tooth[1].position.x,tooth[1].position.y);
    tooth[0].position = transformGamma.transformPoint(width/2-a,(height/2-diameter/2)+b);
    tooth[2].position = sf::Vector2f(width/2,height/2-diameter/2);
    tooth[3].position = transformBeta.transformPoint(width/2,(height/2-diameter/2)+x);

        cout<<tooth[0].position.x<<endl;
        cout<<tooth[0].position.y<<endl;;
        cout<<tooth[1].position.x<<endl;
        cout<<tooth[1].position.y<<endl;;
        cout<<tooth[2].position.x<<endl;
        cout<<tooth[2].position.y<<endl;;
        cout<<tooth[3].position.x<<endl;
        cout<<tooth[3].position.y;

    // only control vertexes
    sf::Vertex P1;
    sf::Vertex P2;
    sf::Vertex P3;
    sf::Vertex P4;

    //cout<<x;

    P1.position = tooth[3].position;
    P4.position = sf::Vector2f(width/2 + 0.06*x,tooth[0].position.y - 0.09 * x);

    P2.position = sf::Vector2f(P4.position.x - x/1.8445 , P4.position.y + x/2.7668);
    P3.position = sf::Vector2f(P1.position.x + x/5.5337, P1.position.y + x/2.7668);

    //support lines
    sf::Vertex lineX[]=
    {
        sf::Vertex(sf::Vector2f(tooth[0].position.x,tooth[0].position.y),sf::Color::Green),
        sf::Vertex(sf::Vector2f(width/2,tooth[0].position.y),sf::Color::Green)
    };

    sf::Vertex lineY[]=
    {
        sf::Vertex(sf::Vector2f(tooth[2].position.x,tooth[2].position.y),sf::Color::Red),
        sf::Vertex(sf::Vector2f(width/2,tooth[0].position.y),sf::Color::Red)
    };

    float t;
    int i;

    for(t=0,i=4; t<1,i<20; t+=0.0625,i++)
    {
        tooth[i].position.x = pow(1-t,3) * P1.position.x + 3*t *pow(1-t,2) * P2.position.x + 3*pow(t,2)*(1-t)* P3.position.x + pow(t,3) * P4.position.x;
        tooth[i].position.y = pow(1-t,3) * P1.position.y + 3*t *pow(1-t,2) * P2.position.y + 3*pow(t,2)*(1-t)* P3.position.y + pow(t,3) * P4.position.y;
    }
    tooth[20].position = P4.position;

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    window = new sf::RenderWindow(sf::VideoMode(width,height,32), "Sharp", sf::Style::Default ,settings);
    window->setFramerateLimit(60);

    while(window->isOpen())
    {
        input();
        if(clock.getElapsedTime().asSeconds()>=1.0f/fps)
        {
            //draw();
            window->clear();
            window->draw(hole);
            window->draw(lineX,2,sf::Lines);
            window->draw(lineY,2,sf::Lines);

            for(int n=0; n<teethAmount; n++)
            {
                transformTooth.rotate(angleRotateTooth,width/2,height/2);
                window->draw(tooth,transformTooth);
            }

            window->display();
            clock.restart();
        }
    }
    delete window;

    return 0;
}

////////////////////////////////////     END OF  MAIN() FUNCTION     /////////////////////////

void input()
{
    sf::Event event;

    while(window->pollEvent(event))
    {
           if((event.type == sf::Event::Closed) ||
              (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
                window->close();
    }
}

void draw()
{
    window->clear(sf::Color::Black);
    //draw something
    window->display();
}
