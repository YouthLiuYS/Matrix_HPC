import random
keys=["strength", "dexterity", "constitution", "intelligence", "wisdom", "charisma"]
dictionary={}
for key in keys:
    dictionary[key]=random.randint(1,20)
    print(key+":"+str(dictionary[key]))

