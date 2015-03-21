#include "Continue.h"

#include <cmath>

void Continue::solve(sim::MouseInterface* mouse) {

    mouse->declareInterfaceType(sim::CONTINUOUS);

    // Initialize the member variable
    m_mouse = mouse;

    while (true) {
        //if (!wallRight()) {
            turnRight();
        //}
        //while (wallFront()) {
            //turnLeft();
        //}
        //moveForward();
        //correctErrors();
    }
}

bool Continue::wallRight() {
    return m_mouse->read("right") > 0.5;
}

bool Continue::wallFront() {
    return m_mouse->read("rightFront") > 0.75;
}

void Continue::turnRight() {
    m_mouse->setWheelSpeeds(-.5*M_PI, -.5*M_PI);
    m_mouse->delay(290);
    m_mouse->setWheelSpeeds(0, 0);
}

void Continue::turnLeft() {
    m_mouse->setWheelSpeeds(5*M_PI, 5*M_PI);
    m_mouse->delay(290);
    m_mouse->setWheelSpeeds(0, 0);
}

void Continue::moveForward() {
    m_mouse->setWheelSpeeds(-10*M_PI, 10*M_PI);
    m_mouse->delay(350);
    for (int i = 0; i < 5; i += 1) {
        if (m_mouse->read("rightFront") > 0.9) {
            break;
        }
        m_mouse->delay(10);
    }
    m_mouse->setWheelSpeeds(0, 0);
    m_mouse->delay(0);
}

void Continue::correctErrors() {
    if (m_mouse->read("rightMiddle") < 0.3) {
        // Right
        m_mouse->setWheelSpeeds(-5, 0);
        m_mouse->delay(10);
    }
    if (m_mouse->read("rightMiddle") > 0.5) {
        // Left
        m_mouse->setWheelSpeeds(0, 5);
        m_mouse->delay(10);
    }
}
