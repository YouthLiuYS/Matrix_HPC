import pygame
pygame.init()
class gameinterface():
    def __init__(self):
        # set the screen of the game
        self.screen = pygame.display.set_mode((350,500))
        # set some colors 
        self.backgroundColor = (255,255,255)
        #set the tittle of the game interface
        pygame.display.set_caption(' Aircraft war')