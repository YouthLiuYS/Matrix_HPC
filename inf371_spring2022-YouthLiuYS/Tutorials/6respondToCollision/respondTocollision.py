from shutil import move
import sys,pygame
from turtle import width
from myball import ball
pygame.init()
#Define the width and height of the screen
#This is the window size
size = width, height= 800, 800
#Create the game window
screen = pygame.display.set_mode(size)
#Define the background color
backgroundColor = (255,255,255)
circle_x = 100
circle_y = 100
class drawBall(ball):
    def __init__(self,circle_x,circle_y):
        super().__init__(circle_x,circle_y)

ball_first = drawBall(circle_x,circle_y)
ball_second = drawBall(circle_x=300, circle_y=300)
ball_First = ball_first.draw_Circle(screen, (0,0,0), 30, 0)
ball_Second = ball_second.draw_Circle(screen, (0,0,0), 30, 0)
isRunning = True
while isRunning:
    for event in pygame.event.get():
        if event.type == pygame.QUIT: sys.exit()
    ball_first.collision(ball_First,ball_Second)
    ball_second.collision(ball_First,ball_Second)   
    
    ball_first.ballMove()
    ball_second.ballMove()
    screen.fill(backgroundColor)
    #Define the first ball
    ball_First = ball_first.draw_Circle(screen, (0,0,0), 30, 0)
    ball_Second = ball_second.draw_Circle(screen, (0,0,0), 30, 0)
    pygame.display.update()#刷新显示