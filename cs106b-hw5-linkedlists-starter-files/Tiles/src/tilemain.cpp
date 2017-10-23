/*
 * CS 106B Tiles
 * This client program uses your TileStack class and contains the 'main'
 * function to set up the overall program's graphical user interface.
 * Some commands use old-style printf to print debug messages because this
 * will not show up on the Stanford pop-up graphical console.
 *
 * Please DO NOT MODIFY this provided file. Your turned-in files should work
 * with an unmodified version of all provided code files.
 *
 * Version: 2016/07/20 Wed
 * Author : Marty Stepp
 */

#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include "console.h"
#include "random.h"
#include "TileStack.h"
#include "gwindow.h"
#include "gobjects.h"
#include "gevents.h"
using namespace std;

// set this to false for the same graphical output every time
static const bool RANDOM = true;

// constants
static const int WINDOW_WIDTH = 600;
static const int WINDOW_HEIGHT = 500;
static const int MIN_SIZE = 20;
static const int MAX_SIZE = 100;
static const int MIN_COLOR = 50;
static const int MAX_COLOR = 255;
static const int TILE_COUNT = 50;

// structure declaration to capture GUI state
struct TileGUI {
    GWindow* window;
    GButton* gbAddRectangle;
    GButton* gbClear;
    GRadioButton* grbHighlight;
    GRadioButton* grbRaise;
    GRadioButton* grbRemove;
    GTextField* gtfMousePos;

    ~TileGUI() {
        delete window;
        delete gbAddRectangle;
        delete gbClear;
        delete grbHighlight;
        delete grbRaise;
        delete grbRemove;
        delete gtfMousePos;
    }
};

// function prototype declarations
void addRandomTile(TileStack& tstack);
bool processEvent(TileGUI& gui, TileStack& tstack);
void setupGui(TileGUI& gui);

int main() {
    // possibly use the same random numbers every time for testing
    if (!RANDOM) {
        setRandomSeed(106);
    }

    // set up GUI and widgets
    TileGUI gui;
    setupGui(gui);

    // place several random tiles onto the screen
    TileStack tstack;
    for (int i = 0; i < TILE_COUNT; i++) {
        addRandomTile(tstack);
    }
    printf("drawAll\n");
    fflush(stdout);
    tstack.drawAll(*gui.window);

    // event loop waits for user to click on tiles
    while (true) {
        if (processEvent(gui, tstack)) {
            gui.window->clearCanvas();
            printf("drawAll\n");
            fflush(stdout);
            tstack.drawAll(*gui.window);
        } else if (!gui.window->isVisible()) {
            // if the user closes the main graphical window, shut down
            gui.window->close();
            break;
        }
    }

    return 0;
}

/*
 * Creates a new tile with a random x/y position, width, height, and color,
 * and adds it to the given tile list.
 */
void addRandomTile(TileStack& tstack) {
    // pick random coords and size
    int width = randomInteger(MIN_SIZE, MAX_SIZE);
    int height = randomInteger(MIN_SIZE, MAX_SIZE);
    int x = randomInteger(0, WINDOW_WIDTH - width);
    int y = randomInteger(0, WINDOW_HEIGHT - height);

    // pick random color
    int r = randomInteger(MIN_COLOR, MAX_COLOR);
    int g = randomInteger(MIN_COLOR, MAX_COLOR);
    int b = randomInteger(MIN_COLOR, MAX_COLOR);
    ostringstream colorout;
    colorout << "#" << setbase(16) << setfill('0') << r << g << b;
    string color = colorout.str();

    // add to top of tile list
    printf("pushTile (x=%d, y=%d, w=%d, h=%d, color=\"%s\")\n",
           x, y, width, height, color.c_str());
    fflush(stdout);
    tstack.pushTile(x, y, width, height, color);
}

/*
 * Waits for one mouse or window event from the graphical subsystem,
 * then handles the event appropriately if it is a mouse button press,
 * telling the tile list to highlight / raise / lower / delete etc.
 * Returns true if an event was processed (and TileStack needs to be redrawn).
 */
bool processEvent(TileGUI& gui, TileStack& tstack) {
    GEvent event = waitForEvent(MOUSE_EVENT | KEY_EVENT | WINDOW_EVENT | ACTION_EVENT);
    int eventClass = event.getEventClass();
    int type = event.getEventType();

    if (eventClass == ACTION_EVENT) {
        GActionEvent actionEvent(event);
        string cmd = actionEvent.getActionCommand();
        if (cmd == "Add") {
            addRandomTile(tstack);
            return true;
        } else if (cmd == "Clear") {
            printf("clear\n");
            fflush(stdout);
            tstack.clear();
            return true;
        }
    } else if (eventClass == MOUSE_EVENT) {
        GMouseEvent mouseEvent(event);
        int x = (int) mouseEvent.getX();
        int y = (int) mouseEvent.getY();
        if (type == MOUSE_PRESSED) {
            if (gui.grbHighlight->isSelected()) {
                printf("highlight (x=%d, y=%d)\n", x, y);
                fflush(stdout);
                tstack.highlight(x, y);
            } else if (gui.grbRaise->isSelected()) {
                printf("raise (x=%d, y=%d)\n", x, y);
                fflush(stdout);
                tstack.raise(x, y);
            } else if (gui.grbRemove->isSelected()) {
                printf("remove (x=%d, y=%d)\n", x, y);
                fflush(stdout);
                tstack.remove(x, y);
            }
            return true;
        } else if (type == MOUSE_MOVED) {
            string posStr = "(x=" + integerToString(x)
                    + ", y=" + integerToString(y) + ")";
            gui.gtfMousePos->setText(posStr);
        }
    } else if (eventClass == KEY_EVENT) {
        GKeyEvent keyEvent(event);
        if (type == KEY_PRESSED) {
            if (tolower(keyEvent.getKeyChar()) == 'a') {
                // listen for 'A' to add a new random tile
                addRandomTile(tstack);
                return true;
            } else if (tolower(keyEvent.getKeyChar()) == 'c') {
                // listen for 'C' to clear all tiles
                tstack.clear();
                return true;
            }
        }
    }

    return false;
}

/*
 * Constructs the graphical window and widgets on the screen.
 */
void setupGui(TileGUI& gui) {
    gui.window = new GWindow(WINDOW_WIDTH, WINDOW_HEIGHT);
    gui.window->center();
    gui.window->setWindowTitle("CS 106B Tiles");
    gui.gbAddRectangle = new GButton("Add");
    gui.gbClear = new GButton("Clear");
    gui.grbHighlight = new GRadioButton("Highlight");
    gui.grbHighlight->setSelected(true);
    gui.grbRaise = new GRadioButton("Raise");
    gui.grbRemove = new GRadioButton("Remove");
    gui.gtfMousePos = new GTextField(9);
    gui.gtfMousePos->setEditable(false);
    gui.window->addToRegion(gui.grbHighlight, "South");
    gui.window->addToRegion(gui.grbRaise, "South");
    gui.window->addToRegion(gui.grbRemove, "South");
    gui.window->addToRegion(gui.gbAddRectangle, "South");
    gui.window->addToRegion(gui.gbClear, "South");
    gui.window->addToRegion(gui.gtfMousePos, "South");
}
