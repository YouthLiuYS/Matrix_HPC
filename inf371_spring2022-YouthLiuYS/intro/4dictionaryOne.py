from multiprocessing.sharedctypes import Value
from turtle import speed


characters={"strength":12,"dexterity":20,"consitution":16,
            "intelligence":18,"wisdom":18,"charisma":20}
print(characters)
for key,value in characters.items():
    print(key,value)
if("strength" in characters):
    print(characters["strength"])
else:
    print(" strength isn't a character stat.")
if("speed" in characters):
    print(characters["speed"])
else:
    print("speed isn't a character stat")
