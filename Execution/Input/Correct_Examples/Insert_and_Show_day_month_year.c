//Inserisci data mese ed anno e mostra a video

int fm(int date, int month, int year) {
     int fmonth, leap;

     //leap function 1 for leap & 0 for non-leap
     if ((year % 100 == 0) && (year % 400 != 0))
        leap = 0;
     else if (year % 4 == 0)
        leap = 1;
     else
        leap = 0;

     fmonth = 3 + (2 - leap) * ((month + 2) / (2 * month))
           + (5 * month + month / 9) / 2;

     //bring it in range of 0 to 6
     fmonth = fmonth % 7;

     return fmonth;
  }


  int day_of_week(int date, int month, int year) {

     int dayOfWeek;
     int YY = year % 100;
     int century = year / 100;

     printf("\nDate: %d", date);
     printf("/%d", month);
     printf("/%d \n", year);

     dayOfWeek = 1.25 * YY + fm(date, month, year) + date - 2 * (century % 4);

     //remainder on division by 7
     dayOfWeek = dayOfWeek % 7;


  }

  int main() {
     int date, month, year;
     printf("\nEnter the date ");
     scanf("%d", &date);

     printf("\nEnter the month ");
     scanf("%d", &month);

     printf("\nEnter the year ");
     scanf("%d", &year);


     day_of_week(date, month, year);

     return 0;
  }
