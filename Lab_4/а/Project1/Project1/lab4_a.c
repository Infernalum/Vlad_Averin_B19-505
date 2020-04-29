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
	����������:
  1. ��������� ������ ��������� ��������� �������; ������� main() ������ ���������: ����� ����, ���� � ������ ������, ����� �� ���������� ��������� �������;
  2. � ��������� ����� ������������� �������� ������������ ����� ������;
  3. ��� �������� b) ������� �������������� ���������, ������������� ������� �������, ������� � ��� ����� ���������� � �� �������� � �����;
  4. � �������� b) ��� ������ � ������ ������������ ������� ������ stdio.h; ������ � ������ ��������� � ������� fread() � fwrite(), � ������� ������ ���� ������� �������� ����� ����������;
*/
/********************************************************************************************************************************************************************************************************/

#define _CRT_SECURE_NO_WARNINGS

#include "Header_4a.h"



// ������ ��������������� ��������� �� �������
const Type errmsgs[] = { "Ok", "�������� ����� (������) � ����� �� �����������", "������� �����������", "������� �����", "����/����� �� ������/�" };



// ������������ ���� ��� ����������� �������
const Type msgs[] = { "0. �����", "1. ��������", "2. �����", "3. �������", "4. ������� �������" };


// ���-�� ����������� (��� ������ � for)
const int NMsgs = sizeof(msgs) / sizeof(msgs[0]);

/* ����� ������ ������������ (������� ��� ������ ������ ������������. ���������� ���������� ����� ������������. � ������ ����� ���� ������ ������ ����� ������������; ���� � ������
����� ������ ������������ ���� ���-�� ���, ���� ������� ������ ��������� �� ������) */
int dialog(const Type msgs[], int N) {
	Type errmsg = "";
	int rc, i, n;
	do {
		puts(errmsg);
		errmsg = "������! ��������� ����:!";
		for (i = 0; i < N; ++i)       // ����� ������ �����������
			puts(msgs[i]);
		printf("��������: --> ");
		n = getInt(&rc);              // ���� ������ ������������
		if (n == 0)                   // ����� ����� - ����� ������
			rc = 0;
	} while (rc < 0 || rc >= N);
	return rc;
}


int I(int k) {						        // ���-�������
	return k % SIZE;
}

/* ������� ������ ����� */
void clean_stdin() {
	int c;
	do
		c = getchar();    // ������������ c ������� �� �������� ������
	while (c != '\n' && c != EOF);
}


/* ���� ������ ����� �� �������� ������. ���� ��������� ������ �� ����� �����(��� ����� ��� ��������� �����), ����� ������ ������ ����� ��� ���. */
int getInt(int *a) {
	int n;
	do {
		n = scanf("%d", a, sizeof(int));
		if (n < 0) // ��������� ����� �����
			return 0;
		if (n == 0) { // ��������� ������������ ������ - ������
			printf("%s\n", "������! ��������� ����:");
			clean_stdin();
		}
	} while (n == 0);
	clean_stdin();
	return 1;
}

/* ���� ������ ������������ ����� �� �������� ������ */
Type getStr() {
	char *ptr = (char *)malloc(1);
	char buf[81];
	int n, len = 0;
	*ptr = '\0';
	do {
		n = scanf("%80[^\n]", buf);
		if (n < 0) {
			free(ptr);
			ptr = NULL;
			continue;
		}
		if (n == 0)
			scanf("%*c");
		else {
			len += strlen(buf);
			ptr = (char *)realloc(ptr, len + 1);
			strcat(ptr, buf);
		}
	} while (n > 0);
	return ptr;
}



/* ���������� ������� ��������� � ������� ������ ��������. ������� ������ ���� � ����������, ��� ���� ��� ���������� ������ ���� ������� � ����� ������, � ����� �� �����������.
���� ���� ����� �����������, ��� ������ ������������.*/
int D_Add(Table *ptab) {
	int k1, k2, rc;
	Type info = NULL;
	printf("������� ������ ����: --> ");
	int n = getInt(&k1);
	if (n == 0)
		return 0;   // ��������� ����� �����
	printf("������� ������ ����: --> ");
	n = getInt(&k2);
	if (n == 0)
		return 0;   // ��������� ����� �����
	printf("������� ����������: --> ");
	info = getStr();
	if (info == NULL)
		return 0;  // ��������� ����� �����
	rc = insert(ptab, k1, k2, info); // ������� �������� � �������
	printf("%s: %d - %d %s\n", errmsgs[rc], k1, k2, info);
	return 1;
}

/* ���� ������������ ������ */
void input(int *k1, int* k2) {
	int n, ans;
	Type errmsg = "";
	do {
		puts(errmsg);
		errmsg = "����������� ����� ���; ����������� ����� 1 ��� 2 ��� ������.";
		printf("������� ���-�� ������, �� ������� ������ �������: --> ");
		n = getInt(&ans);
	} while ((ans < 1) || (ans > 2));
	errmsg = "";
	if (ans == 1) {
		do {
			puts(errmsg);
			errmsg = "����������� ����� ���; ����������� ����� 1 ��� 2 ��� ������.";
			printf("������� ����� ������������ �����: --> ");
			n = getInt(&ans);
			if (n == 0)
				return 0;
		} while ((ans < 1) || (ans > 2));
		if (ans == 1) {
			printf("������� ���� �� ������� ������������ ������: --> ");
			n = getInt(k1);
			if (n == 0)
				return 0;
			return 0;
		}
		else {
			printf("������� ���� �� ������� ������������ ������: --> ");
			n = getInt(k2);
			if (n == 0)
				return 0;
			return 0;
		}
	}
	else {
		printf("������� ���� �� ������� ������������ ������: --> ");
		n = getInt(k1);
		if (n == 0)
			return 0;
		printf("������� ���� �� ������� ������������ ������: --> ");
		n = getInt(k2);
		if (n == 0)
			return 0;
		return 0;
	}
}


/* ���������� ������� ������ ���� ��������� �� ����� ��� ���������� ������ �����. */
int D_Find(Table *ptab) {
	int k1 = -1, k2 = -1, rc;
	input(&k1, &k2);
	rc = find(ptab, k1, k2);
	if (rc == -1) {
		printf("%s:\n", errmsgs[4]);
		return 1;
	}
	printf("\n|  ���� 1  |  ���� 2  |  ind 1  |  ind 2  |       ����������\n");
	printf("|%10d|%10d|%9d|%9d|   %s\n", ptab->space1[rc].key1, ptab->space1[rc].key2, ptab->space1[rc].ind1, ptab->space1[rc].ind2, ptab->space1[rc].info);
	return 1;
}


/* ���������� ������� �������� �� ����� �� ������ ��� ����� ����������� */
int D_Delete(Table *ptab) {
	int k1 = -1, k2 = -1, rc;
	input(&k1, &k2);
	rc = delete(ptab, k1, k2);
	printf("%s\n", errmsgs[rc]);
	return 1;
}

/* ���������� ������� ������ ���� ������� */
int D_Show(Table *ptab) {
	int rc;
	rc = output(ptab->space1);      // ������� ����� �� ������ ������������ ������ (��������, �� 1-���)
	printf("%s\n", errmsgs[rc]);
	return 1;
}


/* ��������� ������� ��������� � ������� ������ ��������. � ������� ���������� ����� ������������ ����������. */
int insert(Table *ptab, int k1, int k2, Type str) {
	int strt1, i1, strt2, i2;      // ��� ������� ������ �������� ������������ ��������������� ����� �����; ���� � ����� �� ������ ������� ��������� ���� - ������
	strt1 = i1 = I(k1);
	while (path1[i1].ind1 > 0) {
		if (path1[i1].key1 == k1)
			return 1;		     // ������� � �������� ������ ���� � �������
		i1 = (i1 + h) % SIZE;  // ��������� �������
		if (i1 == strt1)
			return 2;		 // ��������� � �������� ������� - ������� �����
	}
	strt2 = i2 = I(k2);
	while (path2[i2].ind2 > 0) {
		if (path2[i2].key2 == k2)
			return 1;
		i2 = (i2 + h) % SIZE;
		if (i2 == strt2)
			return 2;
	}
	// ���� ������� �������� �������� � ��� ������������, �� ��������� (���������)
	add(&ptab->space1[i1], k1, k2, str, i1 + 1, i2 + 1);
	add(&ptab->space2[i2], k1, k2, str, i1 + 1, i2 + 1);
	return 0;
}

/* ���������� �������� � ������������ space1/space2 �� ����� � �������� path */
void add(Item *path, int k1, int k2, Type str, int i1, int i2) {
	path->key1 = k1;
	path->key2 = k2;
	path->info = str;
	path->ind1 = i1;
	path->ind2 = i2;
}


/* ��������� ������� ���������� ��������� �� ����� ��� ���������� ������ �����. ��� ���� ��������� ����� ������� �� ����� ���������� ���������� */
int find(Table *ptab, int k1, int k2) {
	int i, strt;
	if (k2 < 0) {
		strt = i = I(k1);
		do {
			if (path1[i].ind1 > 0 && path1[i].key1 == k1)
				return i;               // ���������� ������ �������� �� ������� ������������
			i = (i + h) % SIZE;
			if (i == strt)
				break;
		} while (i != strt);
	}
	if (k1 < 0) {
		strt = i = I(k2);
		do {
			if (path2[i].ind1 > 0 && path2[i].key2 == k2)
				return (path2[i].ind1 - 1);
			i = (i + h) % SIZE;
			if (i == strt)
				break;
		} while (i != strt);
	}
	else {
		strt = i = I(k1);
		do {
			if (path1[i].ind1 > 0 && path1[i].key1 == k1 && path1[i].key2 == k2)
				return i;
			i = (i + h) % SIZE;
			if (i == strt)
				break;
		} while (i != strt);
	}
	return -1;
}

/* ��������� ������� �������� �������� �� ����� �/��� ��� ������. */
int delete(Table *ptab, int k1, int k2) {
	int rc = 4;
	int strt, i;
	if (k2 < 0) {
		strt = i = I(k1);
		do {
			if (path1[i].ind1 == 0)
				return 4;				// ���� �� ������
			else {
				if ((path1[i].ind1 != -1) && (path1[i].key1 == k1)) {
					path2[path1[i].ind2 - 1].ind2 = -1;
					path2[path1[i].ind2 - 1].ind2 = -1;
					path1[i].ind1 = -1;
					path1[i].ind2 = -1;
					return 0;
				}
				else
					i = (i + h) % SIZE;
			}
			if (i == strt)
				return 4;
		} while (i != strt);
	}
	if (k1 < 0) {
		strt = i = I(k2);
		do {
			if (path2[i].ind2 == 0)
				return 4;				// ���� �� ������
			else {
				if ((path2[i].ind2 != -1) && (path2[i].key2 == k2)) {
					path1[path2[i].ind1 - 1].ind1 = -1;
					path1[path2[i].ind1 - 1].ind2 = -1;
					path2[i].ind1 = -1;
					path2[i].ind2 = -1;
					return 0;
				}
				else
					i = (i + h) % SIZE;
			}
			if (i == strt)
				return 4;
		} while (i != strt);
	}
	else {
		strt = i = I(k1);
		do {
			if (path1[i].ind2 == 0)
				return 4;				// ���� �� ������
			else {
				if ((path1[i].ind1 != -1) && (path1[i].key1 == k1) && (path1[i].key2 == k2)) {
					path2[path1[i].ind1 - 1].ind1 = -1;
					path2[path1[i].ind1 - 1].ind2 = -1;
					path1[i].ind1 = -1;
					path1[i].ind2 = -1;
					return 0;
				}
				else
					i = (i + h) % SIZE;
			}
			if (i == strt)
				return 4;
		} while (i != strt);
	}
	return 1;
}


/* ��������� ������� ������ ������� (������ �� ����������). */
int output(Item *ptab) {
	int rc = 3;    // ���������� �������������� ������� ��� ������
	printf("\n|  ���� 1  |  ���� 2  |  ind 1  |  ind 2  |       ����������\n");
	for (int i = 0; i < SIZE; ++i)
		if (ptab[i].ind1 > 0) {
			printf("|%10d|%10d|%9d|%9d|   %s\n", ptab[i].key1, ptab[i].key2, ptab[i].ind1, ptab[i].ind2, ptab[i].info);
			rc = 0;
		}
	return rc;            // ��� �� ������)
}


