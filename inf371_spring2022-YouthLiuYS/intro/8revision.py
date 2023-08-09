import random
class people:
    def __init__(self,strength,dexterity,consitution,intelligence,wisdom,charisma):
        self.characters=characters={}
        characters["strength"]=int(strength)
        characters["dexterity"]=int(dexterity)
        characters["consitution"]=int(consitution)
        characters["intelligence"]=int(intelligence)
        characters["wisdom"]=int(wisdom)
        characters["charisma"]=int(charisma)
        characters["hitpoints"]=characters["consitution"]*30+50
        pass

    def printPlayerStats(self):
        print("The stats of player are :")
        for key in self.characters:
            print(key+":"+str(self.characters[key]))

    def printHitpoints(self):
        print("the hitpoint is {}:".format(self.characters["hitpoints"]))
        

    def attack(self):
        return random.randint(1,self.characters["strength"])

    def defense(self):
        defenseNumber=random.randint(1,20)
        if defenseNumber<self.characters["dexterity"]:
            return defenseNumber
            pass
        else:
            defenseNumber=defenseNumber-self.attack()
            return defenseNumber

    def heal(self):
        healNum=random.randint(1,10)
        self.characters["hitpoints"]+=healNum
        return healNum
 
def main():
    strength=input("strength:")
    dexterity=input("dexterity:")
    consitution=input("consitution:")
    intelligence=input("intelligence:")
    wisdom=input("wisdom:")
    hitpoints=input("hitpoints:")
    peopleOne=people(strength,dexterity,consitution,intelligence,wisdom,hitpoints)
    peopleOne.printPlayerStats()
    peopleOne.printHitpoints()
    print("the attack is : {}".format(peopleOne.attack()))
    print("the defense is : {}".format(peopleOne.defense()))
    print("the heal number is :{}".format(peopleOne.heal()))
    print("the peopleOne is healed and his/hers hitpoint is : {}".format(peopleOne.characters["hitpoints"]))

if __name__=='__main__':
    main()




