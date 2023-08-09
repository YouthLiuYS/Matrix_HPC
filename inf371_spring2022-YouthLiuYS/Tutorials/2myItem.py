import sys,pygame
from turtle import speed, width
pygame.init()
class Item():
    def __init__(self,fileName, screenSize, speed):
        self.picture = pygame.image.load(fileName)
        self.rect = self.picture.get_rect()
        self.speed = speed
        self.width = screenSize[0]
        self.height = screenSize[1]

    def blit(self, screen):
        screen.blit(self.picture, self.rect)
class ball():
  #Define the width and height of the screen
  #This is the window size
  size = width, height= 800, 800
  #Define the speed of the ball
  #This is the ball speed
  ballSpeed = [5,5]
  #Define the background color
  backgroundColor = (255,255,255)
  #Create the game window
  screen = pygame.display.set_mode(size)
  #Define the first ball
  ball_first = Item("Tutorials/ball.gif", size, speed)
  #Define the second ball
  ball_second = Item("Tutorials/ballTwo.png", size, speed)
  isRunning = True
  while isRunning:
    for event in pygame.event.get():
      if event.type == pygame.QUIT: sys.exit()
    screen.fill(backgroundColor)
    ball_first.blit(screen)
    ball_second.blit(screen)
    pygame.display.flip()