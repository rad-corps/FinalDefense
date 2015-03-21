g++ \
./source/bullet.cpp \
./source/DatabaseManager.cpp \
./source/Enemy1.cpp \
./source/Enemy2.cpp \
./source/EnemyBase.cpp \
./source/EnemyBullet.cpp \
./source/FrameworkHelpers.cpp \
./source/GameController.cpp \
./source/GLAHGraphics.cpp \
./source/HighScoreFile.cpp \
./source/Hud.cpp \
./source/Level1.cpp \
./source/LevelBase.cpp \
./source/main.cpp \
./source/MainMenu.cpp \
./source/PauseMenu.cpp \
./source/Player.cpp \
./source/PowerUp.cpp \
./source/SpawnPointGenerator.cpp \
./source/Vector.cpp \
-I./include \
-lSDL2 \
-lSDL2_image \
-lsqlite3 \
-w 

mv ./a.out ./resources/a.out
