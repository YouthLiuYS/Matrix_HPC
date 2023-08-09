import imp
from turtle import screensize
from Bullet import bullet

import pygame
pygame.init()
class aircraft():
    def __init__(self, pictureFile,screen, screenSize):
        self.Coordinate_X = 150
        self.Coordinate_Y = 450
        self.picture = pygame.image.load(pictureFile)
        self.rect = self.picture.get_rect()
        # the screen is where the aircraft object displays on
        self.screen = screen
        # the screenSize is the width and height about the game interface
        self.screenSize = screenSize
        self.bulletList = []
        
    def moveLeft(self):
        if self.Coordinate_X > 0 :
            self.Coordinate_X -= 9
            print('Left')
    def moveRight(self):
        if self.Coordinate_X < self.screenSize[0]:
            self.Coordinate_X += 9
            print('Right')
    def moveUp(self):
        if self.Coordinate_Y > 0:
            self.Coordinate_Y -= 9
            print('Up')
    def moveDown(self):
        if self.Coordinate_Y < self.screenSize[1]:
            self.Coordinate_Y += 9
            print('Down')
    def moveByKeyboard(self,event):
        if event.key == pygame.K_a:
            self.moveLeft()
        if event.key == pygame.K_d:
            self.moveRight() 
        if event.key == pygame.K_w:
            self.moveUp()
        if event.key == pygame.K_s:
            self.moveDown()
        if event.key == pygame.K_SPACE:
            self.Fire_a_Bullet()
    def blitAircraft(self):
        self.screen.blit(self.picture, (self.Coordinate_X,self.Coordinate_Y))
    def blitAllBullets(self):
        Cross_Border_Bullets = []
        for bullet in self.bulletList:
            if bullet.Coordinate_Y < 0:
                Cross_Border_Bullets.append(bullet)
        for bullet in Cross_Border_Bullets:
            self.bulletList.remove(bullet)
        for bullet in self.bulletList:
            bullet.blit()
            bullet.move()
    def Fire_a_Bullet(self):
        newBullet = bullet("PersonalProject/player_bullet.png",self,self.screen,self.screenSize)
        self.bulletList.append(newBullet)
        



