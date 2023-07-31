﻿#include <iostream>       // cin/cout
#include <stdlib.h>       // abs - вычисление модуля числа
#include <cmath>
#include <vector>
#include <string>

using namespace std;
int main() {
    /*float c;
    cin >> c;
    cout << (int)c << " Press any key to exit... \n";*/
    //int x=5%3, y;
    //cin >> y;
    //cout << x << " + " << y << " = " << (x+y); //0.66 -> 0

    // яблоко падает с дерева за время t
    // определить высоту, откуда упало яблоко

    /*int t, h, v, g=10;
    cin >> t;
    v = g*t;
    int vmiddle = v/2;
    h = vmiddle*t;
    cout << h;*/

    // даны два числа a и b, причем b>0
    // посчитать целую часть от деления a на b, округлённую вверх
    // a делится на b; a не делится на b
    // неверная стратегия - разделить с округлением вниз и добавить 1
    // Пример: 8/2+1 = 4+1 = 5, должно быть 4
    // рассмотрим вторую стратегию
    // сначала добавить, потом делить нацело
    // поскольку делим на b, то max что можно добавить (b-1)
    // допустим остаток 1, тогда можем сложить (a+b-1)
    // после этого делим на b: 
    // (a+b-1)/b = (11+5-1)/5 = 3

    /*int a, b;
    cin >> a >> b;
    cout << (a+b-1)/b;*/

    // яблоко упало с ветки
    // сколько времени яблоко летело вторую половину пути,
    // есть конечная скорость составила 20 м/с

    // есть ряд коробок и куча новогодних игрушек
    // найти, сколько игрушек будет в каждой коробке, 
    // если игрушки раскладываются поровну
    // сколько игрушек останется, когда в каждой коробке будет поровну?

    //int k, i, res = 0;
    //cin >> k >> i;
    //res = i % k;
    //cout << res;

    // дано натуральное число, выведите его последнюю цифру

    //int n;
    //cin >> n;
    //cout << (n % 10); //  635412987 -> 7

    // дано целое трехзначное число, найти сумму его цифр

    //int n, a, b, c;
    //cin >> n;           // число от 100 до 999
    //a = n / 100;
    //b = (n - a*100) / 10;
    //c = n % 10;
    //cout << (a+b+c);

    // дано целое неотрицательное число, определите
    // число десятков в нем (предпоследнюю цифру числа)
    // если нет предпоследней цифры, то считайте, что число десятков равно нулю....
    //int a;
    //cin >> a;
    //cout << a/10%10;

    // дано натуральное число 
    // вывести следубщее за ним четное число

    //size_t n;
    //cin >> n;
    ////// н четное
    ////if (n%2 == 0) cout << n+2;
    ////// н нечетное
    ////if (n%2 == 1) cout << n+1;
    //
    //
    //// n = n/2;            4/2 -> 2 -> 2*2 + 2 = 6 (n четный, получено след. четное)
    //// n = n/2;            5/2 -> 2.5 -> 2 -> 2*2 + 2 = 6 (n нечетный, получено след. четное)

    //size_t a = n/2;
    //// cout << (n/2)*2 + 2;
    //cout << 2*(a + 1);

    // в автобусе все кресла двойные
    // нужно оборудовать креслами три автобуса
    // известно кол-во мест в каждом автобусе
    // найти наименьшее кол-во двойных кресел, которое потреб.

    //size_t a, b, c, res = 0;
    //cin >> a >> b >> c;
    //res = a/2 + a%2;
    ////res = res + (b/2 + b%2);
    ////res = res + (c/2 + c%2);
    //res += b/2 + b%2;
    //res += c/2 + c%2;
    //// res = res/2;
    //// res /= 2;
    //cout << res;

    // На дороге стоят километровые столбы.
    // Велосипедист едет по дороге от города с пост. скоростью
    // и курсирует между городом и 2-м городом, распол. на 105 километре
    // На каком расстоянии от последнего города 
    // велосипедист будет через Т часов?

    //size_t v, t, otrezok = 105;
    //cin >> v >> t;
    //cout << (v*t % otrezok);

    // дано четырехзначное число
    // определить, является ли его запись симметричной
    // если число симметричное, вывести 1, иначе 0

    //bool res;
    //int n, a, b, c, d;
    //cin >> n;
    //a = n/1000;
    //b = (n/100)%10;
    //c = (n/10)%10;
    //d = n%10;

    //if (a == d && b == c) {
    //  res = 1;
    //}
    //else {
    //  res = 0;
    //}
    //cout << "res = " << res;

    ///////////////////////////////////////////////

    // нахождение максимума
    // даны два целых числа
    // вывести наибольшее из них

    //int n1, n2;
    //cin >> n1 >> n2;
    //if (n1 > n2){
    //  cout << n1;
    //}
    //else {
    //  cout << n2;
    //}

    //int n1, n2, n3;
    //cin >> n1 >> n2 >> n3;
    //if ((n1 > n2 || n1 == n2) && (n1 > n3 || n1 == n3)){
    //  cout << n1;
    //}
    //else if ((n2>n1 || n2 == n1) && (n2>n3 || n2 == n3)){
    //  cout << n2;
    //}
    //else if ((n3 > n1 || n3 == n1) && (n3 > n2 || n3 > n2)){
    //  cout << n3;
    //}
    //  n1 = 3
    //  n2 = 3
    //  n3 = 1
    // 3+5*7+8  ->   (3+5)*(7+8)


    //int counter = 0, n1, n2, n3;
    //cin >> n1 >> n2 >> n3;
    //// найти количество совпадающих

    //if (n1 == n2) 
    //  counter = 2;
    //else if (n2 == n3) 
    //  counter = 2;

    //if(n1 == n3 && counter == 0) counter = 2;  // то же, что и (n1 == n3 && n2 != n3)
    //else counter += 1; // counter++, в случае выполнения этого блока все числа равны
    //
    //cout << counter;

    /////////////////////////////////////////////

    // неравенства треугольника
    // в треугольника каждая сторона меньше суммы двух других
    // a < b + c, b < a + c, c < a + b
    // 3, 4, 5, 3^2 + 4^2 = 5^2
    // 3 < 4 + 5, 4 < 3 + 5, 5 < 3 + 4

    // если среди трех отрезков каждый меньше суммы двух других,
    // то из этих отрезков можно составить треугольник

    // из трех чисел а, б, с нужно проверить, сущ ли треугольник с такими сторонами
    // вывести Yes, если сущ такой треугольник, иначе вывести No

    //size_t a, b, c;
    //cin >> a >> b >> c;
    //if ((a < b + c) && (b < a + c) && (c < a + b)) {
    //  cout << "Yes";
    //}
    //else {
    //  cout << "No";
    //}

    // шахматная ладья ходит только вверх-вниз и вправо-влево
    /*
    ^
    |....................................
    |....................................
    |....................................
    |....................................
    |....................................
    |....................................
    ------------------------------------->

    в нашей задаче каждая шахм. клетка имеет координаты Х и Y, т.е. номер столбца и номер строки
    на вход подается 2 пары координат (1 клетка и 2 клетка)
    определить, может ли ладья попасть с первой летки на 2ю одним ходом

    */

    //size_t x1, y1, x2, y2;
    //cin >> x1 >> y1 >> x2 >> y2;
    //if ((x1 == x2) || (y1 == y2))
    //  cout << "Yes";
    //else 
    //  cout << "No";

    // шахм. король ходит по гориз. и верт., но только на расстояние в 1 клетку
    // даны 2 пары координат (1 и 2 клетка). Сможет ли король пойти с 1 клетки на 2?

    //int x1, y1, x2, y2, distant;
    //cin >> x1 >> y1 >> x2 >> y2;

    //// расстояние по т. Пифагора
    //distant = sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));

    //// (3,1) (2,5)
    //if (distant == 1)
    //  cout << "Yes";
    //else 
    //  cout << "No";

    /*
    Шахм. слон ходит по диагонали. Даны две клетки шахм. доски,
    надо определить, может ли слон попасть с 1й на 2ю одним ходом. Yes/No
    */

    //int x1, y1, x2, y2;
    //cin >> x1 >> y1 >> x2 >> y2;

    //if (abs(x1-x2) == abs(y1-y2)){
    //  cout << "Yes";
    //}
    //else
    //  cout << "No";

    // до края бассейна остается м метров
    // с каждым тактом расстояние уменьшается на т метров
    // сколько потребуется тактов?

    //int m, t, count = 0;
    //cin >> m >> t;
    //while (m > 0){
    //  m = m - t;        // m -= t;
    //  count++;          // count += 2;        count = count + 2;
    //}
    //cout << count;


    //int n, m, x, y, x2, y2;
    //// n*m бассейн, пловец на расстоянии х от одного из длинных бортиков
    //// y - расстояние до одного из коротких бортиков
    //// какое ближайшее расстояние до (любого) бортика

    //cin >> n >> m >> x >> y;
    //x2 = n-x;
    //y2 = m-y;
    //if ((x <= y)&&(x <= x2)&&(x <= y2))
    //  cout << x;
    //else if ((y <= x)&&(y <= x2)&&(y <= y2))
    //  cout << y;
    //else if ((y2 <= x)&&(y2 <= x2)&&(y2 <= y))
    //  cout << y2;
    //else
    //  cout << x2;

    //// ДЗ

    //// на вход даются три числа
    //// вывести их на экран в порядке "<=" (порядок неубывания)

    //int a, b, c;
    //cin >> a >> b >> c;
    //// квадраты в порядке неубывания остатка при делении на 3
    //// (3^2), (4^2), (5^2) = остатки при делении кв-тов на 3 = 0, 1, 1
    //// (3^2), (5^2), (4^2) = остатки при делении кв-тов на 3 = 0, 1, 1

    //// найти минимум и вывести его, дальше среднее и наибольшее
    //if ((a <= b) && (a <= c)){
    //  cout << a << " ";
    //  if (b <= c) 
    //    cout << b << " " << c;
    //  else 
    //    cout << c << " " << b;
    //}
    //else if ((b <= a) && (b <= c)){
    //  cout << b << " ";
    //  if (a <= c)
    //    cout << a << " " << c;
    //  else                                       // ! (a <= c) ==>  c < a
    //  {
    //    cout << c << " " << a << " ";            // b c a 
    //  }
    //}
    //else {
    //  cout << c;
    //  // проверка, какое из чисел a и b - среднее, а какое наибольшее
    //  // a - среднее, b - наибольшее
    //  if (a <= b)
    //    cout << a << " " << b;
    //  // b - среднее, a - наибольшее
    //  else
    //    cout << b << " " << a;
    //}

    ///////////////////////////////////////

    // даны две коробки, их размеры a*b*c и a2*b2*c2
    // чтобы можно было положить одну коробку в другую, 
    // разрешен только поворот на 90 градусов в вертикальной плоскости (не переворачивать)
    // можно ли положить одну коробку в другую?

    //int a, b, c, a2, b2, c2;
    //cin >> a >> b >> c >> a2 >> b2 >> c2;

    //if (c < c2) {
    //  // первая коробка помещается во вторую
    //  if ((a <= a2 && b <= b2) || (a <= b2 && b <= a2)) {
    //    cout << "First box may be in second";
    //  }
    //}
    //else if (c == c2)
    //{
    //  // проверяются оба варианта (1ая во 2ую и 2ая в 1ую)
    //  
    //  // первая коробка помещается во вторую
    //  if ((a <= a2 && b <= b2) || (a <= b2 && b <= a2)) {
    //    cout << "First box may be in second";
    //  }
    //  // вторая коробка помещается во первую
    //  if ((a2 <= a && b2 <= b) || (a2 <= b && b2 <= a)){
    //    cout << "Second box may be in first";
    //  }
    //}
    //else
    //{
    //  // вторая коробка помещается во первую
    //  if ((a2 <= a && b2 <= b) || (a2 <= b && b2 <= a)){
    //    cout << "Second box may be in first";
    //  }
    //}

    // Пример, который уже был:

    // до края бассейна остается м метров
    // с каждым тактом расстояние уменьшается на т метров
    // сколько потребуется тактов?

    //int m, t, count = 0;
    //cin >> m >> t;
    //while (m > 0){
    //  m = m - t;        // m -= t;
    //  count++;          // count += 2;        count = count + 2;
    //}
    //cout << count;

    //////////////////////////////////

    // Школьный класс покупает пиццу на НГ:
    // нужно выбрать самого младшего школьника, чтобы он сходил в магаз.
    // В последовательности положительных чисел (которая оканчивается на 0)
    // найти минимальное число.

    //int v, min_v;
    //cin >> v;
    //min_v = v;
    //while (v != 0){
    //  if (v < min_v){
    //    min_v = v;
    //  }
    //  cin >> v;
    //}

    ///////////////////////////////////

    // Школьный класс собирает деньги на пиццу на НГ
    // Вводится сумма денег, которая есть у каждого ученика, и в конце ввод 0
    // Нужно вывести на экран общую сумму денег, которая есть у учеников

    //int sum = 0, now;
    //cin >> now;
    //while (now != 0){
    //  sum += now;             // sum = sum + now;
    //  cin >> now;
    //}

    ///////////////////////////////////

    //int lpart, rpart, lsum = 0, rsum = 0;
    //cin >> lpart >> rpart;
    //while (lpart != 0){
    //  lsum = lsum + (lpart % 10);
    //  lpart /= 10;
    //}
    //// действия с пр частью
    //while (rpart != 0)
    //{
    //  rsum += rpart%10;
    //  rpart /= 10;
    //}
    //// проверка что лефтсум == райтсум
    //if (lsum == rsum)
    //  cout <<"Lucky ticket!";
    //else
    //  cout <<"Unlucky ticket!";

    ////////////////////////////////

    //int x = 1;
    //while (x > 0){
    //  x++;
    //  if (x % 2 == 0)
    //    continue;
    //  cout << x << " ";
    //}

    // shift + F5 / для резкого прерывания программы
    // f10 - для построчного выполнения после точки останова

    /////////////////////////////

    // игра "Угадайка"
    // человек вводит цифры 0 или 1
    // программа пытается угадать, какое число введено, и после первой же победы выводит сообщение "WIN", но если уже 10 раз программа не угадала, она выводит "FAIL"

    //int x, count = 0;
    //cin >> x;

    //while (count < 10){
    //  if (x == 1){
    //    cout << "WIN";
    //    break;
    //  }
    //  count++;
    //  cin >> x;
    //}

    //if (count == 10)
    //  cout << "FAIL";
    // м.б. также проверен х (если х != 1) - тогда выводим "фейл"

    ////////////////////////////////////

    // вывести на экран те квадраты всех натуральных чисел, которые меньше N
    //int a = 1, N = 5;
    //cin >> N;
    //while (a*a <= N){
    //  cout << a*a << " ";
    //  a++;
    //}

    //////////////////////////////////

    // зная число N, вывести его наименьший натуральный делитель (не равный 1)
    //int n, a = 2;
    //cin >> n;
    //while (n % a > 0)
    //  a++;
    //cout << a;

    //////////////////////////////////

    // по данному числу N, найти все натуральные числа, которые являются степенями числа 2, но меньше N

    //int N, a = 1;
    //cin >> N;
    //while (a < N) {
    //  cout << a << " ";
    //  a *= 2;                   // a = a*2;
    //}

    //////////////////////////////////

    // дано нутральное число N, вывести Yes, если N = степень двойки, иначе вывести No

    //int N, a = 1;
    //cin >> N;
    //if (N % 2 == 0){
    //  while (a <= N) {
    //    if (a == N){
    //      cout << "Yes";
    //      break;
    //    }
    //    a *= 2;
    //  }
    //  if (a > N)
    //      cout << "No";
    //}
    //else
    //  cout << "No";

    //////////////////////////////////

    // дана последовательность натуральных чисел (в конце идет 0)
    // программа принимает на вход все числа посл-ти, а при вводе 0 программа завершает прием чисел и выводит на экран количество чисел в последовательности (не считая 0)
    // 1 3 4 0 8 0        => 4
    // 7 ........................... 0
    //int cur, count = 0;
    //cin >> cur;
    //while (cur != 0){
    //  count++;
    //  cin >> cur;
    //}
    //cout << count;

    //////////////////////////////////////

    //int cur, sum = 0;
    //cin >> cur;
    //while (cur != 0) {
    //  sum = sum + cur;
    //  cin >> cur;
    //}
    //cout << sum;

    //////////////////////////////////////

    //int cur, max;
    //cin >> cur;
    //max = cur;
    //while (cur != 0) {
    //  // проверка, что очередной элемент превысил максимум
    //  if (cur > max) {
    //    max = cur;
    //  }
    //  cin >> cur;
    //}
    //cout << max;

    //////////////////////////////////////

    //int cur, max, countmax = 0;
    //cin >> cur;
    //max = cur;
    //while (cur != 0) {
    //  // проверка, что очередной элемент превысил максимум
    //  if (cur > max) {
    //    max = cur;
    //    countmax = 1;
    //  }
    //  else if (cur == max) {
    //    countmax++;
    //  }
    //  cin >> cur;
    //}
    //cout << "max = " << max << ", countmax = " << countmax;

    // max*max*max = multmax
    // multmax = 243, max = 3 => countmax = ?

    //int multmax, max, countmax = 0;
    //while (multmax > 1){
    //  multmax /= max;
    //  countmax++;
    //}
    //int check = 1;
    //while (check != multmax){
    //  check *= max;
    //  countmax++;
    //}

    ////////////////////////////////////

    //int i = 1;
    //while(i < 100){
    //  ///
    //  i++;
    //}


    //for (/*начальное значение счетчика*/ int i = 1; 
    //  /* условие продолжения */ i < 100; 
    //  /* изменение счетчика */ i += 20){
    //}

    /*int n;
    cin >> n;

    vector <int> v(n);                // создан вектор v, сост. из цел.ч.
    // Если n = 5, то i изменяется от 0 до 4 => i изменяется от 0 до n-1

    vector <vector<int>> v2(n+5);
    // создан вектор v2, сост. из векторов, сост. из цел.ч.

    //// считывание элементов вектора
    //for (int i = 0; i < n; i++){
    //    cin >> v[i];
    //}

    //// вывод на экран элементов вектора
    //for (int i = 0; i < n; i++){
    //    cout << v[i] << " ";
    //}

    // запись положительных чисел в вектор

    vector <int> box;
    int border;
    cout << "\nВведите кол-во чисел в последовательности";
    cin >> border;
    for (int i = 0; (i < border); i++) {
      int t;
      cin >> t;
      //if (t > 0)
        box.push_back(t); // имя вектора.название метода (аргумент)

    }
    // && || !

    // обработка (поиск минимума и смена местами минимума с посл эл)
    int index_min = 0;
    for (int i=0; i<border; i++) {
      if (box[i] < box[index_min]){
        index_min = i;
      }
    }

    // обмен значений эл-тов: минимального эл-та и последнего эл-та
    int temp;
    temp = box[index_min];
    box[index_min] = box[box.size() - 1];
    box[box.size() - 1] = temp;

    // вывод на экран в правильном порядке
    for (auto now : box){
      cout << now << " ";
    }


    // вывод чисел на экран задом наперед

    for (int i = box.size() - 1; i >= 0; i--){
      cout << box[i] << " ";
    }*/


    /////////////////////////////////////////

    //vector <string> book;
    //book.push_back("Mama ");
    //book.push_back("myla ");
    //book.push_back("ramu.");


    //for (int i = 0; i < book.size(); i++)
    //{
    //  cout << book.front() << " ";
    //}

    //if(book.empty()){
    //  cout << "Book is empty";
    //}
    //else{
    //  cout << book.size();
    //}

    //string s = book.at(1);
    //cout << s;

    /////////////////////////////////////////
    //циклическая перестановка элементов вперед на 1

    // vector v -> v[0], v[1], v[2] -> v[2],  v[0], v[1]

    //int n;
    //cin >> n;
    //vector <int> v(n);

    //for (int i = 0; i < v.size(); i++){
    //  int t;
    //  cin >> t;
    //  if (i != n-1){
    //    v[i+1] = t;
    //  }
    //  else
    //    v[0] = t;
    //}

    //for(auto x : v){
    //  cout << x << " ";
    //}

      ////////////////////////////////////////////

      // подсчет количества положительных элементов

      ////////////////////////////////////////

      //Дан массив чисел (вектор). Выведите все элементы массива, которые больше предыдущего элемента .

      //4 1 10 2 4
      // 10 4

    //int n;
    //cin >> n;
    //vector <int> a(n);

    //for (int i = 0; i < n; i = i+1) {
    //  cin >> a[i];
    //}
    //for (int i = 1; i < n; i = i+1) {
    //  if (a[i] > a[i-1])
    //    cout << a[i] << " ";
    //}

    // throw exception (выброс исключения) - это сообщение об ошибке без вреда
    // error

    //////////////////////////////////////////////

    // Выведите значение наименьшего из всех положительных элементов в векторе. Известно, что в векторе есть хотя бы один положительный элемент.

    //int n, maxeven = 0;                    // int (integer) = целое число
    //bool firsteven = false;
    //cout << "Enter the size of vector: ";
    //cin >> n;
    //vector <int> v(n);

    //for (int i = 0; i < n; i++) {
    //  cin >> v[i];
    //  // поиск наименьшего из всех положительных элементов
    //  //if (v[i] > 0 && (v[i] < min || min == 0))
    //  //  min = v[i];

    //  // поиск наибольшего четного эл-та

    //  /* | 1 | 11 | -2 | 17 | 65 | 7 | 21 | 5 | 3 | -3 */

    //  // нечет - не меняет эталон (образец)
    //  // чет, но меньше или равно образцу - не меняет образец
    //  // чет, больше образца (больше, чем наиб чет из предыд) - обновить образец

    //  if (v[i] % 2 == 0 && (v[i] > maxeven || firsteven == false)){
    //    maxeven = v[i];
    //    firsteven = 1;
    //  }
    //}

    //cout << maxeven << endl;


    //////////////////////////////////////////////

    // Пусть дан массив, упорядоченный по неубыванию элементов. Найти кол-во разных эл-тов в нем

    //int n, count = 1;     // mult = 1;
    //cin >> n;
    //vector <float> _v (n);
    //cin >> _v[0];
    //for (int i = 1; i < n; i++) {
    //  cin >> _v[i];
    //  if (_v[i] > _v[i-1])
    //    count++;
    //}



    //////////////////////////////////////////////

    // массив, упорядоченный по невозрастанию эл-тов, найти кол-во различных четных чисел
    // 7
    // 5 4 4 3 2 0 -1 -> 3
    // 2k+1, k - целое
    // 2k, k - целое
    // k = 10 => 2k+1 = 21, 2k = 20
    // k = -2 => 2k+1 = -3, 2k = -4

    //int n, counteven = 0;
    //cin >> n;
    //vector <int> v(n);
    //for (int i = 0; i < n; i++) {
    //  cin >> v[i];
    //  if (v[i] % 2 == 0 && v[i] != v[i-1])
    //    counteven++;
    //}
    //cout << counteven << endl;

    //////////////////////////////////////////////

    // Дан массив. Выведите те его элементы, которые встречаются в массиве только один раз. Элементы нужно выводить в том порядке, в котором они встречаются в массиве.

    // 8 4 3 5 2 5 1 3 5

    //////////////////////////////////////////////
    ////вывести первую цифру после точки дробного числа
    //float f; cin >> f;
    ////trunc,floor,ceil,round
    //cout << abs((int)(trunc(f * 10)) % 10);
    ////Даны длины сторон треугольника. Вычислите площадь треугольника.
    ////Формула Герона s=корень(p*(p-a)(p-b)(p-c)).p-полупериметр 
    //float a, b, c, p, s; cin >> a >> b >> c; p = (a + b + c) / 2;
    //s = sqrt(p * (p - a) * (p - b) * (p - c));
    ///////////Процентная ставка по вкладу составляет P процентов годовых, которые прибавляются к сумме вклада в конце года. Вклад составляет X рублей Y копеек. Определите размер вклада через год.x=100.y=50.p=75.v=100,5+100,5/100*75= 100.5+1.005*75=100.5+75.375=175.875. s*(1+0.01*p)
int x, y, p; cin >> x >> y >> p; float s = x + y / 100.0;
cout << (int)(s * (1 + 0.01 * p))<< " rubles, "<< (s * (1 + 0.01 * p)- (int)(s * (1 + 0.01 * p)))*100<< " kopeek";
//Процентная ставка по вкладу составляет P процентов годовых, которые прибавляются к сумме вклада в конце года. Вклад составляет X рублей Y копеек. Определите размер вклада через год. найти размер вклада через l лет
    return 0;
}