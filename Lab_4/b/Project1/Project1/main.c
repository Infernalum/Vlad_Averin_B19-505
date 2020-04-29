/********************************************************************************************************************************************************************************************************/
/* ���� 4(�).
  ������� 40***.
	�������� ��������� ��� ������ ��������, ������������ ��� ������������ ������, �� �������� ���������.
	������ ������� ������� ����� ��������� ���������:
  struct Item {
	int key1;      // ���� �������� �� 1-��� ������������ ������
	int key2;       // ���� �������� �� 2-��� ������������ ������
	char *info;    // ��������� �� ����������
	int ind1;	   // ����� � ��������� 1-��� ������������ ������
	int ind2;	   // ����� � ��������� 2-��� ������������ ������
  };
  ������ ������������ ������ ������������ �� �������� ������������ �������, ������������ ������������� ���������. ������������ ������ ������� ���������
(��� �������� ������������� ������� ������� ������������ ��������� - ��������, const int SIZE = ...; ).
  ������������� ��������� ��������:
	- ��������� ������ �������� � ������� ��� �������, ��� � ������� �� ����� ���� ���� ��������� � ����������� �������;
	- �������� �� ������� ��������, ��������� �����-���� ����� ������ ������;
	- ����� � ������� �������� �� ������ ��������� �����; ����������� ������ ������ ���� ����� ���������� �������� �� ���������� ���� ������;
��������� ��������;
	- ����� ����������� ������� �� �����; ��� ���� ������ ������ ������ ��������������� ����������� ���� ��������� �������� �������;
	���� ��� ���������� �������� � ��������� ��������� ��������� ��������, �� ����� ������ ���� �������� �������������� ��������� �� ������.
	����������� ��� �������� ���������:
  a) � ���� �������, � ����������, ����������� � �������� �������, �������� � �������� ������;
  �) � ���� �������, � ����������, ����������� � �������, �������� �� ������� ������ (����������� �������� ���� ������������� �������). ��� �������� ����������� � ��������, ����������� � ��������
������. ������� ����������� �� ����� (��� ��������� � ������ ���) � ������ ������ ������ � ������������ � ���� � ����� ������ ������. ����������, ����������� � �������� �������, ������������ 
� ���� ����� �� ��� ���������� �������� ��������� � �������. ��� ����� �������� �� �������� ���������.
	����������:
  1. ��������� ������ ��������� ��������� �������; ������� main() ������ ���������: ����� ����, ���� � ������ ������, ����� �� ���������� ��������� �������;
  2. � ��������� ����� ������������� �������� ������������ ����� ������;
  3. ��� �������� b) ������� �������������� ���������, ������������� ������� �������, ������� � ��� ����� ���������� � �� �������� � �����;
  4. � �������� b) ��� ������ � ������ ������������ ������� ������ stdio.h; ������ � ������ ��������� � ������� fread() � fwrite(), � ������� ������ ���� ������� �������� ����� ����������;
*/
/********************************************************************************************************************************************************************************************************/


#include "Header_4a.h"

extern const Type msgs[];
extern const int NMsgs;
extern const Type errmsgs[];


// ������ ���������� �� ������� - ��� ���������� ������ �������; ������� ������������ ������� � ������ ������������� ������ �������������� ������� �������� ����������� � ������ ����������
int(*fptr[])(Table *) = { NULL, D_Add, D_Find, D_Delete, D_Show };


int main() {
	setlocale(LC_ALL, "Russian");
	Table table = { NULL , NULL };
	int rc;
	if (D_Load(&table) == 0)	// ��������� �������, ������������� � ������ ���� ������
		return 1;
	while (rc = dialog(msgs, NMsgs))
		if (!fptr[rc](&table))         // ���������� ���������� �������, ��������������� ������ ������������
			break;
	save(&table);				// ��������� �������, ��������� ���� ������
	printf("������� ���������.\n������� �� ��������!\n");
	delTable(&table);
	return 0;
}
