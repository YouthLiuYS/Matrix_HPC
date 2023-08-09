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
        super().__init__(circle_x,circle_x)
    
ball_first = drawBall(circle_x,circle_y)
isRunning = True
while isRunning:
  for event in pygame.event.get():
    if event.type == pygame.QUIT: sys.exit()
    if event.type == pygame.KEYDOWN:
        ball_first.moveKeyboard(event)
  screen.fill(backgroundColor)
  #Define the first ball
  ball_first.draw_Circle(screen, (0,0,0), 50, 0)
        
  pygame.display.update()#刷新显示