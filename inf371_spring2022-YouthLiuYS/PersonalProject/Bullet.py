import pygame


class bullet():
    def __init__(self, pictureFile,aircraft,screen,screenSize):
        self.picture = pygame.image.load(pictureFile)
        self.rect = self.picture.get_rect()
        self.Coordinate_X = aircraft.Coordinate_X+aircraft.rect.width/2-self.rect.width/2
        self.Coordinate_Y = aircraft.Coordinate_Y-self.rect.height
        self.screen = screen
    def move(self):
        self.Coordinate_Y -= 0.1
    def blit(self):
        if self.Coordinate_Y > 0:
            self.screen.blit(self.picture, (self.Coordinate_X,self.Coordinate_Y))

