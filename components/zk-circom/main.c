#include <gmp.h>
#include <stdlib.h>

char* sum_large_numbers(const char* num1_str, const char* num2_str) {
  mpz_t num1, num2, result;

  mpz_init_set_str(num1, num1_str, 10);
  mpz_init_set_str(num2, num2_str, 10);
  mpz_init(result);

  mpz_add(result, num1, num2);

  char* result_str = mpz_get_str(NULL, 10, result);

  mpz_clear(num1);
  mpz_clear(num2);
  mpz_clear(result);

  return result_str;
}