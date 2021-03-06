all:
	g++ -std=c++17 -I ./header -I ./scripts/header -o ./clothSimV2 ./source/*.cpp ./scripts/source/*.cpp ./source/img/*.cpp -L"lib" -Wall -lSDL2main -lSDL2 -lSDL2_ttf -pthread
	./clothSimV2
compile:
	g++ -std=c++17 -I ./header -I ./scripts/header -o ./clothSimV2 ./source/*.cpp ./scripts/source/*.cpp ./source/img/*.cpp -L"lib" -Wall -lSDL2main -lSDL2 -lSDL2_ttf -pthread
run:
	./clothSimV2
push:
	git add ./header ./source ./scripts/header ./scripts/source ./fonts ./img ./Makefile ./README.md
	git commit -a -m "Readme Update"
	git push origin main
