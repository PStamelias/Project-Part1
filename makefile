all: lsh cube cluster
lsh: main1.c 
	gcc -o lsh main1.c
cube: main2.c
	gcc -o cube main2.c
cluster: main3.c
	gcc -o cluster main3.c
clean:
	rm cube
	rm lsh
	rm cluster
