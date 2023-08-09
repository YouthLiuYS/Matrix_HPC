import sys,pygame
from turtle import width
pygame.init()
#Define the width and height of the screen
#This is the window size
size = width, height= 800, 800
#Create the game window
screen = pygame.display.set_mode(size)
#Define the background color
backgroundColor = (255,255,255)
class ball():
  #Define the speed of the ball
  #This is the ball speed
  ballSpeed = [5,5]
  # the method to draw circles
  def draw_Circle(self, screen, color, index, radius, width):
    return pygame.draw.circle(screen, color, index, radius, width)


isRunning = True
while isRunning:
  for event in pygame.event.get():
    if event.type == pygame.QUIT: sys.exit()

    screen.fill(backgroundColor)
    #Define the first ball
    ball_first = ball().draw_Circle(screen, (0,0,0), [100,100], 50, 0)
    #Define the second ball
    ball_second = ball().draw_Circle(screen,(0,0,0), [300,300], 50, 0)
    pygame.display.update()#刷新显示
    
  
  
  
