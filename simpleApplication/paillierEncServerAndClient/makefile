serverObjects =server.o PaillierCryptoSystem.o PaillierCiphertext.o 
clientObjects =client.o
sourcePath=./source/

targets=bin/server ./bin/client
paillierHeaderPath = $(sourcePath)server/paillier
$(targets):$(serverObjects) $(clientObjects)
	g++ -o ./bin/server $(serverObjects) -I $(paillierHeaderPath) -lgmp -lgmpxx
	g++ -o ./bin/client client.o
	rm -rf *.o

server.o:$(sourcePath)server/server.cpp
	g++ -o server.o -c $(sourcePath)server/server.cpp -I $(paillierHeaderPath)

PaillierCryptoSystem.o:$(sourcePath)server/paillier/PaillierCryptoSystem.cpp
	g++ -o PaillierCryptoSystem.o -c $(sourcePath)server/paillier/PaillierCryptoSystem.cpp

PaillierCiphertext.o:$(sourcePath)server/paillier/PaillierCiphertext.cpp
	g++ -o PaillierCiphertext.o -c $(sourcePath)server/paillier/PaillierCiphertext.cpp

client.o:$(sourcePath)client/client.cpp
	g++ -o client.o -c $(sourcePath)client/client.cpp


