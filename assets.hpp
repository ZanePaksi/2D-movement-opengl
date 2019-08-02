#ifndef ASSETS_H
#define ASSETS_H

// OpenGL Libraries
#include <GL/glut.h>

// Additional Libraries
#include <iostream>
#include <math.h>
#include <cstdlib>
#include <cmath>
#include <ctime>
#include <map>

// Global variables
const double TO_RADS = 3.141592654 / 180.0;

using namespace std;

template <class T> class Vec3 {
  public:
    T x, y, z;

    // Constructor
    Vec3() {
      x = y = z = 0;
    }

    // Three parameter constructor
    Vec3(T xVal, T yVal, T zVal) {
      x = xVal;
      y = yVal;
      z = zVal;
    }

    // Setters and Getters
    void set(const T &xValue, const T &yValue, const T &zValue) {
      x = xValue;
      y = yValue;
      z = zValue;
    }

    T getX() const {return x;}
    T getY() const {return y;}
    T getZ() const {return z;}

    void setX(const T &xValue) {x = xValue;}
    void setY(const T &yValue) {x = yValue;}
    void setZ(const T &zValue) {x = zValue;}

    // Helper method
    void zero() {
      x = y = z = 0.0;
    }

    void normalize() {
      // Calculate magnitude of vector
      T magnitude = sqrt((x * x) + (y * y) + (z * z));

      // if the magnitude isn't zero, then divide
      if (magnitude != 0) {
        x /= magnitude;
        y /= magnitude;
        z /= magnitude;
      }
    }

    // Easy adders
    void addX(T value) {x += value;}
    void addY(T value) {y += value;}
    void addZ(T value) {z += value;}

    // Method to display the vector to easily check the values
    void display() {
      std::cout << "X: " << x << "\t Y: " << y << "\t Z: " << z << std::endl;
    }

    // Overloaded add and assign operator to add Vec3's together
    Vec3 operator+=(const Vec3 &vector) {
      x += vector.x;
      y += vector.y;
      z += vector.z;
    }

    // Overloaded multiply and assign operator
    Vec3 operator*=(const T value) {
      x *= value;
      y *= value;
      z *= value;
    }

};

class Player {
  private:
    int player_sides;
    float player_vitality;
    float player_speed;
    int side_cap;

  public:
    // Camera Position - not protected because I keep having to manipulate it
    Vec3<double> userPos;
    Vec3<double> userMovement;
    Vec3<double> userRot;

    int sides = player_sides;
    float speed = player_speed;
    float angle, increment, a, b;

    // Holding keys down
    bool holdLeft = false;
    bool holdRight = false;
    bool holdUp = false;
    bool holdDown = false;

    // Constructor
    Player() {
      // Zero out position
      userPos.zero();
      userRot.zero();
      userMovement.zero();

      player_sides = 3;
      player_speed = 1;
      side_cap = 20;

    }

    // Destructor
    ~Player() {}

    void addSides(int a) {
      if (player_sides < side_cap) {
        setSides(getSides() + 1);
        // Printing for testing purposes
        cout << getSides() << endl;
      }
    }

    void createPlayer() {
      int scale = 1;
      // Convert radians to degrees
      angle = M_PI / 2;
      // this is how we travel around the unit circle.
      increment = ((360 / player_sides) * M_PI) / 180;

      glBegin(GL_POLYGON);
      glColor3f(0.0, 0.0, 0.0);

      for (int i = 0; i < player_sides; i++) {
        //calculate x and y, then add to dictionary
        a = cos(angle) * scale; //x
        b = sin(angle) * scale; //y
        glVertex2f(a,b);
        angle += increment; //Move to the next point
      }
      glEnd();
      glFlush();
    }

    // Method to convert angle from degrees to radians
    const double toRads(const double &angleInDegrees) const {
      return angleInDegrees * TO_RADS;
    }

    void move(float delta) {
      /* Creating a new vector here. This stores the next move and applies it to
      user position all at once. Allowing for a smooth transition.
      */
      double framerateFactor;
      double speedX, speedY;

      if (holdLeft) {
          userRot.addZ(2.0);

      }

      if (holdRight) {
        userRot.addZ(-2.0);

      }

      // Limit Z rotation to 360 degrees, makes thngs easier... maybe?
      if (userRot.getZ() >= 360.0) {
        userRot.addZ(-360.0);
      } else if (userRot.getZ() <=-360.0) {
        userRot.addZ(360.0);
      }

      // Get sin and cos of x and y axis rotation
      double sinZrot = sin( toRads(userRot.getZ()) + M_PI/2 );
      double cosZrot = cos( toRads(userRot.getZ()) + M_PI/2 );


      if (holdUp) {
        userMovement.addY(sinZrot);
        userMovement.addX(-cosZrot);
      }

      if (holdDown) {
        userMovement.addY(-sinZrot);
        userMovement.addX(cosZrot);
      }

      // Normalize movement vector
      userMovement.normalize();

      framerateFactor = player_speed * delta;

      userMovement *= framerateFactor;

      // userMovement.display();

      userPos += userMovement;

      // userPos.display();

      userMovement.zero();
    } // End of move()

    // Getters and Setters
    void setSides(int s) {player_sides = s;}
    int getSides() {return player_sides;}
    double getXPos() const {return userPos.getX();}
    double getYPos() const {return userPos.getY();}

    int getZRot() const {return userRot.getZ();}

};



#endif
