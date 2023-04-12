# Détection du système d'exploitation
ifeq ($(shell uname),Darwin)
	OS = macOS
else ifeq ($(shell uname),Linux)
	OS = Linux
else
	OS = Windows_NT
endif

# Compilateur
CC = gcc
# Paramètres de la compilation
CFLAGS = -g -Wall -Llib -lm

# Nom de l'exécutable
EXEC = DarickVSTheWorld

# Librairies intégrées
LIBS = -lm

# ------------------------------------ SDL ----------------------------------- #

# Oubliez pas de modifier le chemin d'accès à votre SDL2 !
INCLUDE_DIR = include
SDL_CHEMIN_DIR=E:/SDL2
SDL_LIB_DIR=${SDL_CHEMIN_DIR}/lib
SDL_INC_DIR=${SDL_CHEMIN_DIR}/include
SDL_FLAGS = -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf

INCS = -I${SDL_INC_DIR} 

ifeq ($(OS),Windows_NT)
	SDL_LIBS = -L${SDL_LIB_DIR} -lmingw32 ${SDL_FLAGS}
else
	SDL_LIBS = -L${SDL_LIB_DIR} ${SDL_FLAGS}
endif

# ------------------------------- Arborescence ------------------------------- #

# Nom des dossiers contenant les ressources du programme
BINDIR = bin
INCDIR = include
OBJDIR = obj

# Bien placer les fichiers sources dans un dossier nommé ainsi :
SRCDIR = src

DIRS = $(BINDIR) $(OBJDIR) 

# ---------------------------------- Sources --------------------------------- #

# Sélectionne tous les fichiers sources et les en-têtes
# La fonction wildcard permet de cibler un ensemble de fichiers
SOURCES = $(wildcard $(SRCDIR)/*.c)
INCLUDES = $(wildcard $(INCDIR)/*.h)

# Crée la variable objects à partir de la variable sources en remplaçant SRC/ par OBJ/ et .c par .o
OBJECTS = $(SOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

# ---------------------------- Compilation Projet ---------------------------- #

# Exécute toutes les règles du makefile
all: $(DIRS) $(BINDIR)/$(EXEC)
	./$(BINDIR)/$(EXEC)

# Crée les dossiers associés aux ressources du programme
# -p : pas d'erreur si le dossier existe déjà 
# Déplace les fichiers sources dans le dossier source
$(BINDIR):
	mkdir -p $(BINDIR)
$(OBJDIR):
	mkdir -p $(OBJDIR)

# Compile les fichiers sources
# $< : Nom de la première dépendance de la liste des dépendances
# $@ : Nom de la cible
$(OBJECTS): $(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c $< -I$(INCLUDE_DIR) -o $@
	@echo "Compilation de "$<" effectuée."

# Exécute l'édition des liens
$(BINDIR)/$(EXEC): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $@ $(LIBS) $(SDL_LIBS)
	@echo "Édition des liens effectuée."

# ------------------------------- Documentation ------------------------------ #

doc:
	doxygen doxyfile
	@echo "Documentation générée"

# --------------------------------- Nettoyage -------------------------------- #

clean:
ifeq ($(OS),Windows_NT)
	del /Q $(OBJDIR)\*.o
else
	rm -rf $(OBJDIR)/*.o
endif
	@echo "Nettoyage des fichiers objets effectué."



