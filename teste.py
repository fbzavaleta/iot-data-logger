contador = 0
class prints():

    def __init__(self):

        self.self = self
        self.count = 0
    
    def acum(self):
        self.count+=1
        print(self.count)
        



while contador < 10:

    prints().acum() 

    contador+=1

    #no guarda en memoria