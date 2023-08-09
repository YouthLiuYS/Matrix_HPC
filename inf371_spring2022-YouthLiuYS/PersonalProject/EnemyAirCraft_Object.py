from time import time
import pygame
import random
from EnemyBullet import EnemyBullet
pygame.init()
class EnemyAircraft:
    def __init__(self,pictureFile,screen, screenSize):
        self.Coordinate_X = 150
        self.Coordinate_Y = 0
        self.picture = pygame.image.load(pictureFile)
        self.rect = self.picture.get_rect()
        # the screen is where the aircraft object displays on
        self.screen = screen
        # the screenSize is the width and height about the game interface
        self.screenSize = screenSize
        self.bulletList = []
        self.direction = "left"
    def move(self):
        if self.direction == "right" :
            self.Coordinate_X += 0.05
        elif self.direction == "left" :
            self.Coordinate_X -= 0.05
        
        if self.Coordinate_X >= self.screenSize[0] -self.rect.width:
            self.direction = "left"
        elif self.Coordinate_X <= 0 :
            self.direction = "right"

    def blitAircraft(self):
        self.screen.blit(self.picture,(self.Coordinate_X,self.Coordinate_Y))
    def blitAllBullets(self):
        Cross_Border_Bullets = []
        for bullet in self.bulletList:
            if bullet.Coordinate_Y >self.screenSize[1]:
                Cross_Border_Bullets.append(bullet)
        for bullet in Cross_Border_Bullets:
            self.bulletList.remove(bullet)
        for bullet in self.bulletList:
            bullet.blit()
            bullet.move()
    def Fire_a_Bullet(self):
        number = random.randint(1,3500)
        if number == 3:
            newBullet = EnemyBullet("PersonalProject/Enemy_bullet.png",self,self.screen,self.screenSize)
            self.bulletList.append(newBullet)
        