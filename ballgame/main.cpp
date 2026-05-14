#include <iostream>
#include <string>
#include "raylib.h"
#include <cmath>
#include <vector>
#include <ctime>
#define WIDTH 800
#define HEIGHT 600
#define GRAVITY 300
#define JUMP 100

class Ball{
    public:
        float posx=0;
        float posy=0;
        float vel[2];
        Color color;
    Ball(float posx,float posy,float vel[2],Color color){
        this->posx=posx;
        this->posy=posy;
        this->vel[0]=vel[0];
        this->vel[1]=vel[1];
        this->color=color;
    }
};

int main(){
    InitWindow(WIDTH,HEIGHT,"Balls");
    InitAudioDevice();
    SetTargetFPS(60);
    srand(time(0));
    Sound s;
    const char* soundnames[13]={"wav//a1.wav","wav//a1s.wav","wav//b1.wav","wav//c1.wav","wav//c1s.wav","wav//d1.wav","wav//d1s.wav","wav//e1.wav","wav//f1.wav","wav//f1s.wav","wav//g1.wav","wav//g1s.wav","wav//c2.wav"};
    int melody[] = {
    5, 5, 5, 0, 11, 10, 8, 5, 8, 10, // Bar 1
    3, 3, 5, 0, 11, 10, 8, 5, 8, 10, // Bar 2
    2, 2, 5, 0, 11, 10, 8, 5, 8, 10, // Bar 3
    1, 1, 5, 0, 11, 10, 8, 5, 8, 10,5, 5, 5, 0, 11, 10, 8, 5, 8, 10, // Bar 1
    3, 3, 5, 0, 11, 10, 8, 5, 8, 10, // Bar 2
    2, 2, 5, 0, 11, 10, 8, 5, 8, 10, // Bar 3
    1, 1, 5, 0, 11, 10, 8, 5, 8, 10,5, 5, 5, 0, 11, 10, 8, 5, 8, 10, // Bar 1
    3, 3, 5, 0, 11, 10, 8, 5, 8, 10, // Bar 2
    2, 2, 5, 0, 11, 10, 8, 5, 8, 10, // Bar 3
    1, 1, 5, 0, 11, 10, 8, 5, 8, 10 // Bar 4
};
    std::vector<Sound> sounds;
    for (int i=0;i<13;i++){
        Sound s=LoadSound(soundnames[i]);
        sounds.push_back(s);
    }
    float posx=WIDTH/2;
    int radius=200;
    float posy=HEIGHT/2;
    float vel[2]={200,0};
    float cx=WIDTH/2;
    float cy=HEIGHT/2;
    float n[2]={};
    float proj[2]={};
    std::vector<Ball> balls;
    float nm;
    int ballcount=0;
    Color colors[10]={RED,BLUE,GREEN,ORANGE,YELLOW,PURPLE,WHITE,PINK,BROWN,GRAY};
    balls.push_back(Ball(cx,cy,vel,RED));
    while (!WindowShouldClose()){
        float dt=GetFrameTime();
        //falllogic
        
        
        for(Ball &b:balls){
            if ((b.posx-cx)*(b.posx-cx) + (b.posy-cy)*(b.posy-cy)>=radius*radius){
                n[0]=b.posx-cx;
                n[1]=b.posy-cy;
                nm=std::sqrt(n[0]*n[0]+n[1]*n[1]);
                n[0]/=nm;
                n[1]/=nm;

                float dot=n[0]*b.vel[0]+n[1]*b.vel[1];
                proj[0]=dot*n[0];
                proj[1]=dot*n[1];
                b.vel[0]=b.vel[0]-2*proj[0];
                b.vel[1]=b.vel[1]-2*proj[1];
                
                b.vel[1]*=1.1;
                b.vel[0]*=1.1;
                if (ballcount%10==2){
                    SetSoundPitch(sounds[melody[ballcount]],2.0f);
                    PlaySound(sounds[melody[ballcount]]); 
                }
                else{
                    SetSoundPitch(sounds[melody[ballcount]],1.0f);
                    PlaySound(sounds[melody[ballcount]]); 
                }
                std::cout<<melody[ballcount]<<std::endl;
                ballcount+=1;
                
                
            }
            else{
                b.vel[1]+=GRAVITY*dt;
            }
            b.posy+=b.vel[1]*dt;
            b.posx+=b.vel[0]*dt;
            if ((b.posx-cx)*(b.posx-cx) + (b.posy-cy)*(b.posy-cy)>=radius*radius){
                float dist=std::sqrt((b.posx-cx)*(b.posx-cx)+(b.posy-cy)*(b.posy-cy));
                b.posx=cx+(b.posx-cx)/dist*radius;
                b.posy=cy+(b.posy-cy)/dist*radius;
            }
        }
        
        
        if (ballcount>balls.size() ) {
            float randvel[2]={rand()%300+1,rand()%300+1};
            balls.push_back(Ball(cx,cy,randvel,colors[rand()%10]));
        }
        
        //draw
        BeginDrawing();
        ClearBackground(BLACK);
        for (int i=0;i<balls.size();i++){
            DrawCircle(balls[i].posx,balls[i].posy,10,balls[i].color);
        }
        
        DrawCircleLines(cx,cy,radius,RED);
        EndDrawing();
    }

    for (Sound &s:sounds){
        UnloadSound(s);
    }

    CloseWindow();
    CloseAudioDevice();






    return 0;
}

