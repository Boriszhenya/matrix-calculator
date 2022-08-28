#include <iostream>
#include <iomanip>
#include <windows.h>
#include <cstdlib>
#include <conio.h> 

using namespace std;
	 
     // Фунція створення динамічного масиву.
double** createArray(int rows,  int cols)			
{
	double** res = new double* [rows];
	for (int i = 0; i < rows; i++)
	{
		res[i] = new double[cols];
	}
	return res;
}

	 // Фунція видалення динамічного масиву.
void deleteArray(double** arr,  double rows)
{
	for (int i = 0; i < rows; i++)
	{
		delete[] arr[i];
	}
	delete[] arr;
}

     // Функція відповідає за вибір режиму введення елементів матриці.
int autoManualFillArray(int maNual) 
{
	cout << endl<<" Виберіть режим заповнення матриць числами" << endl;
	cout << "1 - автоматичний (випадкові числа), 0 - ручне введення елементів матриці"
		 << endl;
	cin >> maNual;
	return maNual;
}

     // Функція заповненя масиву числами.
void fillArray(double** arr, int rows, int cols, int maNual=1) 
{
	if (maNual == 0)                     // Для ручного введення
	{
		cout << "Введення елементів матриці" << endl;
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++)
			{
				cout << "[" << i << "]" << "[" << j << "]" << "=";  
				cin >> arr[i][j];
			}
			cout << endl;
		}
		cout << endl;
	}
	else
	{                                    // рандомне введення елементів матриці
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++)	arr[i][j] = rand() % 10 + 1;
		}
		cout << endl;
	}
}

	 // Функція виведення масиву з числами на екран.
void showArray(double** arr, int rows, int cols)    
{													
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			cout << setw(10) << arr[i][j]; // setw() форматує вивід на екран
		}
		cout << endl;
	}
	cout << endl<<endl;
}

     // Функція знаходження суми елементів двох матриць.
void sumArray(double** arr1, double** arr2, double** arr3, int rows, int cols)
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			arr3[i][j]=arr1[i][j]+arr2[i][j];
		}
	}
}

	 // Функція знаходження різниці елементів двох матриць.
void differenceArrays(double** arr1, double** arr2, double** arr3, int rows, int cols) 
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			arr3[i][j] = arr1[i][j] - arr2[i][j];
		}
	}
}

     // Функція знаходження добутку елементів двох матриць.
void productArray(double** arr1, double** arr2, double** arr_res, int rows1, int cols1, int cols2) 
{
	for (int i = 0; i < rows1; i++)            
	{
		for (int j = 0; j < cols2; j++)            // Елементи стовбчика матриці №1 перемножаються попарно 
		{										   // на елементи рядочка матриці №2 і сума усіх добутків
			arr_res[i][j] = 0;                     // записується в результуючу матрицю місце де перетинаються 
			for (int k = 0; k < cols1; k++)        // стовбчик та рядочок
			{
				arr_res[i][j] += arr1[i][k] * arr2[k][j];
			}
			
		}
	}
}

	 // Функція піднесення до степеня матриці.
void exponentiationArray(double** arr1, double** arr2, double** arr_res, int rows, int power) 
{
	for (int i = 0; i < rows; i++)                             // Створення копії матриці №1.
	{
		for (int j = 0; j < rows; j++)
		{
			arr2[i][j] = arr1[i][j];
		}
	}
	for (int k = 2; k <= power; k++)                           // Якщо степінь 2 і більше то виконувати множення матриць .
	{
		productArray(arr1, arr2, arr_res, rows, rows, rows);   // Обчислення добутку двох матриць.

		for (int i = 0; i < rows; i++)                         // Підготовлення до наступного циклу множення
		{                                                      // результуюча матриця копіюється в матрицю №2.
			for (int j = 0; j < rows; j++)
			{
				arr2[i][j] = arr_res[i][j];
			}	
		}
	}

}

	 // Фунція знаходження мінора матриці.
void makeMinor(double** minor, double** arr, int size, int rows_delet, int cols_delet)  
{
	for (int i = 0, iminor = 0; i < size; ++i)
	{
		if (i == rows_delet)                          // rows_delet - номер рядочка який викреслюємо
			continue;
		for (int j = 0, jminor = 0; j < size; ++j)
		{
			if (j == cols_delet)                      // cows_delet - номер стовбчика який викреслюємо
				continue;
			minor[iminor][jminor] = arr[i][j];
			++jminor;
		}
		++iminor;
	}
}

	 // Функція знаходження дерермінінта матриці.
double determinant(double** arr, int k)   
{
	double **Dyn_Minor_Arr;
	
	if (k == 1) return arr[0][0];                                          // Часткові випадки.
		if (k == 2) return arr[0][0] * arr[1][1] - arr[0][1] * arr[1][0];  // Часткові випадки.

	double det = 0;														   // Ініціалізація детермінанта.

	Dyn_Minor_Arr = createArray(k-1, k-1);                      // Створення динамічного масиву для мінора.
	
	for (int l = 0; l < k; l++) 
	{
		makeMinor(Dyn_Minor_Arr, arr, k, 0, l);                 // Заповнення елементами мінорної матриці.
		det += (l % 2 ? -1 : 1) * arr[0][l] * determinant(Dyn_Minor_Arr, k - 1);  // Обчислюємо детермінант.
	}

	deleteArray(Dyn_Minor_Arr, k-1);                            // Видалення динамічного масиву мінорів.
	
	return det;
}

     // Функція множення елементів матриці на число.
void multiplicationByNumber(double** arr, int rows, int cols, double K)  
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			arr[i][j] = arr[i][j] * K;
		}
	}
}


int main()
{
  	SetConsoleCP(1251);             // Встановлення кодування Windows-1251 в потік введення.
	SetConsoleOutputCP(1251);       // Встановлення кодування Windows-1251 в потік виведення
	                                // українського тексту встановити шрифт консолі - Lucida Console.
	
	SetConsoleTitle(L"Матричний калькулятор");
	
	int      rows1, cols1, cols2, M, K = 1, maNual = 1;
	double** Arr1;
	double** Arr2;
	double** ArrResult;
	
	while (K != 0)
	{
		cout << "----Матричний калькулятор----" << endl << endl;
		cout << " 1 - Додавання двох матриць" << endl;
		cout << " 2 - Віднімання двох матриць" << endl;
		cout << " 3 - Множення матриці на число" << endl;
		cout << " 4 - Множення двох матриць" << endl;
		cout << " 5 - Знаходження детермінанту матриці" << endl;
		cout << " 6 - Піднесення матриці до цілого додатного степеня " << endl << endl;
		cout << "Виберіть код операції, яку треба виконати - " << endl;
		cin >> M;
			   
		switch (M) 
		{
		case 1 :
			cout << endl << "ДОДАВАННЯ ДВОХ МАТРИЦЬ" << endl << endl;
			cout << "Щоб виконати операцію ДОДАВАННЯ матриці повині мати одно розмірність" << endl;
			cout << "Введіть розмірність матриць" << endl;
			cout << "кількість рядків матриці - ";
			cin >> rows1;
			cout << "кількість стовбців матриці - ";
			cin >> cols1;
			maNual=autoManualFillArray(maNual);				// Визначаємо спосіб заповнення матриць.

			Arr1 = createArray(rows1, cols1);				// Створення динамічного масиву для 1-ї матриці.
			Arr2 = createArray(rows1, cols1);				// Створення динамічного масиву для 2-ї матриці.
			ArrResult = createArray(rows1, cols1);			// Створення динамічного масиву для результуючої 
															// матриці.
			
			fillArray(Arr1, rows1, cols1, maNual);			// Заповнення матриці №1 числами.
			fillArray(Arr2, rows1, cols1, maNual);			// Заповнення матриці №2 числами.

			cout << "---Матриця №1---" << endl;
			showArray(Arr1, rows1, cols1); 
			
			cout << "---Матриця №2---" << endl;
			showArray(Arr2, rows1, cols1);

			sumArray(Arr1, Arr2, ArrResult, rows1, cols1);   // Обчислення суми двох матриць.
			cout << "---Матриця №3 = №1+№2---" << endl;
			showArray(ArrResult, rows1, cols1);              // Виведення на екран матриці
			                                                 // з результатом суми.

			deleteArray(Arr1, rows1);					     // Видалення масиву №1.     
			deleteArray(Arr2, rows1);						 // Видалення масиву №2.
			deleteArray(ArrResult, rows1);					 // Видалення масиву результатів.

			break;

		case 2 :
			cout << endl << "ВІДНІМАННЯ ДВОХ МАТРИЦЬ" << endl << endl;
			cout << "Щоб виконати операцію ВІДНІМАННЯ матриці повині мати одно розмірність" << endl;
			cout << "Введіть розмірність матриць" << endl;
			cout << "кількість рядків матриці - ";
			cin >> rows1;
			cout << "кількість стовбців матриці - ";
			cin >> cols1;
			maNual = autoManualFillArray(maNual);

			Arr1 = createArray(rows1, cols1);       // Створення динамічного масиву для 1-ї матриці.
			Arr2 = createArray(rows1, cols1);       // Створення динамічного масиву для 2-ї матриці.
			ArrResult = createArray(rows1, cols1);  // Створення динамічного масиву для результуючої матриці.
			
			fillArray(Arr1, rows1, cols1, maNual);  // Заповнення матриці №1 числами.
			fillArray(Arr2, rows1, cols1, maNual);  // Заповнення матриці №2 числами.

			cout << "---Матриця №1---" << endl;
			showArray(Arr1, rows1, cols1);			// Виведення на екран матриці №1
			cout << "---Матриця №2---" << endl;
			showArray(Arr2, rows1, cols1);          // Виведення на екран матриці №2
			
			differenceArrays(Arr1, Arr2, ArrResult, rows1, cols1);  // Обчислення різниці двох матриць
			cout << "---Матриця №3 результат різниці---" << endl;
			showArray(ArrResult, rows1, cols1);		// Виведення на екран матриці з результатом різниці 

			deleteArray(Arr1, rows1);               // Видалення масиву №1
			deleteArray(Arr2, rows1);				// Видалення масиву №2
			deleteArray(ArrResult, rows1);			// Видалення масиву результатів

			break;
		
		case 3 :
			int N;
			cout << endl << "МНОЖЕННЯ МАТРИЦІ НА ЧИСЛО" << endl << endl;
			cout << "Введіть розмірність матриць" << endl;
			cout << "кількість рядків матриці - ";
			cin >> rows1;
			cout << "кількість стовбців матриці - ";
			cin >> cols1;
			cout << "Введіть число N на яке будемо множити матрицю - ";
			cin >> N;
			maNual = autoManualFillArray(maNual);

			Arr1 = createArray(rows1, cols1);				// Створення динамічного масиву для 1-ї матриці
						
			fillArray(Arr1, rows1, cols1, maNual);			// Заповнення матриці числами
			
			cout << "---Матриця початкова---" << endl;
			showArray(Arr1, rows1, cols1);					// Виведення початкової матриці на екран

			multiplicationByNumber(Arr1, rows1, cols1, N);	// Знаходження добутку елеменів масиву на число
			cout << "---Матриця результуюча---" << endl;
			showArray(Arr1, rows1, cols1);

			deleteArray(Arr1, rows1);						// Видалення масиву №1  
		
			break;
						
		case 4 :
			cout << endl << "ДОБУТОК ДВОХ МАТРИЦЬ" << endl << endl;
			cout << "Щоб виконати операцію МНОЖЕННЯ повино виконуватися наступна умова" << endl;
			cout << "кількість стовбців першої матриці має дорівнювати кількості рядків";
			cout << "другої матриці" << endl << endl;

			cout << "Введіть кількість рядочків першої матриці - " << endl;
			cin >> rows1;
			cout << "Введіть кількість стовбців першої матриці - " << endl;
			cin >> cols1;
			cout << "Введіть кількість стовбців другої матриці - " << endl;
			cin >> cols2;
			maNual = autoManualFillArray(maNual);
			
			Arr1 = createArray(rows1, cols1);         // Створення динамічного масиву для 1-ї матриці
			Arr2 = createArray(cols1, cols2);         // Створення динамічного масиву для 2-ї матриці
			ArrResult = createArray(rows1, cols2);    // Створення динамічного масиву для результуючої матриці
			
			fillArray(Arr1, rows1, cols1, maNual);    // Заповнення матриці №1 числами
			fillArray(Arr2, cols1, cols2, maNual);    // Заповнення матриці №2 числами

			cout << "---Матриця №1---" << endl;
			showArray(Arr1, rows1, cols1);            // Виведення матриці №1 на екран
			cout << "---Матриця №2---" << endl;
			showArray(Arr2, cols1, cols2);            // Виведення матриці №2 на екран
			
			productArray(Arr1, Arr2, ArrResult, rows1, cols1,cols2); // Обчислення добутку двох матриць
			cout << "---Матриця добутку---" << endl;
			showArray(ArrResult, rows1, cols2);        // Виведення на екран матриці з результатом добутку 

			deleteArray(Arr1, rows1);                  // Видалення масиву №1
			deleteArray(Arr2, cols1);                  // Видалення масиву №2
			deleteArray(ArrResult, rows1);             // Видалення масиву результатів              
			break;
		
		case 5 :
			cout << endl << "ЗНАХОДЖЕННЯ ДЕТЕРМІНАНТУ МАТРИЦІ" << endl << endl;
			cout << "Необхідна умова знаходження детермінанта матриці - матриця має";
			cout << "бути квадратна" << endl;
			cout << "кількість стовбців та рядків матриці мають бути однакові" << endl ;
			cout << "введіть розмірність матриці -"<<endl;
			cin >> rows1;
			maNual = autoManualFillArray(maNual);

			Arr1 = createArray(rows1, rows1);          // Створення динамічного масиву для 1-ї матриці
						
			fillArray(Arr1, rows1, rows1, maNual);     // Заповнення матриці №1 числами

			cout << "---Матриця буде мати вигляд---" << endl;
			showArray(Arr1, rows1, rows1);             // Виведення на екран матриці №1
			
			cout << "Детермінант матриці буде дорівнювати - ";
			cout << determinant(Arr1, rows1) << endl;  // Знаходження детермінанта
			
			deleteArray(Arr1, rows1);                  // Видалення 1 масиву
			
			break;

		case 6 :
			int power;								  // Степінь до якої подносимо матрицю 
			cout << endl << "ПІДНЕСЕННЯ МАТРИЦІ ДО ЦІЛОГО ДОДАТНЬОГО СТЕПЕНЯ" << endl << endl;
			cout << "Необхідна умова піднесення матриці до степеня -";
			cout << "матриця має бути квадратна" << endl;
			cout << "кількість стовбців та рядків матриці мають бути однакові" << endl;
			cout << "введіть розмірність матриці - ";
			cin >> rows1;
			cout << "введіть степінь - ";
			cin >> power;
			
			while (power <1)                         // цикл буде працювати поки не буде введено 
												     // значення степеня більше дорівкює 1
			{
				cout << "значення степеня має бути > = 1, введіть повторно степінь - ";
				cin >> power;
			}
						
			maNual = autoManualFillArray(maNual);     // Визначаємо режим заповнення матриці
			Arr1 = createArray(rows1, rows1);         // Створення динамічного масиву для 1-ї матриці
			fillArray(Arr1, rows1, rows1, maNual);    // Заповнення матриці №1 числами
			cout << "---Матриця початкова буде мати вигляд---" << endl;
			showArray(Arr1, rows1, rows1);            // Виведення на екран матриці №1
			
			if (power == 1)							  // Частковий випадок
			{
				cout << "---Матриця піднесена до " << power << " степеня буде мати вигляд---" << endl;
				showArray(Arr1, rows1, rows1);         // Виведення на екран матриці №1				
			}
			
			if (power > 1)
			{
				Arr2 = createArray(rows1, rows1);         // Створення динамічного масиву для 2-ї матриці
				ArrResult = createArray(rows1, rows1);    // Створення динамічного масиву для результуючої матриці
				
				exponentiationArray(Arr1, Arr2, ArrResult, rows1, power);  // Знаходження результуючої матриці
				
				cout << "---Матриця піднесена до " << power << " степеня буде мати вигляд---" << endl;
				showArray(ArrResult, rows1, rows1);       // Виведення на екран матриці з результатом добутку
				
				deleteArray(Arr2, rows1);                 // Видалення масиву №2
				deleteArray(ArrResult, rows1);            // Видалення масиву результатів; 
			}
			
			deleteArray(Arr1, rows1);					  // Видалення динамічного масиву №1

			break;
		
		default:
			
			cout << "Невірно введені данні" << endl;
		}
		cout << "Бажаєте продовжувати обислення натисніть 1, якщо ні то 0" << endl;
		cin >> K;
	}
	return 0;
}