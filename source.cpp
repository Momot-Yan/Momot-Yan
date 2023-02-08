#include <stdio.h>
#include <stdlib.h>
#include<math.h>
#include <conio.h>
#include <string.h>

typedef struct 
{
  char **board;
  char **players_names;
  int ID;
} game_struct;

void Game (game_struct *game, int ID, int *count_games);
int Select_Op (int *count_games);
bool What_Next ();
void Print_Win (game_struct *game, bool winner, char **players_names, int **connected_four);
void Set_Game (game_struct *game, int ID);
bool Save_Game (game_struct *game, int *count_games);
void Print_Game_Info (game_struct *game);
bool Find_Game_Info (game_struct *game, int ID, char* text);
void Find_Games_By_Player_Name (char* text, char *name);
bool Is_Num (char *string, int len);
int Str_To_Num (char *str, int len);
void Copy_Struct (game_struct *game, char *text, int start_of_game_info, int len_of_game_info);
int File_To_Text (char *text);
bool Load_Game (game_struct *game, int ID);
void Free_Array (int **arr, int rows);
void Free_Char_Array (char **arr, int rows);
char **Set_Board ();
void Print_Board (char **board, int **connected_four);
void Make_Step (game_struct *game, int *count_games, char *player, bool *win, int **connected_four);
void Put_Symbol (char **board, int col, int *row);
bool Check_Win (char *player, char **board, int row, int col, int **connected_four);
bool Check_Cells_Arr (char **board, int **cells_arr);

////////////////////////////////////////////////////////////// Project task

/*
Project task: Write a program that implements a computer version of the connect four (https://en.wikipedia.org/wiki/Connect_Four) game. 
This game is played by two players with the symbols ‘X’ and ‘O’ on a board that is 7 cells wide and 6 cells high. 
Players by points choose the column in which their symbol will be placed on above the symbols that are already in that column. 
The winner is the player that first makes a row of 4 symbols either vertically, horizontally or diagonally. 
When launched, the program should display a main menu with the following three options: 1) Play a new game, 2) Load an already saved game, 3) Quit the game.
If the option "1) Play a new game" is selected, then the program should allow players to enter their names.
First, player "X" should make his move by entering an integer number from 1 to 7, which indicates the column in which he would like to place his symbol.
After that, the players take turns entering their symbols on the board. After each move, the program should display the state of the board.
The game ends either if one of the players connects 4 symbols in a column/row/diagonal, or if the entire field is filled with symbols and no one wins.
Program should check these ending conditions after each turn and properly inform the players if the game has ended and who won. 
If someone wins, the program should print a board with the highlighted connected symbols that caused the victory (the "Y" symbols in the places of the connecteded symbols).
After the game ends, players should be asked if they would like to start a new game or go back to the main menu.

If at some point one of the players enters 0 instead of a integer from 1 to 7, the program should save the current game (game ID, board state, and players names).
If during the game the player selects a column already filled with symbols, the program should inform him that such a move is not allowed and ask him to select some other column.
Each new saved game should have a unique ID of the saved game.
After saving the game, the program should inform the players that their game has been saved and print the ID of the saved game, after which the game play should continue in the described way without further interruptions. 
After saving, the result of the game should be saved inside the "result.txt" file.
If option "2) Load an already saved game" is chosen, a new menu opens with the following options:
1) List of all saved games, 2) List of all saved games for a particular player, 3) Show the board of one of the saved games, 
4) Load the game, 5) Return to the main menu.
If "1) List of all saved games" is selected, then the program should list all the games saved in the file. Games should be listed in the following format:
ID, "X" player name, "O" player name, the number of free cells left on the board. Each saved game should be printed on a new line.
If "2) List all saved games for a particular player" is selected, then the program should ask the user to enter a name. It should then list all the games, 
which have that name as one of the players in the same format as specified above. 
If "3) Show the board of one of the saved games" is selected,
the program should ask the user to enter a game ID and then print out the players names and the board for that game.
If "4) Load Game" is selected, the program should ask the user to enter the saved game ID and then start the game from the saved point.
From this point on, the program should behave in the same way as when a new game is played. After the loaded game is finished, 
the program should allow players to either start a new game (with an empty board) or return to the main menu, i.e. the same choice that they have when they play a game from an empty board
If in options 3) and 4) the user selects a non-existent ID, the program should inform him about this and ask him to enter the correct ID.
*/

/*
Задача финального проекта: Написать игру «Соедини четыре» (https://en.wikipedia.org/wiki/Connect_Four). Игра ведется на доске шириной 7 полей и высотой 6 полей. 
Играют два игрока с символами «X» и «O». Игроки по оч. выбрают столбец, в котором их символ будет размещен над символами, которые уже находятся в этом столбце. 
Победителем становится игрок, который первым соберет ряд из 4 символов по вертикали, горизонтали или диагонали. 
При запуске программа должна отобразить главное меню со следующими тремя опциями: 1) Играть в новую игру, 2) Загрузить уже сохраненную игру, 3) Выйти из игры. 
Если выбран вариант "1) Играть в новую игру", то программа должна позволять игрокам введите их имена. 
Сначала игрок «X» должен сделать свой ход, введя целое число от 1 до 7, которое указывает столбец, в который он хотел бы поместить свой символ. 
После этого игроки по оч. вводят свой знак на доску. После каждого хода программа должна выводить состояние доски. 
Игра заканчивается либо в том случае, если один из игроков соединит 4 символа в столбец/строку/диагональ, либо если все поле заполнено знаками и никто не выиграл. 
Программа должна проверять эти условия окончания после каждого хода и если закончилась ли игра, то должным образом информировать игроков, кто выиграл. 
Если кто-то выигрывает, программа должна распечатать доску с выделенными связанными символами, которые привели к победе (символы «Y» на местах связанных символов). 
После окончания игры игроков следует спросить, хотят ли они начать новую игру или вернуться в главное меню. 
Если во время игры игрок выбирает столбец, уже заполненный символами, программа должна сообщить ему, что такой ход недопустим, и попросить его выбрать другой столбец.
Если в какой-то момент один из игроков введет 0 вместо числа от 1 до 7, программа должна сохранить текущую игру (ID игры, состояние доски и имена игроков). 
Каждая новая сохраненная игра должна иметь уникальный идентификатор сохраненной игры. 
После сохранения игры программа должна сообщить игрокам, что их игра была сохранена, и распечатать ID сохраненной игры, после чего игра должна продолжаться описанным образом без дальнейших перерывов. 
После сохранения результат игры должен быть сохранен внутри файла "result.txt". 
Если выбран вариант "2) Загрузить уже сохраненную игру", откроется новое меню со следующими параметрами:
1) Список всех сохраненных игр, 2) Список всех сохраненных игр для конкретного игрока, 
3) Показать доску одной из сохраненных игр, 4) Загрузить игру, 5) Вернуться в главное меню.
Если выбрано "1) Список всех сохраненных игр", то программа должна напечатать все игры, сохраненные в файле. Игры должны быть перечислены в следующем формате: 
ID, имя игрока «X», имя игрока «O», количество свободных полей, оставшихся на доске. Каждая сохраненная игра должна быть напечатана с новой строки. 
Если выбрано "2) Перечислите все сохраненные игры для конкретного игрока", то программа должна попросить пользователя ввести имя. Затем она должна напечатать все игры, 
где это имя записано как имя у одного из игроков (в формате вывода, указаном выше). Если выбрано "3) Показать поле одной из сохраненных игр", 
программа должна попросить пользователя ввести ID игры, а затем распечатать имена игроков и поле для этой игры. 
Если выбрано "4) Загрузить игру", программа должна попросить пользователя ввести ID сохраненной игры, а затем начать игру с сохраненной точки. 
С этого момента программа должна работать, как и при запуске новой игры. После завершения загруженной игры программа должна позволять игрокам 
либо начать новую игру (с пустой доской), либо вернуться в главное меню, т. е. тот же выбор, что и при игре с пустой доски. 
Если в вариантах 3) и 4) пользователь выбирает несуществующий ID, программа должна сообщить ему об этом и попросить его ввести корректный ID. 
Доставка: учащиеся должны отправить свое решение по почте в виде текстового файла, содержащего исполняемый код, или ZIP-файла, содержащего полный проект. 
Код должен содержать комментарии, поясняющие логику решения. 
*/

////////////////////////////////////////////////////////////// My solution

/*
Solution
Firstly: Display a menu with options: start a new game, load a saved game, exit the game.
Secondly: Create an array called board[6][7] and ask the players to enter their names. Display a 6x7 basic board.
Thirdly: The player with the X character makes the first move. You need to ask the user to enter an integer from 1 to 7.
Fourthly: If 0 is entered, then the game is saved as a structure (containing the names of the players in an array of characters 2*10 and the current state of the field in the form of an array 6*7).
Otherwise, the array is updated, the character of the player is placed at the end of the selected array column (unless it is full) (otherwise the program reports that the selected column is full and asks to choose another one). For example, if 1 is chosen on the first move, then X is placed in the array at the end of the first column.
Fifthly: Checking for a winning combination: 3 columns, 4 rows, 3+3 diagonals are checked around the newly placed symbol.
Sixthly: While no one has won and the field is not yet filled, repeat steps 3-5.

Решение
Первое: Вывести на экран меню с опциями: начать новую игру, загрузить сохраненную игру, выйти из игры.
Второе: Создать массив с именем board[6][7] и попросить игроков ввести свои имена. Вывести на экран базовую доску 6x7, используя константы HEIGHT 6, WIDTH 7. 
Третье: Первым делает ход игрок с символом X. Нужно попросить пользователя ввести целое число от 1 до 7.
Четвертое: Если введен 0, то игра сохраняется в виде структуры (содержащей имена игроков в массиве символов 2*10 и текущее состояние поля в виде массива 6*7).
Иначе массив обновлется, в конец выбранного столбца массива (если только он не полный) помещается символ игрока (иначе программа сообщает о заполненности выбранного столбца и просит выбрать другой). Например, если на первом ходу выбран 1, то X помещается в массив в конце первого столбца. 
Пятое: Проверка наличия выигрышной комбинации: вокруг только что поставленного символа проверяются 3 столбца, 4 строки, 3+3 диагонали. 
Шестое: Пока никто не выиграл и поле еще не заполнено, повторять действия 3-5.
*/



int main () {
  // There are no saved games at the start
  int count_games = 0;

  // Function Select_Op () completes the choise of user
  // The return value is one of the numbers: -2, -1, 0, positive numbers
  // -2 indicates exit, -1 indicates new game, other results indicate the ID of loading game
  int ID = Select_Op (&count_games);
  while (ID != -2){
    game_struct game;
    Set_Game (&game, ID);
    Game (&game, ID, &count_games);
    ID = Select_Op (&count_games);
  }

  printf (" Exit of the game \n ");
  getch ();
}

//////////////////////////////////////////////////////////////      Gameplay

void Game (game_struct *game, int ID, int *count_games)
{
  bool win = false, winner, start_over;
  char player = 'X', **players_names = (char **)malloc (2*sizeof (char *));
  for (int i = 0; i < 2; i++) {
    players_names[i] = (char *)malloc (20*sizeof (char));
  }

  int **connected_four = (int **)malloc (4*sizeof (int *));
  for (int i = 0; i < 4; i++) {
    connected_four[i] = (int *)malloc (2*sizeof (int));
    connected_four[i][0] = -1;
    connected_four[i][1] = -1;
  }

  // Since the game "game" is running, the names of the players saved in this game are displayed
  printf ("\n Names: %20s (player X), %20s (player O)", (*game).players_names[0], (*game).players_names[1]);
  
  Print_Board ((*game).board, connected_four);
  printf ("\n Player X makes the first move");
  while (!win){
    // Players take turns making their moves and then the player switches
    Make_Step (game, count_games, &player, &win, connected_four);
    player = (player == 'X')? 'O' : 'X';
  }
  if (win) {
    winner = (player == 'O');
    //printf ("\n Name of winner: %s", &(players_names[winner]));
    Print_Win (game, winner, players_names, connected_four);

    printf ("\n Do you want to start a new game? Enter 1 to start or 0 to get back to menu: ");
    scanf ("%d", &start_over); 
    if (start_over){
      // The value -1 is the new game indicator 
      Set_Game (game, -1);
      Game (game, -1, count_games);
    }
    else{
      Free_Char_Array (players_names, 1);
      Free_Array (connected_four, 4);
      Free_Char_Array (game->board, 6);
    }
  }
}

// Function for getting user's choise
int Select_Op (int *count_games){
  int op;
  printf ("\n Menu: \n Print 1 to Play a new game  \n Print 2 to Load already saved game  \n Print 3 to Exit the game \n ");
  scanf ("%d", &op); 
  printf (" Choosed option: %d ", op);

  switch (op) {
  case 1:
    printf (" Play a new game \n ");
    return -1;
  case 2:
    // 1) Список всех сохраненных игр, 2) Список всех сохраненных игр для конкретного игрока, 3) Показать доску одной из сохраненных игр, 4) Загрузить игру, 5) Вернуться в главное меню.
    printf ("\n Menu: \n 1) List of all saved games, \n 2) List of all saved games for a particular player, \n 3) Show the board of one of the saved games, \n 4) Load the game, \n 5) Return to the main menu. \n ");
    scanf ("%d", &op);
    // Если выбрано "1) Список всех сохраненных игр", то программа должна напечатать все игры, сохраненные в файле. Игры должны быть перечислены в следующем формате: ID, имя игрока «X», имя игрока «O», количество свободных полей, оставшихся на доске. Каждая сохраненная игра должна быть напечатана с новой строки. Если выбрано "2) Перечислите все сохраненные игры для конкретного игрока", то программа должна попросить пользователя ввести имя. Затем она должна напечатать все игры, где это имя записано как имя у одного из игроков (в формате вывода, указаном выше). Если выбрано "3) Показать поле одной из сохраненных игр", программа должна пользователя ввести ID игры, а затем распечатать имена игроков и поле для этой игры. Если выбрано "4) Загрузить игру", программа должна попросить пользователя ввести ID сохраненной игры, а затем начать игру с сохраненной точки. 
    // According to the logic of the game, actions 1-3 can be repeated many times, but actions 4 and 5 are definitely an exit from the current menu, so only in cases 4 and 5 there is a return
    while (true){
      switch (op) {
      case 1:
        {
          for (int ID_iterator = 0; ID_iterator < *count_games; ID_iterator++) {
            game_struct *game;
            char *text;
            int len = File_To_Text (text);
            if (len == 0)
              printf("\n List of saved games is empty!\n");
            Find_Game_Info (game, ID_iterator, text);
            Print_Game_Info (game);
          }
          break;
        }
      case 2:
        {
          char *name = (char *)malloc (20*sizeof (char));
          name = "";
          while ((strlen (name) < 1) || Is_Num (name, strlen (name))) {
            printf ("\n Please enter the name of player to find games: ");
            scanf ("%20s", name); 
            //fgets(name, sizeof(name), stdin);
          }
          printf ("\n Entered name: %s", name);
          char *text;
          int len = File_To_Text (text);
          if (len == 0)
            printf("\n List of saved games is empty!\n");
          Find_Games_By_Player_Name (text, name);
          break;
        }
      case 3:
        {
          for (int ID_iterator = 0; ID_iterator < *count_games; ID_iterator++) {
            game_struct *game;
            char *text;
            int len = File_To_Text (text);
            if (len == 0)
              printf("\n List of saved games is empty!\n");
            Find_Game_Info (game, ID_iterator, text);

            int **connected_four = (int **)malloc (4*sizeof (int *));
            for (int i = 0; i < 4; i++) {
              connected_four[i] = (int *)malloc (2*sizeof (int));
              connected_four[i][0] = -1;
              connected_four[i][1] = -1;
            }

            Print_Board (game->board, connected_four);
          }
          break;
        }
      case 4:
        {
          int ID;
          while (ID < 0 || ID > *count_games){
            printf (" Please enter the correct game ID, to load already saved game: ");
            scanf ("%d", &ID); 
          }
          return ID;
        }
      case 5:
        {
          return -1;
        }
      }
      printf ("\n Menu: \n 1) List of all saved games, 2) List of all saved games for a particular player, 3) Show the board of one of the saved games, 4) Load the game, 5) Return to the main menu. \n ");
      scanf ("%d", &op);
    }
  default:
    return -2;
  }
}

// Continue working or exit the program
bool What_Next (){
  int answ = 0;
  printf (" Enter 0 to escape the game either 1 to keep on playing: ");
  scanf ("%i", &answ);
  return answ;
}


void Print_Win (game_struct *game, bool winner, char **players_names, int **connected_four){
  // Check for victory, if true, print the board (in which the connected cells are marked with Y) and the name of the winner
  Print_Board ((*game).board, connected_four);
  printf (" The game was ended, the winner is: %s", players_names[winner]);
}

//////////////////////////////////////////////////////////////      game_struct code

void Set_Game (game_struct *game, int ID){
  game_struct temp;
  if (ID == -1) {
    temp.board = Set_Board ();
    temp.players_names = (char **)malloc (2*sizeof (char *));
    for (int i = 0; i < 2; i++) {
      temp.players_names[i] = (char *)malloc (20*sizeof (char));
      temp.players_names[i] = "";
    }
    /*
    temp.players_names[0] = "Jack";
    temp.players_names[1] = "Sparrow";
    */
    while ((strlen (temp.players_names[0]) < 1) || Is_Num (temp.players_names[0], strlen (temp.players_names[0]))) {
      printf ("\n Please enter the name of player X (not empty, spaces are not allowed and letters are required): ");
      scanf ("%20s", temp.players_names[0]); 
    }
    while ((strlen (temp.players_names[0]) < 1) || Is_Num (temp.players_names[0], strlen (temp.players_names[0]))) {
      printf ("\n Please enter the name of player O (not empty, spaces are not allowed and letters are required): ");
      scanf ("%20s", temp.players_names[1]); 
    }
    
    temp.ID = ID;
    game = &temp;
    //Free_Char_Array (temp.players_names, 2);
    //Free_Char_Array (temp.board, 6);
  }
  else{
    // If Load_Game function returned "false", then either the file is empty, or there is no game with this ID
    if (!Load_Game (game, ID)) {
      printf ("\n The game can't be loaded.");
    }
  }
}

bool Save_Game (game_struct *game, int *count_games){
  // The value -1 is the new game indicator, so every unsaved game is run instead of previous one and has this ID, 
  // and the game receives its unique ID and is placed at the end, only at the moment of saving 

  // Opening a text file with write permissions
  // Writing and updating. A new file is being created and, if a file with the same name already exists, its content will be lost. 
  // The program can both write and read.
  FILE *file;
  if ((file = fopen ("result.txt","w+t")) == NULL )
    printf (" File can't be opened!\n");
  return false;

  // Writing to a file
  (*count_games)++;
  game->ID = *count_games;
  // fprintf (" result.txt", game->ID, " ", game->players_names[0], " ", game->players_names[1], " ");
  fwrite (&(game->ID), sizeof (int), 1, file);
  fwrite (" ", 1, 1, file);
  fwrite (game->players_names[0], 20*sizeof (char), 1, file);
  fwrite (" ", 1, 1, file);
  fwrite (game->players_names[1], 20*sizeof (char), 1, file);
  fwrite (" ", 1, 1, file);
  for (int i = 0; i < 6; i++){
    for (int j = 0; j < 7; j++){
      fwrite (&(game->board[i][j]), sizeof (char), 1, file);
    }
  }
  fwrite (" ", 1, 1, file);
  // Totally, info about every game is written with with 4 "space" symbols (one "space" symbol after ID + two "space" symbols after names + one "space" symbol after 42 chars)
  printf (" The game was saved, ID %d\n", &(game->ID));

  // Closing the file
  fclose (file);
  return true;

  /*
  games = (game_struct*) realloc (games, (*count_games)*sizeof (game_struct));
  games[*count_games] = *game;
  */
}

void Print_Game_Info (game_struct *game){
  int empty_cells = 0;
  for (int i = 0; i < 6; i++){
    for (int j = 0; j < 7; j++) {
      if (game->board[i][j] == '.')
        empty_cells++;
    }
  }
  printf("\n %d %s % s %d", &(game->ID), game->players_names[0], game->players_names[1], &empty_cells);
}

// The function of searching for the game info with the given ID in the text line
bool Find_Game_Info (game_struct *game, int ID, char* text) {
  game_struct res;
  // If no game was found for the given ID, then res.ID = -1
  res.ID = -1;
  int start_of_game_info = 0;
  int end_of_game_info = 1;

  for (; end_of_game_info != strlen(text) - 1; )
  {
    const bool start_is_space = (text[start_of_game_info] == ' ');
    const bool end_is_space = (text[end_of_game_info] == ' ');
    if ((!start_is_space) &&(end_is_space)) {
      int len_of_game_info = end_of_game_info-start_of_game_info;
      char *str_of_ID = (char *) malloc ((len_of_game_info)*sizeof (char));
      for (int i = 0; i < (len_of_game_info); i++) {
        str_of_ID[i] = text[start_of_game_info + i];
      }
      if (Is_Num (str_of_ID, (len_of_game_info)) &&(atoi (str_of_ID) == ID)){
        // Matching ID means that further characters are info about the requested game
        res.ID = ID;
        Copy_Struct (&res, text, start_of_game_info, len_of_game_info);
      }
    }
    else {
      end_of_game_info++;
    }
  }
  // If no game was found for the given ID, then res.ID = -1
  if (res.ID != -1) 
    game = &res;
  else
    return false;
  //Free_Char_Array (res.players_names, 2);
  //Free_Char_Array (res.board, 6);
  return true;
}

void Find_Games_By_Player_Name (char *text, char *name){
  game_struct res;
  // If no game was found for the given ID, then res.ID = -1
  res.ID = -1;
  int start_of_game_info = 0;
  int end_of_game_info = 1;

  for (; end_of_game_info != strlen(text) - 1; )
  {
    const bool start_is_space = (text[start_of_game_info] == ' ');
    const bool end_is_space = (text[end_of_game_info] == ' ');
    if ((!start_is_space) &&(end_is_space)) {
      int len_of_game_info = end_of_game_info-start_of_game_info;
      char *str_of_ID = (char *) malloc ((len_of_game_info)*sizeof (char));
      for (int i = 0; i < (len_of_game_info); i++) {
        str_of_ID[i] = text[start_of_game_info + i];
      }
        // ID of every game is followed by players names 
        res.ID = atoi (str_of_ID);
        Copy_Struct (&res, text, start_of_game_info, len_of_game_info);

        // If any game was found for the given name, it's being prined
        if (res.ID != -1 && ((res.players_names[0] = name) || (res.players_names[1] = name))) 
          Print_Game_Info (&res);
    }
    else
      end_of_game_info++;
  }
  Free_Char_Array (res.players_names, 2);
  Free_Char_Array (res.board, 6);
}

bool Is_Num (char *string, int len){
  // Checking that each character of a string is a digit, using the fact that all digits are continuous in ASCII
  for (int i = 0; i < len; i++){
    if (string[i] < '0' || string[i] > '9')
      return false;
  }
  return true;
}

int Str_To_Num (char *str, int len) {
  int res = 0;
  // Converting a string of digits to a number
  for (int i = 0; i < len; i++){
    const int cur_digit = len - i;
    res += (int) (str[cur_digit])*pow (10, (double)i);
  }
  return res;
}

void Copy_Struct (game_struct *res, char *text, int start_of_game_info, int len_of_game_info){
  // Totally, info about every game is written with with 4 "space" symbols (one "space" symbol after ID + two "space" symbols after names + one "space" symbol after 42 chars)

  int count_spaces = 0;
  // len_of_game_info now means the length of game info except ID 
  int len_of_viewed_game_ifo = len_of_game_info;
  len_of_game_info = 0;
  char *str_of_game_info = (char *) malloc (0);
  while (count_spaces < 4) {
    // copying to tmp
    char *tmp = (char*) malloc (len_of_game_info*sizeof (char));
    for (int i = 0; i < len_of_game_info; i++){
      tmp[i] = str_of_game_info[i];
    }
    len_of_game_info++;
    str_of_game_info = (char *) realloc (str_of_game_info, len_of_game_info*sizeof (char));
    for (int i = 0; i < (len_of_game_info-1); i++){
      str_of_game_info[i] = tmp[i];
    }
    free (tmp);
    len_of_viewed_game_ifo += len_of_game_info;
    str_of_game_info[len_of_game_info-1] = text[start_of_game_info+len_of_viewed_game_ifo];
    if (text[start_of_game_info+len_of_viewed_game_ifo] == ' '){
      // players_names[0] starts after first space
      if (count_spaces == 0){
        int count_chars_of_name = 0;
        char *name = (char *) malloc (0*sizeof (char));
        for (int j = 0; j < len_of_game_info; j++){
          // copying to tmp
          char *tmp = (char*) malloc (count_chars_of_name*sizeof (char));
          for (int i = 0; i < count_chars_of_name; i++){
            tmp[i] = name[i];
          }
          count_chars_of_name++;
          name = (char *) realloc (name, len_of_game_info*sizeof (char));
          for (int i = 0; i < (count_chars_of_name-1); i++){
            name[i] = tmp[i];
          }
          free (tmp);
          name[count_chars_of_name-1] = str_of_game_info[j];
        }
        res->players_names[0] = name;
        free (name);
        // len_of_game_info now means the length of game info except ID and players_names[0]
        len_of_viewed_game_ifo += len_of_game_info;
        len_of_game_info = 0;
      }
      // players_names[1] starts after second space
      if (count_spaces == 1){
        int count_chars_of_name = 0;
        char *name = (char *) malloc (0*sizeof (char));
        for (int j = 0; j < len_of_game_info; j++){
          // copying to tmp
          char *tmp = (char*) malloc (count_chars_of_name*sizeof (char));
          for (int i = 0; i < count_chars_of_name; i++){
            tmp[i] = name[i];
          }
          count_chars_of_name++;
          name = (char *) realloc (name, len_of_game_info*sizeof (char));
          for (int i = 0; i < (count_chars_of_name-1); i++){
            name[i] = tmp[i];
          }
          free (tmp);
          name[count_chars_of_name-1] = str_of_game_info[j];
        }
        res->players_names[1] = name;
        free (name);
        // len_of_game_info now means the length of game info except ID and players_names[0]
        len_of_viewed_game_ifo += len_of_game_info;
        len_of_game_info = 0;
      }
      // board state starts after third space
      if (count_spaces == 2){
        // The special feature of the board state is that it is a contiguous array of 42 chars
        char **board = (char **) malloc (6*sizeof (char *));
        for (int i = 0; i < 6; i++) {
          board[i] = (char *) malloc (7*sizeof (char));
          for (int j = 0; j < 7; j++) {
            board[i][j] = str_of_game_info[len_of_viewed_game_ifo+6*i+j];
          }
        }
        res->board = board;
      }
      count_spaces++;
    }
  }
}

int File_To_Text (char *text){
  text = (char*) malloc (0*sizeof (char));
  int len = 0;
  FILE* file;
  char c;

  // Opening file in reading mode
  file = fopen ("test.txt", "r");

  if (NULL == file) {
    printf (" File can't be opened!\n");
    return false;
  }

  // Copying of what is written in file to string using loop
  do {
    c = fgetc (file);
    len++;
    // copying text to tmp
    char *tmp = (char*) malloc (len*sizeof (char));
    for (int i = 0; i < len; i++){
      tmp[i] = text[i];
    }
    len++;
    text = (char *) realloc (text, len);
    for (int i = 0; i < (len-1); i++){
      text[i] = tmp[i];
    }
    free (tmp);
    text[len-1] = c;

    // Checking if character is not EOF
    // If it is EOF stop reading
  } while (c != EOF);

  // Closing the file
  fclose (file);
  return len;
}

bool Load_Game (game_struct *game, int ID){
  // all renewed
  game_struct res;
  char *text;
  int len = File_To_Text (text);
  if (len == 0 || Find_Game_Info (game, ID, text))
    return false;

  return true;
}

// Clearing the of board memory 
void Free_Array (int **arr, int rows)
{
  for (int i = 0; i < rows; i++) {
    free (arr[i]);
  }
  free (arr);
}

void Free_Char_Array (char **arr, int rows)
{
  for (int i = 0; i < rows; i++) {
    free (arr[i]);
  }
  free (arr);
}

//////////////////////////////////////////////////////////////      Board code

// Creating a board 6 rows * 7 columns
char **Set_Board (){
  char **board = (char **)malloc (6*sizeof (char *));
  for (int i = 0; i < 6; i++) {
    board[i] = (char *)malloc (7*sizeof (char));
  }
  for (int i = 0; i < 6; i++) {
    board[i] = (char *)malloc (7*sizeof (char));
    for (int j = 0; j < 7; j++) {
      board[i][j] = '.';
    }
  }
  return board;
}

// Printing the board to the screen
void Print_Board (char **board, int **connected_four)
{
  printf (" \n");
  for (int i = 0; i < 6; i++) {
    printf (" \t|");
    for (int j = 0; j < 7; j++) {
      for (int k = 0; k < 4; k++) {
        // If the current cell of the board is one of the victorios Connected 4, then instead of the symbol standing there, 'Y' is displayed
        if (i == connected_four[k][0] && j == connected_four[k][1]){
          printf (" Y |");
          break;
        }
        if (k == 3) {
          printf (" %c |", board[i][j]);
        }
      }
    }
    printf (" \n");
  }
}

//////////////////////////////////////////////////////////////      Step code

void Make_Step (game_struct *game, int *count_games, char *player, bool *win, int **connected_four)
{
  // Putting new symbol to the board

  printf (" \nPlayer%s, please select a column (1 - 7): ", &player);
  int col=0, row=0;
  scanf ("%d", col);
  col--;

  if (col != 0)
    Put_Symbol (game->board, col, &row);
  else
    Save_Game (game, count_games);

  // Printing out the board

  Print_Board (game->board, connected_four);

  // Checking ending conditions

  if (Check_Win (player, game->board, row, col, connected_four)){
    *win = true;
  }
}

// Putting symbol on the board
void Put_Symbol (char **board, int col, int *row)
{
  while (col < 0 || col > 6)
  {
    printf (" \nPlease select a column (1 - 7) again: ");
    scanf ("%d", col);
    col--;
  }

  *row = 5;
  char cur_sym = board[*row][col];
  while (cur_sym != '.'){
    // Search for the first empty place, moving from the bottom of the column to the top
    if (row == 0)
    {
      printf (" \nThis column is full. Please select some other column: ");
      scanf ("%d", col);
      col--;

      while (col < 0 || col > 6)
      {
        printf (" \nPlease select a column (1 - 7) again: ");
        scanf ("%d", col);
        col--;
      }

      // Resetting the row to start new column from beginning
      *row = 5;
    }
    else
      row--;
  };
}

// Checking for a winning combination after the Nth move: 3 columns, 4 rows, 3+3 diagonals are checked around the newly placed symbol.
// Проверка наличия выигрышной комбинации после энного хода: вокруг только что поставленного символа проверяются 3 столбца, 4 строки, 3+3 диагонали. входные данные: указатель на игрока-победителя, игровая доска, номер строки нового символа, номер столбца нового символа, связанные символы

bool Check_Win (char *player, char **board, int row, int col, int **connected_four){
  // cells_for_connect stores 4 pairs of cell indices for the checking connection (4 pairs of row+column indices)
  int **cells_for_connect = (int **)malloc (4*sizeof (int *));

  for (int i = 0; i < 4; i++) {
    cells_for_connect[i] = (int *)malloc (2*sizeof (int));
  }  

  // Checking columns of height 4 passing through the newly placed symbol:
  // Since there has not been a win so far to this point, it means that there has not yet (!) been any combination of 4 connected symbols in this column,
  // that's wny Connected 4 were not detected below (!) the newly placed symbol, according to checks during previous moves.
  // Each time a newly placed symbol falls on the column from above (!) just like it happens in Tetris , 
  // so there is no sense in checking for the connected symbols above the cell. 
  // The cells above are either empty or there are even no cells above, if the column is full.
  // Only the cells at UNDER (!) the cell should be checked for a connection, 
  // and the cell of the newly placed symbol must necessarily (!) participate in the checking four .
  // Thus, it is proven that the ONLY place where the current player could collect vertical Connected4 is the cell of the newly placed symbol + three cells below it
  // Either not every horizontal line have to be checked, but in the horizontal line of the new placed symbol, 
  // those horizontal arrays that pass through the new placed symbol should be checked, and this is a maximum of 4 horizontal arrays.
  // However, there are far more diagonals around the newly placed symbol to be checked than vertical and horizontal lines. 
  // In the vicinity of the newly placed symbol, there are a maximum of 3 diagonals, from every diagonal "Northwest to Southeast" and "Northeast to Southwest" (also known as NW_to_SE and NE_to_SW)
  // In total, 6 diagonals around the newly placed character must be checked.
  // A convenient way to check all 6 diagonals, is to collect 2 arrays (NW_to_SE and NE_to_SW) and arrange three checks in each of the 2 arrays

  if (row < 3){
    for (int i = 0; i < 4; i++)
    {
      cells_for_connect[i][0] = row+i;
      cells_for_connect[i][1] = col;

    }
    if (Check_Cells_Arr (board, cells_for_connect)){
      *player = connected_four[0][0];
      for (int k = 0; k < 4; k ++){
        connected_four[k][0] = cells_for_connect[k][0];
        connected_four[k][1] = cells_for_connect[k][1];
      }
      return true;
    }
  }

  // Before checking the 3 diagonals of the NW_to_SE, create diagonal for checking arrays

  int** diagonal = (int **)malloc (6*sizeof (int *));
  for (int i = 0; i < 6; i++) {
    diagonal[i] = (int *)malloc (2*sizeof (int));
  }  

  // If row of new placed symbol is less than 4, the highest diagonal containing the new placed symbol starts from the top high row, 
  // in other case it starts from (row-4)
  int row_of_first_diagonal_elem = (row < 4)? 0: (row-4);

  // The column from which the diagonal starts is the most left column, 
  // which contains cells that lie on the same diagonal as the new symbol placed
  int col_of_first_diagonal_elem = col-row;

  for (int i = 0; i < 6; i++)
  {
    cells_for_connect[i][0] = row_of_first_diagonal_elem+i;
    cells_for_connect[i][1] = col_of_first_diagonal_elem+i;

  }

  // The diagonal contains three arrays of 4 cells, and all 3 should be checked

  for (int i = 0; i < 3; i++)
  {
    for (int j = 0; j < 4; j++){
      cells_for_connect[j][0] = diagonal[0+i][0];
      cells_for_connect[j][1] = diagonal[0+i][1];
    }
    if (Check_Cells_Arr (board, cells_for_connect)){
      *player = connected_four[0][0];
      for (int k = 0; k < 4; k ++){
        connected_four[k][0] = cells_for_connect[k][0];
        connected_four[k][1] = cells_for_connect[k][1];
      }
      return true;
    }
  }

  //////////////////////////////////////////////////////////////

  // Updating the diagonal for checking arrays to check the 3 diagonals NE_to_SW: 
  // the row_of_first_diagonal_elem still has the same value because the row of the newly placed symbol has not changed

  // The column from which the diagonal starts is the most RIGHT column, which contains cells that lie on the same diagonal as the new symbol placed
  col_of_first_diagonal_elem = col+row;

  for (int i = 0; i < 6; i++)
  {
    cells_for_connect[i][0] = row_of_first_diagonal_elem+i;
    cells_for_connect[i][1] = col_of_first_diagonal_elem-i;

  }

  // The diagonal contains three arrays of 4 cells, and all 3 should be checked

  for (int i = 0; i < 3; i++)
  {
    for (int j = 0; j < 4; j++){
      cells_for_connect[j][0] = diagonal[0+i][0];
      cells_for_connect[j][1] = diagonal[0+i][1];
    }
    if (Check_Cells_Arr (board, cells_for_connect)){
      *player = connected_four[0][0];
      for (int k = 0; k < 4; k ++){
        connected_four[k][0] = cells_for_connect[k][0];
        connected_four[k][1] = cells_for_connect[k][1];
      }
      Free_Array (cells_for_connect, 4);
      Free_Array (diagonal, 6);
      return true;
    }
  }
  Free_Array (cells_for_connect, 4);
  Free_Array (diagonal, 6);
  return false;
}

bool Check_Cells_Arr (char **board, int **cells_arr){
  if (board[cells_arr[0][0]][cells_arr[0][1]] == board[cells_arr[1][0]][cells_arr[1][1]] && 
    board[cells_arr[1][0]][cells_arr[1][1]] == board[cells_arr[2][0]][cells_arr[2][1]] && 
    board[cells_arr[2][0]][cells_arr[2][1]] == board[cells_arr[3][0]][cells_arr[3][1]])
    return true;
  else 
    return false;
}

//////////////////////////////////////////////////////////////
