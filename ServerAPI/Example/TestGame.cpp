//
//  TestGame.cpp
//  ServerXcode
//
//  Created by James Lennon on 10/21/14.
//  Copyright (c) 2014 James Lennon. All rights reserved.
//

#include "TestGame.h"
#include <iostream>

using namespace std;
using namespace openpad;

void clearScreen(){
    cout << endl << "===================" << endl << endl;
}

TestGame::TestGame(){
    ServerHandler::ServerHandler();
}

void TestGame::setup(){
    slots = 2;
    hasStarted = false;
    memset(board, 0, sizeof(board));
    curturn = 0;
    
    cout << "WELCOME TO TIC TAC TERMINAL" << endl;
    clearScreen();
    printLobby();
}

void TestGame::onStart(){
    setup();
}

string TestGame::getName(){
    return "Tic Tac Terminal";
}

string TestGame::getDesc(){
    return "duh";
}

int TestGame::getFilledSlots(){
    return 2-slots;
}

int TestGame::getOpenSlots(){
    return slots;
}

bool TestGame::canJoin(Client *cli, string &why){
    return !hasStarted;
}

void TestGame::onJoin(Client *cli){
    Player p;
    p.cli = cli;
    players.insert(make_pair(cli->clientID->phoneid, p));
    slots--;
    serv->refreshClients();
    
    if(!OP_DEBUG)printLobby();
    if(slots==0){
        startGame();
    }
}

void TestGame::printLobby(){
    printf("Lobby: (%d/2)\n", getFilledSlots());
    for(map<string, Player>::iterator it = players.begin(); it != players.end(); ++it){
        cout << ">" << it->second.cli->clientID->username << endl;
    }
    clearScreen();
}

void TestGame::startGame(){
    hasStarted = true;
    cout << "STARTING GAME" << endl << endl;
    Player p1 = players.begin()->second, p2 = (players.begin()++)->second;
    printf("%s is X\n%s is O\n", p1.cli->clientID->username.c_str(), p2.cli->clientID->username.c_str());
    clearScreen();
}

PadConfig TestGame::getDefaultControls(){
    PadConfig conf;
    double w = .1;
    double padding = .05;
    
    for(int i=0; i<3; i++){
        for(int j=0; j<3; j++){
            ButtonControl* b = new ButtonControl;
            b->frame.x = j*(w+padding);
            b->frame.y = i*(w+padding);
            b->frame.w = w;
            b->frame.h = w;
            b->controlID = i*3+j;
            conf.controls.push_back(b);
        }
    }
    
    return conf;
}

void TestGame::printBoard(){
    for(int i=0; i<3; i++){
        for(int j=0; j<3; j++){
            int val = board[j][i];
            char c;
            if(val==0){
                c = ' ';
            }else if(val==1){
                c = 'X';
            }else if(val==2){
                c = 'O';
            }
            cout << c;
            if(j<2){
                cout << "|";
            }
        }
        cout << endl << "- - -" << endl;
    }
    clearScreen();
}

void TestGame::startTurn(){
    int amt = curturn%2;
    Player p = players.begin().operator++(amt)->second;
    
    printBoard();
}

void TestGame::doTurn(int loc, int player){
    int x = loc % 3, y = loc/3;
    if(board[x][y]==0){
        board[x][y] = player+1;
        printBoard();
        curturn++;
    }
}

void TestGame::onPadUpdate(Client *cli, PadUpdateObject update){
    if(hasStarted){
        int player = distance(players.begin(), players.find(cli->clientID->phoneid));
        doTurn(update.controlid, player);
    }
}

void TestGame::onDisconnect(Client *cli){
    slots++;
    players.erase(cli->clientID->phoneid);
    if(hasStarted){
        Player winner = players.begin()->second;
        printf("%s quit, %s wins!\n", cli->clientID->username.c_str(), winner.cli->clientID->username.c_str());
    }else{
        serv->refreshClients();
        printLobby();
    }
}
