float FtoC(float F);
float FtoK(float F);
float CtoF(float C);
float CtoK(float C);
float KtoC(float K);
float KtoF(float K);

double history[100];
char unit[100];
int counter = 0;

void menu();
float takeF();
float takeC();
float takeK();
float check(float temp, char stopnie);
void enter();
void save(double previous, char unitP, double next, char unitN);
void show();


