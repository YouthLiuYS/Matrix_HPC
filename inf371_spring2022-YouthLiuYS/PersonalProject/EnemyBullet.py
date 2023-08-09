import pygame
pygame.init()
class EnemyBullet():
    def __init__(self, pictureFile,EnemyAircraft,screen,screenSize):
        self.picture = pygame.image.load(pictureFile)
        self.rect = self.picture.get_rect()
        self.Coordinate_X = EnemyAircraft.Coordinate_X+EnemyAircraft.rect.width/2-self.rect.width/2
        self.Coordinate_Y = EnemyAircraft.rect.height
        self.screen = screen
        self.screenSize = screenSize
    def move(self):
        self.Coordinate_Y += 0.05
    def blit(self):
        if self.Coordinate_Y < self.screenSize[1]:
            self.screen.blit(self.picture, (self.Coordinate_X,self.Coordinate_Y))