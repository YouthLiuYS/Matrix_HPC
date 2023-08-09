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
    def __init__(self): 
        #Define the speed of the ball
        #This is the ball speed
        ballSpeed = [5,5]
    # the method to draw circles
    def draw_Circle(self, screen, color, index, radius, width):
        return pygame.draw.circle(screen, color, index, radius, width)