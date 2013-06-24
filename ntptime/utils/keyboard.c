#include "keyboard.h"

//======================================================================
void Keyboard_Driver(void)
{												//��������� ������ � ����� �� ��������� � ������ KeyButton[9] ������� 3�3
 unsigned char i;

 if (TimerKeyFLAG == 1) 						//���� ����� ���� ���������� ������������ ����������
 {
	 	 	 	 	 	 	 	 	 	 	 	 //	����� ������ KN_STR1,KN_STR2,KN_STR3 - ��� ������ ��������� ������ ���.0 �� ����������� 1
  KN_STR_OFF(KN_PORT,KN_STR1);					//	������ ���.0 �� ����������� 1

  DelayLoop(20000);	  	  						// 	�������� �����


  if(Check_Bit(KN_PORT,KN_COL1) == False)	  	//if (CHKBIT(piKNE,KN_COL1) == 0)
  {
	  Button0[0]++;
  }
  	  else
  	  {
  		  Button1[0]++;
  	  }

  if(Check_Bit(KN_PORT,KN_COL2) == False)	  //if (CHKBIT(piKNE,KN_COL2) == 0)
	  {
	  	  Button0[1]++;
	  }

  	  else
  		  {
  		  	  Button1[1]++;
  		  }
  if(Check_Bit(KN_PORT,KN_COL3) == False)	  //if (CHKBIT(piKNE,KN_COL3)==0)
	  {
	  	  Button0[2]++;
	  }
  	  else
  	  {
  		  Button1[2]++;
  	  }

  KN_STR_ON(KN_PORT,KN_STR1);  	  	  	 // ����������  ���.1 �� ����������� 1

  	  	  	  	  	  	  	  	  	  	  	 //	������ ���.0 �� ����������� 2
  KN_STR_OFF(KN_PORT,KN_STR2);

  DelayLoop(20000);							  //�������� �����

  if(Check_Bit(KN_PORT,KN_COL1) == False)	  	//if (CHKBIT(piKNE,KN_COL1) == 0)
   {
 	  Button0[3]++;
   }
   	  else
   	  {
   		  Button1[3]++;
   	  }

   if(Check_Bit(KN_PORT,KN_COL2) == False)	  //if (CHKBIT(piKNE,KN_COL2) == 0)
 	  {
 	  	  Button0[4]++;
 	  }

   	  else
   		  {
   		  	  Button1[4]++;
   		  }
   if(Check_Bit(KN_PORT,KN_COL3) == False)	  //if (CHKBIT(piKNE,KN_COL3)==0)
 	  {
 	  	  Button0[5]++;
 	  }
   	  else
   	  {
   		  Button1[5]++;
   	  }

  KN_STR_ON(KN_PORT,KN_STR2);

  	  	  	  	  	  	  	  	  	  	  	  // ������ ���.0 �� ����������� 3
  KN_STR_OFF(KN_PORT,KN_STR3);

  DelayLoop(20000);							//�������� �����

  if(Check_Bit(KN_PORT,KN_COL1) == False)	  	//if (CHKBIT(piKNE,KN_COL1) == 0)
   {
 	  Button0[6]++;
   }
   	  else
   	  {
   		  Button1[6]++;
   	  }

   if(Check_Bit(KN_PORT,KN_COL2) == False)	  //if (CHKBIT(piKNE,KN_COL2) == 0)
 	  {
 	  	  Button0[7]++;
 	  }

   	  else
   		  {
   		  	  Button1[7]++;
   		  }
   if(Check_Bit(KN_PORT,KN_COL3) == False)	  //if (CHKBIT(piKNE,KN_COL3)==0)
 	  {
 	  	  Button0[8]++;
 	  }
   	  else
   	  {
   		  Button1[8]++;
   	  }


  KN_STR_ON(KN_PORT,KN_STR3);				 //����������  ���.1 �� ����������� 3

  KN_STR_OFF(KN_PORT,KN_STR3);

  DelayLoop(20000);							//�������� �����


  if(Check_Bit(KN_PORT,KN_COL1) == False)	  	//if (CHKBIT(piKNE,KN_COL1) == 0)
   {
 	  Button0[6]++;
   }
   	  else
   	  {
   		  Button1[6]++;
   	  }

   if(Check_Bit(KN_PORT,KN_COL2) == False)	  //if (CHKBIT(piKNE,KN_COL2) == 0)
 	  {
 	  	  Button0[7]++;
 	  }

   	  else
   		  {
   		  	  Button1[7]++;
   		  }
   if(Check_Bit(KN_PORT,KN_COL3) == False)	  //if (CHKBIT(piKNE,KN_COL3)==0)
 	  {
 	  	  Button0[8]++;
 	  }
   	  else
   	  {
   		  Button1[8]++;
   	  }

  KN_STR_ON(KN_PORT,KN_STR3);				 			//����������  ���.1 �� ����������� 3


  NumberKey++; 											//������� ����� �������� �� ����������

      if  (NumberKey >= NumberKeyDefault)				//���� ��������� �������� - (������ ��������)
      {
         NumberKey = 0;

         for (i=0;i<9;i++)
         {
           if (Button0[i] > Button1[i])								//���� ������ ������!!!
           {

             if (ButtonPress[i] == 0) ButtonPress[i] = 1; 			// ���� ������ ���� �� ������ �� ����� ��������� �������
           }
           else 													//	���� ������ �� ������
           {
        	   	   	   	   	   	   	   	   	   	   	   	   	   	   	   //���� ������ ���� ������,  ������� ���������� � ����� ���������� � ����������
             if (ButtonPress[i] == 2)  ButtonPress[i] = 0; 			//��������� ����������
        	//   if (ButtonPress[i] == 1)  ButtonPress[i] = 0; 		//��������� ����������
           }
           	   	   	   	   	   	   	   	   	   	   	   	   	   	   //�������� �����������
           Button0[i] = 0;
           Button1[i] = 0;
         }
      }

      TimerKeyFLAG = 0;												//����� �����

      for (i=0;i<9;i++)
         {
             	 	 	 	 	 	 	 	 	 	 	 	 //���� ������ ���� ������ - ������������ �������
             if (ButtonPress[i] == 1)
             {
            	 	 	 	 	 	 	 	 	 	 	 	 //�������������� ������ - ����� �� �������� �� �������� ����������
                ButtonPress[i] = 0;
                ButtonNumber = i;							//������ ����� ������� ������

                switch (i)
                {
                 case 0:
                	 	 PsevdoCodButton = ButtonESCAPE;
                	 	 break;
                 case 1:
                         PsevdoCodButton = ButtonLeft;
                          break;
                 case 2:
                         PsevdoCodButton = ButtonRedit;
                          break;
                 case 3:
                         PsevdoCodButton = ButtonUP;
                          break;
                 case 4:
                         PsevdoCodButton = ButtonKrest;
                          break;
                 case 5:
                         PsevdoCodButton = ButtonDown;
                          break;
                 case 6:
                         PsevdoCodButton = ButtonALARM;
                          break;
                 case 7:
                         PsevdoCodButton = ButtonRight;
                          break;
                 case 8:
                 {
                         PsevdoCodButton = ButtonOK;
                          break;
                 }
                }
                ButtonPress[ButtonNumber] = 2;
            }
         }

 	 }
}
