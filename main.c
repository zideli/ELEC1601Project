#include "stdio.h"
#include "stdlib.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL2_gfxPrimitives.h"
/*Changed as clock() gives poor results on mac
#include "time.h"
*/
#include <sys/time.h>

#include "formulas.h"
#include "wall.h"
#include "robot.h"
int done = 0;


int main(int argc, char *argv[]) {
    SDL_Window *window;
    SDL_Renderer *renderer;

    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        return 1;
    }

    window = SDL_CreateWindow("Robot Maze", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, OVERALL_WINDOW_WIDTH, OVERALL_WINDOW_HEIGHT, SDL_WINDOW_OPENGL);
    window = SDL_CreateWindow("Robot Maze", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, OVERALL_WINDOW_WIDTH, OVERALL_WINDOW_HEIGHT, SDL_WINDOW_OPENGL);
    renderer = SDL_CreateRenderer(window, -1, 0);

    struct Robot robot;
    struct Wall_collection *head = NULL;
    int front_left_sensor, front_right_sensor=0, back_left_sensor=0;
    /*Changed as clock() gives poor results on mac
    clock_t start_time,end_time;
    int msec;
    */

    struct timeval start_time, end_time;
    gettimeofday(&start_time, 0);
    unsigned long msec;

    // SETUP MAZE
    // You can create your own maze here. line of code is adding a wall.
    // You describe position of top left corner of wall (x, y), then width and height going down/to right
    // Relative positions are used (OVERALL_WINDOW_WIDTH and OVERALL_WINDOW_HEIGHT)
    // But you can use absolute positions. 10 is used as the width, but you can change this.
    
    // MAZE 1
    // insertAndSetFirstWall(&head, 1,  OVERALL_WINDOW_WIDTH/2, OVERALL_WINDOW_HEIGHT/2, 10, OVERALL_WINDOW_HEIGHT/2);
    // insertAndSetFirstWall(&head, 2,  OVERALL_WINDOW_WIDTH/2-100, OVERALL_WINDOW_HEIGHT/2+100, 10, OVERALL_WINDOW_HEIGHT/2-100);
    // insertAndSetFirstWall(&head, 3,  OVERALL_WINDOW_WIDTH/2-250, OVERALL_WINDOW_HEIGHT/2+100, 150, 10);
    // insertAndSetFirstWall(&head, 4,  OVERALL_WINDOW_WIDTH/2-150, OVERALL_WINDOW_HEIGHT/2, 150, 10);
    // insertAndSetFirstWall(&head, 5,  OVERALL_WINDOW_WIDTH/2-250, OVERALL_WINDOW_HEIGHT/2-200, 10, 300);
    // insertAndSetFirstWall(&head, 6,  OVERALL_WINDOW_WIDTH/2-150, OVERALL_WINDOW_HEIGHT/2-100, 10, 100);
    // insertAndSetFirstWall(&head, 7,  OVERALL_WINDOW_WIDTH/2-250, OVERALL_WINDOW_HEIGHT/2-200, 450, 10);
    // insertAndSetFirstWall(&head, 8,  OVERALL_WINDOW_WIDTH/2-150, OVERALL_WINDOW_HEIGHT/2-100, 250, 10);
    // insertAndSetFirstWall(&head, 9,  OVERALL_WINDOW_WIDTH/2+200, OVERALL_WINDOW_HEIGHT/2-200, 10, 300);
    // insertAndSetFirstWall(&head, 10,  OVERALL_WINDOW_WIDTH/2+100, OVERALL_WINDOW_HEIGHT/2-100, 10, 300);
    // insertAndSetFirstWall(&head, 11,  OVERALL_WINDOW_WIDTH/2+100, OVERALL_WINDOW_HEIGHT/2+200, OVERALL_WINDOW_WIDTH/2-100, 10);
    // insertAndSetFirstWall(&head, 12,  OVERALL_WINDOW_WIDTH/2+200, OVERALL_WINDOW_HEIGHT/2+100, OVERALL_WINDOW_WIDTH/2-100, 10);
    

    // MAZE 3
    insertAndSetFirstWall(&head, 2,  640-10-220, 400, 10, 80);
    insertAndSetFirstWall(&head, 2,  640-200-20, 400, 200, 10);
    insertAndSetFirstWall(&head, 2,  640-10-20, 50, 10, 350);
    insertAndSetFirstWall(&head, 2,  640-280-20, 50, 280, 10);
    insertAndSetFirstWall(&head, 2,  640-10-300, 50, 10, 100);
    insertAndSetFirstWall(&head, 2,  640-110-300, 150, 110, 10);
    insertAndSetFirstWall(&head, 2,  640-10-400, 50, 10, 100);
    insertAndSetFirstWall(&head, 2,  640-400-220, 50, 220, 10);
    insertAndSetFirstWall(&head, 2,  640-10-620, 50, 10, 290);
    insertAndSetFirstWall(&head, 2,  640-620-20, 340, 20, 10);


    insertAndSetFirstWall(&head, 1,  640-10-320, 300, 10, 180);
    insertAndSetFirstWall(&head, 2,  640-200-120, 300, 200, 10);
    insertAndSetFirstWall(&head, 2,  640-10-120, 150, 10, 150);
    insertAndSetFirstWall(&head, 2,  640-80-120, 150, 80, 10);
    insertAndSetFirstWall(&head, 2,  640-10-200, 150, 10, 100);
    insertAndSetFirstWall(&head, 2,  640-310-200, 250, 310, 10);
    insertAndSetFirstWall(&head, 2,  640-10-500, 150, 10, 100);
    insertAndSetFirstWall(&head, 2,  640-20-500, 150, 20, 10);
    insertAndSetFirstWall(&head, 2,  640-10-520, 150, 10, 290);
    insertAndSetFirstWall(&head, 2,  640-120-520, 440, 120, 10);
    


    // OUR MAZE
    // insertAndSetFirstWall(&head, 1,  OVERALL_WINDOW_WIDTH/2, OVERALL_WINDOW_HEIGHT/2+20, 10, OVERALL_WINDOW_HEIGHT/2-120);
    // insertAndSetFirstWall(&head, 2,  OVERALL_WINDOW_WIDTH/2-100, OVERALL_WINDOW_HEIGHT/2+120, 10, OVERALL_WINDOW_HEIGHT/2-80);
    // insertAndSetFirstWall(&head, 3,  OVERALL_WINDOW_WIDTH/2-250, OVERALL_WINDOW_HEIGHT/2+120, 150, 10);
    // insertAndSetFirstWall(&head, 4,  OVERALL_WINDOW_WIDTH/2, OVERALL_WINDOW_HEIGHT/2+20, 150, 10);
    // insertAndSetFirstWall(&head, 5,  OVERALL_WINDOW_WIDTH/2, OVERALL_WINDOW_HEIGHT/2+130, 150, 10);
    // insertAndSetFirstWall(&head, 6,  OVERALL_WINDOW_WIDTH/2+150, OVERALL_WINDOW_HEIGHT/2+130, 10, OVERALL_WINDOW_HEIGHT/2-120);
    // insertAndSetFirstWall(&head, 7,  OVERALL_WINDOW_WIDTH/2-250, OVERALL_WINDOW_HEIGHT/2-230, 10, OVERALL_WINDOW_HEIGHT/2+110);
    // insertAndSetFirstWall(&head, 8,  OVERALL_WINDOW_WIDTH/2+150, OVERALL_WINDOW_HEIGHT/2-150, 10, OVERALL_WINDOW_HEIGHT/2-60);
    // insertAndSetFirstWall(&head, 9,  OVERALL_WINDOW_WIDTH/2-250, OVERALL_WINDOW_HEIGHT/2-230, 500, 10);
    // insertAndSetFirstWall(&head, 10,  OVERALL_WINDOW_WIDTH/2+250, OVERALL_WINDOW_HEIGHT/2-230, 10, OVERALL_WINDOW_HEIGHT/2+90);
    // insertAndSetFirstWall(&head, 11,  OVERALL_WINDOW_WIDTH/2-150, OVERALL_WINDOW_HEIGHT/2-150, 300, 10);
    // insertAndSetFirstWall(&head, 12,  OVERALL_WINDOW_WIDTH/2-250, OVERALL_WINDOW_HEIGHT/2-65, 300, 10);
    // insertAndSetFirstWall(&head, 13,  OVERALL_WINDOW_WIDTH/2+150, OVERALL_WINDOW_HEIGHT/2+200, OVERALL_WINDOW_WIDTH/2-100, 10);
    // insertAndSetFirstWall(&head, 14,  OVERALL_WINDOW_WIDTH/2+250, OVERALL_WINDOW_HEIGHT/2+100, OVERALL_WINDOW_WIDTH/2-100, 10);
    // insertAndSetFirstWall(&head, 15,  OVERALL_WINDOW_WIDTH/2-250, OVERALL_WINDOW_HEIGHT/2+20, 150, 10);

    // OUR SECOND MAZE
    // insertAndSetFirstWall(&head, 1, 0, 0, 10, OVERALL_WINDOW_HEIGHT-10); //left wall
    // insertAndSetFirstWall(&head, 2, 0, 0, OVERALL_WINDOW_WIDTH, 10);//top wall
    // insertAndSetFirstWall(&head, 3, 100, OVERALL_WINDOW_HEIGHT/2+230, OVERALL_WINDOW_WIDTH-100, 10);//bottom wall
    // insertAndSetFirstWall(&head, 4, OVERALL_WINDOW_WIDTH/2+310, 100, 10, OVERALL_WINDOW_HEIGHT-100);//right wall
    // insertAndSetFirstWall(&head, 1,  OVERALL_WINDOW_WIDTH/2, OVERALL_WINDOW_HEIGHT/6+300, 10, 100);
    // insertAndSetFirstWall(&head, 2,  OVERALL_WINDOW_WIDTH/2-100, OVERALL_WINDOW_HEIGHT/6+300, 100, 10);
    // insertAndSetFirstWall(&head, 3,  0, OVERALL_WINDOW_HEIGHT/6+300, 100, 10);
    // insertAndSetFirstWall(&head, 8,  380, OVERALL_WINDOW_HEIGHT/6+200, 10, 100);
    // insertAndSetFirstWall(&head, 5,  90, OVERALL_WINDOW_HEIGHT/6+100, 130, 10);
    // insertAndSetFirstWall(&head, 6,  OVERALL_WINDOW_WIDTH/2-100, OVERALL_WINDOW_HEIGHT/6+100, 10, 100);
    // insertAndSetFirstWall(&head, 7,  OVERALL_WINDOW_WIDTH/2-100, OVERALL_WINDOW_HEIGHT/6+200, 200, 10);
    // insertAndSetFirstWall(&head, 8,  OVERALL_WINDOW_WIDTH/2+100, OVERALL_WINDOW_HEIGHT/6+200, 10, 100);
    // insertAndSetFirstWall(&head, 9,  OVERALL_WINDOW_WIDTH-110, OVERALL_WINDOW_HEIGHT/6+100, 10, 300);
    // insertAndSetFirstWall(&head, 10,  OVERALL_WINDOW_WIDTH/2, OVERALL_WINDOW_HEIGHT/6+100, 210, 10);
    // insertAndSetFirstWall(&head, 11,  OVERALL_WINDOW_WIDTH-110, 0, 10, 100);
    // insertAndSetFirstWall(&head, 12,  OVERALL_WINDOW_WIDTH/2, 100, 220, 10);
    // insertAndSetFirstWall(&head, 13,  0, 100, 200, 10);
    // insertAndSetFirstWall(&head, 14, 135, 250, 50, 100);
    // insertAndSetFirstWall(&head, 15, 380, OVERALL_WINDOW_HEIGHT-60, 10, 100);
    // insertAndSetFirstWall(&head, 15, OVERALL_WINDOW_WIDTH-180, OVERALL_WINDOW_HEIGHT-250, 25, 300);
    
    //COMPLEX MAZE
    // insertAndSetFirstWall(&head, 1,  OVERALL_WINDOW_WIDTH/2-20, OVERALL_WINDOW_HEIGHT/2, 10, OVERALL_WINDOW_HEIGHT/2);
    // insertAndSetFirstWall(&head, 2,  OVERALL_WINDOW_WIDTH/2-80, OVERALL_WINDOW_HEIGHT/2-150, 10, OVERALL_WINDOW_HEIGHT/2+150);
    // insertAndSetFirstWall(&head, 3,  OVERALL_WINDOW_WIDTH/2-80, OVERALL_WINDOW_HEIGHT/2-150, 250, 10);
    // insertAndSetFirstWall(&head, 4,  OVERALL_WINDOW_WIDTH/2-20, OVERALL_WINDOW_HEIGHT/2, 100, 10); 
    // insertAndSetFirstWall(&head, 5,  OVERALL_WINDOW_WIDTH/2+140, OVERALL_WINDOW_HEIGHT/2, 40, 10); 
    // insertAndSetFirstWall(&head, 6,  OVERALL_WINDOW_WIDTH/2+170, OVERALL_WINDOW_HEIGHT/2-150, 10, 150);
    // insertAndSetFirstWall(&head, 7,  OVERALL_WINDOW_WIDTH/2-20, OVERALL_WINDOW_HEIGHT/2-90, 130, 10);
    // insertAndSetFirstWall(&head, 8,  OVERALL_WINDOW_WIDTH/2-20, OVERALL_WINDOW_HEIGHT/2-60, 130, 10);
    // insertAndSetFirstWall(&head, 9,  OVERALL_WINDOW_WIDTH/2-20, OVERALL_WINDOW_HEIGHT/2-90, 10, 30);
    // insertAndSetFirstWall(&head, 10,  OVERALL_WINDOW_WIDTH/2+110, OVERALL_WINDOW_HEIGHT/2-90, 10, 40);
    // insertAndSetFirstWall(&head, 11,  OVERALL_WINDOW_WIDTH/2+80, OVERALL_WINDOW_HEIGHT/2, 10, 140); // v1 left
    // insertAndSetFirstWall(&head, 12,  OVERALL_WINDOW_WIDTH/2+140, OVERALL_WINDOW_HEIGHT/2, 10, 80); // v1 right
    // insertAndSetFirstWall(&head, 13,  OVERALL_WINDOW_WIDTH/2+140, OVERALL_WINDOW_HEIGHT/2+80, 80, 10); // h1 top
    // insertAndSetFirstWall(&head, 14,  OVERALL_WINDOW_WIDTH/2+80, OVERALL_WINDOW_HEIGHT/2+140, 80, 10); // h1 bottom
    // insertAndSetFirstWall(&head, 15,  OVERALL_WINDOW_WIDTH/2+160, OVERALL_WINDOW_HEIGHT/2+140, 10, 80); // v2 left
    // insertAndSetFirstWall(&head, 16,  OVERALL_WINDOW_WIDTH/2+220, OVERALL_WINDOW_HEIGHT/2+80, 10, 80); // v2 right
    // insertAndSetFirstWall(&head, 17,  OVERALL_WINDOW_WIDTH/2+220, OVERALL_WINDOW_HEIGHT/2+160, 100, 10); // h2 top
    // insertAndSetFirstWall(&head, 18,  OVERALL_WINDOW_WIDTH/2+160, OVERALL_WINDOW_HEIGHT/2+220, 160, 10); // h2 bottom

    setup_robot(&robot);
    updateAllWalls(head, renderer);

    SDL_Event event;
    while(!done){
        SDL_SetRenderDrawColor(renderer, 100, 150, 150, 255);
        // SDL_SetRenderDrawColor(renderer, (20*(5-i)), 400+(20*(5-i)), 135+(20*(5-i)), 255);
        SDL_RenderClear(renderer);

        //Move robot based on user input commands/auto commands
        if (robot.auto_mode == 1)
            robotAutoMotorMove(&robot, front_left_sensor, front_right_sensor, back_left_sensor, msec);
        robotMotorMove(&robot);

        //Check if robot reaches endpoint. and check sensor values
        //if (checkRobotReachedEnd(&robot, OVERALL_WINDOW_WIDTH, OVERALL_WINDOW_HEIGHT/2+100, 10, 100)){
        //if (checkRobotReachedEnd(&robot, 220, 480, 100, 10)){ //Maze 2
        //if (checkRobotReachedEnd(&robot, 0, 340, 10, 100)){ // Maze 3
        if (checkRobotReachedEnd(&robot, 640-10-320, 480, 100, 10)){ //Maze 4
             /* Changed as clock() gives poor results on mac

            end_time = clock();

            msec = (end_time-start_time) * 1000 / CLOCKS_PER_SEC;

            */

            gettimeofday(&end_time, 0);

            msec = ((end_time.tv_sec - start_time.tv_sec)*1000)+(end_time.tv_usec - start_time.tv_usec)/1000;
            robotSuccess(&robot, msec);
        }
        else if(checkRobotHitWalls(&robot, head))
            robotCrash(&robot);
        //Otherwise compute sensor information
        else {
            front_left_sensor = checkRobotSensorFrontLeftAllWalls(&robot, head);
            if (front_left_sensor>0)
                printf("Getting close on the front left. Score = %d\n", front_left_sensor);

            front_right_sensor = checkRobotSensorFrontRightAllWalls(&robot, head);
            if (front_right_sensor>0)
                printf("Getting close on the front right. Score = %d\n", front_right_sensor);

            back_left_sensor = checkRobotSensorBackLeftAllWalls(&robot, head);
            if (back_left_sensor>0)
                printf("Getting close on the back left. Score = %d\n", back_left_sensor);
        }
        robotUpdate(renderer, &robot);
        updateAllWalls(head, renderer);

        // Check for user input
        SDL_RenderPresent(renderer);
        while(SDL_PollEvent(&event)){
            if(event.type == SDL_QUIT){
                done = 1;
            }
            const Uint8 *state = SDL_GetKeyboardState(NULL);
            if(state[SDL_SCANCODE_UP] && robot.direction != DOWN){
                robot.direction = UP;
            }
            if(state[SDL_SCANCODE_DOWN] && robot.direction != UP){
                robot.direction = DOWN;
            }
            if(state[SDL_SCANCODE_LEFT] && robot.direction != RIGHT){
                robot.direction = LEFT;
            }
            if(state[SDL_SCANCODE_RIGHT] && robot.direction != LEFT){
                robot.direction = RIGHT;
            }
            if(state[SDL_SCANCODE_SPACE]){
                setup_robot(&robot);
            }
            if(state[SDL_SCANCODE_RETURN]){
                robot.auto_mode = 1;
                /* Changed as clock() gives poor results on mac
                start_time = clock(); */
                gettimeofday(&start_time, 0);
            }
        }

        SDL_Delay(120);
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    printf("DEAD\n");
}
