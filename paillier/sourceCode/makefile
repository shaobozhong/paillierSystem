objects=main.o PaillierCryptoSystem.o PaillierPlaintext.o
main:$(objects)
	g++ -o main main.o PaillierCryptoSystem.o PaillierCiphertext.o -lgmp -lgmpxx

PaillierCryptoSystem.o:paillier/PaillierCryptoSystem.cpp
	g++ -c paillier/PaillierCryptoSystem.cpp
PaillierPlaintext.o:paillier/PaillierCiphertext.cpp
	g++ -c paillier/PaillierCiphertext.cpp
main.o:main.cpp
	g++ -c main.cpp -I paillier
