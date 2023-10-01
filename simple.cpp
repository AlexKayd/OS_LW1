#include <cmath>

bool Simple (int number) {
    // Проверка числа на 0, 1 или любое отрицательноее число
    if (number < 2) {
        return true;
    }
    // Проверка числа на простоту
    for( int w = 2; w <= sqrt(number)+1; w++) {
        if( number % w == 0) {
            return false;
        }
    }
    // Если ничего не сработало - число простое
    return true;
}