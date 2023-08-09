import random
class people:
    characters={"strength":12,"dexterity":20,"consitution":16,
            "intelligence":18,"wisdom":18,"charisma":20}
    characters["hitpoints"]=characters["consitution"]*30+50

    def printPlayerStats(self):
         for key in self.characters:
             print(key+":"+str(self.characters[key]))

    def printHitpoints(self):
        print(self.characters["hitpoints"])
        

    def attack(self):
        return random.randint(1,self.characters["strength"])

    def defense(self):
        defenseNumber=random.randint(1,20)
        if defenseNumber<self.characters["dexterity"]:
            return defenseNumber
            pass
        else:
            defenseNumber=defenseNumber-self.attack
            return defenseNumber

    def heal(self):
        self.characters["hitpoints"]+=random.randint(1,10)
    
def main():
        peopleOne=people()
        peopleOne.printPlayerStats()
        print("the hitpoint is :") 
        peopleOne.printHitpoints()
        print("the attack is : {}".format(peopleOne.attack()))
        print("the defense is : {}".format(peopleOne.defense()))
        peopleOne.heal()
        print("the peopleOne is healed and his/hers hitpoint is : {}".format(peopleOne.characters["hitpoints"]))
if __name__=='__main__':
        main()




