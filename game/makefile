CPP  = g++ -D__DEBUG__
CC   = gcc -D__DEBUG__
OBJ  = animation.o character.o entradasortida.o main.o mundo.o sprite.o static_image.o enemigo.o enemyhandler.o checkpointhandler.o scripthandler.o script.o symboltable.o objeto.o objecthandler.o fxhandler.o phase_info.o characterstatehandler.o keyboardmap.o graphicsfxpostprocessing.o watergraphicfx.o scrollhandler.o game.o timer.o machinimiahandler.o messageboxhandler.o
LINKOBJ  = $(OBJ)
LIBS = -L"/usr/lib" -lalleg -lallegro -lallegro_image -lallegro_primitives -lallegro_font -lallegro_ttf -lallegro_audio -lallegro_acodec -pthread -g
INCS = -I"/usr/include"
CXXINCS = -I"/usr/include/c++/11" -I"/usr/include/c++/11/backward" -I"/usr/include"
BIN  = CamelotRemake.exe
CXXFLAGS = $(CXXINCS) -DALLEGRO -g
CFLAGS = $(INCS) -DALLEGRO_STATICLINK -g
RM = rm -f

.PHONY: all all-before all-after clean clean-custom

all: all-before CamelotRemake.exe all-after


clean: clean-custom
	${RM} $(OBJ) $(BIN)

$(BIN): $(OBJ)
	$(CPP) $(LINKOBJ) -o "CamelotRemake.exe" $(LIBS)

animation.o: animation.cpp
	$(CPP) -c animation.cpp -o animation.o $(CXXFLAGS)

character.o: character.cpp
	$(CPP) -c character.cpp -o character.o $(CXXFLAGS)

entradasortida.o: entradasortida.cpp
	$(CPP) -c entradasortida.cpp -o entradasortida.o $(CXXFLAGS)

main.o: main.cpp
	$(CPP) -c main.cpp -o main.o $(CXXFLAGS)

mundo.o: mundo.cpp
	$(CPP) -c mundo.cpp -o mundo.o $(CXXFLAGS)

sprite.o: sprite.cpp
	$(CPP) -c sprite.cpp -o sprite.o $(CXXFLAGS)

static_image.o: static_image.cpp
	$(CPP) -c static_image.cpp -o static_image.o $(CXXFLAGS)

enemigo.o: enemigo.cpp
	$(CPP) -c enemigo.cpp -o enemigo.o $(CXXFLAGS)

enemyhandler.o: enemyhandler.cpp
	$(CPP) -c enemyhandler.cpp -o enemyhandler.o $(CXXFLAGS)

checkpointhandler.o: checkpointhandler.cpp
	$(CPP) -c checkpointhandler.cpp -o checkpointhandler.o $(CXXFLAGS)

scripthandler.o: scripthandler.cpp
	$(CPP) -c scripthandler.cpp -o scripthandler.o $(CXXFLAGS)

script.o: script.cpp
	$(CPP) -c script.cpp -o script.o $(CXXFLAGS)

symboltable.o: symboltable.cpp
	$(CPP) -c symboltable.cpp -o symboltable.o $(CXXFLAGS)

objeto.o: objeto.cpp
	$(CPP) -c objeto.cpp -o objeto.o $(CXXFLAGS)

objecthandler.o: objecthandler.cpp
	$(CPP) -c objecthandler.cpp -o objecthandler.o $(CXXFLAGS)

fxhandler.o: fxhandler.cpp
	$(CPP) -c fxhandler.cpp -o fxhandler.o $(CXXFLAGS)

phase_info.o: phase_info.cpp
	$(CPP) -c phase_info.cpp -o phase_info.o $(CXXFLAGS)

characterstatehandler.o: characterstatehandler.cpp
	$(CPP) -c characterstatehandler.cpp -o characterstatehandler.o $(CXXFLAGS)

keyboardmap.o: keyboardmap.cpp
	$(CPP) -c keyboardmap.cpp -o keyboardmap.o $(CXXFLAGS)

graphicsfxpostprocessing.o: graphicsfxpostprocessing.cpp
	$(CPP) -c graphicsfxpostprocessing.cpp -o graphicsfxpostprocessing.o $(CXXFLAGS)

watergraphicfx.o: watergraphicfx.cpp
	$(CPP) -c watergraphicfx.cpp -o watergraphicfx.o $(CXXFLAGS)

scrollhandler.o: scrollhandler.cpp
	$(CPP) -c scrollhandler.cpp -o scrollhandler.o $(CXXFLAGS)

game.o: game.cpp
	$(CPP) -c game.cpp -o game.o $(CXXFLAGS)

timer.o: timer.cpp
	$(CPP) -c timer.cpp -o timer.o $(CXXFLAGS)

machinimiahandler.o: machinimiahandler.cpp
	$(CPP) -c machinimiahandler.cpp -o machinimiahandler.o $(CXXFLAGS)

messageboxhandler.o: messageboxhandler.cpp
	$(CPP) -c messageboxhandler.cpp -o messageboxhandler.o $(CXXFLAGS)
