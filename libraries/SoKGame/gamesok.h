#pragma once

 /**
  * @filename ArduBreakout.ino
  * \brief Breakout
  * \details 
  * Copyright (C) 2011 Sebastian Goscik
  * All rights reserved.

  * This library is free software; you can redistribute it and/or
  * modify it under the terms of the GNU Lesser General Public
  * License as published by the Free Software Foundation; either
  * version 2.1 of the License, or (at your option) any later version.
  */

#include <Arduino.h>
#include <Arduboy.h>
#include "breakout_bitmaps.h"

static Arduboy arduboy;


static const unsigned int COLUMNS = 13; //Columns of bricks
static const unsigned int ROWS = 4;     //Rows of bricks
static int dx = -1;                     //Initial movement of ball
static int dy = -1;                     //Initial movement of ball
static int xb;                          //Balls starting possition
static int yb;                          //Balls starting possition
static boolean released;                //If the ball has been released by the player
static boolean paused = false;          //If the game has been paused
static byte xPaddle;                    //X position of paddle
static boolean isHit[ROWS][COLUMNS];    //Array of if bricks are hit or not
static boolean bounced=false;           //Used to fix double bounce glitch
static byte lives = 3;                  //Amount of lives
static byte level = 1;                  //Current level
static unsigned int score=0;            //Score for the game
static unsigned int brickCount;         //Amount of bricks hit
static byte pad,pad2,pad3;              //Button press buffer to stop pause repeating
static byte oldpad,oldpad2,oldpad3;
static char text_buffer[16];            //General string buffer
static boolean start=false;             //If in menu or in game
static boolean initialDraw=false;       //If the inital draw has happened
static char initials[3];                //Initials used in high score

//Ball Bounds used in collision detection
static byte leftBall;
static byte rightBall;
static byte topBall;
static byte bottomBall;

//Brick Bounds used in collision detection
static byte leftBrick;
static byte rightBrick;
static byte topBrick;
static byte bottomBrick;

static byte tick;


void playTone(unsigned int frequency, unsigned long duration);





void movePaddle();

void moveBall();

void drawBall();

void drawPaddle();

void drawLives();

void drawGameOver();

void pause();

void Score();

void newLevel();



//Used to delay images while reading button input
boolean pollFireButton(int n);

//Function by nootropic design to display highscores
boolean displayHighScores(byte file);


boolean titleScreen();



//Function by nootropic design to add high scores
void enterInitials();


void gameBegin ();

void gameLoop ();


#if 0
void enterHighScore(byte file)
#endif