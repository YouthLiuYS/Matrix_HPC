from multiprocessing import Event
import sys,pygame,random
from turtle import circle, width
pygame.init()
#Define the width and height of the screen
#This is the window size
size = width, height= 800, 800
#Create the game window
screen = pygame.display.set_mode(size)
#Define the background color
backgroundColor = (255,255,255)
class ball():
    def __init__(self,circle_x,circle_y): 
        #Define the speed of the ball
        #This is the ball speed
        self.circle_x = circle_x
        self.circle_y = circle_y
        self.ballSpeed = [0.5,0.5]
    # the method to draw circles
    def draw_Circle(self, screen, color, radius, width):
        return pygame.draw.circle(screen, color, [self.circle_x,self.circle_y], radius, width)
    def moveKeyboard(self,event):
        if event.key == pygame.K_LEFT:
            self.circle_x -= self.ballSpeed[0]
        if event.key == pygame.K_RIGHT:
            self.circle_x += self.ballSpeed[0] 
        if event.key == pygame.K_UP:
            self.circle_y -= self.ballSpeed[1]
        if event.key == pygame.K_DOWN:
            self.circle_y += self.ballSpeed[1]
        if event.key ==pygame.K_SPACE:
            self.ballSpeed[0] += 5
            self.ballSpeed[1] += 5
    def ballMove(self):
        self.circle_x += self.ballSpeed[0]
        self.circle_y += self.ballSpeed[1]
        if self.circle_x-30 < 0 or self.circle_x+30 > width:
            self.ballSpeed[0] = -self.ballSpeed[0]
        if self.circle_y-30 < 0 or self.circle_y+30 > height:
            self.ballSpeed[1] = -self.ballSpeed[1]
    def moveMouse(self,moveposition,realpositon):
        self.circle_x = moveposition[0]
        self.circle_y = moveposition[1]
        self.circle_x += realpositon[0]
        self.circle_y += realpositon[1]
    def collision(self,rect_1,rect_2):
        if pygame.Rect.colliderect(rect_1,rect_2):
            self.ballSpeed[0] = random.uniform(-1,1)
            self.ballSpeed[1] = random.uniform(-1,1)
