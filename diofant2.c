#include <stdio.h>
#include <stdlib.h>
#include <math.h>
/*
Список функций:
1.evklid_nod - ищет нод двух чиел по алгоритму евклида(в уравнении - с)
2.gcd - ищет коэффициенты a, b для уравнения
3.solve_diof - решает диофантово уравнение и выдает неоптимальные x и y
4.find_min - зная неоптимальные корни подбирает x и y такие, что сумма |x|+|y| будет минимальна(таким образом кол-во переливаний будет наименьшим)
5.poryadok - выводит порядок действий переливания 
*/
int evklid_nod(int kv, int bn) //находим по алгоритму евклида нод емкости и разности емкостей
{

  if (kv == 0 || bn == 0)
  {
    return kv + bn;
  }

  if (kv > bn)
  {
    return evklid_nod(kv - bn, bn);
  }
  else
  {
    return evklid_nod(kv, bn - kv);
  }
}


int gcd (int a, int b, int* x, int* y) //находим нод и два коэффициента a и b и цифру после равно с для диофантового уравнения
{
  if (a == 0)
  {
    *x = 0;
    *y = 1;
    return b;
  }

  int x1, y1 = 0;

  int d = gcd (b % a, a, &x1, &y1);

  *x = y1 - (b / a) * x1;
  *y = x1;

  return d;
}

int solve_diof(int* x_0, int* y_0, int kv, int bn, int need)  //зная a и b и с находим случайные два решения уравнения(не отпимальные)
{

  int nod = gcd(kv, bn, x_0, y_0);

  printf("НОД:%d\n", nod);


  printf("x_0 = %d;    y_0 = %d;\n", *x_0, *y_0);

  if (nod != 1)
  {
    if (*y_0 == 0)
    {
      *x_0 = (need) / kv;
      *y_0 = *y_0;
    }
    else
    {
      if (*x_0 == 0)
      {
        *x_0 = *x_0;
        *y_0 = (need) / bn;
      }
    }
  }
  else
  {
      *x_0 = need * (*x_0);
      *y_0 = need * (*y_0);
  }

  return nod;
}


int find_min(int* min_y, int* min_x, int x_0, int y_0, int kv, int bn, int nod) //находим оптимальные x и y(у которых будет наименьшая сумма модулей, чтобы было меньше переливаний)
{
    double t_min = NAN;
    double epsilon = 0.00005; // const float epsilon = ....
    
    
    t_min = -((double)x_0 * (double)nod / (double)bn);
    
    
    int t_min_1, t_min_2, sum_t1, sum_t2, x_t2, y_t2, x_t3, y_t3, sum, sum_1= 0;
    
    t_min_1 = round(t_min);
    
    printf("%lf %d %d %d\n", t_min, t_min_1, x_0, bn);
    
    if (abs(t_min - t_min_1) <= epsilon)
    {
        *min_x = x_0 + bn/nod * t_min_1;
        *min_y = y_0 - kv/nod * t_min_1;
        
        sum = abs(*min_x) + abs(*min_y);
    }
    else
    {
        if (t_min > t_min_1)
        {
            t_min_2 = t_min_1 + 1;
        }
        else
        {
            t_min_2 = t_min_1 - 1;
        }
    
        printf("%d %d", t_min_1, t_min_2);
        
        *min_x = x_0 + bn/nod * t_min_1;
        *min_y = y_0 - kv/nod * t_min_1;
        
        sum_t1 = abs(*min_x) + abs(*min_y);
        
        x_t2 = x_0 + bn/nod * t_min_2;
        y_t2 = y_0 - kv/nod * t_min_2;
        
        sum_t2 = abs(x_t2) + abs(y_t2);
        
        if (sum_t1 > sum_t2)
        {
            *min_x = x_t2;
            *min_y = y_t2;
            sum = sum_t2;
        }
        else
        {
            sum = sum_t1;
        }
    }
    
    
    t_min = (double)y_0 * (double)nod / (double)kv;
    
    t_min_1 = round(t_min);
    
    if (abs(t_min - t_min_1) <= epsilon)
    {
        x_t3 = x_0 + bn/nod * t_min_1;
        y_t3 = y_0 - kv/nod * t_min_1;
        
        sum_1 = abs(x_t3) + abs(y_t3);
    }
    else
    {
        if (t_min > t_min_1)
        {
            t_min_2 = t_min_1 + 1;
        }
        else
        {
            t_min_2 = t_min_1 - 1;
        }
        
        x_t3 = x_0 + bn/nod * t_min_1;
        y_t3 = y_0 - kv/nod * t_min_1;
        
        sum_t1 = abs(x_t3) + abs(y_t3);
        
        x_t2 = x_0 + bn/nod * t_min_2;
        y_t2 = y_0 - kv/nod * t_min_2;
        
        sum_t2 = abs(x_t2) + abs(y_t2);
        
        if (sum_t1 > sum_t2)
        {
            x_t3 = x_t2;
            y_t3 = y_t2;
            sum_1 = sum_t2;
        }
        else
        {
            sum_1 = sum_t1;
        }
    }
    
    if (sum_1 < sum)
    {
        *min_x = x_t3;
        *min_y = y_t3;
        sum = sum_1;
    }
    return sum;
}


 void poryadok(int* min_x, int* min_y, int kv, int bn, int cs)
{
    int kv1 = 0;
    int bn1 = 0;
    int bd = 0;
    int cs1 = cs;
    
    printf("kv:%d\n bn:%d\n bd:%d\n", kv, bn, bd);
    
    if ((*min_x > 0) && (*min_y < 0)) //рассматриваем переливания когда нужна разность кувшина и банки
     {
       while (*min_y != 0)
       {
         
         cs1 = cs1 - kv;
         kv1 = kv;
         printf("цистерна>кувшин || cs: %d kv: %d bn: %d bd: %d \n", cs1, kv1, bn1, bd);
         kv1 = kv1 - bn;
         bn1 = bn;
         printf("кувшин>банка || cs: %d kv: %d bn: %d bd: %d \n", cs1, kv1, bn1, bd);
         kv1 = 0;
         bd = bd + kv - bn;
         printf("кувшин>бидон || cs: %d kv: %d bn: %d bd: %d \n", cs1, kv1, bn1, bd);
         cs1 = cs1 + bn;
         printf("банка>цистерна || cs: %d kv: %d bn: %d bd: %d \n", cs1, kv1, bn1, bd);
       
         *min_y = *min_y + 1;
         *min_x = *min_x - 1;

       }

       while (*min_x != 0)
       {
         printf("цистерна>кувшин");
         kv1 = kv;
         cs1 = cs1 - kv;
         printf("кувшин>бидон");
         kv1 = 0;
         bd = bd + kv;
         *min_x = *min_x - 1;
       }
     }


     if ((*min_x > 0) && (*min_y > 0))
     {
         while (*min_x >= 0)
         {
           cs1 = cs1 - kv;
         kv1 = kv;
         printf("цистерна>кувшин || cs: %d kv: %d bn: %d bd: %d \n", cs1, kv1, bn1, bd);
         kv1 = 0;
         bd = bd + kv;
         printf("кувшин>бидон || cs: %d kv: %d bn: %d bd: %d \n", cs1, kv1, bn1, bd);
         *min_x = *min_x - 1;
         }
         while (*min_y >= 0)
         {
           cs1 = cs1 - bn;
           bn1 = bn;
           printf("цистерна>банка || cs: %d kv: %d bn: %d bd: %d \n", cs1, kv1, bn1, bd);
           bn1 = 0;
           bd = bd + bn;
           printf("банка>бидон || cs: %d kv: %d bn: %d bd: %d \n", cs1, kv1, bn1, bd);
           *min_y = *min_y - 1;
         }
     }
/*
     if ((*min_x > 0) && (*min_y < 0) && ((*min_y % 2) == 0)) //рассматриваем переливания когда нужна 2 разности кувшина и банки
     {
       while(*min_y != 0)
       {
         cs1 = cs1 - kv;
         kv1 = kv1 + kv;
         printf("цистерна>кувшин || cs: %d kv: %d bn: %d bd: %d \n", cs1, kv1, bn1, bd);
         kv1 = kv1 - bn;
         bn1 = bn;
         printf("кувшин>банка || cs: %d kv: %d bn: %d bd: %d \n", cs1, kv1, bn1, bd);
         cs1 = cs1 + bn;
         bn1 = 0;
         printf("банка>цистерна || cs: %d kv: %d bn: %d bd: %d \n", cs1, kv1, bn1, bd);
         kv1 = kv1 - bn;
         bn1 = bn;
         printf("кувшин>банка || cs: %d kv: %d bn: %d bd: %d \n", cs1, kv1, bn1, bd);
         cs1 = cs1 + bn;
         bn1 = 0;
         printf("банка>цистерна || cs: %d kv: %d bn: %d bd: %d \n", cs1, kv1, bn1, bd);
         kv1 = 0;
         bd = bd + kv - bn - bn;
         printf("кувшин>бидон || cs: %d kv: %d bn: %d bd: %d \n", cs1, kv1, bn1, bd);
         *min_y = *min_y + 2;
         *min_x = *min_x - 1;
       }
       while (*min_x != 0)
       {
         printf("цистерна>кувшин");
         kv1 = kv;
         cs1 = cs1 - kv;
         printf("кувшин>бидон");
         kv1 = 0;
         bd = bd + kv;
         *min_x = *min_x - 1;
       }
     }
    */
}
int main()
{
  int kv, bn, cs, need;
  need = 0;
  kv = 0;
  bn = 0;
  cs = 0;
  int x = 0;
  int y = 0;
    
    printf("Введите объем кувшина:");
    scanf("%d", &kv);
    
    printf("Введите объем банки:");                     //ввод объемов сосудов
    scanf("%d", &bn);
    
    printf("Введите объем цистерны:");
    scanf("%d", &cs);
    
    printf("Введите необходимое количества молока:");
    scanf("%d", &need);


  int nod = evklid_nod(kv, bn); //если с / нод a и b не делится то уравнение решений не имеет 

  if (need % nod != 0)
  {
    printf("Это невозможно\n\n");
    return 0;
  }
  else
  {
    solve_diof(&x, &y, kv, bn, need);

    printf("x = %d\n"
           "y = %d\n", x, y);   //вывод неоптимальных корней
  }

    
    int min_y, min_x = 0;
    
    int min_sum = find_min(&min_y, &min_x, x, y, kv, bn, nod); //ищем оптимальные корни
    
    printf("min_x = %d\n"
           "min_y = %d\n"
           "sum   = %d\n\n", min_x, min_y, min_sum);
    
    return 0;

}






















































